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


#add for startup script 
if rtconfig.CROSS_TOOL == 'gcc':
     src = src + ['CMSIS/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f4xx.s']
elif rtconfig.CROSS_TOOL == 'keil':
     src = src + ['CMSIS/ST/STM32F4xx/Source/Templates/arm/startup_stm32f4xx.s']
elif rtconfig.CROSS_TOOL == 'iar':
    src = src + ['CMSIS/ST/STM32F4xx/Source/Templates/iar/startup_stm32f4xx.s']

path = [cwd + '/STM32F4xx_StdPeriph_Driver/inc', 
    cwd + '/CMSIS/ST/STM32F4xx/Include',
    cwd + '/CMSIS/Include']

#CPPDEFINES = ['USE_STDPERIPH_DRIVER', rtconfig.STM32_TYPE]
CPPDEFINES = ['USE_STDPERIPH_DRIVER']
group = DefineGroup('STM32_StdPeriph', src, depend = [''], CPPPATH = path, CPPDEFINES = CPPDEFINES)

Return('group')
