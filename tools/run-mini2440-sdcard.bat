start qemu-system-arm.exe -M mini2440 -kernel ..\bsp\mini2440\rtthread-mini2440.axf -show-cursor -sd SDCARD -serial telnet:127.0.0.1:1200,server -serial file:virtualkbd
telnet 127.0.0.1 1200

