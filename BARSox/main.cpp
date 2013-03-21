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

    for (int i=0; i<7; i++) {
        soundSys.changeVolume(0,6*i,100);
        soundSys.changeVolume(0,8*i+2,100);
        soundSys.changeVolume(1,9*i+3,100);
    }

    soundSys.play();

    return 0;
}

