section .text
bits 32

global printMessage
printMessage:
    ret
	mov dl, byte [esi]
	mov eax, [currentIndex]
	mov byte [eax], dl
	inc eax
	mov byte [eax], 0x0f
	inc eax
	mov [currentIndex], eax
	inc esi
	cmp dl, 7
	jne printMessage
	mov eax, [currentIndex]
	add eax, 2
	mov [currentIndex], eax
	ret

section .data
	currentIndex dd 0xb8000