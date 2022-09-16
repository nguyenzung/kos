#ifndef MEMORY_MANAGER
#define MEMORY_MANAGER

#include <kernel/type.h>
#include <kernel/utils.h>

namespace kernel {

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

    void initialize();

    void* malloc(uint16 size);
    void* free(void *ptr);
    void* reserve(void* ptr, uint16 size);  // reserve memory for drivers, modules

protected:
    MemoryEntry* find(uint16 size);    // return the address of the entry such that will point to the creating entry
    void* makeFirstMemoryEntry(uint16 size);
    void* makeMemoryEntry(void* ptrPrev, uint16 size);
    void* makeMemoryEntryAt(void* ptr, void* ptrPrev, uint16 size);
};
}


void* memreg(void* ptr, kernel::uint16 size);
void memunreg(void *ptr);

void* malloc(kernel::size_t size);
void free(void* ptr);

void* operator new(kernel::size_t size);
void operator delete(void* ptr);
void operator delete(void* ptr, kernel::size_t size);

void* operator new[](kernel::size_t size);
void operator delete[](void* ptr);

#endif