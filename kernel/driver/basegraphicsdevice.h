#ifndef BASE_GRAPHICS_DEVICE
#define BASE_GRAPHICS_DEVICE

#include "../type.h"

class BaseGraphicsDevice {
public:
    BaseGraphicsDevice();

    virtual void setupVideoMode()=0;
    virtual void drawPixel(uint32 x, uint32 y,  uint8 r, uint8 g, uint8 b)=0;
    virtual void drawRectangle(uint32 x, uint32 y, uint32 w, uint32 h, uint8 r, uint8 g, uint8 b)=0;
};

#endif