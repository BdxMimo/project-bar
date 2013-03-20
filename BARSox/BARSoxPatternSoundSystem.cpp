#include "BARSoxPatternSoundSystem.h"

using namespace std;

BARSoxPatternSoundSystem::BARSoxPatternSoundSystem()
{
    tempo = 60;
    nBeats = 4;
    notesPerBeat = 2;
    changed = true;

    soundProperties.channels = 2;               //stereo by default
    soundProperties.rate = 44100;               //44100 Hz by default

    beatLen = 60*soundProperties.channels*soundProperties.rate/tempo;
    sndBuf.resize(beatLen*nBeats);

    soundProperties.length = beatLen*nBeats;    //number of samples in the sound buffer
    soundProperties.precision = 0;
    soundProperties.mult = NULL;

    updatePositionTrees();

    tracks.resize(0);
}

BARSoxPatternSoundSystem::BARSoxPatternSoundSystem(unsigned int tempo, unsigned int nBeats, unsigned int notesPerBeat)
{
    this->tempo = tempo;
    this->nBeats = nBeats;
    this->notesPerBeat = notesPerBeat;
    this->changed = true;

    soundProperties.channels = 2;               //stereo by default
    soundProperties.rate = 44100;               //44100 Hz by default

    beatLen = 60*soundProperties.channels*soundProperties.rate/tempo;
    sndBuf.resize(beatLen*nBeats);

    soundProperties.length = beatLen*nBeats;    //number of samples in the sound buffer
    soundProperties.precision = 0;
    soundProperties.mult = NULL;

    updatePositionTrees();

    tracks.clear();
}

unsigned int BARSoxPatternSoundSystem::addTrack(const char *filename)
{
    tracks.push_back(BARSoxTrack(filename, nBeats, notesPerBeat));
    changed = true;

    return tracks.size();
}

unsigned int BARSoxPatternSoundSystem::deleteTrack(unsigned int i)
{
    tracks.erase(tracks.begin()+i);
    changed = true;

    return tracks.size();
}

void BARSoxPatternSoundSystem::changeTempo(unsigned int newVal)
{
    tempo = newVal;
    beatLen = 60*88200/tempo;

    sndBuf.resize(beatLen*nBeats);
    soundProperties.length = beatLen*nBeats;

    updatePositionTrees();
    changed = true;
}

void BARSoxPatternSoundSystem::changeNBeats(unsigned int newVal)
{
    //change the tracks with the new value (if identical, no need to change)
    if (nBeats != newVal) {
        for (unsigned int i=0; i<tracks.size(); i++) {
            tracks[i].nBeatsChanged(newVal);
        }
        changed = true;
    }

    if (nBeats > newVal) {
        nBeats = newVal;
        positionTrees.resize(newVal);
    } else if (nBeats < newVal) {
        sox_sample_t* pos = &sndBuf[nBeats*beatLen];
        sox_uint64_t len = beatLen;

        for (unsigned int i=nBeats; i<newVal; i++) {
            positionTrees.push_back(new BARSoxPositionNode(0, pos, len));
            for (unsigned int elts=1; elts != notesPerBeat; elts *= 2) {
                positionTrees.back()->divideLeaves();
            }
            pos += len;
        }
    }

    sndBuf.resize(beatLen*newVal,0);
    soundProperties.length = beatLen*newVal;

    nBeats = newVal;
}

void BARSoxPatternSoundSystem::changeNotesPerBeat(unsigned int newVal)
{
    if (notesPerBeat != newVal) {
        for (unsigned int i=0; i<tracks.size(); i++) {
            tracks[i].notesPerBeatChanged(newVal);
        }

        notesPerBeat = newVal;
        updatePositionTrees();
        changed = true;
    }
}

void BARSoxPatternSoundSystem::changeVolume(unsigned int iTrack, unsigned int iNote, unsigned int v)
{
    if (iTrack < tracks.size()) {
        tracks[iTrack].setVolumeAt(iNote, v);
        changed = true;
    }
}

void BARSoxPatternSoundSystem::changeMasterVolume(unsigned int iTrack, unsigned int mv)
{
    if (iTrack < tracks.size()) {
        tracks[iTrack].setMasterVolume(mv);
        changed = true;
    }
}

