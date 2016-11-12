#ifndef _ASOUNDCONTROLER_HH_
# define _ASOUNDCONTROLER_HH_

# include "SoundProperties.hh"

class			ASoundControler
{

public:

    virtual ~ASoundControler() {};

    virtual void		startInputStream() = 0;
    virtual void		startOutputStream() = 0;
    virtual void		stopInputStream() = 0;
    virtual void		stopOutputStream() = 0;
    virtual const DecPack	&getRecorded() = 0;
    virtual void		setToPlay(DecPack const &) = 0;

};

#endif // _ASOUNDCONTROLER_HH_
