import os

ARCH = 'arm'
CPU = 'cortex-m23'
CROSS_TOOL = os.getenv('RTT_CC', 'gcc')
BOARD_NAME = 'frdm-mcxc162'
BSP_LIBRARY_TYPE = 'MCXC162'
EXEC_PATH = os.getenv('RTT_EXEC_PATH', '')
BUILD = 'debug'


def _resolve_package_path(package_name, marker):
    bsp_root = os.path.dirname(os.path.abspath(__file__))
    search_roots = ['libraries', os.path.join('..', 'libraries'), 'packages']

    for search_root in search_roots:
        package_path = os.path.join(search_root, package_name)
        if os.path.isfile(os.path.join(bsp_root, package_path, marker)):
            return package_path.replace('\\', '/')

    return os.path.join('packages', package_name).replace('\\', '/')


NXP_MCX_CMSIS_ROOT = _resolve_package_path('nxp-mcx-cmsis-latest', 'Core/Include/core_cm23.h')
NXP_MCX_SERIES_ROOT = _resolve_package_path('nxp-mcx-series-latest', 'MCXC162/gcc/MCXC162_flash.ld')

if CROSS_TOOL == 'gcc':
    PLATFORM = 'gcc'
elif CROSS_TOOL == 'keil':
    PLATFORM = 'armclang'
elif CROSS_TOOL == 'iar':
    PLATFORM = 'iccarm'
else:
    raise RuntimeError('Unsupported toolchain: ' + CROSS_TOOL)

if PLATFORM == 'gcc':
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    STRIP = PREFIX + 'strip'

    DEVICE = ' -mcpu=cortex-m23 -mthumb -mfloat-abi=soft -ffunction-sections -fdata-sections'
    CFLAGS = DEVICE + ' -Wall -std=c99'
    CXXFLAGS = DEVICE + ' -Wall -fno-exceptions -fno-rtti'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS = DEVICE
    LFLAGS += ' -specs=nano.specs -specs=nosys.specs'
    LFLAGS += ' -Wl,--gc-sections,-Map=rtthread.map,--print-memory-usage'
    LFLAGS += ' -T"' + NXP_MCX_SERIES_ROOT + '/MCXC162/gcc/MCXC162_flash.ld"'

    if BUILD == 'debug':
        CFLAGS += ' -Os -gdwarf-2'
        CXXFLAGS += ' -Os -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -Os'
        CXXFLAGS += ' -Os'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET\n'
    CPATH = ''
    LPATH = ''
    M_CFLAGS = CFLAGS + ' -mlong-calls -fPIC'
    M_CXXFLAGS = CXXFLAGS + ' -mlong-calls -fPIC'
    M_LFLAGS = DEVICE + ' -shared -fPIC -nostartfiles -static-libgcc -Wl,--gc-sections,-z,max-page-size=0x4'
    M_POST_ACTION = STRIP + ' -R .hash $TARGET\n' + SIZE + ' $TARGET\n'

elif PLATFORM == 'armclang':
    CC = 'armclang'
    CXX = 'armclang'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --cpu Cortex-M23'
    CFLAGS = ' --target=arm-arm-none-eabi -mcpu=cortex-m23 -mfloat-abi=soft'
    CFLAGS += ' -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -std=c99'
    CXXFLAGS = ' --target=arm-arm-none-eabi -mcpu=cortex-m23 -mfloat-abi=soft'
    CXXFLAGS += ' -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -fno-exceptions -fno-rtti'
    AFLAGS = DEVICE + ' --apcs=interwork'
    LFLAGS = DEVICE + ' --strict --info sizes --info totals --info unused --info veneers'
    LFLAGS += ' --list rtthread.map'
    LFLAGS += ' --scatter "' + NXP_MCX_SERIES_ROOT + '/MCXC162/arm/MCXC162_flash.scf"'

    if BUILD == 'debug':
        CFLAGS += ' -O1 -g -gdwarf-3'
        CXXFLAGS += ' -O1 -g -gdwarf-3'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'
        CXXFLAGS += ' -O2'

    POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin\nfromelf -z $TARGET'

elif PLATFORM == 'iccarm':
    CC = 'iccarm'
    CXX = 'iccarm'
    AS = 'iasmarm'
    AR = 'iarchive'
    LINK = 'ilinkarm'
    TARGET_EXT = 'out'

    dlib_config = os.path.normpath(os.path.join(EXEC_PATH, '..', 'inc', 'c', 'DLib_Config_Normal.h'))
    CFLAGS = ' --cpu=Cortex-M23 --fpu=None --endian=little -e'
    CFLAGS += ' --dlib_config "' + dlib_config + '" --diag_suppress Pa050'
    CXXFLAGS = CFLAGS
    AFLAGS = ' -s+ -r --cpu Cortex-M23 --fpu None'
    LFLAGS = ' --config "' + NXP_MCX_SERIES_ROOT + '/MCXC162/iar/MCXC162_flash.icf"'
    LFLAGS += ' --redirect _Printf=_PrintfTiny --redirect _Scanf=_ScanfSmall'
    LFLAGS += ' --entry __iar_program_start'

    if BUILD == 'debug':
        CFLAGS += ' --debug -On'
        CXXFLAGS += ' --debug -On'
    else:
        CFLAGS += ' -Oh'
        CXXFLAGS += ' -Oh'

    POST_ACTION = 'ielftool --bin $TARGET rtthread.bin'


def dist_handle(BSP_ROOT, dist_dir):
    import sys

    sys.path.append(os.path.join(os.path.dirname(BSP_ROOT), '..', 'tools'))
    from sdk_dist import dist_do_building
    dist_do_building(BSP_ROOT, dist_dir)
