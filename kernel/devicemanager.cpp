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
    mouse.active();
    this->registerDevice(&timer);
    this->registerDevice(&keyboard);
    this->registerDevice(&mouse);
}

void DeviceManager::registerDevice(InterruptHandler *handler) {
    this->handlers[handler->getVector()] = handler;
}

void DeviceManager::handleInterrupt(uint8 vector) {
    this->handlers[vector]->handleInterrupt();
}