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
    int i, j, k;
    printf("\n [Count] %d %s %p", argc, argv[0], &i);
    for (i = 0; i <= argc; i++)
    {
        for (j = 0; j < 200; j++)
            for (k = 0; k < 3000; k++)
            {}
//        printf(" Count ");
        result += i;
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
        for (j = 0; j < 200; j++)
            for (k = 0; k < 3000; k++)
            {}
//        printf("  Ask  ");
        result += i;
    }
    return result;
}

int TaskTest::processOne(int argc, char** argv)
{
    uint64 result = 0;
    int i, j, k;
    printf("\n [P1] %d %s %p", argc, argv[0], &i);
    for (i = 0; i <= argc; i++)
    {
        for (j = 0; j < 20000; j++)
            for (k = 0; k < 3000; k++)
            {}
        printf("  P_1  ");
        result += i;
    }
    return result;
}

int TaskTest::processTwo(int argc, char** argv)
{
    uint64 result = 0;
    int i, j, k;
    printf("\n [P2] %d %s %p", argc, argv[0], &i);
    for (i = 0; i <= argc; i++)
    {
        for (j = 0; j < 20000; j++)
            for (k = 0; k < 3000; k++)
            {}
        printf("  P_2  ");
        result += i;
    }
    return result;
}
