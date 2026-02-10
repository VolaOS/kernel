#include "vga.h"


static volatile uint16_t* __vga = (volatile uint16_t*)VGA_ADDR;
static vga_cursor_t __cursor = { 0, 0 };
static uint8_t __color = VGA_ATTR(BRIGHT_WHITE, BLACK);


// устанавливает курсор в позицию (_X, _Y)
static void set_cursor(const uint8_t _X, const uint8_t _Y)
{
	__cursor.x = _X;
	__cursor.y = _Y;
}


// меняет глобальный цвет
void vga_color(const vga_color_t _Fg, const vga_color_t _Bg)
{
	__color = VGA_ATTR(_Fg, _Bg);
}

// печатает символ
void vga_putc(const uint8_t _Character)
{
	if (__cursor.y >= VGA_HEIGHT)
		return;

	if (_Character == '\n')
	{
		set_cursor(0, ++__cursor.y);
		return;
	}

	const unsigned index = __cursor.y * VGA_WIDTH + __cursor.x;
	__vga[index] = (__color << 8) | _Character;

	if (++__cursor.x >= VGA_WIDTH)
		set_cursor(0, ++__cursor.y);
}

// очищает экран
void vga_clear(void)
{
	set_cursor(0, 0);

	for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
		vga[i] = (BRIGHT_WHITE << 8) | ' ';

	set_cursor(0, 0);
}

// печатает строку
void vga_puts(const char* _Str)
{
	char c;
	while ((c = *_Str++) != '\0')
		vga_putc(c);
}

// выводит сообщение об ошибке и останавливает процессор
void vga_error(const char* _Message)
{
	vga_color(RED, BLACK);
	vga_puts("Error: ");
	vga_puts(_Message);
	for (;;) { __asm__ volatile("hlt"); }
}
