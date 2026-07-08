@echo off
REM === xStep OS Build Script ===

set GCC=C:\i686-elf-tools-windows\bin\i686-elf-gcc.exe
set LD=C:\i686-elf-tools-windows\bin\i686-elf-ld.exe

echo [1/3] Compiling kernel.c...
"%GCC%" -m32 -ffreestanding -nostdlib -fno-builtin -c kernel.c -o kernel.o
if errorlevel 1 goto error

echo [2/3] Linking kernel.o -^> kernel.bin...
"%LD%" -m elf_i386 -Ttext 0x100000 -e kernel_main -o kernel.bin kernel.o
if errorlevel 1 goto error

echo [3/3] Kernel builded
goto end

:error
echo.
echo !!! ERROR WHILE BUILDING !!!

:end
pause
