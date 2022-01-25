import os

# toolchains options
ARCH='arm'
CPU='cortex-m3'
CROSS_TOOL='keil'

print("############rtconfig##############")

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR
if CROSS_TOOL == 'keil':
    PLATFORM    = 'armcc'
    EXEC_PATH   = r'D:\Keil_v5'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
MCU_TYPE = 'TAE32F53xx'

if PLATFORM == 'armcc':
    # toolchains
    CC = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --cpu ' + CPU 
    CFLAGS = '-c ' + DEVICE + ' --apcs=interwork --c99'
    AFLAGS = DEVICE + ' --apcs=interwork '
    LFLAGS = DEVICE + '  --scatter "drivers/linker_scripts/tae32f53xx_ac5_sram.sct" --info sizes --info totals --info unused --info veneers --list rtthread.map --strict'
  
    CFLAGS += ' -I' + EXEC_PATH + '/ARM/ARMCC/INC'
    LFLAGS += ' --libpath ' + EXEC_PATH + '/ARM/ARMCC/LIB'

    CFLAGS += ' -D__MICROLIB '
    AFLAGS += ' --pd "__MICROLIB SETA 1" '
    LFLAGS += ' --library_type=microlib '
    EXEC_PATH += '/arm/armcc/bin/'

    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin \nfromelf -z $TARGET'
