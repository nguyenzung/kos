#ifndef VESA_H
#define VESA_H

#include <kernel/type.h>
#include <kernel/utils.h>
#include <driver/basegraphicsdevice.h>

using namespace kernel;

namespace driver
{

class VESA: BaseGraphicsDevice {
public:
    class Font {
        
    };

protected:
    uint16 width;
    uint16 height;
    uint8 depth;
    
    void *frameBuffer;
public:
    VESA(void *frameBufferInfo);
    ~VESA();
    
    DEF_MODULE_INSTANCE(VESA)
    
    void setupVideoMode() override;
    void drawPixel(uint32 x, uint32 y, uint8 r, uint8 g, uint8 b) override;
    void drawRectangle(uint32 x, uint32 y, uint32 w, uint32 h, uint8 r, uint8 g, uint8 b) override;
    
};

}

#endif // VESA_H
