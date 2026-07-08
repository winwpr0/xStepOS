/* font.c - Загрузка шрифта Terminus в VGA */
#include "font.h"
#include "io.h"

/* Внешний массив из xstep_font.c */
extern uint8_t xstep_font[];

void vga_load_font(void) {
    /* Выключаем видео */
    outb(0x3C4, 0x01);
    uint8_t seq1 = inb(0x3C5);
    outb(0x3C5, seq1 | 0x20);

    /* Выбираем Plane 2 (где хранится шрифт) */
    outb(0x3C4, 0x02);
    outb(0x3C5, 0x04);

    /* Копируем шрифт в VGA память (0xA0000) */
    uint8_t* vga_mem = (uint8_t*)0xA0000;
    for (int i = 0; i < 4096; i++) {
        vga_mem[i] = xstep_font[i];
    }

    /* Включаем видео */
    outb(0x3C4, 0x01);
    outb(0x3C5, seq1 & ~0x20);
}
