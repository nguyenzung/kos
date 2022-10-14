#include <kernel/printer.h>
#include <kernel/utils.h>
#include <stdlib/string.h>

#define ADDRESS_LENGTH 66
#define SCREEN_WITH 80
#define SCREEN_HIEGHT 25
#define SCREEN_MAP_MEM 0xb8000 

using namespace kernel;

uint8 Printer::x = 0;
uint8 Printer::y = 0;

void Printer::printfHelper(int i, const char *format) { print((char*)format + i); }

int volatile *Printer::getLockInstance() {
    static DECLARE_LOCK(print_lock);
//    INIT_LOCK(print_lock);
    return &print_lockLocked;
}

void Printer::updatePointer(int len) {
    if (x + len > SCREEN_WITH) {
        x = x + len - SCREEN_WITH;
        y++;
    } else {
        x = x + len;
    }
    if (y == 24)
    {
        std::memmove((void*)(SCREEN_MAP_MEM - 160), (void*)SCREEN_MAP_MEM, 160 * 25);
        y--;
    }
}

void Printer::putc(char c, int i, void (*ptr)(int)) {
    unsigned char *VideoMapAddress =
        (unsigned char *)SCREEN_MAP_MEM+ y * SCREEN_WITH * 2 + x * 2;

    switch (c) {
    case '\n':
        println();
        break;
    default:
        VideoMapAddress[i * 2] = c;
        VideoMapAddress[i * 2 + 1] = 0x2f;
        if (ptr != nullptr)
            ptr(1);
        break;
    }
}

void Printer::print(const char *message, uint8 len) {
    if (len == 0) {
        while (message[len] != '\0')
            len++;
    }

    for (int i = 0; i < len; i++)
        putc(message[i], i, nullptr);

    updatePointer(len);
}

void Printer::println(const char *message, uint8 len) {
    Printer::print(message, len);
    y++;
    x = 0;

    if (y == 24)
    {
        std::memmove((void*)(SCREEN_MAP_MEM - 160), (void*)SCREEN_MAP_MEM, 160 * 25);
        y--;
    }
}

char* buildMessage(uint64 address, char *message, uint8 length, char* (*fun_ptr)(uint64, char*, uint8))
{
    for (int i = 0; i < ADDRESS_LENGTH - 1; i++) {
        message[i] = ' ';
    }
    fun_ptr(address, message, ADDRESS_LENGTH);
    uint8 index = 0;
    for (uint8 i = 0; i < ADDRESS_LENGTH; i++) {
        if (message[i] == ' ') {
            index++;
        } else {
            break;
        }
    }
    char *pMessage = message + index;
    return pMessage;
}

void Printer::printAddress(uint64 address)
{
    char message[ADDRESS_LENGTH];
    char *pMessage = buildMessage(address, message, ADDRESS_LENGTH, &Utils::convertIntToHexString);
    Printer::print(pMessage, ADDRESS_LENGTH - (pMessage - message));
}

void Printer::printlnAddress(uint64 address)
{
    char message[ADDRESS_LENGTH];
    char *pMessage = buildMessage(address, message, ADDRESS_LENGTH, &Utils::convertIntToHexString);
    Printer::println(pMessage, ADDRESS_LENGTH - (pMessage - message));
}

void Printer::printNumber(uint64 address)
{
    char message[ADDRESS_LENGTH];
    char *pMessage = buildMessage(address, message, ADDRESS_LENGTH, &Utils::convertIntToDecString);
    Printer::print(pMessage, ADDRESS_LENGTH - (pMessage - message));
}

void Printer::printlnNumber(uint64 address)
{
    char message[ADDRESS_LENGTH];
    char *pMessage = buildMessage(address, message, ADDRESS_LENGTH, &Utils::convertIntToDecString);
    Printer::println(pMessage, ADDRESS_LENGTH - (pMessage - message));
}

void Printer::printBinary(uint64 address)
{
    char message[ADDRESS_LENGTH];
    char *pMessage = buildMessage(address, message, ADDRESS_LENGTH, &Utils::convertIntToBinString);
    Printer::print(pMessage, ADDRESS_LENGTH - (pMessage - message));
}

void Printer::printlnBinary(uint64 address)
{
    char message[ADDRESS_LENGTH];
    char *pMessage = buildMessage(address, message, ADDRESS_LENGTH, &Utils::convertIntToBinString);
    Printer::println(pMessage, ADDRESS_LENGTH - (pMessage - message));
}

void Printer::print()
{
    Printer::print(" ", 1);
}

void Printer::println()
{
    Printer::println(" ", 1);
}

void Printer::printlnNumbers(uint64 *numbers, uint8 size) 
{
    for (uint8 i = 0; i < size; i++) {
        Printer::print(" ", 1);
        Printer::printNumber(numbers[i]);
    }
    Printer::println();
}

void Printer::printlnAddresses(uint64 *numbers, uint8 size)
{
    for (uint8 i = 0; i < size; i++) {
        Printer::print(" ", 1);
        Printer::printAddress(numbers[i]);
    }
    Printer::println();
}

void Printer::clearScreen() {
    asm ("movq $0xB8000, %rdi");             
    asm ("movq $0x1F201F201F201F20, %rax"); 
    asm ("movq $500, %rcx");                
    asm ("rep stosq");
}
