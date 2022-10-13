#ifndef HASH_TABLE
#define HASH_TABLE

#include <kernel/kernelobject.h>
#include <kernel/type.h>
#include <stdlib/list.h>
#include <stdlib/pair.h>
#include <stdlib/algorithm.h>
#include <kernel/printer.h>

#define NUM_SLOT_DEFAULT 5399    // We choose a prime number for the total slots

using namespace kernel;

namespace std
{

template <typename K, typename V>
class UnorderedMap
{
    uint16 numSlot;
    List<Pair<K, V>*> **lists;
    bool error;

public:
    UnorderedMap(uint16 numSlot = NUM_SLOT_DEFAULT):numSlot(numSlot)
    {
        printf("\n Total slots %d", numSlot);
        this->error = false;
        lists = new List<Pair<K, V>*>*[numSlot];
        if (!lists)
        {
            this->error = true;
            return;
        }
        for (int i = 0; i < numSlot; i++)
        {
            lists[i] = new List<Pair<K, V>*>();
            if (!lists[i])
            {
                this->error = true;
                return;
            }
        }
    }

    ~UnorderedMap()
    {
        for (int i = 0; i < this->numSlot; ++i)
        {   
            if (lists[i])
                delete lists[i];
        }
        if (lists)
            delete[] lists;
    }
    
    Pair<K, V>* put(K key, V object)
    {
        uint64 index = this->hash(key);
        List<Pair<K, V>*> *list = this->lists[index];
        typename List<Pair<K, V>*>::Iterator it = std::find(list->begin(), list->end(), [key](Pair<K, V>* pair){
            return key == pair->first;
        });
        if (it != list->end())
        {
            (*it)->second = object;
            return *it;
        } else 
        {
            Pair<K, V> *pair = new Pair<K, V>(key, object);
            if(pair)
                list->add(pair);
            return pair;
        }
    }

    Pair<K, V>* putNewKey(K key, V object)
    {
        uint64 index = this->hash(key);
        List<Pair<K, V>*> *list = this->lists[index];
        Pair<K, V> *pair = new Pair<K, V>(key, object);
        if (pair)
            list->add(pair);
        return pair;
    }

    bool contains(K key)
    {
        uint64 index = this->hash(key);
        // printf("\n Index %d", index);
        List<Pair<K, V>*> *list = this->lists[index];
        typename List<Pair<K, V>*>::Iterator it = std::find(list->begin(), list->end(), [key](Pair<K, V>* pair){
            return key == pair->first;
        });
        return it != list->end();
    }

    Pair<K, V>* get(K key)
    {
        uint64 index = this->hash(key);
        List<Pair<K, V>*> *list = this->lists[index];
        typename List<Pair<K, V>*>::Iterator it = std::find(list->begin(), list->end(), [key](Pair<K, V>* pair){
            return key == pair->first;
        });
        if (it != list->end())
        {
            return *it;
        } else {
            Pair<K, V>* pair = new Pair<K, V>(key, V());
            if(pair)
                list->add(pair);
            return pair;
        }
    }

    /*
    *   Developer need to make sure the map contains the key before removing
    */
    void erase(K key)
    {
        uint64 index = this->hash(key);
        List<Pair<K, V>*> *list = this->lists[index];
        typename List<Pair<K, V>*>::Iterator it = std::find(list->begin(), list->end(), [key](Pair<K, V>* pair){
            return key == pair->first;
        });
        if (it != list->end())
        {
            delete list->removeNodeByValue(*it);
            delete *it;
        }
    } 

    Pair<K,V>& operator[](K key)
    {
        // printf("[Map] %d %d", key);
        Pair<K, V>* pair = this->get(key);
        return *pair;
    }

protected:
    /*
    *   Using universal hashing
    */
    uint64 hash(K key)
    {
        uint64 p = 267419;   // Randomly choose a prime number
        uint64 a = 187639;    // a < p
        uint64 b = 203183;   // b < p
        uint64 index = ((a * (uint64) key + b) % p) % numSlot;
        return index;
    }
};

}

#endif