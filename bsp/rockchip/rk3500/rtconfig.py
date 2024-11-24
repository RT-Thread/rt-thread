import os

# toolchains options
ARCH        ='aarch64'
CPU         ='cortex-a'
CROSS_TOOL  ='gcc'

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = os.path.join(os.getcwd(), '..', '..', '..')

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

PLATFORM    = 'gcc'
EXEC_PATH   = r'/opt/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/bin/'

EXEC_PATH   = os.getenv('RTT_EXEC_PATH') or '/usr/bin'

BUILD = 'release'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX  = os.getenv('RTT_CC_PREFIX') or 'aarch64-none-elf-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    CPP     = PREFIX + 'cpp'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'

    DEVICE = ' -g -march=armv8.2-a -mtune=cortex-a55 -fdiagnostics-color=always'
    CPPFLAGS= ' -E -P -x assembler-with-cpp'
    CFLAGS = DEVICE + ' -Wall -Wno-cpp'
    AFLAGS = ' -c' + ' -x assembler-with-cpp -D__ASSEMBLY__'
    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--no-warn-rwx-segments -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,system_vectors -T link.lds'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -ggdb'
        CPPFLAGS += ' -O0 -ggdb'
        AFLAGS += ' -ggdb'
    else:
        CFLAGS += ' -O2 -ggdb'
        CPPFLAGS += ' -O2 -ggdb'

    CXXFLAGS = CFLAGS

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
POST_ACTION += 'md5sum rtthread.bin\n'
