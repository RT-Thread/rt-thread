import os

# toolchains options
ARCH='arm'
CPU='cortex-a'
CROSS_TOOL='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

# only support GNU GCC compiler
PLATFORM 	= 'gcc'
EXEC_PATH 	= '/opt/arm-none-eabi-gcc'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

# BUILD = 'relsase'
BUILD = 'debug'
if os.getenv('RTT_BUILD_TYPE'):
    BUILD = os.getenv('RTT_BUILD_TYPE')

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
    DEVICE = ' -Wall -Werror -mcpu=cortex-a9 -mfloat-abi=hard -mfpu=vfpv3 -ffunction-sections -fdata-sections -funwind-tables '
    CFLAGS = DEVICE
    AFLAGS = ' -c -fmessage-length=0' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__ -I. '
    LINK_SCRIPT = 'lscript.ld'
    LFLAGS = DEVICE + ' -Wl,-Map=zynq7000.map,--gc-sections,-build-id=none -specs=Xilinx.spec -Wl,-T -Wl,%s' % LINK_SCRIPT
    CXXFLAGS = DEVICE + ' -std=gnu++11 -Woverloaded-virtual -fno-exceptions -fno-rtti'

    CPATH = ''
    LPATH = ''

    M_CFLAGS = CFLAGS + ' -mlong-calls -fPIC '
    M_CXXFLAGS = CXXFLAGS + ' -mlong-calls -fPIC'
    M_LFLAGS = DEVICE + CXXFLAGS + ' -Wl,--gc-sections,-z,max-page-size=0x4' +\
                                ' -shared -fPIC -nostartfiles -nostdlib -static-libgcc'
    M_POST_ACTION = STRIP + ' -R .hash $TARGET\n' + SIZE + ' $TARGET \n'

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O3'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' +\
                SIZE + ' $TARGET \n'
