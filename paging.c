/* paging.c - Реализация paging */
#include "paging.h"
#include "vga.h"

/* Page Directory и Page Tables (выравниваем по 4KB) */
__attribute__((aligned(4096)))
uint32_t page_directory[1024] = {0};

__attribute__((aligned(4096)))
uint32_t page_tables[1024 * 1024] = {0}; /* 1024 таблицы по 1024 записей */

/* Временная страница для identity mapping */
__attribute__((aligned(4096)))
uint32_t first_page_table[1024] = {0};

void paging_init(void) {
    xstep_puts("[PAGING] Initializing...\n", 0x0B);

    /* Identity map первые 4MB (0x00000000 - 0x003FFFFF) */
    /* Это нужно, чтобы процессор не упал после включения paging */
    for (int i = 0; i < 1024; i++) {
        first_page_table[i] = (i * 0x1000) | PAGE_PRESENT | PAGE_WRITE;
    }

    /* Маппим первые 4MB по адресу 0xC0000000 (Higher Half) */
    /* Это значит: виртуальный адрес 0xC0000000 -> физический 0x00000000 */
    for (int i = 0; i < 1024; i++) {
        page_tables[i] = (i * 0x1000) | PAGE_PRESENT | PAGE_WRITE;
    }

    /* Заполняем Page Directory */
    page_directory[0] = (uint32_t)first_page_table | PAGE_PRESENT | PAGE_WRITE;
    page_directory[KERNEL_PAGE_NUMBER] = (uint32_t)page_tables | PAGE_PRESENT | PAGE_WRITE;

    /* Загружаем Page Directory в CR3 */
    __asm__ volatile("mov %0, %%cr3" :: "r"(page_directory));

    /* Включаем paging в CR0 */
    uint32_t cr0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000; /* PG bit */
    __asm__ volatile("mov %0, %%cr0" :: "r"(cr0));

    xstep_puts("[PAGING] Enabled! Higher Half at 0xC0000000\n", 0x0A);
}

void paging_map_page(uint32_t virtual_addr, uint32_t physical_addr, uint32_t flags) {
    uint32_t pd_index = virtual_addr >> 22;
    uint32_t pt_index = (virtual_addr >> 12) & 0x3FF;

    /* TODO: Динамическое создание page tables */
    /* Пока просто маппим в первую таблицу */
    if (pd_index < 1024) {
        page_tables[pt_index] = (physical_addr & 0xFFFFF000) | flags | PAGE_PRESENT;
    }
}

void paging_unmap_page(uint32_t virtual_addr) {
    uint32_t pt_index = (virtual_addr >> 12) & 0x3FF;
    page_tables[pt_index] = 0;

    /* Инвалидируем TLB */
    __asm__ volatile("invlpg (%0)" :: "r"(virtual_addr) : "memory");
}
