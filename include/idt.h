#pragma once

#include <stdint.h>

#define IDT_SIZE  256
#define IDT_SEL   0x10
#define IDT_FLAGS 0x8E


typedef struct __attribute__((packed))  // packed для того, чтобы gcc не выравнивал структуру и не добавлял лишние байты
{
	uint16_t offset_low;		// младшие 16 бит смещения
	uint16_t selector;			// селектор сегмента кода
	uint8_t  zero;				// всегда 0
	uint8_t  flags;				// флаги
	uint16_t offset_high;		// старшие 16 бит смещения
} idt_entry_t;

typedef struct __attribute__((packed))
{
	uint16_t limit;		// (размер idt) - 1
	uint32_t base;		// адрес idt
} idt_ptr_t;


void idt_init(void);
void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);
extern void idt_flush(idt_ptr_t* idt_ptr);
