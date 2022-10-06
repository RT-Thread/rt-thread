import os

# toolchains options
ARCH='arm'
CPU='am335x'
CROSS_TOOL='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM 	= 'gcc'
    EXEC_PATH 	= r'C:\Program Files (x86)\CodeSourcery\Sourcery_CodeBench_Lite_for_ARM_EABI\bin'
elif CROSS_TOOL == 'iar':
    PLATFORM    = 'iccarm'
    EXEC_PATH   = r'C:\Program Files\IAR Systems\Embedded Workbench 9.1'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

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
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,Reset_Handler -T link.lds'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2 -Wall'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2 -Wall'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' +\
                  SIZE + ' $TARGET \n'

elif PLATFORM == 'iccarm':
    # no toolchains, only ide
    EXEC_PATH = EXEC_PATH + '/arm/bin/'
