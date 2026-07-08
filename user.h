/* user.h - Система пользователей xStep OS */
#ifndef USER_H
#define USER_H

#include "types.h"

#define MAX_USERS 16
#define MAX_STR 64

#define PERM_ADMIN    0x01
#define PERM_VGA      0x02
#define PERM_AUDIO    0x04
#define PERM_INPUT    0x08
#define PERM_CMD_ROOT 0x10

typedef struct {
    char username[MAX_STR];
    char display_name[MAX_STR];
    char password[MAX_STR];
    uint32_t permissions;
    int is_logged_in;
} user_t;

void user_system_init(void);
int user_create(const char* username, const char* display_name, const char* password, uint32_t perms);
user_t* user_login(const char* username, const char* password);
void user_logout(user_t* user);
user_t* user_get_current(void);

#endif
