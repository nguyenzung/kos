#ifndef VGA_H
#define VGA_H

#include <kernel/basegraphicsdevice.h>
#include <kernel/type.h>
#include <kernel/utils.h>

namespace driver
{

typedef enum VGAColor {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    WHITE,
    GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    BRIGHT_WHITE
} VGAColor;


class VGA: public BaseGraphicsDevice
{
protected:
    uint8* getFrameSegment();        
    VGAColor getColorIndex(uint8 r, uint8 g, uint8 b);
    DEF_MODULE_INSTANCE(VGA)
public:
    VGA();

    void active();
    void deactive();
    void handleInterrupt();

    void setupVideoMode() override;
    void drawPixel(uint16 x, uint16 y, VGAColor colorIndex);
    void drawPixel(uint16 x, uint16 y,  uint8 r, uint8 g, uint8 b) override;
    void drawRectangle(uint16 x, uint16 y, uint16 w, uint16 h, VGAColor color);
    void drawRectangle(uint16 x, uint16 y, uint16 w, uint16 h, uint8 r, uint8 g, uint8 b) override;

};
 
}

#endif