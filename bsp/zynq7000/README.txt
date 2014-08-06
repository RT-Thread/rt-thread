Place the rtthread.bin in the SD card and run:

     mmcinfo; fatload mmc 0 0x1ff00000 rtthread.bin; go 0x1ff00000

in the uboot console.
