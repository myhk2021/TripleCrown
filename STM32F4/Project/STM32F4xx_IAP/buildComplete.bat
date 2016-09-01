echo off

del ..\BOOT_RAM_Update.bin

..\FILLFILE.exe ..\update0.bin 32768

..\binmerge.exe ..\update0.bin ..\MDK-ARM\BOOT_RAM\BOOT_RAM.bin ..\BOOT_RAM_Update.bin 0

del ..\update0.bin

del ..\STM32F407Complete.bin

..\FILLFILE.exe ..\update0.bin 131072

..\binmerge.exe ..\update0.bin ..\MDK-ARM\BOOT_ROM\BOOT_ROM.bin ..\update1.bin 0
..\binmerge.exe ..\update1.bin ..\MDK-ARM\BOOT_RAM\BOOT_RAM.bin ..\update2.bin 32768
..\binmerge.exe ..\update2.bin ..\MDK-ARM\MAIN_ROM\MAIN_ROM.bin ..\STM32F407Complete.bin 65536

del ..\update0.bin
del ..\update1.bin
del ..\update2.bin

