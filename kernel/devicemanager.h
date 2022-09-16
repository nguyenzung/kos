#ifndef DEVICE_MANAGER
#define DEVICE_MANAGER

#include "basedriver.h"
#include "type.h"
#include "driver/keyboard.h"


namespace kernel {

class DeviceManager {
protected:
    BaseDriver* drivers[256];
    Keyboard keyboard;
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