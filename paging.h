/* paging.h - Управление страничной памятью */
#ifndef PAGING_H
#define PAGING_H

#include "types.h"

/* Адреса */
#define KERNEL_VIRTUAL_BASE 0xC0000000
#define KERNEL_PAGE_NUMBER  (KERNEL_VIRTUAL_BASE >> 22)

/* Инициализация paging */
void paging_init(void);

/* Маппинг страниц */
void paging_map_page(uint32_t virtual_addr, uint32_t physical_addr, uint32_t flags);
void paging_unmap_page(uint32_t virtual_addr);

/* Флаги страниц */
#define PAGE_PRESENT    0x001
#define PAGE_WRITE      0x002
#define PAGE_USER       0x004
#define PAGE_4MB        0x080

#endif
