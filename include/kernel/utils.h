#ifndef UTILS
#define UTILS

#include <kernel/type.h>

namespace kernel
{

#define ASM_CMD(reg) "movq %%" #reg ", %0;" 
#define READ_CPU(reg, variable) asm (ASM_CMD(reg) :"=m"(variable)::);   

#define DEF_MODULE_INSTANCE(ClassName)              \
    public:                                         \
    static ClassName *instance;                     \
    static void setInstance(ClassName *instance);   \
    static ClassName* getInstance();

#define IMPL_MODULE_INSTANCE(ClassName)            \
ClassName* ClassName::instance = nullptr;           \
void ClassName::setInstance(ClassName *instance) {  \
    ClassName::instance = instance;                 \
}                                                   \
ClassName* ClassName::getInstance() {               \
    return ClassName::instance;                     \
}                                                   

class Utils
{
public:
  static void microdelay(int amount);
  static char* convertIntToHexString(uint64 value, char* message, uint8 len);
    static char* convertIntToDecString(uint64 value, char* message, uint8 len);
    static char* convertIntToBinString(uint64 value, char* message, uint8 len);
    static uint8 length(char *string);
};
}

#endif
