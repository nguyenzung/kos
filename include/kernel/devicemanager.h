#ifndef DEVICE_MANAGER
#define DEVICE_MANAGER

#include <kernel/interrupthandler.h>
#include <kernel/type.h>
#include <driver/keyboard.h>
#include <driver/timer.h>
#include <driver/mouse.h>

namespace kernel 
{

class DeviceManager 
{
protected:
    driver::Keyboard keyboard;
    driver::Timer timer;
    driver::Mouse mouse;
public:

    DeviceManager();
    ~DeviceManager();

    void initialize();
    void registerInterrupt(InterruptHandler *handler);
};

}

#endif
