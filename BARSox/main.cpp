#include <iostream>
#include "BARSoxSound.h"
#include "BARSoxPositionNode.h"
#include "BARSoxPatternSoundSystem.h"

#include "BARSimpleResampler.h"

#include <assert.h>

using namespace std;

int main()
{
    vector<float> data(60);

    for (int i=0; i<data.size(); i++) {
        data[i] = i/2;
        cout << data[i] << " ";
    }
    cout << endl;

    BARSimpleResampler<float>::downsample(data, 44100, 22050, true);

    for (int i=0; i<data.size(); i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    return 0;

    BARSoxPatternSoundSystem soundSys(120, 10, 2);

    assert(soundSys.addTrack("drum.wav") == 1);
    assert(soundSys.addTrack("snare.wav") == 2);

    soundSys.preview(1);

    for (int i=0; i<10; i++) {
        soundSys.changeVolume(0,2*i,50);
        soundSys.changeVolume(1,2*i+1,100);
    }

    soundSys.play();

    return 0;
}

