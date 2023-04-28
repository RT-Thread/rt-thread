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
RTCONFIG =

include .config

ifdef CONFIG_TARGET_E2000Q
RTCONFIG := e2000q
endif

ifdef CONFIG_TARGET_E2000D
RTCONFIG := e2000d
endif

ifdef CONFIG_RT_USING_SMART
RTCONFIG := $(RTCONFIG)_rtsmart
else
RTCONFIG := $(RTCONFIG)_rtthread
endif

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

saveconfig:
	@echo "Save configs to" ./configs/$(RTCONFIG)
	@cp ./.config ./configs/$(RTCONFIG) -f
	@cp ./rtconfig.h ./configs/$(RTCONFIG).h -f

load_e2000q_rtsmart:
	@echo "Load configs from ./configs/e2000q_rtsmart"
	@cp ./configs/e2000q_rtsmart ./.config -f
	@cp ./configs/e2000q_rtsmart.h ./rtconfig.h -f
	@scons -c

load_e2000q_rtthread:
	@echo "Load configs from ./configs/e2000q_rtthread"
	@cp ./configs/e2000q_rtthread ./.config -f
	@cp ./configs/e2000q_rtthread.h ./rtconfig.h -f
	@scons -c

load_e2000d_rtsmart:
	@echo "Load configs from ./configs/e2000d_rtsmart"
	@cp ./configs/e2000d_rtsmart ./.config -f
	@cp ./configs/e2000d_rtsmart.h ./rtconfig.h -f
	@scons -c

load_e2000d_rtthread:
	@echo "Load configs from ./configs/e2000d_rtthread"
	@cp ./configs/e2000d_rtthread ./.config -f
	@cp ./configs/e2000d_rtthread.h ./rtconfig.h -f
	@scons -c
