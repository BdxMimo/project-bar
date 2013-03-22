#ifndef BARSOXPATTERNSOUNDSYSTEM_H
#define BARSOXPATTERNSOUNDSYSTEM_H

#include "BARDefines.h"

#include <vector>
#include <sox.h>
#include "BARSoxPositionNode.h"
#include "BARSoxTrack.h"
#include "BARSimpleResampler.h"

class BARSoxPatternSoundSystem
{
    protected:
        std::vector<sox_sample_t> sndBuf;
        std::vector<BARSoxPositionNode*> positionTrees;
        std::vector<BARSoxTrack> tracks;

        unsigned int tempo;
        unsigned int nBeats;
        unsigned int notesPerBeat;

        unsigned int beatLen;

        sox_signalinfo_t soundProperties;

        bool changed;

        void updatePositionTrees();

    public:
        BARSoxPatternSoundSystem();
        BARSoxPatternSoundSystem(unsigned int tempo, unsigned int nBeats, unsigned int notesPerBeat);

        unsigned int addTrack(const char* filename);
        unsigned int deleteTrack(unsigned int i);

        void changeTempo(unsigned int newVal);
        void changeNBeats(unsigned int newVal);
        void changeNotesPerBeat(unsigned int newVal);

        void changeVolume(unsigned int iTrack, unsigned int iNote, unsigned int v);
        void changeMasterVolume(unsigned int iTrack, unsigned int mv);

        void changeMute(unsigned int iTrack, bool mute);

        void updateSoundBuffer();
        void play(unsigned int loops=1);

        void preview(unsigned int iTrack);
};

#endif // BARSOXPATTERNSOUNDSYSTEM_H
