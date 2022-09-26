#include <kernel/devicemanager.h>
#include <kernel/printer.h>
#include <kernel/iocommand.h>

#include <kernel/kernel.h>

using namespace kernel;

DeviceManager::DeviceManager() {
    this->initialize();
}

DeviceManager::~DeviceManager() {
    
}

void DeviceManager::initialize() {
    keyboard.active();
    timer.active();
    mouse.active();
    this->registerInterrupt(&timer);
    this->registerInterrupt(&keyboard);
    this->registerInterrupt(&mouse);
}

void DeviceManager::registerInterrupt(InterruptHandler *handler) {
    Kernel::getInstance()->getInterruptManager()->registerInterrupt(handler);
}
