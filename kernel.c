/* kernel.c - xStep OS */

#include "vga.h"
#include "user.h"

void kernel_main(void) {
    vga_clear(0x00);

    vga_puts("xStep OS - User System Test\n", 0x0F);
    vga_puts("===========================\n", 0x0A);
    vga_puts("\n", 0x0F);

    user_system_init();
    vga_puts("--- Setup ---\n", 0x0B);

    user_create("danya", "Danya", "a78fdu3i", PERM_ADMIN | PERM_VGA | PERM_AUDIO | PERM_INPUT);
    user_create("julia", "Julia", "df09f9d8", PERM_VGA | PERM_AUDIO | PERM_INPUT);

    vga_puts("\n--- Login Test ---\n", 0x0B);

    vga_puts("Login: danya / wrongpass\n", 0x07);
    user_login("danya", "wrongpass");

    vga_puts("Login: danya / a78fdu3i\n", 0x07);
    user_t* u1 = user_login("danya", "a78fdu3i");

    user_t* current = user_get_current();
    if (current) {
        vga_puts("Current: ", 0x0F);
        vga_puts(current->display_name, 0x0E);
        vga_puts("\n", 0x0F);
    }

    vga_puts("\nSystem halted.\n", 0x07);
    while (1) {
        __asm__ volatile ("hlt");
    }
}
