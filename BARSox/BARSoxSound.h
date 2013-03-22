#ifndef BARSOXSOUND_H
#define BARSOXSOUND_H

#include "BARDefines.h"

#include <sox.h>

/**
 * @brief libSoX wrapper for one sound.
 * @author Hugo Duprat [<a href="mailto:hugo.duprat@gmail.com">Contact</a>]
 * @date 2/21/2013
 */
class BARSoxSound
{
    private:
        sox_format_t* sound;
        sox_sample_t* buffer;
        sox_format_t* audioOutput;
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

        sox_format_t* getFormat();
        sox_sample_t* getBuffer();

        ~BARSoxSound();
};

#endif // BARSOXSOUND_H
