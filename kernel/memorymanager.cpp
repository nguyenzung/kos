#include "memorymanager.h"

extern void* heap_base;

MemoryManager::MemoryManager() {
    heapAddress = (uint64)heap_base;
    first = nullptr;
    last = nullptr;
}

MemoryManager::~MemoryManager() {

}

void* MemoryManager::malloc(uint16 size) {
    return 0;
}

bool MemoryManager::free(void *ptr) {
    return true;
}