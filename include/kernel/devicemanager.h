#ifndef DEVICE_MANAGER
#define DEVICE_MANAGER

#include <kernel/interrupthandler.h>
#include <kernel/type.h>


namespace kernel 
{

class DeviceManager 
{
protected:
    InterruptHandler* handlers[256];
    
public:

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
