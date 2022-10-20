#include <driver/vesa.h>

using namespace driver;

IMPL_MODULE_INSTANCE(VESA)

VESA::VESA(void *frameBufferInfo)
{
    VESA::instance = this;
    
}

void VESA::setupVideoMode()
{
    
}

void VESA::drawPixel(uint32 x, uint32 y, uint8 r, uint8 g, uint8 b)
{
    
}

void VESA::drawRectangle(uint32 x, uint32 y, uint32 w, uint32 h, uint8 r, uint8 g, uint8 b)
{
    
}

