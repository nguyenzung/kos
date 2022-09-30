
#include <kernel/kernel.h>
#include <kernel/printer.h>

int main() {
    kernel::Kernel kernel;
    kernel.initialize();
    kernel::Kernel::start(1, 0);    
}