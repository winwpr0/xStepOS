@echo off
REM === xStep OS Build Script ===

set GCC=C:\i686-elf-tools-windows\bin\i686-elf-gcc.exe
set AS=C:\i686-elf-tools-windows\bin\i686-elf-as.exe
set LD=C:\i686-elf-tools-windows\bin\i686-elf-ld.exe

echo [1/5] multiboot.S
"%AS%" --32 multiboot.S -o multiboot.o
if errorlevel 1 goto error

echo [2/5] vga.c
"%GCC%" -m32 -ffreestanding -nostdlib -fno-builtin -c vga.c -o vga.o
if errorlevel 1 goto error

echo [3/5] user.c
"%GCC%" -m32 -ffreestanding -nostdlib -fno-builtin -c user.c -o user.o
if errorlevel 1 goto error

echo [4/5] kernel.c
"%GCC%" -m32 -ffreestanding -nostdlib -fno-builtin -c kernel.c -o kernel.o
if errorlevel 1 goto error

echo [5/5] Linking...
"%LD%" -m elf_i386 -Ttext 0x100000 -e kernel_main -o kernel.bin multiboot.o kernel.o vga.o user.o
if errorlevel 1 goto error

echo Done! kernel.bin created.
goto end

:error
echo.
echo !!! BUILD ERROR !!!

:end
pause
