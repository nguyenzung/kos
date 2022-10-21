#include <driver/vga.h>
#include <kernel/iocommand.h>
#include <kernel/printer.h>

#define VGA_MISC            0x3c2
#define VGA_CRTC_INDEX      0x3d4
#define VGA_CRTC_DATA       0x3d5
#define VGA_SEQ_INDEX       0x3c4
#define VGA_SEQ_DATA        0x3c5
#define VGA_GC_INDEX 		0x3CE
#define VGA_GC_DATA 		0x3CF 

#define	VGA_INSTAT_READ		0x3DA
#define	VGA_AC_INDEX		0x3C0
#define	VGA_AC_WRITE		0x3C0


using namespace kernel;
using namespace driver;

IMPL_MODULE_INSTANCE(VGA)


VGA::VGA()
    :BaseGraphicsDevice()
{
    VGA::setInstance(this);
}

void VGA::active()
{

}

void VGA::deactive()
{

}

void VGA::handleInterrupt()
{
    
}
            
void VGA::setupVideoMode()
{
    uint8 g_320x200x256[]=
    {
        /* MISC */
            0x63,
        /* SEQ */
            0x03, 0x01, 0x0F, 0x00, 0x0E,
        /* CRTC */
            0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
            0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
            0xFF,
        /* GC */
            0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
            0xFF,
        /* AC */
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
            0x41, 0x00, 0x0F, 0x00, 0x00
    };
    //  misc
    uint8 *data = g_320x200x256;
    outb(VGA_MISC, *(data++)) ;
    // data++;
    
    // sequencer
    for(uint8 i = 0; i < 5; i++)
    {
        outb(VGA_SEQ_INDEX, i);
        outb(VGA_SEQ_DATA, *(data++));
        // data++;
    }
    
    // cathode ray tube controller
    outb(VGA_CRTC_INDEX, 0x03);
    outb(VGA_CRTC_DATA, inb(VGA_CRTC_DATA) | 0x80);
    outb(VGA_CRTC_INDEX, 0x11);
    outb(VGA_CRTC_DATA, inb(VGA_CRTC_DATA) & ~0x80);
    
    data[0x03] = data[0x03] | 0x80;
    data[0x11] = data[0x11] & ~0x80;
    
    for(uint8 i = 0; i < 25; i++)
    {
        outb(VGA_CRTC_INDEX, i);
        outb(VGA_CRTC_DATA, *(data++));
        // data++;
    }
    
    // graphics controller
    for(uint8 i = 0; i < 9; i++)
    {
        outb(VGA_GC_INDEX, i);
        outb(VGA_GC_DATA, *(data++));
        // data++;
    }
    
    // attribute controller
    for(uint8 i = 0; i < 21; i++)
    {
        inb(VGA_INSTAT_READ);
        outb(VGA_AC_INDEX, i);
        outb(VGA_AC_WRITE, *(data++));
        // data++;
    }
    inb(VGA_INSTAT_READ);
    outb(VGA_AC_INDEX, 0x20);    
}


uint8* VGA::getFrameSegment()
{
    outb(VGA_GC_INDEX, 0x06);
    uint8 segmentNumber = inb(VGA_GC_DATA) & (3<<2);
    switch(segmentNumber)
    {
        default:
        case 0<<2: return (uint8*)0x00000;
        case 1<<2: return (uint8*)0xA0000;
        case 2<<2: return (uint8*)0xB0000;
        case 3<<2: return (uint8*)0xB8000;
    }
}

VGAColor VGA::getColorIndex(uint8 r, uint8 g, uint8 b)
{
    uint32 color = r << 16 | g << 8 | b;
    switch (color)
    {
    case 0x000000:
        return VGAColor::BLACK;
    case 0x0000ff:
        return VGAColor::BLUE;
    case 0x00ff00:
        return VGAColor::GREEN;
    case 0x00ffff:
        return VGAColor::CYAN;
    case 0xff0000:
        return VGAColor::RED;
    case 0xff00ff:
        return VGAColor::MAGENTA;
    case 0x964B00:
        return VGAColor::BROWN;
    case 0xffffff:
        return VGAColor::WHITE;
    case 0x808080:
        return VGAColor::GRAY;
    case 0x000080:
        return VGAColor::LIGHT_BLUE;
    case 0x008000:
        return VGAColor::LIGHT_GREEN;
    case 0x008080:
        return VGAColor::LIGHT_CYAN;
    case 0x800000:
        return VGAColor::LIGHT_RED;
    case 0x800080:
        return VGAColor::LIGHT_MAGENTA;
    case 0xffff00:
        return VGAColor::YELLOW;
    case 0xa8a8a8:
        return VGAColor::BRIGHT_WHITE;
    default:
        break; VGAColor::WHITE;
    }
}

void VGA::drawPixel(uint16 x, uint16 y,  VGAColor colorIndex)
{
    if(x < 0 || 320 <= x
    || y < 0 || 200 <= y)
        return;
        
    uint8* pixelAddress = getFrameSegment() + 320*y + x;
    *pixelAddress = colorIndex;
}
           
void VGA::drawPixel(uint16 x, uint16 y,  uint8 r, uint8 g, uint8 b)
{
    drawPixel(x,y, getColorIndex(r,g,b));
}

void VGA::drawRectangle(uint16 x, uint16 y, uint16 w, uint16 h, VGAColor color)
{
    for(uint32 Y = y; Y < y + h; Y++)
        for(uint32 X = x; X < x + w; X++)
            drawPixel(X, Y, color);
}

void VGA::drawRectangle(uint16 x, uint16 y, uint16 w, uint16 h, uint8 r, uint8 g, uint8 b)
{
    for(uint32 Y = y; Y < y + h; Y++)
        for(uint32 X = x; X < x + w; X++)
            drawPixel(X, Y, r, g, b);
}

