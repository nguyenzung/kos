#include <ui/console.h>
#include <driver/serial.h>

using namespace ui;

Console::Console(Widget *parent)
    :Window(parent)
{
    x = 20;
    y = 20;
}

Console::~Console()
{
    
}

void Console::render()
{
    static int direction = 5;
    if (x + width + direction < parent->getWidth() - 5 && x + direction >= 5)
        x += direction;
    else {
        direction = -direction;
    }
    rectangle(0, 0, width, height, 0x0000ff);
}

