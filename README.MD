# A simple 64 bits Operating System for x64

Just for fun.

I use C++ and Assembly to develop the OS. I use g++ and Nasm for compiler tools

## Dependencies

- Any `gcc` toolchain that support x64.
- `make`
- `nasm`
- `grub`
- `xorriso` - For making iso file used by `grub-mkrescure`.
- `qemu` - Using `qemu-system-x86_64` for testing.

Make sure all dependencies were installed, and you good to go.

## How to run:

Build the source code with `make` or `make all` or run the os on Qemu with `make demo`.


## Timeline:

1. Enter Long mode: check CPU support, setup Memory mapping, setup GDT
2. Create interrupt handler. Using PIC. I have plan to move to APIC later.
3. Create debug functions: print, printNumber, printAddress. 
4. Some simple drivers: Timer, Keyboard, Video Graphics
5. Create DynamicMemory module. Now we use operator: new, delete, new[], delete[]
6. Add datastructure: list. We need to add more data structure like: tree, hashtable...
7. Support multithreading. Schedule tasks
8. ...

Reference: https://wiki.osdev.org/Expanded_Main_Page