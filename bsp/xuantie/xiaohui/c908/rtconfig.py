import os
import re

# toolchains options
ARCH        = 'risc-v'
VENDOR      = 't-head'
CPU         = 'c908'
CROSS_TOOL  = 'gcc'

RTT_ROOT = os.getenv('RTT_ROOT', r'../../../..')

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = os.getenv('RTT_EXEC_PATH') or os.path.expanduser('~/tools/Xuantie-900-gcc-linux-6.6.0-musl64-x86_64-V3.0.2/bin')
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
#BUILD = 'release'

CORE = 'risc-v'
MAP_FILE = 'rtthread.map'
LINK_FILE = 'link.lds.generated'
TARGET_NAME = 'rtthread.bin'

#------- GCC settings ----------------------------------------------------------
if PLATFORM == 'gcc':
    # toolchains
    PREFIX = os.getenv('RTT_CC_PREFIX') or 'riscv64-unknown-linux-musl-'
    CC = PREFIX + 'gcc'
    CXX= PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -mcmodel=medany -march=rv64imafdcv_zicsr_zifencei -mabi=lp64d '

    GLOBAL_DEFINES = ' -DC908_PLIC_PHY_ADDR=0x08000000UL '

    CFLAGS = DEVICE + GLOBAL_DEFINES + ' -fno-pie -fno-pic -Wno-cpp -fvar-tracking -ffreestanding -fno-common -ffunction-sections -fdata-sections -fstrict-volatile-bitfields '
    AFLAGS = ' -c' + DEVICE + ' -fno-pie -fno-pic -x assembler-with-cpp -D__ASSEMBLY__'
    LFLAGS = DEVICE + ' -no-pie -nostartfiles -Wl,--gc-sections,-Map=' + MAP_FILE + ',-cref,-u,Reset_Handler -T ' + LINK_FILE + ' -lsupc++ -lgcc -static'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -g3'
        AFLAGS += ' -g3'
    else:
        CFLAGS += ' -O2 -g2'

    CXXFLAGS = CFLAGS

    POST_ACTION = OBJCPY + ' -O binary $TARGET ' + TARGET_NAME + '\n'
    POST_ACTION += SIZE + ' $TARGET\n'

def dist_handle(BSP_ROOT, dist_dir):
    import sys
    cwd_path = os.getcwd()
    sys.path.append(os.path.join(os.path.dirname(BSP_ROOT), '../tools'))
    from sdk_dist import dist_do_building
    dist_do_building(BSP_ROOT, dist_dir)
