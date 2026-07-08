/* kernel.c - Первое ядро xStep OS
 * Версия: 26.1a / a1.0_build1
 */

/* 1. Мультизагрузочный заголовок для GRUB */
__asm__(
    ".section .multiboot\n"
    ".align 4\n"
    ".long 0x1BADB002\n"           /* Магическое число */
    ".long 0x03\n"                 /* Флаги */
    ".long -(0x1BADB002 + 0x03)\n" /* Контрольная сумма */
    ".section .text\n"
);

/* 2. Точка входа в ядро */
void kernel_main(void) {
    /* 3. Выводим приветствие в видеопамять (0xB8000) */
    volatile char* video = (volatile char*)0xB8000;
    const char* msg = "                                                                                                                                                                                                                                                                                                                                                                                                                            Starting xStep...                                                                                                                                                                                                        ";
    int i = 0;

    while (msg[i] != '\0') {
        video[i * 2]     = msg[i];   /* Символ */
        video[i * 2 + 1] = 0x0F;     /* Белый текст на чёрном фоне */
        i++;
    }

    /* 4. Останавливаемся (пока нет обработки прерываний) */
    while (1) {
        __asm__ volatile ("hlt");
    }
}
