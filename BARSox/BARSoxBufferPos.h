#ifndef BARSOXBUFFERPOS_H
#define BARSOXBUFFERPOS_H

#include <sox.h>

/**
 * @brief A class to determine the position and length of a beat in a sound buffer.
 */
class BARSoxBufferPos
{
    public:
        sox_sample_t* pos;  /**< Position in the sound buffer. */
        sox_uint64_t len;   /**< Length of a beat. */

        BARSoxBufferPos();
        BARSoxBufferPos(sox_sample_t*, sox_uint64_t);
};

#endif // BARSOXBUFFERPOS_H
