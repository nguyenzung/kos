#ifndef DEVICE_MANAGER
#define DEVICE_MANAGER

#include "basedriver.h"
#include "type.h"

class DeviceManager {
protected:

public:
    DeviceManager();
    ~DeviceManager();

    void initialize();

public:
    void registerDevice(BaseDriver *driver);
    void handleInterrupt(uint8 vector);
};

#endif