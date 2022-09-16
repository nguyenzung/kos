#ifndef IO_COMMAND
#define IO_COMMAND

#include <kernel/type.h>

namespace kernel {

class IOCommand {
public:
    static void outb(uint16 port, uint8 value);
    static uint8 inb(uint16 port);

    static void outw(uint16 port, uint16 value);
    static uint16 inw(uint16 port);

    static void outl(uint16 port, uint32 value);
    static uint32 inl(uint16 port);

    static void io_wait(void);

};

}
#endif