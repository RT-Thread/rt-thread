import os
ARCH     = 'risc-v'
CPU      = 'e901'
# toolchains options
CROSS_TOOL  = 'gcc'

#------- toolchains path -------------------------------------------------------
if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'D:\C-Sky\CDKRepo\Toolchain\XTGccElfNewlib\V3.2.0\R\bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)
    
if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
#BUILD = 'release'

CORE = 'risc-v'
MAP_FILE = 'rtthread.map'
LINK_FILE = '../../libraries/xuantie_libraries/chip_riscv_dummy/gcc_flash_smartl_lite.ld'
if os.path.exists('./libraries'):
    LINK_FILE = './libraries/xuantie_libraries/chip_riscv_dummy/gcc_flash_smartl_lite.ld'
TARGET_NAME = 'rtthread.bin'

#------- GCC settings ----------------------------------------------------------
if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'riscv64-unknown-elf-'
    CC = PREFIX + 'gcc'
    CXX= PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    
    MCPU = ' -mcpu=e901plusbm-cp ' # Modify here based on CPU architecture.
    MCPU_DEFINE = ' -DCONFIG_CPU_XUANTIE_E901PLUS_BM_CP=1 ' # Modify here based on CPU architecture.
    DEVICE = MCPU + MCPU_DEFINE + ' -Wno-main -mcmodel=medany'

    GLOBAL_DEFINES = ( 
                      '-DCONFIG_KERNEL_RTTHREAD=1 ' 
                      '-D__RT_KERNEL_SOURCE__=1 ' 
                      '-DCONFIG_CSI_V2=1 ' 
                      '-DCONFIG_CSI=csi2 ' 
                      '-DCONFIG_INIT_TASK_STACK_SIZE=4096 ' 
                      '-DCONFIG_APP_TASK_STACK_SIZE=8192 ' 
                      '-DCONFIG_ARCH_MAINSTACK=4096 ' 
                      '-DCONFIG_ARCH_INTERRUPTSTACK=4096 ' 
                      '-DCONFIG_XIP=1 ' 
                      '-DCONFIG_LIBC_MINI_PRINTF_SUPPORT=1 ' 
                      '-DCONFIG_SYSTICK_HZ=100 ' 
                      '-DCONFIG_BOARD_SMARTL_EVB=1 ' 
                      '-DCONFIG_DEBUG=1 ' 
                      '-DCLI_CONFIG_STACK_SIZE=4096 '
                      )

    CFLAGS = DEVICE + ' -g -Wall -Wno-unused-function -Wformat -Wformat-security -Warray-bounds -Wuninitialized \
                        -Wreturn-type -Wcomment -Wswitch -Wparentheses -specs=minilibc.specs -MP -MMD -Os -Wpointer-arith \
                        -Wno-undef -ffunction-sections -fdata-sections -fno-inline-functions -fno-builtin \
                        -fno-strict-aliasing -Wno-char-subscripts -Wno-unused-but-set-variable ' + GLOBAL_DEFINES
    
    AFLAGS = DEVICE + ' -g -Wall -Wno-unused-function -Wformat -Wformat-security -Warray-bounds -Wuninitialized \
                        -Wreturn-type -Wcomment -Wswitch -Wparentheses -specs=minilibc.specs -MP -MMD -Os -Wpointer-arith \
                        -Wno-undef -ffunction-sections -fdata-sections -fno-inline-functions -fno-builtin \
                        -fno-strict-aliasing -Wno-char-subscripts -Wno-unused-but-set-variable ' + ' -MP -MMD -D"Default_IRQHandler=SW_handler" ' + GLOBAL_DEFINES
    
    LFLAGS = DEVICE +  ' -MP -MMD  -Wl,-zmax-page-size=1024 -Wl,-Map=yoc.map -Wl,-zmax-page-size=1024 -Wl,-Map=yoc.map -Wl,--whole-archive -Wl,--no-whole-archive -specs=minilibc.specs -nostartfiles -Wl,--gc-sections '
    LFLAGS += ' -T ' + LINK_FILE
     
    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -Os -g3'
        AFLAGS += ' -g3'
    else:
        CFLAGS += ' -O2 -g2'

    CXXFLAGS = CFLAGS

    POST_ACTION = OBJCPY + ' -O binary $TARGET ' + TARGET_NAME + '\n'
    POST_ACTION += SIZE + ' $TARGET\n'

def dist_handle(BSP_ROOT, dist_dir):
    import sys
    cwd_path = os.getcwd()
    sys.path.append(os.path.join(os.path.dirname(BSP_ROOT), '../tools'))
    from sdk_dist import dist_do_building
    dist_do_building(BSP_ROOT, dist_dir)
