#ifndef MEMORY_MANAGER
#define MEMORY_MANAGER

#include "type.h"

typedef struct MemoryEntry {
    MemoryEntry *next;
    MemoryEntry *back;
    uint16 size;
} MemoryEntry;

class MemoryManager {
    static MemoryManager *instance;
    uint64 heapAddress;
    MemoryEntry *first;
    MemoryEntry *last;

    MemoryManager();
    ~MemoryManager();

    MemoryEntry* find();

    void* malloc(uint16 size);
    bool free(void *ptr);
    
};

#endif