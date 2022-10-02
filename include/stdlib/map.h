#ifndef AVL_TREE
#define AVL_TREE

#include <stdlib/pair.h>
#include <kernel/type.h>
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
        kernel::uint64 height;

        TreeNode(K key, V value)
        {
            pair = makePair(key, value);
            parent = nullptr;
            left = 0;
            right = 0;
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

    Map<K,V>():root(nullptr){}

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
            root = candidate;
            return root->pair;
        } else {
            return put(candidate, root);
        }
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
        printf(" [%d: %d] ", node->key(), node->value());
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
        printf(" [%d: %d] ", node->key(), node->value());
        if (node->left)
        {
            preorderTravel(node->left);
        }
        if (node->right)
        {
            preorderTravel(node->right);
        }
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
                node->right = candidate;
                return candidate->pair;
            }else
            {
                return put(candidate, node->right);
            }

        case 1:
            if (node->left == nullptr)
            {
                node->left = candidate;
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