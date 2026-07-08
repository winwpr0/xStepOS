/* keyboard.c - Драйвер PS/2 клавиатуры с отладкой */
#include "keyboard.h"
#include "io.h"
#include "vga.h"

static const char scancode_to_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

static const char scancode_to_ascii_shift[] = {
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' '
};

static int shift_pressed = 0;
static int caps_lock = 0;

void keyboard_init(void) {
    /* Ждём готовности контроллера */
    while (inb(KEYBOARD_STATUS_PORT) & 0x02);

    /* Включаем сканирование */
    outb(KEYBOARD_DATA_PORT, 0xF4);

    shift_pressed = 0;
    caps_lock = 0;

    vga_puts("[KEYBOARD] PS/2 keyboard initialized\n", 0x0B);
    vga_puts("[KEYBOARD] Try pressing keys...\n", 0x07);
}

static char read_scancode(void) {
    uint8_t status;
    int timeout = 1000000;

    while (timeout > 0) {
        status = inb(KEYBOARD_STATUS_PORT);
        if (status & 0x01) {
            return inb(KEYBOARD_DATA_PORT);
        }
        timeout--;
    }

    return 0;
}

char keyboard_getchar(void) {
    while (1) {
        uint8_t scancode = read_scancode();

        if (scancode == 0) {
            /* Таймаут - выведем точку для отладки */
            vga_putc('.', 0x08);
            continue;
        }

        if (scancode & 0x80) {
            uint8_t make = scancode & 0x7F;
            if (make == KEY_LSHIFT || make == KEY_RSHIFT) shift_pressed = 0;
            continue;
        }

        if (scancode == KEY_LSHIFT || scancode == KEY_RSHIFT) {
            shift_pressed = 1;
            vga_puts("[SHIFT]\n", 0x0E);
            continue;
        }
        if (scancode == KEY_CAPSLOCK) {
            caps_lock = !caps_lock;
            continue;
        }

        if (scancode < sizeof(scancode_to_ascii)) {
            char c = shift_pressed ? scancode_to_ascii_shift[scancode] : scancode_to_ascii[scancode];

            if (caps_lock && c >= 'a' && c <= 'z') c -= 32;
            else if (caps_lock && c >= 'A' && c <= 'Z') c += 32;

            if (c != 0) {
                vga_puts("[", 0x08);
                vga_putc(c, 0x0E);
                vga_puts("]\n", 0x08);
                return c;
            }
        }

        /* Отладка - выводим scancode */
        vga_puts("[SC:", 0x08);
        vga_putc((scancode >> 4) + '0', 0x08);
        vga_putc((scancode & 0x0F) + '0', 0x08);
        vga_puts("]\n", 0x08);
    }
}

int keyboard_has_input(void) {
    return (inb(KEYBOARD_STATUS_PORT) & 0x01) != 0;
}

void keyboard_readline(char* buffer, int max_len) {
    int i = 0;
    char c;

    while (i < max_len - 1) {
        c = keyboard_getchar();

        if (c == '\n') {
            vga_putchar('\n', 0x0F);
            break;
        } else if (c == '\b') {
            if (i > 0) {
                i--;
                vga_backspace();
            }
        } else {
            buffer[i] = c;
            i++;
            vga_putchar(c, 0x0F);
        }
    }

    buffer[i] = '\0';
}
