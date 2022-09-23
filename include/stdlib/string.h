#ifndef STRING
#define STRING

#include <kernel/type.h>

using namespace kernel;

void* memmove(void* des, void* src, size_t size);
void* memset(void* des, uint8 c, size_t size);


#endif