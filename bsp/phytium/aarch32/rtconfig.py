import os
import rtconfig

# toolchains options
ARCH='arm'
CPU='cortex-a'
CROSS_TOOL='gcc'

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = r'../../..'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

# only support GNU GCC compiler.
PLATFORM    = 'gcc'
EXEC_PATH   = r'/usr/lib/arm-none-eabi/bin'
if os.getenv('AARCH32_CROSS_PATH'):
    EXEC_PATH = os.getenv('AARCH32_CROSS_PATH')
    print('EXEC_PATH = {}'.format(EXEC_PATH))
else:
    print('AARCH32_CROSS_PATH not found')

BUILD = 'debug'

LIBPATH = EXEC_PATH + r'/../lib'

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

    DEVICE = ' -g -DGUEST  -ffreestanding  -Wextra -g -mfpu=crypto-neon-fp-armv8 -mfloat-abi=softfp -march=armv8-a -fdiagnostics-color=always'

    # CFLAGS = DEVICE + ' -Wall'
    CFLAGS = DEVICE
    AFLAGS = ' -c'+ DEVICE + ' -fsingle-precision-constant  -fno-builtin -x assembler-with-cpp -D__ASSEMBLY__'    
    LINK_SCRIPT = 'link.lds'
    LFLAGS = DEVICE + '  -Wl,--gc-sections,-Map=rtthread_a32.map,-cref,-u,system_vectors'+\
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

    CXXFLAGS = CFLAGS

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread_a32.bin\n' +\
                  SIZE + ' $TARGET \n'
