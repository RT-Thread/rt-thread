import os

# toolchains options
ARCH='arm'
CPU='cortex-m7'
CROSS_TOOL='gcc'

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR
if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'D:\Program Files (x86)\GNU Tools ARM Embedded\5.4 2016q3\bin'
elif CROSS_TOOL == 'keil':
	PLATFORM 	= 'armcc'
	EXEC_PATH 	= 'C:/Keil_v5'
elif CROSS_TOOL == 'iar':
    PLATFORM 	= 'iar'
    IAR_PATH    = r'C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.0'

if os.getenv('RTT_EXEC_PATH'):
	EXEC_PATH = os.getenv('RTT_EXEC_PATH')

#BUILD = 'debug'
BUILD = 'release'

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
    STRIP = PREFIX + 'strip'

    DEVICE = ' -mcpu=cortex-m7 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -ffunction-sections -fdata-sections'
    CFLAGS = DEVICE + ' -std=c99 -Wall -DUSE_HAL_DRIVER -D__ASSEMBLY__ -D__FPU_PRESENT -eentry'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -Wa,-mimplicit-it=thumb '
    LFLAGS = DEVICE + ' -lm -lgcc -lc' + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread-imxrt-gcc.map,-cref,-u,Reset_Handler -T ./Libraries/gcc/MIMXRT1052xxxxx_flexspi_nor.ld'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
        CFLAGS += ' -O0'
    else:
        CFLAGS += ' -O2 -Os'

    POST_ACTION = OBJCPY + ' -O binary --remove-section=.boot_data --remove-section=.image_vertor_table --remove-section=.ncache $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

    # module setting 
    CXXFLAGS = ' -Woverloaded-virtual -fno-exceptions -fno-rtti '
    M_CFLAGS = CFLAGS + ' -mlong-calls -fPIC '
    M_CXXFLAGS = CXXFLAGS + ' -mlong-calls -fPIC'
    M_LFLAGS = DEVICE + CXXFLAGS + ' -Wl,--gc-sections,-z,max-page-size=0x4' +\
                                    ' -shared -fPIC -nostartfiles -static-libgcc'
    M_POST_ACTION = STRIP + ' -R .hash $TARGET\n' + SIZE + ' $TARGET \n'

elif PLATFORM == 'armcc':
    # toolchains
    CC = 'armcc'
    CXX = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --cpu Cortex-M7.fp.sp'
    CFLAGS = DEVICE + ' --apcs=interwork'
    AFLAGS = DEVICE
    LFLAGS = DEVICE + ' --info sizes --info totals --info unused --info veneers --list rtthread-imxrt-mdk.map --scatter ./Libraries/arm/MIMXRT1052xxxxx_flexspi_nor.scf'

    CFLAGS += ' --diag_suppress=66,1296,186'
    CFLAGS += ' -I' + EXEC_PATH + '/ARM/RV31/INC'
    LFLAGS += ' --libpath ' + EXEC_PATH + '/ARM/RV31/LIB'

    EXEC_PATH += '/arm/bin40/'

    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS
    CFLAGS += ' --c99'

    POST_ACTION = 'fromelf -z $TARGET'
    # POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin \nfromelf -z $TARGET'

elif PLATFORM == 'iar':
    # toolchains
    CC = 'iccarm'
    AS = 'iasmarm'
    AR = 'iarchive'
    LINK = 'ilinkarm'
    TARGET_EXT = 'out'

    DEVICE = ' -D USE_STDPERIPH_DRIVER'

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
    CFLAGS += ' --cpu=Cortex-M7'
    CFLAGS += ' -e'
    CFLAGS += ' --fpu=None'
    CFLAGS += ' --dlib_config "' + IAR_PATH + '/arm/INC/c/DLib_Config_Normal.h"'
    CFLAGS += ' -Ol'
    CFLAGS += ' --use_c++_inline'

    AFLAGS = ''
    AFLAGS += ' -s+'
    AFLAGS += ' -w+'
    AFLAGS += ' -r'
    AFLAGS += ' --cpu Cortex-M7'
    AFLAGS += ' --fpu None'

    LFLAGS = ' --config ./Libraries/iar/MIMXRT1052xxxxx_flexspi_nor.icf'
    LFLAGS += ' --redirect _Printf=_PrintfTiny'
    LFLAGS += ' --redirect _Scanf=_ScanfSmall'
    LFLAGS += ' --entry __iar_program_start'

    EXEC_PATH = IAR_PATH + '/arm/bin/'
    POST_ACTION = ''
