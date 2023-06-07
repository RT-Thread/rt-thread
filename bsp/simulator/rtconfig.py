import os
import sys
import SCons.Tool.MSCommon.vc

# toolchains options
ARCH='sim'
ASAN = False
#CROSS_TOOL='msvc' or 'gcc' or 'mingw'
#'msvc' and 'mingw' are both for windows
# 'gcc' is for linux
if sys.platform == 'win32':
    CROSS_TOOL='msvc'
else:
    CROSS_TOOL='gcc'
    ASAN = True

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path 
if  CROSS_TOOL == 'gcc' or CROSS_TOOL == 'clang-analyze':
    CPU       = 'posix'
    PLATFORM  = 'gcc'
    EXEC_PATH = '/usr/bin'

elif  CROSS_TOOL == 'mingw':
    CPU       = 'win32'
    PLATFORM  = 'mingw'
    EXEC_PATH = r'D:\Program Files\CodeBlocks\MinGW\bin'

elif  CROSS_TOOL == 'msvc':
    CPU       = 'win32'
    PLATFORM  = 'cl'
    EXEC_PATH = ''
    try:
        vc_version = ''
        vc_versions = SCons.Tool.MSCommon.vc.get_installed_vcs()
        if not vc_versions:
            print("No vc version!")
            exit(1)
        else:
            vc_version = vc_versions[0]
        EXEC_PATH = SCons.Tool.MSCommon.vc.find_vc_pdir(vc_version)
        if not EXEC_PATH:
            print('Installed VC %s failure!' % vc_version)
            exit(1)
        else:
            print('Successfully installed VC %s, path:%s' % (vc_version, EXEC_PATH))
    except:
        pass

else:
    print("Simulator does not support this CROSS TOOL!")
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
    # DEVICE = ' -m32 ' # open this when build 32bit target on 64bit PC
    CFLAGS = DEVICE + ' -I/usr/include -w -D_REENTRANT -D_LINUX -DHAVE_SYS_SIGNALS'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    # LFLAGS = DEVICE + ' -Wl,-Map=rtthread-linux.map -pthread -T gcc.ld' # open this when build 32bit target
    LFLAGS = DEVICE + ' -Wl,-Map=rtthread-linux.map -pthread -T gcc_elf64.ld' # open this when build 64bit target

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -g -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    if ASAN == True:
        CFLAGS += ' -Wall -g -O0 -fsanitize=address -fsanitize-recover=address,all -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fdiagnostics-color'
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
