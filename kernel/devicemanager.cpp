#include <kernel/devicemanager.h>
#include <kernel/printer.h>
#include <kernel/iocommand.h>

using namespace kernel;

DeviceManager::DeviceManager() {
    initialize();
}

DeviceManager::~DeviceManager() {
    
}

void DeviceManager::initialize() {
    keyboard.active();
    // timer.active();
    mouse.active();
    // this->registerDevice(&timer);
    registerDevice(&keyboard);
    registerDevice(&mouse);
}

void DeviceManager::registerDevice(InterruptHandler *handler) {
    handlers[handler->getVector()] = handler;
}

void DeviceManager::handleInterrupt(uint8 vector) {
    handlers[vector]->handleInterrupt();
}