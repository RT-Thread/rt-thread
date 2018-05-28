import os

# toolchains options
ARCH		='arm'
CPU        	='arm926'
CROSS_TOOL	='gcc'

TextBase 	= '0x00080000'

if os.getenv('RTT_CC'):
	CROSS_TOOL 	= os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM 	= 'gcc'
    EXEC_PATH 	= r'E:/embTools/arm-2014.05/bin'
    
    if os.getenv('RTT_EXEC_PATH'):
	    EXEC_PATH = os.getenv('RTT_EXEC_PATH')
elif CROSS_TOOL == 'keil':
	PLATFORM 	= 'armcc'
	EXEC_PATH 	= r'D:/Keil'
elif CROSS_TOOL == 'iar':
	PLATFORM 	= 'iar'
	IAR_PATH 	= 'D:/IAR Systems/Embedded Workbench 7.3'
else:
    print ('================ERROR============================')
    print ('unknown platform!')
    print ('=================================================')
    exit(0)

BUILD = 'debug'
MAP_FILE = 'rtthread_nuc970.map'
LINK_FILE = 'nuc970_ram'
TARGET_NAME = 'rtthread.bin'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX 		= 'arm-none-eabi-'
    CC 			= PREFIX + 'gcc'
    CXX 		= PREFIX + 'g++'
    AS 			= PREFIX + 'gcc'
    AR 			= PREFIX + 'ar'
    LINK 		= PREFIX + 'g++'
    TARGET_EXT 	= 'elf'
    SIZE 		= PREFIX + 'size'
    OBJDUMP 	= PREFIX + 'objdump'
    OBJCPY 		= PREFIX + 'objcopy'
    
    DEVICE 		= ' -mcpu=arm926ej-s'
    CFLAGS 		= DEVICE + ' -fno-pic -fno-builtin -fno-exceptions -ffunction-sections -fdata-sections -fno-omit-frame-pointer'
    AFLAGS 		= ' -c' + DEVICE + ' -x assembler-with-cpp'
    AFLAGS += ' -IPlatform'
    LFLAGS 		= DEVICE + ' -Wl,--gc-sections,-Map=rtthread_nuc970.map,-cref,-u,Reset_Handler -T nuc970_ram.ld' + ' -Ttext ' + TextBase

	#add definition...
    CFLAGS		+= ' -DWEBS -DRTT_SL -DNDEBUG'

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS
    CFLAGS += ' -std=gnu99'
    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
#------- Keil settings ---------------------------------------------------------
elif PLATFORM == 'armcc':
    # toolchains
    CC = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'elf'
    EXEC_PATH += '/arm/armcc/bin/'

    DEVICE = ' --cpu ARM926EJ-S'
    CFLAGS = DEVICE + ' --c99 --apcs=interwork --diag_suppress=870'
    AFLAGS = DEVICE + ' -Iplatform'
    LFLAGS = DEVICE + ' --strict'
    LFLAGS += ' --info sizes --info totals --info unused --info veneers'
    LFLAGS += ' --list ' + MAP_FILE
    LFLAGS += ' --scatter  ' + LINK_FILE + '.scat'

    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = 'fromelf --bin $TARGET --output ' + TARGET_NAME + ' \n'
    POST_ACTION += 'fromelf -z $TARGET\n'
#------- IAR settings ----------------------------------------------------------
elif PLATFORM == 'iar':
    # toolchains
    CC = 'iccarm'
    AS = 'iasmarm'
    AR = 'iarchive'
    LINK = 'ilinkarm'
    TARGET_EXT = 'out'


    CFLAGS =  ' --cpu ARM926EJ-S'
    CFLAGS += ' --diag_suppress Pa050'
    CFLAGS += ' --no_cse'
    CFLAGS += ' --no_unroll'
    CFLAGS += ' --no_inline'
    CFLAGS += ' --no_code_motion'
    CFLAGS += ' --no_tbaa'
    CFLAGS += ' --no_clustering'
    CFLAGS += ' --no_scheduling'

    CFLAGS += ' --endian=little'
    CFLAGS += ' -e'
    CFLAGS += ' --fpu=none'
    CFLAGS += ' --dlib_config "' + IAR_PATH + '/arm/INC/c/DLib_Config_Normal.h"'
    CFLAGS += ' --silent'

    AFLAGS =  ' --cpu ARM926EJ-S'
    AFLAGS += ' -s+'
    AFLAGS += ' -w+'
    AFLAGS += ' -r'
    AFLAGS += ' --fpu none'
    AFLAGS += ' -S'
    AFLAGS += ' -Iplatform'
    
    if BUILD == 'debug':
        CFLAGS += ' --debug'
        CFLAGS += ' -On'
    else:
        CFLAGS += ' -Oh'

    LFLAGS = '--config ' + LINK_FILE +'.icf'
    LFLAGS += ' --entry __iar_program_start'
    LFLAGS += ' --map ' + MAP_FILE
    LFLAGS += ' --silent'

    EXEC_PATH = IAR_PATH + '/arm/bin/'
    POST_ACTION = 'ielftool  --silent --bin $TARGET ' + TARGET_NAME