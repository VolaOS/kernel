#include <stdint.h>

#include "vga.h"
#include "idt.h"


void kernel_main(uint32_t multiboot_magic, uint32_t multiboot_info_addr)
{
	vga_clear();
	idt_init();

	vga_puts("VolaOS v0.1.0\n\n");

	// для теста ISR0
	// volatile int a = 1, b = 0;
	// volatile int c = a / b;

	for (;;) { __asm__ volatile("hlt"); }
}
