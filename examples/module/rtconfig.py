# bsp name
BSP = 'mini2440'

# toolchains
EXEC_PATH 	= 'C:/Program Files/CodeSourcery/Sourcery G++ Lite/bin'
PREFIX = 'arm-none-eabi-'
CC = PREFIX + 'gcc'
CXX = PREFIX + 'g++'
AS = PREFIX + 'gcc'
AR = PREFIX + 'ar'
LINK = PREFIX + 'gcc'
TARGET_EXT = 'so'
SIZE = PREFIX + 'size'
OBJDUMP = PREFIX + 'objdump'
OBJCPY = PREFIX + 'objcopy'

DEVICE = ' -mcpu=arm920t'
CFLAGS = DEVICE + ' -O0 -fPIC -DFTK_AS_PLUGIN -DRT_THREAD '
AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
LFLAGS = DEVICE + ' -Wl,-z,max-page-size=0x4 -shared -fPIC -nostdlib -s'

CPATH = ''
LPATH = ''
