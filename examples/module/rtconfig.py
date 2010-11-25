import SCons.cpp

EXEC_PATH 	= 'E:/Program Files/CodeSourcery/Sourcery G++ Lite/bin'
BUILD = 'debug'

# toolchains
PREFIX = 'arm-none-eabi-'
CC = PREFIX + 'gcc'
AS = PREFIX + 'gcc'
AR = PREFIX + 'ar'
LINK = PREFIX + 'ld'
TARGET_EXT = 'axf'
SIZE = PREFIX + 'size'
OBJDUMP = PREFIX + 'objdump'
OBJCPY = PREFIX + 'objcopy'
CFLAGS = ''
AFLAGS = ''
LFLAGS = ''

CPATH = ''
LPATH = ''

if BUILD == 'debug':
	CFLAGS += ' -O0 -gdwarf-2'
	AFLAGS += ' -gdwarf-2'
else:
        CFLAGS += ' -O2'