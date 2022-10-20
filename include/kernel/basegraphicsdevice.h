#ifndef BASE_GRAPHICS_DEVICE
#define BASE_GRAPHICS_DEVICE

#include <kernel/basedriver.h>
#include <kernel/type.h>

using namespace kernel;

namespace kernel
{

class BaseGraphicsDevice : public BaseDriver {
public:
    uint16  width;
    uint16  height;
    uint8   depth;
    
    BaseGraphicsDevice();
    ~BaseGraphicsDevice();
    
    void active() override;
    void deactive() override;
    
    void handleInterrupt() override;

    virtual void setupVideoMode()=0;
    virtual void drawPixel(uint16 x, uint16 y,  uint8 r, uint8 g, uint8 b)=0;
    virtual void drawRectangle(uint16 x, uint16 y, uint16 w, uint16 h, uint8 r, uint8 g, uint8 b)=0;
    virtual void clearScreen(uint8 r, uint8 g, uint8 b);
};

void drawPixel();

}
#endif