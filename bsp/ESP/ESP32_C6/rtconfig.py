import os
import sys

BSP_ROOT = os.path.dirname(os.path.abspath(__file__))
RTT_ROOT = os.getenv('RTT_ROOT') or os.path.normpath(os.path.join(BSP_ROOT, '..', '..', '..'))
sys.path = sys.path + [os.path.join(RTT_ROOT, 'tools')]
from env_package import find_package_path

# toolchains options
ARCH        ='risc-v'
CPU         =''
CROSS_TOOL  ='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'~/.espressif/tools/riscv32-esp-elf/esp-2022r1-11.2.0/riscv32-esp-elf/bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')
EXEC_PATH = os.path.expanduser(EXEC_PATH)

BUILD = 'debug'

if PLATFORM == 'gcc':
    PREFIX = 'riscv32-esp-elf-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'g++'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    STRIP = PREFIX + 'strip'

    DEVICE = ' -nostartfiles -march=rv32imac --specs=nosys.specs -fasynchronous-unwind-tables '
    CFLAGS = DEVICE + '-include ../../components/libc/compilers/common/include/sys/ioctl.h -gdwarf-4 -ggdb -Og '
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    idf_path = find_package_path(BSP_ROOT, 'ESP-IDF-latest', relative_to=BSP_ROOT, pathsep='/')
    rom = idf_path + '/components/esp_rom/esp32c6/ld/'
    soc_ld = idf_path + '/components/soc/esp32c6/ld/'
    rom_scripts = [
        'esp32c6.rom.ld',
        'esp32c6.rom.api.ld',
        'esp32c6.rom.libgcc.ld',
        'esp32c6.rom.newlib.ld',
        'esp32c6.rom.version.ld',
        'esp32c6.rom.heap.ld',
        'esp32c6.rom.spiflash.ld',
        'esp32c6.rom.wdt.ld',
    ]
    link_scripts = [' -T idf_port/ld/memory.ld -T idf_port/ld/sections.ld']
    link_scripts += [' -T ' + rom + name for name in rom_scripts]
    link_scripts.append(' -T ' + soc_ld + 'esp32c6.peripherals.ld')
    LFLAGS = DEVICE + ' -Wl,--cref -Wl,--defsym=IDF_TARGET_ESP32C6=0 -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,_start ' + ''.join(link_scripts) + ' -Wl,--wrap=_Unwind_SetEnableExceptionFdeSorting -Wl,--wrap=__register_frame_info_bases -Wl,--wrap=__register_frame_info -Wl,--wrap=__register_frame -Wl,--wrap=__register_frame_info_table_bases -Wl,--wrap=__register_frame_info_table -Wl,--wrap=__register_frame_table -Wl,--wrap=__deregister_frame_info_bases -Wl,--wrap=__deregister_frame_info -Wl,--wrap=_Unwind_Find_FDE -Wl,--wrap=_Unwind_GetGR -Wl,--wrap=_Unwind_GetCFA -Wl,--wrap=_Unwind_GetIP -Wl,--wrap=_Unwind_GetIPInfo -Wl,--wrap=_Unwind_GetRegionStart -Wl,--wrap=_Unwind_GetDataRelBase -Wl,--wrap=_Unwind_GetTextRelBase -Wl,--wrap=_Unwind_SetIP -Wl,--wrap=_Unwind_SetGR -Wl,--wrap=_Unwind_GetLanguageSpecificData -Wl,--wrap=_Unwind_FindEnclosingFunction -Wl,--wrap=_Unwind_Resume -Wl,--wrap=_Unwind_RaiseException -Wl,--wrap=_Unwind_DeleteException -Wl,--wrap=_Unwind_ForcedUnwind -Wl,--wrap=_Unwind_Resume_or_Rethrow -Wl,--wrap=_Unwind_Backtrace -Wl,--wrap=__cxa_call_unexpected -Wl,--eh-frame-hdr -Wl,--wrap=__gxx_personality_v0  -Wl,--cref -Wl,--defsym=IDF_TARGET_ESP32C6=0'
    CXXFLAGS = CFLAGS

    POST_ACTION = OBJCPY + ' -Oihex $TARGET rtthread.hex\n' + SIZE + ' $TARGET \n'

def dist_handle(BSP_ROOT, dist_dir):
    import sys
    sys.path.append(os.path.join(os.path.dirname(BSP_ROOT), 'tools'))
    from sdk_dist import dist_do_building
    dist_do_building(BSP_ROOT, dist_dir)
