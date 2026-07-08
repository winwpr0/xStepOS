/* hpfs.c - Парсер HPFS */
#include "hpfs.h"
#include "ata.h"
#include "vga.h"

static hpfs_super_t superblock;
static int hpfs_mounted = 0;

/* Вывод числа в hex */
static void print_hex(uint8_t byte, uint8_t color) {
    const char* hex_chars = "0123456789ABCDEF";
    vga_putc(hex_chars[(byte >> 4) & 0x0F], color);
    vga_putc(hex_chars[byte & 0x0F], color);
}

/* Вывод числа в десятичном виде */
static void print_number(uint32_t n, uint8_t color) {
    char buf[12];
    int i = 0;
    if (n == 0) {
        vga_putc('0', color);
        return;
    }
    while (n > 0) {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }
    while (i > 0) {
        vga_putc(buf[--i], color);
    }
}

/* Читаем и выводим первые 32 байта сектора 1 для отладки */
static void debug_sector1(void) {
    uint8_t buffer[512];

    vga_puts("[DEBUG] Sector 1 raw data (first 32 bytes):", 0x07);
    vga_newline(0x07);

    if (ata_read_sector(1, buffer) != 0) {
        vga_puts("[DEBUG] FAILED to read sector 1!", 0x0C);
        vga_newline(0x0C);
        return;
    }

    vga_puts("[DEBUG] ", 0x08);
    for (int i = 0; i < 32; i++) {
        print_hex(buffer[i], 0x08);
        vga_putc(' ', 0x08);
        if ((i + 1) % 16 == 0) {
            vga_newline(0x08);
            if (i < 31) {
                vga_puts("[DEBUG] ", 0x08);
            }
        }
    }
    vga_newline(0x07);

    /* Показываем как ASCII */
    vga_puts("[DEBUG] ASCII: ", 0x08);
    for (int i = 0; i < 16; i++) {
        if (buffer[i] >= 32 && buffer[i] < 127) {
            vga_putc(buffer[i], 0x08);
        } else {
            vga_putc('.', 0x08);
        }
    }
    vga_newline(0x07);
}

int hpfs_mount(void) {
    uint8_t buffer[512];

    /* ОТЛАДКА: показываем что в секторе 1 */
    debug_sector1();

    /* Читаем сектор 1 — там лежит superblock HPFS */
    if (ata_read_sector(1, buffer) != 0) {
        return -1;
    }

    /* Копируем superblock */
    for (int i = 0; i < (int)sizeof(hpfs_super_t); i++) {
        ((uint8_t*)&superblock)[i] = buffer[i];
    }

    /* Проверяем магическое число "HPFS" */
    if (superblock.magic[0] != 'H' ||
        superblock.magic[1] != 'P' ||
        superblock.magic[2] != 'F' ||
        superblock.magic[3] != 'S') {
        return -1; /* Это не HPFS */
        }

        hpfs_mounted = 1;
    return 0;
}

void hpfs_print_info(void) {
    if (!hpfs_mounted) {
        vga_puts("[HPFS] File system not mounted!", 0x0C);
        vga_newline(0x0C);
        return;
    }

    vga_puts("=== HPFS File System Info ===", 0x0E);
    vga_newline(0x0E);

    vga_puts("Magic:        ", 0x0F);
    vga_putc(superblock.magic[0], 0x0F);
    vga_putc(superblock.magic[1], 0x0F);
    vga_putc(superblock.magic[2], 0x0F);
    vga_putc(superblock.magic[3], 0x0F);
    vga_newline(0x0F);

    vga_puts("Sector size:  ", 0x0F);
    print_number(superblock.sector_size, 0x0F);
    vga_puts(" bytes", 0x0F);
    vga_newline(0x0F);

    vga_puts("Sectors/cluster: ", 0x0F);
    print_number(superblock.sectors_per_cluster, 0x0F);
    vga_newline(0x0F);

    vga_puts("Total sectors: ", 0x0F);
    print_number(superblock.num_sectors, 0x0F);
    vga_newline(0x0F);

    vga_puts("Free sectors:  ", 0x0F);
    print_number(superblock.num_free_sectors, 0x0F);
    vga_newline(0x0F);

    vga_puts("Root FNODE LBA: ", 0x0F);
    print_number(superblock.root_fnode_lbn, 0x0F);
    vga_newline(0x0F);

    vga_puts("Num bands:     ", 0x0F);
    print_number(superblock.num_bands, 0x0F);
    vga_newline(0x0F);

    vga_puts("Band size:     ", 0x0F);
    print_number(superblock.band_size, 0x0F);
    vga_newline(0x0F);

    vga_puts("Volume size:   ~", 0x0A);
    print_number(superblock.num_sectors / 2048, 0x0A);
    vga_puts(" MB", 0x0A);
    vga_newline(0x0A);

    vga_puts("=================================", 0x0E);
    vga_newline(0x0E);
}
