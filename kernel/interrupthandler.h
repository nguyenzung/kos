#ifndef INTERRUPT_HANDLER
#define INTERRUPT_HANDLER

#include "type.h"

class InterruptHandler {
protected:
    uint8 vector;

    virtual void handle() = 0;
};

#endif