#include <kernel/printer.h>
#define CHECK(EXPR) printf("\n%s " #EXPR, EXPR ? "ok" : "nok")

#include <test/testqueue.h>
#include <test/teststack.h>

void test()
{
    testQueue();
    testStack();
}
