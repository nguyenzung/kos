#include <tasks/counter.h>
#include <kernel/printer.h>
#include <kernel/type.h>
#include <kernel/utils.h>
#include <stdlib/lock.h>
#include <stdlib/string.h>

using namespace kernel;

extern uint64 counter;

int TaskTest::count(int argc, char** argv)
{
    counter = 0;
    int i, j, k;
    printf(" count %d %s %p", argc, argv[0], &i);
    
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10000; j++)
            for (k = 0; k < 3000; k++)
            {}
        printf("[ count %d %p %d] \n", i, &i, counter);
    }
    printf("\n[End count]\n");
    return 0;
}

int TaskTest::ask(int argc, char** argv)
{
    int i, j, k;
    printf(" ask %d %s %p", argc, argv[0], &i);
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10000; j++)
            for (k = 0; k < 3000; k++)
            {}
            printf("[ ask %d %p %d] \n", i, &i, counter);
    }
    printf("\n [End ask] \n");
    return 1;
}