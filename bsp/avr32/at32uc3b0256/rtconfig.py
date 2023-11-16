import os

# toolchains options
ARCH     = 'avr32'
CPU      = 'uc3'
PART     = 'uc3b0256'
BOARD    = 'USERBOARD'
ATOMICS  = ' -D__STDC_NO_ATOMICS__'

CROSS_TOOL 	= 'gcc'

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
	PLATFORM 	= 'gcc'
	EXEC_PATH 	= 'C:/Program Files (x86)/Atmel/AVR Tools/AVR Toolchain/bin'
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

#BUILD = 'debug'
BUILD = 'release'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'avr32-'
    CC = PREFIX + 'gcc'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -mpart=' + PART
    CFLAGS = DEVICE + ' -DBOARD=' + BOARD + ATOMICS + ' -fmessage-length=0 -ffunction-sections -masm-addr-pseudos'
    AFLAGS = ' -c -x assembler-with-cpp' + DEVICE
    LFLAGS = DEVICE + ' -Wl,--gc-sections --rodata-writable -Wl,--direct-data -LSOFTWARE_FRAMEWORK/UTILS/LIBS/NEWLIB_ADDONS -T avr32elf_uc3b0256.lds'

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -g3 -Wall'
        AFLAGS += ' -g3'
    else:
        CFLAGS += ' -O2 -Wall'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
