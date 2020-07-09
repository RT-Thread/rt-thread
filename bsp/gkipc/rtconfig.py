import os
import sys
import re

# toolchains options
ARCH         = 'arm'
CPU          = 'armv6'
OUTPUT_NAME  = 'rtthread'
CROSS_TOOL   = 'gcc' # we use gcc compiler always
PLATFORM     = 'gcc'
LD_NAME      = 'link'

EXEC_PATH    = r'C:\gcc-arm-none-eabi-4_9\bin'
if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD  = 'release'

CODEC  = '7102C'
#develop mode select: develop/release
DEVMODE = 'release'
'''
CODEC  = '7102C'
BOARD  = 'GK7102C_EVB'
#sc1135 jxh65 sc1145 ov9750 ar0130 jxh42
SENSOR = 'sc1135'
TUNNING_TOOL_SUPPORT = 'YES' ##'YES'
#develop mode select: develop/release
DEVMODE = 'release'
'''
if CODEC == '7101':
    CODEC_TYPE        = '710X'
    MEMORY_BYTES_DDR0 = '0x08000000'

    MEMORY_PPM_BASE   = '0xC0000000'
    MEMORY_PPM_SIZE   = '0x00200000'
    MEMORY_OS_BASE    = '0xC0200000'
    MEMORY_OS_SIZE    = '0x02300000'
    MEMORY_BSB_BASE   = str(int(MEMORY_OS_BASE,16) + int(MEMORY_OS_SIZE,16))
    MEMORY_BSB_SIZE   = '0x00400000'
    MEMORY_DSP_BASE   = str(int(MEMORY_OS_BASE,16) + int(MEMORY_OS_SIZE,16) + int(MEMORY_BSB_SIZE,16))
    MEMORY_DSP_SIZE   = str(int(MEMORY_BYTES_DDR0,16) - int(MEMORY_BSB_SIZE,16) - int(MEMORY_OS_SIZE,16) - int(MEMORY_PPM_SIZE,16))

if CODEC == '7102':
    CODEC_TYPE        = '710X'
    MEMORY_BYTES_DDR0 = '0x04000000'

    MEMORY_PPM_BASE   = '0xC0000000'
    MEMORY_PPM_SIZE   = '0x00200000'
    MEMORY_OS_BASE    = '0xC0200000'
    MEMORY_OS_SIZE    = '0x02300000'
    MEMORY_BSB_BASE   = str(int(MEMORY_OS_BASE,16) + int(MEMORY_OS_SIZE,16))
    MEMORY_BSB_SIZE   = '0x00200000'
    MEMORY_DSP_BASE   = str(int(MEMORY_OS_BASE,16) + int(MEMORY_OS_SIZE,16) + int(MEMORY_BSB_SIZE,16))
    MEMORY_DSP_SIZE   = str(int(MEMORY_BYTES_DDR0,16) - int(MEMORY_BSB_SIZE,16) - int(MEMORY_OS_SIZE,16) - int(MEMORY_PPM_SIZE,16))
 
if CODEC == '7101S':
    CODEC_TYPE        = '710XS'
    MEMORY_BYTES_DDR0 = '0x08000000'

    MEMORY_PPM_BASE   = '0xC0000000'
    MEMORY_PPM_SIZE   = '0x00200000'
    MEMORY_OS_BASE    = '0xC0200000'
    MEMORY_OS_SIZE    = '0x02300000'
    MEMORY_BSB_BASE   = str(int(MEMORY_OS_BASE,16) + int(MEMORY_OS_SIZE,16))
    MEMORY_BSB_SIZE   = '0x00400000'
    MEMORY_DSP_BASE   = str(int(MEMORY_OS_BASE,16) + int(MEMORY_OS_SIZE,16) + int(MEMORY_BSB_SIZE,16))
    MEMORY_DSP_SIZE   = str(int(MEMORY_BYTES_DDR0,16) - int(MEMORY_BSB_SIZE,16) - int(MEMORY_OS_SIZE,16) - int(MEMORY_PPM_SIZE,16))

if CODEC == '7102S':
    CODEC_TYPE        = '710XS'
    MEMORY_BYTES_DDR0 = '0x04000000'

    MEMORY_PPM_BASE   = '0xC0000000'
    MEMORY_PPM_SIZE   = '0x00200000'
    MEMORY_OS_BASE    = '0xC0200000'
    MEMORY_OS_SIZE    = '0x02300000'
    MEMORY_BSB_BASE   = str(int(MEMORY_OS_BASE,16) + int(MEMORY_OS_SIZE,16))
    MEMORY_BSB_SIZE   = '0x00200000'
    MEMORY_DSP_BASE   = str(int(MEMORY_OS_BASE,16) + int(MEMORY_OS_SIZE,16) + int(MEMORY_BSB_SIZE,16))
    MEMORY_DSP_SIZE   = str(int(MEMORY_BYTES_DDR0,16) - int(MEMORY_BSB_SIZE,16) - int(MEMORY_OS_SIZE,16) - int(MEMORY_PPM_SIZE,16))
 
