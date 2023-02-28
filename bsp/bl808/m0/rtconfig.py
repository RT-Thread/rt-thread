import os

# toolchains options
ARCH        ='risc-v'
VENDOR      ='t-head'
CPU         ='e9xx'
CROSS_TOOL  ='gcc'

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = r'../../..'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'/opt/Xuantie-900-gcc-elf-newlib-x86_64-V2.6.1/bin'
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

    DEVICE  = ' -march=rv32imafcxthead -mabi=ilp32f -mtune=e907 -mcmodel=medany'
    CFLAGS  = DEVICE + ' -Wall -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=deprecated-declarations -Wextra -Wno-unused-parameter -Wno-sign-compare'
    CFLAGS += ' -Wno-old-style-declaration -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -fshort-enums -fcommon -ffreestanding -fno-strict-aliasing -fno-jump-tables -save-temps=obj'

    LINKER_SCRIPTS_PATH = r'libraries/platform/soc/bl808/startup_bl808/evb/ld/'
    LINKER_SCRIPTS = 'bl808_flash.ld'

    CFLAGS += ' -DCFG_COMPONENT_BLOG_ENABLE=0 -DARCH_RISCV -DBFLB_USE_HAL_DRIVER -DCPU_M0 -DBL808'

    AFLAGS  = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,_start -T ' + LINKER_SCRIPTS_PATH + LINKER_SCRIPTS
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf'
        AFLAGS += ' -gdwarf'
    else:
        CFLAGS += ' -O3'

    CXXFLAGS = CFLAGS + ' -std=gnu++17 -Wno-multichar'

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread_m0.bin\n' + SIZE + ' $TARGET \n'
