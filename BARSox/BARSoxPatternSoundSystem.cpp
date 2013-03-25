#include "BARSoxPatternSoundSystem.h"

using namespace std;

BARSoxPatternSoundSystem::BARSoxPatternSoundSystem()
{
    sox_init();

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

    audioOutput = sox_open_write("default", &soundProperties, NULL, AUDIO_DRIVER, NULL, NULL);

    updatePositionTrees();

    tracks.clear();
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

    audioOutput = sox_open_write("default", &soundProperties, NULL, AUDIO_DRIVER, NULL, NULL);

    updatePositionTrees();

    tracks.clear();
}

unsigned int BARSoxPatternSoundSystem::addTrack(const char *filename)
{
    tracks.push_back(new BARSoxTrack(filename, nBeats, notesPerBeat));
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
            tracks[i]->nBeatsChanged(newVal);
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
            tracks[i]->notesPerBeatChanged(newVal);
        }

        notesPerBeat = newVal;
        updatePositionTrees();
        changed = true;
    }
}

void BARSoxPatternSoundSystem::changeVolume(unsigned int iTrack, unsigned int iNote, unsigned int v)
{
    if (iTrack < tracks.size()) {
        tracks[iTrack]->setVolumeAt(iNote, v);
        changed = true;
    }
}

void BARSoxPatternSoundSystem::changeMasterVolume(unsigned int iTrack, unsigned int mv)
{
    if (iTrack < tracks.size()) {
        tracks[iTrack]->setMasterVolume(mv);
        changed = true;
    }
}

void BARSoxPatternSoundSystem::changeMute(unsigned int iTrack, bool mute)
{
    if (iTrack < tracks.size()) {
        tracks[iTrack]->setMute(mute);
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
    BARSoxTrack* track = NULL;
    BARSoxPositionNode* posNode = NULL;
    sox_sample_t* position = NULL;
    vector<sox_sample_t> trackBuf;
    sox_signalinfo_t trackProperties;

    float masterVolume = 0;
    float volume = 0;

    float sampleVol = 0;

    float sample=0;

    unsigned int i = 0, j = 0, beat = 0, note = 0;

    sox_uint64_t bufLen = sndBuf.size();

    sndBuf.clear();
    sndBuf.resize(bufLen,0);

    for (i=0; i<tracks.size(); i++) {
        track = tracks[i];
        trackProperties = track->getProperties();
        masterVolume = track->getMasterVolume();

        if (!track->isMute() && masterVolume > 0) {
            trackBuf = track->getTrackSoundBuffer();
            BARSimpleResampler<sox_sample_t>::resample(trackBuf, trackProperties.rate, soundProperties.rate, true);

            for (beat=0; beat<nBeats; beat++) {
                posNode = positionTrees[beat];

                for (note=0; note<notesPerBeat; note++) {
                    position = posNode->getAt(note).pos;
                    volume = track->getVolumeAt(beat*notesPerBeat+note);

                    if (volume > 0) {
                        sampleVol = (volume/100)*(masterVolume/100);
                        for(j=0; j<trackBuf.size() && position != &sndBuf.back(); j++) {
                            sample = sampleVol*trackBuf[j];
                            if (sample > 0) {
                                if (*position <= (sox_sample_t)(INT_MAX - sample))
                                    *position += sample;
                                else
                                    *position = INT_MAX;
                            } else {
                                if (*position >= (sox_sample_t)(INT_MIN - sampleVol*trackBuf[j]))
                                    *position += sample;
                                else
                                    *position = INT_MIN;
                            }
                            position++;
                        }
                    }
                }
            }
        }
    }
}

void BARSoxPatternSoundSystem::playNote(unsigned int iNote)
{
    if (changed) {
        updateSoundBuffer();
        changed = false;
    }

    if (iNote < notesPerBeat*nBeats) {

        BARSoxPositionNode* beatNode;
        BARSoxBufferPos noteBufPos;

        sox_uint64_t i = 0, imax = 0, ibegin = 0;

        beatNode = positionTrees[iNote/notesPerBeat];
        noteBufPos = beatNode->getAt(iNote%notesPerBeat);

        ibegin = noteBufPos.pos-&sndBuf[0];
        imax = ibegin+noteBufPos.len - MAX_SAMPLES;

        for (i=ibegin; i<imax; i+=MAX_SAMPLES) {
            sox_write(audioOutput, &sndBuf[i], MAX_SAMPLES);
        }
        //for the rest
        sox_write(audioOutput, &sndBuf[i], ibegin+noteBufPos.len-i);
        emit endOfNoteDetected(iNote);
    }
}

void BARSoxPatternSoundSystem::play(unsigned int loops)
{
    if (changed) {
        updateSoundBuffer();
        changed = false;
    }

    audioOutput = sox_open_write("default", &soundProperties, NULL, AUDIO_DRIVER, NULL, NULL);

    BARSoxPositionNode* beatNode;
    BARSoxBufferPos noteBufPos;
    unsigned int note = 0;

    sox_uint64_t i = 0, imax = 0, ibegin = 0;

    for (unsigned int loop = 0; loop < (loops < 1 ? 1 : loops); loop++) {
        for (unsigned int beat = 0; beat < nBeats; beat++) {
            beatNode = positionTrees[beat];
            for (note = 0; note < notesPerBeat; note++) {
                noteBufPos = beatNode->getAt(note);

                ibegin = noteBufPos.pos-&sndBuf[0];
                imax = ibegin+noteBufPos.len - MAX_SAMPLES;

                for (i=ibegin; i<imax; i+=MAX_SAMPLES) {
                    sox_write(audioOutput, &sndBuf[i], MAX_SAMPLES);
                }
                //for the rest
                sox_write(audioOutput, &sndBuf[i], ibegin+noteBufPos.len-i);
                emit endOfNoteDetected(notesPerBeat*beat+note);
            }
        }
    }
}

void BARSoxPatternSoundSystem::preview(unsigned int iTrack)
{
    if (iTrack < tracks.size()) {
        vector<sox_sample_t> trackBuf = tracks[iTrack]->getTrackSoundBuffer();
        sox_signalinfo_t prevProperties = tracks[iTrack]->getProperties();

        BARSimpleResampler<sox_sample_t>::resample(trackBuf, prevProperties.rate, soundProperties.rate, prevProperties.channels == 2);

        prevProperties.rate = soundProperties.rate;
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

BARSoxPatternSoundSystem::~BARSoxPatternSoundSystem()
{
    for (unsigned int i = 0; i < positionTrees.size(); i++) {
        delete positionTrees.back();
        positionTrees.pop_back();
    }

    for (unsigned int i = 0; i < tracks.size(); i++) {
        delete tracks[i];
    }

    sox_quit();
}
