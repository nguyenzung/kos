%macro PUSH_REGISTERS 0
    push rax
    push rbx
    push rcx 
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    push rbp
    push gs
    push fs

%endmacro

%macro POP_REGISTERS 0
    pop fs
    pop gs
    pop rbp
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

%macro IRS_ERR_STUB 1
isrStub_%+%1:
    PUSH_REGISTERS
    cld
    call _ZN6kernel16InterruptManager11getInstanceEv
    mov rdi, rax
    mov rsi, (%1 + 0x20)
    call _ZN6kernel16InterruptManager15handleInterruptEm
    POP_REGISTERS
    iretq
%endmacro 
; if writing for 64-bit, use iretq instead
%macro IRS_NO_ERR_STUB 1
isrStub_%+%1:
    PUSH_REGISTERS
    cld
    call _ZN6kernel16InterruptManager11getInstanceEv
    mov rdi, rax
    mov rsi, (%1 + 0x20)
    call _ZN6kernel16InterruptManager15handleInterruptEm
    POP_REGISTERS
    iretq
%endmacro

section .text
bits 64

global startLongMode
global __cxa_pure_virtual
global isrTimerHandler
; extern stack_base
extern GDT64Data
extern main
extern printMessage
extern _ZN6kernel16InterruptManager15handleInterruptEm ; interruptHandler
extern _ZN6kernel16InterruptManager11getInstanceEv ; getInterrupManagerInstance
extern _GLOBAL__sub_I__ZN13DeviceManager13deviceManagerE;
extern _ZN6kernel11TaskManager11getInstanceEv
extern _ZN6kernel11TaskManager4saveEPm
extern _ZN6kernel11TaskManager4loadEPm
extern _ZN6kernel11TaskManager14saveMainKernelEPm
extern _ZN6kernel11TaskManager14loadMainKernelEPm
extern _ZN6kernel6Kernel11getInstanceEv ; get kernel instance
; extern _ZN6kernel7Context4saveEPm   ; context save
; extern _ZN6kernel7Context4loadEPm   ; context load
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
    ; mov rax, rip
    ; push rip
    mov rax, 0
    mov ss, rax
    mov ds, rax
    mov es, rax
    mov fs, rax
    mov gs, rax
    ; mov rbp, stack_base
    mov rsp, stack_base
    mov rdi, 0xB8000             
    mov rax, 0x1F201F201F201F20 
    mov ecx, 500
    rep stosq
    ; mov rax, isrStub_0
    ; cmp rax, [isrStubTable]
    ; je debug
    mov rsi, [stackBase]
    ;mov qword [rsi], 0x12345678
    mov qword [rsi-8], 0x87654321
    mov rsi, [heapBase]
    mov qword [rsi], 0x23456789
    call main

isrTimerHandler:
    ; call switchTask
    ; push 0x123456
    PUSH_REGISTERS
    
    mov rsi, rsp
    add rsi, (17 * 8 + 32)  ; calculate stackframe size
    mov [stackIndex], rsi

    ; mov rsi, interrupt_handler_msg
    ; call printMessage

    ; save task context
    call _ZN6kernel11TaskManager11getInstanceEv
    mov rdi, rax
    mov rsi, [stackIndex]
    call _ZN6kernel11TaskManager4saveEPm

    ; process interrupt in mainthread
    call _ZN6kernel16InterruptManager11getInstanceEv
    mov rdi, rax
    mov rsi, 0x20
    call _ZN6kernel16InterruptManager15handleInterruptEm


    ; schedule new task
    call _ZN6kernel11TaskManager11getInstanceEv
    mov rdi, rax
    mov rsi, [stackIndex]
    call _ZN6kernel11TaskManager4loadEPm

    POP_REGISTERS
    iretq

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

section .data
global isrStubTable
global stackBase
global stackSize
global heapBase
    stackIndex dq 0
isrStubTable:
    dq 0
%assign i 0 
%rep    32 
    dq isrStub_%+i
%assign i i+1 
%endrep
    stackBase               dq stack_base
    stackLimit              dq stack_limit
    heapBase                dq heap_base
    stackSize               dq stack_size
    interrupt_handler_msg   db "[Enable Paging]",7

section .bss
global stack_base
global heap_base
align 4096
stack_bottom: 		resb 8*1024*1024
stack_base:         resb 32*1024*1024
stack_limit:        
stack_size 			equ $ - stack_bottom
heap_base:          resb 256*1024*1024

