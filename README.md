# xStep OS

xStep OS — это экспериментальная операционная система, создаваемая с нуля на языке C и ассемблере. Проект создан Владиславом (winwpr0_) в рамках экосистемы Noverra. Цель — создать лёгкую, минималистичную и понятную ОС, сочетающую в себе философию Unix и эстетику Windows NT.

xStep OS (say as "cross-step") is an experimental operating system being built from scratch in C and assembly language. Created by Vladislav (winwpr0_) as part of the Noverra ecosystem. The goal is to create a lightweight, minimalist, and intuitive OS that combines Unix philosophy with Windows NT aesthetics.

## 🚀 Текущий статус / Current Status

- ✅ Загрузчик (multiboot.S) работает в QEMU
- ✅ Ядро на C компилируется и запускается
- ✅ Система пользователей (создание, логин, права доступа)
- ✅ VGA вывод с цветным текстом
- ✅ HPFS парсер (в разработке)
- ✅ ATA/IDE драйвер (PIO режим)
- ✅ Сборка через build.bat

- ✅ Bootloader (multiboot.S) works in QEMU
- ✅ C kernel compiles and runs
- ✅ User system (create, login, permissions)
- ✅ VGA text output with colors
- ✅ HPFS parser (in development)
- ✅ ATA/IDE driver (PIO mode)
- ✅ Build via build.bat

## ️ Технологии / Technologies

- **Языки / Languages:** C, Assembly (FASM)
- **Эмуляция / Emulation:** QEMU (i386)
- **Целевая архитектура / Target Arch:** x86 (32-bit)
- **Загрузчик / Bootloader:** Multiboot (QEMU direct boot)
- **Файловая система / FS:** HPFS (в разработке / in development)
- **Инструменты / Tools:** i686-elf-gcc, i686-elf-ld, FASM (для boot.asm)

## 📂 Структура проекта / Project Structure

```
xStepOS/
├── kernel.c          # Точка входа ядра
├── vga.c / vga.h     # VGA драйвер (текстовый режим)
├── user.c / user.h   # Система пользователей
├── encoding.c / encoding.h  # Кодировки (кириллица, греческий)
├── font.c / font.h   # Загрузка шрифтов VGA (для Grafix)
├── xstep_font.c      # Массив шрифта Terminus
├── ata.c / ata.h     # ATA/IDE драйвер
├── hpfs.c / hpfs.h   # HPFS парсер
├── io.h              # Порты ввода-вывода
├── types.h           # Базовые типы
├── multiboot.S       # Multiboot заголовок
├── build.bat         # Скрипт сборки
├── run.bat           # Запуск в QEMU
├── clean.bat         # Очистка
└── Origin/boot/      # Альтернативный загрузчик (FASM)
```

## 🔧 Сборка и запуск / Build & Run

### Требования / Requirements:
- Windows 10/11
- [i686-elf-tools]([https://github.com/lordmilko/i686-elf-tools/releases]) (gcc, ld, as)
- QEMU for Windows

### Сборка / Build:
```cmd
build.bat
```

### Запуск / Run:
```cmd
run.bat
```

### Очистка / Clean:
```cmd
clean.bat
```

## 👥 Система пользователей / User System

xStep OS поддерживает многопользовательский режим с правами доступа:

```c
user_create("danya", "Danya", "password", PERM_ADMIN | PERM_VGA);
user_create("julia", "Julia", "password", PERM_VGA);
```

**Права / Permissions:**
- `PERM_ADMIN` — администратор
- `PERM_VGA` — доступ к видео
- `PERM_AUDIO` — доступ к аудио
- `PERM_INPUT` — доступ к вводу
- `PERM_CMD_ROOT` — root-команды

## ️ Дорожная карта / Roadmap

- [ ] OMC-SH (командная оболочка)
- [ ] Драйвер клавиатуры (PS/2)
- [ ] Paging (виртуальная память)
- [ ] Прерывания (IDT)
- [ ] Аллокатор памяти (kmalloc/kfree)
- [ ] Многозадачность
- [ ] Grafix (графическая надстройка)

## 📜 Лицензия / License

Проект распространяется под лицензией GNU GPL v3.  
This project is licensed under the GNU GPL v3 license.

---

Сделано с 🧡 в рамках Noverra OS Lab.  
Made with 🧡 in the Noverra OS Lab.
