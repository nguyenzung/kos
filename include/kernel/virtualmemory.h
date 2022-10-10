#ifndef VIRTUAL_MEMORY
#define VIRTUAL_MEMORY

#include <kernel/memorymapper.h>
#include <kernel/osspace.h>
#include <kernel/type.h>

namespace kernel
{

class VirtualMemory
{
public:
    MemoryMapper memoryMapper;
    uint64 size;

    VirtualMemory();
    
    void initialize(uint64 size, OSSpace space);
    void loadDefault();     // Load config from assembly code
    void active();
};

}
#endif