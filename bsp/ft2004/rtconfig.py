import os


# toolchains options
ARCH='arm'
CPU='cortex-a'
CROSS_TOOL='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

# only support GNU GCC compiler.
PLATFORM    = 'gcc'
EXEC_PATH   = r'/usr/lib/arm-none-eabi/bin'
if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

LIBPATH  = '/usr/lib/arm-none-eabi/lib'


if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    STRIP = PREFIX + 'strip'

    
    DEVICE = ' -march=armv8-a  -mfpu=vfpv4-d16 -ftree-vectorize -ffast-math -mfloat-abi=soft --specs=nano.specs --specs=nosys.specs -fno-builtin '

    CFLAGS = DEVICE + ' -Wall'
    AFLAGS = ' -c'+ DEVICE + ' -fsingle-precision-constant  -fno-builtin -x assembler-with-cpp -D__ASSEMBLY__'    
    LINK_SCRIPT = 'ft_aarch32.lds'
    LFLAGS = DEVICE + '  -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,system_vectors'+\
                      ' -T %s' % LINK_SCRIPT

    CPATH = ''
    LPATH = LIBPATH

    # generate debug info in all cases
    AFLAGS += ' -gdwarf-2'
    CFLAGS += ' -g -gdwarf-2'

    if BUILD == 'debug':
        CFLAGS += ' -O0'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' +\
                  SIZE + ' $TARGET \n'
