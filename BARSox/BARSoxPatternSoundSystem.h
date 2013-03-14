#ifndef BARSOXPATTERNSOUNDSYSTEM_H
#define BARSOXPATTERNSOUNDSYSTEM_H

#include <vector>
#include <sox.h>
#include "BARSoxPositionNode.h"
#include "BARSoxTrack.h"

class BARSoxPatternSoundSystem
{
    protected:
        std::vector<sox_sample_t> sndBuf;
        std::vector<BARSoxPositionNode> positionTrees;
        std::vector<BARSoxTrack> tracks;

        unsigned int tempo;
        unsigned int nBeats;
        unsigned int notesPerBeat;

        unsigned int beatLen;

        void updatePositionTrees();

    public:
        BARSoxPatternSoundSystem();
        BARSoxPatternSoundSystem(unsigned int tempo, unsigned int nBeats, unsigned int notesPerBeat);

        void addTrack(const char* filename);
        void deleteTrack(unsigned int i);

        void changeTempo(unsigned int newVal);
        void changeNBeats(unsigned int newVal);
        //void changeNotesPerBeat(unsigned int newVal);
};

#endif // BARSOXPATTERNSOUNDSYSTEM_H
