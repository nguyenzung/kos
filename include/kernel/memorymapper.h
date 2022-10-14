#ifndef MEMORY_MAPPER
#define MEMORY_MAPPER

#include <kernel/type.h>
#include <kernel/osspace.h>

namespace kernel
{

#define PAGE_SIZE           512
#define NUM_PD_TABLE        4
#define NUM_PT_TABLE        2048
#define MEMORY_FRAME_SIZE   4096

class PML4
{
public:
    __attribute__((aligned(0x1000)))
    uint64 value[PAGE_SIZE];
    
    PML4();
    void setEntry(uint16 index, void *pdpAddress, OSSpace space);
};

class PDP
{
public:
    __attribute__((aligned(0x1000)))
    uint64 value[PAGE_SIZE];
    
    PDP();
    void setEntry(uint16 index, void *pdAddress, OSSpace space);
};

class PD
{
public:
    __attribute__((aligned(0x1000)))
    uint64 value[PAGE_SIZE];
    
    PD();
    void setEntry(uint16 index, void *ptAddress, OSSpace space);
};

class PT
{
public:
    __attribute__((aligned(0x1000)))
    uint64 value[PAGE_SIZE];
    
    PT();
    void setEntry(uint16 index, uint64 frameIndex, OSSpace space);
};


class MemoryMapper
{
public:
//    __attribute__((aligned(0x1000)))
    PML4   pml4;
    PDP    pdp;
    PD     pd[NUM_PD_TABLE];
    PT     pt[NUM_PT_TABLE]; // Cache 4GB
    
    uint64 size;
    
    MemoryMapper();
    
    void initialize(uint64 size, OSSpace space);
    void debug();
};

}

#endif
