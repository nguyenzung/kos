#ifndef INTERRUPT_MANAGER
#define INTERRUPT_MANAGER

#include <kernel/utils.h>
#include <kernel/type.h>
#include <driver/keyboard.h>

namespace kernel {

typedef struct {
	uint16    isr_low;      
	uint16    kernel_cs;    
	uint8	  ist;          
	uint8     attributes;   
	uint16    isr_mid;      
	uint32    isr_high;    
	uint32    reserved;
} __attribute__((packed)) GateEntry;


typedef struct {
	uint16	limit;
	uint64	base;
} __attribute__((packed)) IDTR;

class InterruptManager {
protected:
    GateEntry idt[256];
	IDTR idtr;
	// Keyboard keyboard;
	uint64 testData;
	

public:
    InterruptManager();
    ~InterruptManager();

	// static InterruptManager* instance;
	// static void setInstance(InterruptManager *instance);
	// static InterruptManager* getInstance();

	DEF_MODULE_INSTANCE(InterruptManager)

    void initialize();
	void* getIDTAddress();

	void exceptionHandle(uint64 vector);

protected:
	void setupIDT();
	void setGateEntry(uint8 vector, void* irs, uint8 flags);

};

}

#endif