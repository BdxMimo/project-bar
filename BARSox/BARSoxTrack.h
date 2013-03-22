#ifndef BARSOXTRACK_H
#define BARSOXTRACK_H

#include "BARSoxPositionNode.h"
#include "BARSoxNode.h"
#include <sox.h>
#include <vector>

#include "BARDefines.h"

/**
 * @brief The BARSoxTrack class handles data for one track.
 * A track contains only one kind of sound, repeated along beats.
 * @author Hugo Duprat [<a href="mailto:hugo.duprat@gmail.com">Contact</a>]
 * @date 3/08/2013
 *
 * @todo See if it would be useful to create an instance counter.
 */
class BARSoxTrack
{
    protected:
        unsigned int masterVolume; /**< Master volume for the track. */
        unsigned int nBeats; /**< Number of beats of the pattern.*/
        unsigned int notesPerBeat; /**< Amount of notes per beat (1,2,4 or 8).*/

        std::vector<sox_sample_t> trackSoundBuffer; /**< Sound buffer for the track sound. */
        std::vector< BARSoxNode<unsigned int>* > volumeTrees; /**< Volume trees per beat for the track. */

        bool mute; /**< @c true if mute track, @c false otherwise. */
        sox_signalinfo_t properties;

    public:
        BARSoxTrack();
        BARSoxTrack(const char* filename,unsigned int nBeats = 4, unsigned int notesPerBeat = 2, unsigned int masterVolume = 100);

        void updateVolumeTrees(unsigned int npbBegin, unsigned int npbEnd);
        void nBeatsChanged(unsigned int newVal);
        void notesPerBeatChanged(unsigned int newVal);

        const std::vector<sox_sample_t>& getTrackSoundBuffer();
        unsigned int getVolumeAt(unsigned int i);
        void setVolumeAt(unsigned int i, unsigned int vol);

        unsigned int getMasterVolume();
        void setMasterVolume(unsigned int mv);

        bool isMute();
        void setMute(bool mute);

        sox_signalinfo_t getProperties();

        ~BARSoxTrack();
};

#endif // BARSOXTRACK_H
