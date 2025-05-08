# BSP Note: For TI EK-TM4C1294XL Tiva C Series Connected LancuhPad	(REV D)

import os
import sys
# toolchains options
CROSS_TOOL = 'gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')
# device options
ARCH = 'arm'
CPU = 'cortex-m33'


# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR
if CROSS_TOOL == 'gcc':
    PLATFORM = 'gcc'
    EXEC_PATH = r'C:\Users\XXYYZZ'
elif CROSS_TOOL == 'keil':
    PLATFORM = 'armcc'
    EXEC_PATH = 'C:/Keil_v5'
elif CROSS_TOOL == 'iar':
    PLATFORM = 'iccarm'
    EXEC_PATH = 'C:/Program Files (x86)/IAR Systems/Embedded Workbench 7.2'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
#BUILD = 'release'

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

    DEVICE = ' -mcpu=cortex-m33 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections'
    CFLAGS = DEVICE + ' -Dgcc'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -Wa,-mimplicit-it=thumb '
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rt-thread.map,-cref,-u,Reset_Handler -T board/linker_scripts/link.lds'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2 -g'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n'
    POST_ACTION += OBJCPY + ' -O ihex $TARGET rtthread.hex\n'
    POST_ACTION += SIZE + ' $TARGET\n'

elif PLATFORM == 'armcc':
    # toolchains
    CC = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --cpu ' + CPU 
    CFLAGS = '-c ' + DEVICE + ' --apcs=interwork --c99'
    CFLAGS += ' -mfpu=fpv5-sp-d16 -mfloat-abi=hard '
    AFLAGS = DEVICE + ' --apcs=interwork '
    LFLAGS = DEVICE + ' --scatter "board/linker_scripts/link.sct" --info sizes --info totals --info unused --info veneers --list rtthread.map --strict'

    CFLAGS += ' -I' + EXEC_PATH + '/ARM/ARMCC/INC'
    LFLAGS += ' --libpath ' + EXEC_PATH + '/ARM/ARMCC/LIB'

    CFLAGS += ' -D__MICROLIB '
    AFLAGS += ' --pd "__MICROLIB SETA 1" '
    LFLAGS += ' --library_type=microlib '
    EXEC_PATH += '/arm/armcc/bin/'

    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin \nfromelf -z $TARGET'

elif PLATFORM == 'iccarm':
    # toolchains
    CC = 'iccarm'
    AS = 'iasmarm'
    AR = 'iarchive'
    LINK = 'ilinkarm'
    TARGET_EXT = 'out'

    DEVICE = '-Dewarm' # + ' -D' + PART_TYPE

    CFLAGS = DEVICE
    CFLAGS += ' --diag_suppress Pa050'
    CFLAGS += ' --no_cse' 
    CFLAGS += ' --no_unroll' 
    CFLAGS += ' --no_inline' 
    CFLAGS += ' --no_code_motion' 
    CFLAGS += ' --no_tbaa' 
    CFLAGS += ' --no_clustering' 
    CFLAGS += ' --no_scheduling' 

    CFLAGS += ' --endian=little' 
    CFLAGS += ' --cpu=Cortex-M33' 
    CFLAGS += ' -e' 
    CFLAGS += ' --fpu=VFPv4_sp'

    CFLAGS += ' --dlib_config "' + EXEC_PATH + '/arm/INC/c/DLib_Config_Normal.h"'    
    CFLAGS += ' --silent'
        
    AFLAGS = DEVICE
    AFLAGS += ' -s+' 
    AFLAGS += ' -w+' 
    AFLAGS += ' -r' 
    AFLAGS += ' --cpu ' + CPU
    AFLAGS += ' --fpu VFPv5_sp'

    AFLAGS += ' -S'

    if BUILD == 'debug':
        CFLAGS += ' --debug'
        CFLAGS += ' -On'
    else:
        CFLAGS += ' -Oh'

    LFLAGS = ' --config "board/linker_scripts/link.icf"'
    LFLAGS += ' --entry __iar_program_start'    
    #LFLAGS += ' --silent'

    EXEC_PATH = EXEC_PATH + '/arm/bin/'
    POST_ACTION = ''
