/* shell.h - OMC-SH (OpenMc Shell) */
#ifndef SHELL_H
#define SHELL_H

#include "types.h"

#define SHELL_MAX_CMD_LEN 256
#define SHELL_MAX_ARGS 16

/* Запуск оболочки */
void shell_run(void);

#endif
