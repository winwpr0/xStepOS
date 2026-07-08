; boot.asm - Простой загрузчик xStep OS
use16
org 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    ; Вывод сообщения
    mov si, msg
    call print

    ; Загрузка ядра (сектора 2-17, 16 секторов = 8KB)
    mov ah, 0x02
    mov al, 16
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [boot_drive]
    mov bx, 0x1000
    int 0x13
    jc disk_err

    ; Переход в Protected Mode
    cli
    lgdt [gdt_desc]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:0x10000

disk_err:
    mov si, err_msg
    call print
    jmp $

print:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print
.done:
    ret

msg db 'xStep Boot...', 13, 10, 0
err_msg db 'Disk Error!', 0
boot_drive db 0

; GDT
gdt_start:
    dq 0
    dw 0xFFFF, 0, 0, 10011010b, 11001111b, 0
    dw 0xFFFF, 0, 0, 10010010b, 11001111b, 0
gdt_end:

gdt_desc:
    dw gdt_end - gdt_start - 1
    dd gdt_start

times 510-($-$$) db 0
dw 0xAA55
