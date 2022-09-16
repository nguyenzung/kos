#include "kernel.h"
#include "type.h"
#include "printer.h"
#include "driver/vga.h"
#include "utils.h"


Kernel* Kernel::instance = nullptr;

Kernel::Kernel() 
{
    Kernel::instance = this;
}

Kernel::~Kernel() 
{

}

Kernel* Kernel::getInstance() {
    return Kernel::instance;
}

void Kernel::startKernel() {
    memoryManager.initialize();
    deviceManager.initialize();
    interruptManager.initialize();

    // VGA vga;
    // vga.setupVideoMode();
    // vga.drawRectangle(0,0, 320, 200, VGAColor::CYAN);
}

void Kernel::hlt() {
    asm ("_cpp_stop:; hlt; jmp _cpp_stop;");
}

MemoryManager* Kernel::getMemoryManager() {
    return &this->memoryManager;
}

DeviceManager* Kernel::getDeviceManager() {
    return &this->deviceManager;
}
InterruptManager* Kernel::getInterruptManager() {
    return &this->interruptManager;
}
