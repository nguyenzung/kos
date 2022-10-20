#include <kernel/pic.h>
#include <kernel/iocommand.h>
#include <kernel/type.h>

using namespace kernel;

#define PIC1                0x20		/* IO base address for master PIC */
#define PIC2                0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND        PIC1
#define PIC1_DATA           (PIC1+1)
#define PIC2_COMMAND        PIC2
#define PIC2_DATA           (PIC2+1)

#define ICW1_ICW4           0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE         0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4      0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL          0x08		/* Level triggered (edge) mode */
#define ICW1_INIT           0x10		/* Initialization - required! */
 
#define ICW4_8086           0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO           0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE      0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER     0x0C		/* Buffered mode/master */
#define ICW4_SFNM           0x10		/* Special fully nested (not) */

PIC::PIC()
{
    
}

PIC::~PIC()
{
    
}

void PIC::enable()
{
    remap();
}

void PIC::disable()
{
    outb(PIC2_DATA, 0xff);
    outb(PIC1_DATA, 0xff);
}

void PIC::remap()
{
    uint8 a1, a2;
 
	a1 = inb(PIC1_DATA);                            // save masks
	a2 = inb(PIC2_DATA);
 
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);      // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, 0x0 + OFFSET);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, 0x8 + OFFSET);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 4);                            // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_DATA, 2);                            // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
    
    outb(PIC1_DATA, a1);                            // restore saved masks.
    outb(PIC2_DATA, a2);
}

void PIC::setMask(uint8 irq)
{
    uint16 port;
    uint8 value;
     
    if(irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    value = inb(port) | (1 << irq);
    outb(port, value); 
}

void PIC::clearMask(uint8 irq)
{
    uint16 port;
    uint8 value;
 
    if(irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    value = inb(port) & ~(1 << irq);
    outb(port, value);
}

void PIC::eoi(uint8 vector)
{
    if (vector - OFFSET <= 8)
    {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
}