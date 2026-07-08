# xStep OS

**xStep OS** — это экспериментальная операционная система, создаваемая с нуля на языке C и ассемблере. 
Проект создан Владиславом (winwpr0_) в рамках экосистемы Noverra.
Цель — создать лёгкую, минималистичную и понятную ОС, сочетающую в себе философию Unix и эстетику Windows NT.

**xStep OS (say as "cross-step")** is an experimental operating system being built from scratch in C and assembly language.
Created by Vladislav (winwpr0_) as part of the Noverra ecosystem.
The goal is to create a lightweight, minimalist, and intuitive OS that combines Unix philosophy with Windows NT aesthetics.

---

## 🚀 Текущий статус / Current Status

- ✅ Загрузчик (FASM) работает и выводит приветственное сообщение.
- ✅ Ядро на C компилируется и запускается в QEMU.
- ✅ Поддержка мультизагрузки (GRUB / Windows DualBoot) на реальном оборудовании.
- ✅ Базовая структура проекта готова к расширению.
- ✅ Bootloader (FASM) works and outputs a welcome message.
- ✅ C kernel compiles and runs in QEMU.
- ✅ Multiboot support (GRUB / Windows DualBoot) on real hardware.
- ✅ Basic project structure is ready for expansion.

---

## 🛠️ Технологии / Technologies

- **Языки / Languages:** C, Assembly (FASM), Vala (планируется / planned).
- **Эмуляция / Emulation:** QEMU.
- **Целевая архитектура / Target Arch:** x86 (32-bit), позже x86-64 и ARM.
- **Загрузчик / Bootloader:** GRUB (в будущем свой / custom in the future).
- **Файловая система / FS:** HPFS (в планах / planned).

---

## 📂 Структура проекта / Project Structure

```text
xStepOS/
├── boot/            # Исходный код загрузчика (FASM)
├── kernel/          # Ядро на C
├── system/          # Системные скрипты и конфигурации
├── build/           # Скомпилированные файлы (kernel.bin, boot.bin)
└── docs/            # Документация (планируется)
```

---

## 🔧 Сборка и запуск / Build & Run

**Для запуска в QEMU:**
```bash
gcc -m32 -ffreestanding -nostdlib -fno-builtin -c kernel/kernel.c -o kernel.o
ld -m elf_i386 -Ttext 0x100000 -o kernel.bin kernel.o
qemu-system-i386 -kernel kernel.bin
```

---

## 📜 Лицензия / License

Проект распространяется под лицензией **GNU GPL v3**.
This project is licensed under the **GNU GPL v3** license.

---

Сделано с 🧡 в рамках **Noverra OS Lab**.
Made with 🧡 in the **Noverra OS Lab**.
