Import('RTT_ROOT')
Import('rtconfig')
from building import *

cwd = GetCurrentDir()

# add the general drivers.
src = Split("""
drv_common.c
""")

if GetDepend(['RT_USING_PIN']):
    src += ['drv_gpio.c']

if GetDepend(['RT_USING_SERIAL']):
    if GetDepend(['RT_USING_SERIAL_V2']):
        src += ['drv_usart_v2.c']
    else:
        src += ['drv_uart.c']

if GetDepend(['RT_USING_I2C', 'RT_USING_I2C_BITOPS']):
    if GetDepend('BSP_USING_I2C1'):
        src += ['drv_soft_i2c.c']

if GetDepend(['RT_USING_I2C']):
    if GetDepend('BSP_USING_HW_I2C3') or GetDepend('BSP_USING_HW_I2C4') or GetDepend('BSP_USING_HW_I2C6'):
        src += ['drv_i2c.c']

if GetDepend(['BSP_USING_SDIO1']):
    src += Glob('drv_sdio.c')

if GetDepend(['BSP_USING_SDCARD']):
    src += Glob('drv_sdcard.c')

if GetDepend(['BSP_USING_PWM']):
    src += ['drv_pwm.c']

if GetDepend(['BSP_USING_SPI']):
    src += ['drv_spi.c']

if GetDepend(['BSP_USING_ADC']):
    src += ['drv_adc.c']

if GetDepend(['BSP_USING_USBD']):
    src += ['drv_usbd.c']

if GetDepend('BSP_USING_RTC'):
    src += ['drv_rtc.c']

if GetDepend('BSP_USING_ON_CHIP_FLASH'):
    src += ['drv_flash.c']

if GetDepend(['RT_USING_WDT']):
    src += ['drv_wdt.c']

if GetDepend(['RT_USING_DAC']):
    src += ['drv_dac.c']

if GetDepend(['BSP_USING_TIM']):
    src += ['drv_hwtimer.c']

path =  [cwd]
path += [cwd + '/config']

group = DefineGroup('Drivers', src, depend = [''], CPPPATH = path)

Return('group')
