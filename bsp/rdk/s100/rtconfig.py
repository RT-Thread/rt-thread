import os
import sys


def _config_enabled(symbol, default=False):
    config_path = os.path.join(os.path.dirname(__file__), '.config')

    try:
        with open(config_path, 'r', encoding='utf-8') as cfg:
            text = cfg.read()
            if f'CONFIG_{symbol}=y' in text:
                return True
            if f'# CONFIG_{symbol} is not set' in text:
                return False
            return default
    except OSError:
        return default

# toolchains options
ARCH='arm'
CPU='cortex-r52'
CROSS_TOOL='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')
if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')

# cross_tool provides the cross compiler
if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'/opt/toolchain/gcc-arm-none-eabi-10.3-2021.10/bin'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

# BUILD = 'debug'
BUILD = 'release'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    CXX = PREFIX + 'g++'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    NM = PREFIX + 'nm'

    if _config_enabled('RT_USING_FPU', default=True):
        DEVICE = ' -mcpu=cortex-r52 -marm -mfloat-abi=hard -mfpu=vfpv3-d16 -mlittle-endian'
    else:
        DEVICE = ' -mcpu=cortex-r52 -marm -mfloat-abi=soft -mgeneral-regs-only -mlittle-endian'
    COMMON_CFLAGS = (
        ' -fno-inline'
        ' -ffunction-sections'
        ' -fdata-sections'
        ' -fdiagnostics-parseable-fixits'
        ' -fmessage-length=0'
        ' -funsigned-char'
        ' -funsigned-bitfields'
        ' -fno-common'
        ' -fno-strict-aliasing'
        ' -funwind-tables'
        ' -Dgcc'
    )

    CFLAGS = DEVICE + COMMON_CFLAGS
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,system_vector -lgcc -T link.lds'

    if BUILD == 'debug':
        CFLAGS += ' -Og -ggdb3 -gdwarf-4'
        AFLAGS += ' -ggdb3 -gdwarf-4'
    else:
        CFLAGS += ' -O2'
    CXXFLAGS = CFLAGS

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
