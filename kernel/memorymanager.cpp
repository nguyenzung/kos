#include "memorymanager.h"
#include "printer.h"

extern void* heapBase;
extern void* stackBase;
extern void* protected_start_bss;
extern void* protected_end_bss;

IMPLE_MODULE_INSTANCE(MemoryManager)

MemoryManager::MemoryManager() {
    kernelHeapAddress = heapBase;
    kernelStackBase =  stackBase;
    Printer::printlnAddress((uint64)kernelHeapAddress);
    first = (MemoryEntry*) this->makeFirstMemoryEntry(0xffff);
    MemoryManager::setInstance(this);
}

MemoryManager::~MemoryManager() {

}

MemoryEntry* MemoryManager::find(uint16 size) {
    MemoryEntry *current = this->first;
    Printer::println("**", 2);
    while (current->next)
    {
        MemoryEntry *next = current->next;
        if((uint64)current + MEMORY_ENTRY_SIZE + current->size + size <= (uint64)next) {
            Printer::println("Found", 5);
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
    MemoryEntry *entry = (MemoryEntry*)this->kernelHeapAddress;
    entry->size = size;
    entry->next = 0;
    // Printer::printNumber(entry->size);
    // Printer::print(" FIRST ", 7);
    // Printer::printlnNumber((uint64)entry->next);
    return entry;
}

void* MemoryManager::makeMemoryEntry(void* prevAddress, uint16 size) {
    Printer::printlnAddress((uint64)this);
    MemoryEntry *prev = (MemoryEntry*)prevAddress;
    MemoryEntry *entry;
    void* entryAddress = prevAddress + sizeof(MemoryEntry) + prev->size;
    entry = (MemoryEntry*)entryAddress;
    entry->size = size;
    entry->next = prev->next;
    if (entry->next != prev->next) {
        Printer::println("W T F",5);
    }
    uint64 *next = (uint64*)entryAddress;
    prev->next = entry;
    return entry;
}