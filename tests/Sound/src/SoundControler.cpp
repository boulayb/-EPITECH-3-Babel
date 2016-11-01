#include <iostream>
#include "opus.h"
#include "portaudio.h"
#include "SoundProperties.hh"
#include "Codec.hh"
#include "SoundControler.hh"

SoundControler::SoundControler() : inputStream(NULL), outputStream(NULL), paError(paNoError)
{
    this->paError = Pa_Initialize();
    if (this->checkPaError())
        std::cerr << "Error: can't initialize portaudio." << std::endl;
    this->initInputParam();
    this->initOutputParam();
    this->openInputStream();
    this->openOutputStream();
    this->startInputStream();
    this->startOutputStream();
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

int			SoundControler::openInputStream()
{
    this->paError = Pa_OpenStream(&this->inputStream,
				  &this->inputParam,
				  NULL,
				  SAMPLE_RATE,
				  FRAMES_PER_BUFFER,
				  paClipOff,
				  SoundControler::recordCallback,
				  this);
    if (this->checkPaError())
	return (1);
    return (0);
}

int			SoundControler::openOutputStream()
{
    this->paError = Pa_OpenStream(&this->outputStream,
    				  &this->outputParam,
    				  NULL,
    				  SAMPLE_RATE,
    				  FRAMES_PER_BUFFER,
    				  paClipOff,
    				  SoundControler::playCallback,
    				  this);
    if (this->checkPaError())
	return (1);
    return (0);
}

int			SoundControler::startInputStream()
{
    this->paError = Pa_StartStream(this->inputStream);
    if (this->checkPaError())
	return (1);
    return (0);
}

int			SoundControler::startOutputStream()
{
    this->paError = Pa_StartStream(this->outputStream);
    if (this->checkPaError())
	return (1);
    return (0);
}

int			SoundControler::stopInputStream()
{
    this->paError = Pa_StopStream(this->inputStream);
    if (this->checkPaError())
	return (1);
    return (0);
}

int			SoundControler::stopOutputStream()
{
    this->paError = Pa_StopStream(this->outputStream);
    if (this->checkPaError())
	return (1);
    return (0);
}

int			SoundControler::recordCallback(const void *inputBuffer,
						       void *outputBuffer,
						       unsigned long framesPerBuffer,
						       const PaStreamCallbackTimeInfo* timeInfo,
						       PaStreamCallbackFlags statusFlags,
						       void *userData)
{
    SoundControler	*data;
    const SAMPLE	*rptr;
    const SAMPLE	*wptr;
    
    std::cout << "this->recordCallback();" << std::endl;
    data = (SoundControler *)userData;
    rptr = (const SAMPLE *)inputBuffer;

    // CALL data->codec.encodeData();
    
    (void)data;
    (void)rptr;
    (void)wptr;
    (void)inputBuffer;
    (void)outputBuffer;
    (void)framesPerBuffer;
    (void)timeInfo;
    (void)statusFlags;
    return (paContinue);
}

int			SoundControler::playCallback(const void *inputBuffer,
						     void *outputBuffer,
						     unsigned long framesPerBuffer,
						     const PaStreamCallbackTimeInfo* timeInfo,
						     PaStreamCallbackFlags statusFlags,
						     void *userData)
{
    SoundControler	*data;
    const SAMPLE	*rptr;
    
    std::cout << "this->playCallback();" << std::endl;
    
    data = (SoundControler *)userData;
    rptr = (const SAMPLE *)outputBuffer;

    // CALL data->codec.decodeData();
    
    (void)data;
    (void)rptr;    
    (void)inputBuffer;
    (void)outputBuffer;
    (void)framesPerBuffer;
    (void)timeInfo;
    (void)statusFlags;
    return (paContinue);
}

void			SoundControler::AudioIn()
{
    while ((this->paError = Pa_IsStreamActive(this->outputStream)) == 1)
	{
	    Pa_Sleep(1);
	}
    this->stopOutputStream();
    this->stopInputStream();
}

void			SoundControler::AudioOut()
{
    
}
