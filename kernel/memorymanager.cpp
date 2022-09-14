#include "memorymanager.h"

extern uint64 heapBase;
extern uint64 stackBase;

IMPLE_MODULE_INSTANCE(MemoryManager)

MemoryManager::MemoryManager() {
    kernelHeapAddress = (uint64)heapBase;
    kernelStackBase = (uint64) stackBase;
    first = nullptr;
    last = nullptr;
    MemoryManager::setInstance(this);
}

MemoryManager::~MemoryManager() {

}

void* MemoryManager::malloc(uint16 size) {
    return 0;
}

bool MemoryManager::free(void *ptr) {
    return true;
}

bool MemoryManager::reserve(void* ptr, uint16 size) {
    return true;
}