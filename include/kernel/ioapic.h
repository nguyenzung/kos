#ifndef IOAPIC_H
#define IOAPIC_H

#include<kernel/type.h>

namespace kernel
{
#define IOAPICID    0x00
#define IOAPICVER   0x01
#define IOAPICARB   0x02

#define IOREGSEL    0x00
#define IOREGWIN    0x10

typedef struct RedirectionEntry 
{
    uint64 vector           : 8;
    uint64 deliveryMode     : 3;
    uint64 destinationMode  : 1;
    uint64 deliveryStatus   : 1;
    uint64 pinPolarity      : 1;
    uint64 remoteIRR        : 1;
    uint64 triggerMode      : 1;
    uint64 mask             : 1;
    uint64 reserved         : 39;
    uint64 destination      : 8;
} RedirectionEntry;

class IOAPIC
{
public:    
    IOAPIC();
    ~IOAPIC();
    
    void initialize();
    
    void write32(uint8 regIndex, uint32 value);
    uint32 read32(uint8 regIndex);
    
    // write 64 bits data
    void write(uint8 irqRegBaseIndex, uint64 value);    
    // read 64 bits data
    uint64 read(uint8 irqRegBaseIndex);
    
    void setupIRQ(uint8 irqIndex, uint8 apicId);
    
    uint8 getIRQRegIndex(uint8 irqIndex);
    
    
};

/*
 *  Support 1 IOAPIC: enough for now because the os can handle up to 24 external interrupts
 */
IOAPIC *loadIOAPIC(uint8 index = 0);

}

#endif // IOAPIC_H
