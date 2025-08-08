include .config

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
	make mv_file

mv_file:
	mv rtthread_a64.elf rtthread_a64_$(CONFIG_BOARD_NAME).elf 
	mv rtthread_a64.bin rtthread_a64_$(CONFIG_BOARD_NAME).bin 
	cp rtthread_a64_$(CONFIG_BOARD_NAME).elf /mnt/d/tftpboot/rtthread_a64.elf
	cp rtthread_a64_$(CONFIG_BOARD_NAME).bin /mnt/d/tftpboot/rtthread_a64.bin

mv_auto_test_file:
	mv rtthread_a64.elf rtthread_a64_$(CONFIG_BOARD_NAME).elf 
	mv rtthread_a64_$(CONFIG_BOARD_NAME).elf /home/zhugy/tftpboot/rtthread_elfs/

debug:
	@$(OD) -D rtthread_a64_$(CONFIG_BOARD_NAME).elf > rtthread_a64_$(CONFIG_BOARD_NAME).asm
	@$(OD) -S rtthread_a64_$(CONFIG_BOARD_NAME).elf > rtthread_a64_$(CONFIG_BOARD_NAME).dis

all:
	@echo "Build started..."
	scons -j8

clean:
	@echo "Cleaning..."
	scons -c

menuconfig:
	@echo "Running menuconfig..."
	scons --menuconfig