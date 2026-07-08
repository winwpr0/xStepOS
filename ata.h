/* ata.h - Драйвер ATA/IDE в режиме PIO */
#ifndef ATA_H
#define ATA_H

#include "types.h"

void ata_init(void);
int ata_read_sector(uint32_t lba, uint8_t* buffer);
int ata_detect_drive(uint8_t drive);

#endif
