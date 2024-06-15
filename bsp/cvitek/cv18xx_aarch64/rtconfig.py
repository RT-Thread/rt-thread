import os

# toolchains options
ARCH        ='aarch64'
CPU         ='cortex-a'
CROSS_TOOL  = 'gcc'
PLATFORM    = 'gcc'
EXEC_PATH   = os.getenv('RTT_EXEC_PATH') or '/usr/bin'
BUILD       = 'debug'

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
    STRIP   = PREFIX + 'strip'
    CFPFLAGS = ' '
    AFPFLAGS = ' '
    DEVICE   = ' -march=armv8-a -mtune=cortex-a53 -ftree-vectorize -ffast-math -funwind-tables -fno-strict-aliasing'

    CPPFLAGS= ' -E -P -x assembler-with-cpp'
    CXXFLAGS= DEVICE + CFPFLAGS + ' -Wall -fdiagnostics-color=always'
    CFLAGS  = DEVICE + CFPFLAGS + ' -Wall -Wno-cpp -std=gnu99 -fdiagnostics-color=always'
    AFLAGS  = ' -c' + AFPFLAGS + ' -x assembler-with-cpp'
    LFLAGS  = DEVICE + ' -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,system_vectors -T link.lds' + ' -lsupc++ -lgcc -static'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS   += ' -O0 -gdwarf-2'
        CXXFLAGS += ' -O0 -gdwarf-2'
        AFLAGS   += ' -gdwarf-2'
    else:
        CFLAGS   += ' -Os'
        CXXFLAGS += ' -Os'
    CXXFLAGS += ' -Woverloaded-virtual -fno-exceptions -fno-rtti'

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
POST_ACTION += OBJCPY + ' -O binary $TARGET Image \n' + SIZE + ' $TARGET \n'
POST_ACTION += 'cd .. && bash mksdimg.sh ' + os.getcwd() + ' Image \n'
