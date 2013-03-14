#include "BARSoxPatternSoundSystem.h"

using namespace std;

BARSoxPatternSoundSystem::BARSoxPatternSoundSystem()
{
    tempo = 60;
    nBeats = 4;
    notesPerBeat = 2;

    beatLen = 60*88200/tempo;
    sndBuf.resize(beatLen*nBeats);

    updatePositionTrees();

    tracks.resize(0);
}

BARSoxPatternSoundSystem::BARSoxPatternSoundSystem(unsigned int tempo, unsigned int nBeats, unsigned int notesPerBeat)
{
    this->tempo = tempo;
    this->nBeats = nBeats;
    this->notesPerBeat = notesPerBeat;

    beatLen = 60*88200/tempo;
    sndBuf.resize(beatLen*nBeats);

    updatePositionTrees();

    tracks.clear();
}

void BARSoxPatternSoundSystem::addTrack(const char *filename)
{
    tracks.push_back(BARSoxTrack(filename, nBeats, notesPerBeat));
}

void BARSoxPatternSoundSystem::deleteTrack(unsigned int i)
{
    tracks.erase(tracks.begin()+i);
}

void BARSoxPatternSoundSystem::changeTempo(unsigned int newVal)
{
    tempo = newVal;
    beatLen = 60*88200/tempo;

    updatePositionTrees();
}

void BARSoxPatternSoundSystem::changeNBeats(unsigned int newVal)
{
    if (nBeats != newVal) {
        for (unsigned int i=0; i<tracks.size(); i++) {
            tracks[i].nBeatsChanged(newVal);
        }
    }

    if (nBeats > newVal) {
        nBeats = newVal;
        positionTrees.resize(newVal);
        sndBuf.resize(beatLen*newVal);
    } else if (nBeats < newVal) {
        sox_sample_t* pos = &sndBuf[nBeats*beatLen];
        sox_uint64_t len = beatLen;

        for (unsigned int i=nBeats; i<newVal; i++) {
            BARSoxPositionNode tree(0, pos, len);
            for (unsigned int elts=1; elts != notesPerBeat; elts *= 2) {
                tree.divideLeaves();
            }

            positionTrees.push_back(tree);
            pos += len;
        }
    }

    nBeats = newVal;
}

void BARSoxPatternSoundSystem::updatePositionTrees()
{
    positionTrees.clear();

    sox_sample_t* pos = &sndBuf[0];
    sox_uint64_t len = beatLen;

    for (int i=0; i<nBeats; i++) {
        BARSoxPositionNode tree(0, pos, len);
        for (unsigned int elts=1; elts != notesPerBeat; elts *= 2) {
            tree.divideLeaves();
        }

        positionTrees.push_back(tree);
        pos += len;
    }
}
