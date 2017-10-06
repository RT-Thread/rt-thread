#************************************************************
# RT-Thread RTOS makefile base on Andes N1068A core
#
# Mengxin Technology Co., Ltd.
# Archer Chang <archer.zhang@wh-mx.com>
# 2017.07.25 16:00
#
#************************************************************

CROSS_COMPILE ?= nds32le-elf-
SIZE_OUTPUTS = .PHONY.size

CC	    := $(CROSS_COMPILE)gcc
OBJCOPY	:= $(CROSS_COMPILE)objcopy
AR	    := $(CROSS_COMPILE)ar
AS	    := $(CROSS_COMPILE)as

ifeq ($(DEBUG),1)
	OPTIM	:= -O0 -g2
else
	OPTIM	:= -O2 -g0
endif

ROOT_PATH                  := .
RTOS_PATH		           := $(ROOT_PATH)/../..
ARCH_PATH		           := $(RTOS_PATH)/libcpu
KERNEL_PATH		           := $(RTOS_PATH)/src
COMPONENTS_PATH	           := $(RTOS_PATH)/components
COMPONENTS_INIT_PATH       := $(COMPONENTS_PATH)/init
COMPONENTS_DRV_PATH        := $(COMPONENTS_PATH)/drivers
COMPONENTS_DRVSRC_PATH     := $(COMPONENTS_DRV_PATH)/src
COMPONENTS_DRVINC_PATH     := $(COMPONENTS_DRV_PATH)/include
COMPONENTS_DRVINC_DRV_PATH := $(COMPONENTS_DRVINC_PATH)/drivers
BSP_PATH		           := $(RTOS_PATH)/bsp
CLI_PATH		           := $(COMPONENTS_PATH)/finsh

PLATFORM_PATH     := $(BSP_PATH)/AE210P
ARCH_SEL_PATH	  := $(ARCH_PATH)/nds32
CONFIG_PATH		  := $(PLATFORM_PATH)
BOARD_PATH		  := $(PLATFORM_PATH)/board
#LIBC_PATH	      := $(PLATFORM_PATH)/libc
LDSCRIPT          := $(BOARD_PATH)/ae210p.ld
CONFIG_H          := $(CONFIG_PATH)/config.h
PLATFORM_DEF	  := -DAE210P
ARCH_INCLUDE_PATH := $(ARCH_PATH)/nds32

HW_HAL_SRC := $(BOARD_PATH)/ae210p.c \
			  $(PLATFORM_PATH)/board.c \
			  $(ARCH_SEL_PATH)/cpuport.c \
			  $(PLATFORM_PATH)/startup.c \
			  $(PLATFORM_PATH)/application.c 

DRIVERS_PATH := $(PLATFORM_PATH)/driver

OS_DEF := -DCONFIG_OS_RTTHREAD
INCLUDE_PATH := \
	-I$(RTOS_PATH) \
	-I$(ARCH_INCLUDE_PATH) \
	-I$(RTOS_PATH)/include \
	-I${KERNEL_PATH} \
	-I$(CONFIG_PATH) \
	-I$(PLATFORM_PATH) \
	-I$(BOARD_PATH) \
	-I$(DRIVERS_PATH) \
	-I$(CLI_PATH) \
	-I$(COMPONENTS_DRVINC_PATH) \
	-I$(COMPONENTS_DRVINC_DRV_PATH) \
	-I$(COMPONENTS_INIT_PATH) 

SMALL_HEAP_DEF := 

#Check GCC version
VERSION := $(shell $(CC) --version | grep ^$(CC) | sed 's/^.* //g')
GCC_VERSION := $(shell echo $(VERSION)| sed -e 's/\.\([0-9][0-9]\)/\1/g' -e 's/\.\([0-9]\)/0\1/g' -e 's/^[0-9]\{3,4\}$$/&00/' )

# GCC version before 4.8.2 doesn't support -mcmodel
ifneq ($(shell expr `echo $(GCC_VERSION)` \< 40802 ),1)
	CMODEL := -mcmodel=large
endif

CFLAGS := \
	$(INCLUDE_PATH) \
	-Wall \
	$(PLATFORM_DEF) \
	$(OS_DEF) \
	$(SMALL_HEAP_DEF) \
	-fno-builtin -fomit-frame-pointer -funroll-loops \
	-fno-strict-aliasing -ffunction-sections \
	$(CMODEL) \
	$(OPTIM) \
	$(OSC_DEF) \
	$(CFLAGS_EXT)

