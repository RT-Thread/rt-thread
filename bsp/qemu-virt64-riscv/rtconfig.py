import os
import subprocess

def config_enabled(name):
    try:
        with open('rtconfig.h', 'r') as config:
            return '#define {}'.format(name) in config.read()
    except OSError:
        return False


def compiler_accepts(compiler, options):
    try:
        result = subprocess.run(
            [compiler] + options + ['-x', 'c', '-c', '-o', os.devnull, '-'],
            input=b'',
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
            check=False,
        )
    except OSError:
        return False

    return result.returncode == 0

# toolchains options
ARCH        ='risc-v'
CPU         =''
CROSS_TOOL  ='gcc'
RISCV_ABI   = os.getenv('RTT_RISCV_ABI')

RTT_ROOT = os.getenv('RTT_ROOT') or os.path.join(os.getcwd(), '..', '..')

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = os.getenv('RTT_EXEC_PATH') or '/usr/bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX  = os.getenv('RTT_CC_PREFIX') or 'riscv64-unknown-elf-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    CPP     = PREFIX + 'cpp'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'

    xlen = '64' if config_enabled('ARCH_RISCV64') else '32'
    abi_base = 'lp64' if xlen == '64' else 'ilp32'
    extensions = 'imac'

    if config_enabled('ARCH_RISCV_FPU_D'):
        extensions = 'imafdc'
    elif config_enabled('ARCH_RISCV_FPU_S'):
        extensions = 'imafc'

    abi = RISCV_ABI
    if not abi and (xlen == '32' or config_enabled('RT_USING_SMART')):
        abi = abi_base

    march_base = 'rv{}{}'.format(xlen, extensions)
    march_modern = '{}_zicsr_zifencei'.format(march_base)
    compiler = os.path.join(EXEC_PATH, CC)
    if not os.path.isfile(compiler):
        compiler = CC
    abi_option = ['-mabi={}'.format(abi)] if abi else []
    march = march_modern if compiler_accepts(
        compiler, ['-march={}'.format(march_modern)] + abi_option) else march_base
    DEVICE = ' -mcmodel=medany -march={} '.format(march)
    if abi:
        DEVICE += ' -mabi={} '.format(abi)
    CPPFLAGS= ' -nostdinc -undef -E -P -x assembler-with-cpp'
    CFLAGS  = DEVICE + '-ffreestanding -flax-vector-conversions -Wno-cpp -fno-common -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -fdiagnostics-color=always'
    AFLAGS  = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__ '
    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,_start -T link.lds' + ' -lsupc++ -lgcc -static'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -ggdb -fvar-tracking '
        AFLAGS += ' -ggdb'
    else:
        CFLAGS += ' -O2 -Os'

    CXXFLAGS = CFLAGS

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtthread.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
