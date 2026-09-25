import os

ARCH = 'risc-v'
CPU = 'ch32'
CROSS_TOOL = 'gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if CROSS_TOOL == 'gcc':
    PLATFORM = 'gcc'
    EXEC_PATH = r'D:\rtt\sdk-toolchain-RISC-V-GCC-WCH\bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
CORE = 'risc-v'
MAP_FILE = 'rtthread.map'
LINK_FILE = './board/linker_scripts/link.lds'
TARGET_NAME = 'rtthread.bin'

if PLATFORM == 'gcc':
    PREFIX = 'riscv-none-embed-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -march=rv32ec -mabi=ilp32e -mcmodel=medany -msmall-data-limit=8 -ffunction-sections -fdata-sections -nostartfiles --specs=nano.specs -lc '
    CFLAGS = DEVICE
    AFLAGS = '-c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS = DEVICE
    LFLAGS += ' -Wl,--gc-sections,-cref,-Map=' + MAP_FILE
    LFLAGS += ' -T ' + LINK_FILE
    CXXFLAGS = CFLAGS

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -Os -g'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -Os'

    POST_ACTION = OBJCPY + ' -O binary $TARGET ' + TARGET_NAME + '\n'
    POST_ACTION += SIZE + ' $TARGET\n'
