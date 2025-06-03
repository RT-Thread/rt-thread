import os
ARCH     = 'risc-v'
CPU      = 'r910'
# toolchains options
CROSS_TOOL  = 'gcc'

#------- toolchains path -------------------------------------------------------
if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'D:\RT-ThreadStudio\repo\Extract\ToolChain_Support_Packages\RISC-V\XTGccElfNewlib\V3.0.1\R\bin'
else:
    print('Please make sure your toolchains is GNU GCC!')
    exit(0)
    
if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
#BUILD = 'release'

CORE = 'risc-v'
MAP_FILE = 'rtthread.map'
LINK_FILE = '../../libraries/xuantie_libraries/chip_riscv_dummy/gcc_flash_xiaohui.ld'
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
    
    MCPU = ' -mcpu=r910 ' # Modify here based on CPU architecture.
    MCPU_DEFINE = ' -DCONFIG_CPU_XUANTIE_R910=1 ' # Modify here based on CPU architecture.
    DEVICE = MCPU + MCPU_DEFINE + ' -Wno-main -mcmodel=medany -MP -MMD '

    GLOBAL_DEFINES = (
        ' -DCONFIG_KERNEL_RTTHREAD=1 '
        ' -D__RT_KERNEL_SOURCE__=1 '
        ' -DCONFIG_CSI_V2=1 '
        ' -DCONFIG_CSI="csi2" '
        ' -DCONFIG_SUPPORT_TSPEND=0 '
        ' -DCONFIG_SUPPORT_IRQ_NESTED=0 '
        ' -DCONFIG_XIP=1 '
        ' -DCONFIG_ARCH_MAINSTACK=8192 '
        ' -DCONFIG_ARCH_INTERRUPTSTACK=8192 '
        ' -DCONFIG_BOARD_XIAOHUI_EVB=1 '
        ' -DCLI_CONFIG_STACK_SIZE=8192 '
        ' -DCONFIG_PLIC_BASE=134217728 '
        ' -DCONFIG_VIC_TSPDR=201326592 '
        ' -DCONFIG_CLIC_BASE=201392128 '
        ' -DCONFIG_FPP_ENABLE=0 '
        ' -DCONFIG_INTC_CLIC_PLIC=1 '
        ' -DCONFIG_INIT_TASK_STACK_SIZE=8192 '
        ' -DCONFIG_APP_TASK_STACK_SIZE=8192 '
        ' -DCONFIG_SYSTICK_HZ=100 '
        ' -DCONFIG_DEBUG=1 '
    )

    CFLAGS = DEVICE + ' -c -Wno-unused-function -g -Wpointer-arith -Wno-undef -Wall -ffunction-sections -fdata-sections -fno-inline-functions \
                        -fno-builtin -fno-strict-aliasing -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast' + GLOBAL_DEFINES
    
    AFLAGS = DEVICE + ' -D"Default_IRQHandler=SW_handler" ' + GLOBAL_DEFINES
    
    LFLAGS = DEVICE + ' -Wl,-zmax-page-size=1024 -Wl,-Map=yoc.map -nostartfiles -Wl,--gc-sections '
    LFLAGS += ' -T ' + LINK_FILE
    
    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -g3'
        AFLAGS += ' -g3'
    else:
        CFLAGS += ' -O2 -g2'

    CXXFLAGS = CFLAGS

    POST_ACTION = OBJCPY + ' -O binary $TARGET ' + TARGET_NAME + '\n'
    POST_ACTION += SIZE + ' $TARGET\n'

def dist_handle(BSP_ROOT, dist_dir):
    import sys
    cwd_path = os.getcwd()
    sys.path.append(os.path.join(os.path.dirname(BSP_ROOT), 'tools'))
    from sdk_dist import dist_do_building
    dist_do_building(BSP_ROOT, dist_dir)
