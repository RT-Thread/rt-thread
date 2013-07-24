HEADERS += \
    ../rtconfig.h \
    ../drivers/led.h \
    ../drivers/drv_uart.h \
    ../drivers/board.h \
    ../../../components/drivers/include/rtdevice.h \
    ../../../components/drivers/include/drivers/serial.h \
    ../../../include/rtthread.h \
    ../../../include/rtservice.h \
    ../../../include/rtm.h \
    ../../../include/rthw.h \
    ../../../include/rtdef.h \
    ../../../include/rtdebug.h \
    ../../../src/module.h \
    ../../../../../../../../Keil/ARM/INC/Freescale/Kinetis/MK60F12.H

SOURCES += \
    ../applications/startup.c \
    ../applications/application.c \
    ../drivers/system_MK60F12.c \
    ../drivers/led.c \
    ../drivers/drv_uart.c \
    ../drivers/board.c \
    ../../../components/drivers/serial/serial.c \
    ../../../src/timer.c \
    ../../../src/thread.c \
    ../../../src/slab.c \
    ../../../src/scheduler.c \
    ../../../src/object.c \
    ../../../src/module.c \
    ../../../src/mempool.c \
    ../../../src/memheap.c \
    ../../../src/mem.c \
    ../../../src/kservice.c \
    ../../../src/irq.c \
    ../../../src/ipc.c \
    ../../../src/idle.c \
    ../../../src/device.c \
    ../../../src/clock.c

OTHER_FILES += \
    ../drivers/startup_MK60F12.s \
    ../../../src/SConscript
