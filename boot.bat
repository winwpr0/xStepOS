@echo off
set FASM=C:\FASM\fasm.exe
echo Сборка загрузчика...
"%FASM%" boot\boot.asm boot\boot.bin
if errorlevel 1 (
    echo Ошибка!
) else (
    echo Готово! boot.bin создан.
)
pause
