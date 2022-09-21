#include <tasks/counter.h>
#include <kernel/printer.h>

int counter(int argc, char** argv)
{
    kernel::Printer::println("counter", 7);
    asm("sti");
    while (true)
    {
        for (int i = 0; i < 20000; i++)
        {
            for(int j = 0; j < 5000; j++)
            {

            }
        }
        
        kernel::Printer::print(" Counter ", 9);
        kernel::Printer::printNumber(argc);
        
    }
    return 0;
}

int counter1(int argc, char** argv)
{
    kernel::Printer::println("counter", 7);
    asm("sti");
    while (true)
    {
        for (int i = 0; i < 20000; i++)
        {
            for(int j = 0; j < 5000; j++)
            {

            }
        }
        
        kernel::Printer::print(" Ask ", 6);
        kernel::Printer::printNumber(argc);
        
    }
    return 0;
}