void BARSoxPatternSoundSystem::changeMute(unsigned int iTrack, bool mute)
{
    if (iTrack < tracks.size()) {
        tracks[iTrack].setMute(mute);
        changed = true;
    }
}


void BARSoxPatternSoundSystem::updatePositionTrees()
{
    positionTrees.clear();

    sox_sample_t* pos = &sndBuf[0];
    sox_uint64_t len = beatLen;

    for (unsigned int i=0; i<nBeats; i++) {
        positionTrees.push_back(new BARSoxPositionNode(0, pos, len));
        for (unsigned int elts=1; elts != notesPerBeat; elts *= 2) {
            positionTrees.back()->divideLeaves();
        }
        pos += len;
    }
}

void BARSoxPatternSoundSystem::updateSoundBuffer()
{
    BARSoxTrack track;
    BARSoxPositionNode* posNode;
    sox_sample_t* position = NULL;
    vector<sox_sample_t> trackBuf;

    unsigned int masterVolume = 0;
    unsigned int volume = 0;

    unsigned int i = 0, j = 0, beat = 0, note = 0;

    sox_uint64_t bufLen = sndBuf.size();

    sndBuf.clear();
    sndBuf.resize(bufLen,0);

    for (i=0; i<tracks.size(); i++) {
        track = tracks[i];
        masterVolume = track.getMasterVolume();

        if (!track.isMute() && masterVolume > 0) {
            trackBuf = track.getTrackSoundBuffer();

            for (beat=0; beat<nBeats; beat++) {
                posNode = positionTrees[beat];

                for (note=0; note<notesPerBeat; note++) {
                    position = posNode->getAt(note).pos;
                    volume = track.getVolumeAt(beat*notesPerBeat+note);

                    if (volume > 0) {
                        for(j=0; j<trackBuf.size() && position != &sndBuf.back(); j++) {
                            *position += volume*(masterVolume*trackBuf[j]/100)/100;
                            position++;
                        }
                    }
                }
            }
        }
    }
}

void BARSoxPatternSoundSystem::play()
{
    if (changed) {
        updateSoundBuffer();
        changed = false;
    }

    sox_format_t* audioOutput = sox_open_write("default", &soundProperties, NULL, AUDIO_DRIVER, NULL, NULL);

    BARSoxPositionNode* beatNode;
    BARSoxBufferPos noteBufPos;
    unsigned int note = 0;

    sox_uint64_t i = 0, imax = 0;

    for (unsigned int beat = 0; beat < nBeats; beat++) {
        beatNode = positionTrees[beat];
        for (note = 0; note < notesPerBeat; note++) {
            noteBufPos = beatNode->getAt(note);

            imax = noteBufPos.len - MAX_SAMPLES;

            for (i=noteBufPos.pos-&sndBuf[0]; i<imax; i+=MAX_SAMPLES) {
                sox_write(audioOutput, &sndBuf[i], MAX_SAMPLES);
            }
            //for the rest
            sox_write(audioOutput, &sndBuf[i], noteBufPos.len-i);
        }
    }
}

void BARSoxPatternSoundSystem::preview(unsigned int iTrack)
{
    if (iTrack < tracks.size()) {
        vector<sox_sample_t> trackBuf = tracks[iTrack].getTrackSoundBuffer();
        sox_signalinfo_t prevProperties;

        prevProperties.channels = soundProperties.channels;
        prevProperties.rate = soundProperties.rate;
        prevProperties.mult = soundProperties.mult;
        prevProperties.precision = soundProperties.precision;

        prevProperties.length = trackBuf.size();

        sox_format_t* audioOutput = sox_open_write("default", &prevProperties, NULL, AUDIO_DRIVER, NULL, NULL);
        sox_uint64_t imax = prevProperties.length - MAX_SAMPLES;
        sox_uint64_t i=0;
        for (i=0; i<imax; i+=MAX_SAMPLES) {
            sox_write(audioOutput, &trackBuf[i], MAX_SAMPLES);
        }
        //for the rest
        sox_write(audioOutput, &trackBuf[i], prevProperties.length-i);
        sox_close(audioOutput);
    }
}
