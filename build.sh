windres swag.rc -O coff -o swag.res
gcc swag.c -o swag.exe swag.res -mwindows -Oz -s -fdata-sections -ffunction-sections -Wl,--gc-sections -fno-ident -fno-asynchronous-unwind-tables -Wall -Wextra -static