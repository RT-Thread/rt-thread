
# toolchains options
ARCH     = 'avr32'
CPU      = 'uc3'
PART     = 'uc3b0256'
BOARD    = 'USERBOARD'

CROSS_TOOL 	= 'gcc'

if  CROSS_TOOL == 'gcc':
	PLATFORM 	= 'gcc'
	EXEC_PATH 	= 'C:/Program Files/Atmel/AVR Tools/AVR Toolchain/bin'
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
    CFLAGS = DEVICE + ' -DBOARD=' + BOARD + ' -fmessage-length=0 -ffunction-sections -masm-addr-pseudos'
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
