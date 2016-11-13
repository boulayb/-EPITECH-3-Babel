#include "Server.hpp"

int main(int argc, char *argv[])
{
  Server *babelServer;

  if (argc == 2 && argv[1] != nullptr)
  {
    try
    {
      int port = std::stoi(argv[1]);
      babelServer = new Server(port);
    }
    catch (std::invalid_argument &e) {
      std::cerr << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
    catch (std::out_of_range &e) {
      std::cerr << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  }
  else
    babelServer = new Server;
  babelServer->startServer();
  delete babelServer;
}

