#include <kernel/interruptmanager.h>
#include <kernel/printer.h>
#include <kernel/iocommand.h>
#include <kernel/utils.h>
#include <kernel/taskmanager.h>
#include <kernel/kernel.h>
#include <kernel/apic.h>

using namespace kernel;

extern uint16 GDT64Code;
extern void* isrStubTable[];
extern void* isrTimerHandler;

static void testPageFault() {
    uint64 a = 12;
    uint64 m = 0xffffffff;
    uint64 *p = (uint64*)m;
    *p = a;
    Printer::print("Page Fault", 10);
}

static void testDivZero() {
    uint8 a = 12;
    uint8 b = 4;
    b = b - 4;
    uint8 c = a/b;
    Printer::print("Div Zero", 10);
}

InterruptManager::InterruptManager()
    :isLegacy(true)
{
    InterruptManager::instance = this;
    // Printer::print(" INT ", 5);
    // Printer::printlnAddress(uint64(this));
}

InterruptManager::~InterruptManager()
{

}

IMPL_MODULE_INSTANCE(InterruptManager)

void InterruptManager::initialize()
{
    this->setupIDT();
}

void* InterruptManager::getIDTAddress()
{
    return this->idt;
}

// This function need to be called in Kernel main thread
void InterruptManager::handleInterrupt(uint64 vector)
{
    Kernel::getInstance()->getDeviceManager()->handleInterrupt(vector);
    if(isLegacy)
        pic.eoi(vector);
    else
        apic->finishedINT(vector);
    
}

void InterruptManager::enableAPIC()
{
    isLegacy = false;
    pic.disable();
    apic = loadAPIC();
    apic->enable();
    apic->startTimer();
}

__attribute__((interrupt))
void handleException(ExceptionStackFrame *frame, uint64 errorCode)
{
    printf("\n [CPU Exception] %d %d %d %d %d| %d \n", errorCode, frame->rip, frame->cs, frame->ss, frame->rsp, frame);
    TaskManager::getInstance()->contextInfo();
    while (true)
    {
        /* code */
    }
    outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void InterruptManager::setupIDT()
{
    idtr.base = (uint64)&idt[0];
    idtr.limit = (uint16)sizeof(GateEntry) * 256 - 1;
    
    for (uint8 vector = 0; vector < 32; vector++) {
        this->setGateEntry(vector, (void*)(&handleException), 0x8E);
    }

    for (uint8 vector = OFFSET; vector < 32 + OFFSET; vector++) {
        this->setGateEntry(vector, isrStubTable[vector + 1 - OFFSET], 0x8E);
    }
    this->setGateEntry(0x20, &isrTimerHandler, 0x8E);    
    asm ("lidt %0" : : "m"(idtr));
    pic.enable();   
}

void InterruptManager::setGateEntry(uint8 vector, void* isr, uint8 flags)
{
    GateEntry* entry    = &idt[vector];
    entry->isr_low      = (uint64)isr & 0xFFFF;
    entry->kernel_cs    = GDT64Code;
    entry->ist          = 0;
    entry->attributes   = flags;
    entry->isr_mid      = ((uint64)isr >> 16) & 0xFFFF;
    entry->isr_high     = ((uint64)isr >> 32) & 0xFFFFFFFF;
    entry->reserved     = 0;
}

