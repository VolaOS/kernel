#include <stdint.h>
#include "vga.h"


void kernel_main(uint32_t multiboot_magic, uint32_t multiboot_info_addr)
{
	(void)multiboot_info_addr;

	vga_clear();
	vga_puts("VolaOS v0.1.0\n");

	for (;;) { __asm__ volatile("hlt"); }
}
