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
 */
BARSoxTrack::BARSoxTrack(const char *filename, unsigned int nBeats, unsigned int notesPerBeat, unsigned int masterVolume)
{
    this->masterVolume = masterVolume;
    this->mute = false;
    this->nBeats = nBeats;
    this->notesPerBeat = notesPerBeat;

    sox_format_t* sound = sox_open_read(filename, NULL, NULL, NULL);

    properties = sound->signal;

    trackSoundBuffer.resize(properties.length);
    sox_read(sound, &trackSoundBuffer[0], properties.length);

    volumeTrees.clear();
    for (unsigned int beat = 0; beat < nBeats; beat++) {
        volumeTrees.push_back(new BARSoxNode<unsigned int>);
        for(unsigned int elts = 1; elts < notesPerBeat; elts *= 2) {
            volumeTrees.back()->divideLeaves();
        }
    }
}

void BARSoxTrack::updateVolumeTrees(unsigned int npbBegin, unsigned int npbEnd)
{
    while (npbBegin != npbEnd) {
        if (npbBegin < npbEnd) {
            for (unsigned int i=0; i < nBeats; i++) {
                volumeTrees[i]->divideLeaves();
            }
            npbBegin*=2;
        } else {
            for (unsigned int i=0; i < nBeats; i++) {
                volumeTrees[i]->mergeLeaves();
            }
            npbBegin/=2;
        }
    }
}

void BARSoxTrack::nBeatsChanged(unsigned int newVal)
{
    if (nBeats < newVal) {
        for (unsigned int beat = nBeats; beat < newVal; beat++) {
            volumeTrees.push_back(new BARSoxNode<unsigned int>());
            for(unsigned int elts = 1; elts != notesPerBeat; elts *= 2) {
                volumeTrees.back()->divideLeaves();
            }
        }
    } else if (nBeats > newVal) {
        volumeTrees.resize(newVal);
    }

    nBeats = newVal;
}

void BARSoxTrack::notesPerBeatChanged(unsigned int newVal)
{
    updateVolumeTrees(notesPerBeat, newVal);
    notesPerBeat = newVal;
}

const vector<sox_sample_t>& BARSoxTrack::getTrackSoundBuffer()
{
    return trackSoundBuffer;
}

unsigned int BARSoxTrack::getVolumeAt(unsigned int i)
{
    unsigned int beat = i/notesPerBeat;
    unsigned int note = i%notesPerBeat;

    if (beat>=nBeats) {
        return 0;
    }

    return mute ? 0 : volumeTrees[beat]->getAt(note);
}

void BARSoxTrack::setVolumeAt(unsigned int i, unsigned int vol)
{
    unsigned int beat = i/notesPerBeat;
    unsigned int note = i%notesPerBeat;

    if (beat<nBeats) {
        volumeTrees[beat]->setAt(note, vol);
    }
}

unsigned int BARSoxTrack::getMasterVolume()
{
    return masterVolume;
}

void BARSoxTrack::setMasterVolume(unsigned int mv)
{
    masterVolume = mv;
}

bool BARSoxTrack::isMute()
{
    return mute;
}

void BARSoxTrack::setMute(bool mute)
{
    BARSoxTrack::mute = mute;
}

sox_signalinfo_t BARSoxTrack::getProperties()
{
    return properties;
}

BARSoxTrack::~BARSoxTrack()
{

}
