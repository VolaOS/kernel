#include <stdint.h>
#include <string.h>

#include "idt.h"


extern void isr0(void);

static idt_entry_t idt[IDT_SIZE];
static idt_ptr_t idtp;


void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags)
{
	idt[num].offset_low  = (uint16_t)(base & 0xFFFF);
	idt[num].offset_high = (uint16_t)((base >> 16) & 0xFFFF);
	idt[num].zero		 = 0;
	idt[num].selector	 = selector;
	idt[num].flags		 = flags;
}

void idt_init(void)
{
	idtp.limit = (uint16_t)(sizeof(idt) - 1);
	idtp.base  = (uint32_t)(uintptr_t)&idt[0];

	memset(idt, 0, sizeof(idt));

	idt_set_gate(0, (uint32_t)(uintptr_t)isr0, IDT_SEL, IDT_FLAGS);

	idt_flush(&idtp);
}
