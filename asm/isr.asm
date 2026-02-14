bits 32

section .text
global isr0
extern isr0_handler

isr0:
	pusha

	call isr0_handler

	popa
	iret
