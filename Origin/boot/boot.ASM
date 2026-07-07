format binary
use16
org 0x7c00

; --- ГЛОБАЛЬНЫЕ КОНСТАНТЫ ---
boot_drive equ 0x7c02     

jmp start

start:
    jmp 0x0000:.reload_cs

.reload_cs:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00        ; Стек ниже загрузчика

    mov [boot_drive], dl  ; Сохраняем номер диска
    sti                   ; Включаем прерывания обратно

    ; 1. Выводим стартовое сообщение первого сектора
    mov si, msg_boot
    call print_string

    ; 2. СТАДИЯ STAGE 1: Загружаем 16-й сектор (Stage 2) через LBA пакет в стеке
    sub sp, 16            ; Выделяем 16 байт под DAP
    mov bp, sp

    mov word [bp], 16     ; Размер пакета
    mov word [bp+2], 1    ; Читаем 1 сектор (где лежит hpfs.asm)
    mov word [bp+4], 0x9A00 ; Смещение буфера назначения (0x7C00 + 8192)
    mov word [bp+6], 0    ; Сегмент буфера (0x0000)
    mov dword [bp+8], 16  ; LBA адрес 16 (наш Stage 2)
    mov dword [bp+12], 0  ; Верхние 32-бита LBA

    mov dl, [boot_drive]  
    mov si, bp            ; DS:SI указывает на пакет в стеке
    mov ah, 0x42          ; Расширенное чтение LBA
    int 0x13
    
    jc .disk_error        ; Если BIOS вернул ошибку чтения
    add sp, 16            ; Восстанавливаем стек от DAP

    ; 3. Теперь, когда драйвер HPFS считан по адресу 0x9A00, вызываем его!
    call read_superblock
    call find_root_directory
    call find_file_kernel
    call load_kernel

    ; 4. Выводим маркер успешного завершения всего процесса
    mov si, msg_done
    call print_string

    jmp $                 ; Вечный цикл

.disk_error:
    add sp, 16            ; На всякий случай чистим стек перед выводом
    mov si, msg_err
    call print_string
    jmp $

; --- СИСТЕМНЫЕ ФУНКЦИИ ---
print_string:
    push ax
    push bx
.loop:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0e          
    mov bh, 0x00          
    int 0x10
    jmp .loop
.done:
    pop bx
    pop ax
    ret

; --- СЕКЦИЯ СТРОК И ДАННЫХ ---
msg_boot  db 'Starting from system:/', 13, 10, 0
msg_done  db 'Driver stubs executed successfully!', 13, 10, 0
msg_err   db 'Stage 2 Disk Read Error!', 13, 10, 0

; --- СИГНАТУРА ПЕРВОГО СЕКТОРА (MBR) ---
times 510-($-$$) db 0
dw 0xaa55

; =========================================================================
; --- СЕКЦИЯ ДИСКА ВНЕ ЗАГРУЗОЧНОГО СЕКТОРА ---
times 8192 - ($ - $$) db 0

; Сюда принудительно вставляется ваш hpfs.asm.
include 'hpfs.asm'

times 10240 - ($ - $$) db 0
