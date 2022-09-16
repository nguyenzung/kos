#ifndef DEVICE_MANAGER
#define DEVICE_MANAGER

#include <kernel/basedriver.h>
#include <kernel/type.h>
#include <driver/keyboard.h>
#include <driver/timer.h>

namespace kernel {

class DeviceManager {
protected:
    BaseDriver* drivers[256];
    driver::Keyboard keyboard;
    driver::Timer timer;
public:
    DeviceManager();
    ~DeviceManager();

    void initialize();

public:
    void registerDevice(BaseDriver *driver);
    void handleInterrupt(uint8 vector);
};

}

#endif