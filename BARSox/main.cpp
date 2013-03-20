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
    BARSoxPatternSoundSystem soundSys(120, 4, 2);

    assert(soundSys.addTrack("bar.wav") == 1);
    assert(soundSys.addTrack("sixten.wav") == 2);
    soundSys.preview(1);
    soundSys.preview(0);

    return 0;
}

