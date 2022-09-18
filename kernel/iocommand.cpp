#include <kernel/iocommand.h>

using namespace kernel;

void outb(uint16 port, uint8 value)
{
    asm ("outb %0, %1" : : "r" (value), "Nd" (port));
}

uint8 inb(uint16 port)
{
    uint8 result;
    asm ("inb %1, %0" : "=r" (result) : "Nd" (port));
    return result;
}

void outw(uint16 port, uint16 value)
{
    asm ("outw %0, %1" : : "r" (value), "Nd" (port));
}

uint16 inw(uint16 port) 
{
    uint16 result;
    asm ("inw %1, %0" : "=r" (result) : "Nd" (port));
    return result;
}

void outl(uint16 port, uint32 value)
{
    asm ("outl %0, %1" : : "r" (value), "Nd" (port));
}

uint32 inl(uint16 port)
{
    uint32 result;
    asm ("inl %1, %0" : "=r" (result) : "Nd" (port));
    return result;
}

void io_wait() {
    outb(0x80, 0);
}