#ifndef IOAPIC_H
#define IOAPIC_H

#include<kernel/type.h>

namespace kernel
{

class IOAPIC
{
public:
    IOAPIC();
    ~IOAPIC();
    
    void setValue();
};

IOAPIC *loadIOAPIC(uint8 index = 0);

}

#endif // IOAPIC_H
