/* shell.cpp - OMC-SH на C++ */

#include "vga.h"
#include "keyboard.h"
#include "user.h"

namespace omc {

    /* Класс команды */
    class Command {
    public:
        const char* name;
        void (*handler)(int argc, char** argv);
    };

    /* Вспомогательная функция */
    static int str_cmp(const char* a, const char* b) {
        while (*a && *b) {
            if (*a != *b) return 1;
            a++; b++;
        }
        return (*a != *b);
    }

    /* Обработчики команд */
    static void cmd_help(int argc, char** argv) {
        (void)argc; (void)argv;
        vga_puts("OMC-SH v1.0 Commands:\n", 0x0F);
        vga_puts("  help     - Show help\n", 0x07);
        vga_puts("  clear    - Clear screen\n", 0x07);
        vga_puts("  echo     - Print text\n", 0x07);
        vga_puts("  whoami   - Current user\n", 0x07);
        vga_puts("  logout   - Logout\n", 0x07);
        vga_puts("  shutdown - Halt system\n", 0x07);
    }

    static void cmd_clear(int argc, char** argv) {
        (void)argc; (void)argv;
        vga_clear(0x00);
    }

    static void cmd_echo(int argc, char** argv) {
        for (int i = 1; i < argc; i++) {
            vga_puts(argv[i], 0x0F);
            if (i < argc - 1) vga_puts(" ", 0x0F);
        }
        vga_puts("\n", 0x0F);
    }

    static void cmd_whoami(int argc, char** argv) {
        (void)argc; (void)argv;
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

    static void cmd_logout(int argc, char** argv) {
        (void)argc; (void)argv;
        user_t* current = user_get_current();
        if (current) {
            user_logout(current);
            vga_puts("Logged out.\n", 0x0A);
        } else {
            vga_puts("No user logged in.\n", 0x0C);
        }
    }

    static void cmd_shutdown(int argc, char** argv) {
        (void)argc; (void)argv;
        vga_puts("System halted.\n", 0x0C);
        while (1) {
            __asm__ volatile("hlt");
        }
    }

    /* Таблица команд */
    static Command commands[] = {
        {"help",     cmd_help},
        {"clear",    cmd_clear},
        {"echo",     cmd_echo},
        {"whoami",   cmd_whoami},
        {"logout",   cmd_logout},
        {"shutdown", cmd_shutdown},
        {nullptr,    nullptr}
    };

    /* Парсинг командной строки */
    static int parse_command(char* input, char** argv, int max_args) {
        int argc = 0;
        char* p = input;

        while (*p && argc < max_args) {
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

    /* Выполнение команды */
    static void execute(int argc, char** argv) {
        if (argc == 0) return;

        for (int i = 0; commands[i].name != nullptr; i++) {
            if (str_cmp(argv[0], commands[i].name) == 0) {
                commands[i].handler(argc, argv);
                return;
            }
        }

        vga_puts("Unknown command: ", 0x0C);
        vga_puts(argv[0], 0x0C);
        vga_puts("\n", 0x0C);
    }

    /* Главный цикл оболочки */
    void shell_run(void) {
        char input[256];
        char* argv[16];

        vga_puts("\nOMC-SH v1.0 - xStep OS Shell (C++)\n", 0x0B);
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
            int argc = parse_command(input, argv, 16);
            execute(argc, argv);
        }
    }

} /* namespace omc */
