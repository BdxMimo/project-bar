#include "BARSoxBufferPos.h"

BARSoxBufferPos::BARSoxBufferPos()
{
    pos=0;
    len=0;
}

BARSoxBufferPos::BARSoxBufferPos(sox_sample_t *position, sox_uint64_t length)
{
    pos = position;
    len = length;
}
