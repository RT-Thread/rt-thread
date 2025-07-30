fatload mmc 1:1 0x480000 rtthread.bin;
fatload mmc 1:1 0x8300000 tspi-rk3566-user-v10-linux.dtb;
booti 0x480000 - 0x8300000;
