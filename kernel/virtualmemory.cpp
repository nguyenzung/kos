#include <kernel/virtualmemory.h>
#include <kernel/printer.h>

using namespace kernel;

VirtualMemory:: VirtualMemory()
{
    
}

void VirtualMemory::initialize(uint64 size, OSSpace space)
{
    this->size = size;
    memoryMapper.initialize(size, space);
    memoryMapper.debug();
}

void VirtualMemory::loadDefault()
{

}

void VirtualMemory::active()
{    
    asm ("movq %0, %%cr3"::"r"(memoryMapper.pml4.value):);
}