#include <driver/serial.h>
#include <kernel/interruptmanager.h>
#include <kernel/printer.h>
#include <kernel/iocommand.h>
#include <stdlib/string.h>

#define PORT 0x3f8


using namespace driver;


bool SERIAL::isBufferNull() {
   return inb(PORT + 5) & 0x20;
}

void SERIAL::send(char a) {
//   while (!isBufferNull()){}
   int i;
   for(i = 0; i < 128 && !isBufferNull(); i++){}
      outb(PORT,a);
}

void SERIAL::printSerial(char *msg){
    while (*msg != '\0'){
      send(*msg);
      msg++;
    }
}

void SERIAL::println()
{
    send('\0');
}

void SERIAL::printNumber(uint64 number)
{
    char message[12];
    std::memset(message, ' ', 11);
    printSerial(Utils::convertIntToDecString(number, message, 11));
}

IMPL_MODULE_INSTANCE(SERIAL)

SERIAL::SERIAL(){
    SERIAL::instance = this;
}

SERIAL::~SERIAL() {

}

void SERIAL::active() {
   outb(PORT + 1, 0x00);    // Disable all interrupts                                                                                                 
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)                                                                                    
   outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud                                                                                  
   outb(PORT + 1, 0x00);    //                  (hi byte)                                                                                             
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit                                                                                        
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold                                                                        
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set                      
}

void SERIAL::deactive() {

}

void SERIAL::handleInterrupt() {
}

