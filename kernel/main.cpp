
#include <kernel/os.h>
#include <kernel/printer.h>

int main() {
    OS os;
    os.initialize();
    os.setupHardware();
    
    os.startOS();
}