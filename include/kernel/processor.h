#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <kernel/type.h>

namespace kernel
{

class Processor
{
public:
    uint8 localApicId;
    
    Processor();
    
    virtual void intialize(uint8 localApicID = 0);
};

}
#endif // PROCESSOR_H
