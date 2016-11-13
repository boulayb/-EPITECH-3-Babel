#ifndef _APACKBUILDER_HH_
# define _APACKBUILDER_HH_

# include "SoundProperties.hh"

class			APackBuilder
{

public:
    virtual ~APackBuilder() {};

    virtual const EncPack		getEncoded() = 0;
    virtual void			setEncoded(EncPack const *pack) = 0;

};

#endif // _APACKBUILDER_HH_
