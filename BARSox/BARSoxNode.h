#ifndef BARSOXNODE_H
#define BARSOXNODE_H

#include <sox.h>

template<typename T>
/**
 * @brief The BARSoxNode class
 */
class BARSoxNode
{
    protected:
        float id;
        BARSoxNode *left, *right;

        T data;

        virtual void additionalOperations() {

        }

    public:
        BARSoxNode()
        {
            id = 0;
            data = T();
            left = NULL;
            right = NULL;
        }

        BARSoxNode(float id, T initialData, BARSoxNode* left=NULL, BARSoxNode* right=NULL)
        {
            BARSoxNode::id = id;
            BARSoxNode::left = left;
            BARSoxNode::right = right;
            BARSoxNode::data = initialData;

            if (left == NULL && right != NULL) {
                left = new BARSoxNode(right->getId(), right->get(), right->getLeft(), right->getRight());
            } else if (right == NULL && left != NULL) {
                right = new BARSoxNode(left->getId(), left->get(), left->getLeft(), left->getRight());
            }
        }

        bool divideLeaves()
        {
            if (left == NULL) {
                left = new BARSoxNode(2*id, data, NULL, NULL);
            } else {
                left->divideLeaves();
            }

            if (right == NULL) {
                right = new BARSoxNode(2*id+1, data, NULL, NULL);
            } else {
                right->divideLeaves();
            }

            id = (left->id + right->id)/2;
            additionalOperations();
            return true;
        }

        bool mergeLeaves()
        {
            if (left == NULL) {
                return false;
            }

            if (left->isLeaf()) {
                id = left->id/2;
                data = left->data;
                delete left,right;
            } else {
                left->mergeLeaves();
                right->mergeLeaves();
            }
        }

        BARSoxNode* getNode(float i)
        {
            float iLeft = i-1e-5, iRight = i+1e-5;
            if (id < iLeft) {
                return left->getNode(i);
            }

            if (id > iRight) {
                return right->getNode(i);
            }

            return this;
        }

        void setId(float id)
        {
            BARSoxNode::id = id;
        }

        void set(T data)
        {
            BARSoxNode::data = data;
        }

        T get()
        {
            return data;
        }

        float getId()
        {
            return id;
        }

        BARSoxNode* getLeft()
        {
            return left;
        }

        BARSoxNode* getRight()
        {
            return right;
        }

        bool isLeaf()
        {
            return left == NULL && right == NULL;
        }

        virtual ~BARSoxNode()
        {
            delete left;
            delete right;
        }
};

#endif // BARSOXNODE_H
