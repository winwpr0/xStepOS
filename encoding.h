/* encoding.h - Система кодировок xStep OS */
#ifndef ENCODING_H
#define ENCODING_H

#include "types.h"

/* Функция вывода строки с поддержкой \c (кириллица) и \g (греческий) */
void xstep_puts(const char* str, uint8_t color);

/* Функция получения байта кодировки по транслиту */
uint8_t get_cyrillic_byte(char ascii_char);
uint8_t get_greek_byte(char ascii_char);

#endif
