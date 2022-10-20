#ifndef MULTIBOOTHEADER_H
#define MULTIBOOTHEADER_H

#include <kernel/type.h>
#include <kernel/utils.h>

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
    union
    {
        struct
        {
            uint32 framebufferPaletteAddrress;
            uint16 framebufferPaletteNumColors;
        };
        struct
        {
            uint8 framebufferRedFieldPosition;
            uint8 framebufferRedMaskSize;
            uint8 framebufferGreenFieldPosition;
            uint8 framebufferGreenMaskSize;
            uint8 framebufferBlueFieldPosition;
            uint8 framebufferBlueMaskSize;
        };
    };
}MultibootTagFrameBuffer;

class Multiboot    
{
public:
    MultibootHeader *mbHeader;
    MultibootTagFrameBuffer *frameBuffer;
    
    Multiboot();
    ~Multiboot();
    
    DEF_MODULE_INSTANCE(Multiboot)
    
    void initializeInLegacyMode(void *multibootAddress);
    
    MultibootHeader *getMultibootHeader();
    MultibootTagFrameBuffer * getFrameBuffer();
};

}

#endif // MULTIBOOTHEADER_H
