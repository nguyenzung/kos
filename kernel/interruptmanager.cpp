#include <kernel/interruptmanager.h>
#include <kernel/printer.h>
#include <kernel/iocommand.h>
#include <kernel/utils.h>

#include <kernel/kernel.h>

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

extern uint16 GDT64Code;
extern void* isrStubTable[];
extern void* isrTimerHandler;

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
 
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
 
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, 0x0 + OFFSET);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, 0x8 + OFFSET);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
 
	// outb(PIC1_DATA, a1);
	// outb(PIC2_DATA, a2);
}

void IRQ_clear_mask(unsigned char IRQline)
{
    uint16 port;
    uint8 value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}

InterruptManager::InterruptManager()
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
void InterruptManager::exceptionHandle(uint64 vector)
{
    Kernel::getInstance()->getDeviceManager()->handleInterrupt(vector);
    if (vector - OFFSET <= 8)
    {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
    // Printer::printAddress(vector);
   
}

void InterruptManager::setupIDT()
{
    idtr.base = (uint64)&idt[0];
    idtr.limit = (uint16)sizeof(GateEntry) * 256 - 1;
 
    for (uint8 vector = OFFSET; vector < 32 + OFFSET; vector++) {
        this->setGateEntry(vector, isrStubTable[vector + 1 - OFFSET], 0x8E);
    }
    this->setGateEntry(0x20, &isrTimerHandler, 0x8E);
    PIC_remap();
    asm ("lidt %0" : : "m"(idtr));
    // asm("int $10");
    asm ("sti");
    // Printer::println("OK",2);
    // testPageFault();
    // testDivZero();
    // Printer::printAddress(123);
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

