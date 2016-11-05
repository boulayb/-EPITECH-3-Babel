#ifndef _ACODEC_HH_
# define _ACODEC_HH_

class		ACodec
{

public:
    virtual ~ACodec() {};
    
    virtual EncPack	encodePack(DecPack const &) = 0;
    virtual DecPack	decodePack(EncPack const &) = 0;
    virtual int		initEncoder() = 0;
    virtual int		initDecoder() = 0;

};

#endif // _ACODEC_HH_
