#ifndef DEVICE_MANAGER
#define DEVICE_MANAGER

#include <kernel/interrupthandler.h>
#include <kernel/type.h>
#include <driver/keyboard.h>
#include <driver/timer.h>

namespace kernel {

class DeviceManager {
protected:
    InterruptHandler* handlers[256];
    driver::Keyboard keyboard;
    driver::Timer timer;
public:
    DeviceManager();
    ~DeviceManager();

    void initialize();

public:
    void registerDevice(InterruptHandler *handler);
    void handleInterrupt(uint8 vector);
};

}

#endif