#ifndef PRINTER
#define PRINTER

#include <kernel/type.h>
#include <kernel/utils.h>
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
    static void putc(char c, int i = 0, void (*ptr)(int) = updatePointer);
    static void print(char *message, uint8 length = 0);
    static void println(char *message, uint8 length);
    static void printAddress(uint64 address);
    static void printlnAddress(uint64 address);
    static void printNumber(uint64 address);
    static void printlnNumber(uint64 address);
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
    char tmp[10] = {0};

    for (; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            switch (format[i + 1]) {
            case 'd':
                Utils::convertIntToDecString((uint64)first, tmp, 10);
                Printer::print(tmp, 10);
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
void Printer::printf(const char *format, Args... args) {
    Printer::printfHelper(0, format, args...);
}

} // namespace kernel

template <typename... Args>
void printf(const char *format, Args... args) {
    kernel::Printer::printf(format, args...);
}

#endif
