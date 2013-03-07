#include <iostream>
#include "BARSoxSound.h"

#define INPUT_ERROR     1
#define OUTPUT_ERROR    2

using namespace std;

int main()
{
    BARSoxSound half1("sixten.wav"), half2("bjorken.wav");
    half1.play();
    half2.play();
    for (int k=1; k<101; k++)
        cout << k << endl;

    return 0;
}

