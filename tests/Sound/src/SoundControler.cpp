#include <iostream>
#include "SoundControler.hh"

SoundControler::SoundControler() : inputStream(NULL), outputStream(NULL), paError(paNoError), isRunning(false)
{
    this->paError = Pa_Initialize();
    if (this->checkPaError())
        std::cerr << "Error: can't initialize portaudio." << std::endl;
    this->encPack.size = 0;    
    this->decPack.size = 0;    
    this->initInputParam();
    this->initOutputParam();
}

SoundControler::~SoundControler()
{
    if (this->inputStream)
        Pa_CloseStream(this->inputStream);
    if (this->outputStream)
        Pa_CloseStream(this->outputStream);
    Pa_Terminate();
}

SoundControler::SoundControler(SoundControler const &other)
{
    if (this != &other)
        {
            this->paError = other.paError;
            this->inputStream = other.inputStream;
            this->outputStream = other.outputStream;
        }
}

SoundControler &SoundControler::operator=(SoundControler const &other)
{
    if (this != &other)
	{
            this->paError = other.paError;
            this->inputStream = other.inputStream;
            this->outputStream = other.outputStream;
	}
    return (*this);
}

bool			SoundControler::checkPaError()
{
    if (this->paError != paNoError)
	{
	    std::cerr << "an error occured while using the portaudio stream" << std::endl;
	    std::cerr << "error number : " << this->paError << std::endl;
	    std::cerr << "error message : " << Pa_GetErrorText(this->paError) << std::endl;
	    if (this->inputStream)
		Pa_CloseStream(this->inputStream);
	    if (this->outputStream)
		Pa_CloseStream(this->outputStream);
	    Pa_Terminate();
	    return (true);
	}
    return (false);
}

void			SoundControler::initInputParam()
{
    this->inputParam.device = Pa_GetDefaultInputDevice();
    if (this->outputParam.device == paNoDevice)
	std::cerr << "Error: No default intput device." << std::endl;
    this->inputParam.channelCount = CHANNEL;
    this->inputParam.sampleFormat = PA_SAMPLE_TYPE;
    this->inputParam.suggestedLatency = Pa_GetDeviceInfo(this->inputParam.device)->defaultLowOutputLatency;
    this->inputParam.hostApiSpecificStreamInfo = NULL;
}

void			SoundControler::initOutputParam()
{
    this->outputParam.device = Pa_GetDefaultOutputDevice();
    if (this->outputParam.device == paNoDevice)
	std::cerr << "Error: No default output device." << std::endl;
    this->outputParam.channelCount = CHANNEL;
    this->outputParam.sampleFormat = PA_SAMPLE_TYPE;
    this->outputParam.suggestedLatency = Pa_GetDeviceInfo(this->outputParam.device)->defaultLowOutputLatency;
    this->outputParam.hostApiSpecificStreamInfo = NULL;
}

void			SoundControler::openInputStream()
{
    this->paError = Pa_OpenStream(&this->inputStream,
				  &this->inputParam,
				  NULL,
				  SAMPLE_RATE,
				  FRAMES_PER_BUFFER,
				  paClipOff,
				  SoundControler::recordCallback,
				  this);
    this->checkPaError();
}

void			SoundControler::openOutputStream()
{
    this->paError = Pa_OpenStream(&this->outputStream,
				  NULL,
    				  &this->outputParam,
    				  SAMPLE_RATE,
    				  FRAMES_PER_BUFFER,
    				  paClipOff,
    				  SoundControler::playCallback,
    				  this);
    this->checkPaError();
}

void			SoundControler::startInputStream()
{
    this->openInputStream();
    this->paError = Pa_StartStream(this->inputStream);
    this->isRunning = true;
    this->checkPaError();
}

void			SoundControler::startOutputStream()
{
    this->openOutputStream();
    this->paError = Pa_StartStream(this->outputStream);
    this->checkPaError();
}

void			SoundControler::stopInputStream()
{
    this->paError = Pa_StopStream(this->inputStream);
    this->isRunning = false;
    this->checkPaError();
}

void			SoundControler::stopOutputStream()
{
    this->paError = Pa_StopStream(this->outputStream);
    this->checkPaError();
}

int			SoundControler::recordCallback(const void *inputBuffer,
						                   void *,
                                           unsigned long framesPerBuffer,
						                   const PaStreamCallbackTimeInfo *,
                                           PaStreamCallbackFlags,
						                   void *userData)
{
    SoundControler	*soundControler = reinterpret_cast<SoundControler *>(userData);
    DecPack		decPack;

    decPack.size = framesPerBuffer * CHANNEL;
    decPack.sample.assign(reinterpret_cast<const float *>(inputBuffer), reinterpret_cast<const float *>(inputBuffer) + framesPerBuffer * CHANNEL);
    soundControler->setDecPack(decPack);
    soundControler->setEncPack(soundControler->codec.encodePack(decPack));
    // soundControler->setDecPack(soundControler->codec.decodePack(soundControler->getEncPack()));
    return (paContinue);
}

int			SoundControler::playCallback(const void *,
						     void *outputBuffer,
						     unsigned long,
						     const PaStreamCallbackTimeInfo *,
						     PaStreamCallbackFlags,
						     void *userData)
{
    SoundControler	*soundControler = reinterpret_cast<SoundControler *>(userData);
    DecPack		decPack = soundControler->getDecPack();
    // DecPack		decPack = soundControler->codec.decodePack(soundControler->getEncPack());
    SAMPLE		*tmp = decPack.sample.data();
    SAMPLE		*outputPtr = static_cast<SAMPLE *>(outputBuffer);

    if (soundControler->isRunning)
    	{
    	    for (int i = 0; i < decPack.size; i++)
    		*outputPtr++ = tmp[i];
    	}
    return (paContinue);
}

void			SoundControler::setDecPack(DecPack const &pack)
{
    this->decPack = pack;
}

const DecPack		&SoundControler::getDecPack()
{   
    return (this->decPack);
}

void			SoundControler::setEncPack(EncPack const &pack)
{
    this->encPack = pack;
}

const EncPack		&SoundControler::getEncPack()
{
    return (this->encPack);
}

void			SoundControler::testAudio()
{
    while ((this->paError = Pa_IsStreamActive(this->inputStream)) == 1)
    	{
    	    Pa_Sleep(1);
    	}
    this->stopOutputStream();
    this->stopInputStream();
}
