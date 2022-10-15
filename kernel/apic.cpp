#include <kernel/apic.h>
#include <kernel/sdt.h>
#include <kernel/printer.h>

using namespace kernel;

APIC::APIC()
{
}

APIC::~APIC()
{   
}

void APIC::enable()
{
    printf("\n APIC:: enable ");
    uint32 apicId = read(LAPIC_ID);
    uint32 apicVersion = read(LAPIC_VERSION) & 0xff;
    printf("\n [APIC] apicId: %d apicVersion: %d ", apicId, apicVersion);
    write(SPURIOUS, read(SPURIOUS) | 0x100);
}

void APIC::disable()
{
}

void APIC::write(uint16 reg, uint32 data)
{
    
    uint32 *address = (uint32*)((void*)this + reg);
    *address = data;
}

uint32 APIC::read(uint16 reg)
{
    uint32 *address = (uint32*)((void*)this + reg);
    return *address;
}

void APIC::startTimer()
{
    write(TPR, 1);
    write(TIMER_INITIAL_COUNT, UINT16_MAX * 2);
    uint32 counter = read(TIMER_CURRENT_COUNT);
    printf("\n APIC:: counter down %d", counter);
    write(TIMER_LVT, 0x00020);
    counter = read(TIMER_LVT);
    printf("\n APIC:: timer lvt %p", counter);
    counter = read(TIMER_CURRENT_COUNT);
    printf("\n APIC:: counter down %d", counter);
}

APIC* kernel::loadAPIC()
{
    APIC *apicAddress = (APIC*)(SDT::getInstance()->getMADTHeader()->localAPICAddress);
    return apicAddress;
}