#ifndef HASH_TABLE
#define HASH_TABLE

#include <kernel/kernelobject.h>
#include <kernel/type.h>
#include <stdlib/list.h>
#include <stdlib/algorithm.h>
#include <kernel/printer.h>

#define HASH_TABLE_NUM_SLOT_DEFAULT 5399    // We choose a prime number for the total slots

using namespace kernel;

namespace std
{

template <typename K, typename V>
class Pair 
{
    K key_;

public:
    const K &key;
    V value;

    Pair(K key, V value):key(key_)
    {
        this->key_ = key;
        this->value = value;
    }
    
    Pair& operator = (V value)
        {
            this->value = value;
            return *this;
        }
};

template <typename K, typename V>
class UnorderedMap
{
    uint16 numSlot;
    List<Pair<K, V>*> **lists;

public:
    UnorderedMap()
    {
        this->numSlot = HASH_TABLE_NUM_SLOT_DEFAULT;
        lists = new List<Pair<K, V>*>*[numSlot];
        for (int i = 0; i < numSlot; i++)
        {
            lists[i] = new List<Pair<K, V>*>();
        }
    }

    ~UnorderedMap()
    {
        for (int i = 0; i < this->numSlot; ++i)
        {
            delete lists[i];
        }
        delete[] lists;
    }

    
    uint64 put(K key, V object)
    {
        uint64 index = this->getIndex(key);
        List<Pair<K, V>*> *list = this->lists[index];
        typename List<Pair<K, V>*>::Iterator it = std::find(list->begin(), list->end(), [key](Pair<K, V>* pair){
            return key == pair->key;
        });
        if (it != list->end())
        {
            (*it)->value = object;
        } else
        {
            Pair<K, V> *pair = new Pair<K, V>(key, object);
            list->add(pair);
        }
        return index;
    }

    bool contains(K key)
    {
        uint64 index = this->getIndex(key);
        List<Pair<K, V>*> *list = this->lists[index];
        typename List<Pair<K, V>*>::Iterator it = std::find(list->begin(), list->end(), [key](Pair<K, V>* pair){
            return key == pair->key;
        });
        return it != list->end();
    }

    Pair<K, V>* get(K key)
    {
        uint64 index = this->getIndex(key);
        List<Pair<K, V>*> *list = this->lists[index];
        typename List<Pair<K, V>*>::Iterator it = std::find(list->begin(), list->end(), [key](Pair<K, V>* pair){
            return key == pair->key;
        });
        if (it != list->end())
        {
            return *it;
        } else {
            Pair<K, V>* pair = new Pair<K, V>(key, V());
            list->add(pair);
            return pair;
        }
    }

    /*
    *   Developer need to make sure the map contains the key before removing
    */
    void remove(K key)
    {
        uint64 index = this->getIndex(key);
        List<Pair<K, V>*> *list = this->lists[index];
        typename List<Pair<K, V>*>::Iterator it = std::find(list->begin(), list->end(), [key](Pair<K, V>* pair){
            return key == pair->key;
        });
        if (it != list->end())
        {
            delete list->removeNodeByValue(*it);
            delete *it;
        }
    } 

    Pair<K,V>& operator[](K key)
    {
        printf("[Map] %d % d", key);
        Pair<K, V>* pair = this->get(key);
        return *pair;
    }

protected:
    uint64 getIndex(K key)
    {
        uint64 index = (uint64) key % HASH_TABLE_NUM_SLOT_DEFAULT;
        return index;
    }
};

}

#endif