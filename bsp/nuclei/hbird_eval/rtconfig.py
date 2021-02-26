import os

# toolchains options
ARCH='risc-v'
CPU='nuclei'
CROSS_TOOL='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if CROSS_TOOL == 'gcc':
    PLATFORM 	= 'gcc'
    EXEC_PATH 	= 'D:/Software/Nuclei/gcc/bin'
else:
    print("CROSS_TOOL = {} not yet supported" % CROSS_TOOL)

# if os.getenv('RTT_EXEC_PATH'):
# 	EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
# Fixed configurations below
NUCLEI_SDK_SOC = "hbird"
NUCLEI_SDK_BOARD = "hbird_eval"
# Configurable options below
# DOWNLOAD: https://doc.nucleisys.com/nuclei_sdk/develop/buildsystem.html#download
NUCLEI_SDK_DOWNLOAD = "ilm"
# CORE: See https://doc.nucleisys.com/nuclei_sdk/develop/buildsystem.html#core
NUCLEI_SDK_CORE = "nx600"

if PLATFORM == 'gcc':
    # toolchains
    PREFIX  = 'riscv-nuclei-elf-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'gcc'
    GDB     = PREFIX + 'gdb'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'

    CFLAGS  = ' -ffunction-sections -fdata-sections -fno-common '
    AFLAGS  = CFLAGS
    LFLAGS  = ' --specs=nano.specs --specs=nosys.specs -nostartfiles -Wl,--gc-sections '
    LFLAGS += ' -Wl,-cref,-Map=rtthread.map'
    LFLAGS  += ' -u _isatty -u _write -u _sbrk -u _read -u _close -u _fstat -u _lseek '
    CPATH   = ''
    LPATH   = ''
    LIBS = ['stdc++']

    if BUILD == 'debug':
        CFLAGS += ' -O2 -ggdb'
        AFLAGS += ' -ggdb'
    else:
        CFLAGS += ' -O2 -Os'

    CXXFLAGS = CFLAGS

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

def dist_handle(BSP_ROOT, dist_dir):
    import sys
    cwd_path = os.getcwd()
    sys.path.append(os.path.join(os.path.dirname(BSP_ROOT), 'tools'))
    from sdk_dist import dist_do_building
    dist_do_building(BSP_ROOT, dist_dir)
