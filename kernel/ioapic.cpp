#include <kernel/ioapic.h>
#include <kernel/sdt.h>
#include <kernel/pic.h>
#include <kernel/printer.h>

using namespace kernel;

IOAPIC::IOAPIC()
{
    
}

IOAPIC::~IOAPIC()
{
    
}

void IOAPIC::initialize()
{
    uint32 ioApicId  = read32(IOAPICID);
    uint32 ioApicVer = read32(IOAPICVER) & 0b1111111111;
    uint32 maxRedirectionEntry = ((read32(IOAPICVER) >> 16) & 0xff) + 1;
    // printf("\n IOAPIC info: id: %d | ver: %d | count: %d", ioApicId, ioApicVer, maxRedirectionEntry);
    
    setupIRQ(1, 0);     // enable Keyboard Interrupt
    setupIRQ(12, 0);    // enable Mouse Interrupt
}

void IOAPIC::write32(uint8 regIndex, uint32 value)
{
    *(volatile uint32*)this = regIndex;
    *(volatile uint32*)((void*)this + IOREGWIN) = value;
}

uint32 IOAPIC::read32(uint8 regIndex)
{
    *(volatile uint32*)this = regIndex;
    return *(volatile uint32*)((void*)this + IOREGWIN);
}

void IOAPIC::write(uint8 irqRegBaseIndex, uint64 value)
{
    uint32 low = value & 0xffffffff;
    write32(irqRegBaseIndex, low);
    uint32 high = value >> 32;
    write32(irqRegBaseIndex + 1, high);    
}

uint64 IOAPIC::read(uint8 irqRegBaseIndex)
{
    uint64 value = read32(irqRegBaseIndex + 1);
    value = value << 32;
    value = value | read32(irqRegBaseIndex);
    return value;
}

void IOAPIC::setupIRQ(uint8 irqIndex, uint8 apicId)
{
    RedirectionEntry entry;
    entry.vector = irqIndex + OFFSET;
    entry.deliveryMode = 0;             // Fixed Mode
    entry.destinationMode = 0;          // Physical Mode
    entry.deliveryStatus = 0;
    entry.pinPolarity = 0;              // Active High
    entry.triggerMode = 0;              // Edge
    entry.destination = apicId;    
    write(getIRQRegIndex(irqIndex), *((uint64*)(&entry)));
}

uint8 IOAPIC::getIRQRegIndex(uint8 irqIndex)
{
    return 0x10 + irqIndex*2;
}

IOAPIC* kernel::loadIOAPIC(uint8 index)
{
    std::Vector<IOAPICDescriptor*> ioApicDescriptors = SDT::getInstance()->getIOAPICDescriptors();
    if (ioApicDescriptors.size() > 0)
    {
        IOAPICDescriptor* descriptor = ioApicDescriptors[index];
        IOAPIC *ioApic = (IOAPIC*)(descriptor->ioApicAddress);
        ioApic->initialize();
        return (IOAPIC*)(descriptor->ioApicAddress);
    }
    
    return nullptr;
}
