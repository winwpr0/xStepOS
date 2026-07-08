@echo off
set HOME=C:\Users\winwpr0_

REM Создаём пустой диск 10MB
"C:\MinGW\msys\1.0\bin\bash.exe" -c "dd if=/dev/zero of=/c/Users/winwpr0_/Documents/xStepOS/disk.img bs=1M count=10"

REM Создаём HPFS superblock через echo с escape-последовательностями
"C:\MinGW\msys\1.0\bin\bash.exe" -c "echo -ne 'HPFS' > /c/Users/winwpr0_/Documents/xStepOS/hpfs.tmp"
"C:\MinGW\msys\1.0\bin\bash.exe" -c "echo -ne '\x00\x02' >> /c/Users/winwpr0_/Documents/xStepOS/hpfs.tmp"
"C:\MinGW\msys\1.0\bin\bash.exe" -c "echo -ne '\x08' >> /c/Users/winwpr0_/Documents/xStepOS/hpfs.tmp"
"C:\MinGW\msys\1.0\bin\bash.exe" -c "echo -ne '\x00' >> /c/Users/winwpr0_/Documents/xStepOS/hpfs.tmp"
"C:\MinGW\msys\1.0\bin\bash.exe" -c "echo -ne '\x00\x50\x00\x00' >> /c/Users/winwpr0_/Documents/xStepOS/hpfs.tmp"
"C:\MinGW\msys\1.0\bin\bash.exe" -c "echo -ne '\x20\x4E\x00\x00' >> /c/Users/winwpr0_/Documents/xStepOS/hpfs.tmp"
"C:\MinGW\msys\1.0\bin\bash.exe" -c "echo -ne '\x02\x00\x00\x00' >> /c/Users/winwpr0_/Documents/xStepOS/hpfs.tmp"
"C:\MinGW\msys\1.0\bin\bash.exe" -c "echo -ne '\x02\x00\x00\x00' >> /c/Users/winwpr0_/Documents/xStepOS/hpfs.tmp"
"C:\MinGW\msys\1.0\bin\bash.exe" -c "echo -ne '\x00\x40\x00\x00' >> /c/Users/winwpr0_/Documents/xStepOS/hpfs.tmp"

REM Записываем в сектор 1 (смещение 512 байт)
"C:\MinGW\msys\1.0\bin\bash.exe" -c "dd if=/c/Users/winwpr0_/Documents/xStepOS/hpfs.tmp of=/c/Users/winwpr0_/Documents/xStepOS/disk.img bs=1 seek=512 conv=notrunc"

REM Удаляем временный файл
"C:\MinGW\msys\1.0\bin\bash.exe" -c "rm -f /c/Users/winwpr0_/Documents/xStepOS/hpfs.tmp"

echo Готово! disk.img создан
pause
