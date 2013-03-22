#ifndef BARDEFINES_H
#define BARDEFINES_H

    #ifndef AUDIO_DRIVER
        #ifdef __WIN32
            #define AUDIO_DRIVER    "waveaudio"
        #elif __APPLE
            #define AUDIO_DRIVER    "coreaudio"
        #elif __linux__
            #define AUDIO_DRIVER    "alsa"
        #endif
    #endif

    #ifndef MAX_SAMPLES
        #define MAX_SAMPLES     2048
    #endif

#endif // BARDEFINES_H
