#include <ui/desktop.h>
#include <ui/console.h>

using namespace ui;

Desktop::Desktop(Widget *parent)
    : Window(parent)
{
    console = new Console(this);
    console->setSize(640, 480);
}

Desktop::~Desktop()
{
    
}

void Desktop::render()
{
    rectangle(0, 0, width, height, 0x0000ff00);
}