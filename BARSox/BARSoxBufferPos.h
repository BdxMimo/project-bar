#ifndef BARSOXBUFFERPOS_H
#define BARSOXBUFFERPOS_H

#include <sox.h>

class BARSoxBufferPos
{
public:
    sox_sample_t* pos;
    sox_uint64_t len;

    BARSoxBufferPos();
    BARSoxBufferPos(sox_sample_t*, sox_uint64_t);


};

#endif // BARSOXBUFFERPOS_H
