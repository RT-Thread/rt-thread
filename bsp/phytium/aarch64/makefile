.PHONY: debug boot all clean menuconfig

CC = $(RTT_EXEC_PATH)/$(RTT_CC_PREFIX)gcc
CXX = $(RTT_EXEC_PATH)/$(RTT_CC_PREFIX)g++
CPP = $(RTT_EXEC_PATH)/$(RTT_CC_PREFIX)gcc -E -P -x c
STRIP = $(RTT_EXEC_PATH)/$(RTT_CC_PREFIX)strip --strip-unneeded
OBJCOPY = $(RTT_EXEC_PATH)/$(RTT_CC_PREFIX)objcopy
OBJDUMP = $(RTT_EXEC_PATH)/$(RTT_CC_PREFIX)objdump
LD = $(RTT_EXEC_PATH)/$(RTT_CC_PREFIX)ld
AR = $(RTT_EXEC_PATH)/$(RTT_CC_PREFIX)ar rcs
NM = $(RTT_EXEC_PATH)/$(RTT_CC_PREFIX)nm
OD = $(RTT_EXEC_PATH)/$(RTT_CC_PREFIX)objdump


boot:
	make all
	cp rtthread_a64.elf /mnt/d/tftboot
	cp rtthread_a64.bin /mnt/d/tftboot

debug:
	@$(OD) -D rtthread_a64.elf > rtthread_a64.asm
	@$(OD) -S rtthread_a64.elf > rtthread_a64.dis
	
all:
	@echo "Build started..."
	scons -j1024

clean:
	@echo "Cleaning..."
	scons -c

menuconfig:
	@echo "Running menuconfig..."
	scons --menuconfig
