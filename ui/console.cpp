#include <ui/console.h>
#include <driver/serial.h>

using namespace ui;

Console::Console(Widget *parent)
    :Window(parent), color(0x0000ff), direction(3)
{

}

Console::~Console()
{
    
}

void Console::setDirection(int direction)
{
    this->direction = direction;
}

void Console::setColor(uint32 color)
{
    this->color = color;
}

void Console::render()
{
    if (x + width + direction < parent->getWidth() && x + direction >= 0)
        x += direction;
    else {
        direction = -direction;
    }
    rectangle(0, 0, width, height, color);
}

