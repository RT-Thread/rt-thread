import os

# toolchains options
ARCH='arc'
CPU='em'
CROSS_TOOL='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if CROSS_TOOL == 'gcc':
    PLATFORM 	= 'gcc'
    EXEC_PATH 	= 'C:/arc_gnu/bin'
elif CROSS_TOOL =='mw':
    PLATFORM 	= 'mw'
    EXEC_PATH 	= 'C:/ARC/MetaWare/arc/bin'

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

    TARGET = 'rtthread_snps_embarc.elf'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread_snps_embarc.bin\n' +\
            SIZE + ' $TARGET \n'

elif PLATFORM == 'mw':
    # toolchains
    CC = 'ccac'
    CXX = 'ccac'
    AS = 'ccac'
    AR = 'arac'
    LINK = 'ccac'
    TARGET_EXT = 'elf'
    SIZE = 'sizeac'
    OBJDUMP = 'elfdumpac'
    OBJCPY = 'elf2bin'
    DBG = 'mdb'

    TARGET = 'rtthread_snps_embarc.elf'

    POST_ACTION = OBJCPY + ' $TARGET rtthread_snps_embarc.bin\n' +\
            SIZE + ' $TARGET \n'
