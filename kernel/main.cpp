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

    // VGA vga;
    // vga.setupVideoMode();
    // vga.drawRectangle(0,0, 320, 200, VGAColor::YELLOW);
    asm ("_cpp_stop:; hlt; jmp _cpp_stop;");
    return 0;
}