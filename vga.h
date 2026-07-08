/* vga.h - Простой вывод текста в VGA память */
#ifndef VGA_H
#define VGA_H

#include "types.h"

void vga_clear(uint8_t color);
void vga_putc(char c, uint8_t color);
void vga_puts(const char* s, uint8_t color);
void vga_newline(uint8_t color);

#endif
