import os

# toolchains options
ARCH='risc-v'
CPU='bumblebee'
CROSS_TOOL='gcc'

# bsp lib config
BSP_LIBRARY_TYPE = None

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')
if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR
if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'C:/Program Files (x86)/GNU Tools RISC-V Embedded/8 2019.08-2/bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
   EXEC_PATH = os.getenv('RTT_EXEC_PATH')

CORE = 'risc-v'
BUILD = 'debug'
MAP_FILE = 'rtthread.map'
LINK_FILE = './board/linker_scripts/link.lds'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'riscv-none-embed-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    CXX = PREFIX + 'g++'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -march=rv32imafdc -mcmodel=medany -msmall-data-limit=8 -mdiv -mabi=ilp32d -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections '

    # C Compilation Parameters
    CFLAGS = DEVICE + ' -std=gnu11 -DUSE_STDPERIPH_DRIVE -save-temps=obj'
    # Assembly Compilation Parameters
    AFLAGS = DEVICE + '-c'+ ' -x assembler-with-cpp'
    # Linking Parameters
    LFLAGS = DEVICE + ' -nostartfiles -Xlinker --gc-sections --specs=nano.specs --specs=nosys.specs ' + ' -T ' + LINK_FILE + ' -Wl,-Map=' + MAP_FILE

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -g3'
        AFLAGS += ' -g3'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS 

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

def dist_handle(BSP_ROOT, dist_dir):
    import sys
    cwd_path = os.getcwd()
    sys.path.append(os.path.join(os.path.dirname(BSP_ROOT), 'tools'))
    from sdk_dist import dist_do_building
    dist_do_building(BSP_ROOT, dist_dir)
