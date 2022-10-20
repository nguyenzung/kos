#ifndef MULTIBOOTHEADER_H
#define MULTIBOOTHEADER_H

#include <kernel/type.h>

namespace kernel
{

#define MULTIBOOT_FRAMEBUFFER_INDEXED      0
#define MULTIBOOT_FRAMEBUFFER_RGB          1
#define MULTIBOOT_FRAMEBUFFER_EGA_TEXT     2

typedef struct MultibootHeader
{
    uint32 totalSize;
    uint32 reseved;
} MultibootHeader;

typedef struct MultibootTag 
{
    uint32 type;
    uint32 size;
} MultibootTag;

typedef struct MultibootTagFrameBuffer
{
    MultibootTag tag;
    uint32  address;
    uint32  pitch;
    uint32  width;
    uint32  height;
    uint8   bpp;    
    uint8   type;
    uint16  reserved;
}MultibootTagFrameBuffer;

class Multiboot    
{
    MultibootHeader *header;
};

}

#endif // MULTIBOOTHEADER_H
