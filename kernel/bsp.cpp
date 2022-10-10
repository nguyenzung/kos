#include <kernel/bsp.h>
#include <stdlib/string.h>
#include <kernel/printer.h>
#include <cpuid.h>

using namespace kernel;

// bootstrap function when activating another cores
extern void *setupAPAddress;

BSP::BSP():Processor()
{
    
}

void BSP::intialize(uint8)
{
    __asm__ ("mov $1, %%eax; cpuid; shrl $24, %%ebx;": "=b"(this->localApicId) : : );
    printf("\n Setup AP %d ", setupAPAddress);
    
    std::memmove((void*)0x8000, setupAPAddress, 4096);
}

void BSP::disablePIC()
{
    
}

void BSP::enableAPIC()
{
    
}

void BSP::activeSMP()
{
    
}