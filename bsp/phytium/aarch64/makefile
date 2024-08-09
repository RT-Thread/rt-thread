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

ifdef CONFIG_E2000Q_DEMO_BOARD
RTCONFIG := e2000q_demo
endif

ifdef CONFIG_E2000D_DEMO_BOARD
RTCONFIG := e2000d_demo
endif

ifdef CONFIG_TARGET_PHYTIUMPI
RTCONFIG := phytium_pi
endif

ifdef CONFIG_RT_USING_SMART
RTCONFIG := $(RTCONFIG)_rtsmart
else
RTCONFIG := $(RTCONFIG)_rtthread
endif

ifdef CONFIG_PHYTIUM_RTT_TEST
RTCONFIG := $(RTCONFIG)_test
endif

ifdef CONFIG_RT_CHERRYUSB_HOST_PUSB2
RTCONFIG := $(RTCONFIG)_pusb2_hc
endif

ifdef CONFIG_RT_CHERRYUSB_DEVICE_PUSB2
RTCONFIG := $(RTCONFIG)_pusb2_dc
endif

boot:
	make all
	cp rtthread_a64.elf /mnt/d/tftpboot
	cp rtthread_a64.bin /mnt/d/tftpboot

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

load_e2000q_demo_rtsmart:
	@echo "Load configs from ./configs/e2000q_demo_rtsmart"
	@cp ./configs/e2000q_demo_rtsmart ./.config -f
	@cp ./configs/e2000q_demo_rtsmart.h ./rtconfig.h -f
	@scons -c

load_e2000q_demo_rtsmart_test:
	@echo "Load configs from ./configs/e2000q_demo_rtsmart_test"
	@cp ./configs/e2000q_demo_rtsmart_test ./.config -f
	@cp ./configs/e2000q_demo_rtsmart_test.h ./rtconfig.h -f
	@scons -c

load_e2000q_demo_rtthread:
	@echo "Load configs from ./configs/e2000q_demo_rtthread"
	@cp ./configs/e2000q_demo_rtthread ./.config -f
	@cp ./configs/e2000q_demo_rtthread.h ./rtconfig.h -f
	@scons -c

load_e2000q_demo_rtthread_test:
	@echo "Load configs from ./configs/e2000q_demo_rtthread_test"
	@cp ./configs/e2000q_demo_rtthread_test ./.config -f
	@cp ./configs/e2000q_demo_rtthread_test.h ./rtconfig.h -f
	@scons -c

load_e2000d_demo_rtsmart:
	@echo "Load configs from ./configs/e2000d_demo_rtsmart"
	@cp ./configs/e2000d_demo_rtsmart ./.config -f
	@cp ./configs/e2000d_demo_rtsmart.h ./rtconfig.h -f
	@scons -c

load_e2000d_demo_rtsmart_test:
	@echo "Load configs from ./configs/e2000d_demo_rtsmart_test"
	@cp ./configs/e2000d_demo_rtsmart_test ./.config -f
	@cp ./configs/e2000d_demo_rtsmart_test.h ./rtconfig.h -f
	@scons -c

load_e2000d_demo_rtthread:
	@echo "Load configs from ./configs/e2000d_demo_rtthread"
	@cp ./configs/e2000d_demo_rtthread ./.config -f
	@cp ./configs/e2000d_demo_rtthread.h ./rtconfig.h -f
	scons -c

load_e2000d_demo_rtthread_test:
	@echo "Load configs from ./configs/e2000d_demo_rtthread_test"
	@cp ./configs/e2000d_demo_rtthread_test ./.config -f
	@cp ./configs/e2000d_demo_rtthread_test.h ./rtconfig.h -f
	scons -c

load_phytium_pi_rtthread:
	@echo "Load configs from ./configs/phytium_pi_rtthread"
	@cp ./configs/phytium_pi_rtthread ./.config -f
	@cp ./configs/phytium_pi_rtthread.h ./rtconfig.h -f
	scons -c

load_phytium_pi_rtthread_pusb2_hc:
	@echo "Load configs from ./configs/phytium_pi_rtthread_pusb2_hc"
	@cp ./configs/phytium_pi_rtthread_pusb2_hc ./.config -f
	@cp ./configs/phytium_pi_rtthread_pusb2_hc.h ./rtconfig.h -f
	scons -c

load_phytium_pi_rtsmart:
	@echo "Load configs from ./configs/phytium_pi_rtsmart"
	@cp ./configs/phytium_pi_rtsmart ./.config -f
	@cp ./configs/phytium_pi_rtsmart.h ./rtconfig.h -f
	@scons -c