if CODEC == '7102C':
    CODEC_TYPE        = '7102C'
    CODEC_SUB_TYPE    = '7102C'
    MEMORY_BYTES_DDR0 = '0x04000000'

    MEMORY_PPM_BASE   = '0xC0000000'
    MEMORY_PPM_SIZE   = '0x00200000'
    MEMORY_OS_BASE    = '0xC0200000'
    MEMORY_OS_SIZE    = '0x02200000'
    MEMORY_BSB_BASE   = str(int(MEMORY_OS_BASE,16) + int(MEMORY_OS_SIZE,16))
    MEMORY_BSB_SIZE   = '0x00200000'
    MEMORY_DSP_BASE   = str(int(MEMORY_OS_BASE,16) + int(MEMORY_OS_SIZE,16) + int(MEMORY_BSB_SIZE,16))
    MEMORY_DSP_SIZE   = str(int(MEMORY_BYTES_DDR0,16) - int(MEMORY_BSB_SIZE,16) - int(MEMORY_OS_SIZE,16) - int(MEMORY_PPM_SIZE,16))

PROGRAM_MEMORY_START = '0xC0000000'
PROGRAM_MEMORY_BYTES =  MEMORY_BYTES_DDR0
PROGRAM_STACK_BYTES  = '0x00010000'
PROGRAM_HEAP_BYTES   = '0x00010000'
PROGRAM_LOAD_ADDRESS = '0xC0200000'

MEMORY_BYTES_DDR1    = '0x00000000'
MEMORY_OFFSET_VIDEO  = '0x00000000'

MEMORY_START_BEP = '0x40000000'
MEMORY_BYTES_BEP = '0x00040000'

USE_IPC = '0'
MEMORY_START_IPC = '0x00000000'
MEMORY_BYTES_IPC = '0x00000000'

MEMORY_HEAP2_END = '0xC4000000'
ARM_PROGRAM_HEAP2_BYTES = '0x1c00000'

DDR_MEMORY_START_1  = '0xC0000000'
DDR_MEMORY_BYTES_1  =  MEMORY_BYTES_DDR0


