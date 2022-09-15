#include "memorymanager.h"
#include "printer.h"

extern void* heapBase;
extern void* stackBase;
extern void* protected_start_bss;
extern void* protected_end_bss;

IMPLE_MODULE_INSTANCE(MemoryManager)

MemoryManager::MemoryManager() {
    kernelHeapBase = heapBase;
    kernelStackBase =  stackBase;
    Printer::print("HeapBase: ", 10);
    Printer::printAddress((uint64)kernelHeapBase);
    Printer::print(" StackBase: ", 12);
    Printer::printlnAddress((uint64)kernelStackBase);
    first = (MemoryEntry*) this->makeFirstMemoryEntry(0xffff);
    MemoryManager::setInstance(this);
}

MemoryManager::~MemoryManager() {

}

MemoryEntry* MemoryManager::find(uint16 size) {
    MemoryEntry *current = this->first;
    while (current->next)
    {
        MemoryEntry *next = current->next;
        if((uint64)current + MEMORY_ENTRY_SIZE + current->size + size <= (uint64)next) {
            return current;
        }
        current = next;
    }
    return current;
}

void* MemoryManager::malloc(uint16 size) {
    MemoryEntry* prev = this->find(size);
    return this->makeMemoryEntry(prev, size);
}

void* MemoryManager::free(void *ptr) {
    return 0;
}

void* MemoryManager::reserve(void* ptr, uint16 size) {
    return 0;
}

void* MemoryManager::makeFirstMemoryEntry(uint16 size) {
    MemoryEntry *entry = (MemoryEntry*)this->kernelHeapBase;
    entry->size = size;
    entry->next = 0;
    return entry;
}

void* MemoryManager::makeMemoryEntry(void* prevAddress, uint16 size) {
    MemoryEntry *prev = (MemoryEntry*)prevAddress;
    MemoryEntry *entry;
    uint64 entryAddress = (uint64)prevAddress + (uint64)10 + (uint64)(prev->size);
    entry = (MemoryEntry*)entryAddress;
    entry->size = size;
    entry->next = prev->next;
    prev->next = entry;
    return entry;
}