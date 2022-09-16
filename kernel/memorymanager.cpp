#include "memorymanager.h"
#include "printer.h"

extern void* heapBase;
extern void* stackBase;
extern void* protected_start_bss;
extern void* protected_end_bss;

IMPLE_MODULE_INSTANCE(MemoryManager)

MemoryManager::MemoryManager() {
    static_assert(sizeof(MemoryEntry) == MEMORY_ENTRY_SIZE);
    kernelHeapBase = heapBase;
    kernelStackBase =  stackBase;
    // Printer::print("HeapBase: ", 10);
    // Printer::printAddress((uint64)kernelHeapBase);
    // Printer::print(" StackBase: ", 12);
    // Printer::printlnAddress((uint64)kernelStackBase);
    first = (MemoryEntry*) this->makeFirstMemoryEntry(1000);
    Printer::printlnNumber((uint64)first);
    MemoryManager::setInstance(this);
}

MemoryManager::~MemoryManager() {

}

MemoryEntry* MemoryManager::find(uint16 size) {
    MemoryEntry *current = this->first;
    while (current->next)
    {
        MemoryEntry *next = current->next;
        if((uint64)current + MEMORY_ENTRY_SIZE + current->size + MEMORY_ENTRY_SIZE + size <= (uint64)next) {            
            return current;
        }
        current = next;
    }
    return current;
}

void* MemoryManager::malloc(uint16 size) {
    MemoryEntry* prev = this->find(size);
    void* ptr = this->makeMemoryEntry(prev, size);
    return ptr + MEMORY_ENTRY_SIZE;
}

void* MemoryManager::free(void *ptr) {
    ptr = ptr - MEMORY_ENTRY_SIZE;
    MemoryEntry *prev = this->first;
    MemoryEntry *current = prev->next;
    while(current) {
        if (current == ptr) {
            prev->next = current->next;
            return (void*)current + MEMORY_ENTRY_SIZE;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void* MemoryManager::reserve(void* ptr, uint16 size) {
    ptr = ptr - MEMORY_ENTRY_SIZE;
    MemoryEntry *current = this->first;
    while(current) {
        // Printer::println("W", 1);
        if (current->next) {
            if(current < ptr && ptr < current->next) {
                if (((void*)current + MEMORY_ENTRY_SIZE + current->size <= ptr) && (ptr + size + MEMORY_ENTRY_SIZE <= (void*)current->next)) {
                    this->makeMemoryEntryAt(ptr, current, size);
                    return ptr + MEMORY_ENTRY_SIZE;
                } else {
                    return 0;
                }
            } 
        }else {
            if ((void*)current + MEMORY_ENTRY_SIZE + current->size <= ptr) {
                this->makeMemoryEntryAt(ptr , current, size);
                return ptr + MEMORY_ENTRY_SIZE;
            }
        }
        current = current->next;
    }
    return 0;
}

void* MemoryManager::makeFirstMemoryEntry(uint16 size) {
    MemoryEntry *entry = (MemoryEntry*)this->kernelHeapBase;
    entry->size = size;
    entry->next = 0;
    return entry;
}

void* MemoryManager::makeMemoryEntry(void* ptrPrev, uint16 size) {
    MemoryEntry *prev = (MemoryEntry*)ptrPrev;
    void* ptr = ptrPrev + MEMORY_ENTRY_SIZE + (prev->size);
    return this->makeMemoryEntryAt(ptr, ptrPrev, size);
}

void* MemoryManager::makeMemoryEntryAt(void* ptr, void* ptrPrev, uint16 size) {
    MemoryEntry *prev = (MemoryEntry*)ptrPrev;
    MemoryEntry *entry = (MemoryEntry*)ptr;
    entry->size = size;
    entry->next = prev->next;
    prev->next = entry;
    return ptr;
}

void* memreg(void* ptr, uint16 size) {
    return MemoryManager::getInstance()->reserve(ptr, size);
}

void memunreg(void *ptr) {
    MemoryManager::getInstance()->free(ptr);
}

void* malloc(size_t size) {
    // void *ptr = MemoryManager::getInstance()->malloc(size);
    return MemoryManager::getInstance()->malloc(size);
}

void free(void* ptr){
    MemoryManager::getInstance()->free(ptr);
}

void* operator new(size_t size) {
    // void *ptr = MemoryManager::getInstance()->malloc(size);
    return MemoryManager::getInstance()->malloc(size);
}

void* operator new[](size_t size) {
    // void *ptr = MemoryManager::getInstance()->malloc(size);
    return MemoryManager::getInstance()->malloc(size);
}

void operator delete(void* ptr) {
    MemoryManager::getInstance()->free(ptr);
}
void operator delete[](void* ptr) {
    MemoryManager::getInstance()->free(ptr);
}