# Copyright 2021-2023 HPMicro
# SPDX-License-Identifier: BSD-3-Clause

import os
import sys

# toolchains options
ARCH='risc-v'
CPU='hpmicro'
CHIP_NAME='HPM6360'

CROSS_TOOL='gcc'

# bsp lib config
BSP_LIBRARY_TYPE = None

# Fallback toolchain info
FALLBACK_TOOLCHAIN_VENDOR='RISC-V'
FALLBACK_TOOLCHAIN_PKG='RISC-V-GCC-RV32'
FALLBACK_TOOLCHAIN_VER='2022-04-12'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

RTT_EXEC_PATH = os.getenv('RTT_EXEC_PATH')
if RTT_EXEC_PATH != None:
    folders = RTT_EXEC_PATH.split(os.sep)
    # If the `RT-Thread Env` is from the RT-Thread Studio, generate the RTT_EXEC_PATH using `FALLBACK_TOOLCHAIN_INFO`
    if 'arm_gcc' in folders and 'platform' in folders:
        RTT_EXEC_PATH = ''
        for path in folders:
            if path != 'platform':
                RTT_EXEC_PATH = RTT_EXEC_PATH + path + os.sep
            else:
                break
        RTT_EXEC_PATH = os.path.join(RTT_EXEC_PATH, 'repo', 'Extract', 'ToolChain_Support_Packages', FALLBACK_TOOLCHAIN_VENDOR, FALLBACK_TOOLCHAIN_PKG, FALLBACK_TOOLCHAIN_VER, 'bin')
    # Override the 'RTT_RISCV_TOOLCHAIN' only if the `RT-Thread ENV` is from the RT-Thread Studio
    if 'platform' in folders:
        os.environ['RTT_RISCV_TOOLCHAIN'] = RTT_EXEC_PATH

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler path, for example, GNU RISC-V toolchain, IAR
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

    ARCH_ABI = ' -mcmodel=medlow '
    CFLAGS = ARCH_ABI  + ' -DUSE_NONVECTOR_MODE=1 ' + ' -ffunction-sections -fdata-sections -fno-common '
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
        LINKER_FILE = 'board/linker_scripts/flash_rtt.ld'
    LFLAGS += ' -T ' + LINKER_FILE

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

    # module setting
    CXXFLAGS = CFLAGS +  ' -Woverloaded-virtual -fno-exceptions -fno-rtti '
    CFLAGS = CFLAGS + ' -std=gnu11'