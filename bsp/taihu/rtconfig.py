import os

# toolchains options

ARCH='ppc'
CPU='ppc405'
CROSS_TOOL='gcc'
TextBase = '0x00000000'

PLATFORM = 'gcc'
EXEC_PATH = 'C:/Program Files/CodeSourcery/Sourcery G++ Lite/bin'
BUILD = 'debug'

if os.getenv('RTT_EXEC_PATH'):
	EXEC_PATH = os.getenv('RTT_EXEC_PATH')

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'powerpc-eabi-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -mcpu=405 -mno-multiple -mno-string -mno-update -fno-exceptions -fno-builtin -msoft-float'

    CFLAGS = DEVICE + ' -D__KERNEL__'
    AFLAGS = '-D__ASSEMBLY__ -fno-exceptions  -fno-builtin  -mregnames -c -Wall -Xassembler -m405 -msoft-float -ffunction-sections'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,--cref,-Map=rtthread.map -T taihu.lds' + ' -Ttext=' + TextBase

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    DASM_ACTION = OBJDUMP + ' -d rtthread-taihu.elf > rtt.asm\n'
    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n' # + DASM_ACTION
