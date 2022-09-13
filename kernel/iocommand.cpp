#include "iocommand.h"

void IOCommand::outb(uint16 port, uint8 value) {
    asm ("outb %0, %1" : : "a" (value), "Nd" (port));
}

uint8 IOCommand::inb(uint16 port) {
    uint8 result;
    asm ("inb %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}

void IOCommand::outw(uint16 port, uint16 value) {
    asm ("outw %0, %1" : : "r" (value), "Nd" (port));
}

uint16 IOCommand::inw(uint16 port) {
    uint16 result;
    asm ("inw %1, %0" : "=r" (result) : "Nd" (port));
    return result;
}

void IOCommand::outl(uint16 port, uint32 value) {
    asm ("outl %0, %1" : : "r" (value), "Nd" (port));
}

uint32 IOCommand::inl(uint16 port) {
    uint32 result;
    asm ("inl %1, %0" : "=r" (result) : "Nd" (port));
    return result;
}

void IOCommand::io_wait() {
    IOCommand::outb(0x80, 0);
}
