#ifndef AVL_TREE
#define AVL_TREE

#include <stdlib/pair.h>
#include <stdlib/math.h>
#include <kernel/printer.h>
#include <driver/serial.h>

namespace std
{

using namespace kernel;

/*
*   Using AVLTree data structure to implement map
*/
template <typename K, typename V>
class Map
{    
    class TreeNode
    {
    public:
        Pair<K,V> *pair;
        TreeNode *parent;
        TreeNode *left;
        TreeNode *right;
        int height;

        TreeNode(K key, V value)
        {
            pair = makePair(key, value);
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            height = 0;
        }

        ~TreeNode()
        {
            if (pair)
                delete pair;
        }

        void setValue(V value)
        {
            pair->second = value;
        }

        void addLeft(TreeNode *node)
        {
            this->left = node;
            if (node)
                node->parent = this;
        }

        void addRight(TreeNode *node)
        {
            this->right = node;
            if (node)
                node->parent = this;
        }

        void addParent(TreeNode *parent, TreeNode *old)
        {
            if (parent)
            {
                TreeNode *parentLeftChild = parent->left;
                TreeNode *parentRightChild = parent->right;
                if (parentLeftChild == old)
                {
                    parent->addLeft(this);
                } else {
                    parent->addRight(this);
                }
            } else {
                this->parent = nullptr;
            }
        }

        void childUnlink()
        {
            if (parent)
            {
                if (parent->left == this)
                {
                    parent->addLeft(nullptr);
                } else if (parent->right == this) {
                    parent->addRight(nullptr);
                }
            }
            parent = nullptr;
        }

        int updateHeight()
        {
            int leftHeight = getLeftHeight();
            int rightHeight = getRightHeight();
            // printf("\n %d %d ", leftHeight, rightHeight);
            height = std::max(leftHeight, rightHeight) + 1;
        }

        int getBalanceScore()
        {
            return getLeftHeight() - getRightHeight();
        }

        int getRightHeight() 
        {
            return right ? right->height : -1;
        }

        int getLeftHeight()
        {
            return left ? left->height : -1;
        }

        int compareKey(K key)
        {
            if (pair->first == key)
                return 0;
            if (pair->first > key)
                return 1;
            return -1;
        }

        int compareKey(TreeNode *node)
        {
            return compareKey(node->pair->first);
        }

        K key()
        {
            return pair->first;
        }

        V value()
        {
            return pair->second;
        }
    };

public:
    class Iterator
    {
    protected:
        TreeNode* ptr;

    public:
        Iterator(TreeNode* ptr)
        {
            this->ptr = ptr;
        }

        Iterator& operator = (TreeNode* ptr)
        {
            this->ptr = ptr;
            return *this;
        }

        Iterator& operator++()
        {
            if (ptr)
            {
                ptr = ptr->next;
            }
            return *this;
        }
 
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
 
        bool operator!=(const Iterator& iterator)
        {
            return ptr != iterator.ptr;
        }
        
        bool operator==(const Iterator& iterator)
        {
            return ptr == iterator.ptr;
        }
 
        Pair<K,V>* operator*()
        {
            return ptr->pair;
        }
    };

public:
    TreeNode *root;
    uint32 size_;

    Map<K,V>():root(nullptr), size_(0){}

    ~Map<K,V>(){
        if (root)
            delete root;
    }

    Pair<K, V>* put(K key, V value)
    {
        TreeNode *candidate = new TreeNode(key, value);
        if (!candidate)
        {
            return nullptr;
        }
        if (!root)
        {
            ++size_;
            root = candidate;
            return root->pair;
        } else {
            return put(candidate, root);
        }
    }

    bool earse(K key)
    {
        TreeNode *node = findNode(key, root);
        if (node)
        {
            TreeNode *swapNode = findSwapNode(node);
            TreeNode *anchorNode;
            if (swapNode)
            {
                *node->pair = *swapNode->pair;
                if (swapNode->left)
                {
                    anchorNode = swapNode->left;
                    anchorNode->addParent(swapNode->parent, swapNode);
                }else{
                    anchorNode = swapNode->parent;
                }
                
                swapNode->childUnlink();
                --size_;
                delete swapNode;
            } else {
                anchorNode = node->parent;
                node->childUnlink();
                if (node == root)
                {
                    root = nullptr;
                }
                --size_;
                delete node;
            }
            if(anchorNode)
            {
                updateHeightBottomUp(anchorNode);
                maintainAVLProperty(anchorNode);
            }
            return true;
        }
        return false;
    }

