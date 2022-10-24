#ifndef CONSOLE_H
#define CONSOLE_H

#include <ui/window.h>

namespace ui 
{

class Console : public Window
{
 protected:
    uint32 color;
    int direction;
    
 public:
    Console(Widget *parent = 0);
    ~Console();
    
    void setDirection(int direction);
    void setColor(uint32 color);
    virtual void render();
    
};

}

#endif // CONSOLE_H
