#include <kernel/apic.h>
#include <kernel/sdt.h>
#include <kernel/printer.h>
#include <driver/cmos.h>

using namespace kernel;

APIC::APIC()
{
}

APIC::~APIC()
{   
}

void APIC::enable()
{
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

void APIC::finishedINT(uint8 vector)
{
    write(EOI, 0);
}

void APIC::startTimer()
{
    write(TIMER_INITIAL_COUNT, UINT32_MAX);
    driver::CMOS::getInstance()->updateDateTime();  
    uint32 delay = (UINT32_MAX - read(TIMER_CURRENT_COUNT))/10000;
    write(TIMER_INITIAL_COUNT, delay);
    write(TIMER_LVT, 0x20020);
}

APIC* kernel::loadAPIC()
{
    APIC *apicAddress = (APIC*)(SDT::getInstance()->getMADTHeader()->localAPICAddress);
    return apicAddress;
}