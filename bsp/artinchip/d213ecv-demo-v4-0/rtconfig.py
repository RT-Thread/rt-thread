import os
import shutil
import subprocess

ARCH = 'risc-v'
CPU = 'c906'
CROSS_TOOL = 'gcc'
PLATFORM = 'gcc'
EXEC_PATH = os.getenv('RTT_EXEC_PATH') or ''
PREFIX = os.getenv('RTT_CC_PREFIX') or 'riscv64-unknown-elf-'

CC = PREFIX + 'gcc'
CXX = PREFIX + 'g++'
AS = CC
AR = PREFIX + 'ar'
LINK = CC
SIZE = PREFIX + 'size'
OBJCPY = PREFIX + 'objcopy'
OBJDUMP = PREFIX + 'objdump'
TARGET_EXT = 'elf'

# Accept both the CI GCC 10 ISA spelling and newer GNU assemblers.
compiler = os.path.join(EXEC_PATH, CC) if EXEC_PATH else shutil.which(CC)
if compiler and os.name == 'nt' and not compiler.lower().endswith('.exe'):
    compiler += '.exe'
isa = 'rv64imafdc'
if compiler and os.path.isfile(compiler):
    version = subprocess.check_output([compiler, '-dumpversion']).decode()
    if int(version.split('.')[0]) >= 12:
        isa += '_zicsr_zifencei'
if not EXEC_PATH and compiler:
    EXEC_PATH = os.path.dirname(compiler)

DEVICE = ' -march=' + isa + ' -mabi=lp64d -mcmodel=medany'
CFLAGS = DEVICE + ' -O2 -g -Wall -ffunction-sections -fdata-sections -fno-common'
CXXFLAGS = CFLAGS
AFLAGS = DEVICE + ' -c -g -x assembler-with-cpp -D__ASSEMBLY__'
LFLAGS = DEVICE + ' -nostartfiles -Wl,--gc-sections -Wl,-Map=rtthread.map -T link.lds'
CPATH = ''
LPATH = ''
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET\n'


def dist_handle(BSP_ROOT, dist_dir):
    from mkdist import do_copy_folder
    libraries = os.path.join(BSP_ROOT, 'libraries')
    if not os.path.isdir(libraries):
        libraries = os.path.join(BSP_ROOT, '..', 'libraries')
    do_copy_folder(libraries, os.path.join(dist_dir, 'libraries'))
