#include "BARSoxTrack.h"

using namespace std;

/**
 * @brief Default constructor.
 */
BARSoxTrack::BARSoxTrack() : tempo(0), masterVolume(0), soundFormat(NULL), audioOutput(NULL), sampleRate(0), unitLength(0)
{
}

/**
 * @brief Constructor.
 * @param sound The sound that is played on the track.
 * @param masterVolume The volume of the track.
 * @param tempo The tempo of the track (beats per minute).
 * @param buffer A sound buffer (e.g. the buffer of the BARSoxSoundSystem).
 * @param audioOutput The audio output for playing the track.
 */
BARSoxTrack::BARSoxTrack(BARSoxSound sound, std::vector<sox_sample_t> &buffer, float masterVolume, unsigned int tempo, sox_format_t *audioOutput)
{
    BARSoxTrack::sound = sound;
    BARSoxTrack::soundFormat = sound.getFormat();
    BARSoxTrack::tempo = tempo;
    BARSoxTrack::masterVolume = masterVolume;

    BARSoxTrack::buffer = buffer;
    BARSoxTrack::sampleRate = soundFormat != NULL ? soundFormat->signal.rate*soundFormat->signal.channels : 44100;
    BARSoxTrack::units = vector<float>(buffer.size()/sampleRate, 0);
    BARSoxTrack::audioOutput = audioOutput;

    if (audioOutput == NULL) {
        audioOutput = sox_open_write("default", &soundFormat->signal, &soundFormat->encoding, AUDIO_DRIVER, &soundFormat->oob, NULL);
    }

    BARSoxTrack::unitLength = (unsigned int)(sampleRate*60.0/tempo);
    BARSoxTrack::soundLength = soundFormat->signal.length;
}

/**
 * @brief Constructor (best suited for testing a track alone)
 * @param sound The sound that is played on the track.
 * @param masterVolume The volume of the track.
 * @param tempo The tempo of the track (beats per minute).
 * @param nbUnits Number of units in the track (a unit per beat).
 * @param audioOutput The audio output for playing the track.
 */
BARSoxTrack::BARSoxTrack(BARSoxSound sound, float masterVolume, unsigned int tempo, unsigned int nbUnits, sox_format_t *audioOutput)
{
    BARSoxTrack::sound = sound;
    BARSoxTrack::soundFormat = sound.getFormat();
    BARSoxTrack::tempo = tempo;
    BARSoxTrack::masterVolume = masterVolume;

    BARSoxTrack::sampleRate = soundFormat != NULL ? soundFormat->signal.rate*soundFormat->signal.channels : 44100;
    BARSoxTrack::units = vector<float>(nbUnits);
    BARSoxTrack::buffer = vector<sox_sample_t>(nbUnits*sampleRate,0);
    BARSoxTrack::audioOutput = audioOutput;

    if (audioOutput == NULL) {
        audioOutput = sox_open_write("default", &soundFormat->signal, &soundFormat->encoding, AUDIO_DRIVER, &soundFormat->oob, NULL);
    }

    BARSoxTrack::unitLength = (unsigned int)(sampleRate*60.0/tempo);
    BARSoxTrack::soundLength = soundFormat->signal.length;
}

/**
 * @brief Plays the sound associated to the track.
 * @return @c true if the sound was played correctly, @c false otherwise.
 */
bool BARSoxTrack::preview()
{
    return sound.play();
}

/**
 * @brief Gets the tempo of the track (in beats per minute).
 * @return The tempo of the track.
 */
unsigned int BARSoxTrack::getTempo() const
{
    return tempo;
}

/**
 * @brief Gets the master volume of the track.
 * @return The master volume.
 */
float BARSoxTrack::getMasterVolume() const
{
    return masterVolume;
}

/**
 * @brief Sets the master volume of the track: 0 for mute, 1 for max volume.
 * @param vol The volume to set.
 */
void BARSoxTrack::setMasterVolume(float vol)
{
    masterVolume = vol < 0 ? 0 : vol > 1 ? 1 : vol;
}

/**
 * @brief Sets the tempo of the track: minimum is 20 beats per minute.
 * @param t The tempo to set.
 */
void BARSoxTrack::setTempo(unsigned int t)
{
    tempo = t <=20 ? 20 : t;
}

/**
 * @brief For every modification of a track (unit volume, etc.) we update the concerned units.
 * If the total volume difference is zero, there's nothing to do.
 * @param i The number of the unit.
 * @param masterVol The master volume (in case of change)
 * @param vol The unit volume (in case of change)
 * @return @c true in most cases.
 */
bool BARSoxTrack::updateUnit(unsigned int i, float masterVol, float vol)
{
    if (vol < 0 || masterVol < 0 || vol > 1 || masterVol > 1) {
        return false;
    }

    //We use the difference from the latest state.
    float volDiff = masterVol*vol - masterVolume*units[i];
    if (volDiff != 0) {
        //The sound we play may be longer than one unit. For the last unit don't use soundLength but unitLength.
        unsigned int max = i < units.size()-1 ? soundLength : unitLength;
        unsigned int fj = unitLength*i;

        sox_sample_t* buf = sound.getBuffer();

        for (unsigned int j=0; j<max; j++) {
            buffer[fj++] += volDiff*buf[j];
        }
    }

    masterVolume = masterVol;
    units[i] = vol;

    return true;
}

bool BARSoxTrack::playUnit(unsigned int i)
{
    if (audioOutput != NULL) {
        unsigned int fj = unitLength*i;
        for (unsigned int j=fj; j < fj+unitLength; j+=MAX_SAMPLES) {
            sox_write(audioOutput, &buffer[j], MAX_SAMPLES);
        }
    } else {
        return false;
    }
    return true;
}

bool BARSoxTrack::play()
{
    unsigned int i=0;
    for (unsigned int i=0; playUnit(i) && i<units.size(); i++);

    return i==units.size();
}

BARSoxTrack::~BARSoxTrack()
{
    delete audioOutput;
}
