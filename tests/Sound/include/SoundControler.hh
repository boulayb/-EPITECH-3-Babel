#ifndef _SOUNDCONTROLER_HH_
# define _SOUNDCONTROLER_HH_

class			SoundControler
{

private:
    Codec		codec;

    PaStreamParameters  inputParam;
    PaStreamParameters  outputParam;

    PaStream*           inputStream;
    PaStream*           outputStream;
    
    PaError             paError;
    
public:
    SoundControler();
    SoundControler(SoundControler const&);
    ~SoundControler();

    SoundControler& operator=(SoundControler const&);

private:
    bool		checkPaError();
    void		initInputParam();
    void		initOutputParam();
    int			openInputStream();
    int			openOutputStream();
    int			startInputStream();
    int			startOutputStream();
    int			stopInputStream();
    int			stopOutputStream();
        
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

    /* TMP */
public:
    void		AudioIn();
    void		AudioOut();

    
};

#endif // _SOUNDCONTROLER_HH_
