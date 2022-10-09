#include <kernel/memorymapper.h>

using namespace kernel;

PML4::PML4()
{
    for(int i = 0; i < PAGE_SIZE; ++i)
        value[i] = 0;
}

void PML4::setEntry(uint16 index, void *pdpAddress, OSSpace space)
{
    uint64 address = (uint64)pdpAddress;
    address = address | 0b11;
    if(space == OSSpace::RING_3)
        address = address | 0b100;
    value[index] = address;
}

PDP::PDP()
{
    for(int i = 0; i < PAGE_SIZE; ++i)
        value[i] = 0;
}

void PDP::setEntry(uint16 index, void *pdAddress, OSSpace space)
{
    uint64 address = (uint64)pdAddress;
    address = address | 0b11;
    if(space == OSSpace::RING_3)
        address = address | 0b100;
    value[index] = address;
}

PD::PD()
{
    for(int i = 0; i < PAGE_SIZE; ++i)
        value[i] = 0;
}

void PD::setEntry(uint16 index, void *ptAddress, OSSpace space)
{
    uint64 address = (uint64)ptAddress;
    address = address | 0b11;
    if(space == OSSpace::RING_3)
        address = address | 0b100;
    value[index] = address;
}

PT::PT()
{
    for(int i = 0; i < PAGE_SIZE; ++i)
        value[i] = 0;
}

void PT::setEntry(uint16 index, uint64 frameIndex, OSSpace space)
{
    uint64 address = frameIndex * MEMORY_FRAME_SIZE;
    address = address | 0b11;
    if(space == OSSpace::RING_3)
        address = address | 0b100;
    value[index] = address;
}

MemoryMapper::MemoryMapper()
{
    
}

void MemoryMapper::initialize()
{
    
}