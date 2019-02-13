import os

# toolchains options
ARCH='arc'
CPU='em'
CROSS_TOOL='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

# only support GNU GCC compiler
PLATFORM 	= 'gcc'
EXEC_PATH 	= 'C:/arc/gnu/bin'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arc-elf32-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    DBG = PREFIX + 'gdb'
    DEVICE = ' -mno-sdata -Wall -mcpu=em4_fpus -mlittle-endian -mcode-density -mdiv-rem -mswap -mnorm -mmpy-option=6 -mbarrel-shifter -mfpu=fpus_all'
    CFLAGS = DEVICE
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LINK_SCRIPT = 'emsk_em9d.ld'
    LFLAGS = DEVICE + ' -mno-sdata -nostartfiles -Wl,--gc-sections,-Map=emsk_em9d.map,-cref,-u,system_vectors -T %s' % LINK_SCRIPT

    OPENOCD_SCRIPT_ROOT = 'C:/arc/gnu/share/openocd/scripts'
    OPENOCD_CFG_FILE = OPENOCD_SCRIPT_ROOT + '/board/snps_em_sk_v2.2.cfg'

    OPENOCD_OPTIONS  = '-s %s -f %s' % (OPENOCD_SCRIPT_ROOT, OPENOCD_CFG_FILE)

    DBG_HW_FLAGS = ''' -ex "target remote | openocd --pipe %s" -ex "load" ''' % OPENOCD_OPTIONS


    TARGET = 'rtthread_snps_emsk_em9d.' + TARGET_EXT

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' +\
            SIZE + ' $TARGET \n'
    #POST_ACTION = DBG + DBG_HW_FLAGS + TARGET
