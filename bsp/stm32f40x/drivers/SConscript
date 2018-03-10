from building import *

cwd = GetCurrentDir()

# add the general drivers.
src = Split("""
board.c
stm32f4xx_it.c
usart.c
""")

# add Ethernet drivers.
if GetDepend('RT_USING_LWIP'):
    src += ['stm32f4xx_eth.c']

# add gpio drivers.
if GetDepend('RT_USING_PIN'):
    src += ['gpio.c']

CPPPATH = [cwd]

group = DefineGroup('Drivers', src, depend = [''], CPPPATH = CPPPATH)

Return('group')
