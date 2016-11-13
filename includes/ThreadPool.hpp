#ifndef THREADPOOL_HPP_
# define THREADPOOL_HPP_

# include <thread>
# include <mutex>
# include <queue>
# include <condition_variable>
# include <vector>
# include <functional>
# include <utility>
# include <iostream>

template<typename T>
class ThreadPool
{
  public:
    ThreadPool(int numberOfThreads = 4)
    {
      this->_finished = false;
      this->_shutDown = false;
      this->_currentTasks = 0;
      for(int i = 0; i < numberOfThreads; ++i)
      {
        this->_threadList.emplace_back(std::thread(&ThreadPool::task, this));
      }
    }

    ~ThreadPool()
    {
      if (!_finished)
      {
        this->shutDown();
      }
    }
    void putTaskInQueue(std::function<void(ThreadPool &, T )> f,
                        T &functionParameter)
    {
      {
        std::unique_lock<std::mutex> lock(this->_mutex);
        std::pair<T, std::function<void(ThreadPool &, T)>> pair(functionParameter, f);
        this->_tasks.push(pair);
        this->_currentTasks++;
      }
      this->_cond.notify_one();
    }

    void shutDown()
    {
      {
        std::unique_lock<std::mutex> lock(this->_mutex);
        this->_shutDown = true;
      }
      this->_cond.notify_all();
      for(std::thread &thread : this->_threadList)
      {
        thread.join();
      }
      this->_threadList.clear();
      this->_finished = true;
    }

    int getCurrentTasks() const
    {
      return this->_currentTasks;
    }

  private:
    void task()
    {
      std::function<void(ThreadPool &, T)> currentTask;
      T parameter;

      while (true)
      {
        {
          std::unique_lock<std::mutex> lock(this->_mutex);
          this->_cond.wait(lock, [this]
          {
            return !this->_tasks.empty() || this->_shutDown;
          });
          if (this->_shutDown && this->_tasks.empty())
          {
            return;
          }
          currentTask = this->_tasks.front().second;
          parameter = this->_tasks.front().first;
          this->_tasks.pop();
        }
        currentTask(*this, parameter);
        {
          std::unique_lock<std::mutex> lock(this->_mutex);
          this->_currentTasks--;
        }
      }
    }

    std::vector<std::thread>            _threadList;
    std::mutex                          _mutex;
    std::queue<std::pair<T, std::function<void(ThreadPool &, T)>>> _tasks;
    std::condition_variable              _cond;
    bool                                 _finished;
    bool                                 _shutDown;
    int                                  _currentTasks;
};

#endif /* THREADPOOL_HPP_ */
