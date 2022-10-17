#include <kernel/devicemanager.h>
#include <kernel/printer.h>
#include <kernel/iocommand.h>

using namespace kernel;

DeviceManager::DeviceManager() {
}

DeviceManager::~DeviceManager() {
    
}

void DeviceManager::initialize() {

}

void DeviceManager::registerDevice(InterruptHandler *handler) {
    handlers[handler->getVector()] = handler;
}

void DeviceManager::handleInterrupt(uint8 vector) {
    handlers[vector]->handleInterrupt();
}