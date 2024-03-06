@echo off
if not exist .\x64\NUL mkdir .\x64
windres swag.rc -O coff -o x64/swag.res
gcc swag.c -o x64/swag.exe x64/swag.res -mwindows -Oz -s -fdata-sections -ffunction-sections -Wl,--gc-sections -fno-ident -fno-asynchronous-unwind-tables -Wall -Wextra -static
