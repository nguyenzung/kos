#include <kernel/gdt.h>

using namespace kernel;

GDT64::GDT64()
{
    
}

GDT64::~GDT64()
{
    
}

void GDT64::initialize(OSSpace osspace)
{
    
}

void GDT64::setupKernelModeGDT()
{
//    *((uint64*)&entries[0]) = 0;
//    entries[1].limit0 = 0;
//    entries[1].base0 = 0;
}

void GDT64::setupUserModeGDT()
{
    
}