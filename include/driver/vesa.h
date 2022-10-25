#ifndef VESA_H
#define VESA_H

#include <kernel/type.h>
#include <kernel/utils.h>
#include <kernel/multiboot.h>

#include <kernel/basegraphicsdevice.h>

using namespace kernel;

namespace driver
{

class VESA: public BaseGraphicsDevice {
public:

protected:    
    void *frameBuffer;
    uint8 alphaIndex;
    uint8 redIndex;
    uint8 greenIndex;
    uint8 blueIndex;
    
public:
    VESA();
    ~VESA();
    
    DEF_MODULE_INSTANCE(VESA)
    
    void setupVideoMode() override;
    void drawPixel(uint16 x, uint16 y, uint8 r, uint8 g, uint8 b) override;
    void drawRectangle(uint16 x, uint16 y, uint16 w, uint16 h, uint8 r, uint8 g, uint8 b) override;
    void clearScreen(uint8 r, uint8 g, uint8 b);
};

}

#endif // VESA_H
