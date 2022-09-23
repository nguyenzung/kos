#ifndef HASH_TABLE
#define HASH_TABLE

#include <kernel/kernelobject.h>
#include <kernel/type.h>
#include <stdlib/list.h>

#define HASH_TABLE_NUM_SLOT_DEFAULT 2000

using namespace kernel;


namespace std
{

template <typename K, typename V>
class HashTable
{
    List<V> **lists;
public:

    HashTable(uint16 numSlot)
    {
        if(numSlot > HASH_TABLE_NUM_SLOT_DEFAULT)
        {
            numSlot = HASH_TABLE_NUM_SLOT_DEFAULT;
        }
        lists = new List<V>*[numSlot];
        for (int i = 0; i < numSlot; i++)
        {
            lists[i] = new List<V>();
        }
    }
    ~HashTable();

    uint16 getIndex(K key)
    {
        return 0;
    }

    uint16 save(K key, V object)
    {
        uint16 index = this->getIndex(object);
        // this->lists[index];
        return index;
    }

    V getObject(K key)
    {
        return 0;
    }    
};

}

#endif