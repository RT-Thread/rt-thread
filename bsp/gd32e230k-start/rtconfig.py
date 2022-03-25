import os

# toolchains options
ARCH='arm'
CPU='cortex-m23'
CROSS_TOOL='keil'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR
if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'D:/toolchain/gnu_tools_arm_embedded/5.4_2016q3/bin'
elif CROSS_TOOL == 'keil':
    PLATFORM 	= 'armclang'
    EXEC_PATH 	= r'C:/Keil_v5'
elif CROSS_TOOL == 'iar':
    PLATFORM 	= 'iar'
    EXEC_PATH 	= r'C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.0'

if os.getenv('RTT_EXEC_PATH'):
	EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

if PLATFORM == 'gcc':
    # tool-chains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
	
    DEVICE = ' -mcpu=cortex-m23 -mthumb -ffunction-sections -fdata-sections'
    CFLAGS = DEVICE + ' -Dgcc' # -D' + PART_TYPE
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -Wa,-mimplicit-it=thumb '
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread-gd32.map,-cref,-u,Reset_Handler -T gd32_rom.ld'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2 -g'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

elif PLATFORM == 'armclang':
    # toolchains
    CC = 'armclang'
    CXX = 'armclang'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --cpu Cortex-M23 '
    CFLAGS = ' --target=arm-arm-none-eabi -mcpu=cortex-M23 '
    CFLAGS += ' -mcpu=cortex-M23 '
    CFLAGS += ' -c -fno-rtti -funsigned-char -fshort-enums -fshort-wchar '
    CFLAGS += ' -gdwarf-3 -ffunction-sections '
    AFLAGS = DEVICE + ' --apcs=interwork '
    LFLAGS = DEVICE + ' --info sizes --info totals --info unused --info veneers '
    LFLAGS += ' --list rt-thread-gd32.map '
    LFLAGS += r' --strict --scatter "gd32_rom.sct" '
    CFLAGS += ' -I' + EXEC_PATH + '/ARM/ARMCLANG/include'
    LFLAGS += ' --libpath=' + EXEC_PATH + '/ARM/ARMCLANG/lib'

    EXEC_PATH += '/ARM/ARMCLANG/bin/'

    if BUILD == 'debug':
        CFLAGS += ' -g -O1' # armclang recommend
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'
        
    CXXFLAGS = CFLAGS
    CFLAGS += ' -std=c99'

    POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin \nfromelf -z $TARGET'

elif PLATFORM == 'iar':
    # toolchains
    CC = 'iccarm'
    AS = 'iasmarm'
    AR = 'iarchive'
    LINK = 'ilinkarm'
    TARGET_EXT = 'out'

    DEVICE = ' -D USE_STDPERIPH_DRIVER' + ' -D GD32F30X_HD'

    CFLAGS = DEVICE
    CFLAGS += ' --diag_suppress Pa050'
    CFLAGS += ' --no_cse'
    CFLAGS += ' --no_unroll'
    CFLAGS += ' --no_inline'
    CFLAGS += ' --no_code_motion'
    CFLAGS += ' --no_tbaa'
    CFLAGS += ' --no_clustering'
    CFLAGS += ' --no_scheduling'
    CFLAGS += ' --debug'
    CFLAGS += ' --endian=little'
    CFLAGS += ' --cpu=Cortex-M23'
    CFLAGS += ' -e'
    CFLAGS += ' --fpu=None'
    CFLAGS += ' --dlib_config "' + EXEC_PATH + '/arm/INC/c/DLib_Config_Normal.h"'
    CFLAGS += ' -Ol'
    CFLAGS += ' --use_c++_inline'

    AFLAGS = ''
    AFLAGS += ' -s+'
    AFLAGS += ' -w+'
    AFLAGS += ' -r'
    AFLAGS += ' --cpu Cortex-M23'
    AFLAGS += ' --fpu None'

    LFLAGS = ' --config gd32_rom.icf'
    LFLAGS += ' --redirect _Printf=_PrintfTiny'
    LFLAGS += ' --redirect _Scanf=_ScanfSmall'
    LFLAGS += ' --entry __iar_program_start'

    EXEC_PATH += '/arm/bin/'
    POST_ACTION = ''

