#pragma once

#include <stdint.h>

#define VGA_ADDR 		0xB8000
#define VGA_WIDTH  		80
#define VGA_HEIGHT  	25

#define VGA_ATTR(fg, bg) ((bg << 4) | fg) // bg - старший байт, fg - младший байт


typedef enum
{
	BLACK 			= 0x00,
	BLUE 			= 0x01,
	GREEN			= 0x02,
	CYAN			= 0x03,
	RED 			= 0x04,
	MAGENTA			= 0x05,
	BROWN			= 0x06,
	WHITE			= 0x07,
	GRAY			= 0x08,
	LIGHT_BLUE		= 0x09,
	LIGHT_GREEN		= 0x0A,
	LIGHT_CYAN		= 0x0B,
	LIGHT_RED		= 0x0C,
	LIGHT_MAGENTA	= 0x0D,
	YELLOW			= 0x0E,
	BRIGHT_WHITE	= 0x0F
} vga_color_t;

typedef struct
{
	uint8_t x;
	uint8_t y;
} vga_cursor_t;


void vga_clear(void);
void vga_putc(const uint8_t _Character);
void vga_puts(const char* _Str);
void vga_color(const vga_color_t _Fg, const vga_color_t _Bg);
void vga_error(const char* _Message);
