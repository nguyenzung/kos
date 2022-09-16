#ifndef MEMORY_MANAGER
#define MEMORY_MANAGER

#include "type.h"
#include "utils.h"

#define MEMORY_ENTRY_SIZE 10
typedef struct MemoryEntry {
    MemoryEntry *next;
    uint16 size;
} __attribute__((packed)) MemoryEntry;

class MemoryManager {
    void* kernelHeapBase;
    void* kernelStackBase;
    MemoryEntry *first;
    DEF_MODULE_INSTANCE(MemoryManager)
public:
    MemoryManager();
    ~MemoryManager();

    void* malloc(uint16 size);
    void* free(void *ptr);
    void* reserve(void* ptr, uint16 size);  // reserve for drivers, modules

protected:
    MemoryEntry* find(uint16 size);    // return the address of the entry such that will point to the creating entry
    void* makeFirstMemoryEntry(uint16 size);
    void* makeMemoryEntry(void* ptrPrev, uint16 size);
    void* makeMemoryEntryAt(void* ptr, void* ptrPrev, uint16 size);
};

void* memreg(void* ptr, uint16 size);
void memunreg(void *ptr);

void* malloc(size_t);
void free(void* ptr);

void* operator new(size_t size);
void operator delete(void* ptr);

void* operator new[](size_t size);
void operator delete[](void* ptr);

#endif