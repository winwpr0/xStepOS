@echo off
REM Создаём образ диска с загрузчиком и ядром

REM 1. Копируем загрузчик в начало
copy /b boot\boot.bin disk.img > nul

REM 2. Добавляем ядро (начиная с сектора 2)
REM Ядро должно быть выровнено по 512 байт
fsutil file createnew kernel_padded.bin 512 > nul
copy /b kernel.bin >> kernel_padded.bin > nul

REM 3. Добавляем HPFS superblock (сектор 1)
REM ... (твой скрипт создания superblock)

echo Готово! disk.img создан.
pause
