/* multiboot.S - Multiboot 1 + PVH Note для QEMU 8+ */

/* Multiboot 1 заголовок */
.section .multiboot
.align 4
.long 0x1BADB002
.long 0x00000003
.long -(0x1BADB002 + 0x00000003)

/* PVH ELF Note */
.section .note.Xen, "a"
.align 4
.long 4                    /* namesz */
.long 4                    /* descsz */
.long 18                   /* type: XEN_ELFNOTE_PHYS32_ENTRY */
.ascii "Xen\0"             /* name */
.align 4
.long kernel_main          /* entry point */

/* Точка входа для линкера */
.global _start
_start:
    jmp kernel_main
