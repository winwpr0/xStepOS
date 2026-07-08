/* hpfs.h - Структуры и функции HPFS */
#ifndef HPFS_H
#define HPFS_H

#include "types.h"

/* HPFS Superblock (сектор 1, 512 байт) */
typedef struct {
    char     magic[4];          /* "HPFS" */
    uint16_t sector_size;       /* Обычно 512 */
    uint8_t  sectors_per_cluster;
    uint8_t  reserved;
    uint32_t num_sectors;       /* Всего секторов на томе */
    uint32_t num_free_sectors;  /* Свободных секторов */
    uint32_t root_fnode_lbn;    /* LBA корневого каталога (FNODE) */
    uint32_t num_bands;
    uint32_t band_size;         /* Секторов в бэнде (обычно 16384) */
    uint32_t ndirblks;
    /* ... остальные поля ... */
} __attribute__((packed)) hpfs_super_t;

/* HPFS FNODE (File Node, 256 байт) */
typedef struct {
    uint16_t magic;             /* 0xF7E5 */
    uint16_t flags;
    uint32_t file_size;
    uint32_t creation_date;
    uint32_t ea_size;
    uint8_t  name_len;
    char     name[64];
    /* ... */
} __attribute__((packed)) hpfs_fnode_t;

int hpfs_mount(void);
void hpfs_print_info(void);

#endif
