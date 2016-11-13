#ifndef _SOUNDPROPERTIES_HH_
# define _SOUNDPROPERTIES_HH_

# include <vector>

# define APPLICATION OPUS_APPLICATION_VOIP
# define PA_SAMPLE_TYPE paFloat32
# define SAMPLE_RATE 48000
# define FRAMES_PER_BUFFER 1920
# define CHANNEL 2
# define DECODE_FEC 0
# define SAMPLE_SILENCE 0

typedef float SAMPLE;

struct				EncPack
{
    int				size;
    std::vector<unsigned char>	data;
};

struct				DecPack
{
    int				size;
    std::vector<SAMPLE>		sample;
};

# endif // _SOUNDPROPERTIES_HH_
