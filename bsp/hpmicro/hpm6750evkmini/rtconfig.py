# Copyright 2021-2022 hpmicro
# SPDX-License-Identifier: BSD-3-Clause

import os
import sys

# toolchains options
ARCH='risc-v'
CPU='hpmicro'

CHIP_NAME='HPM6750'

CROSS_TOOL='gcc'

# bsp lib config
BSP_LIBRARY_TYPE = None

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

# cross_tool provides the cross compiler
# EXEC_PATH is the compilercute path, for example, CodeSourcery, Keil MDK, IAR
if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    if os.getenv('RTT_RISCV_TOOLCHAIN'):
        EXEC_PATH = os.getenv('RTT_RISCV_TOOLCHAIN')
    else:
        EXEC_PATH   = r'/opt/riscv-gnu-gcc/bin'
else:
    print("CROSS_TOOL = {} not yet supported" % CROSS_TOOL)



BUILD = 'flash_debug'

if PLATFORM == 'gcc':
    PREFIX = 'riscv32-unknown-elf-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    GDB = PREFIX + 'gdb'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    STRIP = PREFIX + 'strip'

    DEVICE = ' -std=gnu11 -DUSE_NONVECTOR_MODE=1'
    ARCH_ABI = '   -mcmodel=medlow '
    CFLAGS = DEVICE + ARCH_ABI + ' -ffunction-sections -fdata-sections -fno-common'
    AFLAGS = CFLAGS
    LFLAGS  = ARCH_ABI + '  --specs=nano.specs --specs=nosys.specs  -u _printf_float -u _scanf_float -nostartfiles -Wl,--gc-sections '

    CPATH = ''
    LPATH = ''

    if BUILD == 'ram_debug':
        CFLAGS += ' -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
        CFLAGS += ' -O0'
        LFLAGS += ' -O0'
        LINKER_FILE = 'board/linker_scripts/ram_rtt.ld'
    elif BUILD == 'ram_release':
        CFLAGS += ' -O2 -Os'
        LFLAGS += ' -O2 -Os'
        LINKER_FILE = 'board/linker_scripts/ram_rtt.ld'
    elif BUILD == 'flash_debug':
        CFLAGS += ' -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
        CFLAGS += ' -O0'
        LFLAGS += ' -O0'
        CFLAGS += ' -DFLASH_XIP=1'
        LINKER_FILE = 'board/linker_scripts/flash_rtt.ld'
    elif BUILD == 'flash_release':
        CFLAGS += ' -O2 -Os'
        LFLAGS += ' -O2 -Os'
        CFLAGS += ' -DFLASH_XIP=1'
        LINKER_FILE = 'board/linker_scripts/flash_rtt.ld'
    else:
        CFLAGS += ' -O2 -Os'
        LFLAGS += ' -O2 -Os'
        LINKER_FILE = 'board/linker_scripts/ram_rtt.ld'
    LFLAGS += ' -T ' + LINKER_FILE

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

    # module setting
    CXXFLAGS = ' -Woverloaded-virtual -fno-exceptions -fno-rtti '
    M_CFLAGS = CFLAGS + ' -mlong-calls -fPIC '
    M_CXXFLAGS = CXXFLAGS + ' -mlong-calls -fPIC'
    M_LFLAGS = DEVICE + CXXFLAGS + ' -Wl,--gc-sections,-z,max-page-size=0x4' +\
                                    ' -shared -fPIC -nostartfiles -static-libgcc'
