import os

# toolchains options
ARCH='sim'
#CROSS_TOOL='msvc' or 'gcc' or 'mingw'
#'msvc' and 'mingw' are both for windows
# 'gcc' is for linux
CROSS_TOOL='msvc'

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path 
if  CROSS_TOOL == 'gcc' or CROSS_TOOL == 'clang-analyze':
    CPU       = 'posix'
    PLATFORM  = 'gcc'
    EXEC_PATH = ''

elif  CROSS_TOOL == 'mingw':
    CPU       = 'win32'
    PLATFORM  = 'mingw'
    EXEC_PATH = r'D:\Program Files\CodeBlocks\MinGW\bin'

elif  CROSS_TOOL == 'msvc':
    CPU       = 'win32'
    PLATFORM  = 'cl'
    EXEC_PATH = ''
else:
    print "bad CROSS TOOL!"
    exit(1)

if os.getenv('RTT_EXEC_PATH'):
	EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
#BUILD = ''

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = ''
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'axf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -ffunction-sections -fdata-sections'
    DEVICE = '  '
    CFLAGS = DEVICE + ' -I/usr/include -w -D_REENTRANT'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    #LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread-linux.map -lpthread'
    LFLAGS = DEVICE + ' -Wl,-Map=rtthread-linux.map -pthread -T gcc.ld'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -g -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = ''

elif PLATFORM == 'mingw':
    # toolchains
    PREFIX = ''
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'exe'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -ffunction-sections -fdata-sections'
    DEVICE = '  '
    CFLAGS = DEVICE
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    DEFFILE_LFLAGS = DEVICE + ' -Wl,-Map=rtthread-win32.map,--output-def,rtthread.def -T mingw.ld '
    LFLAGS = DEVICE + ' -Wl,-Map=rtthread-win32.map -T mingw.ld '
    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -g -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = ''

elif PLATFORM == 'cl':
    # toolchains
    PREFIX = ''
    TARGET_EXT = 'exe'
    AS = PREFIX + 'cl'
    CC = PREFIX + 'cl'
    AR = PREFIX + 'cl'
    LINK = PREFIX + 'cl'
    AFLAGS = ''
    CFLAGS = ''
    LFLAGS = ''

    if BUILD == 'debug':
        CFLAGS += ' /MTd'
        LFLAGS += ' /DEBUG'
    else:
        CFLAGS += ' /MT'
        LFLAGS += ''

    CFLAGS += ' /ZI /Od /W 3 /WL '
    LFLAGS += ' /SUBSYSTEM:CONSOLE /MACHINE:X86 '

    CPATH = ''
    LPATH = ''

    POST_ACTION = ''
