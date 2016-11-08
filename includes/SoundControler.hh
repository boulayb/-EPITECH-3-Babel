#ifndef _SOUNDCONTROLER_HH_
# define _SOUNDCONTROLER_HH_

# include "ASoundControler.hh"

class			SoundControler : public ASoundControler
{

private:
    Codec		codec;

    PaStreamParameters  inputParam;
    PaStreamParameters  outputParam;

    PaStream*           inputStream;
    PaStream*           outputStream;
    
    PaError             paError;

    bool		isRunning;
    
    DecPack		decPack;
    EncPack		encPack;
    
public:
    SoundControler();
    SoundControler(SoundControler const&);
    ~SoundControler();

    SoundControler& operator=(SoundControler const&);

private:
    bool		checkPaError();
    void		initInputParam();
    void		initOutputParam();
    void		openInputStream();
    void		openOutputStream();
    void		startInputStream();
    void		startOutputStream();
    void		stopInputStream();
    void		stopOutputStream();

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
    
public:
    void		setDecPack(DecPack const &pack);
    const DecPack	&getDecPack();

    void		setEncPack(EncPack const &pack);
    const EncPack	&getEncPack();

    // TEMPORARY ~ use this method to test audio in/out
    void		testAudio();
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

};

#endif // _SOUNDCONTROLER_HH_
