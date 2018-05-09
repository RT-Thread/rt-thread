import os
ARCH     = 'risc-v'
CPU      = 'e310'
# toolchains options
CROSS_TOOL  = 'gcc'

#------- toolchains path -------------------------------------------------------
if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = '/home/zj/risc-v/riscv64-unknown-elf-gcc-20170612-x86_64-linux-centos6/bin'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
#BUILD = 'release'

CORE = 'risc-v'
MAP_FILE = 'rtthread.map'
LINK_FILE = 'sdram'
TARGET_NAME = 'rtthread.bin'

#------- GCC settings ----------------------------------------------------------
if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'riscv64-unknown-elf-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -march=rv32imac -mabi=ilp32 -DUSE_PLIC -DUSE_M_TIME -mcmodel=medany -msmall-data-limit=8  -g -L.  -nostartfiles  -lc '
    CFLAGS = DEVICE
    CFLAGS += ''
    AFLAGS = '-c'+ DEVICE + ' -x assembler-with-cpp'
    AFLAGS += ' -Iplatform'
    LFLAGS = DEVICE 
    LFLAGS += ' -Wl,--gc-sections,-cref,-Map=' + MAP_FILE
    LFLAGS += ' -T ' + LINK_FILE + '.ld'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET ' + TARGET_NAME + '\n' 
    POST_ACTION += SIZE + ' $TARGET\n'
