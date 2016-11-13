#ifndef _PACKBUILDER_HH_
# define _PACKBUILDER_HH_

# include "SoundControler.hh"
# include "Codec.hh"
# include "APackBuilder.hh"

class				PackBuilder : public APackBuilder
{
private:
    Codec			codec;
    SoundControler		soundControler;
  
public:
    PackBuilder();
    ~PackBuilder();

    const EncPack		getEncoded();
    void			setEncoded(EncPack const *pack);

    SoundControler		&getSoundControler();
    Codec			&getCodec();
};

#endif // _PACKBUILDER_HH_
