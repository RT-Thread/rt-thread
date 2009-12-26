# component options
# finsh shell option
RT_USING_FINSH = True

# device file system options
RT_USING_DFS = True
RT_USING_DFS_EFSL = True
RT_USING_DFS_ELMFAT = False
RT_USING_DFS_YAFFS2 = False

# lwip options
RT_USING_LWIP = True

# rtgui options
RT_USING_RTGUI = False

# toolchains options
ARCH='arm'
CPU='lm3s'
#PLATFORM = 'gcc'
#EXEC_PATH = 'E:/Program Files/CodeSourcery/Sourcery G++ Lite/bin'
PLATFORM = 'armcc'
EXEC_PATH = 'E:/Keil'
#PLATFORM = 'iar'
#EXEC_PATH = 'E:/Program Files/IAR Systems/Embedded Workbench 5.4/'
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

    DEVICE = ' -mcpu=cortex-m3 -mthumb'
    CFLAGS = DEVICE + ' -Dsourcerygxx' + ' -DRT_USING_MINILIBC' 
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread-lm3s.map,-cref,-u,ResetISR -T lm3s_rom.ld'

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

    DEVICE = ' --device DARMSTM'
    CFLAGS = DEVICE + ' --apcs=interwork'
    AFLAGS = DEVICE
    LFLAGS = DEVICE + ' --info sizes --info totals --info unused --info veneers --list rtthread-stm32.map --scatter stm32_rom.sct'

    CFLAGS += ' -I' + EXEC_PATH + '/ARM/RV31/INC'
    LFLAGS += ' --libpath ' + EXEC_PATH + '/ARM/RV31/LIB'

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
    CC = 'iccarm'
    AS = 'iasmarm'
    AR = 'iarchive'
    LINK = 'ilinkarm'
    TARGET_EXT = 'out'

    DEVICE = ' --cpu DARMSTM --thumb'

    CFLAGS = ''
    AFLAGS = ''
    LFLAGS = ' --config stm32f10x_flash.icf'

    EXEC_PATH += '/arm/bin/'
    RT_USING_MINILIBC = False
    POST_ACTION = ''