    void updateHeightBottomUp(TreeNode *node)
    {
        if (node)
        {
            node->updateHeight();
            if (node->parent)
                updateHeightBottomUp(node->parent);
        }
    }

    void leftRotate()
    {
        root = leftRotate(root);
    }

    void leftRightRotate()
    {
        root = leftRightRotate(root);
    }

    void rightRotate()
    {
        root = rightRotate(root);
    }

    void rightLeftRotate()
    {
        root = rightLeftRotate(root);
    }

    Pair<K,V>* find(K key)
    {
        return find(key, root);
    }

    void inorderTravel()
    {
        printf("\n In-Order Travel \n");
        inorderTravel(root);
    }
    
    template<typename Processor>
    void revertInorderProcess(Processor processor)
    {
        revertInorderProcess(root, processor);
    }
    
    template<typename Processor>
    void inorderProcess(Processor processor)
    {
        inorderProcess(root, processor);
    }

    void preorderTravel()
    {
        printf("\n Pre-Order Travel \n");
        preorderTravel(root);
    }

    uint32 size()
    {
        return size_;
    }

    V min()
    {        
        TreeNode *current = root;
        V result = current->value();
        while (current->left)
        {
            current = current->left;
            if (result > current->value())
                result = current->value();
        }
        return result;
    }

    V max()
    {
        TreeNode *current = root;
        V result = current->value();
        while (current->right)
        {
            current = current->right;
            if (result < current->value())
                result = current->value();
        }
        return result;
    }

protected:
    void inorderTravel(TreeNode *node)
    {
        if (!node)
        {
            return;
        }
        if (node->left)
        {
            inorderTravel(node->left);
        }
        printf("[%d:%d] ", node->key(), node->value());
        if (node->right)
        {
            inorderTravel(node->right);
        }
    }
    
    template <typename Processor>
    void revertInorderProcess(TreeNode *node, Processor processor)
    {
        if (!node)
        {
            return;
        }
        if (node->right)
        {
            revertInorderProcess(node->right, processor);
        }
        processor(node->value());        
        if (node->left)
        {
            revertInorderProcess(node->left, processor);
        }
    }
    
    template <typename Processor>
    void inorderProcess(TreeNode *node, Processor processor)
    {
        if (!node)
        {
            return;
        }
        if (node->left)
        {
            inorderProcess(node->left, processor);
        }
        processor(node->value());        
        if (node->right)
        {
            inorderProcess(node->right, processor);
        }
    }

    void preorderTravel(TreeNode *node)
    {
        if (!node)
        {
            return;
        }
        printf("[%d:%d] ", node->key(), node->height);
        if (node->left)
        {
            preorderTravel(node->left);
        }
        if (node->right)
        {
            preorderTravel(node->right);
        }
    }

    Pair<K, V>* upperBound(V value)
    {
        return nullptr;
    }

    Pair<K, V>* lowerBound(V value)
    {
        return nullptr;
    }

    TreeNode* findSwapNode(TreeNode *node)
    {
        if (node)
        {
            if (node->left)
            {
                // printf(" \n Swap find in left");
                return findMaxSuccessor(node->left);
            } else if (node->right)
            {
                 // printf(" \n Swap find in right");
                 return findMinSuccessor(node->right);
            }
        }
        return nullptr;
    }

    TreeNode* findMinSuccessor(TreeNode *node)
    {
        TreeNode *current = node;
        while (current && current->left)
        {
            current = current->left;
        }
        return current;
    }

    TreeNode* findMaxSuccessor(TreeNode *node)
    {
        TreeNode *current = node;
        while (current && current->right)
        {
            current = current->right;
        }
        return current;
    }

