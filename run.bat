@echo off
REM === xStep OS Run Script ===
REM Запуск ядра в QEMU с подключением диска disk.img

"C:\Program Files\qemu\qemu-system-i386.exe" ^
    -kernel kernel.bin ^
    -hda disk.img ^
    -m 64 ^
    -name "xStep OS"

pause
