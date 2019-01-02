import os

# toolchains options
ARCH='sim'
#CROSS_TOOL='msvc' or 'gcc' or 'mingw'
#'msvc' and 'mingw' are both for windows
# 'gcc' is for linux
CROSS_TOOL='mingw'

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
    print("bad CROSS TOOL!")
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
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -ffunction-sections -fdata-sections'
    DEVICE = '  '
    CFLAGS = DEVICE + ' -I/usr/include -w -D_REENTRANT -D_LINUX -DHAVE_SYS_SIGNALS'
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
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'g++'
    TARGET_EXT = 'exe'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ''
    CFLAGS = DEVICE + ' -D_Win32 -DNO_OLDNAMES -fno-pic -fno-builtin -fno-exceptions -fno-omit-frame-pointer'

    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS = DEVICE + ' -static-libgcc  -Wl,--gc-sections,-Map=rtthread-win32.map -T mingw.ld '
    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -g -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS
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

    CFLAGS += ' /Zi /Od /W 3 /WL /D_Win32'
    LFLAGS += ' /SUBSYSTEM:CONSOLE /MACHINE:X86 /INCREMENTAL:NO'

    CPATH = ''
    LPATH = ''

    POST_ACTION = ''
