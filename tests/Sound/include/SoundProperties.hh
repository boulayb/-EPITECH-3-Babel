#ifndef _SOUNDPROPERTIES_HH_
# define _SOUNDPROPERTIES_HH_

# define APPLICATION OPUS_APPLICATION_VOIP
# define PA_SAMPLE_TYPE paFloat32
# define SAMPLE_RATE 48000
# define FRAMES_PER_BUFFER 480
# define CHANNEL 1
# define DECODE_FEC 0

typedef float SAMPLE;

struct			EncPack
{
    int			size;
    unsigned char	*data;
};

struct			DecPack
{
    int			size;
    SAMPLE		*data;
};

# endif // _SOUNDPROPERTIES_HH_
