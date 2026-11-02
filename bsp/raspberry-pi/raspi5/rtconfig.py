import os
import subprocess

# toolchains options
ARCH        ='aarch64'
CPU         ='cortex-a'
CROSS_TOOL  ='gcc'

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = r'../../..'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

PLATFORM    = 'gcc'
EXEC_PATH   = r'/opt/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/bin/'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

PREFERRED_MTUNE = 'cortex-a76'
MTUNE_FALLBACKS = ('cortex-a73', 'generic')

def _gcc_supports_mtune(cc, exec_path, march, tune):
    env = os.environ.copy()
    if exec_path:
        env['PATH'] = exec_path + os.pathsep + env.get('PATH', '')

    try:
        ret = subprocess.run(
            [cc, '-march=' + march, '-mtune=' + tune, '-c', '-x', 'c', '-', '-o', os.devnull],
            input=b'',
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
            env=env,
            check=False,
        )
        return ret.returncode == 0
    except (OSError, subprocess.SubprocessError):
        return False

def resolve_mtune(cc, exec_path, preferred=PREFERRED_MTUNE, march='armv8-a',
                    fallbacks=MTUNE_FALLBACKS):
    for tune in (preferred,) + fallbacks:
        if _gcc_supports_mtune(cc, exec_path, march, tune):
            if tune != preferred:
                print('Note: %s does not support -mtune=%s, using -mtune=%s' % (
                    cc, preferred, tune))
            return tune
    return fallbacks[-1]

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX  = os.getenv('RTT_CC_PREFIX') or 'aarch64-none-elf-'
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

    MTUNE = resolve_mtune(CC, EXEC_PATH)
    DEVICE = ' -march=armv8-a -mtune=%s -fdiagnostics-color=always' % MTUNE
    CPPFLAGS = ' -nostdinc -undef -E -P -x assembler-with-cpp'
    CFLAGS = DEVICE + ' -Wall -Wno-cpp -D_POSIX_SOURCE'
    AFLAGS = ' -c' + ' -x assembler-with-cpp -D__ASSEMBLY__'
    LFLAGS  = DEVICE + ' -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,system_vectors -T link.lds'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -ggdb'
        AFLAGS += ' -ggdb'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
