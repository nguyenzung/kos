#include <stdlib/string.h>
#include <kernel/printer.h>

using namespace kernel;

uint64 counter;

namespace std
{

/*
 *  Support move from right to left
 */
void* memmove(void* des, void* src, size_t size)
{    
    if (des < src)
    {   
        uint8 *bdes = (uint8*)des;
        uint8 *bsrc = (uint8*)src;
        for (size_t i = 0; i < size; i++)
            *(bdes++) = *(bsrc++);
    }
    return des;
}

void* memset(void* des, uint8 c, size_t size)
{
    uint8 *bdes = (uint8*)des;
    for(int i = 0; i < size; i++)
        *(bdes++) = c;
    return des;
}

}