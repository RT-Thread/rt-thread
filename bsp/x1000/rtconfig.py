import os

# toolchains options
ARCH        ='mips'
CPU         ='x1000'
CROSS_TOOL  ='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'/opt/mips-2016.05/bin/'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

# BUILD = 'debug'
BUILD = 'release'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX  = 'mips-sde-elf-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'g++'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'
    STRIP   = PREFIX + 'strip'

    DEVICE = ' -mips32r2 -msoft-float -mfp32'
    CFLAGS  = DEVICE + ' -EL -G0 -mno-abicalls -fno-pic -fno-builtin -fno-exceptions -ffunction-sections -fno-omit-frame-pointer'
    AFLAGS  = ' -c' + DEVICE + ' -EL -x assembler-with-cpp'
    LFLAGS  = DEVICE + ' -EL -Wl,--gc-sections,-Map=rtthread_x1000.map,-cref,-u,Reset_Handler -T x1000_ram.lds'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS

    M_CFLAGS = DEVICE + ' -EL -G0 -O2 -mno-abicalls -fno-common -fno-exceptions -fno-omit-frame-pointer -mlong-calls -fno-pic '
    M_CXXFLAGS = M_CFLAGS
    M_LFLAGS = DEVICE + ' -EL -r -Wl,--gc-sections,-z,max-page-size=0x4' +\
                                    ' -nostartfiles -static-libgcc'
    M_POST_ACTION = STRIP + ' -R .hash $TARGET\n' + SIZE + ' $TARGET \n'

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
