
#include <kernel/kernel.h>

int main() {
    kernel::Kernel kernel;
    kernel.initialize();
    kernel.start();
    kernel::Kernel::hlt(1, 0);    
}