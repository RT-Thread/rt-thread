import os

# toolchains options
# CPUNAME = e906/e906f/e906fd/e906p/e906fp/e906fdp
# CPUNAME = e907/e907f/e907fd/e907p/e907fp/e907fdp
ARCH        ='risc-v'
CPU         ='e9xx'
CPUNAME     ='e906fdp'
VENDOR      ='t-head'
CROSS_TOOL  ='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'/home/chenzx/.thead/riscv64-elf-x86_64-2.0.1/bin/'
else:
    print ('Please make sure your toolchains is GNU GCC!')
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


    if CPUNAME == 'e906fdp' or CPUNAME == 'e907fdp':
        DEVICE = ' -march=rv32imafdcpzp64_xtheade -mabi=ilp32d'
    if CPUNAME == 'e906fp' or CPUNAME == 'e907fp':
        DEVICE = ' -march=rv32imafcpzp64_xtheade -mabi=ilp32f'
    if CPUNAME == 'e906p' or CPUNAME == 'e907p':
        DEVICE = ' -march=rv32imacpzp64_xtheade -mabi=ilp32'
    if CPUNAME == 'e906fd' or CPUNAME == 'e907fd':
        DEVICE = ' -march=rv32imafdc_xtheade -mabi=ilp32d'
    if CPUNAME == 'e906f' or CPUNAME == 'e907f':
        DEVICE = ' -march=rv32imafc_xtheade -mabi=ilp32f'
    if CPUNAME == 'e906' or CPUNAME == 'e907':
        DEVICE = ' -march=rv32imac_xtheade -mabi=ilp32'

    CFLAGS  = DEVICE + ' -c -g -ffunction-sections -fdata-sections -Wall -mcmodel=medlow'
    AFLAGS  = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--no-whole-archive -T gcc_csky.ld -lm -lc -lgcc -Wl,-gc-sections -Wl,-zmax-page-size=1024 -Wl,-Map=rtt.map'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2 -g2'

    CXXFLAGS = CFLAGS

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
