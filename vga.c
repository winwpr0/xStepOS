/* vga.c - Реализация VGA вывода */
#include "vga.h"

static uint16_t* vga_buffer = (uint16_t*)0xB8000;
static int cursor_x = 0;
static int cursor_y = 0;

void vga_clear(uint8_t color) {
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = (color << 8) | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
}

void vga_putc(char c, uint8_t color) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        vga_buffer[cursor_y * 80 + cursor_x] = (color << 8) | c;
        cursor_x++;
        if (cursor_x >= 80) {
            cursor_x = 0;
            cursor_y++;
        }
    }
    if (cursor_y >= 25) {
        /* Простой скролл: очищаем экран */
        vga_clear(color);
    }
}

void vga_puts(const char* s, uint8_t color) {
    while (*s) {
        vga_putc(*s++, color);
    }
}

void vga_newline(uint8_t color) {
    vga_putc('\n', color);
}
