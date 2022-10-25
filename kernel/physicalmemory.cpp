#include <kernel/physicalmemory.h>

IMPL_MODULE_INSTANCE(PhysicalMemory)


PhysicalMemory::PhysicalMemory()
{
    setInstance(this);
}

PhysicalMemory::~PhysicalMemory()
{
}

void PhysicalMemory::initialize()
{
    frameInfo = new std::UnorderedMap<uint32, uint8>(20129);
    totalFrame          = UINT32_MAX;   // Need to calculate
    minAllocatedIndex   = 0;            // Need to calculate
    nextAllocatedIndex  = minAllocatedIndex;
}

uint32 PhysicalMemory::load()
{
    uint32 index;
    return index = loadInFreeFrames(), index != -1 ? index: loadByNext();
}

int PhysicalMemory::loadInFreeFrames()
{
    if (freeFrames.size() > 0)
    {
        uint32 index = freeFrames.removeLast();
        return load(index);
    }
    return -1;
}

uint32 PhysicalMemory::loadByNext()
{
    while (nextAllocatedIndex <= totalFrame)
    {
        if (!(*frameInfo).contains(nextAllocatedIndex))
        {
            (*frameInfo).putNewKey(nextAllocatedIndex, 1);
            nextAllocatedIndex++;
            return (nextAllocatedIndex - 1);
        }
        nextAllocatedIndex++;
    }
    return 0;
}

uint32 PhysicalMemory::load(uint32 index)
{
    return (index >= minAllocatedIndex && index <= totalFrame && (*frameInfo)[index].second < UINT16_MAX) ? (*frameInfo)[index].second++, index : 0;
}

uint8 PhysicalMemory::checkIndex(uint32 index)
{
    return (*frameInfo)[index].second;
}

bool PhysicalMemory::unload(uint32 index)
{
    if((*frameInfo).contains(index))
    {
        --(*frameInfo)[index];
        if ((*frameInfo)[index].second == 0)
        {
            (*frameInfo).erase(index);
            freeFrames.add(index);
        }
        return true;
    }
    return false;
}
