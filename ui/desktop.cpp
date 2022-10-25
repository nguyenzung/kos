#include <ui/desktop.h>
#include <ui/console.h>
#include <ui/label.h>

using namespace ui;

Desktop::Desktop(Widget *parent)
    : Window(parent)
{
//    Console *console0 = new Console(this);
//    console0->setSize(480, 320);
//    console0->setPosition(30, 500);
//    console0->setColor(0xffff00);
    
    console = new Console(this);
    console->setSize(960, 640);
    console->setPosition(10, 65);

    
    Console *console1 = new Console(console);
    console1->setSize(480, 320);
    console1->setPosition(60, -20);
    console1->setDirection(-2);
    console1->setColor(0xff0000);
    
    Console *console2 = new Console(console);
    console2->setSize(640, 480);
    console2->setPosition(60, 360);
    console2->setDirection(-3);
    console2->setColor(0xffff00);
    console2->setIsWrapped(false);
    
    Console *console22 = new Console(console2);
    console22->setSize(480, 320);
    console22->setPosition(100, -120);
    console22->setDirection(3);
    console22->setColor(0x00ffff);

	Label *label = new Label(console22, "hello");
	label->setColor(0x00ff00);
}

Desktop::~Desktop()
{
    
}

void Desktop::render()
{
    rectangle(0, 0, width, height, 0x0000ff00);
}
