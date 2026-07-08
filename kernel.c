/* kernel.c - xStep OS с OMC-SH */

#include "vga.h"
#include "user.h"
#include "keyboard.h"
#include "shell.h"

void kernel_main(void) {
    vga_clear(0x00);

    vga_puts("xStep OS - Starting...\n", 0x0F);

    /* Инициализация системы пользователей */
    user_system_init();
    user_create("danya", "Danya", "a78fdu3i", PERM_ADMIN | PERM_VGA | PERM_AUDIO | PERM_INPUT);
    user_create("julia", "Julia", "df09f9d8", PERM_VGA | PERM_AUDIO | PERM_INPUT);

    /* Инициализация клавиатуры */
    keyboard_init();

    /* Авто-логин для теста */
    vga_puts("\nAuto-login as danya...\n", 0x0B);
    user_login("danya", "a78fdu3i");

    /* Запуск оболочки */
    shell_run();
}
