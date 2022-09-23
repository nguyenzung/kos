#include <tasks/counter.h>
#include <kernel/printer.h>
#include <kernel/type.h>

kernel::uint64 k;

int counter(int argc, char** argv)
{
    asm("sti");
    while (true)
    {
        k++;
    }
    return 0;
}

int ask(int argc, char** argv)
{
    asm("sti");
    while (true)
    {
        k--;       
    }
    return 0;
}