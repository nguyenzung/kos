#ifndef PIC_H
#define PIC_H

#include <kernel/type.h>

namespace kernel
{

#define OFFSET 0x20

class PIC
{
public:
    PIC();
    ~PIC();
    
    void enable();
    void disable();
    
    void remap();
    void setMask(uint8 irq);
    void clearMask(uint8 irq);
    
    void eoi(uint8 vector);
};

}

#endif // PIC_H
