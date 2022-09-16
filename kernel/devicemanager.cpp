#include <kernel/devicemanager.h>
#include <kernel/printer.h>
#include <kernel/iocommand.h>

using namespace kernel;

DeviceManager::DeviceManager() {
    this->initialize();
}

DeviceManager::~DeviceManager() {
    
}

void DeviceManager::initialize() {
    keyboard.active();
    timer.active();
    this->registerDevice(&timer);
    this->registerDevice(&keyboard);
    
}

void DeviceManager::registerDevice(BaseDriver *driver) {
    this->drivers[driver->getVector()] = driver;
}

void DeviceManager::handleInterrupt(uint8 vector) {
    this->drivers[vector]->handleInterrupt();
}