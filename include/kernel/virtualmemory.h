#ifndef VIRTUAL_MEMORY
#define VIRTUAL_MEMORY

#include <kernel/memorymapper.h>
#include <kernel/type.h>

namespace kernel
{

class VirtualMemory
{
public:
    MemoryMapper mapper;
    uint64 size;

    VirtualMemory();
    
    void initialize(uint64 size);
    void loadDefault();     // Load config from assembly code
    void active();
};

}
#endif