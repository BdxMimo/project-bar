#ifndef BARSOXPOSITIONNODE_H
#define BARSOXPOSITIONNODE_H

#include "BARSoxNode.h"
#include "BARSoxBufferPos.h"

/**
 * @brief Node from a tree structure which stores the positions of the beats
 * in the sound buffer and their length in samples.
 * @author Hugo Duprat [<a href="mailto:hugo.duprat@gmail.com">Contact</a>]
 * @date 3/08/2013
 */
class BARSoxPositionNode : public BARSoxNode<BARSoxBufferPos>
{
    public:
        /**
         * @brief Default constructor.
         */
        BARSoxPositionNode() : BARSoxNode<BARSoxBufferPos>()
        {}

        /**
         * @brief Copy constructor with parent (in terms of inheritance).
         * @param node The node with the parent type.
         */
        BARSoxPositionNode(BARSoxNode<BARSoxBufferPos> node)
        {
            id = node.getId();
            data = node.get();
        }

        /**
         * @brief Constructor.
         * @param id ID of the node.
         * @param bufferPosObj BARSoxBufferPos object that gives a buffer position and a length.
         */
        BARSoxPositionNode(float id, BARSoxBufferPos bufferPosObj)
        {
            this->id = id;
            data = bufferPosObj;
        }

        /**
         * @brief Constructor.
         * @param id ID of the node.
         * @param bufferPos Position of the beat in the sound buffer.
         * @param bufferLen Length of the beat in the sound buffer.
         */
        BARSoxPositionNode(float id, sox_sample_t* bufferPos, sox_uint64_t bufferLen)
        {
            this->id = id;
            data = BARSoxBufferPos(bufferPos, bufferLen);
        }

        /**
         * @brief Splits the leaves of the tree given by the node
         * in two nodes with half length.
         *
         * The left node contains the same buffer position and half the length
         * of its parent, and the right node contains a position at half-length
         * from its parent's buffer position. The IDs are reevaluated.
         * @return @c true
         */
        virtual bool divideLeaves()
        {
            if (left == NULL) {
                left = new BARSoxPositionNode(2*id, data.pos, data.len/2);
            } else {
                left->divideLeaves();
            }

            if (right == NULL) {
                right = new BARSoxPositionNode(2*id+1, data.pos + data.len/2, data.len - data.len/2);
            } else {
                right->divideLeaves();
            }

            id = (left->getId() + right->getId())/2;
            return true;
        }

        /**
         * @brief Suppresses the leaves from the tree defined by the node.
         * @return @c false if no leaves, @c true otherwise.
         */
        virtual bool mergeLeaves() {
            if (left == NULL) {
                return false;
            }

            if (left->isLeaf()) {
                id = left->getId()/2;
                delete left;
                left = NULL;
                delete right;
                right = NULL;
            } else {
                left->mergeLeaves();
                right->mergeLeaves();

                id = (left->getId()+right->getId())/2;
            }

            return true;
        }

};

#endif // BARSOXPOSITIONNODE_H
