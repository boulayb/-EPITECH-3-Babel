#include "PackBuilder.hh"

PackBuilder::PackBuilder()
{

}

PackBuilder::~PackBuilder()
{

}

const EncPack		PackBuilder::getEncoded()
{
    EncPack		encoded = this->codec.encodePack(this->soundControler.getRecorded());

    return (encoded);
}

void			PackBuilder::setEncoded(EncPack const *pack)
{
    DecPack		decoded = this->codec.decodePack(pack);
    this->soundControler.setToPlay(decoded);
}

SoundControler	&PackBuilder::getSoundControler()
{
    return (this->soundControler);
}

Codec		&PackBuilder::getCodec()
{
    return (this->codec);
}
