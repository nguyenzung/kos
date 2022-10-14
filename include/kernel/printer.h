#ifndef PRINTER
#define PRINTER

#include <kernel/type.h>
#include <kernel/utils.h>
#include <stdlib/lock.h>
// #include <type_traits>

namespace kernel {
    

class Printer {
    static uint8 x;
    static uint8 y;
    static uint8 z;

  public:
    /*
     * print arguments follow a format
     * %d -> print as an integer
     * %p -> print as an address in hex
     * %s -> print as a string
     *
     * @param format a format string
     * @param args variadic parameter corresponding with the format string
     */
    template <typename... Args>
    static void printf(const char *format, Args... args);

    /*
     * print a character
     */
    static int volatile *getLockInstance();
    static void putc(char c, int i = 0, void (*ptr)(int) = updatePointer);
    static void print(const char *message, uint8 length = 0);
    static void println(const char *message, uint8 length);
    static void printAddress(uint64 address);
    static void printlnAddress(uint64 address);
    static void printNumber(uint64 address);
    static void printlnNumber(uint64 address);
    static void printBinary(uint64 address);
    static void printlnBinary(uint64 address);
    static void print();
    static void println();
    static void printlnNumbers(uint64 *numbers, uint8 size);
    static void printlnAddresses(uint64 *numbers, uint8 size);
    static void clearScreen();

  private:
    /*
     * update cursor position
     * @param len number of pixel to be moved in vertical
     */
    static void updatePointer(int len);
    static void printfHelper(int i, const char *format);
    template <typename T, typename... Args>
    static void printfHelper(int i, const char *format, T first, Args... args);
};

template <typename T, typename... Args>
void Printer::printfHelper(int i, const char *format, T first, Args... args) {
    for (; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            switch (format[i + 1]) {
            case 'b':
                Printer::printBinary((uint64)first);
                break;
            case 'd':
                Printer::printNumber((uint64)first);
                break;
            case 'p':
                Printer::printAddress((uint64)first);
                break;
            case 's':
                Printer::print((char*)first);
                break;
            default:
                break;
            }
            i += 2;
            printfHelper(i, format, args...);
            break;
        } else {
            Printer::putc(format[i]);
        }
    }
}

template <typename... Args>
void Printer::printf(const char *format, Args... args) 
{
    Printer::printfHelper(0, format, args...);
}

template <typename... Args>
void printf(const char *format, Args... args) {
    volatile int &print_lockLocked = *Printer::getLockInstance();
    LOCK(print_lock);
//    asm("cli");
    kernel::Printer::printf(format, args...);
//    asm("sti");
    UNLOCK(print_lock);
}

} // namespace kernel


#endif
