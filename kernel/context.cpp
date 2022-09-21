#include <kernel/context.h>
#include <kernel/printer.h>
#include <kernel/kernel.h>

using namespace kernel;

Context::Context()
{
}

Context::Context(uint64 rbp, uint64 rsp, mainFunction entryPoint)
{
    this->rbp = rbp;
    this->rsp = rsp;
    this->rip = (uint64)entryPoint;
}

Context::~Context()
{
}

void Context::initialize()
{
}

void Context::save(uint64* address)
{
    this->ss = *(address--);
    this->rsp= *(address--);
    this->flags = *(address--);
    this->cs = *(address--);
    this->rip = *(address--);
    this->rax = *(address--);
    this->rbx = *(address--);
    this->rcx = *(address--);
    this->rdx = *(address--);
    this->rsi = *(address--);
    this->rdi = *(address--);
    this->r8 = *(address--);
    this->r9 = *(address--);
    this->r10 = *(address--);
    this->r11 = *(address--);
    this->r12 = *(address--);
    this->r13 = *(address--);
    this->r14 = *(address--);
    this->r15 = *(address--);

    Printer::printAddress(this->ss);
    Printer::print();
    Printer::printAddress(this->rsp);
    Printer::print();
    Printer::printAddress(this->flags);
    Printer::print();
    Printer::printAddress(this->cs);
    Printer::print();
    Printer::printAddress(this->rip);
    Printer::print();
    Printer::printAddress(this->rax);
    Printer::print();
    Printer::printAddress(this->rbx);
    Printer::print();
    Printer::printAddress(this->rcx);
    Printer::print();
    Printer::printAddress(this->rdx);
    Printer::print();
    Printer::printAddress(this->rsi);
    Printer::print();
    Printer::printAddress(this->rdi);

    Printer::println();
}

void Context::load(uint64 *address)
{
    Printer::print(" LOAD ", 6);
    Printer::printAddress(this->ss);
    Printer::print();
    Printer::printAddress(this->rsp);
    Printer::print();
    Printer::printAddress(this->flags);
    Printer::print();
    Printer::printAddress(this->cs);
    Printer::print();
    Printer::printAddress(this->rip);
    Printer::print();
    Printer::printAddress(this->rax);
    Printer::print();
    Printer::printAddress(this->rbx);
    Printer::print();
    Printer::printAddress(this->rcx);
    Printer::print();
    Printer::printAddress(this->rdx);
    Printer::print();
    Printer::printAddress(this->rsi);
    Printer::print();
    Printer::printAddress(this->rdi);

    Printer::println();
    // while (true)
    // {
    //     /* code */
    // }
    

    *(address--) = this->ss;
    *(address--) = this->rsp;
    *(address--) = this->flags;
    *(address--) = this->cs;
    // *(address--) = (uint64)&kernel::Kernel::hlt;
    *(address--) = this->rip;
    *(address--) = this->rax;
    *(address--) = this->rbx;
    *(address--) = this->rcx;
    *(address--) = this->rdx;
    *(address--) = this->rsi;
    *(address--) = this->rdi;
    *(address--) = this->r8;
    *(address--) = this->r9;
    *(address--) = this->r10;
    *(address--) = this->r11;
    *(address--) = this->r12;
    *(address--) = this->r13;
    *(address--) = this->r14;
    *(address--) = this->r15;
}