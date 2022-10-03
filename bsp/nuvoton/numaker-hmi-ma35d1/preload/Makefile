TARGET	?= preload

#################################
# GNU ARM Embedded Toolchain
#################################
CC=aarch64-elf-gcc
CXX=aarch64-elf-g++
LD=aarch64-elf-ld
AR=aarch64-elf-ar
AS=aarch64-elf-as
CP=aarch64-elf-objcopy
OD=aarch64-elf-objdump
NM=aarch64-elf-nm
SIZE=aarch64-elf-size
A2L=aarch64-elf-addr2line

#################################
# Working directories
#################################
ROOT		 = .

#################################
# Source Files
#################################

# Search path and source files

ASMSOURCES =  $(notdir $(wildcard *.ASM))

INCLUDE_DIRS  =	-I$(ROOT)

#################################
# Object List
#################################
OBJECTS=

#################################
# Target Output Files
#################################
TARGET_O=$(TARGET).o
TARGET_ASM=$(TARGET).asm

#################################
# Flags
#################################
MCFLAGS=-march=armv8-a
OPTIMIZE = -O2
AFLAGS=-c $(MCFLAGS) -x assembler-with-cpp -D__ASSEMBLY__
LDSCRIPT=
LDFLAGS = -nostartfiles  -Wl,--gc-sections,-cref,-Map=$(TARGET).map,-cref,-u,_start -T $(TARGET).ld

#################################
# Build
#################################
all: clean $(TARGET_O)

$(TARGET_O):
	@echo -n "Build $@ ..."
	$(CC) -c $(INCLUDE_DIRS) $(AFLAGS) $(ASMSOURCES) $(LDFLAGS)
	$(OD) -d $@ > $(TARGET).txt

#################################
# Recipes
#################################
.PHONY: all clean

clean:
	rm -f $(TARGET_O)