LD_FLAGS := $(OPTIM) -fno-builtin -nostartfiles -static -Wl,--gc-sections $(CMODEL)
AFLAGS   := -fno-builtin

# Add `-fno-delete-null-pointer-checks` flag if the compiler supports it.
# GCC assumes that programs cannot safely dereference null pointers, 
# and that no code or data element resides there.
# However, 0x0 is the vector table memory location, so the test must not be removed.
ifeq ($(shell $(CC) -fno-delete-null-pointer-checks -E - 2>/dev/null >/dev/null </dev/null ; echo $$?),0)
	CFLAGS += -fno-delete-null-pointer-checks
	LD_FLAGS += -fno-delete-null-pointer-checks
endif

# Maybe necessary
NO_IFC = y
NO_EX9 = y

ifeq ($(shell echo | $(CC) -E -dM - | grep __NDS32_EXT_IFC__ > /dev/null && echo IFC),IFC)
	ifeq ($(NO_IFC),y)
		CFLAGS += -mno-ifc -DCONFIG_NO_NDS32_EXT_IFC
		LD_FLAGS += -Wl,--mno-ifc
	endif
else
	ifneq ($(NO_IFC),)
		$(error this toolchain do not support IFC extension)
	endif
endif

ifeq ($(shell echo | $(CC) -E -dM - | grep __NDS32_EXT_EX9__ > /dev/null && echo EX9),EX9)
	ifeq ($(NO_EX9),y)
		CFLAGS += -mno-ex9 -DCONFIG_NO_NDS32_EXT_EX9
		LD_FLAGS += -Wl,--mno-ex9
	endif
else
	ifneq ($(NO_EX9),)
		$(error this toolchain do not support EX9 extension)
	endif
endif

ifeq ($(CACHE),1)
	CFLAGS += -DCONFIG_CACHE_SUPPORT
endif


# add INTC check
ifeq ($(EXT_INTC),1)
	CFLAGS += -DCONFIG_EXT_INTC
endif

# HWZOL check
ifeq ($(HWZOL),1)
	ifeq ($(shell echo | $(CC) -E -dM -mext-zol - | grep '\<__NDS32_EXT_ZOL__\>' > /dev/null && echo "ZOL"), ZOL)
		CFLAGS += -DCONFIG_HWZOL
		LD_FLAGS += -mext-zol
	else
		$(error this toolchain do not support ZOL extension)
	endif
endif

RTOS_SRC := \
	$(KERNEL_PATH)/clock.c \
	$(KERNEL_PATH)/device.c \
	$(KERNEL_PATH)/idle.c \
	$(KERNEL_PATH)/ipc.c \
	$(KERNEL_PATH)/irq.c \
	$(KERNEL_PATH)/kservice.c \
	$(KERNEL_PATH)/mem.c \
	$(KERNEL_PATH)/mempool.c \
	$(KERNEL_PATH)/scheduler.c \
	$(KERNEL_PATH)/thread.c \
	$(KERNEL_PATH)/timer.c \
	$(KERNEL_PATH)/object.c \

NDS32_SRC := \
	$(PLATFORM_PATH)/reset.c \
	$(PLATFORM_PATH)/cache.c \
	$(HW_HAL_SRC) \

BOOT_SRC := \
	$(PLATFORM_PATH)/start.S	\
	$(ARCH_SEL_PATH)/context_gcc.S

CLI_SRC := 
ifeq ($(USING_CLI),1)
	CLI_SRC	+= $(KERNEL_PATH)/components.c \
			   $(COMPONENTS_DRVSRC_PATH)/ringbuffer.c \
			   $(COMPONENTS_DRVSRC_PATH)/completion.c \
			   $(COMPONENTS_DRVSRC_PATH)/dataqueue.c \
			   $(CLI_PATH)/cmd.c \
			   $(CLI_PATH)/finsh_compiler.c \
			   $(CLI_PATH)/finsh_error.c \
			   $(CLI_PATH)/finsh_heap.c \
			   $(CLI_PATH)/finsh_init.c \
			   $(CLI_PATH)/finsh_node.c \
			   $(CLI_PATH)/finsh_ops.c \
			   $(CLI_PATH)/finsh_parser.c \
			   $(CLI_PATH)/finsh_token.c \
			   $(CLI_PATH)/finsh_var.c \
			   $(CLI_PATH)/finsh_vm.c \
			   $(CLI_PATH)/msh.c \
			   $(CLI_PATH)/msh_cmd.c \
			   $(CLI_PATH)/shell.c \
			   $(CLI_PATH)/symbol.c 
