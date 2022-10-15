#ifndef APIC_H
#define APIC_H

#include <kernel/type.h>

namespace kernel
{

#define LAPIC_ID            0x20
#define LAPIC_VERSION       0x30
#define TPR                 0x80
#define EOI                 0xB0
#define LOGICAL_DESTINATION 0xD0
#define SPURIOUS            0xF0
#define INT_CMD_LOW         0x300
#define INT_CMD_HIGH        0x310
#define TIMER_LVT           0x320
#define TIMER_INITIAL_COUNT 0x380
#define TIMER_CURRENT_COUNT 0x390
#define TIMER_DIVIDE_CONFIG 0x3E0

class APIC
{
public:
    APIC();
    ~APIC();
    
    void enable();
    void disable();
    
    void write(uint16 reg, uint32 data);
    uint32 read(uint16 reg);
    
    void startTimer();
};

APIC* loadAPIC();

}

#endif // APIC_H
