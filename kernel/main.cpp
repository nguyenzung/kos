
#include <kernel/os.h>
#include <kernel/printer.h>

int main() {
    OS os;
    os.setupHardware();
    os.initialize();
    os.startOS();
}