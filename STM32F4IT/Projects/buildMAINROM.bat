rem echo off

del ..\MAIN_ROM_Update.bin

..\FILLFILE.exe ..\update0.bin 65536

..\binmerge.exe ..\update0.bin ..\MDK-ARM\MAIN_ROM\MAIN_ROM.bin ..\MAIN_ROM_Update.bin 0

del ..\update0.bin

