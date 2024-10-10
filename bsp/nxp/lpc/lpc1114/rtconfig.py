import os

# toolchains options
ARCH        ='arm'
CPU         ='cortex-m0'
CROSS_TOOL  ='gcc'
BOARD_NAME = 'lpc1114'

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR
if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'C:\Users\XXYYZZ'
elif CROSS_TOOL == 'keil':
    PLATFORM 	= 'armcc'
    EXEC_PATH 	= 'C:/keil_v5'
elif CROSS_TOOL == 'iar':
    PLATFORM  = 'iccarm'
    EXEC_PATH    = r'C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.3'

if os.getenv('RTT_EXEC_PATH'):
	EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug' 
# BUILD = 'release' 


if PLATFORM == 'gcc':
    # toolchains
    PREFIX  = 'arm-none-eabi-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'g++'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'

    DEVICE  = ' -mcpu=cortex-m0 -mthumb -ffunction-sections -fdata-sections'
    CFLAGS  = DEVICE + ' -Wall'
    AFLAGS  = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,Reset_Handler -T link.lds'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -Os'

    CXXFLAGS = CFLAGS

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtthread.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
