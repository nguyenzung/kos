#ifndef WINDOW_H
#define WINDOW_H

#include <kernel/widget.h>

namespace ui
{

class Window : public Widget
{
public:
    Window(Widget *parent = 0);
    ~Window();
    
    virtual void render()=0;
};

}

#endif // WINDOW_H