    TreeNode* maintainAVLProperty(TreeNode *node) 
    {
        TreeNode *current = node;
        while (current)
        {
            bool isRoot = (current == root);
            int score = current->getBalanceScore();
            if (score > 1) // Left Heavier
            {
                TreeNode *left = current->left;
                int score_ = left->getBalanceScore();
                if (score_ >= 0) // Left Left Case
                {
                    current = rightRotate(current);
                } else {    // Left Right Case
                    current = leftRightRotate(current);
                }
            } else if (score < -1) // Right heavier
            {
                TreeNode *right = current->right;
                int score_ = right->getBalanceScore();
                if (score_ <= 0) // Right Right Case
                {
                    current = leftRotate(current);
                } else {    // Right Left Case
                    current = rightLeftRotate(current);
                }
            }
            if (isRoot)
            {
                root = current;
            }
            current = current->parent;
        }
    }

    TreeNode* leftRotate(TreeNode *node)
    {
        if (node && node->right)
        {
            TreeNode *parent = node->parent;
            TreeNode *rightNode = node->right;
            TreeNode *rightLeft = rightNode->left;
            node->addRight(rightLeft);
            rightNode->addLeft(node);
            rightNode->addParent(parent, node);
            
            node->updateHeight();
            updateHeightBottomUp(rightNode);
            return rightNode;
        }
        return node;
    }

    TreeNode* leftRightRotate(TreeNode *node)
    {
        if (node && node->left)
        {
            TreeNode *parent = node->parent;
            TreeNode *left = node->left;
            TreeNode *leftRight = left->right;
            left->addRight(leftRight->left);
            node->addLeft(leftRight->right);
            leftRight->addLeft(left);
            leftRight->addRight(node);
            leftRight->addParent(parent, node);
            left->updateHeight();
            node->updateHeight();
            updateHeightBottomUp(leftRight);
            return leftRight;
        }
        return node;
    }

    TreeNode* rightRotate(TreeNode *node)
    {
        if (node && node->left)
        {
            TreeNode *parent = node->parent;
            TreeNode *leftNode = node->left;
            TreeNode *leftRight = leftNode->right;
            leftNode->addRight(node);
            node->addLeft(leftRight);
            leftNode->addParent(parent, node);
            node->updateHeight();
            updateHeightBottomUp(leftNode);
            return leftNode;
        }
        return node;
    }

    TreeNode* rightLeftRotate(TreeNode *node)
    {
        if (node && node->right)
        {
            TreeNode *parent = node->parent;
            TreeNode *right = node->right;
            TreeNode *rightLeft = right->left;
            right->addLeft(rightLeft->right);
            node->addRight(rightLeft->left);
            rightLeft->addLeft(node);
            rightLeft->addRight(right);
            rightLeft->addParent(parent, node);
            right->updateHeight();
            node->updateHeight();
            updateHeightBottomUp(rightLeft);
            return rightLeft;
        }
        return node;
    }

    Pair<K, V>* put(TreeNode *candidate, TreeNode *node)
    {
        int result = node->compareKey(candidate);
        switch (result)
        {
        case 0:
            node->setValue(candidate->pair->second);
            delete candidate;
            return node->pair;

        case -1:
            if (!node->right)
            {
                ++size_;
                node->addRight(candidate);
                updateHeightBottomUp(node);
                maintainAVLProperty(candidate);
                return candidate->pair;
            }else
            {
                return put(candidate, node->right);
            }

        case 1:
            if (!node->left)
            {
                ++size_;
                node->addLeft(candidate);
                updateHeightBottomUp(node);
                maintainAVLProperty(candidate);
                return candidate->pair;
            }else
            {
                return put(candidate, node->left);
            }

        default:
            break;
        }
        return 0;
    }

    TreeNode* findNode(K key, TreeNode *node)
    {
        if (node)
        {
            switch (node->compareKey(key))
            {
            case 0:
                return node;
            case -1:
                return node->right ? findNode(key, node->right) : nullptr;
            case 1:
                return node->left ? findNode(key, node->left) : nullptr;
            default:
                break;
            }
        }
        return nullptr;
    }

    Pair<K,V>* find(K key, TreeNode *node)
    {
        TreeNode *result = findNode(key, node);
        return result ? result->pair : nullptr;
    }

public:
    Iterator begin()
    {
        TreeNode *current = root;
        while (current && current->left ) {
            current = current->left;
        }
        return Iterator(current);
    }
 
    Iterator end()
    {
        return Iterator(0);
    }
};

}

#endif