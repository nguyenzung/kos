#include <kernel/memorymapper.h>
#include <kernel/physicalmemory.h>

using namespace kernel;

PML4::PML4()
{
    for(int i = 0; i < PAGE_SIZE; ++i)
        value[i] = 0;
}

void PML4::setEntry(uint16 index, void *pdpAddress, OSSpace space)
{
    
    uint64 address = (uint64)pdpAddress;
    printf("\n [Before] %d %b %p", index, address, pdpAddress);
    address = address | 0b11;
    if(space == OSSpace::RING_3)
        address = address | 0b100;
    value[index] = address;
    printf("\n [After] %d %b %p", index, address, pdpAddress);
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

void MemoryMapper::initialize(uint64 size, OSSpace space)
{
    uint64 totalPhysicalMemoryFrame = (size / MEMORY_FRAME_SIZE) + (size % MEMORY_FRAME_SIZE ? 1 : 0);
    if (totalPhysicalMemoryFrame > PAGE_SIZE * PAGE_SIZE)
        totalPhysicalMemoryFrame = PAGE_SIZE * PAGE_SIZE;
    
    pml4.setEntry(0, &pdp.value[0], space);
    pdp.setEntry(0, &pd.value[0], space);
    PhysicalMemory *physicalMemory = PhysicalMemory::getInstance();
    for (uint32 i = 0; i < totalPhysicalMemoryFrame; ++i)
    {
        uint32 frameIndex = physicalMemory->load();
        pt[i / PAGE_SIZE].setEntry(i % PAGE_SIZE, frameIndex, space);
        if (i  % PAGE_SIZE == 0)
        {
            pd.setEntry(i / PAGE_SIZE, &pt[i / PAGE_SIZE], space);
        }      
    }
}

void MemoryMapper::debug()
{
    printf("\nPML4 %b %b ", pml4.value[0], pml4.value[1]);
    printf("\nPDP %b %b ", pdp.value[0], pdp.value[1]);
    printf("\nPD %b %b %b %b ", pd.value[0], pd.value[1], pd.value[255], pd.value[256]);  
    
    printf("\nPML4 %p %p ", &pml4.value[0], &pml4.value[1]);
    printf("\nPDP %p %p ", &pdp.value[0], &pdp.value[1]);
    printf("\nPD %p %p %p %p ", &pd.value[0], &pd.value[1], &pd.value[255], &pd.value[256]);  
}