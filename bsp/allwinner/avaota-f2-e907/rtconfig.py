import os

ARCH = 'risc-v'
CPU = 'generic'
CROSS_TOOL = 'gcc'

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = os.path.normpath(os.path.join(os.getcwd(), '..', '..', '..'))

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if CROSS_TOOL == 'gcc':
    PLATFORM = 'gcc'
    EXEC_PATH = os.getenv('RTT_EXEC_PATH') or '/opt/riscv-none-embed/bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

BUILD = 'debug'
LINK_FILE = 'link.lds'
TARGET_NAME = 'rtthread.bin'

if PLATFORM == 'gcc':
    PREFIX = os.getenv('RTT_CC_PREFIX') or 'riscv-none-embed-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -ffunction-sections -fdata-sections'
    CFLAGS = DEVICE + ' -Wall -Wno-unused-function -fno-builtin -fno-strict-aliasing -g -D__STACKSIZE__=8192'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -D__STACKSIZE__=8192'
    LFLAGS = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref -T ' + LINK_FILE
    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -g3'
        AFLAGS += ' -g3'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS
    POST_ACTION = OBJCPY + ' -O binary $TARGET ' + TARGET_NAME + '\n' + SIZE + ' $TARGET \n'
