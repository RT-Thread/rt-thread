import os

# toolchains options
ARCH        ='risc-v'
CPU         ='virt64'
CROSS_TOOL  ='llvm-riscv'

RTT_ROOT = os.getenv('RTT_ROOT') or os.path.join(os.getcwd(), '..', '..')

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'llvm-riscv':
    PLATFORM    = 'llvm-riscv'
    EXEC_PATH   = os.getenv('RTT_EXEC_PATH') or '/usr/bin'
else:
    print('Please make sure your toolchains is LLVM RISC-V!')
    exit(0)

BUILD = 'release'

if PLATFORM == 'llvm-riscv':
    # toolchains
    PREFIX  = os.getenv('RTT_CC_PREFIX') or 'riscv64-unknown-elf-'
    CC      = PREFIX + 'clang'
    CXX     = PREFIX + 'clang++'
    AS      = PREFIX + 'clang'
    AR      = PREFIX + 'llvm-ar'
    LINK    = PREFIX + 'clang++'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'

    DEVICE  = ' -mcmodel=medany -march=rv64imac -mabi=lp64 '
    # Enable emulated TLS
    CFLAGS  = DEVICE + '-fno-omit-frame-pointer -flax-vector-conversions -Wno-cpp -fno-common -ffunction-sections -fdata-sections -fdiagnostics-color=always -Xclang -fexperimental-max-bitint-width=20000 -fbracket-depth=2048 -Wno-parentheses-equality -DGSIM -femulated-tls'
    AFLAGS  = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__ '
    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,_start -T link.lds' + ' -stdlib=libstdc++ -lc -lsupc++ -lgcc -lstdc++ -static'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -ggdb '
        AFLAGS += ' -ggdb'
    else:
        CFLAGS += ' -O3'

    CXXFLAGS = CFLAGS

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtthread.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
