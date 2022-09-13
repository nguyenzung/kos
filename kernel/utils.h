#ifndef UTILS
#define UTILS

#include "type.h"

#define ASM_CMD(reg) "movq %%" #reg ", %0;" 
#define READ_CPU(reg, variable) asm (ASM_CMD(reg) :"=m"(variable)::);   

class Utils{
public:
    static char* convertIntToHexString(uint64 value, char* message, uint8 len);
    static uint8 length(char *string);
};


#endif