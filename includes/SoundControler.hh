#ifndef _SOUNDCONTROLER_HH_
# define _SOUNDCONTROLER_HH_

# include <mutex>
# include "portaudio.h"
# include "SoundProperties.hh"
# include "ASoundControler.hh"

class			SoundControler : public ASoundControler
{

private:
    PaStreamParameters  inputParam;
    PaStreamParameters  outputParam;

    PaStream*           inputStream;
    PaStream*           outputStream;
    
    PaError             paError;

    bool		isRunning;
    std::mutex mutex;
    DecPack		toPlay;
    DecPack		recorded;
public:
    SoundControler();
    SoundControler(SoundControler const&);
    ~SoundControler();

    SoundControler& operator=(SoundControler const&);

public:
    void		startInputStream();
    void		startOutputStream();
    void		stopInputStream();
    void		stopOutputStream();

    const DecPack	&getRecorded();
    void		setToPlay(DecPack const &pack);

  // temp
    PaStream		*getInputStream();

private:
    void		setRecorded(DecPack const &pack);
    const DecPack	&getToPlay();
  
private:
    bool		checkPaError();
    void		initInputParam();
    void		initOutputParam();
    void		openInputStream();
    void		openOutputStream();

    static int		recordCallback(const void *inputBuffer,
				       void *outputBuffer,
				       unsigned long framesPerBuffer,
				       const PaStreamCallbackTimeInfo* timeInfo,
				       PaStreamCallbackFlags statusFlags,
				       void *userData);

    static int		playCallback(const void *inputBuffer,
				     void *outputBuffer,
				     unsigned long framesPerBuffer,
				     const PaStreamCallbackTimeInfo* timeInfo,
				     PaStreamCallbackFlags statusFlags,
				     void *userData);

};

#endif // _SOUNDCONTROLER_HH_
