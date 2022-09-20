#include <kernel/context.h>
#include <kernel/printer.h>

using namespace kernel;

Context::Context()
{

}

Context::Context(uint64 rbp, uint64 rsp, mainFunction entryPoint)
{

}

Context::~Context()
{

}

void Context::initialize()
{

}

void Context::save(uint64* address)
{
    Printer::print(" SAVE ", 6);
    Printer::printlnAddress((uint64)address);
    this->ss = *(address--);
    this->rsp= *(address--);
    this->flags = *(address--);
    this->cs = *(address--);
    this->rip = *(address--);
    Printer::printAddress(this->ss);
    Printer::printAddress(this->rsp);
    Printer::printAddress(this->flags);
    Printer::printAddress(this->cs);
    Printer::printAddress(this->rip);
}

void Context::load(uint64 *address)
{

}