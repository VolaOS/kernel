bits 32

section .multiboot
align 4
dd 0x1BADB002		; magic number
dd 0x00000000		; flags
dd -(0x1BADB002)	; checksum

section .text
global start
extern kernel_main

start:
	cli

	mov esp, stack_top

	push ebx 	; multiboot_info_addr
	push eax 	; multiboot_magic
	call kernel_main

.hang:
	hlt
	jmp .hang

section .bss
align 16
stack_bottom:
	resb 8192
stack_top:
