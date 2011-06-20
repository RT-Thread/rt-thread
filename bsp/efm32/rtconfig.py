# toolchains options
ARCH     = 'arm'
CPU      = 'cortex-m3'
CROSS_TOOL 	= 'gcc'

if CROSS_TOOL == 'gcc':
	PLATFORM 	= 'gcc'
	EXEC_PATH 	= 'C:\Program Files (x86)\CodeSourcery\Sourcery G++ Lite\bin'

BUILD = 'debug'
# EFM32_BOARD 	=  'EFM32_G890_STK'
EFM32_BOARD 	=  'EFM32_G290_DK'

if EFM32_BOARD == 'EFM32_G890_STK':
#	EFM32_FAMILY = 'Gecko'
	EFM32_TYPE = 'EFM32G890F128'
elif EFM32_BOARD == 'EFM32_G290_DK':
#	EFM32_FAMILY = 'Gecko'
	EFM32_TYPE = 'EFM32G290F128'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'axf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -mcpu=cortex-m3 -mthumb'
    CFLAGS = DEVICE + ' -DRT_USING_MINILIBC'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread-efm32.map,-cref,-u,Reset_Handler -T efm32_rom.ld'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

