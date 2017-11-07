import os

# toolchains options
ARCH='arm'
CPU='arm926'
CROSS_TOOL='gcc'

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery,

if  CROSS_TOOL == 'gcc':
	PLATFORM 	= 'gcc'
	EXEC_PATH 	= ''
elif CROSS_TOOL == 'keil':
    print '================ERROR============================'
    print 'Not support keil yet!'
    print '================================================='
    exit(0)
elif CROSS_TOOL == 'iar':
    print '================ERROR============================'
    print 'Not support iar yet!'
    print '================================================='
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
	EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc -mcpu=arm926ej-s -marm -fpic'
    AS = PREFIX + 'gcc -mcpu=arm926ej-s -marm -fpic'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'ld'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ''
    CFLAGS = DEVICE + ' -Wall '
    AFLAGS = ' -c' + DEVICE
    LFLAGS = DEVICE + ' -Map versatilepb.map -T versatilepb.lds '

    CPATH = ''
    LPATH = ''
    LIBS  = ['gcc']
    # FIXME 
    LIBPATH = ['/usr/lib/gcc/arm-none-eabi/4.8.2']

    if BUILD == 'debug':
        CFLAGS += ' -O0 -g '
        AFLAGS += ' -g '
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
