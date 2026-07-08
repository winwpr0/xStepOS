/* vga.c - VGA текстовый режим */
#include "vga.h"
#include "io.h"

static uint16_t cursor_x = 0;
static uint16_t cursor_y = 0;

static void update_cursor(void) {
    uint16_t pos = cursor_y * 80 + cursor_x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void vga_clear(uint8_t color) {
    uint16_t* vga = (uint16_t*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        vga[i] = ' ' | (color << 8);
    }
    cursor_x = 0;
    cursor_y = 0;
    update_cursor();
}

void vga_putc(char c, uint8_t color) {
    uint16_t* vga = (uint16_t*)0xB8000;
    int pos = cursor_y * 80 + cursor_x;

    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\b') {
        if (cursor_x > 0) {
            cursor_x--;
            pos = cursor_y * 80 + cursor_x;
            vga[pos] = ' ' | (color << 8);
        }
    } else {
        vga[pos] = c | (color << 8);
        cursor_x++;
    }

    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= 25) {
        /* Прокрутка */
        for (int i = 0; i < 80 * 24; i++) {
            vga[i] = vga[i + 80];
        }
        for (int i = 80 * 24; i < 80 * 25; i++) {
            vga[i] = ' ' | (color << 8);
        }
        cursor_y = 24;
    }

    update_cursor();
}

void vga_putchar(char c, uint8_t color) {
    vga_putc(c, color);
}

void vga_puts(const char* str, uint8_t color) {
    while (*str) {
        vga_putc(*str, color);
        str++;
    }
}

void vga_backspace(void) {
    if (cursor_x > 0) {
        cursor_x--;
        uint16_t* vga = (uint16_t*)0xB8000;
        int pos = cursor_y * 80 + cursor_x;
        vga[pos] = ' ' | (0x0F << 8);
        update_cursor();
    } else if (cursor_y > 0) {
        cursor_y--;
        cursor_x = 79;
        uint16_t* vga = (uint16_t*)0xB8000;
        int pos = cursor_y * 80 + cursor_x;
        vga[pos] = ' ' | (0x0F << 8);
        update_cursor();
    }
}
