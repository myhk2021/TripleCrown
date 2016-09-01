echo off

del ..\BOOT_ROM_Update.bin

..\FILLFILE.exe ..\update0.bin 32768

..\binmerge.exe ..\update0.bin ..\MDK-ARM\BOOT_ROM\BOOT_ROM.bin ..\BOOT_ROM_Update.bin 0

del ..\update0.bin

