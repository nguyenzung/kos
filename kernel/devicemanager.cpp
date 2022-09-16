#include "devicemanager.h"
#include "printer.h"


DeviceManager::DeviceManager() {
    this->initialize();
}

DeviceManager::~DeviceManager() {
    
}

void DeviceManager::initialize() {

}

void DeviceManager::registerDevice(BaseDriver *driver) {

}

void DeviceManager::handleInterrupt(uint8 vector) {
    Printer::printlnNumber(vector);
}