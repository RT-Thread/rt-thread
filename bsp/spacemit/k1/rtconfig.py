
import os

# --- Toolchains Core Options ---
ARCH        = 'risc-v'
VENDOR      = 'spacemit'
CPU         = 'x60'
# CPU         = 'rv64'
CROSS_TOOL  = 'gcc'


RTT_ROOT = os.getenv('RTT_ROOT') or os.path.join(os.getcwd(), '..', '..', '..')

# --- Toolchain Path & Prefix ---
if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = os.getenv('RTT_EXEC_PATH') or '/opt/gcc-riscv/spacemit-toolchain-elf-newlib-x86_64-v1.1.2/bin'
else:
    print('Error: Please use GNU GCC toolchain for this project.')
    exit(0)

# --- Build Type ---
# 开发阶段默认为 debug，方便调试。执行 scons --build=release 可切换
BUILD = 'debug'

if PLATFORM == 'gcc':
    PREFIX  = os.getenv('RTT_CC_PREFIX') or 'riscv64-unknown-elf-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'

    # --- Core Config---
    #DEVICE  = ' -mcpu=spacemit-x60 -march=rv64gcv_zba_zbb_zbc_zbs -mabi=lp64d'
    DEVICE  = ' -mcpu=spacemit-x60 -march=rv64gc_zba_zbb_zbc_zbs -mabi=lp64d'

    CFLAGS  = DEVICE + ' -ffreestanding -fno-common -ffunction-sections -fdata-sections -Wall'
    CFLAGS += ' -I. '

    AFLAGS  = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__'

    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,_start -T link.lds'
    LFLAGS += ' -lsupc++ -lgcc -static'

    CPATH   = ''
    LPATH   = ''


    if BUILD == 'debug':
        CFLAGS += ' -O0 -ggdb -fno-omit-frame-pointer'  
        CFLAGS += ' -DDEBUG_ENABLE'  
        AFLAGS += ' -ggdb'
    else:
        CFLAGS += ' -O2' 

    CXXFLAGS = CFLAGS

# --- Post-build Actions ---
DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtthread.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
