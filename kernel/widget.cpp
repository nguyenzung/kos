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
    :parent(parent)
{
    if (parent)
        parent->addChild(this, z);
}

Widget::Widget(uint16 x, uint16 y, uint16 w, uint16 h, Widget *parent)
    :x(x), y(y),width(w), height(h), parent(parent)
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

void Widget::osUpdate()
{
    this->render();
    std::Map<uint32, Widget*>::Iterator it = childs.begin();
    if (it != childs.end())
    {
        Widget *widget = (*it)->second;
        widget->osUpdate();
    }    
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
    driver::SERIAL::getInstance()->printSerial("\n AddChild ");
    uint32 zIndex = calculateZ(z);
    mapper[child] = zIndex;
    childs.put(zIndex, child);
    child->z = z;
}

void Widget::rectangle(uint16 x, uint16 y, uint16 w, uint16 h, uint8 r, uint8 g, uint8 b)
{
    if (x > width || y > height || x + w > width || y + h > height)
    {
        return;
    }
    if (parent)
    {
        parent->rectangle(x + this->x, y + this->y, w, h, r, g, b);
    }else
    {
        GraphicsServer::getInstance()->drawRectangle(x, y, w, h, r, g, b);
    }
}

void Widget::rectangle(uint16 x, uint16 y, uint16 w, uint16 h, uint32 color)
{
    this->rectangle(x, y, w, h, (color >> 16) & 0xff, (color >> 8) & 0xff, (color >> 0) & 0xff);
}


