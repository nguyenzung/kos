#include "utils.h"

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