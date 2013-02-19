#include "BARSoxSound.h"

/**
 * @brief Instance counter.
 */
int BARSoxSound::instances = 0;

/**
 * @brief Default constructor.
 *
 * Creates an empty BARSoxSound object.
 */
BARSoxSound::BARSoxSound()
{
    init();
    sound = NULL;
    duration = 0;
    audioOutput = NULL;
    sharedSound = true;
    memorizeBuffer = false;
    ++instances;
}

/**
 * @brief Constructor with file name.
 *
 * Creates a BARSoxSound object for an unshared sound.
 * @param[in] filename Path to the sound file.
 */
BARSoxSound::BARSoxSound(const char* filename)
{
    if (init()) {
        sound = sox_open_read(filename, NULL, NULL, NULL);
        if (sound != NULL) {
            duration = sound->signal.length/(sound->signal.rate*sound->signal.channels);
            audioOutput = sox_open_write("default", &sound->signal, NULL, AUDIO_DRIVER, NULL, NULL);
            sharedSound = false;
        } else {
            duration = 0;
            audioOutput = NULL;
            sharedSound = true;
        }
    } else {
        sound = NULL;
        duration = 0;
        audioOutput = NULL;
        sharedSound = true;
    }
    memorizeBuffer = false;
    ++instances;
}

/**
 * @brief Constructor with sox_format_t.
 *
 * Creates a BARSoxSound object for a shared sound (i.e. the sound already exists out of the instance).
 * @param[in] sound Reference pointer to the sound file.
 */
BARSoxSound::BARSoxSound(sox_format_t *sound)
{
    if (init() && sound != NULL) {
        BARSoxSound::sound = sound;
        duration = sound->signal.length/(sound->signal.rate*sound->signal.channels);
        audioOutput = sox_open_write("default", &sound->signal, NULL, AUDIO_DRIVER, NULL, NULL);
    } else {
        sound = NULL;
        duration = 0;
        audioOutput = NULL;
    }
    sharedSound = true;
    memorizeBuffer = false;
    ++instances;
}

/**
 * @brief Accessor to the duration of the sound.
 * @return The duration of the sound, in seconds.
 */
double BARSoxSound::getDuration()
{
    return duration;
}

/**
 * @brief Accessor to the original path of the sound.
 * @return A relative path to the sound, returns "NULL" if the sound doesn't exist.
 */
const char* BARSoxSound::getFilename()
{
    return sound != NULL ? sound->filename : "NULL";
}

/**
 * @brief Safe method to load a sound from a file name.
 *
 * It unloads any sound that has already been loaded before loading the new sound.
 * @param[in] filename Path to the sound file.
 * @return @c true if the sound has been effectively loaded, @c false otherwise.
 */
bool BARSoxSound::load(char *filename)
{
    //unload the previous sound
    unload();

    //load the new sound
    sound = sox_open_read(filename, NULL, NULL, NULL);
    if (sound != NULL) {
        duration = sound->signal.length/(sound->signal.rate*sound->signal.channels);
        audioOutput = sox_open_write("default", &sound->signal, NULL, AUDIO_DRIVER, NULL, NULL);
        sharedSound = false;
        return true;
    }
    return false;
}

/**
 * @brief Safe method to load a sound from a shared sound.
 *
 * It unloads any sound that has already been loaded before loading the new sound.
 * @param[in] sound Reference pointer to the sound file.
 * @return @c true if the sound has been effectively loaded, @c false otherwise.
 */
bool BARSoxSound::load(sox_format_t *sound)
{
    if (sound == NULL) {
        return false;
    }

    //unload the previous sound
    unload();

    //load the new sound
    BARSoxSound::sound = sound;
    duration = sound->signal.length/(sound->signal.rate*sound->signal.channels);
    audioOutput = sox_open_write("default", &sound->signal, NULL, AUDIO_DRIVER, NULL, NULL);
    sharedSound = true;
    return true;
}

/**
 * @brief Plays the sound.
 * @return @c true if the sound has been effectively played, @c false otherwise.
 */
bool BARSoxSound::play()
{
    if (!memorizeBuffer) {
        buffer = new sox_sample_t[sound->signal.length];
        sox_read(sound, buffer, sound->signal.length);
        memorizeBuffer = true;
    }

    size_t readBytes = sox_write(audioOutput, buffer, sound->signal.length);

    return readBytes > 0;
}

/**
 * @brief [private] Unloads a sound (and deletes it if unshared).
 */
void BARSoxSound::unload()
{
    if (sound != NULL) {
        if (sharedSound) {
            sound = NULL;
        } else {
            sox_close(sound);
            delete sound;
        }
    }

    duration = 0;

    if (audioOutput != NULL) {
        sox_close(audioOutput);
    }

    sharedSound = true;
    memorizeBuffer = false;
}

/**
 * @brief [private] Initializes the SoX session for the first instance, does not do anything otherwise.
 * @return true if the SoX session has been initialized.
 */
bool BARSoxSound::init()
{
    return instances == 0 ? (sox_init() == SOX_SUCCESS) : true;
}

/**
 * @brief [private] Quits the SoX session if the last instance is destroyed, does not do anything otherwise.
 */
void BARSoxSound::quit()
{
    if (instances == 0) {
        sox_quit();
    }
}

/**
 * @brief Destructor.
 */
BARSoxSound::~BARSoxSound()
{
    unload();
    --instances;
    quit();
}

