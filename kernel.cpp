/* kernel.cpp - Точка входа xStep OS */

#include "vga.h"
#include "user.h"
#include "keyboard.h"

namespace omc {
    void shell_run(void);
}

extern "C" void kernel_main(void) {
    vga_clear(0x00);

    vga_puts("xStep OS - Starting (C++)...\n", 0x0F);

    user_system_init();
    user_create("danya", "Danya", "a78fdu3i",
                PERM_ADMIN | PERM_VGA | PERM_AUDIO | PERM_INPUT);
    user_create("julia", "Julia", "df09f9d8",
                PERM_VGA | PERM_AUDIO | PERM_INPUT);

    keyboard_init();

    vga_puts("\nAuto-login as danya...\n", 0x0B);
    user_login("danya", "a78fdu3i");

    omc::shell_run();
}
