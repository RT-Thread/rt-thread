import os
import sys

# toolchains options
ARCH='arm'
CPU='cortex-m7'
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
    EXEC_PATH   = r'C:\Users\XXYYZZ'
elif CROSS_TOOL == 'keil':
    PLATFORM    = 'armclang'
    EXEC_PATH   = r'C:/Keil_v5'
elif CROSS_TOOL == 'iar':
    PLATFORM    = 'iccarm'
    EXEC_PATH   = r'C:/Program Files/IAR Systems/Embedded Workbench 9.2'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
# BUILD = 'release'

# Read linker script selection from rtconfig.h (set by Kconfig BSP_LINKER_SCRIPT_* choice).
# Supported types: RAM, HYPERRAM, FLEXSPI_NOR, FLEXSPI_NOR_HYPERRAM
# Default to RAM when no match is found.
_LINKER_SCRIPT_TYPE = 'RAM'
_rtconfig_h = os.path.join(os.path.dirname(__file__), 'rtconfig.h')
if os.path.exists(_rtconfig_h):
    with open(_rtconfig_h, 'r') as _f:
        for _line in _f:
            _s = _line.strip()
            if _s.startswith('//'):
                continue
            # Check the most specific name first to avoid false matches.
            if _s.startswith('#define BSP_LINKER_SCRIPT_FLEXSPI_NOR_HYPERRAM'):
                _LINKER_SCRIPT_TYPE = 'FLEXSPI_NOR_HYPERRAM'
                break
            if _s.startswith('#define BSP_LINKER_SCRIPT_FLEXSPI_NOR'):
                _LINKER_SCRIPT_TYPE = 'FLEXSPI_NOR'
                break
            if _s.startswith('#define BSP_LINKER_SCRIPT_HYPERRAM'):
                _LINKER_SCRIPT_TYPE = 'HYPERRAM'
                break
            if _s.startswith('#define BSP_LINKER_SCRIPT_RAM'):
                _LINKER_SCRIPT_TYPE = 'RAM'
                break

# Base filename (without extension) for the selected linker script.
_LINKER_SCRIPT_BASE = {
    'RAM':                  'MIMXRT1189xxxxx_cm7_ram',
    'HYPERRAM':             'MIMXRT1189xxxxx_cm7_hyperram',
    'FLEXSPI_NOR':          'MIMXRT1189xxxxx_cm7_flexspi_nor',
    'FLEXSPI_NOR_HYPERRAM': 'MIMXRT1189xxxxx_cm7_flexspi_nor_hyperram',
}[_LINKER_SCRIPT_TYPE]


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

    DEVICE = ' -mcpu=' + CPU + ' -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections'
    CFLAGS = DEVICE + ' -Wall -D__FPU_PRESENT -eentry'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -Wa,-mimplicit-it=thumb -D__START=entry'

    LINKER_SCRIPT = 'board/linker_scripts/' + _LINKER_SCRIPT_BASE + '.ld'

    LFLAGS = DEVICE + ' -lm -lgcc -lc' + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,Reset_Handler -T ' + LINKER_SCRIPT

    CPATH = ''
    LPATH = ''

    AFLAGS += ' -D__STARTUP_INITIALIZE_NONCACHEDATA'
    AFLAGS += ' -D__STARTUP_CLEAR_BSS'

    if BUILD == 'debug':
        CFLAGS += ' -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
        CFLAGS += ' -O0'
    else:
        CFLAGS += ' -O2 -Os'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

    # module setting
    CXXFLAGS = ' -Woverloaded-virtual -fno-exceptions -fno-rtti '
    M_CFLAGS = CFLAGS + ' -mlong-calls -fPIC '
    M_CXXFLAGS = CXXFLAGS + ' -mlong-calls -fPIC'
    M_LFLAGS = DEVICE + CXXFLAGS + ' -Wl,--gc-sections,-z,max-page-size=0x4' +\
                                    ' -shared -fPIC -nostartfiles -static-libgcc'
    M_POST_ACTION = STRIP + ' -R .hash $TARGET\n' + SIZE + ' $TARGET \n'

elif PLATFORM == 'armcc':
    CC = 'armcc'
    CXX = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --cpu ' + CPU + '.fp.sp'
    CFLAGS = DEVICE + ' --apcs=interwork'
    AFLAGS = DEVICE

    LINKER_SCRIPT = 'board/linker_scripts/' + _LINKER_SCRIPT_BASE + '.scf'

    LFLAGS = DEVICE + ' --libpath "' + EXEC_PATH + '\ARM\ARMCC\lib" --info sizes --info totals --info unused --info veneers --list rtthread.map --scatter "' + LINKER_SCRIPT + '"'

    LFLAGS += ' --keep *.o(.rti_fn.*)   --keep *.o(FSymTab) --keep *.o(VSymTab)'

    CFLAGS += ' --diag_suppress=66,1296,186,6314'
    CFLAGS += ' -I' + EXEC_PATH + '/ARM/RV31/INC'
    LFLAGS += ' --libpath ' + EXEC_PATH + '/ARM/RV31/LIB'

    EXEC_PATH += '/arm/bin40/'

    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS
    CFLAGS += ' --c99'

    POST_ACTION = 'fromelf -z $TARGET'
    # POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin \nfromelf -z $TARGET'

