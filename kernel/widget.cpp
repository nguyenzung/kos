#include <kernel/widget.h>
#include <kernel/graphicsserver.h>
#include <driver/serial.h>

using namespace kernel;



//Widget::Widget(Widget *parent)
//    :parent(parent)
//{
//    if (parent)
//        parent->addChild(this);
//}

Widget::Widget(Widget *parent, uint16 z)
    :parent(parent), isWrapped(true)
{
    if (parent)
        parent->addChild(this, z);
}

Widget::Widget(int16 x, int16 y, uint16 w, uint16 h, Widget *parent)
    :x(x), y(y),width(w), height(h), parent(parent), isWrapped(true)
{
    if (parent)
        parent->addChild(this);
}

Widget::~Widget()
{
    
}

void Widget::setSize(uint16 w, uint16 h)
{
    this->width = w;
    this->height = h;
}

void Widget::setPosition(int16 x, int16 y)
{
    this->x = x;
    this->y = y;
}

void Widget::setIsWrapped(bool isWrapped)
{
    this->isWrapped = isWrapped;
}

void Widget::osUpdate()
{
    this->render();
    childs.inorderProcess([this](Widget *widget){
        widget->osUpdate();
    });   
}

void Widget::render()
{
    
}

uint32 Widget::getX()
{
    return x;
}

uint32 Widget::getY()
{
    return y;
}

uint32 Widget::getZ()
{
    return z;
}

uint32 Widget::getWidth()
{
    return width;
}

uint32 Widget::getHeight()
{
    return height;
}

void Widget::updateZ(uint16 z)
{
    this->z = z;
    if (parent)
    {
        parent->updateZOfChild(this, z);
    }
}

void Widget::updateZOfChild(Widget *child, uint16 z)
{
    uint32 newZIndex = calculateZ(z);
    uint32 oldZIndex = mapper[child].second;
    mapper[child] = newZIndex;
    childs.earse(oldZIndex);
    childs.put(newZIndex, child);
}

uint32 Widget::calculateZ(uint16 z)
{
    uint32 total = childs.size();
    uint32 z_ = (z << 16) | total;
    return z_;
}

void Widget::addChild(Widget *child, uint16 z)
{
    uint32 zIndex = calculateZ(z);
    mapper[child] = zIndex;
    childs.put(zIndex, child);
    child->z = z;
}

void Widget::rectangle(int16 x, int16 y, uint16 w, uint16 h, uint8 r, uint8 g, uint8 b)
{
    
    if (isWrapped)
    {
        int16 xTopLeft = x;
        int16 yTopLeft = y;
        uint16 xBottomRight = x + w;
        uint16 yBottomRight = y + h;
        
        if (xTopLeft < 0)
            xTopLeft = 0;
        if (yTopLeft < 0)
            yTopLeft = 0;
        if (xBottomRight > width)
            xBottomRight = width;
        if (yBottomRight > height)
            yBottomRight = height;
        x = xTopLeft;
        y = yTopLeft;
        w = xBottomRight - xTopLeft;
        h = yBottomRight - yTopLeft;
        
    }else{
        driver::SERIAL::getInstance()->printSerial("\n is wrapped = false ");
        driver::SERIAL::getInstance()->printNumber(x);
        driver::SERIAL::getInstance()->printSerial(" ");
        driver::SERIAL::getInstance()->printNumber(y);
        driver::SERIAL::getInstance()->printSerial(" ");
        driver::SERIAL::getInstance()->printNumber(w);
        driver::SERIAL::getInstance()->printSerial(" ");
        driver::SERIAL::getInstance()->printNumber(h);
    }
    if (parent)
    {
        parent->rectangle(x + this->x, y + this->y, w, h, r, g, b);
    }else
    {
        GraphicsServer::getInstance()->drawRectangle(x, y, w, h, r, g, b);
    }
}

void Widget::rectangle(int16 x, int16 y, uint16 w, uint16 h, uint32 color)
{
    this->rectangle(x, y, w, h, (color >> 16) & 0xff, (color >> 8) & 0xff, (color >> 0) & 0xff);
}


