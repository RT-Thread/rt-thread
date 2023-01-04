import os
# toolchains options
ARCH     = 'arm'
CPU      = 'cortex-a'
# toolchains options
CROSS_TOOL 	= 'gcc'

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')
if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR

if  CROSS_TOOL == 'gcc':
	PLATFORM = 'gcc'
	EXEC_PATH = r'C:\Program Files (x86)\GNU Tools ARM Embedded\6 2017-q1-update\bin'

if os.getenv('RTT_EXEC_PATH'):
	EXEC_PATH = os.getenv('RTT_EXEC_PATH')

#BUILD = 'debug'
BUILD = ''
MAP_FILE = 'rtthread_ma35d1.map'
LINK_FILE = 'linking_scripts/aarch32'
TARGET_NAME = 'rtthread.bin'

#------- GCC settings ----------------------------------------------------------
if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    CXX = PREFIX + 'g++'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    STRIP = PREFIX + 'strip'

    DEVICE = ' -march=armv8-a -mfpu=neon-vfpv4  -ftree-vectorize -ffast-math -msoft-float'
    CFLAGS = DEVICE + ' -Wall -fno-zero-initialized-in-bss '
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__'
    LFLAGS = DEVICE + ' -nostartfiles  -Wl,--gc-sections,-cref,-Map=' + MAP_FILE + ',-cref,-u,system_vectors' + ' -T ' + LINK_FILE + '.ld'
    CXXFLAGS = '  -march=armv8-a -mfpu=neon-vfpv4 -std=c++11 '

    M_CFLAGS = CFLAGS + ' -mlong-calls -fPIC '
    M_CXXFLAGS = CXXFLAGS + ' -mlong-calls -fPIC'
    M_LFLAGS = DEVICE + CXXFLAGS + ' -Wl,--gc-sections,-z,max-page-size=0x4' +\
                                ' -shared -fPIC -nostartfiles -nostdlib -static-libgcc'
    M_POST_ACTION = STRIP + ' -R .hash $TARGET\n' + SIZE + ' $TARGET \n'
    #M_BIN_PATH = r'z:\fatdisk\root'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2 -g'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS 

    POST_ACTION = OBJCPY + ' -O binary $TARGET ' + TARGET_NAME + '\n' 
    POST_ACTION += SIZE + ' $TARGET\n'


def dist_handle(BSP_ROOT, dist_dir):
    import sys
    cwd_path = os.getcwd()
    sys.path.append(os.path.join(os.path.dirname(BSP_ROOT), 'tools'))
    from sdk_dist import dist_do_building
    dist_do_building(BSP_ROOT, dist_dir)
