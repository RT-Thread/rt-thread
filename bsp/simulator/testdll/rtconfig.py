# bsp name
BSP = 'simulator'

# toolchains
EXEC_PATH = ''
PREFIX = ''
TARGET_EXT = 'dll'
AS = PREFIX + 'cl'
CC = PREFIX + 'cl'
AR = PREFIX + 'cl'
LINK = PREFIX + 'cl'
AFLAGS = ''
CFLAGS = ''
LFLAGS = ''
BUILD = 'debug'

if BUILD == 'debug':
    CFLAGS += ' /MTd'
    LFLAGS += ' /DEBUG'
else:
    CFLAGS += ' /MT'
    LFLAGS += ''

CFLAGS += ' /ZI /Od /W 3 /WL'
LFLAGS += ' /DEF:rttapp.def /SUBSYSTEM:CONSOLE /MACHINE:X86'
#LFLAGS += ' /DEF:rttapp.def /SUBSYSTEM:WINDOWS /MACHINE:X86' #/ENTRY:mainCRTStartup 

CPATH = ''
LPATH = ''

'''
EXEC_PATH 	= 'C:/Program Files/CodeSourcery/Sourcery G++ Lite/bin'
PREFIX = 'arm-none-eabi-'
CC = PREFIX + 'gcc'
CXX = PREFIX + 'g++'
AS = PREFIX + 'gcc'
AR = PREFIX + 'ar'
LINK = PREFIX + 'gcc'
TARGET_EXT = 'so'
SIZE = PREFIX + 'size'
OBJDUMP = PREFIX + 'objdump'
OBJCPY = PREFIX + 'objcopy'

DEVICE = ' -mcpu=arm920t'
CFLAGS = DEVICE + ' -O0 -fPIC -DFTK_AS_PLUGIN -DRT_THREAD '
AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
LFLAGS = DEVICE + ' -Wl,-z,max-page-size=0x4 -shared -fPIC -nostdlib -s'

CPATH = ''
LPATH = ''
'''
