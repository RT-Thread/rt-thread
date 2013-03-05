import os

# toolchains options
ARCH     = 'mips'
CPU      = 'jz47xx'

CROSS_TOOL  = 'gcc'

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
	PLATFORM 	= 'gcc'
	EXEC_PATH 	= '/home/bernard/workspace/jz/mips-2011.09/bin'
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
	
BUILD		= 'debug'

# toolchains
PREFIX = 'mips-sde-elf-'
CC = PREFIX + 'gcc'
AS = PREFIX + 'gcc'
AR = PREFIX + 'ar'
LINK = PREFIX + 'gcc'
TARGET_EXT = 'elf'
SIZE = PREFIX + 'size'
OBJDUMP = PREFIX + 'objdump'
OBJCPY = PREFIX + 'objcopy'

DEVICE = ' -mips32 -msoft-float'
CFLAGS = DEVICE + ' -EL -G0 -DRT_USING_MINILIBC -mno-abicalls -fno-pic -fno-builtin -fno-exceptions -ffunction-sections -fomit-frame-pointer'
AFLAGS = ' -c' + DEVICE + ' -EL -x assembler-with-cpp'
LFLAGS = DEVICE + ' -EL -Wl,--gc-sections,-Map=rtthread-jz47xx.map,-cref,-u,Reset_Handler -T jz47xx_ram.lds'

CPATH = ''
LPATH = ''

if BUILD == 'debug':
	CFLAGS += ' -O0 -gdwarf-2'
	AFLAGS += ' -gdwarf-2'
else:
	CFLAGS += ' -O2'

RT_USING_MINILIBC = True
DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
COPY_ACTION = 'copy rtthread.bin usbboot\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
