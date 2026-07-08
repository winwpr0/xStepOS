/* encoding.c - Реализация парсинга кодировок */
#include "encoding.h"
#include "vga.h"

uint8_t get_cyrillic_byte(char c) {
    switch (c) {
        case 'A': return 0x80; case 'B': return 0x81;
        case 'D': return 0x82; case 'E': return 0x83;
        case 'G': return 0x85; case 'K': return 0x8A;
        case 'L': return 0x8B; case 'M': return 0x8C;
        case 'N': return 0x8D; case 'O': return 0x8E;
        case 'P': return 0x8F; case 'R': return 0x90;
        case 'S': return 0x91; case 'T': return 0x92;
        case 'V': return 0x95; case 'Y': return 0x98;
        case 'Z': return 0x99;
        case 'a': return 0xA0; case 'b': return 0xA1;
        case 'e': return 0xA2; case 'g': return 0xA3;
        case 'k': return 0xA4; case 'l': return 0xA5;
        case 'm': return 0xA6; case 'n': return 0xA7;
        case 'o': return 0xA8; case 'p': return 0xA9;
        case 'r': return 0xAA; case 's': return 0xAB;
        case 't': return 0xAC; case 'u': return 0xAD;
        case 'v': return 0xAE; case 'z': return 0xB0;
        case 'i': return 0xB1; case 'd': return 0xB4;
        case 'y': return 0xB5; case 'h': return 0xB6;
        default:  return '?';
    }
}

uint8_t get_greek_byte(char c) {
    switch (c) {
        case 'A': return 0xC1; case 'B': return 0xC2;
        case 'G': return 0xC3; case 'D': return 0xC4;
        case 'E': return 0xC5; case 'Z': return 0xC6;
        case 'H': return 0xC7; case 'a': return 0xE1;
        case 'b': return 0xE2; case 'g': return 0xE3;
        case 'd': return 0xE4; case 'e': return 0xE5;
        default:  return '?';
    }
}

void xstep_puts(const char* str, uint8_t color) {
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '\\' && str[i+1] != '\0') {
            char mode = str[i+1];

            if (mode == 'c') {
                if (str[i+2] != '\0') {
                    uint8_t cyrillic_byte = get_cyrillic_byte(str[i+2]);
                    vga_putc(cyrillic_byte, color);
                    i += 3;
                    continue;
                }
            }
            else if (mode == 'g') {
                if (str[i+2] != '\0') {
                    uint8_t greek_byte = get_greek_byte(str[i+2]);
                    vga_putc(greek_byte, color);
                    i += 3;
                    continue;
                }
            }
            else if (mode == 'n') {
                vga_putc('\n', color);
                i += 2;
                continue;
            }
        }

        vga_putc(str[i], color);
        i++;
    }
}
