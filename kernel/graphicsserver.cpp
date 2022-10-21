#include <kernel/graphicsserver.h>
#include <driver/serial.h>

using namespace kernel;

IMPL_MODULE_INSTANCE(GraphicsServer)

GraphicsServer::GraphicsServer()
    :width(0), height(0), depth(0), frameBuffer(0), widget(0)
{
    GraphicsServer::instance = this;
    INIT_LOCK(frameBufferLock);
}

GraphicsServer::~GraphicsServer()
{
    if (this->frameBuffer)
        delete this->frameBuffer;
}

void GraphicsServer::initializeDevice(BaseGraphicsDevice *device)
{
    this->width = device->width;
    this->height = device->height;
    this->depth = device->depth;
    this->frameBuffer = new uint8[this->width * this->height * this->depth];
    this->device = device;
}

void GraphicsServer::update()
{
    // We can just use memmov
    
    if (frameBuffer && widget)
    {
        widget->osUpdate();
        for(uint16 j = 0; j < height; ++j)
        {
            for (uint16 i = 0; i < width; ++i)
            {
                uint8 *data = frameBuffer + (width * j + i) * depth;
                device->drawPixel(i, j, data[0], data[1], data[2]);
            }
        }
    }
}

void GraphicsServer::setBaseWidget(Widget *widget)
{
    this->widget = widget;
    this->widget->setSize(this->width, this->height);
}

void GraphicsServer::drawPixel(uint16 x, uint16 y, uint8 r, uint8 g, uint8 b)
{
    uint8 *address = (uint8*)(frameBuffer + y * width * 3 + x * 3);
    address[0] = r;
    address[1] = g;
    address[2] = b;
}

void GraphicsServer::drawRectangle(uint16 x, uint16 y, uint16 w, uint16 h, uint8 r, uint8 g, uint8 b)
{
    LOCK(frameBufferLock);
    for (int j = y; j < y + h; ++j)
        for (int i = x; i < x + w; ++i)
            drawPixel(i, j, r, g, b);
    UNLOCK(frameBufferLock);
}

void GraphicsServer::clearScreen(uint8 r, uint8 g, uint8 b)
{
    drawRectangle(0, 0, width, height, r, g, b);
}

void GraphicsServer::drawPixel(uint16 x, uint16 y, uint32 color)
{
    uint8 *address = (uint8*)(frameBuffer + y * width * 3 + x * 3);
    address[0] = (color >> 16) & 0xff;
    address[1] = (color >> 8) & 0xff;
    address[2] = (color >> 0) & 0xff;
}

void GraphicsServer::drawRectangle(uint16 x, uint16 y, uint16 w, uint16 h, uint32 color)
{
    LOCK(frameBufferLock);
    for (int j = y; j < y + h; ++j)
        for (int i = x; i < x + w; ++i)
            drawPixel(i, j, (color >> 16) & 0xff, (color >> 8) & 0xff, (color >> 0) & 0xff);
    UNLOCK(frameBufferLock);
}

void GraphicsServer::clearScreen(uint32 color)
{
    drawRectangle(0, 0, width, height, (color >> 16) & 0xff, (color >> 8) & 0xff, (color >> 0) & 0xff);
}
