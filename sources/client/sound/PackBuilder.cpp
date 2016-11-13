#include "PackBuilder.hh"

PackBuilder::PackBuilder()
{

}

PackBuilder::~PackBuilder()
{

}

#include <iostream>
const EncPack		PackBuilder::getEncoded()
{
    std::cout << "ok" << std::endl;
    EncPack		encoded = this->codec.encodePack(this->soundControler.getRecorded());
    std::cout << "end" << std::endl;

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
