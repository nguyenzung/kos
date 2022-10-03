#ifndef AVL_TREE
#define AVL_TREE

#include <stdlib/pair.h>
#include <stdlib/math.h>
// #include <kernel/type.h>
#include <kernel/printer.h>

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

    // class Iterator
    // {

    // };

public:
    TreeNode *root;
    uint32 size;

    Map<K,V>():root(nullptr), size(0){}

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
            ++size;
            root = candidate;
            return root->pair;
        } else {
            return put(candidate, root);
        }
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

    void preorderTravel()
    {
        printf("\n Pre-Order Travel \n");
        preorderTravel(root);
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

    TreeNode* maintainAVLProperty(TreeNode *node) 
    {
        TreeNode *current = node;
        while (current)
        {
            bool isRoot = current == root;
            int score = current->getBalanceScore();
            if (score > 1) // Left Heavier
            {
                TreeNode *left = current->left;
                int score_ = left->getBalanceScore();
                if (score_ >= 0) // Left Left Case
                {
                    printf("\nRotate Right");
                    current = rightRotate(current);
                } else {    // Left Right Case
                    printf("\nRotate Left Right");
                    current = leftRightRotate(current);
                }
            } else if (score < -1) // Right heavier
            {
                TreeNode *right = current->right;
                int score_ = right->getBalanceScore();
                if (score_ <= 0) // Right Right Case
                {
                    current = leftRotate(current);
                    printf("\n Rotate Left %d ", current->value());
                } else {    // Right Left Case
                    printf("\n Rotate Right Left");
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
            if (node->right == nullptr)
            {
                ++size;
                node->addRight(candidate);
                updateHeightBottomUp(node);
                maintainAVLProperty(candidate);
                return candidate->pair;
            }else
            {
                return put(candidate, node->right);
            }

        case 1:
            if (node->left == nullptr)
            {
                ++size;
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

    Pair<K,V>* find(K key, TreeNode *node)
    {
        if (node)
        {
            switch (node->compareKey(key))
            {
            case 0:
                return node->pair;
            case -1:
                return find(key, node->right);
            case 1:
                return find(key, node->left);
            default:
                break;
            }
        }
        return nullptr;
    }



};

}

#endif