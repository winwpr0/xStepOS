/* shell.c - OMC-SH (OpenMc Shell) */
#include "shell.h"
#include "vga.h"
#include "keyboard.h"
#include "user.h"

/* Простая функция сравнения строк */
static int str_cmp(const char* a, const char* b) {
    while (*a && *b) {
        if (*a != *b) return 1;
        a++; b++;
    }
    return (*a != *b);
}

/* Парсинг командной строки */
static int parse_command(char* input, char** argv) {
    int argc = 0;
    char* p = input;

    while (*p && argc < 16) {
        while (*p == ' ') p++;
        if (*p == '\0') break;
        argv[argc++] = p;
        while (*p && *p != ' ') p++;
        if (*p == ' ') {
            *p = '\0';
            p++;
        }
    }

    return argc;
}

/* Встроенная команда: help */
static void cmd_help(void) {
    vga_puts("OMC-SH Commands:\n", 0x0F);
    vga_puts("  help     - Show this help\n", 0x07);
    vga_puts("  clear    - Clear screen\n", 0x07);
    vga_puts("  echo     - Print text\n", 0x07);
    vga_puts("  whoami   - Show current user\n", 0x07);
    vga_puts("  logout   - Logout current user\n", 0x07);
    vga_puts("  shutdown - Halt system\n", 0x07);
}

/* Встроенная команда: clear */
static void cmd_clear(void) {
    vga_clear(0x00);
}

/* Встроенная команда: echo */
static void cmd_echo(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        vga_puts(argv[i], 0x0F);
        if (i < argc - 1) vga_puts(" ", 0x0F);
    }
    vga_puts("\n", 0x0F);
}

/* Встроенная команда: whoami */
static void cmd_whoami(void) {
    user_t* current = user_get_current();
    if (current) {
        vga_puts(current->display_name, 0x0E);
        vga_puts(" (", 0x0F);
        vga_puts(current->username, 0x07);
        vga_puts(")\n", 0x0F);
    } else {
        vga_puts("Not logged in\n", 0x0C);
    }
}

/* Встроенная команда: logout */
static void cmd_logout(void) {
    user_t* current = user_get_current();
    if (current) {
        user_logout(current);
        vga_puts("Logged out.\n", 0x0A);
    } else {
        vga_puts("No user logged in.\n", 0x0C);
    }
}

/* Встроенная команда: shutdown */
static void cmd_shutdown(void) {
    vga_puts("System halted.\n", 0x0C);
    while (1) {
        __asm__ volatile("hlt");
    }
}

/* Выполнение команды */
static void execute_command(int argc, char** argv) {
    if (argc == 0) return;

    char* cmd = argv[0];

    if (str_cmp(cmd, "help") == 0) {
        cmd_help();
    } else if (str_cmp(cmd, "clear") == 0) {
        cmd_clear();
    } else if (str_cmp(cmd, "echo") == 0) {
        cmd_echo(argc, argv);
    } else if (str_cmp(cmd, "whoami") == 0) {
        cmd_whoami();
    } else if (str_cmp(cmd, "logout") == 0) {
        cmd_logout();
    } else if (str_cmp(cmd, "shutdown") == 0) {
        cmd_shutdown();
    } else {
        vga_puts("Unknown command: ", 0x0C);
        vga_puts(cmd, 0x0C);
        vga_puts("\n", 0x0C);
    }
}

/* Главный цикл оболочки */
void shell_run(void) {
    char input[256];
    char* argv[16];

    vga_puts("\nOMC-SH v1.0 - xStep OS Shell\n", 0x0B);
    vga_puts("Type 'help' for available commands.\n\n", 0x07);

    while (1) {
        user_t* current = user_get_current();
        if (current) {
            vga_puts(current->username, 0x0E);
        } else {
            vga_puts("guest", 0x07);
        }
        vga_puts(":/ > ", 0x0F);

        keyboard_readline(input, 256);
        int argc = parse_command(input, argv);
        execute_command(argc, argv);
    }
}
