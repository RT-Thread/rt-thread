import os

# toolchains options
ARCH        ='arm'
CPU         ='cortex-a'
CROSS_TOOL  = 'gcc'
PLATFORM    = 'gcc'
EXEC_PATH   = os.getenv('RTT_EXEC_PATH') or '/usr/bin'
BUILD       = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX  = os.getenv('RTT_CC_PREFIX') or 'arm-linux-musleabi-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'
    STRIP   = PREFIX + 'strip'
    CFPFLAGS = ' -msoft-float'
    AFPFLAGS = ' -mfloat-abi=softfp -mfpu=vfpv3-d16'
    DEVICE   = ' -march=armv7-a -mtune=cortex-a7 -ftree-vectorize -ffast-math -funwind-tables -fno-strict-aliasing -fcommon'

    CXXFLAGS= DEVICE + CFPFLAGS + ' -Wall'
    CFLAGS  = DEVICE + CFPFLAGS + ' -Wall -std=gnu99'
    AFLAGS  = DEVICE + ' -c' + AFPFLAGS + ' -x assembler-with-cpp -D__ASSEMBLY__'
    LFLAGS  = DEVICE + ' -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,system_vectors -T link.lds' + ' -lgcc'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS   += ' -O0 -gdwarf-2' + ' -Wno-unused-function'
        CXXFLAGS += ' -O0 -gdwarf-2'
        AFLAGS   += ' -gdwarf-2'
    else:
        CFLAGS   += ' -Os'
        CXXFLAGS += ' -Os'
    CXXFLAGS += ' -Woverloaded-virtual -fno-exceptions -fno-rtti'
    MKIMAGE = '-t imximage -b rtthread.bin -o rtthread.imx -g rtthread.img -a 0x80001000'

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n' +\
              'python3 mkimage.py ' + MKIMAGE + '\n'
