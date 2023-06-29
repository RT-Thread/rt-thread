import os

# toolchains options
ARCH='arm'
CPU='cortex-m33'
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
    PLATFORM     = 'gcc'
    EXEC_PATH     = r'/opt/gcc-arm-none-eabi-6_2-2016q4/bin'
elif CROSS_TOOL == 'keil':
    PLATFORM    = 'armclang'
    EXEC_PATH   = r'D:/Keil_v5'
elif CROSS_TOOL == 'iar':
    PLATFORM    = 'iccarm'
    EXEC_PATH   = r'C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.3'

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

    DEVICE = ' -mcpu=' + CPU + ' -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections'
    CFLAGS = DEVICE
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -Wa,-mimplicit-it=thumb '
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,Reset_Handler -T drivers/linker_scripts/link.lds'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2 -g'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

elif PLATFORM == 'armclang':
    # toolchains
    CC = 'armclang'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --cpu ' + CPU
    CFLAGS = ' -xc -std=c99 --target=arm-arm-none-eabi -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -c'
    CFLAGS += ' -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -D__MICROLIB -mlittle-endian -ffunction-sections'

    AFLAGS = ' --cpu=Cortex-M33 --fpu=FPv5-SP --li --pd "__MICROLIB SETA 1" --pd "__UVISION_VERSION SETA 531" --pd "ARMCM33_DSP_FP SETA 1"'

    LFLAGS = ' --cpu=Cortex-M33 --info sizes --info totals --info unused --info veneers --list ./build/ACM32F4.map --scatter ./build/ACM32F4.sct'
    LFLAGS += ' --library_type=microlib --strict'
    LFLAGS += ' --summary_stderr --info summarysizes --map --load_addr_map_info --xref --callgraph --symbols'

    EXEC_PATH += '/ARM/ARMCLANG/bin'

    if BUILD == 'debug':
        CFLAGS += ' -gdwarf-3 -O0'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -gdwarf-3 -O1'

    POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin \nfromelf -z $TARGET'

elif PLATFORM == 'iccarm':
    # toolchains
    CC = 'iccarm'
    CXX = 'iccarm'
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
    CFLAGS += ' --debug'
    CFLAGS += ' --endian=little'
    CFLAGS += ' --cpu=' + CPU
    CFLAGS += ' -e'
    CFLAGS += ' --fpu=VFPv4_sp'
    CFLAGS += ' --dlib_config "' + EXEC_PATH + '/arm/INC/c/DLib_Config_Normal.h"'
    CFLAGS += ' --silent'

    AFLAGS = DEVICE
    AFLAGS += ' -s+'
    AFLAGS += ' -w+'
    AFLAGS += ' -r'
    AFLAGS += ' --cpu ' + CPU
    AFLAGS += ' --fpu VFPv4_sp'
    AFLAGS += ' -S'

    if BUILD == 'debug':
        CFLAGS += ' --debug'
        CFLAGS += ' -On'
    else:
        CFLAGS += ' -Oh'

    CXXFLAGS = CFLAGS
    LFLAGS = ' --config "drivers/linker_scripts/link.icf"'
    LFLAGS += ' --entry __iar_program_start'


    CXXFLAGS = CFLAGS

    EXEC_PATH = EXEC_PATH + '/arm/bin/'
    POST_ACTION = 'ielftool --bin $TARGET rtthread.bin'
