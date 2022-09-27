#include <tasks/counter.h>
#include <kernel/printer.h>
#include <kernel/type.h>
#include <kernel/utils.h>
#include <stdlib/lock.h>

using namespace kernel;

int TaskTest::count(int argc, char** argv)
{
    int i, j, k;
    uint64 rsp, rbp;
    READ_CPU(RSP, rsp);
    printf(" count %d %s %p %p", argc, argv[0], &i, rsp);
    for (i = 0; i < 6000; i++)
    {
        for (j = 0; j < 1000; j++)
            for (k = 0; k < 30; k++)
            {}
        READ_CPU(RSP, rsp);
        READ_CPU(RBP, rbp);
        printf("[count %d %p %p %p] \n", i, &i, rsp, rbp);

    }

    // while (true)
    // {
    //     printf(" Count ");
    // }
    

    printf("\n[End count]\n");
    return 0;
}

int TaskTest::ask(int argc, char** argv)
{
    int i, j, k;
    uint64 rsp, rbp;
    READ_CPU(RSP, rsp);
    printf(" ask %d %s %p %p", argc, argv[0], &i, rsp);
    
    for (i = 0; i < 6000; i++)
    {
        for (j = 0; j < 1000; j++)
            for (k = 0; k < 30; k++)
            {}
        READ_CPU(RSP, rsp);
        READ_CPU(RBP, rbp);
        printf("[ask %d %p %p %p] \n", i, &i, rsp, rbp);
    }
    // while (true)
    // {
    //     printf(" Ask ");
    // }
    printf("\n [End ask] \n");
    return 1;
}