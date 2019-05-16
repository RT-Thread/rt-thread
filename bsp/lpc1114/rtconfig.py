import os

# toolchains options
ARCH        ='arm'
CPU         ='cortex-m0'
CROSS_TOOL  ='gcc'

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = '../..'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'/usr/bin'
else:
    print 'Please make sure your toolchains is GNU GCC!'
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'release'
# BUILD = 'debug'

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

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
