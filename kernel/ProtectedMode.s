section .multiboot
start_multiboot:
    dd 0xe85250d6
    dd 0
    dd end_multiboot - start_multiboot
    dd 0x100000000 - (0xe85250d6 + 0 + (end_multiboot - start_multiboot))
end_multiboot:
align 8
	dw 5
	dw 1
	dd 20
	dd 1024
	dd 768
	dd 24
align 8
    dw 0
	dw 0
	dd 8

section .text
bits 32
global start

extern printMessage
extern startLongMode

start:
    mov [multibootData], ebx
	call verifySupportCPUID
	call verifySupportLongMode
	call setupMemoryPaging
	call enablePaging
	call enableLongMode
	hlt

; error if we can not flip cpuid flag, 
verifySupportCPUID:
	pushfd
	pop eax
	mov ebx, eax
	xor eax, 1<<21 ; 
	push eax
	popfd
	pushfd
	pop eax
	cmp eax, ebx
	je endBoot64
	mov esi, support_cpuid_message
	call printMessage
	ret

verifySupportLongMode:
	mov eax, 0x80000000
	cpuid
	cmp eax, 0x80000001
	jb endBoot64
	mov eax, 0x80000001
	cpuid
	test edx, 1 << 29
	jz endBoot64
	mov esi, support_long_mode_message
	call printMessage
	ret

setupMemoryPaging:
	mov esi, lv3_page_address
	or esi, 0b11	
	mov [lv4_page_address], esi

	mov esi, lv2_page_address
	or esi, 0b11	
	mov [lv3_page_address], esi

	mov ebx, lv1_page_address          
    mov ecx, LV2_PAGE_ROW                 
	mov esi, lv2_page_address
.set_l2_entry:
	or ebx, 0b11
    mov DWORD [esi], ebx         
    add ebx, 0x1000              
    add esi, 8                   
    loop .set_l2_entry

; Start init Level 1 entry
	mov ebx, 0x00000000          
    mov ecx, LV1_PAGE_TOTAL_ROW                 
	mov esi, lv1_page_address
.set_l1_entry:
	or ebx, 0b11
    mov DWORD [esi], ebx         
    add ebx, 0x1000              
    add esi, 8                   
    loop .set_l1_entry
	ret
	
enablePaging:
	mov esi, lv4_page_address
	mov cr3, esi

	mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax
	
	mov ecx, 0xC0000080          
    rdmsr                        
    or eax, 1 << 8               
    wrmsr
	mov eax, cr0                 
    or eax, 1 << 31
    mov cr0, eax     
	ret

enableLongMode:
	lgdt [GDT64.Pointer]    
    jmp GDT64.Code:startLongMode
	ret

endBoot64:
	jmp $
	ret

section .rodata
global GDT64
global GDT64Code
global GDT64Data
global GDT64TSS
global GDTPTR
; Access bits
PRESENT		equ 1 << 7
NOT_SYS     equ 1 << 4
EXEC        equ 1 << 3
DC          equ 1 << 2
RW          equ 1 << 1
ACCESSED    equ 1 << 0

; Flags bits
GRAN_4K     equ 1 << 7
SZ_32       equ 1 << 6
LONG_MODE   equ 1 << 5
align 4096
GDT64:
    .Null: equ $ - GDT64
        dq 0
    .Code: equ $ - GDT64
        dd 0x0000                                   ; Limit & Base (low, bits 0-15)
        db 0                                        ; Base (mid, bits 16-23)
        db PRESENT | NOT_SYS | EXEC | RW            ; Access
        db GRAN_4K | LONG_MODE | 0xF                ; Flags & Limit (high, bits 16-19)
        db 0                                        ; Base (high, bits 24-31)
    .Data: equ $ - GDT64
        dd 0xFFFF                                   ; Limit & Base (low, bits 0-15)
        db 0                                        ; Base (mid, bits 16-23)
        db PRESENT | NOT_SYS | RW                   ; Access
        db GRAN_4K | SZ_32 | 0xF                    ; Flags & Limit (high, bits 16-19)
        db 0                                        ; Base (high, bits 24-31)
    .TSS: equ $ - GDT64
        dd 0x00000068
        dd 0x00CF8900
    .Pointer:
        dw $ - GDT64 - 1
        dq GDT64
GDTPTR		equ GDT64.Pointer
; GDT64Code   equ GDT64.Code
section .data
global pageMapStart
global pageMapEnd
global multibootData
	current_lv2_index 			dw 0
	current_lv1_index 			dw 0
	support_cpuid_message 		db "[Support CPUID]",7
	support_long_mode_message 	db "[Support Long Mode]",7
	setup_lv1_message 			db "[Setup Level 1 ROW]",7
	finish_lv1_message 			db "[Finish Level 1 ROW]",7
	setup_lv2_message 			db "[Setup Level 2 ROW]",7
	finish_lv2_message 			db "[Finish Level 2 ROW]",7
	enable_paging_message 		db "[Enable Paging]",7
	debug						db "[DEBUG]", 7
	GDT64Code					dq GDT64.Code
	GDT64Data					dq GDT64.Data
	GDT64TSS					dq GDT64.TSS
	multibootData				dq 0
	pageMapStart				dq lv4_page_address
	pageMapEnd					dq end_page_address

section .bss
	align 4096
	lv4_page_address:	resb PAGE_TABLE_SIZE
	lv3_page_address: 	resb PAGE_TABLE_SIZE
	lv2_page_address: 	resb LV2_PAGE_TABLE_NUM*PAGE_TABLE_SIZE
	lv1_page_address: 	resb LV1_PAGE_TABLE_NUM*PAGE_TABLE_SIZE*LV2_PAGE_TABLE_NUM
	end_page_address:	

	PAGE_TABLE_SIZE 	equ 4096

	LV4_PAGE_ROW 		equ 512
	LV3_PAGE_ROW 		equ 512
	LV2_PAGE_ROW 		equ 256
	LV1_PAGE_ROW 		equ 512
	LV1_PAGE_TOTAL_ROW 	equ LV1_PAGE_ROW * LV2_PAGE_ROW

	LV2_PAGE_TABLE_NUM 	equ 8
	LV1_PAGE_TABLE_NUM 	equ LV2_PAGE_ROW
	