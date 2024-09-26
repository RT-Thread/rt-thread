import os

# toolchains options
ARCH        ='risc-v'
VENDOR      ='t-head'
CPU         ='c908'
CROSS_TOOL  ='gcc'

RTT_ROOT = os.getenv('RTT_ROOT', r'../..')

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'/opt/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1/bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

EXEC_PATH = os.getenv('RTT_EXEC_PATH', EXEC_PATH)

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    #PREFIX  = 'riscv64-unknown-elf-'
    PREFIX  = os.getenv('RTT_CC_PREFIX') or 'riscv64-unknown-linux-musl-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'

    DEVICE  = ' -mcmodel=medany -march=rv64imafdc -mabi=lp64'
    CFLAGS  = DEVICE + ' -Wno-cpp -fvar-tracking -ffreestanding -fno-common -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -D_POSIX_SOURCE '
    AFLAGS  = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__'
    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,_start -T link.lds' + ' -lsupc++ -lgcc -static'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O2 -g -gdwarf-2'
        AFLAGS += ' -g -gdwarf-2'
    else:
        CFLAGS += ' -O2 -g -gdwarf-2'

    CXXFLAGS = CFLAGS

POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
