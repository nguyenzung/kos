#include <kernel/utils.h>

using namespace kernel;

char* Utils::convertIntToHexString(uint64 value, char* message, uint8 len){
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
    message[len-1]=48;
    return message;
}

char* Utils::convertIntToDecString(uint64 value, char* message, uint8 len){
    while (value > 0) {
        uint8 r = value % 10;
        value = value / 10;
        message[len-1] = (r + 48);
        len--;
    }
    message[len-1]=48;
    return message;
}

uint8 Utils::length(char *string) {
    if (!string) {
        return 0;
    } else {
        uint32 len = 0;
        while (*string != '\n') {
            len++;
            ++string;
        }
        return len + 1;
    }
}