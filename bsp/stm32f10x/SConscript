import rtconfig
Import('RTT_ROOT')
from building import *

src_bsp = ['application.c', 'startup.c', 'board.c', 'stm32f10x_it.c']
src_drv = ['rtc.c', 'usart.c', 'serial.c', 'led.c']

if GetDepend('RT_USING_DFS'):
	if rtconfig.STM32_TYPE == 'STM32F10X_HD':
		src_drv += ['sdcard.c']
	else:
		src_drv += ['msd.c']

if GetDepend('RT_USING_LWIP'):
	src_drv += ['enc28j60.c'] + ['dm9000a.c']

if GetDepend('RT_USING_RTGUI'):
    src_drv += ['touch.c', 'calibration.c']

if GetDepend('RT_USING_RTGUI'):
	if rtconfig.RT_USING_LCD_TYPE == 'FMT0371':
		src_drv += ['lcd_a70.c']
	elif rtconfig.RT_USING_LCD_TYPE == 'ILI932X':
		src_drv += ['ili_lcd_general.c']
	elif rtconfig.RT_USING_LCD_TYPE == 'SSD1289':
		src_drv += ['ssd1289.c']

src = src_bsp + src_drv
CPPPATH = [ GetCurrentDir() ]
CPPDEFINES = []
group = DefineGroup('Startup', src, depend = [''], CPPPATH = CPPPATH, CPPDEFINES = CPPDEFINES)

Return('group')
