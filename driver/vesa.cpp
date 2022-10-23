#include <driver/vesa.h>
#include <kernel/multiboot.h>
#include <driver/serial.h>
#include <stdlib/string.h>

using namespace driver;
using namespace kernel;

IMPL_MODULE_INSTANCE(VESA)

VESA::VESA()
{
    VESA::instance = this;   
}

VESA::~VESA()
{
    
}

void VESA::setupVideoMode()
{
    driver::SERIAL::getInstance()->printSerial("\n VESA Setup Video Mode ");
    Multiboot * multiboot = Multiboot::getInstance();
    MultibootTagFrameBuffer *frameBuffer = multiboot->getFrameBuffer();
    this->frameBuffer = (void*)frameBuffer->address;   // Load memory map
    this->width = 1024;
    this->height = 768;
    this->depth = 3; 
    this->redIndex = 2;
    this->greenIndex = 1;
    this->blueIndex = 0;    
//    this->clearScreen(0x00,0xff,0xff);
}

void VESA::drawPixel(uint16 x, uint16 y, uint8 r, uint8 g, uint8 b)
{
    uint8 *address = (uint8*)(frameBuffer + y * this->width * 3 + x * 3);
    address[this->redIndex] = r;
    address[this->greenIndex] = g;
    address[this->blueIndex] = b;
}

void VESA::drawRectangle(uint16 x, uint16 y, uint16 w, uint16 h, uint8 r, uint8 g, uint8 b)
{
    for (int j = y; j < y + h; ++j)
        for (int i = x; i < x + w; ++i)
            this->drawPixel(i, j, r, g, b);        
}

void VESA::clearScreen(uint8 r, uint8 g, uint8 b)
{
    this->drawRectangle(0, 0, width, height, r, g, b);
}

