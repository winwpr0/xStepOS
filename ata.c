/* ata.c - Реализация ATA PIO драйвера */
#include "ata.h"
#include "io.h"

/* ATA порты (Primary channel) */
#define ATA_DATA      0x1F0
#define ATA_ERROR     0x1F1
#define ATA_SECCOUNT  0x1F2
#define ATA_LBA_LOW   0x1F3
#define ATA_LBA_MID   0x1F4
#define ATA_LBA_HIGH  0x1F5
#define ATA_DRIVE     0x1F6
#define ATA_STATUS    0x1F7
#define ATA_COMMAND   0x1F7

#define ATA_CMD_READ  0x20
#define ATA_SR_BSY    0x80
#define ATA_SR_DRQ    0x08
#define ATA_SR_ERR    0x01

void ata_init(void) {
    /* Сброс контроллера */
    outb(0x1F6, 0xA0);
    io_wait();
    outb(0x1F6, 0xB0);
    io_wait();
}

int ata_detect_drive(uint8_t drive) {
    /* drive: 0 = master, 1 = slave */
    outb(ATA_DRIVE, 0xA0 | (drive << 4));
    io_wait();
    outb(ATA_SECCOUNT, 0);
    outb(ATA_LBA_LOW, 0);
    outb(ATA_LBA_MID, 0);
    outb(ATA_LBA_HIGH, 0);
    outb(ATA_COMMAND, 0xEC); /* Identify */

    uint8_t status = inb(ATA_STATUS);
    if (status == 0) return 0; /* Нет диска */

        while (inb(ATA_STATUS) & ATA_SR_BSY);
        if (inb(ATA_STATUS) & ATA_SR_ERR) return 0;

        return 1;
}

int ata_read_sector(uint32_t lba, uint8_t* buffer) {
    /* Ждём готовности */
    while (inb(ATA_STATUS) & ATA_SR_BSY);

    /* Выбираем диск и режим LBA28 */
    outb(ATA_DRIVE, 0xE0 | ((lba >> 24) & 0x0F));
    outb(ATA_SECCOUNT, 1);
    outb(ATA_LBA_LOW,  lba & 0xFF);
    outb(ATA_LBA_MID,  (lba >> 8) & 0xFF);
    outb(ATA_LBA_HIGH, (lba >> 16) & 0xFF);
    outb(ATA_COMMAND, ATA_CMD_READ);

    io_wait();

    /* Ждём готовности и DRQ (данные готовы) */
    uint8_t status;
    int timeout = 100000;
    do {
        status = inb(ATA_STATUS);
        if (status & ATA_SR_ERR) return -1;
        timeout--;
    } while ((status & ATA_SR_BSY) && timeout > 0);

    if (timeout <= 0) return -1;
    if (!(status & ATA_SR_DRQ)) return -1;

    /* Читаем 256 слов = 512 байт */
    for (int i = 0; i < 256; i++) {
        uint16_t data = inw(ATA_DATA);
        buffer[i * 2]     = data & 0xFF;
        buffer[i * 2 + 1] = (data >> 8) & 0xFF;
    }

    return 0;
}
