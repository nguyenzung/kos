#include "type.h"
#include "printer.h"
#include "interruptmanager.h"
#include "utils.h"
// #include "driver/vga.h"
#include "memorymanager.h"

int main() {
    // Printer::printlnNumber(12);
    InterruptManager interruptManager;
    interruptManager.setup();


    MemoryManager memoryManager;
    // Printer::printlnAddress((uint64)&memoryManager);

    void *p1 = memoryManager.malloc(0xffff);
    void *p2 = memoryManager.malloc(12);
    void *p3 = memoryManager.malloc(20);
    void *p4 = memoryManager.malloc(40);

    Printer::printlnAddress((uint64)p1);
    Printer::printlnAddress((uint64)p2);
    Printer::printlnAddress((uint64)p3);
    Printer::printlnAddress((uint64)p4);
    
    // VGA vga;
    // vga.setupVideoMode();
    // vga.drawRectangle(0,0, 320, 200, VGAColor::YELLOW);
    asm ("_cpp_stop:; hlt; jmp _cpp_stop;");
    return 0;
}