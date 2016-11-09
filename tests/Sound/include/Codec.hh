#ifndef _CODEC_HH_
# define _CODEC_HH_

# include "opus.h"
# include "SoundProperties.hh"
# include "ACodec.hh"

class			Codec : public ACodec
{

private:
    OpusEncoder		*encoder;
    OpusDecoder		*decoder;

    int			opusError;

public:
    Codec();
    Codec(Codec const&);
    ~Codec();

    Codec& operator=(Codec const&);
    
    const EncPack	encodePack(DecPack const &);
    const DecPack	decodePack(EncPack const &);

private:
    int			initEncoder();
    int			initDecoder();
    
};

#endif // _CODEC_HH_
