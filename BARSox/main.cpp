#include <iostream>
#include "BARSoxSound.h"
#include "BARSoxPositionNode.h"
#include "BARSoxPatternSoundSystem.h"

#include <assert.h>

#define INPUT_ERROR     1
#define OUTPUT_ERROR    2

using namespace std;

int main()
{
    BARSoxPatternSoundSystem soundSys(120, 10, 2);

    assert(soundSys.addTrack("bjorken.wav") == 1);
    assert(soundSys.addTrack("sixten.wav") == 2);
    soundSys.preview(1);
    soundSys.preview(0);

    soundSys.changeVolume(0,0,100);
    soundSys.changeVolume(1,0,50);
    soundSys.changeVolume(1,7,90);

    soundSys.play();

    return 0;
}

