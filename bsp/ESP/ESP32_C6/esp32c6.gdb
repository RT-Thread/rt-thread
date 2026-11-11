# Panic GDB stub for ESP32-C6. Default images do not enter this stub.
# After a panic with BSP_ENABLE_GDBSTUB, connect the UART port (CP210x).
set remote hardware-breakpoint-limit 1
set remote hardware-watchpoint-limit 1
set remote interrupt-on-connect on
set remote kill-packet off
set remote symbol-lookup-packet off
set remotetimeout 20
set serial baud 115200
file ./rtthread.elf
mem 0x40000000 0x4007ffff ro
mem 0x40800000 0x4087ffff rw
mem 0x42000000 0x42ffffff ro
mem 0x50000000 0x50003fff rw
mem 0x60000000 0x600dffff rw
target remote \\.\COM13
