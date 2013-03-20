#ifndef BARSOXNODE_H
#define BARSOXNODE_H

#include <sox.h>
#include <assert.h>

template<typename T>
/**
 * @brief Node from a tree structure which can store various data.
 */
class BARSoxNode
{
    protected:
        float id;   /**< ID of the node. */
        BARSoxNode *left; /**< Left child of the node. */
        BARSoxNode *right; /**< Right child of the node. */

        T data; /**< Data of the type assigned to the node. */

    public:
        /**
         * @brief Default constructor.
         */
        BARSoxNode()
        {
            id = 0;
            data = T();
            left = NULL;
            right = NULL;
        }

        /**
         * @brief Constructor.
         * @param id ID of the node.
         * @param initialData Data assigned to the node.
         * @param left Left child of the node (@c NULL for no node)
         * @param right Right child of the node (@c NULL for no node)
         */
        BARSoxNode(float id, T initialData, BARSoxNode* left=NULL, BARSoxNode* right=NULL)
        {
            this->id = id;
            this->left = left;
            this->right = right;
            this->data = initialData;

            if (left == NULL && right != NULL) {
                left = new BARSoxNode(right->getId(), right->get(), right->getLeft(), right->getRight());
            } else if (right == NULL && left != NULL) {
                right = new BARSoxNode(left->getId(), left->get(), left->getLeft(), left->getRight());
            }
        }

        /**
         * @brief Splits the leaves of the tree given by the node in two.
         * @return @c true
         */
        virtual bool divideLeaves()
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
            return true;
        }

        /**
         * @brief Suppresses the leaves from the tree defined by the node.
         * @return @c false if no leaves, @c true otherwise.
         */
        virtual bool mergeLeaves()
        {
            if (left == NULL) {
                return false;
            }

            if (left->isLeaf()) {
                id = left->id/2;
                data = left->data;

                delete left;
                left = NULL;

                delete right;
                right = NULL;
            } else {
                left->mergeLeaves();
                right->mergeLeaves();

                id = (left->id+right->id)/2;
            }

            return true;
        }

        /**
         * @brief Gets the node of a precise ID.
         * @param i The ID of the node to get.
         * @return The node with the corresponding ID.
         */
        BARSoxNode* getNode(float i)
        {
            if (isLeaf()) {
                return this;
            }

            float iLeft = i-1e-5, iRight = i+1e-5;
            if (id < iLeft) {
                return left->getNode(i);
            }

            if (id > iRight) {
                return right->getNode(i);
            }

            return this;
        }

        /**
         * @brief Sets the ID of the node with the corresponding value.
         * @param id The ID to set.
         */
        void setId(float id)
        {
            BARSoxNode::id = id;
        }

        /**
         * @brief Sets the data of the node.
         * @param data The data to assign to the node.
         */
        void set(T data)
        {
            BARSoxNode::data = data;
        }

        /**
         * @brief Sets data to a specific node.
         * @param id The ID of the node to modify.
         * @param data The data to set.
         */
        void setAt(float id, T data)
        {
            getNode(id)->set(data);
        }

        /**
         * @brief Gets the data from the node.
         * @return The data assigned to the node.
         */
        T get()
        {
            return data;
        }

        /**
         * @brief Gets the ID of the node.
         * @return The ID of the node.
         */
        float getId()
        {
            return id;
        }

        /**
         * @brief Gets the data from a specific node.
         * @param id The ID of the node to modify.
         * @return The data of the node.
         */
        T getAt(float id)
        {
            return getNode(id)->get();
        }

        /**
         * @brief Gets the left child of the node.
         * @return The left child of the node.
         */
        BARSoxNode* getLeft()
        {
            return left;
        }

        /**
         * @brief Gets the right child of the node.
         * @return The right child of the node.
         */
        BARSoxNode* getRight()
        {
            return right;
        }

        /**
         * @brief Determines if the node is actually a leaf.
         * @return @c true if the node is a leaf, @c false otherwise.
         */
        bool isLeaf()
        {
            return left == NULL && right == NULL;
        }

        /**
         * @brief Destructor.
         */
        virtual ~BARSoxNode()
        {
            if (!isLeaf()) {
                delete left;
                left = NULL;
                delete right;
                right = NULL;
            }
            assert(left==NULL);
            assert(right==NULL);
        }
};

#endif // BARSOXNODE_H
