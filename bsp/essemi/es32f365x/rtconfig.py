import os
import sys

# toolchains options
CROSS_TOOL = 'keil'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

# device options
ARCH = 'arm'
CPU = 'cortex-m3'

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR
if  CROSS_TOOL  == 'gcc': # not support gcc yet
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'C:/GCC'

elif CROSS_TOOL == 'keil':
    PLATFORM    = 'armcc'
    EXEC_PATH   = r'C:/Keil'

elif CROSS_TOOL == 'iar': # not support iar yet
    PLATFORM    = 'iccarm'
    EXEC_PATH   = r'C:/IAR'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
#BUILD = 'release'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    DEVICE = ' -mcpu=' + CPU + ' -mthumb -ffunction-sections -fdata-sections'
    CFLAGS = DEVICE
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -Wa,-mimplicit-it=thumb'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,Reset_Handler -T board/linker_scripts/link.lds'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2 -g'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + OBJCPY + ' -O ihex $TARGET rtthread.hex\n' + SIZE + ' $TARGET \n'
elif PLATFORM == 'armcc':
    # toolchains
    CC = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --device DARMSTM'
    CFLAGS = '-c ' + DEVICE + ' --apcs=interwork --c99'
    AFLAGS = DEVICE + ' --apcs=interwork '
    LFLAGS = DEVICE + ' --scatter "board/linker_scripts/link.sct" --info sizes --info totals --info unused --info veneers --list rtthread.map  --strict'

    CFLAGS += ' -I' + EXEC_PATH + '/ARM/ARMCC/include'
    LFLAGS += ' --libpath ' + EXEC_PATH + '/ARM/ARMCC/lib'

    CFLAGS += ' -D__MICROLIB '
    AFLAGS += ' --pd "__MICROLIB SETA 1" '
    LFLAGS += ' --library_type=microlib '
    EXEC_PATH += '/ARM/ARMCC/bin'

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

    DEVICE = '-Dewarm'

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
    CFLAGS += ' --cpu=Cortex-M0' 
    CFLAGS += ' -e' 
    CFLAGS += ' --fpu=None'
    CFLAGS += ' --dlib_config "' + EXEC_PATH + '/arm/INC/c/DLib_Config_Normal.h"'    
    CFLAGS += ' --silent'

    AFLAGS = DEVICE
    AFLAGS += ' -s+' 
    AFLAGS += ' -w+' 
    AFLAGS += ' -r' 
    AFLAGS += ' --cpu Cortex-M0' 
    AFLAGS += ' --fpu None' 
    AFLAGS += ' -S'

    LFLAGS = ' --config "board\linker_scripts\link.icf"'
    LFLAGS += ' --redirect _Printf=_PrintfTiny' 
    LFLAGS += ' --redirect _Scanf=_ScanfSmall' 
    if BUILD == 'debug':
        CFLAGS += ' --debug'
        CFLAGS += ' -On'
    else:
        CFLAGS += ' -Oh'

    LFLAGS += ' --entry __iar_program_start'
    EXEC_PATH = EXEC_PATH + '/arm/bin/'
    POST_ACTION = ''
