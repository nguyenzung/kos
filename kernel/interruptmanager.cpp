#include "interruptmanager.h"
#include "printer.h"
#include "iocommand.h"
#include "utils.h"

#include "kernel.h"

using namespace kernel;

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

#define OFFSET 0x20

extern void* GDT64;
extern void* stackBase;
extern void* heapBase;
extern void* GDTPTR;
extern uint16 GDT64Code;
extern void* isrStubTable[];
extern void *print;

// static void testPageFault() {
//     uint64 a = 12;
//     uint64 m = 0xffffffff;
//     uint64 *p = (uint64*)m;
//     *p = a;
//     Printer::print("Page Fault", 10);
// }

// static void testDivZero() {
//     uint8 a = 12;
//     uint8 b = 4;
//     b = b - 4;
//     uint8 c = a/b;
//     Printer::print("Page Fault", 10);
// }

void PIC_remap()
{
	unsigned char a1, a2;
 
	a1 = IOCommand::inb(PIC1_DATA);                        // save masks
	a2 = IOCommand::inb(PIC2_DATA);
 
	IOCommand::outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	IOCommand::io_wait();
	IOCommand::outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	IOCommand::io_wait();
	IOCommand::outb(PIC1_DATA, 0x0 + OFFSET);                 // ICW2: Master PIC vector offset
	IOCommand::io_wait();
	IOCommand::outb(PIC2_DATA, 0x8 + OFFSET);                 // ICW2: Slave PIC vector offset
	IOCommand::io_wait();
	IOCommand::outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	IOCommand::io_wait();
	IOCommand::outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	IOCommand::io_wait();
 
	IOCommand::outb(PIC1_DATA, ICW4_8086);
	IOCommand::io_wait();
	IOCommand::outb(PIC2_DATA, ICW4_8086);
	IOCommand::io_wait();
 
	IOCommand::outb(PIC1_DATA, a1);
	IOCommand::outb(PIC2_DATA, a2);
}

InterruptManager::InterruptManager() {
    testData=0x123454321;
    InterruptManager::setInstance(this);
}

InterruptManager::~InterruptManager(){

}


IMPLE_MODULE_INSTANCE(InterruptManager)

void InterruptManager::initialize() {
    this->setupIDT();
}

void* InterruptManager::getIDTAddress() {
    return this->idt;
}

void InterruptManager::exceptionHandle(uint64 vector) {
    // // Printer::printlnAddress(testData);
        Kernel::getInstance()->getDeviceManager()->handleInterrupt(vector);

    // Printer::printAddress(vector);
   
}

void InterruptManager::setupIDT() {
    uint64* sp = (uint64*)stackBase;
    idtr.base = (uint64)&idt[0];
    idtr.limit = (uint16)sizeof(GateEntry) * 256 - 1;
 
    for (uint8 vector = OFFSET; vector < 32 + OFFSET; vector++) {
        this->setGateEntry(vector, isrStubTable[vector + 1 - OFFSET], 0x8E);
    }
    PIC_remap();
    
    asm ("lidt %0" : : "m"(idtr));
    // asm("int $10");
    asm ("sti");
    // Printer::println("OK",2);
    // testPageFault();
    // testDivZero();
    // Printer::printAddress(123);
}

void InterruptManager::setGateEntry(uint8 vector, void* isr, uint8 flags) {
    GateEntry* entry    = &idt[vector];
    entry->isr_low      = (uint64)isr & 0xFFFF;
    entry->kernel_cs    = GDT64Code;
    entry->ist          = 0;
    entry->attributes   = flags;
    entry->isr_mid      = ((uint64)isr >> 16) & 0xFFFF;
    entry->isr_high     = ((uint64)isr >> 32) & 0xFFFFFFFF;
    entry->reserved     = 0;
}

