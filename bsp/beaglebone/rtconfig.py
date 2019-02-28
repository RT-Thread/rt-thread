import os

# toolchains options
ARCH='arm'
CPU='am335x'
BOARD=CPU+'-beaglebone'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')
else:
    CROSS_TOOL='gcc'

if  CROSS_TOOL == 'gcc':
    PLATFORM 	= 'gcc'
    if os.getenv('RTT_EXEC_PATH'):
        EXEC_PATH = os.getenv('RTT_EXEC_PATH')
    else:
        EXEC_PATH = r'C:\Program Files (x86)\CodeSourcery\Sourcery_CodeBench_Lite_for_ARM_EABI\bin'
elif CROSS_TOOL == 'armcc':
    PLATFORM 	= 'armcc'
    if os.getenv('RTT_EXEC_PATH'):
        EXEC_PATH = os.getenv('RTT_EXEC_PATH')
    else:
        EXEC_PATH = r'C:\Keil_v5\ARM\ARMCC\bin'
elif CROSS_TOOL == 'armclang':
    PLATFORM 	= 'armclang'
    if os.getenv('RTT_EXEC_PATH'):
        EXEC_PATH = os.getenv('RTT_EXEC_PATH')
    else:
        EXEC_PATH = r'C:\Keil_v5\ARM\ARMCLANG\bin'

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -Wall -march=armv7-a -mtune=cortex-a8'+\
             ' -ftree-vectorize -ffast-math -mfpu=vfpv3-d16 -mfloat-abi=softfp'
    #DEVICE = ' '
    CFLAGS = DEVICE
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__ -I.'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=' + BOARD + '.map,-cref,-u,system_vectors -T ' + BOARD + '.lds'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2 -DNDEBUG'

    CXXFLAGS = CFLAGS
    POST_ACTION = OBJCPY + ' -O binary $TARGET ' + BOARD + '.bin\n' + SIZE + ' $TARGET \n'

elif PLATFORM == 'armcc':
    # toolchains
    CC = 'armcc --c99 --gnu'
    CXX = 'armcc --cpp11 --gnu'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    COMFLAGS  = ' --cpu=Cortex-A8 --fpu=VFPv3_D16 --unaligned_access'
    COMFLAGS += ' -J' + EXEC_PATH + '/../include'
    if BUILD == 'debug':
        COMFLAGS += ' -g -O0'
    else:
        COMFLAGS += ' -O3 -DNDEBUG'

    CC += COMFLAGS
    CXX += COMFLAGS
    CFLAGS = ''
    CXXFLAGS = ''

    AFLAGS  = ' --cpu=Cortex-A8 --unaligned_access --diag_style=ide --no_brief_diagnostics'
    AFLAGS += ' --cpreproc --cpreproc_opts=--cpu=Cortex-A8,-I.'
    if BUILD == 'debug':
        AFLAGS += ' -g'

    LFLAGS  = ' --cpu=Cortex-A8 --info=sizes,totals,unused,veneers --diag_style=ide --datacompressor=off --no_autoat --entry=system_vectors'
    LFLAGS += ' --map --list=' + BOARD + '.map --scatter=' + BOARD + '.sct'
    if BUILD == 'debug':
        LFLAGS += ' --debug --locals'
    else:
        LFLAGS += ' --no_debug --no_locals'

    POST_ACTION = 'fromelf --bin $TARGET --output ' + BOARD + '.bin \nfromelf -z $TARGET'

elif PLATFORM == 'armclang':
    # toolchains
    CC = 'armclang'
    CXX = 'armclang'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    CFLAGS  = ' --target=arm-arm-none-eabi -mcpu=cortex-a8 -mfloat-abi=hard -munaligned-access'
    CFLAGS += ' -fshort-wchar -fdiagnostics-format=msvc -fno-exceptions'
    CFLAGS += ' -Wno-reserved-user-defined-literal -Wno-unused-const-variable'
    CFLAGS += ' -Wno-incompatible-library-redeclaration'
    CFLAGS += ' -I' + EXEC_PATH + '/../include'
    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
    else:
        CFLAGS += ' -O3 -DNDEBUG' ' -Wno-unused-variable'
    CXXFLAGS = CFLAGS

    AFLAGS  = ' --cpu=Cortex-A8 --unaligned_access --diag_style=ide --no_brief_diagnostics'
    AFLAGS += ' --cpreproc --cpreproc_opts=--target=arm-arm-none-eabi,-mcpu=cortex-a8,-I.'
    if BUILD == 'debug':
        AFLAGS += ' -g'

    LFLAGS  = ' --cpu=Cortex-A8 --info=sizes,totals,unused,veneers --diag_style=ide --datacompressor=off --no_autoat --entry=system_vectors'
    LFLAGS += ' --map --list=' + BOARD + '.map --scatter=' + BOARD + '.sct'
    if BUILD == 'debug':
        LFLAGS += ' --debug --locals'
    else:
        LFLAGS += ' --no_debug --no_locals'

    POST_ACTION = 'fromelf --bin $TARGET --output ' + BOARD + '.bin \nfromelf -z $TARGET'
