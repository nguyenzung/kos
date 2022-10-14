#include <kernel/gdt.h>

using namespace kernel;

GDT::GDT()
{
    
}

GDT::~GDT()
{
    
}

void GDT::initialize(OSSpace osspace)
{
    
}

void GDT::setupKernelModeGDT()
{
//    *((uint64*)&entries[0]) = 0;
//    entries[1].limit0 = 0;
//    entries[1].base0 = 0;
}

void GDT::setupUserModeGDT()
{
    
}