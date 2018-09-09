import os

# toolchains options
ARCH='arm'
CPU='am335x'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')
else:
    CROSS_TOOL='gcc'

if  CROSS_TOOL == 'gcc':
    PLATFORM 	= 'gcc'
    if os.getenv('RTT_EXEC_PATH'):
        EXEC_PATH = os.getenv('RTT_EXEC_PATH')
    else:
        EXEC_PATH 	= r'C:\Program Files (x86)\CodeSourcery\Sourcery_CodeBench_Lite_for_ARM_EABI\bin'
elif CROSS_TOOL == 'armclang':
    PLATFORM 	= 'armclang'
    #EXEC_PATH	= r'C:\Program Files\DS-5 v5.29.1\sw\ARMCompiler6.10.1\bin'
    EXEC_PATH 	= r'C:\Keil_v5\ARM\ARMCompiler6.10.1\bin'

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
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread-beaglebone.map,-cref,-u,Reset_Handler -T beaglebone_ram.lds'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2 -Wall'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2 -Wall'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' +\
                  SIZE + ' $TARGET \n'

elif PLATFORM == 'armclang':
    # toolchains
    CC = 'armclang'
    CXX = 'armclang'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    CFLAGS  = ' --target=arm-arm-none-eabi -mcpu=cortex-a8 -mfloat-abi=hard -mno-unaligned-access'
    CFLAGS += ' -D__CLANG_ARM -D__align(n)="__attribute__((aligned(n)))"'
    CFLAGS += ' -D__weak="__attribute__((weak))" -Dasm="__asm" -D__asm__="__asm"'
    CFLAGS += ' -fshort-wchar -fdiagnostics-format=msvc -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables'
    CFLAGS += ' -Wno-nonportable-include-path -Wno-invalid-source-encoding -Wunused-variable -Wformat -Wuninitialized -Wfloat-conversion'
    CFLAGS += ' -Wno-unicode-homoglyph -Wno-unused-command-line-argument -Wno-reserved-user-defined-literal -Wno-unused-const-variable'
    CFLAGS += ' -Wno-incompatible-library-redeclaration'

    AFLAGS  = ' --cpu=Cortex-A8 --no_unaligned_access --diag_style=ide --no_brief_diagnostics'
    AFLAGS += ' --cpreproc --cpreproc_opts=--target=arm-arm-none-eabi,-mcpu=cortex-a8,-Wno-nonportable-include-path,-Wno-unicode-homoglyph'
    LFLAGS  = ' --cpu=Cortex-A8 --info=sizes,totals,unused,veneers --diag_style=ide --datacompressor=off --no_autoat --entry=system_vectors'
    LFLAGS += ' --map --list=am335x.map --symdefs=am335x.sym --scatter=am335x.sct'

    CFLAGS += ' -I' + EXEC_PATH + '/../include'

    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
        AFLAGS += ' -g'
        LFLAGS += ' --debug --locals'
    else:
        CFLAGS += ' -O3' ' -Wno-unused-variable'
        LFLAGS += ' --no_debug --no_locals'

    CXXFLAGS = CFLAGS

    POST_ACTION = 'fromelf --bin $TARGET --output am335x.bin \nfromelf -z $TARGET'
