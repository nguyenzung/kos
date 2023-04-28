#ifndef GDT_H
#define GDT_H

#include <kernel/type.h>
#include <kernel/osspace.h>

namespace kernel
{
#define PRESENT         1 << 7
#define USER_PL         3 << 5
#define SYS_SEG         1 << 4
#define EXEC            1 << 3
#define DC              1 << 2

#define OPERAND_SIZE    1 << 6
#define LONG            1 << 5

typedef struct GDT64Entry
{
    uint16  limit0;
    uint16  base0;
    uint8   base1;
    uint8   accessByte;
    uint8   limit1AndFlags;    // first 4 bits is used for limit, next 4 bits is used for flags
    uint8   base2;
} __attribute__((packed)) GDT64Entry;

class GDT64
{
    __attribute__((aligned(0x1000)))
    GDT64Entry entries[4];
public:
    GDT64();
    ~GDT64();
    
    void initialize(OSSpace osspace);
    
    void setupKernelModeGDT();
    void setupUserModeGDT();
};

}

#endif // GDT_H
