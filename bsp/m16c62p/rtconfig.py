import os

# toolchains options
ARCH     = 'm16c'
CPU      = 'm16c62p'

CROSS_TOOL 	= 'iar'

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
	PLATFORM 	= 'gcc'
	EXEC_PATH 	= 'C:/Program Files/Renesas/Hew/Tools/KPIT Cummins/GNUM16CM32C-ELF/v11.01/m32c-elf/bin'
elif CROSS_TOOL == 'iar':
	PLATFORM  = 'iccarm'
	EXEC_PATH = 'C:/Program Files/IAR Systems/Embedded Workbench Evaluation 6.0'
#	EXEC_PATH 	= 'C:/Program Files/IAR Systems/Embedded Workbench Evaluation 6.0'
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
    CC = 'iccm16c'
    AS = 'am16c'
    AR = 'xar'
    LINK = 'xlink'
    TARGET_EXT = 'mot'
    
    DEVICE = '--cpu M16C'
    
    AFLAGS = '-s+'
#    AFLAGS += ' -M<>' 
    AFLAGS += ' -w+' 
    AFLAGS += ' -r' 
    AFLAGS += ' -I"' + EXEC_PATH + '/m16c/INC"'
        
    LFLAGS = '-xms'
    LFLAGS += ' -I"' + EXEC_PATH + '/m16c/LIB"' 
    LFLAGS += ' -rt' 
    LFLAGS += ' -s __program_start' 
    LFLAGS += ' -D_CSTACK_SIZE=80' 
    LFLAGS += ' -D_ISTACK_SIZE=40' 
    LFLAGS += ' -D_DATA16_HEAP_SIZE=1000' 
    LFLAGS += ' -D_FAR_HEAP_SIZE=400'
    LFLAGS += ' -D_DATA20_HEAP_SIZE=400'
    LFLAGS += ' "' + EXEC_PATH + '/m16c/LIB/CLIB/clm16cfnffwc.r34"' 
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
    CFLAGS += ' -I"' + EXEC_PATH + '/m16c/INC"'
    CFLAGS += ' -I"' + EXEC_PATH + '/m16c/INC/CLIB"' 
    CFLAGS += ' -Ol' 
    CFLAGS += ' --no_cse' 
    CFLAGS += ' --no_unroll' 
    CFLAGS += ' --no_inline' 
    CFLAGS += ' --no_code_motion' 
    CFLAGS += ' --no_tbaa'    
	
	EXEC_PATH = EXEC_PATH + '/m16c/bin'
   
    POST_ACTION = ''
