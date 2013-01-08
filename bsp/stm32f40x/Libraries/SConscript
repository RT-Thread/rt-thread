import rtconfig
Import('RTT_ROOT')
from building import *

# get current directory
cwd = GetCurrentDir()

# The set of source files associated with this SConscript file.
src = Split("""
CMSIS/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
""")

src += Glob('STM32F4xx_StdPeriph_Driver/src/*.c')

# starupt scripts for each STM32 kind
# startup_scripts = {}
# startup_scripts['STM32F10X_CL']     = 'startup_stm32f10x_cl.s'
# startup_scripts['STM32F10X_HD']     = 'startup_stm32f10x_hd.s'
# startup_scripts['STM32F10X_HD_VL']  = 'startup_stm32f10x_hd_vl.s'
# startup_scripts['STM32F10X_LD']     = 'startup_stm32f10x_ld.s'
# startup_scripts['STM32F10X_LD_VL']  = 'startup_stm32f10x_ld_vl.s'
# startup_scripts['STM32F10X_MD']     = 'startup_stm32f10x_md.s'
# startup_scripts['STM32F10X_MD_VL']  = 'startup_stm32f10x_md_vl.s'
# startup_scripts['STM32F10X_XL']	    = 'startup_stm32f10x_xl.s'

#add for startup script 
if rtconfig.CROSS_TOOL == 'gcc':
     src = src + ['CMSIS/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f4xx.s']
elif rtconfig.CROSS_TOOL == 'keil':
     src = src + ['CMSIS/ST/STM32F4xx/Source/Templates/arm/startup_stm32f4xx.s']
# elif rtconfig.CROSS_TOOL == 'iar':
    # src = src + ['CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/iar/' + startup_scripts[rtconfig.STM32_TYPE]]

path = [cwd + '/STM32F4xx_StdPeriph_Driver/inc', 
    cwd + '/CMSIS/ST/STM32F4xx/Include',
    cwd + '/CMSIS/Include',
    cwd + '/CMSIS/CM3/DeviceSupport/ST/STM32F10x']

#CPPDEFINES = ['USE_STDPERIPH_DRIVER', rtconfig.STM32_TYPE]
CPPDEFINES = ['USE_STDPERIPH_DRIVER']
group = DefineGroup('STM32_StdPeriph', src, depend = [''], CPPPATH = path, CPPDEFINES = CPPDEFINES)

Return('group')
