import SCons.cpp

# component options

# make all component false 
RT_USING_DFS 		= False
RT_USING_FINSH 		= False
RT_USING_DFS_ELMFAT= False
RT_USING_DFS_YAFFS2= False
RT_USING_LWIP 		= False
RT_USING_RTGUI 		= False

# parse rtconfig.h to get used component
PreProcessor = SCons.cpp.PreProcessor()
f = file('rtconfig.h', 'r')
contents = f.read()
f.close()
PreProcessor.process_contents(contents)
rtconfig_ns = PreProcessor.cpp_namespace

# finsh shell options
if rtconfig_ns.has_key('RT_USING_FINSH'):
	RT_USING_FINSH = True

# device virtual filesystem options 
if rtconfig_ns.has_key('RT_USING_DFS'):
    RT_USING_DFS = True
    
    if rtconfig_ns.has_key('RT_USING_DFS_EFSL'):
        RT_USING_DFS_EFSL = True
    if rtconfig_ns.has_key('RT_USING_DFS_ELMFAT'):
        RT_USING_DFS_ELMFAT = True
    if rtconfig_ns.has_key('RT_USING_DFS_YAFFS2'):
        RT_USING_DFS_YAFFS2 = True

# lwip options
if rtconfig_ns.has_key('RT_USING_LWIP'):
    RT_USING_LWIP = True
    if rtconfig_ns.has_key('RT_USING_WEBSERVER'):
        RT_USING_WEBSERVER = True

# rtgui options
if rtconfig_ns.has_key('RT_USING_RTGUI'):
    RT_USING_RTGUI = True

# toolchains options
ARCH='arm'
CPU='lm3s'
#PLATFORM = 'gcc'
#EXEC_PATH = 'E:/Program Files/CodeSourcery/Sourcery G++ Lite/bin'
PLATFORM = 'armcc'
EXEC_PATH = 'E:/Keil'
BUILD = 'release'

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
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread-lm3s.map,-cref,-u,Reset_Handler -T lm3s_rom.ld'

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
    LFLAGS = DEVICE + ' --info sizes --info totals --info unused --info veneers --list rtthread-lm3s.map --scatter lm3s_rom.sct'

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
