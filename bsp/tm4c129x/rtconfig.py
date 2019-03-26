# BSP Note: For TI EK-TM4C1294XL Tiva C Series Connected LancuhPad    (REV D)

import os

# toolchains options
ARCH='arm'
CPU='cortex-m4'
CROSS_TOOL='keil'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')
    
#device options
PART_TYPE = 'PART_TM4C129XNCZAD'
# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR
if  CROSS_TOOL == 'gcc':
    PLATFORM     = 'gcc'
    EXEC_PATH    = r'D:\ArdaArmTools\Sourcery_Lite\bin'
elif CROSS_TOOL == 'keil':
    PLATFORM     = 'armcc'
    EXEC_PATH    = r'C:\Keil_v5'
elif CROSS_TOOL == 'iar':
    PLATFORM     = 'iar'
    EXEC_PATH    = 'C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.0'
    
if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

#BUILD = 'debug'
BUILD = 'release'

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
    
    DEVICE = ' -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -ffunction-sections -fdata-sections'
    CFLAGS = DEVICE + ' -Dgcc'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -Wa,-mimplicit-it=thumb '
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread-tm4c129x.map,-cref,-u,Reset_Handler -T tm4c_rom.ld'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2 -g'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

elif PLATFORM == 'armcc':
    # toolchains
    CC = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --cpu Cortex-M4.fp '
    CFLAGS = '-c ' + DEVICE + ' --apcs=interwork --c99'
    AFLAGS = DEVICE + ' --apcs=interwork '
    LFLAGS = DEVICE + ' --scatter tm4c_rom.sct --info sizes --info totals --info unused --info veneers --list rtthread-tm4c129x.map --strict'

    CFLAGS += ' -I' + EXEC_PATH + '/ARM/ARMCC/INC'
    LFLAGS += ' --libpath ' + EXEC_PATH + '/ARM/ARMCC/LIB'
    
    EXEC_PATH += '/arm/armcc/bin/'

    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin \nfromelf -z $TARGET'

elif PLATFORM == 'iar':
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
    CFLAGS += ' --cpu=Cortex-M4' 
    CFLAGS += ' -e' 
    CFLAGS += ' --fpu=VFPv4_sp'
    CFLAGS += ' --dlib_config "' + EXEC_PATH + '/arm/INC/c/DLib_Config_Normal.h"'    
    CFLAGS += ' --silent'

    AFLAGS = DEVICE
    AFLAGS += ' -s+' 
    AFLAGS += ' -w+' 
    AFLAGS += ' -r' 
    AFLAGS += ' --cpu Cortex-M4' 
    AFLAGS += ' --fpu VFPv4_sp' 
    AFLAGS += ' -S'
    
    if BUILD == 'debug':
        CFLAGS += ' --debug' 
        CFLAGS += ' -On'    
    else:
        CFLAGS += ' -Oh'        
    
    LFLAGS = ' --config "tm4c_rom.icf"'
    LFLAGS += ' --entry __iar_program_start'    
    #LFLAGS += ' --silent'
    
    EXEC_PATH = EXEC_PATH + '/arm/bin/'
    POST_ACTION = ''