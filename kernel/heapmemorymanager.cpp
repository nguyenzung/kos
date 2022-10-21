#include <kernel/heapmemorymanager.h>
#include <kernel/printer.h>

using namespace kernel;

IMPL_MODULE_INSTANCE(HeapMemoryManager)

HeapMemoryManager::HeapMemoryManager()
{
}

HeapMemoryManager::HeapMemoryManager(void *heapBase, uint64 heapSize, void *stackBase)
{
    initialize(heapBase, heapSize, stackBase);
}

HeapMemoryManager::~HeapMemoryManager()
{
}

void HeapMemoryManager::initialize(void *heapBase, uint64 heapSize, void *stackBase)
{
    static_assert(sizeof(kernel::MemoryEntry) == MEMORY_ENTRY_SIZE);
    this->heapBase = heapBase;
    this->heapLimit = heapBase + heapSize;
    this->stackBase =  stackBase;
    available = total = heapSize;
    used = 0;
    last = first = (MemoryEntry*) this->makeFirstMemoryEntry(0x1000);
    printf("Heap base %d Heap limit %d First allocation %d \n", heapBase, heapLimit, first);
    HeapMemoryManager::setInstance(this);    
}

MemoryEntry* HeapMemoryManager::find(uint32 size)
{
    if ((uint64)this->last + MEMORY_ENTRY_SIZE + this->last->size + MEMORY_ENTRY_SIZE + size <= (uint64)heapLimit)
    {
        return this->last;
    }else{
        MemoryEntry *current = this->first;
        while (current->next)
        {
            MemoryEntry *next = current->next;
            if((uint64)current + MEMORY_ENTRY_SIZE + current->size + MEMORY_ENTRY_SIZE + size <= (uint64)next)
            {
                return current;
            }
            current = next;
        }
        return nullptr;
    }
}

void* HeapMemoryManager::malloc(uint32 size)
{
    MemoryEntry* prev = this->find(size);
    if (prev)
    {
        void* ptr = this->makeMemoryEntry(prev, size);
        return ptr + MEMORY_ENTRY_SIZE;
    }
    return nullptr;
}

void* HeapMemoryManager::free(void *ptr)
{
    if (ptr == this->first)
        return nullptr;
    ptr = ptr - MEMORY_ENTRY_SIZE;
    MemoryEntry *prev = this->first;
    MemoryEntry *current = prev->next;
    while(current)
    {
        if (current == ptr)
        {
            if (current == this->last)
                this->last = current->prev;
            if (current->next)
                current->next->prev = prev;
            prev->next = current->next;
            used -= MEMORY_ENTRY_SIZE + current->size;
            available = total - used;
            return (void*)current + MEMORY_ENTRY_SIZE;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void* HeapMemoryManager::reserve(void* ptr, uint32 size)
{
    printf("\n Reserve %d %d ", (uint64)ptr, size);
    if ((uint64)ptr + size >= (uint64)heapLimit)
    {
        return nullptr;
    }
    ptr = ptr - MEMORY_ENTRY_SIZE;
    MemoryEntry *current = this->first;
    while(current) {
        if (current->next)
        {
            if(current < ptr && ptr < current->next)
            {
                if (((void*)current + MEMORY_ENTRY_SIZE + current->size <= ptr) && (ptr + size + MEMORY_ENTRY_SIZE <= (void*)current->next))
                {
                    this->makeMemoryEntryAt(ptr, current, size);
                    return ptr + MEMORY_ENTRY_SIZE;
                } else {
                    return 0;
                }
            }
        }else {
            if ((void*)current + MEMORY_ENTRY_SIZE + current->size <= ptr)
            {
                this->makeMemoryEntryAt(ptr , current, size);
                return ptr + MEMORY_ENTRY_SIZE;
            }
        }
        current = current->next;
    }
    return 0;
}

void* HeapMemoryManager::makeFirstMemoryEntry(uint32 size)
{
    MemoryEntry *entry = (MemoryEntry*)this->heapBase;
    entry->size = size;
    entry->next = nullptr;
    entry->prev = nullptr;
    used += MEMORY_ENTRY_SIZE + size;
    available = total - used;
    return entry;
}

void* HeapMemoryManager::makeMemoryEntry(void* ptrPrev, uint32 size)
{
    MemoryEntry *prev = (MemoryEntry*)ptrPrev;
    void* ptr = ptrPrev + MEMORY_ENTRY_SIZE + (prev->size);
    return this->makeMemoryEntryAt(ptr, ptrPrev, size);
}

void* HeapMemoryManager::makeMemoryEntryAt(void* ptr, void* ptrPrev, uint32 size)
{
    MemoryEntry *prev = (MemoryEntry*)ptrPrev;
    MemoryEntry *entry = (MemoryEntry*)ptr;
    if (prev == this->last)
        this->last = entry;
    entry->size = size;
    entry->next = prev->next;
    entry->prev = prev;
    // entry->nextFreeAddress = ptr + MEMORY_ENTRY_SIZE + size;
    prev->next = entry;
    if (entry->next)
    {
        entry->next->prev = entry;
    }
    used += MEMORY_ENTRY_SIZE + size;
    available = total - used;
    return ptr;
}

/*
*   MemoryEntry is not null
*/
void* getFreeAddress(MemoryEntry *entry)
{
    void *ptr = (void*)entry + MEMORY_ENTRY_SIZE + entry->size;
    return ptr;
}

/*
*   MemoryEntry is not null
*/
void* getFreeSize(MemoryEntry *entry, HeapMemoryManager *instance)
{
    uint64 ptr = (uint64)entry + MEMORY_ENTRY_SIZE + entry->size;
    uint64 next = (uint64)entry->next;
    return (void*)(next?  next - ptr: (uint64)instance->heapLimit - ptr);
}

void* deleteNode(MemoryEntry *node, MemoryEntry *root)
{
    return nullptr;
}

void* addNode(MemoryEntry *node, MemoryEntry *root)
{
    return nullptr;
}

void* find(uint64 size, MemoryEntry* root)
{
    return nullptr;
}

void* memreg(void* ptr, uint32 size)
{
    return HeapMemoryManager::getInstance()->reserve(ptr, size);
}

void memunreg(void *ptr)
{
    HeapMemoryManager::getInstance()->free(ptr);
}

void* malloc(size_t size)
{
    // void *ptr = MemoryManager::getInstance()->malloc(size);
    return HeapMemoryManager::getInstance()->malloc(size);
}

void free(void* ptr)
{
    HeapMemoryManager::getInstance()->free(ptr);
}

void* operator new(size_t size)
{
    // void *ptr = MemoryManager::getInstance()->malloc(size);
    return HeapMemoryManager::getInstance()->malloc(size);
}

void* operator new[](size_t size)
{
    // void *ptr = MemoryManager::getInstance()->malloc(size);
    return HeapMemoryManager::getInstance()->malloc(size);
}

void operator delete(void* ptr)
{
    void *result = HeapMemoryManager::getInstance()->free(ptr);
    // printf("\n DEL %p \n", result);
}

void operator delete(void* ptr, size_t)
{
    void *result = HeapMemoryManager::getInstance()->free(ptr);
    // printf("\n DEL %p \n", result);
}

void operator delete[](void* ptr)
{
    void *result = HeapMemoryManager::getInstance()->free(ptr);
    // printf("\n DEL[] %p \n", result);
}