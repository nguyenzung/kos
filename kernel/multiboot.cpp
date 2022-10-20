#include <kernel/multiboot.h>
#include <kernel/printer.h>
#include <stdlib/string.h>
#include <driver/serial.h>

using namespace kernel;
using namespace driver;

IMPL_MODULE_INSTANCE(Multiboot)

Multiboot::Multiboot()
{
    Multiboot::instance = this;
}

Multiboot::~Multiboot()
{
    
}

void Multiboot::initializeInLegacyMode(void *multibootAddress)
{
    mbHeader = (MultibootHeader*)multibootAddress;
    void *endTagAddress = (multibootAddress + mbHeader->totalSize);
    void *tagAddress = (multibootAddress + 8);
    while (tagAddress < endTagAddress) {
        MultibootTag *tag = (MultibootTag*)tagAddress;
        if (tag->type == 8)
        {
            frameBuffer = (MultibootTagFrameBuffer*)tag;
            frameBuffer->framebufferBlueFieldPosition;
        }
        tagAddress += ((tag->size + 7) & ~7);        
    }
}

MultibootHeader *Multiboot::getMultibootHeader()
{
    return mbHeader;
}

MultibootTagFrameBuffer *Multiboot::getFrameBuffer()
{
    return frameBuffer;
}
