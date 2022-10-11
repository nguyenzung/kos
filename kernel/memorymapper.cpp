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
    PhysicalMemory *physicalMemory = PhysicalMemory::getInstance();
    
    uint64 totalPhysicalMemoryFrame = (size / MEMORY_FRAME_SIZE) + (size % MEMORY_FRAME_SIZE ? 1 : 0);
    if (totalPhysicalMemoryFrame > PAGE_SIZE * NUM_PT_TABLE)
        totalPhysicalMemoryFrame = PAGE_SIZE * NUM_PT_TABLE;    
    pml4.setEntry(0, &pdp.value[0], space);
    for (uint8 i = 0; i < NUM_PD_TABLE; ++i)
        pdp.setEntry(i, &pd[i].value[0], space);
    for (uint64 i = 0; i < totalPhysicalMemoryFrame; ++i)
    {
        uint32 frameIndex = physicalMemory->load();
        pt[i >> 9].setEntry(i & 0b111111111, frameIndex, space);
        if (i % PAGE_SIZE == 0)
        {
            pd[i >> 18].setEntry((i >> 9) & 0b111111111, &pt[i >> 9].value[0], space);
        }      
    }
}

void MemoryMapper::debug()
{
    printf("\nPML4 %b %b ", pml4.value[0], pml4.value[1]);
    printf("\nPDP %b %b ", pdp.value[0], pdp.value[3]);
    printf("\nPD %b %b %b %b ", pd[3].value[0], pd[3].value[1], pd[3].value[255], pd[2].value[256]); 
     printf("\nPT %b %b %b %b ", pt[2047].value[0], pt[2047].value[1], pt[2047].value[255], pt[2047].value[511]); 
    
//    printf("\nPML4 %p %p ", &pml4.value[0], &pml4.value[1]);
//    printf("\nPDP %p %p ", &pdp.value[0], &pdp.value[1]);
//    printf("\nPD %p %p %p %p ", &pd.value[0], &pd.value[1], &pd.value[255], &pd.value[256]);  
}