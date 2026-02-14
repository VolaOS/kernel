#include "vga.h"


void isr0_handler(void)
{
	vga_clear();
	vga_error("ISR0");
}
