import os

# toolchains options
ARCH        ='risc-v'
VENDOR      ='t-head'
CPU         ='c906'
CROSS_TOOL  ='gcc'

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = r'../../../..'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'/opt/riscv64_musl/bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
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

    DEVICE  = ' -march=rv64imafdc -mabi=lp64 -mcmodel=medany'
    CFLAGS  = DEVICE + ' -Wall -Wno-cpp -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=deprecated-declarations -Wextra -Wno-unused-parameter -Wno-sign-compare'
    CFLAGS += ' -Wno-old-style-declaration -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -fshort-enums -fcommon -ffreestanding -fno-strict-aliasing -fno-jump-tables -save-temps=obj'
    CFLAGS += ' -D_POSIX_SOURCE'
    CFLAGS += ' -DCFG_COMPONENT_BLOG_ENABLE=0 -DBFLB_USE_HAL_DRIVER -DCPU_D0 -DBL808 -DLOG_UART_ID_0'

    AFLAGS  = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__'
    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,_start -T board/linker_scripts/link.lds' + ' -lsupc++ -lgcc -static'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf'
        AFLAGS += ' -gdwarf'
    else:
        CFLAGS += ' -O3'

    CXXFLAGS = CFLAGS

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread_d0.bin\n' + SIZE + ' $TARGET \n'
POST_ACTION += 'python3 merge_rtsmart.py'
