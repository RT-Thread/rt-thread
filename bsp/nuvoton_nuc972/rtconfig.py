import os

# toolchains options
ARCH		='arm'
CPU        	='arm926'
CROSS_TOOL	='keil'

TextBase 	= '0x00000000'

if os.getenv('RTT_CC'):
	CROSS_TOOL 	= os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM 	= 'gcc'
    EXEC_PATH 	= r'E:/embStudio/tools/arm-2015.q3/bin'
    
    if os.getenv('RTT_EXEC_PATH'):
	    EXEC_PATH = os.getenv('RTT_EXEC_PATH')
elif CROSS_TOOL == 'keil':
	PLATFORM 	= 'armcc'
	EXEC_PATH 	= r'd:/Keil'
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
    #CFLAGS 		= DEVICE
    CFLAGS 		= DEVICE + ' -fno-pic -fno-builtin -fno-exceptions -ffunction-sections -fno-omit-frame-pointer'
    AFLAGS 		= ' -c' + DEVICE + ' -x assembler-with-cpp'
    AFLAGS += ' -IPlatform'
    LFLAGS 		= DEVICE + ' -Wl,--gc-sections,-Map=rtthread_nuc970.map,-cref,-u,Reset_Handler -T nuc970_ram.ld' + ' -Ttext ' + TextBase

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'
    
    CXXFLAGS = CFLAGS

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
    LFLAGS += ' --scatter  ' + LINK_FILE + '.sct'

    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = 'fromelf --bin $TARGET --output ' + TARGET_NAME + ' \n'
    POST_ACTION += 'fromelf -z $TARGET\n'
