#ifndef GRAPHICSERVER_H
#define GRAPHICSERVER_H

#include <kernel/basegraphicsdevice.h>
#include <kernel/type.h>
#include <kernel/utils.h>
#include <kernel/widget.h>

namespace kernel
{

class GraphicsServer
{
public:
    DECLARE_LOCK(frameBufferLock);
    uint8 *frameBuffer;
    
    uint16 width;
    uint16 height;
    uint8 depth; 
    
    BaseGraphicsDevice *device;
    Widget *widget;
    
    GraphicsServer();
    ~GraphicsServer();
    
    DEF_MODULE_INSTANCE(GraphicsServer)
    
    void initializeDevice(BaseGraphicsDevice *device);
    
    void update();
    
    void setBaseWidget(Widget *widget);
    
    void drawPixel(uint16 x, uint16 y, uint8 r, uint8 g, uint8 b);
    void drawRectangle(uint16 x, uint16 y, uint16 w, uint16 h, uint8 r, uint8 g, uint8 b);
    void clearScreen(uint8 r, uint8 g, uint8 b);
    
    void drawPixel(uint16 x, uint16 y, uint32 color);
    void drawRectangle(uint16 x, uint16 y, uint16 w, uint16 h, uint32 color);

    void drawText(uint16 x, uint16 y, char code, uint32 color);
    void clearScreen(uint32 color);
};

}

#endif // GRAPHICSERVER_H
