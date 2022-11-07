import os

# toolchains options
ARCH        ='aarch64'
CPU         ='cortex-a'
CROSS_TOOL  ='gcc'

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = r'../../..'

PLATFORM    = 'gcc'
EXEC_PATH   = r'/opt/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/bin/' 
if os.getenv('AARCH64_CROSS_PATH'):
    EXEC_PATH = os.getenv('AARCH64_CROSS_PATH')
    print('EXEC_PATH = {}'.format(EXEC_PATH))
else:
    print('AARCH64_CROSS_PATH not found')

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX  = 'aarch64-none-elf-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'

    DEVICE = ' -march=armv8-a -mtune=cortex-a72'
    CFLAGS = DEVICE + ' -Wall'
    AFLAGS = ' -c' + ' -x assembler-with-cpp -D__ASSEMBLY__'
    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread_a64.map,-cref,-u,system_vectors -T link.lds -fdiagnostics-color=always'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtthread_a64.dis\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread_a64.bin\n' + SIZE + ' $TARGET \n'
