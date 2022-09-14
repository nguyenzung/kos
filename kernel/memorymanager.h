#ifndef MEMORY_MANAGER
#define MEMORY_MANAGER

#include "type.h"
#include "utils.h"

#define MEMORY_ENTRY_SIZE 10
typedef struct MemoryEntry {
    MemoryEntry *next;
    uint16 size;
}__attribute__((packed))  MemoryEntry;

class MemoryManager {
    void* kernelHeapAddress;
    void* kernelStackBase;
    MemoryEntry *first;
    DEF_MODULE_INSTANCE(MemoryManager)
public:
    MemoryManager();
    ~MemoryManager();

    
    MemoryEntry* find(uint16 size);    // return the address of the entry such that will point to the creating entry

    void* malloc(uint16 size);
    void* free(void *ptr);

    void* reserve(void* ptr, uint16 size);  // reserve for drivers, modules

// protected:
    void* makeFirstMemoryEntry(uint16 size);
    void* makeMemoryEntry(void* prevAddress, uint16 size);
};

#endif