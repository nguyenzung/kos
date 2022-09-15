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
    Printer::printlnNumber((uint64)&memoryManager);

    int *a = new int[5];
    Printer::printlnNumber((uint64)a);

    int *b = new int[10];
    Printer::printlnNumber((uint64)b);

    delete[] a;

    a = new int[6];
    Printer::printlnNumber((uint64)a);


    // delete a;
    
    // VGA vga;
    // vga.setupVideoMode();
    // vga.drawRectangle(0,0, 320, 200, VGAColor::YELLOW);
    asm ("_cpp_stop:; hlt; jmp _cpp_stop;");
    return 0;
}