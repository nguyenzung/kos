#include <stdlib/string.h>


using namespace kernel;

namespace std
{

/*
 *  Support move from right to left
 */
void* memmove(void* des, void* src, size_t size)
{    
    size_t numq = size >> 3;
    size_t numb = size & 0b111;
    if (des < src)
    {   
        uint64 *qdes = (uint64*)des;
        uint64 *qsrc = (uint64*)src;
        for (size_t i = 0; i < numq; ++i)
        {
            qdes[i] = qsrc[i];
        }
        uint8 *bdes = (uint8*)(des + numq * 8);
        uint8 *bsrc = (uint8*)(src + numq * 8);
        for (size_t i = 0; i < numb; ++i)
        {
            bdes[i] = bsrc[i];
        }
    }
    return des;
}

void* memset(void* des, uint8 c, size_t size)
{
    size_t numq = size >> 3;
    uint16 cw = c;
    cw = (cw << 8) | c;
    uint32 cd = cw;
    cd = (cd << 16) | cw;
    uint64 cq = cd;
    cq = (cq << 32) | cd;
    uint64* qdes = (uint64*) des;
    for (int i = 0; i < numq; i++)
    {
        qdes[i] = cq;
    }
    
    size_t numb = size & 0b111;
    uint8 *bdes = (uint8*)(des + numq * 8);
    for(int i = 0; i < numb; i++)
    {
        bdes[i] = c;
    }
    return 0;
}

}