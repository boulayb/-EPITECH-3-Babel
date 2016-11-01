#include <iostream>
#include "opus.h"
#include "SoundProperties.hh"
#include "Codec.hh"

Codec::Codec() : opusError(OPUS_OK)
{
    this->initEncoder();
    this->initDecoder();
}

Codec::~Codec()
{
    opus_encoder_destroy(this->encoder);
    opus_decoder_destroy(this->decoder);
}

Codec::Codec(Codec const &other)
{
    if (this != &other)
	{
	    this->opusError = other.opusError;
	}
}

Codec &Codec::operator=(Codec const &other)
{
    if (this != &other)
        {
            this->opusError = other.opusError;
        }
    return (*this);
}

int			Codec::initEncoder()
{
    this->encoder = opus_encoder_create(SAMPLE_RATE, CHANNEL, APPLICATION, &this->opusError);
    if (this->opusError != OPUS_OK || this->encoder == NULL)
        return (1);
    return (0);
}

int			Codec::initDecoder()
{
    this->decoder = opus_decoder_create(SAMPLE_RATE, CHANNEL, &this->opusError);
    if (this->opusError != OPUS_OK || this->decoder == NULL)
        return (1);
    return (0);
}

EncPack			Codec::encodePack(DecPack const &decPack)
{
    EncPack		encPack;
    
    encPack.data = new unsigned char[FRAMES_PER_BUFFER * CHANNEL];
    if ((encPack.size = opus_encode_float(this->encoder, decPack.data, FRAMES_PER_BUFFER, encPack.data, decPack.size)) < 0)
	{
	    std::cerr << "error while encoding" << std::endl;
	}
    return (encPack);
}

DecPack			Codec::decodePack(EncPack const &encPack)
{
    DecPack		decPack;

    decPack.data = new SAMPLE[FRAMES_PER_BUFFER * CHANNEL];
    if ((decPack.size = opus_decode_float(this->decoder, encPack.data, encPack.size, decPack.data, FRAMES_PER_BUFFER, DECODE_FEC)) < 0)
	{
            std::cerr << "error while decoding" << std::endl;
        }
    return (decPack);
}
