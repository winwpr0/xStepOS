; hpfs.asm - Драйвер HPFS для загрузчика xStep

boot_drive     equ 0x7c02     ; Адрес переменной номера диска
BUFFER_ADDR    equ 0x9000     ; Адрес временного буфера

read_sector:
    ; Передавать: EAX = LBA сектор, BX = смещение буфера памяти
    push bx
    push cx
    push dx
    push si
    push bp

    ; Создаём DAP (Disk Address Packet) на стеке
    sub sp, 16                
    mov bp, sp

    mov word [bp], 16         ; Размер пакета (0x10)
    mov word [bp+2], 1        ; Читаем 1 сектор
    mov [bp+4], bx            ; Смещение буфера (из регистра BX)
    mov word [bp+6], 0        ; Сегмент буфера (0x0000)
    mov dword [bp+8], eax     ; LBA-адрес (нижние 32 бита из EAX)
    mov dword [bp+12], 0      ; LBA-адрес (верхние 32 бита)

    ; Вызываем int 0x13, функция 0x42
    mov dl, [boot_drive]      ; Теперь FASM отлично знает, что это адрес 0x7C02!
    mov si, bp                ; DS:SI указывает на DAP
    mov ah, 0x42
    int 0x13
    
    jc .read_error            ; Ошибка чтения диска

    add sp, 16                ; Освобождаем 16 байт из стека
    
    pop bp
    pop si
    pop dx
    pop cx
    pop bx
    ret

.read_error:
    jmp $

read_superblock:
    mov eax, 16
    mov bx, BUFFER_ADDR       
    call read_sector
    ret

find_root_directory:
    ret

find_file_kernel:
    ret

load_kernel:
    ret
