#include <iostream>
#include "portaudio.h"
#include "opus.h"
#include "PackBuilder.hh"
#include "SoundProperties.hh"
#include "Codec.hh"
#include "SoundControler.hh"


// TEST MAIN 1
int			main()
{
    PackBuilder	A;
    PackBuilder	B;

    A.getSoundControler().startInputStream();
    B.getSoundControler().startOutputStream();
    while (Pa_IsStreamActive(A.getSoundControler().getInputStream()))
      {
	B.setEncoded(A.getEncoded());
      }
    return (0);
}
