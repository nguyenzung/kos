#ifndef PRINTER
#define PRINTER

#include "type.h"

class Printer {
    static uint8 x;
    static uint8 y;
public:
    static void print(char *message, uint8 length);
    static void println(char *message, uint8 length);
    static void printAddress(uint64 address);
    static void printlnAddress(uint64 address);
    static void printNumber(uint64 address);
    static void printlnNumber(uint64 address);
    static void clearScreen();
};

#endif