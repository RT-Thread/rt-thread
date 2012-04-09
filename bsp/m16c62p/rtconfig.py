import os

# toolchains options
ARCH     = 'm16c'
CPU      = 'm16c62p'

CROSS_TOOL 	= 'iar'

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
	PLATFORM 	= 'gcc'
	EXEC_PATH 	= 'E:/Program Files/CodeSourcery/Sourcery G++ Lite/bin'
elif CROSS_TOOL == 'iar':
	PLATFORM 	= 'iar'
	IAR_PATH = 'C:/Program Files/IAR Systems/Embedded Workbench Evaluation 6.0'
#	EXEC_PATH 	= 'C:/Program Files/IAR Systems/Embedded Workbench Evaluation 6.0'
elif CROSS_TOOL == 'keil':
    print '================ERROR============================'
    print 'Not support keil yet!'
    print '================================================='
    exit(0)	

if os.getenv('RTT_EXEC_PATH'):
	EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'axf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -mcpu=arm920t'
    CFLAGS = DEVICE
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp' + ' -DTEXT_BASE=' + TextBase
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread_mini2440.map,-cref,-u,_start -T mini2440_ram.ld' + ' -Ttext ' + TextBase

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

elif PLATFORM == 'iar':
    # toolchains
    CC = 'iccm16c'
    AS = 'am16c'
    AR = 'xar'
    LINK = 'xlink'
    TARGET_EXT = 'mot'
    
    DEVICE = '--cpu M16C'
    
    EXEC_PATH = IAR_PATH + '/m16c/bin'
    
    AFLAGS = '-s+'
#    AFLAGS += ' -M<>' 
    AFLAGS += ' -w+' 
    AFLAGS += ' -r' 
    AFLAGS += ' -I"' + IAR_PATH + '/m16c/INC"'
        
    LFLAGS = '-xms'
    LFLAGS += ' -I"' + IAR_PATH + '/m16c/LIB"' 
    LFLAGS += ' -rt' 
    LFLAGS += ' -s __program_start' 
    LFLAGS += ' -D_CSTACK_SIZE=80' 
    LFLAGS += ' -D_ISTACK_SIZE=40' 
    LFLAGS += ' -D_DATA16_HEAP_SIZE=1000' 
    LFLAGS += ' -D_FAR_HEAP_SIZE=400'
    LFLAGS += ' -D_DATA20_HEAP_SIZE=400'
    LFLAGS += ' "' + IAR_PATH + '/m16c/LIB/CLIB/clm16cfnffwc.r34"' 
    LFLAGS += ' -e_small_write=_formatted_write' 
    LFLAGS += ' -e_medium_read=_formatted_read'
    
    CFLAGS = DEVICE
    CFLAGS += ' --data_model=far'
    CFLAGS += ' --calling_convention=normal' 
    CFLAGS += ' --variable_data=near' 
    CFLAGS += ' --constant_data=far' 
    CFLAGS += ' --code_segment=CODE' 
    CFLAGS += ' --debug' 
    CFLAGS += ' -e' 
    CFLAGS += ' --align_func 1' 
    CFLAGS += ' -I"' + IAR_PATH + '/m16c/INC"'
    CFLAGS += ' -I"' + IAR_PATH + '/m16c/INC/CLIB"' 
    CFLAGS += ' -Ol' 
    CFLAGS += ' --no_cse' 
    CFLAGS += ' --no_unroll' 
    CFLAGS += ' --no_inline' 
    CFLAGS += ' --no_code_motion' 
    CFLAGS += ' --no_tbaa'    
   
    POST_ACTION = ''
