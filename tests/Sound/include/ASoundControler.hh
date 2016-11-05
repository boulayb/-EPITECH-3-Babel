#ifndef _ASOUNDCONTROLER_HH_
# define _ASOUNDCONTROLER_HH_

class			ASoundControler
{

public:

    virtual ~ASoundControler() {};

    virtual void	initInputParam() = 0;
    virtual void	initOutputParam() = 0;
    virtual void	openInputStream() = 0;
    virtual void	openOutputStream() = 0;
    virtual void	startInputStream() = 0;
    virtual void	startOutputStream() = 0;
    virtual void	stopInputStream() = 0;
    virtual void	stopOutputStream() = 0;

};

#endif // _ASOUNDCONTROLER_HH_
