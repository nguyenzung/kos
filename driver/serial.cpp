#include <driver/serial.h>
#include <kernel/interruptmanager.h>
#include <kernel/printer.h>
#include <kernel/iocommand.h>


#define port 0x3f8


using namespace driver;

void SERIAL::KhoiTaoSerial(){

   outb(port + 1, 0x00);    // Disable all interrupts                                                                                                 
   outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)                                                                                    
   outb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud                                                                                  
   outb(port + 1, 0x00);    //                  (hi byte)                                                                                             
   outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit                                                                                        
   outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold                                                                        
   outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set                                                                                              
   //   outb(port + 4, 0x1E);    // Set in loopback mode, test the serial chip                                                                        
   //   outb(port + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)                                           


}

bool SERIAL::buffer_gui_di_co_null_ko() {
   return inb(port + 5) & 0x20;
}

void SERIAL::gui_di(char a) {
   while (buffer_gui_di_co_null_ko() == 0){}

   outb(port,a);
}

void SERIAL::printSerial(char *msg){
    while (*msg != '\0'){
      SERIAL::gui_di(*msg);
        msg++;
    }
}

SERIAL::SERIAL(){

}

SERIAL::~SERIAL() {

}

void SERIAL::active() {

  KhoiTaoSerial();
}

void SERIAL::deactive() {

}

void SERIAL::handleInterrupt() {
}

