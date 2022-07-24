# QMK Firmware for KBD67Lite R2 & R3 Wired


## V2 PCB Flash Guide

1. Hold `ESC` and plug the board in
2. Clear EEPROM in QMK Toolbox
3. Flash the firmware

### Or use QMK CLI to flash
`qmk compile -kb kbdfans/kbd67/mkiirgb/v2 -km shigure -j 32`
`qmk flash -kb kbdfans/kbd67/mikkrgb/v2 -km shigure -j 32`

## V3 PCB Flash Guide

1. Hold `ESC` and plug the board in
2. Open the USB flash drive and delete `FLASH.bin`
3. Paste the new firmware `.bin` to the flash drive
4. Eject the board first then unplug the board

### Or use QMK CLI to flash
`qmk flash -kb kbdfans/kbd67/mikkrgb/v3 -km shigure -j 32`