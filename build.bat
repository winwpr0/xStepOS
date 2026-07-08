@echo off
set GCC=C:\i686-elf-tools-windows\bin\i686-elf-gcc.exe
set AS=C:\i686-elf-tools-windows\bin\i686-elf-as.exe
set LD=C:\i686-elf-tools-windows\bin\i686-elf-ld.exe

echo [1/7] multiboot.S
"%AS%" --32 multiboot.S -o multiboot.o
echo [2/7] vga.c
"%GCC%" -m32 -ffreestanding -nostdlib -fno-builtin -c vga.c -o vga.o
echo [3/7] keyboard.c
"%GCC%" -m32 -ffreestanding -nostdlib -fno-builtin -c keyboard.c -o keyboard.o
echo [4/7] user.c
"%GCC%" -m32 -ffreestanding -nostdlib -fno-builtin -c user.c -o user.o
echo [5/7] shell.c
"%GCC%" -m32 -ffreestanding -nostdlib -fno-builtin -c shell.c -o shell.o
echo [6/7] kernel.c
"%GCC%" -m32 -ffreestanding -nostdlib -fno-builtin -c kernel.c -o kernel.o
echo [7/7] Linking...
"%LD%" -m elf_i386 -Ttext 0x100000 -e kernel_main -o kernel.bin multiboot.o kernel.o vga.o keyboard.o user.o shell.o
echo Done! kernel.bin created.
pause
