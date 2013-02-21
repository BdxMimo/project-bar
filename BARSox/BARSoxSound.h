#ifndef BARSOXSOUND_H
#define BARSOXSOUND_H

#define AUDIO_DRIVER    "waveaudio"

#include <sox.h>

/**
 * @brief libSoX wrapper for one sound.
 * @author Hugo Duprat <a href="mailto:hugo.duprat@gmail.com">[Contact]</a>
 */
class BARSoxSound
{
    private:
        sox_format_t* sound;
        sox_format_t* audioOutput;
        sox_sample_t* buffer;
        double duration;

        bool sharedSound;
        bool memorizeBuffer;

        static int instances;

        void unload();
        bool init();
        void quit();

    public:
        BARSoxSound();
        BARSoxSound(const char* filename);
        BARSoxSound(sox_format_t* sound);

        double getDuration();
        const char* getFilename();

        bool load(char* filename);
        bool load(sox_format_t* sound);
        bool play();

        ~BARSoxSound();
};

#endif // BARSOXSOUND_H
