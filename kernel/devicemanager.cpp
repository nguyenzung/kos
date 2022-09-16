#include <kernel/devicemanager.h>
#include <kernel/printer.h>

using namespace kernel;

DeviceManager::DeviceManager() {
    this->initialize();
}

DeviceManager::~DeviceManager() {
    
}

void DeviceManager::initialize() {
    keyboard.active();
    this->registerDevice(&keyboard);
}

void DeviceManager::registerDevice(BaseDriver *driver) {
    this->drivers[driver->getVector()] = driver;
}

void DeviceManager::handleInterrupt(uint8 vector) {
    // Printer::printlnNumber(vector);
    this->drivers[vector]->handleInterrupt();
}