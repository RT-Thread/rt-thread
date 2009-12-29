# component options

# finsh shell option
RT_USING_FINSH = True

# device file system options
RT_USING_DFS = False
RT_USING_DFS_EFSL = False
RT_USING_DFS_ELMFAT = False
RT_USING_DFS_YAFFS2 = False

# lwip options
RT_USING_LWIP = False

# rtgui options
RT_USING_RTGUI = False

# toolchains options
ARCH='arm'
CPU='lpc24xx'
TextBase='0x30000000'

#PLATFORM = 'gcc'
#EXEC_PATH = 'd:/SourceryGCC/bin'
PLATFORM = 'armcc'
EXEC_PATH = 'd:/Keil'
BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -mcpu=arm920t'
    CFLAGS = DEVICE + ' -DRT_USING_MINILIBC'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=main.elf.map,-cref,-u,Reset_Handler -T mini2440_rom.ld'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    RT_USING_MINILIBC = True
    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

elif PLATFORM == 'armcc':
    # toolchains
    CC = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --device DARMP'
    CFLAGS = DEVICE + ' --apcs=interwork'
    AFLAGS = DEVICE
    LFLAGS = DEVICE + ' --info sizes --info totals --info unused --info veneers --list rtt-lpc2478.map --strict --scatter ".\objs\lpc2478.sct"t'

    CFLAGS += ' -I"' + EXEC_PATH + '/ARM/RV31/INC"'
    CFLAGS += ' -I"' + EXEC_PATH + '/ARM/INC/Philips"'
    LFLAGS += ' --libpath "' + EXEC_PATH + '/ARM/RV31/LIB"'

    EXEC_PATH += '/arm/bin40/'

    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'

    RT_USING_MINILIBC = False
    if RT_USING_FINSH:
        LFLAGS += ' --keep __fsym_* --keep __vsym_*'
    POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin \nfromelf -z $TARGET'

elif PLATFORM == 'iar':
    # toolchains
    CC = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'

    CFLAGS = ''
    AFLAGS = ''
    LFLAGS = ''
