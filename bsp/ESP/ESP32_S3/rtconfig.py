import os
import sys

BSP_ROOT = os.path.dirname(os.path.abspath(__file__))
RTT_ROOT = os.getenv('RTT_ROOT') or os.path.normpath(os.path.join(BSP_ROOT, '..', '..', '..'))
sys.path = sys.path + [os.path.join(RTT_ROOT, 'tools')]
from env_package import find_package_path

# toolchains options
ARCH        ='xtensa'
CPU         ='esp32s3'
CROSS_TOOL  ='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'~/.espressif/tools/xtensa-esp32s3-elf/esp-12.2.0_20230208/xtensa-esp32s3-elf/bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')
EXEC_PATH = os.path.expanduser(EXEC_PATH)

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'xtensa-esp32s3-elf-'
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

    # -mlongcalls is what ESP-IDF uses everywhere: plain jumps cannot reach
    # across the 0x3C000000/0x40370000/0x600xxxxx ranges this SoC maps code
    # and ROM into. --specs=nosys.specs drops libgloss syscalls; the IDF
    # newlib port in the ESP-IDF package provides the real ones.
    DEVICE  = ' -nostartfiles -mlongcalls --specs=nosys.specs -fasynchronous-unwind-tables '
    CFLAGS = DEVICE + '-include ../../components/libc/compilers/common/include/sys/ioctl.h -gdwarf-4 -ggdb -Og '
    AFLAGS =  ' -c' + DEVICE + ' -x assembler-with-cpp'
    idf_path = find_package_path(BSP_ROOT, 'ESP-IDF-latest', relative_to=BSP_ROOT, pathsep='/')
    # memory.ld + sections.ld under idf_port/ld are generated from ESP-IDF
    # 5.1.4's esp32s3 templates (see idf_port/ld/ header comments); the ROM
    # alias scripts and peripheral map come straight from the package.
    LFLAGS = DEVICE + ' -Wl,--cref -Wl,--defsym=IDF_TARGET_ESP32S3=0 -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,call_start_cpu0 -T idf_port/ld/memory.ld -T idf_port/ld/sections.ld -T ' + idf_path + '/components/esp_rom/esp32s3/ld/esp32s3.rom.ld -T ' + idf_path + '/components/esp_rom/esp32s3/ld/esp32s3.rom.api.ld -T ' + idf_path + '/components/esp_rom/esp32s3/ld/esp32s3.rom.libgcc.ld -T ' + idf_path + '/components/esp_rom/esp32s3/ld/esp32s3.rom.newlib.ld -T ' + idf_path + '/components/esp_rom/esp32s3/ld/esp32s3.rom.version.ld -T ' + idf_path + '/components/soc/esp32s3/ld/esp32s3.peripherals.ld -Wl,--wrap=esp_system_abort -Wl,--wrap=esp_flash_init_default_chip '
    CXXFLAGS = CFLAGS

    POST_ACTION = OBJCPY + ' -Oihex $TARGET rtthread.hex\n' + SIZE + ' $TARGET \n'

def dist_handle(BSP_ROOT, dist_dir):
    import sys
    sys.path.append(os.path.join(os.path.dirname(BSP_ROOT), 'tools'))
    from sdk_dist import dist_do_building
    dist_do_building(BSP_ROOT, dist_dir)
