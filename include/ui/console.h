#ifndef CONSOLE_H
#define CONSOLE_H

#include <ui/window.h>

namespace ui 
{

class Console : public Window
{
 public:
    Console(Widget *parent = 0);
    ~Console();
    
    virtual void render();
    
};

}

#endif // CONSOLE_H
