import os

# toolchains options
ARCH        ='risc-v'
CPU         ='rv64'
CROSS_TOOL  ='gcc'

# bsp lib config
BSP_LIBRARY_TYPE = None

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = r'../../..'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'/opt/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1/bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX  = 'riscv64-unknown-elf-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'

    DEVICE  = ' -march=rv64imafdc -mabi=lp64d -mcmodel=medany'
    CFLAGS  = DEVICE + ' -std=gnu11 -ffunction-sections -fdata-sections -Wl,--gc-sections -Wno-pointer-to-int-cast -fno-builtin -Wno-missing-field-initializers -fdiagnostics-color=always' 
    CFLAGS += ' -Wall -nostdlib'
    CFLAGS += ' -DCONFIG_64BIT'

    LINKER_SCRIPTS = r'cv180x_lscript.ld'
    LINKER_SCRIPTS_PATH = r' -L board/script/cv180x'

    AFLAGS  = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS  = DEVICE + ' -nostartfiles -fms-extensions -ffunction-sections -fdata-sections -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,_start -T ' + LINKER_SCRIPTS + LINKER_SCRIPTS_PATH
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O2 -g'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O3'

    CXXFLAGS = CFLAGS + ' -std=gnu++17 -Wno-multichar -Wno-parentheses'

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
POST_ACTION += 'cd .. && bash combine-fip.sh ' + os.getcwd() + ' rtthread.bin' + ' \n'