if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC  = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS  = PREFIX + 'gcc'
    AR  = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = '.elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    
    DEVICE = ' -mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=soft'
    CFLAGS = DEVICE + ' -mno-unaligned-access' 

    #for ADI library
    CFLAGS += ' -DFLASH_USING_SEM'
    CFLAGS += ' -DAUDIO_ECHO_CANCELLATION_SUPPORT'
    #for GD library
    #CFLAGS += ' -DSRC_INLINE'
    
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__'
    LFLAGS = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map='+ OUTPUT_NAME +'.map,-cref,-u,_start -T' + LD_NAME +'.ld'

    CPATH = ''
    LPATH = ''
    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2 '
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'


    CFLAGS += ' -mabi=aapcs-linux'
    CFLAGS += ' -D_ARM_GNU'
    CFLAGS += ' -D_ARM'
	
    if CODEC == '7101':
        CFLAGS += ' -DCODEC_710X' 
        CFLAGS += ' -DGK710X'
        CFLAGS += ' -DGK7101' 
    elif CODEC == '7102':
        CFLAGS += ' -DCODEC_710X' 
        CFLAGS += ' -DGK710X'
        CFLAGS += ' -DGK7102' 
    elif CODEC == '7101S':
        CFLAGS += ' -DCODEC_710XS' 
        CFLAGS += ' -DGK7101S' 
        AFLAGS += ' -DCPU_USE_GK710XS=' + '1' 
    elif CODEC == '7102S':
        CFLAGS += ' -DCODEC_710XS' 
        CFLAGS += ' -DGK7102S' 
        AFLAGS += ' -DCPU_USE_GK710XS=' + '1' 
    elif CODEC == '7102C':
        CFLAGS += ' -DCODEC_710XS' 
        CFLAGS += ' -DGK7102C' 
        AFLAGS += ' -DCPU_USE_GK710XS=' + '1'  
		
    AFLAGS += ' -DARM1176_USE_VFP=' + '1'

    CFLAGS += ' -DUSE_RT_DRIVER_FRAMEWORK'

    #CFLAGS += ' -D%s' %BOARD
    #if 	BOARD  == 'GK7102_HZD_JXH42' or BOARD  == 'GK7102S_HZD_JXH42':
    #    CFLAGS += ' -DUSE_BOARD_HZD'
		
    #if TUNNING_TOOL_SUPPORT	== 'YES':
    #    CFLAGS  += ' -DMODULE_SUPPORT_TUNING_TOOL'

    LFLAGS += ' -Wl,--defsym,PROGRAM_MEMORY_START='+ PROGRAM_MEMORY_START 
    LFLAGS += ' -Wl,--defsym,PROGRAM_MEMORY_BYTES='+ PROGRAM_MEMORY_BYTES 
    LFLAGS += ' -Wl,--defsym,PROGRAM_STACK_BYTES=' + PROGRAM_STACK_BYTES 
    LFLAGS += ' -Wl,--defsym,PROGRAM_HEAP_BYTES='  + PROGRAM_HEAP_BYTES 
    LFLAGS += ' -Wl,--defsym,PROGRAM_LOAD_ADDRESS='+ PROGRAM_LOAD_ADDRESS 
    LFLAGS += ' -Wl,--defsym,MEMORY_BYTES_DDR0='   + MEMORY_BYTES_DDR0 
    LFLAGS += ' -Wl,--defsym,MEMORY_BYTES_DDR1='   + MEMORY_BYTES_DDR1 
    LFLAGS += ' -Wl,--defsym,MEMORY_OFFSET_VIDEO=' + MEMORY_OFFSET_VIDEO 
    LFLAGS += ' -Wl,--defsym,MEMORY_START_BEP='    + MEMORY_START_BEP       
    LFLAGS += ' -Wl,--defsym,MEMORY_BYTES_BEP='    + MEMORY_BYTES_BEP      
    LFLAGS += ' -Wl,--defsym,USE_IPC='             + USE_IPC      
    LFLAGS += ' -Wl,--defsym,MEMORY_START_IPC='    + MEMORY_START_IPC       
    LFLAGS += ' -Wl,--defsym,MEMORY_BYTES_IPC='    + MEMORY_BYTES_IPC      
    LFLAGS += ' -Wl,--defsym,MEMORY_HEAP2_END='    + MEMORY_HEAP2_END     
    LFLAGS += ' -Wl,--defsym,ARM_PROGRAM_HEAP2_BYTES='+ ARM_PROGRAM_HEAP2_BYTES 

    LFLAGS += ' -Wl,--no-whole-archive' 
    LFLAGS += ' -Wl,--discard-locals' 
    LFLAGS += ' -Wl,--check-sections' 
    LFLAGS += ' -Wl,--cref' 
    LFLAGS += ' -Wl,--allow-multiple-definition' 
    LFLAGS += ' -static' 
    LFLAGS += ' -Wl,--no-enum-size-warning' 
    LFLAGS += ' -Wl,--start-group'
    LFLAGS += ' -lc -lgcc -lm -lstdc++ -Wl,--end-group'
    
    LD_group = ' -Wl,--start-group'
    LD_grend = ' -lgnu_c -lc -lgcc -lm -lstdc++ -Wl,--end-group'

    AFLAGS  += ' -DDDR_MEMORY_PPM_BASE=' + MEMORY_PPM_BASE
    AFLAGS  += ' -DDDR_MEMORY_PPM_SIZE=' + MEMORY_PPM_SIZE
    AFLAGS  += ' -DDDR_MEMORY_OS_BASE='  + MEMORY_OS_BASE
    AFLAGS  += ' -DDDR_MEMORY_OS_SIZE='  + MEMORY_OS_SIZE
    AFLAGS  += ' -DDDR_MEMORY_DSP_BASE=' + MEMORY_DSP_BASE
    AFLAGS  += ' -DDDR_MEMORY_DSP_SIZE=' + MEMORY_DSP_SIZE
    AFLAGS  += ' -DDDR_MEMORY_BSB_BASE=' + MEMORY_BSB_BASE
    AFLAGS  += ' -DDDR_MEMORY_BSB_SIZE=' + MEMORY_BSB_SIZE
    AFLAGS  += ' -DDDR_MEMORY_DDR_BASE=' + DDR_MEMORY_START_1
    AFLAGS  += ' -DDDR_MEMORY_DDR_SIZE=' + DDR_MEMORY_BYTES_1

    CFLAGS  += ' -DDDR_MEMORY_PPM_BASE=' + MEMORY_PPM_BASE
    CFLAGS  += ' -DDDR_MEMORY_PPM_SIZE=' + MEMORY_PPM_SIZE
    CFLAGS  += ' -DDDR_MEMORY_OS_BASE='  + MEMORY_OS_BASE
    CFLAGS  += ' -DDDR_MEMORY_OS_SIZE='  + MEMORY_OS_SIZE
    CFLAGS  += ' -DDDR_MEMORY_DSP_BASE=' + MEMORY_DSP_BASE
    CFLAGS  += ' -DDDR_MEMORY_DSP_SIZE=' + MEMORY_DSP_SIZE
    CFLAGS  += ' -DDDR_MEMORY_BSB_BASE=' + MEMORY_BSB_BASE
    CFLAGS  += ' -DDDR_MEMORY_BSB_SIZE=' + MEMORY_BSB_SIZE
    CFLAGS  += ' -DDDR_MEMORY_DDR_BASE=' + DDR_MEMORY_START_1
    CFLAGS  += ' -DDDR_MEMORY_DDR_SIZE=' + DDR_MEMORY_BYTES_1
	


    CXXFLAGS = CFLAGS
    POST_ACTION = OBJCPY + ' -O binary $TARGET '+ OUTPUT_NAME +'.bin\n' + SIZE + ' $TARGET \n'