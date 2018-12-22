import os
import sys
import re

# toolchains options
ARCH         = 'arm'
CPU          = 'armv6'
OUTPUT_NAME  = 'rtthread'
CROSS_TOOL   = 'gcc' # we use gcc compiler always
PLATFORM     = 'gcc'
LD_NAME      = 'link'

EXEC_PATH    = r'D:\arm-2013.11\bin'
if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'release'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC  = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS  = PREFIX + 'gcc'
    AR  = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = '.elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    DEVICE = ' -mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=soft'
    CFLAGS = DEVICE + ' -mno-unaligned-access'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__'
    LFLAGS = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map='+ OUTPUT_NAME +'.map,-cref,-u,_start -T' + LD_NAME +'.ld'
    CPATH = ''
    LPATH = ''
    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2 '
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS
    POST_ACTION = OBJCPY + ' -O binary $TARGET '+ OUTPUT_NAME +'.bin\n' + SIZE + ' $TARGET \n'
