#include <tasks/counter.h>
#include <kernel/printer.h>

int counter(int argc, char** argv)
{
    while (true)
    {
        for (int i = 0; i < 2000; i++)
        {
            for(int j = 0; j < 2000; j++)
            {

            }
        }
        
        kernel::Printer::print(" Counter ", 9);
        kernel::Printer::printNumber(argc);
        // asm("hlt");
    }
    return 0;
}