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
    uint64 result = 0;
    printf("Size of uint64 %d", sizeof(result));
    int i, j, k;
    printf("\n [Count] %d %s %p", argc, argv[0], &i);

    
    for (i = 0; i <= argc; i++)
    {
        result += (uint64)i;
    }
    return result;
}

int TaskTest::ask(int argc, char** argv)
{
    uint64 result = 0;
    int i, j, k;
    printf("\n [Ask] %d %s %p", argc, argv[0], &i);
    for (i = 0; i <= argc; i++)
    {
        for (j = 0; j < 10; j++)
            for (k = 0; k < 300; k++)
            {}
        result += i;
    }
    return result;
}
