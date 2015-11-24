@echo off

set prefix=i686-w64-mingw32-

:: To compile 64-bit, uncomment this:
:: set prefix=x86_64-w64-mingw32-

%prefix%gcc -o replace-notepad.exe replace-notepad.c -municode -mwindows -lshlwapi -O2 -s
