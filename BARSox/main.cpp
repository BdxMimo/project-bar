#include <iostream>
#include "BARSoxSound.h"

#define INPUT_ERROR     1
#define OUTPUT_ERROR    2

using namespace std;

int main()
{
    BARSoxSound sound("wav.wav");
    BARSoxSound unk("unknown.wav");

    cout << sound.getFilename() << endl << "Duration: " << sound.getDuration() << endl;
    sound.play();
    return 0;
}

