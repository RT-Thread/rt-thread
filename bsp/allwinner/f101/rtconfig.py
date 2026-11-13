import os

# An RV32 GNU toolchain is selected through RTT_EXEC_PATH/RTT_CC_PREFIX.
ARCH = 'risc-v'
CPU = ''
VENDOR = 't-head'
CROSS_TOOL = 'gcc'
PLATFORM = 'gcc'
BUILD = 'debug'

RTT_ROOT = os.getenv('RTT_ROOT') or os.path.normpath(
        os.path.join(os.getcwd(), '..', '..', '..'))
EXEC_PATH = os.getenv('RTT_EXEC_PATH') or ''
PREFIX = os.getenv('RTT_CC_PREFIX') or 'riscv64-unknown-elf-'

CC = PREFIX + 'gcc'
CXX = PREFIX + 'g++'
CPP = PREFIX + 'cpp'
AS = PREFIX + 'gcc'
AR = PREFIX + 'ar'
LINK = PREFIX + 'gcc'
SIZE = PREFIX + 'size'
OBJDUMP = PREFIX + 'objdump'
OBJCPY = PREFIX + 'objcopy'
TARGET_EXT = 'elf'

DEVICE = ' -mcmodel=medany -march=rv32imafdc -mabi=ilp32d '
CPPFLAGS = ' -nostdinc -undef -E -P -x assembler-with-cpp'
CFLAGS = DEVICE + \
        '-ffreestanding -flax-vector-conversions -Wno-cpp -fno-common ' \
        '-ffunction-sections -fdata-sections -fstrict-volatile-bitfields '
AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__ '
LFLAGS = DEVICE + \
        ' -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,_start ' \
        '-T link.lds -lsupc++ -lgcc -static'

if BUILD == 'debug':
    CFLAGS += ' -O0 -ggdb -fvar-tracking'
    AFLAGS += ' -ggdb'
else:
    CFLAGS += ' -O2 -Os'

CXXFLAGS = CFLAGS

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtthread.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + \
        SIZE + ' $TARGET\n'
