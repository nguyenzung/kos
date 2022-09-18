#ifndef INTERRUPT_HANDLER
#define INTERRUPT_HANDLER

#include <kernel/type.h>

namespace kernel 
{

class InterruptHandler 
{

protected:
    uint8 vector;

public:
    InterruptHandler(uint8 vector);
    uint8 getVector();

    virtual void handleInterrupt() = 0;
};

}

#endif