/* vga.h - VGA текстовый режим */
#ifndef VGA_H
#define VGA_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
    #endif

    void vga_clear(uint8_t color);
    void vga_puts(const char* str, uint8_t color);
    void vga_putc(char c, uint8_t color);
    void vga_putchar(char c, uint8_t color);
    void vga_backspace(void);

    #ifdef __cplusplus
}
#endif

#endif