endif

#DRIVER_SRC := \
	${UART_DRIVER_SRC} \
	${LCD_DRIVER_SRC} \
	${SD_DRIVER_SRC} \
	${TOUCHSCREEN_DRIVER_SRC} \
	${AC97_DRIVER_SRC} \
	${DMA_DRIVER_SRC} \
	${HAL_DRIVER_SRC} \

DRIVER_SRC	:= \
	$(PLATFORM_PATH)/driver/uart/uart.c \
	$(PLATFORM_PATH)/driver/gpio/gpio.c \
	$(BOARD_PATH)/uart_dev.c \
	$(COMPONENTS_DRV_PATH)/serial/serial.c 
#	$(PLATFORM_PATH)/driver/dma/dmad.c 

#LIBC_SRC := \
#	$(LIBC_PATH)/stdio/fgets.c \
#	$(LIBC_PATH)/stdio/fputs.c \
#	$(LIBC_PATH)/stdio/fprintf.c \
#	$(LIBC_PATH)/stdio/do_printf.c \
#	$(LIBC_PATH)/stdio/printf.c \
#	$(LIBC_PATH)/string/memcpy.c \
#	$(LIBC_PATH)/string/memmove.c \
#	$(LIBC_PATH)/string/memset.c \
#	$(LIBC_PATH)/string/strcat.c \
#	$(LIBC_PATH)/string/strcasecmp.c \
#	$(LIBC_PATH)/string/strcmp.c \
#	$(LIBC_PATH)/string/strcpy.c \
#	$(LIBC_PATH)/string/strdup.c \
#	$(LIBC_PATH)/string/strlen.c \
#	$(LIBC_PATH)/string/strstr.c \
#	$(LIBC_PATH)/string/strupr.c \
#	$(LIBC_PATH)/string/wchar.c \
#	$(LIBC_PATH)/stdlib/qsort.c

#LIBC_FILE_SRC := \
#	$(LIBC_PATH)/stdio/file.c \

#********************************************
#  Applications
#********************************************
APP_SRCS := 

#################################################################
#								#
# Source code to each application				#
#								#
#################################################################
SRCS := \
	${NDS32_SRC} \
	${RTOS_SRC} \
	${DRIVER_SRC} \
	${CLI_SRC} \
	${APP_SRCS} #\
#	${LIBC_SRC} 

ALL_C_SRCS	:= ${SRCS} 
ALL_AS_SRCS	+= ${BOOT_SRC} 

# % can match to all the strings
ALL_C_OBJS := $(patsubst %.S,%.o,$(patsubst %.c,%.o,${ALL_C_SRCS}))
ALL_AS_OBJS := $(patsubst %.S,%.o,${ALL_AS_SRCS})

OBJS = ${ALL_C_OBJS} ${ALL_AS_OBJS}

.PHONY: all clean distclean

all: ${APP}.elf ${APP}.bin $(SIZE_OUTPUTS)
	if test ! -d ./build; then \
		mkdir ./build; \
	fi
	mv ${APP}.elf ${APP}.bin ./build

clean:
	$(RM) $(OBJS)
	$(RM) ./build/${APP}.elf ./build/${APP}.bin

distclean: clean
	$(RM) -rf build/

.SUFFIXES : .o .c .S

.c.o : $(CONFIG_H)
	$(CC) -include $(CONFIG_H) -c $(CFLAGS) $< -o $@
.S.o : $(CONFIG_H)
	$(CC) -include $(CONFIG_H) -c $(CFLAGS) $(AFLAGS) $< -o $@

${APP}.elf: $(CONFIG_H) ${KCONFIG_CONFIG} ${ALL_C_OBJS} ${ALL_AS_OBJS}
	@echo ' '
	$(CC) -T$(LDSCRIPT) ${ALL_C_OBJS} ${ALL_AS_OBJS} $(LD_FLAGS) $(LFLAGS_EXT) -o $@
	@echo ' '

${APP}.bin: ${APP}.elf
#	@echo ' '
	$(OBJCOPY) ${APP}.elf -O binary ${APP}.bin
	@echo ' '

.PHONY.size: 
#	@echo ' '
	$(CROSS_COMPILE)size ${APP}.elf | tee .PHONY.size
	@echo ' '

.PHONY: all clean distclean .PHONY.size
