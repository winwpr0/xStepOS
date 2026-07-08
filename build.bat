@echo off
REM === xStep OS Build Script (C + C++) ===

set GCC=C:\i686-elf-tools-windows\bin\i686-elf-gcc.exe
set GPP=C:\i686-elf-tools-windows\bin\i686-elf-g++.exe
set AS=C:\i686-elf-tools-windows\bin\i686-elf-as.exe
set LD=C:\i686-elf-tools-windows\bin\i686-elf-ld.exe

echo [1/8] multiboot.S
"%AS%" --32 multiboot.S -o multiboot.o

echo [2/8] vga.c
"%GCC%" -m32 -ffreestanding -nostdlib -fno-builtin -c vga.c -o vga.o

echo [3/8] keyboard.c
"%GCC%" -m32 -ffreestanding -nostdlib -fno-builtin -c keyboard.c -o keyboard.o

echo [4/8] user.c
"%GCC%" -m32 -ffreestanding -nostdlib -fno-builtin -c user.c -o user.o

echo [5/8] shell.cpp
"%GPP%" -m32 -ffreestanding -nostdlib -fno-builtin -fno-exceptions -fno-rtti -c shell.cpp -o shell.o

echo [6/8] kernel.cpp
"%GPP%" -m32 -ffreestanding -nostdlib -fno-builtin -fno-exceptions -fno-rtti -c kernel.cpp -o kernel.o

echo [7/8] crt0.cpp
"%GPP%" -m32 -ffreestanding -nostdlib -fno-builtin -fno-exceptions -fno-rtti -c crt0.cpp -o crt0.o

echo [8/8] Linking...
"%LD%" -m elf_i386 -Ttext=0x100000 -e kernel_main -o kernel.bin multiboot.o kernel.o vga.o keyboard.o user.o shell.o crt0.o

echo Done! kernel.bin created.
pause
