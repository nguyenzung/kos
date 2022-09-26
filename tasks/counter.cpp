#include <tasks/counter.h>
#include <kernel/printer.h>
#include <kernel/type.h>
#include <stdlib/lock.h>

int counter(int argc, char** argv)
{
        // printf(" count ");

    while (true)
    {
        for(int i = 0; i < 20000; i++)
        {
            for(int j = 0; j < 10000; j++)
            {
            }
        }
        kernel::Printer::println("Count", 5);
    }
    return 0;
}

int ask(int argc, char** argv)
{
    // asm("sti");
        // printf(" ask ");
    while (true)
    {
        for(int i = 0; i < 20000; i++)
        {
            for(int j = 0; j < 10000; j++)
            {
            }
        }
        kernel::Printer::println(" Ask ", 5);
    }
    return 0;
}