#include <iostream>
#include "portaudio.h"
#include "opus.h"
#include "SoundProperties.hh"
#include "Codec.hh"
#include "SoundControler.hh"

int			main()
{
    SoundControler	asound;

    asound.AudioIn();
    return (0);
}
