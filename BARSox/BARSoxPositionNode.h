#ifndef BARSOXPOSITIONNODE_H
#define BARSOXPOSITIONNODE_H

#include "BARSoxNode.h"
#include "BARSoxBufferPos.h"

class BARSoxPositionNode : public BARSoxNode<BARSoxBufferPos>
{
    protected:
        virtual void additionalOperations()
        {
            left->set(BARSoxBufferPos(data.pos, data.len/2));
            right->set(BARSoxBufferPos(data.pos+data.len/2, data.len-data.len/2));
        }

    public:
        BARSoxPositionNode()
        {}

        BARSoxPositionNode(BARSoxNode<BARSoxBufferPos> node)
        {
            id = node.getId();
            data = node.get();
        }

        BARSoxPositionNode(BARSoxBufferPos bufferPosObj)
        {
            id = 0;
            data = bufferPosObj;
        }

        BARSoxPositionNode(sox_sample_t* bufferPos, sox_uint64_t bufferLen)
        {
            id = 0;
            data = BARSoxBufferPos(bufferPos, bufferLen);
        }

};

#endif // BARSOXPOSITIONNODE_H
