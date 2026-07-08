/* keyboard.h - Драйвер PS/2 клавиатуры */
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define KEY_ESCAPE 0x01
#define KEY_BACKSPACE 0x0E
#define KEY_TAB 0x0F
#define KEY_ENTER 0x1C
#define KEY_LCTRL 0x1D
#define KEY_LSHIFT 0x2A
#define KEY_RSHIFT 0x36
#define KEY_LALT 0x38
#define KEY_CAPSLOCK 0x3A

#ifdef __cplusplus
extern "C" {
    #endif

    void keyboard_init(void);
    char keyboard_getchar(void);
    void keyboard_readline(char* buffer, int max_len);
    int keyboard_has_input(void);

    #ifdef __cplusplus
}
#endif

#endif
