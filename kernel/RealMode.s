global setupAPAddress

section .text
setupAP:
	mov al, 'A'
	int 0x10
	mov al, 'P'
	int 0x10
	mov al, ' '
	int 0x10
	mov al, 'S'
	int 0x10
	mov al, 't'
	int 0x10
	mov al, 'a'
	int 0x10
	mov al, 'r'
	int 0x10
	mov al, 't'
	int 0x10
	mov al, 'e'
	int 0x10
	mov al, 'd'
	int 0x10
	
	jmp $
	
section .data
	msg				db	"AP Started", 7
	setupAPAddress	dq	setupAP