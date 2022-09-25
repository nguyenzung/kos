#ifndef MEMORY_MANAGER
#define MEMORY_MANAGER

#include <kernel/type.h>
#include <kernel/utils.h>

namespace kernel 
{

#define MEMORY_ENTRY_SIZE 12
typedef struct MemoryEntry 
{
    MemoryEntry *next;
    uint32 size;
} __attribute__((packed)) MemoryEntry;

class HeapMemoryManager 
{
    void* kernelHeapBase;
    void* kernelStackBase;
    MemoryEntry *first;
    DEF_MODULE_INSTANCE(HeapMemoryManager)
public:
    HeapMemoryManager();
    ~HeapMemoryManager();

    void initialize();

    void* malloc(uint32 size);
    void* free(void *ptr);
    void* reserve(void* ptr, uint32 size);  // reserve memory for drivers, modules

protected:
    MemoryEntry* find(uint32 size);    // return the address of the entry such that will point to the creating entry
    void* makeFirstMemoryEntry(uint32 size);
    void* makeMemoryEntry(void* ptrPrev, uint32 size);
    void* makeMemoryEntryAt(void* ptr, void* ptrPrev, uint32 size);
};
}


void* memreg(void* ptr, kernel::uint32 size);
void memunreg(void *ptr);

void* malloc(kernel::size_t size);
void free(void* ptr);

void* operator new(kernel::size_t size);
void operator delete(void* ptr);
void operator delete(void* ptr, kernel::size_t size);

void* operator new[](kernel::size_t size);
void operator delete[](void* ptr);

#endif