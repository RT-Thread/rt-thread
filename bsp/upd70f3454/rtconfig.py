import os

# toolchains options
ARCH     = 'v850'
CPU      = '70f34'

CROSS_TOOL 	= 'iar'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    print('================ERROR============================')
    print('Not support gcc yet!')
    print('=================================================')
    exit(0)
elif CROSS_TOOL == 'iar':
    PLATFORM  = 'iccarm'
    EXEC_PATH = 'C:/Program Files/IAR Systems/Embedded Workbench 6.0 Evaluation_0'
elif CROSS_TOOL == 'keil':
    print('================ERROR============================')
    print('Not support keil yet!')
    print('=================================================')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'm32c-elf-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'out'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -mcpu=m16c'
    CFLAGS = DEVICE
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS = DEVICE + ' -nostartfiles' + ' -Wl,--gc-sections,-Map=rtthread_m16c.map,-cref,-u,_start -T m16c62p.ld'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O srec $TARGET rtthread.mot\n' + SIZE + ' $TARGET \n'

elif PLATFORM == 'iccarm':
    # toolchains
    CC = 'iccv850'
    AS = 'av850'
    AR = 'xar'
    LINK = 'xlink'
    TARGET_EXT = 'hex'

    DEVICE = '--cpu V850'

    AFLAGS = '-s+'
    AFLAGS = ' -v1'
#    AFLAGS += ' -M<>' 
    AFLAGS += ' -s+' 
    AFLAGS += ' -DCODE_MODEL_NORMAL' 
    AFLAGS += ' -DDATA_MODEL_TINY'
    AFLAGS += ' -w+'
    AFLAGS += ' -r'
    AFLAGS += ' -I"' + EXEC_PATH + '/v850/INC"'

    LFLAGS = '-xms'
    LFLAGS += ' -I"' + EXEC_PATH + '/v850/LIB"' 
    LFLAGS += ' -rt' 
    LFLAGS += ' -s __program_start' 
    LFLAGS += ' -D_CSTACK_SIZE=1000' 
    LFLAGS += ' "' + EXEC_PATH + '/v850/LIB/dl85nn1.r85"'
    LFLAGS += ' -D_HEAP_SIZE=0' 

#    LFLAGS += ' "' + EXEC_PATH + '/v850/lib/CLIB/clm16cfnffwc.r34"' 
#   LFLAGS += ' -e_small_write=_formatted_write' 
#    LFLAGS += ' -e_medium_read=_formatted_read'

#    CFLAGS = DEVICE
    CFLAGS = '--diag_suppress Pa050'
    CFLAGS += ' -v1' 
    CFLAGS += ' -mt' 
    CFLAGS += ' --code_model normal' 
    CFLAGS += ' --no_cse' 
    CFLAGS += ' --no_unroll' 
    CFLAGS += ' --no_inline' 
    CFLAGS += ' --no_code_motion' 
    CFLAGS += ' --dlib_config "' + EXEC_PATH + '/v850/LIB/dl85nn1.h"'
    CFLAGS += ' -I"' + EXEC_PATH + '/v850/INC"'
    CFLAGS += ' --no_tbaa' 
    CFLAGS += ' --debug' 
    CFLAGS += ' --lock_regs 0' 
    CFLAGS += ' --migration_preprocessor_extensions' 
    CFLAGS += ' -e' 
    CFLAGS += ' -Ol'

    EXEC_PATH = EXEC_PATH + '/v850/bin'

    POST_ACTION = ''
