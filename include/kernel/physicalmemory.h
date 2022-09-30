#ifndef PHYSICAL_MEMORY
#define PHYSICAL_MEMORY

#include <kernel/type.h>
#include <stdlib/unorderedmap.h>

namespace kernel
{

class PhysicalMemory
{
public:
    uint32 totalFrame;
    uint32 nextAllocatedIndex;
    uint32 minAllocatedIndex;
    std::UnorderedMap<uint32, uint8> frameInfo;    // A Frame can be assigned to many processes
    std::List<uint32> freeFrames;

public:
    PhysicalMemory();
    ~PhysicalMemory();

    uint32 load();
    uint32 loadInFreeFrames();
    uint32 loadByNext();
    uint32 load(uint32 index);

    uint8 checkIndex(uint32 index);
    bool unload(uint32 index);

};

}

#endif