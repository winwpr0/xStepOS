/* user.c - Реализация системы пользователей */
#include "user.h"
#include "vga.h"

static user_t users[MAX_USERS];
static int user_count = 0;
static user_t* current_user = NULL;

static int str_len(const char* s) {
    int len = 0;
    while (s[len]) len++;
    return len;
}

static int str_cmp(const char* a, const char* b) {
    while (*a && *b) {
        if (*a != *b) return 1;
        a++; b++;
    }
    return (*a != *b);
}

static void str_cpy(char* dest, const char* src, int max_len) {
    int i = 0;
    while (src[i] && i < max_len - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void user_system_init(void) {
    user_count = 0;
    current_user = NULL;
    vga_puts("[USER] User system initialized\n", 0x0B);
}

int user_create(const char* username, const char* display_name, const char* password, uint32_t perms) {
    if (user_count >= MAX_USERS) {
        vga_puts("[USER] ERROR: User table full!\n", 0x0C);
        return -1;
    }

    user_t* u = &users[user_count];
    str_cpy(u->username, username, MAX_STR);
    str_cpy(u->display_name, display_name, MAX_STR);
    str_cpy(u->password, password, MAX_STR);
    u->permissions = perms;
    u->is_logged_in = 0;

    user_count++;

    vga_puts("[USER] Created user: ", 0x0A);
    vga_puts(u->display_name, 0x0E);
    vga_puts(" (", 0x0F);
    vga_puts(u->username, 0x07);
    vga_puts(")\n", 0x0F);

    return 0;
}

user_t* user_login(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (str_cmp(users[i].username, username) == 0) {
            if (str_cmp(users[i].password, password) == 0) {
                users[i].is_logged_in = 1;
                current_user = &users[i];

                vga_puts("[USER] Login successful: ", 0x0A);
                vga_puts(users[i].display_name, 0x0E);
                vga_puts("\n", 0x0F);
                return &users[i];
            } else {
                vga_puts("[USER] ERROR: Wrong password!\n", 0x0C);
                return NULL;
            }
        }
    }
    vga_puts("[USER] ERROR: User not found!\n", 0x0C);
    return NULL;
}

void user_logout(user_t* user) {
    if (user) {
        user->is_logged_in = 0;
        if (current_user == user) {
            current_user = NULL;
        }
        vga_puts("[USER] Logged out: ", 0x0A);
        vga_puts(user->display_name, 0x0E);
        vga_puts("\n", 0x0F);
    }
}

user_t* user_get_current(void) {
    return current_user;
}
