import os

# toolchains options
ARCH        = 'arm'
CPU         = 'cortex-m3'
CROSS_TOOL  = 'gcc'

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')

if CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'C:\Program Files (x86)\CodeSourcery\Sourcery G++ Lite\bin'
    #EXEC_PATH  = 'C:\Program Files (x86)\yagarto\bin'
elif CROSS_TOOL == 'keil':
    print('================ERROR============================')
    print('Not support keil yet!')
    print('=================================================')
    exit(0)
elif CROSS_TOOL == 'iar':
    print('================ERROR============================')
    print('Not support iar yet!')
    print('=================================================')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
	EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'
# EFM32_BOARD		=  'EFM32_G8XX_STK'
# EFM32_BOARD		=  'EFM32_GXXX_DK'
EFM32_BOARD		=  'EFM32GG_DK3750'

if EFM32_BOARD == 'EFM32_G8XX_STK':
    EFM32_FAMILY = 'Gecko'
    EFM32_TYPE = 'EFM32G890F128'
    EFM32_LCD =  'none'
elif EFM32_BOARD == 'EFM32_GXXX_DK':
    EFM32_FAMILY = 'Gecko'
    EFM32_TYPE = 'EFM32G290F128'
    EFM32_LCD =  'none'
elif EFM32_BOARD == 'EFM32GG_DK3750':
    EFM32_FAMILY = 'Giant Gecko'
    EFM32_TYPE = 'EFM32GG990F1024'
#    EFM32_LCD =  'LCD_MAPPED'
    EFM32_LCD =  'LCD_DIRECT'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections'
    CFLAGS = DEVICE
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread-efm32.map,-cref,-u,__cs3_reset -nostartfiles -T'
    if EFM32_BOARD == 'EFM32_G8XX_STK' or EFM32_BOARD == 'EFM32_GXXX_DK':
        LFLAGS += ' efm32g_rom.ld'
    elif EFM32_BOARD == 'EFM32GG_DK3750':
        LFLAGS += ' efm32gg_rom.ld'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

