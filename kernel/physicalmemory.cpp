#include <kernel/physicalmemory.h>

PhysicalMemory::PhysicalMemory()
{
    // Temporary hard code
    totalFrame          = 100010;    
    minAllocatedIndex   = 100000;
    nextAllocatedIndex  = minAllocatedIndex;
}

PhysicalMemory::~PhysicalMemory()
{

}

uint32 PhysicalMemory::load()
{
    uint32 index;
    return index = loadInFreeFrames(), index ? index: loadByNext();
}

uint32 PhysicalMemory::loadInFreeFrames()
{
    // TODO
    return 0;
}

uint32 PhysicalMemory::loadByNext()
{
    while (nextAllocatedIndex <= totalFrame)
    {
        if (!frameInfo.contains(nextAllocatedIndex))
        {
            frameInfo[nextAllocatedIndex] = 1;
            nextAllocatedIndex++;
            return (nextAllocatedIndex - 1);
        }
        nextAllocatedIndex++;
    }
    return 0;
}

uint32 PhysicalMemory::load(uint32 index)
{
    // printf("\n [ %d, %d, %d ]", index, minAllocatedIndex, totalFrame);
    return  (index >= minAllocatedIndex && index <= totalFrame && frameInfo[index].second < UINT16_MAX) ? ++frameInfo[index].second : 0;
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
