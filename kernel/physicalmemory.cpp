#include <kernel/physicalmemory.h>

PhysicalMemory::PhysicalMemory()
{
}

PhysicalMemory::~PhysicalMemory()
{
}

void PhysicalMemory::initialize()
{
    totalFrame          = UINT32_MAX;   // Need to calculate
    minAllocatedIndex   = 30000;       // Need to calculate
    nextAllocatedIndex  = minAllocatedIndex;
}

uint32 PhysicalMemory::load()
{
    uint32 index;
    return index = loadInFreeFrames(), index ? index: loadByNext();
}

uint32 PhysicalMemory::loadInFreeFrames()
{
    if (freeFrames.size > 0)
    {
        uint32 index = freeFrames.removeLast();
        return load(index);
    }
    return 0;
}

uint32 PhysicalMemory::loadByNext()
{
    while (nextAllocatedIndex <= totalFrame)
    {
        if (!frameInfo.contains(nextAllocatedIndex))
        {
            frameInfo.putNewKey(nextAllocatedIndex, 1);
            nextAllocatedIndex++;
            return (nextAllocatedIndex - 1);
        }
        nextAllocatedIndex++;
    }
    return 0;
}

uint32 PhysicalMemory::load(uint32 index)
{
    return (index >= minAllocatedIndex && index <= totalFrame && frameInfo[index].second < UINT16_MAX) ? frameInfo[index].second++, index : 0;
}

uint8 PhysicalMemory::checkIndex(uint32 index)
{
    return frameInfo[index].second;
}

bool PhysicalMemory::unload(uint32 index)
{
    if(frameInfo.contains(index))
    {
        --frameInfo[index];
        if (frameInfo[index].second == 0)
        {
            frameInfo.erase(index);
            freeFrames.add(index);
        }
        return true;
    }
    return false;
}
