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
NUCLEI_SDK_ROOT = os.path.abspath("../nuclei_sdk")
SOC_LIBRARY_ROOT = os.path.join(NUCLEI_SDK_ROOT, "SoC", "gd32vf103")
LINK_FILE = os.path.join(SOC_LIBRARY_ROOT, "Board", "gd32vf103v_rvstar", "Source", "GCC", "gcc_gd32vf103_flashxip.ld")
OPENOCD_CFG = os.path.join(SOC_LIBRARY_ROOT, "Board", "gd32vf103v_rvstar", "openocd_gd32vf103.cfg")

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

    DEVICE  = '-march=rv32imac -mabi=ilp32 -mcmodel=medany '
    CFLAGS  = DEVICE + ' -ffunction-sections -fdata-sections -fno-common '
    AFLAGS  = CFLAGS
    LFLAGS  = DEVICE + ' --specs=nano.specs --specs=nosys.specs -nostartfiles -Wl,--gc-sections '
    LFLAGS += ' -Wl,-cref,-Map=rtthread.map -u _printf_float'
    LFLAGS += ' -T ' + LINK_FILE
    LFLAGS  += ' -u _isatty -u _write -u _sbrk -u _read -u _close -u _fstat -u _lseek '
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O2 -ggdb'
        AFLAGS += ' -ggdb'
    else:
        CFLAGS += ' -O2 -Os'

    CXXFLAGS = CFLAGS

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
