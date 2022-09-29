#include <kernel/context.h>
#include <kernel/printer.h>
#include <kernel/kernel.h>
#include <tasks/counter.h>
#include <kernel/taskmanager.h>

using namespace kernel;

Context::Context()
{
}

Context::~Context()
{
}

void Context::initialize()
{
    this->cs = 0x08;
    this->flags = (1 << 9);
    this->rdi = (uint64) this->task;
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
    this->rbp = *(address--);
    this->gs = *(address--);
    this->fs = *(address--);
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
    *(address--) = this->rbp;
    *(address--) = this->gs;
    *(address--) = this->fs;
}

void Context::info()
{
    printf("\n Info0 %d %d %d %d %d %d %d %d %d %d ", task, rbp, rsp, rax, rbx, rcx, rdi, rsi, rip, flags);
    printf("\n Info1 %d %d %d %d %d %d %d %d %d %d %d %d", r8, r9, r10, r11, r12, r13, r14, r15, gs, fs, cs, ss);
}