import os

ARCH       = 'rh850'
CPU        = 'g4kh'
CROSS_TOOL = 'gcc'

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = os.path.join(os.getcwd(), '..', '..', '..', '..')

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if CROSS_TOOL == 'gcc':
    PLATFORM  = 'gcc'
    EXEC_PATH = '/opt/v850-elf/bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

def config_enabled(name):
    try:
        with open('rtconfig.h', 'r') as config:
            return '#define {}'.format(name) in config.read()
    except OSError:
        return False

if PLATFORM == 'gcc':
    PREFIX  = os.getenv('RTT_CC_PREFIX') or 'v850-elf-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'

    DEVICE = ' -mv850e3v5 -mrh850-abi'
    if not config_enabled('RT_USING_FPU'):
        DEVICE += ' -msoft-float'
    DEVICE += ' -ffunction-sections -fdata-sections'
    DEVICE += ' -Wa,-mwarn-signed-overflow -Wa,-mwarn-unsigned-overflow'

    CFLAGS  = DEVICE + ' -Wall'
    AFLAGS  = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref -T board/linker_scripts/link.lds'

    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -g'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

def dist_handle(BSP_ROOT, dist_dir):
    import sys
    sys.path.append(os.path.join(os.path.dirname(BSP_ROOT), 'tools'))
    from sdk_dist import dist_do_building
    dist_do_building(BSP_ROOT, dist_dir)
