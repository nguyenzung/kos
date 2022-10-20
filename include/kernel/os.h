#ifndef OS_H
#define OS_H

#include <kernel/kernel.h>
#include <driver/keyboard.h>
#include <driver/mouse.h>

class OS
{
public:
    Kernel kernel;
    
    driver::Keyboard keyboard;
    driver::Mouse mouse;
    
    OS();
    ~OS();
    
    void initialize();
    void setupHardware();
    void startOS();
};

#endif // OS_H
