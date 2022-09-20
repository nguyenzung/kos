#include <kernel/context.h>
#include <kernel/printer.h>

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
    // Printer::print(" SAVE ", 6);
    // Printer::printlnAddress((uint64)address);
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

    // Printer::printAddress(this->ss);
    // Printer::print();
    // Printer::printAddress(this->rsp);
    // Printer::print();
    // Printer::printAddress(this->flags);
    // Printer::print();
    // Printer::printAddress(this->cs);
    // Printer::print();
    // Printer::printAddress(this->rip);
}

void Context::load(uint64 *address)
{
    *(address--) = this->ss;
    *(address--) = this->rsp;
    *(address--) = this->flags;
    *(address--) = this->cs;
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