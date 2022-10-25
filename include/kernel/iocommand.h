#ifndef IO_COMMAND
#define IO_COMMAND

#include <kernel/type.h>

using namespace kernel;

uint64 rdtsc();
void outb(uint16 port, uint8 value);
uint8 inb(uint16 port);
void outw(uint16 port, uint16 value);
uint16 inw(uint16 port);
void outl(uint16 port, uint32 value);
uint32 inl(uint16 port);
void io_wait(void);


#endif