elif PLATFORM == 'armclang':
    # toolchains
    CC = 'armclang'
    CXX = 'armclang'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --cpu ' + CPU
    CFLAGS = ' --target=arm-arm-none-eabi'
    CFLAGS += ' -mcpu=' + CPU
    CFLAGS += ' -mfpu=fpv4-sp-d16'
    CFLAGS += ' -mfloat-abi=hard'
    CFLAGS += ' -c -fno-rtti -funsigned-char -fshort-enums -fshort-wchar '
    CFLAGS += ' -gdwarf-3 -ffunction-sections '
    AFLAGS = DEVICE + ' --apcs=interwork '
    AFLAGS += ' -x assembler-with-cpp'
    AFLAGS += ' -Wa,-mimplicit-it=thumb'

    # armlink --scatter accepts the file without extension; append .scf explicitly.
    LINKER_SCRIPT = 'board/linker_scripts/' + _LINKER_SCRIPT_BASE + '.scf'

    LFLAGS = DEVICE + ' --info sizes --info totals --info unused --info veneers '
    LFLAGS += ' --list rt-thread.map '
    LFLAGS += r' --strict --scatter "' + LINKER_SCRIPT + '" '
    CFLAGS += ' -I' + EXEC_PATH + '/ARM/ARMCLANG/include'
    LFLAGS += ' --libpath=' + EXEC_PATH + '/ARM/ARMCLANG/lib'

    EXEC_PATH += '/ARM/ARMCLANG/bin/'

    if BUILD == 'debug':
        CFLAGS += ' -g -O1' # armclang recommend
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS
    CFLAGS += ' -std=c99'

    POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin \nfromelf -z $TARGET'

elif PLATFORM == 'iccarm':
    CC = 'iccarm'
    CXX = 'iccarm'
    AS = 'iasmarm'
    AR = 'iarchive'
    LINK = 'ilinkarm'
    TARGET_EXT = 'out'

    DEVICE = ' -D__FPU_PRESENT'

    CFLAGS = DEVICE
    CFLAGS += ' --diag_suppress Pa050'
    CFLAGS += ' --no_cse'
    CFLAGS += ' --no_unroll'
    CFLAGS += ' --no_inline'
    CFLAGS += ' --no_code_motion'
    CFLAGS += ' --no_tbaa'
    CFLAGS += ' --no_clustering'
    CFLAGS += ' --no_scheduling'
    CFLAGS += ' --debug'
    CFLAGS += ' --endian=little'
    CFLAGS += ' --cpu=' + CPU
    CFLAGS += ' -e'
    CFLAGS += ' --fpu=None'
    CFLAGS += ' --dlib_config "' + EXEC_PATH + '/arm/INC/c/DLib_Config_Normal.h"'
    CFLAGS += ' -Ol'
    CFLAGS += ' --use_c++_inline'

    AFLAGS = ''
    AFLAGS += ' -s+'
    AFLAGS += ' -w+'
    AFLAGS += ' -r'
    AFLAGS += ' --cpu ' + CPU
    AFLAGS += ' --fpu None'

    if BUILD == 'debug':
        CFLAGS += ' --debug'
        CFLAGS += ' -On'
    else:
        CFLAGS += ' -Oh'

    LINKER_SCRIPT = 'board/linker_scripts/' + _LINKER_SCRIPT_BASE + '.icf'

    LFLAGS = ' --config "' + LINKER_SCRIPT + '"'

    LFLAGS += ' --redirect _Printf=_PrintfTiny'
    LFLAGS += ' --redirect _Scanf=_ScanfSmall'
    LFLAGS += ' --entry __iar_program_start'

    CXXFLAGS = CFLAGS

    EXEC_PATH = EXEC_PATH + '/arm/bin/'
    POST_ACTION = 'ielftool --bin $TARGET rtthread.bin'

# Map from linker script type to the matching Keil target name.
_LINKER_SCRIPT_TO_KEIL_TARGET = {
    'RAM':                  'rtthread_ram',
    'HYPERRAM':             'rtthread_hyperram',
    'FLEXSPI_NOR':          'rtthread_flexspi_nor',
    'FLEXSPI_NOR_HYPERRAM': 'rtthread_flexspi_nor_hyperram',
}

def update_keil_active_target(uvoptx_path='project.uvoptx'):
    """Set <IsCurrentTarget> in project.uvoptx to match the selected linker script."""
    import xml.etree.ElementTree as etree

    active = _LINKER_SCRIPT_TO_KEIL_TARGET.get(_LINKER_SCRIPT_TYPE, 'rtthread_ram')

    if not os.path.exists(uvoptx_path):
        return

    tree = etree.parse(uvoptx_path)
    root = tree.getroot()

    for tgt in tree.findall('Target'):
        tname = tgt.find('TargetName')
        is_current = tgt.find('TargetOption/OPTFL/IsCurrentTarget')
        if tname is not None and is_current is not None:
            is_current.text = '1' if tname.text == active else '0'

    out = open(uvoptx_path, 'w')
    out.write('<?xml version="1.0" encoding="UTF-8" standalone="no" ?>\n')
    out.write(etree.tostring(root, encoding='utf-8').decode())
    out.close()

    print('Keil active target set to: ' + active)

def dist_handle(BSP_ROOT, dist_dir):
    import sys
    cwd_path = os.getcwd()
    # sys.path.append(os.path.join(os.path.dirname(BSP_ROOT), 'tools'))
    sys.path.append(os.path.join(os.path.dirname(os.path.dirname(BSP_ROOT)), 'tools'))
    from sdk_dist import dist_do_building
    dist_do_building(BSP_ROOT, dist_dir)
