#ifndef INTERRUPT_MANAGER
#define INTERRUPT_MANAGER

#include <kernel/pic.h>
#include <kernel/apic.h>
#include <kernel/utils.h>
#include <kernel/type.h>
#include <driver/keyboard.h>

namespace kernel 
{
typedef struct GateEntry
{
	uint16    isr_low;      
	uint16    kernel_cs;    
	uint8	  ist;          
	uint8     attributes;   
	uint16    isr_mid;      
	uint32    isr_high;    
	uint32    reserved;
} __attribute__((packed)) GateEntry;

typedef struct ExceptionStackFrame {
    uint64 rip;
    uint64 cs;
    uint64 flags;
    uint64 rsp;
    uint64 ss;
} __attribute__((packed)) ExceptionStackFrame;

typedef struct 
{
	uint16	limit;
	uint64	base;
} __attribute__((packed)) IDTR;

class InterruptManager 
{
protected:
    GateEntry idt[256];
	IDTR idtr;
    PIC pic;
    APIC *apic;
    bool isLegacy;
	// Keyboard keyboard;

public:
    InterruptManager();
    ~InterruptManager();

	// static InterruptManager* instance;
	// static void setInstance(InterruptManager *instance);
	// static InterruptManager* getInstance();

	DEF_MODULE_INSTANCE(InterruptManager)

    void initialize();
	void* getIDTAddress();

	void handleInterrupt(uint64 vector);
    
    void enableAPIC();

protected:
	void setupIDT();
	void setGateEntry(uint8 vector, void* irs, uint8 flags);

};

}

#endif