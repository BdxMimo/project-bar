#include "BARSoxTrack.h"

using namespace std;

/**
 * @brief Default constructor.
 */
BARSoxTrack::BARSoxTrack() : masterVolume(100), nBeats(4), notesPerBeat(2), mute(false)
{
}

/**
 * @brief Constructor.
 * @param filename Filename of the track sound.
 * @param nBeats Number of beats in the track.
 * @param notesPerBeat Number of notes per beat in the track.
 * @param masterVolume Master volume of the track.
 *
 * @todo Deal with filename to get the trackSoundBuffer and the beatTrees,
 * and take the case <tt>audioOutput == NULL</tt> in account.
 */
BARSoxTrack::BARSoxTrack(const char *filename, unsigned int nBeats, unsigned int notesPerBeat, unsigned int masterVolume)
{
    this->masterVolume = masterVolume;
    this->mute = false;
    this->nBeats = nBeats;
    this->notesPerBeat = notesPerBeat;

    sox_format_t* sound = sox_open_read(filename, NULL, NULL, NULL);

    trackSoundBuffer.resize(sound->signal.length);
    sox_read(sound, &trackSoundBuffer[0], sound->signal.length);

    volumeTrees.clear();
    volumeTrees.resize(nBeats, BARSoxNode<unsigned int>(0));
}

void BARSoxTrack::updateVolumeTrees(unsigned int npbBegin, unsigned int npbEnd)
{
    while (npbBegin != npbEnd) {
        if (npbBegin < npbEnd) {
            for (int i=0; i < nBeats; i++) {
                volumeTrees[i].divideLeaves();
            }
            npbBegin*=2;
        } else {
            for (int i=0; i < nBeats; i++) {
                volumeTrees[i].mergeLeaves();
            }
            npbBegin/=2;
        }
    }
}

void BARSoxTrack::nBeatsChanged(unsigned int newVal)
{
    if (nBeats < newVal) {
        BARSoxNode<unsigned int> node;

        for(unsigned int elts = 1; elts != notesPerBeat; elts *= 2) {
            node.divideLeaves();
        }

        volumeTrees.resize(newVal, node);
    } else if (nBeats > newVal) {
        volumeTrees.resize(newVal);
    }

    nBeats = newVal;
}
