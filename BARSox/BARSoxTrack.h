#ifndef BARSOXTRACK_H
#define BARSOXTRACK_H

#include "BARSoxSound.h"
#include <vector>

#ifndef AUDIO_DRIVER
    #define AUDIO_DRIVER    "waveaudio"
#endif

/**
 * @brief The BARSoxTrack class handles data for one track.
 * A track contains only one kind of sound, repeated along units (corresponding to eighth notes in the current tempo).
 * @author Hugo Duprat [<a href="mailto:hugo.duprat@gmail.com">Contact</a>]
 * @date 2/21/2013
 */
class BARSoxTrack
{
    private:
        BARSoxSound sound;
        unsigned int tempo;
        float masterVolume;
        std::vector<float> units;

        sox_format_t* soundFormat;
        sox_format_t* audioOutput;
        std::vector<sox_sample_t> buffer;
        double sampleRate;
        unsigned int unitLength;
        sox_uint64_t soundLength;


    public:
        BARSoxTrack();
        BARSoxTrack(BARSoxSound sound, std::vector<sox_sample_t>& buffer, float masterVolume = 1,
                     unsigned int tempo = 120, sox_format_t* audioOutput = NULL);
        BARSoxTrack(BARSoxSound sound, float masterVolume, unsigned int tempo, unsigned int nbUnits, sox_format_t *audioOutput = NULL);

        bool preview();

        unsigned int getTempo() const;
        float getMasterVolume() const;

        void setMasterVolume(float vol);
        void setTempo(unsigned int t);

        bool updateUnit(unsigned int i, float masterVol, float vol);

        bool playUnit(unsigned int i);
        bool play();

        ~BARSoxTrack();
};

#endif // BARSOXTRACK_H
