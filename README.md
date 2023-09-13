# QMK Firmware for KBD67Lite R2 & R3 Wired


## V2 PCB Flash Guide

1. Hold `ESC` and plug the board in
2. Clear EEPROM in QMK Toolbox
3. Flash the firmware

### Or use QMK CLI to flash
`qmk compile -kb kbdfans/kbd67/mkiirgb/v2 -km shigure -j 32`

`qmk flash -kb kbdfans/kbd67/mkiirgb/v2 -km shigure -j 32`