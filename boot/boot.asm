bits 32

section .multiboot
align 4
dd 0x1BADB002
dd 0x00000000
dd -(0x1BADB002)

section .text
global start
extern kernel_main

start:
	cli

	mov esp, stack_top

	push ebx
	push eax
	call kernel_main

.hang:
	hlt
	jmp .hang

section .bss
align 16
resb 8192
stack_top:
