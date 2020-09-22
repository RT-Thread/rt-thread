import os

# toolchains options
ARCH        ='risc-v'
CPU         ='e906'
CPUNAME     ='e906f'
VENDOR      ='t-head'
CROSS_TOOL  ='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'/home/xinge/tools/riscv64-elf-x86_64-20200616-1.9.6/bin'
else:
    print 'Please make sure your toolchains is GNU GCC!'
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

# BUILD = 'debug'
BUILD = 'release'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX  = 'riscv64-unknown-elf-'
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

    if CPUNAME == 'e906fd':
        DEVICE = ' -march=rv32imafdcxthead -mabi=ilp32d'
    if CPUNAME == 'e906f':
        DEVICE = ' -march=rv32imafcxthead -mabi=ilp32f'
    if CPUNAME == 'e906':
        DEVICE = ' -march=rv32imacxthead -mabi=ilp32'

    CFLAGS  = DEVICE + ' -c -g -ffunction-sections -fdata-sections -Wall -mcmodel=medlow'
    AFLAGS  = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--no-whole-archive -T gcc_csky.ld -lm -lc -lgcc -Wl,-gc-sections -Wl,-zmax-page-size=1024'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2 -g2'

    CXXFLAGS = CFLAGS

#    M_CFLAGS = DEVICE + ' -EL -G0 -O2 -mno-abicalls -fno-common -fno-exceptions -fno-omit-frame-pointer -mlong-calls -fno-pic '
 #   M_CXXFLAGS = M_CFLAGS
 #   M_LFLAGS = DEVICE + ' -EL -r -Wl,--gc-sections,-z,max-page-size=0x4' +\
  #                                  ' -nostartfiles -static-libgcc'
 #   M_POST_ACTION = STRIP + ' -R .hash $TARGET\n' + SIZE + ' $TARGET \n'

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
