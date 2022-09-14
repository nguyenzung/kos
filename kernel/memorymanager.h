#ifndef MEMORY_MANAGER
#define MEMORY_MANAGER

#include "type.h"
#include "utils.h"

typedef struct MemoryEntry {
    MemoryEntry *next;
    MemoryEntry *back;
    uint16 size;
} MemoryEntry;

class MemoryManager {
    uint64 kernelHeapAddress;
    uint64 kernelStackBase;
    MemoryEntry *first;
    MemoryEntry *last;
    DEF_MODULE_INSTANCE(MemoryManager)
public:
    MemoryManager();
    ~MemoryManager();

    MemoryEntry* find(uint16 size);

    void* malloc(uint16 size);
    bool free(void *ptr);

    bool reserve(void* ptr, uint16 size);
};

#endif