import os

# toolchains options
ARCH = 'aarch64'
CPU = 'cortex-a'
CROSS_TOOL = 'gcc'

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = os.path.join(os.getcwd(), '..', '..', '..')

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

# only support GNU GCC compiler.
PLATFORM  = 'gcc'
EXEC_PATH = r'/opt/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/bin/'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = os.getenv('RTT_CC_PREFIX') or 'aarch64-none-elf-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    CPP = PREFIX + 'cpp'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -march=armv8-a -mtune=cortex-a55'
    DEVICE += ' -fno-omit-frame-pointer -ffunction-sections -fdata-sections'
    CPPFLAGS = ' -E -P -x assembler-with-cpp'
    CFLAGS = DEVICE + ' -Wall -Wno-cpp'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,system_vectors -T link.lds'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -ggdb'
        CPPFLAGS += ' -O0 -ggdb'
    else:
        CFLAGS += ' -O2 -ggdb'
        CPPFLAGS += ' -O2 -ggdb'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' +\
                  SIZE + ' $TARGET \n'
    DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > disasm.txt\n'
