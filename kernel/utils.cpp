#include <kernel/utils.h>
#include <kernel/iocommand.h>

using namespace kernel;

static void microdelay(int amount) {
    uint64 x = rdtsc() + (uint64) amount * 10000;
    while ((int64) (x - rdtsc()) > 0) {
        asm volatile("pause");
    }
}

char* Utils::convertIntToHexString(uint64 value, char* message, uint8 len)
{
    if (value == 0) 
    {
        message[len-1] = 48;
    }
    while (value > 0) {
        uint8 r = value & 0xf;
        value = value >> 4;
        if(r < 10){
            message[len-1] = (r + 48);
        }else{
            message[len-1] = (r + 55);
        }
        len--;
    }
    // 
    return message;
}

char* Utils::convertIntToDecString(uint64 value, char* message, uint8 len)
{
    if (value == 0) 
    {
        message[len-1] = 48;
    }
    while (value > 0) {
        uint8 r = value % 10;
        value = value / 10;
        message[len-1] = (r + 48);
        len--;
    }
    // message[len-1] = 48;
    return message;
}

char* Utils::convertIntToBinString(uint64 value, char* message, uint8 len)
{
    if (value == 0) 
    {
        message[len-1] = 48;
    }
    while (value > 0) {
        uint8 r = value & 0b1;
        value = value >> 1;
        message[len-1] = (r + 48);
        len--;
    }
    
    // message[len-1] = 48;
    return message;
}

uint8 Utils::length(char *string) {
    if (!string) {
        return 0;
    } else {
        uint32 len = 0;
        while (*string != '\0') {
            len++;
            ++string;
        }
        return len + 1;
    }
}
