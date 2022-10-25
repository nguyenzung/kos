#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <kernel/type.h>
#include <stdlib/map.h>
#include <stdlib/unorderedmap.h>

namespace kernel
{
class GraphicsServer;
class Widget
{
private:

protected:
    int16 x, y;
    uint16 z, width, height;   // x, y, z is relative position base on parent widget
    bool isWrapped;
    Widget *parent;
    std::Map<uint32, Widget*> childs;
    std::UnorderedMap<Widget*, uint32> mapper;

public:
//    Widget(Widget *parent = 0);
    Widget(Widget *parent = 0, uint16 z = 0);
    Widget(int16 x, int16 y, uint16 w, uint16 h, Widget *parent = 0);
    ~Widget();
    
    void setSize(uint16 w, uint16 h);
    void setPosition(int16 x, int16 y);
    void setIsWrapped(bool isWrapped);
    
    void addChild(Widget *child, uint16 z = 0);
    void removeChild(Widget *widget);
    
    virtual void render();
//    virtual void update() = 0;
    
    uint32 getX();
    uint32 getY();
    uint32 getZ();
    uint32 getWidth();
    uint32 getHeight();

protected:
    void osUpdate();
    void updateZ(uint16 z);
    void updateZOfChild(Widget *widget, uint16 z);
    uint32 calculateZ(uint16 z);
    void rectangle(int16 x, int16 y, uint16 w, uint16 h, uint8 r, uint8 g, uint8 b);
    void rectangle(int16 x, int16 y, uint16 w, uint16 h, uint32 color);
    void text(int16 x, int16 y, char code, uint32 color);
    
    friend class GraphicsServer;
};

}

#endif // UIWIDGET_H
