import os

# toolchains options
ARCH='arm'
CPU='cortex-m3'
CROSS_TOOL='gcc'

# bsp lib config
BSP_LIBRARY_TYPE = None

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')
if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR
if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'C:\Users\XXYYZZ'
elif CROSS_TOOL == 'keil':
    PLATFORM    = 'armcc'
    EXEC_PATH   = r'C:/Keil_v5'
elif CROSS_TOOL == 'iar':
    PLATFORM    = 'iar'
    EXEC_PATH   = r'C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.0'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

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

    DEVICE = ' -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections'
    CCFLAGS = DEVICE + ' -Dgcc'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -Wa,-mimplicit-it=thumb '
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rt-thread.map,-cref,-u,Reset_Handler -T board/linker_scripts/link.lds'
    CFLAGS = ' -std=c99'
    CXXFLAGS = ' -std=c++11'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CCFLAGS += ' -O0 -gdwarf-2 -g'
        AFLAGS += ' -gdwarf-2'
    else:
        CCFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

elif PLATFORM == 'armcc':
    # toolchains
    CC = 'armcc'
    CXX = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    CFLAGS = ' --c99'
    CXXFLAGS = ' --cpp11'
    DEVICE = ' --cpu Cortex-M3 '
    CCFLAGS = '-c ' + DEVICE + ' --apcs=interwork'
    AFLAGS = DEVICE + ' --apcs=interwork '
    LFLAGS = DEVICE + ' --scatter "board\linker_scripts\link.sct" --info sizes --info totals --info unused --info veneers --list rt-thread.map --strict'
    CCFLAGS += ' -I' + EXEC_PATH + '/ARM/ARMCC/include'
    LFLAGS += ' --libpath=' + EXEC_PATH + '/ARM/ARMCC/lib'

    CFLAGS += ' -D__MICROLIB '
    AFLAGS += ' --pd "__MICROLIB SETA 1" '
    LFLAGS += ' --library_type=microlib '
    EXEC_PATH += '/ARM/ARMCC/bin/'

    if BUILD == 'debug':
        CCFLAGS += ' -g -O0'
        AFLAGS += ' -g'
    else:
        CCFLAGS += ' -O2'

    POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin \nfromelf -z $TARGET'

elif PLATFORM == 'iar':
    # toolchains
    CC = 'iccarm'
    CXX = 'iccarm'
    AS = 'iasmarm'
    AR = 'iarchive'
    LINK = 'ilinkarm'
    TARGET_EXT = 'out'

    DEVICE = '-Dewarm'

    CCFLAGS = DEVICE
    CCFLAGS += ' --diag_suppress Pa050'
    CCFLAGS += ' --no_cse'
    CCFLAGS += ' --no_unroll'
    CCFLAGS += ' --no_inline'
    CCFLAGS += ' --no_code_motion'
    CCFLAGS += ' --no_tbaa'
    CCFLAGS += ' --no_clustering'
    CCFLAGS += ' --no_scheduling'
    CCFLAGS += ' --endian=little'
    CCFLAGS += ' --cpu=Cortex-M3'
    CCFLAGS += ' -e'
    CCFLAGS += ' --fpu=None'
    CCFLAGS += ' --dlib_config "' + EXEC_PATH + '/arm/INC/c/DLib_Config_Normal.h"'
    CCFLAGS += ' --silent'

    AFLAGS = DEVICE
    AFLAGS += ' -s+'
    AFLAGS += ' -w+'
    AFLAGS += ' -r'
    AFLAGS += ' --cpu Cortex-M3'
    AFLAGS += ' --fpu None'
    AFLAGS += ' -S'

    if BUILD == 'debug':
        CCFLAGS += ' --debug'
        CCFLAGS += ' -On'
    else:
        CCFLAGS += ' -Oh'

    LFLAGS = ' --config "board/linker_scripts/link.icf"'
    LFLAGS += ' --entry __iar_program_start'
    
    CFLAGS = ' '
    CXXFLAGS = ' '
    
    EXEC_PATH = EXEC_PATH + '/arm/bin/'
    POST_ACTION = 'ielftool --bin $TARGET rtthread.bin'
