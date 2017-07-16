import os
ARCH     = 'risc-v'
CPU      = 'e310'
# toolchains options
CROSS_TOOL  = 'gcc'

#------- toolchains path -------------------------------------------------------
if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
   # EXEC_PATH  = 'D:/ArdaArmTools/Sourcery_Lite/bin'
    EXEC_PATH   = '/home/zj/risc-v/riscv64-unknown-elf-gcc-20170612-x86_64-linux-centos6/bin'
elif CROSS_TOOL == 'keil':
    PLATFORM    = 'armcc'
    EXEC_PATH   = 'C:/Keil_v5'
elif CROSS_TOOL == 'iar':
    PLATFORM    = 'iar'
    IAR_PATH    = 'C:/Program Files (x86)/IAR Systems/Embedded Workbench 7.0'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
#BUILD = 'release'

CORE = 'risc-v'
MAP_FILE = 'rtthread.map'
LINK_FILE = 'sdram'
TARGET_NAME = 'rtthread.bin'

#------- GCC settings ----------------------------------------------------------
if PLATFORM == 'gcc':
    # toolchains
    PREFIX = '/home/zj/risc-v/riscv64-unknown-elf-gcc-20170612-x86_64-linux-centos6/bin/riscv64-unknown-elf-'
    #PREFIX = 'arm-none-linux-gnueabi-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'axf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8  -g -L.  -nostartfiles  -lc '
#    DEVICE += '-Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=open -Wl,--wrap=lseek -Wl,--wrap=read -Wl,--wrap=write -Wl,--wrap=fstat -Wl,--wrap=stat -Wl,--wrap=close -Wl,--wrap=link -Wl,--wrap=unlink -Wl,--wrap=execve -Wl,--wrap=fork -Wl,--wrap=getpid -Wl,--wrap=kill -Wl,--wrap=wait -Wl,--wrap=isatty -Wl,--wrap=times -Wl,--wrap=sbrk -Wl,--wrap=_exit'
    CFLAGS = DEVICE
#    CFLAGS += ' -I ./mx28_registers/'
    CFLAGS += ''
    AFLAGS = '-c'+ DEVICE + ' -x assembler-with-cpp'
    AFLAGS += ' -Iplatform'
    LFLAGS = DEVICE 
    LFLAGS += ' -Wl,--gc-sections,-cref,-Map=' + MAP_FILE
    LFLAGS += ' -T ' + LINK_FILE + '.ld'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET ' + TARGET_NAME + '\n' 
    POST_ACTION += SIZE + ' $TARGET\n'
#------- Keil settings ---------------------------------------------------------
elif PLATFORM == 'armcc':
    # toolchains
    CC = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'
    EXEC_PATH += '/arm/armcc/bin/'

    DEVICE = ' --cpu=' + CORE
    CFLAGS = DEVICE + ' --apcs=interwork --diag_suppress=870'
    AFLAGS = DEVICE + ' -Iplatform'
    LFLAGS = DEVICE + ' --strict'
    LFLAGS += ' --info sizes --info totals --info unused --info veneers'
    LFLAGS += ' --list ' + MAP_FILE
    LFLAGS += ' --scatter  ' + LINK_FILE + '.scat'

    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = 'fromelf --bin $TARGET --output ' + TARGET_NAME + ' \n'
    POST_ACTION += 'fromelf -z $TARGET\n'
#------- IAR settings ----------------------------------------------------------
elif PLATFORM == 'iar':
    # toolchains
    CC = 'iccarm'
    AS = 'iasmarm'
    AR = 'iarchive'
    LINK = 'ilinkarm'
    TARGET_EXT = 'axf'

    DEVICE = CORE

    CFLAGS = '--cpu=' + DEVICE
    CFLAGS += ' --diag_suppress Pa050'
    CFLAGS += ' --no_cse'
    CFLAGS += ' --no_unroll'
    CFLAGS += ' --no_inline'
    CFLAGS += ' --no_code_motion'
    CFLAGS += ' --no_tbaa'
    CFLAGS += ' --no_clustering'
    CFLAGS += ' --no_scheduling'

    CFLAGS += ' --endian=little'
    CFLAGS += ' -e'
    CFLAGS += ' --fpu=none'
    CFLAGS += ' --dlib_config "' + IAR_PATH + '/arm/INC/c/DLib_Config_Normal.h"'
    CFLAGS += ' --silent'

    AFLAGS = '--cpu '+ DEVICE
    AFLAGS += ' -s+'
    AFLAGS += ' -w+'
    AFLAGS += ' -r'
    AFLAGS += ' --fpu none'
    AFLAGS += ' -S'
    AFLAGS += ' -Iplatform'
    
    if BUILD == 'debug':
        CFLAGS += ' --debug'
        CFLAGS += ' -On'
    else:
        CFLAGS += ' -Oh'

    LFLAGS = '--config ' + LINK_FILE +'.icf'
    LFLAGS += ' --entry __iar_program_start'
    LFLAGS += ' --map ' + MAP_FILE
    LFLAGS += ' --silent'

    EXEC_PATH = IAR_PATH + '/arm/bin/'
    POST_ACTION = 'ielftool  --silent --bin $TARGET ' + TARGET_NAME
