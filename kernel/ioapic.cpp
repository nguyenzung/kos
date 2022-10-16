#include <kernel/ioapic.h>
#include <kernel/sdt.h>

using namespace kernel;

IOAPIC::IOAPIC()
{
    
}

IOAPIC::~IOAPIC()
{
    
}

void IOAPIC::setValue()
{
    
}

IOAPIC* kernel::loadIOAPIC(uint8 index)
{
    std::List<IOAPICDescriptor*> ioApicDescriptors = SDT::getIOAPICDescriptors();
    uint8 current = 0;
    return nullptr;
}