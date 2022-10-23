#ifndef DESKTOP_H
#define DESKTOP_H

#include <ui/window.h>

namespace ui 
{

class Console;
class Desktop: public Window 
{
public:
    Console *console;
    
    Desktop(Widget *parent = 0);
    ~Desktop();
    
    virtual void render();
};

}

#endif // DESKTOP_H
