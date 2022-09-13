%macro PUSH_REGISTERS 0
    push rax
    push rcx 
    push rdx
    push r8
    push r9
    push r10
    push r11
    push rsi
    push rdi
%endmacro

%macro POP_REGISTERS 0
    pop rdi
    pop rsi
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdx
    pop rcx
    pop rax
%endmacro

%macro IRS_ERR_STUB 1
isrStub_%+%1:
    PUSH_REGISTERS
    cld
    mov rsi, %1
    call _ZN16InterruptManager15exceptionHandleEm
    POP_REGISTERS
    iretq
%endmacro
; if writing for 64-bit, use iretq instead
%macro IRS_NO_ERR_STUB 1
isrStub_%+%1:
    PUSH_REGISTERS
    cld
    mov rsi, %1
    call _ZN16InterruptManager15exceptionHandleEm
    POP_REGISTERS
    iretq
%endmacro

section .text
global startLongMode
global isrStubTable
global __cxa_pure_virtual
; extern callConstructors;
extern stack_base
extern GDT64.Data
extern main
extern _ZN16InterruptManager15exceptionHandleEm
bits 64
%assign i 0 
%rep    32 
global isrStub_%+i
%assign i i+1
%endrep

; for bypass error with pure virtual function in c++
__cxa_pure_virtual:
    ret

startLongMode:
    cli               
    ; sti
    mov rax, GDT64.Data
    mov ss, rax
    mov ds, rax
    mov es, rax
    mov fs, rax
    mov gs, rax
    mov rsp, stack_base
    ; call callConstructors;
    mov rdi, 0xB8000             
    mov rax, 0x1F201F201F201F20 
    mov ecx, 500                
    rep stosq
    ; mov rax, isrStub_0
    ; cmp rax, [isrStubTable]
    ; je debug
    call main
debug:
    call isrStub_0
    jmp $


IRS_NO_ERR_STUB 0
IRS_NO_ERR_STUB 1
IRS_NO_ERR_STUB 2
IRS_NO_ERR_STUB 3
IRS_NO_ERR_STUB 4
IRS_NO_ERR_STUB 5
IRS_NO_ERR_STUB 6
IRS_NO_ERR_STUB 7
IRS_ERR_STUB    8
IRS_NO_ERR_STUB 9
IRS_ERR_STUB    10
IRS_ERR_STUB    11
IRS_ERR_STUB    12
IRS_ERR_STUB    13
IRS_ERR_STUB    14
IRS_NO_ERR_STUB 15
IRS_NO_ERR_STUB 16
IRS_ERR_STUB    17
IRS_NO_ERR_STUB 18
IRS_NO_ERR_STUB 19
IRS_NO_ERR_STUB 20
IRS_NO_ERR_STUB 21
IRS_NO_ERR_STUB 22
IRS_NO_ERR_STUB 23
IRS_NO_ERR_STUB 24
IRS_NO_ERR_STUB 25
IRS_NO_ERR_STUB 26
IRS_NO_ERR_STUB 27
IRS_NO_ERR_STUB 28
IRS_NO_ERR_STUB 29
IRS_ERR_STUB 30
IRS_NO_ERR_STUB 31

; section .data
isrStubTable:
%assign i 0 
%rep    32 
    dq isrStub_%+i
%assign i i+1 
%endrep
