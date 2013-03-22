#include <iostream>
#include "BARSoxSound.h"
#include "BARSoxPositionNode.h"
#include "BARSoxPatternSoundSystem.h"

#include "BARSimpleResampler.h"

#include <assert.h>

using namespace std;

int main()
{
    BARSoxPatternSoundSystem soundSys(120, 4, 4);

    assert(soundSys.addTrack("drum.wav") == 1);
    assert(soundSys.addTrack("snare.wav") == 2);

    for (int i=0; i<2; i++) {
        soundSys.changeVolume(0,4*i,100);
        soundSys.changeVolume(1,4*i+2,100);
    }
    soundSys.changeVolume(0,5,100);

    for (int i=0; i<2; i++) {
        soundSys.changeVolume(0,3*i+8,100);
        soundSys.changeVolume(1,4*i+10,100);
    }
    soundSys.changeVolume(0,13,100);

    soundSys.play();

    return 0;
}

