#include <kernel/kernel.h>
#include <kernel/type.h>
#include <kernel/printer.h>
#include <driver/vga.h>
#include <kernel/utils.h>
#include <kernel/kernelobject.h>
#include <datastructure/list.h>

using namespace kernel;

Kernel* Kernel::instance = 0;

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

    heapMemoryManager.initialize();
    deviceManager.initialize();
    interruptManager.initialize();

    ds::Node *no1 = new ds::Node((kernel::KernelObject*)1);
    ds::Node *no2 = new ds::Node((kernel::KernelObject*)2);
    ds::Node *no3 = new ds::Node((kernel::KernelObject*)3);
    ds::Node *no4 = new ds::Node((kernel::KernelObject*)4);
    ds::Node *no5 = new ds::Node((kernel::KernelObject*)5);

    ds::List list;
    list.addNode(no1);
    list.addNode(no2);
    list.addNode(no3);
    list.addNode(no4);
    list.addNode(no5);

    for(ds::Node *it = list.begin(); it != list.end(); it = list.next())
    {
         Printer::printNumber((uint64)it);
        Printer::println();
    }
    list.removeNodeByAddress(no1);
    delete no1;
    list.addNodeAfter(no5, new ds::Node((kernel::KernelObject*)6));
    // Printer::printlnNumber((uint64)(new ds::Node((kernel::KernelObject*)6)));
    Printer::println();
    
    for(ds::Node *it = list.begin(); it != list.end(); it = list.next())
    {
         Printer::printNumber((uint64)it);
        Printer::println();
    }
   
    // VGA vga;
    // vga.setupVideoMode();
    // vga.drawRectangle(0,0, 320, 200, VGAColor::CYAN);
}

void Kernel::hlt() {
    asm ("_cpp_stop:; hlt; jmp _cpp_stop;");
}

HeapMemoryManager* Kernel::getHeapMemoryManager() {
    return &this->heapMemoryManager;
}

DeviceManager* Kernel::getDeviceManager() {
    return &this->deviceManager;
}
InterruptManager* Kernel::getInterruptManager() {
    return &this->interruptManager;
}
