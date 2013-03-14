#include "BARSoxBufferPos.h"

/**
 * @brief Default constructor.
 */
BARSoxBufferPos::BARSoxBufferPos()
{
    pos=0;
    len=0;
}

/**
 * @brief Constructor.
 * @param position The position of the beat in the sound buffer.
 * @param length Length of the beat in samples.
 */
BARSoxBufferPos::BARSoxBufferPos(sox_sample_t *position, sox_uint64_t length)
{
    pos = position;
    len = length;
}
