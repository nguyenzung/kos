#include "printer.h"
#include "utils.h"

#define ADDRESS_LENGTH 18
#define SCREEN_WITH 80
#define SCREEN_HIEGHT 25

uint8 Printer::x = 0;
uint8 Printer::y = 10;

void Printer::print(char *message, uint8 len) {
    unsigned char *VideoMapAddress = (unsigned char*) 0xb8000 + y * SCREEN_WITH * 2 + x * 2;
    for (int i = 0; i < len; i++) {
        VideoMapAddress[i * 2] = message[i];
        VideoMapAddress[i * 2 + 1] = 0x2f;
    }
    if (x + len > SCREEN_WITH) {
        x = x + len - SCREEN_WITH;
        y++;
    } else {
        x = x + len;
    }
}

void Printer::println(char *message, uint8 len) {
    Printer::print(message, len);
    y++;
    x = 0;
}

void Printer::printAddress(uint64 address) {
    char message[ADDRESS_LENGTH];
    for (int i = 0; i < ADDRESS_LENGTH - 1; i++) {
        message[i] = ' ';
    }
    Utils::convertIntToHexString(address, message, ADDRESS_LENGTH);
    uint8 index = 0;
    for (uint8 i = 0; i < ADDRESS_LENGTH; i++) {
        if (message[i] == ' ') {
            index++;
        } else {
            break;
        }
    }
    char *pMessage = message + index;
    Printer::print(pMessage, ADDRESS_LENGTH - index + 1);
}

void Printer::printlnAddress(uint64 address) {
    char message[ADDRESS_LENGTH];
    for (int i = 0; i < ADDRESS_LENGTH - 1; i++) {
        message[i] = ' ';
    }
    Utils::convertIntToHexString(address, message, ADDRESS_LENGTH);
    uint8 index = 0;
    for (uint8 i = 0; i < ADDRESS_LENGTH; i++) {
        if (message[i] == ' ') {
            index++;
        } else {
            break;
        }
    }
    char *pMessage = message + index;
    Printer::println(pMessage, ADDRESS_LENGTH - index);
}

void Printer::clearScreen() {
    asm ("movq $0xB8000, %rdi");             
    asm ("movq $0x1F201F201F201F20, %rax"); 
    asm ("movq $500, %rcx");                
    asm ("rep stosq");
}