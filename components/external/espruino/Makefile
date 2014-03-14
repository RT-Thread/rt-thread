# This file is part of Espruino, a JavaScript interpreter for Microcontrollers
#
# Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# -----------------------------------------------------------------------------
# Makefile for Espruino
# -----------------------------------------------------------------------------
# Set ONE of the following environment variables to compile for that board:
#
# ESPRUINO_1V0=1          # Espruino board rev 1.0
# ESPRUINO_1V1=1          # Espruino board rev 1.1 and 1.2
# ESPRUINO_1V3=1          # Espruino board rev 1.3
# OLIMEXINO_STM32=1                # Olimexino STM32
# OLIMEXINO_STM32_BOOTLOADER=1     # Olimexino STM32 with bootloader
# EMBEDDED_PI=1           # COOCOX STM32 Embedded Pi boards
# HYSTM32_24=1            # HY STM32 2.4 Ebay boards
# HYSTM32_28=1            # HY STM32 2.8 Ebay boards
# HYSTM32_32=1            # HY STM32 3.2 VCT6 Ebay boards
# STM32VLDISCOVERY=1
# STM32F3DISCOVERY=1
# STM32F4DISCOVERY=1
# STM32F429IDISCOVERY=1
# CARAMBOLA=1
# RASPBERRYPI=1
# LPC1768=1 # beta
# LCTECH_STM32F103RBT6=1 # LC Technology STM32F103RBT6 Ebay boards
# Or nothing for standard linux compile
#
# Also:
#
# DEBUG=1                 # add debug symbols (-g)
# RELEASE=1               # Force release-style compile (no asserts, etc)
# SINGLETHREAD=1          # Compile single-threaded to make compilation errors easier to find
# BOOTLOADER=1            # make the bootloader (not Espruino)
# PROFILE=1               # Compile with gprof profiling info

ifndef SINGLETHREAD
MAKEFLAGS=-j5 # multicore
endif

INCLUDE=-I$(ROOT) -I$(ROOT)/targets -I$(ROOT)/src -I$(ROOT)/gen
LIBS=
DEFINES=
CFLAGS=-Wall -Wextra -Wconversion -Werror=implicit-function-declaration -fdiagnostics-show-option
OPTIMIZEFLAGS= 
#-fdiagnostics-show-option - shows which flags can be used with -Werror 

# Espruino flags...
USE_MATH=1

ifeq ($(shell uname -m),armv6l)
RASPBERRYPI=1 # just a guess
endif

ifeq ($(shell uname),Darwin)
MACOSX=1
endif

# Gordon's car ECU (extremely beta!)
ifdef ECU
STM32F4DISCOVERY=1
#HYSTM32_32=1 
USE_TRIGGER=1
DEFINES += -DECU
endif

ifdef RELEASE
# force no asserts to be compiled in
DEFINES += -DNO_ASSERT
endif

CWD = $(shell pwd)
ROOT = $(CWD)
PRECOMPILED_OBJS=
PLATFORM_CONFIG_FILE=gen/platform_config.h
BASEADDRESS=0x08000000

###################################################
# When adding stuff here, also remember build_pininfo, platform_config.h, jshardware.c
ifdef ESPRUINO_1V0
USB=1
#USE_NET=1
#USE_CC3000=1
USE_GRAPHICS=1
USE_FILESYSTEM=1
FAMILY=STM32F1
CHIP=STM32F103RG
BOARD=ESPRUINOBOARD_R1_0
DEFINES+=-DESPRUINOBOARD
STLIB=STM32F10X_XL
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f1/lib/startup_stm32f10x_hd.o
OPTIMIZEFLAGS+=-O3
else ifdef ESPRUINO_1V1
DEFINES+=-DESPRUINO_1V1
USE_BOOTLOADER=1
BOOTLOADER_PROJ_NAME=bootloader_espruino_1v1
USB=1
USE_NET=1
USE_CC3000=1
USE_GRAPHICS=1
USE_FILESYSTEM=1
FAMILY=STM32F1
CHIP=STM32F103RC
BOARD=ESPRUINOBOARD_R1_1
DEFINES+=-DESPRUINOBOARD
STLIB=STM32F10X_XL
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f1/lib/startup_stm32f10x_hd.o
OPTIMIZEFLAGS+=-Os # not that short on memory, but Travis compiler is old and uses more
else ifdef ESPRUINO_1V3
DEFINES+=-DESPRUINO_1V3
USE_BOOTLOADER=1
BOOTLOADER_PROJ_NAME=bootloader_espruino_1v3
USB=1
USE_NET=1
USE_CC3000=1
USE_GRAPHICS=1
USE_FILESYSTEM=1
FAMILY=STM32F1
CHIP=STM32F103RC
BOARD=ESPRUINOBOARD
STLIB=STM32F10X_XL
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f1/lib/startup_stm32f10x_hd.o
OPTIMIZEFLAGS+=-O3
else ifdef OLIMEXINO_STM32
USB=1
USE_FILESYSTEM=1
FAMILY=STM32F1
CHIP=STM32F103RB
BOARD=OLIMEXINO_STM32
STLIB=STM32F10X_MD
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f1/lib/startup_stm32f10x_md.o
OPTIMIZEFLAGS+=-Os # short on program memory
else ifdef OLIMEXINO_STM32_BOOTLOADER
USB=1
USE_FILESYSTEM=1
FAMILY=STM32F1
CHIP=STM32F103RB_MAPLE
DEFINES += -DSTM32F103RB
SAVE_ON_FLASH=1
BOARD=OLIMEXINO_STM32_BOOTLOADER
STLIB=STM32F10X_MD
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f1/lib/startup_stm32f10x_md.o
OPTIMIZEFLAGS+=-Os # short on program memory
else ifdef EMBEDDED_PI
USB=1
# USE_FILESYSTEM=1 # no SD-CARD READER
FAMILY=STM32F1
CHIP=STM32F103RB
BOARD=EMBEDDED_PI
STLIB=STM32F10X_MD
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f1/lib/startup_stm32f10x_md.o
OPTIMIZEFLAGS+=-Os # short on program memory
else ifdef HYSTM32_24
USB=1
USE_GRAPHICS=1
USE_LCD_FSMC=1
USE_FILESYSTEM=1
USE_FILESYSTEM_SDIO=1
FAMILY=STM32F1
CHIP=STM32F103VE
BOARD=HYSTM32_24
STLIB=STM32F10X_HD
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f1/lib/startup_stm32f10x_hd.o
OPTIMIZEFLAGS+=-O3
else ifdef HYSTM32_28
USB=1
USE_GRAPHICS=1
USE_LCD_FSMC=1
DEFINES+=-DILI9325_BITBANG # bit-bang the LCD driver
SAVE_ON_FLASH=1
#USE_FILESYSTEM=1 # just normal SPI
FAMILY=STM32F1
CHIP=STM32F103RB
BOARD=HYSTM32_28
STLIB=STM32F10X_MD
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f1/lib/startup_stm32f10x_md.o
OPTIMIZEFLAGS+=-Os
else ifdef HYSTM32_32
USB=1
USE_GRAPHICS=1
USE_LCD_FSMC=1
USE_FILESYSTEM=1
USE_FILESYSTEM_SDIO=1
FAMILY=STM32F1
CHIP=STM32F103VC
BOARD=HYSTM32_32
STLIB=STM32F10X_HD
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f1/lib/startup_stm32f10x_hd.o
OPTIMIZEFLAGS+=-O3
else ifdef STM32F4DISCOVERY
USB=1
#USE_NET=1
#USE_CC3000=1
USE_GRAPHICS=1
DEFINES += -DUSE_USB_OTG_FS=1
FAMILY=STM32F4
CHIP=STM32F407
BOARD=STM32F4DISCOVERY
STLIB=STM32F4XX
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f4/lib/startup_stm32f4xx.o
OPTIMIZEFLAGS+=-O3
else ifdef STM32F429IDISCOVERY
USB=1
USE_GRAPHICS=1
#USE_LCD_FSMC=1
DEFINES += -DUSE_USB_OTG_FS=1
FAMILY=STM32F4
CHIP=STM32F429
BOARD=STM32F429IDISCOVERY
STLIB=STM32F4XX
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f4/lib/startup_stm32f4xx.o
OPTIMIZEFLAGS+=-O3
else ifdef SMARTWATCH
DEFINES+=-DHSE_VALUE=26000000UL
USB=1
FAMILY=STM32F2
CHIP=STM32F205RG
BOARD=SMARTWATCH
STLIB=STM32F2XX
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f2/lib/startup_stm32f2xx.o
OPTIMIZEFLAGS+=-O3
else ifdef STM32F3DISCOVERY
#USE_BOOTLOADER=1
#BOOTLOADER_PROJ_NAME=bootloader_espruino_stm32f3discovery
USB=1
FAMILY=STM32F3
CHIP=STM32F303
BOARD=STM32F3DISCOVERY
STLIB=STM32F3XX
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f3/lib/startup_stm32f30x.o
OPTIMIZEFLAGS+=-O3
else ifdef STM32VLDISCOVERY
FAMILY=STM32F1
CHIP=STM32F100RB
BOARD=STM32VLDISCOVERY
STLIB=STM32F10X_MD_VL
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f1/lib/startup_stm32f10x_md_vl.o
OPTIMIZEFLAGS+=-Os # short on program memory
else ifdef TINYCHIP
FAMILY=STM32F1
CHIP=STM32F103TB
BOARD=TINYCHIP
STLIB=STM32F10X_MD
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f1/lib/startup_stm32f10x_md.o
OPTIMIZEFLAGS+=-Os # short on program memory
else ifdef LPC1768
MBED=1
FAMILY=LPC1768
CHIP=LPC1768
BOARD=LPC1768
MBED_GCC_CS_DIR=$(ROOT)/targets/libmbed/LPC1768/GCC_CS
PRECOMPILED_OBJS+=$(MBED_GCC_CS_DIR)/sys.o $(MBED_GCC_CS_DIR)/cmsis_nvic.o $(MBED_GCC_CS_DIR)/system_LPC17xx.o $(MBED_GCC_CS_DIR)/core_cm3.o $(MBED_GCC_CS_DIR)/startup_LPC17xx.o 
LIBS+=-L$(MBED_GCC_CS_DIR)  -lmbed 
OPTIMIZEFLAGS+=-O3
else ifdef CARAMBOLA
BOARD=CARAMBOLA
DEFINES += -DCARAMBOLA -DSYSFS_GPIO_DIR="\"/sys/class/gpio\""
LINUX=1
USE_FILESYSTEM=1
USB=1
USE_GRAPHICS=1
USE_NET=1
else ifdef RASPBERRYPI
BOARD=RASPBERRYPI
DEFINES += -DRASPBERRYPI -DSYSFS_GPIO_DIR="\"/sys/class/gpio\""
LINUX=1
USE_FILESYSTEM=1
USB=1
USE_GRAPHICS=1
#USE_LCD_SDL=1
USE_NET=1
else ifdef LCTECH_STM32F103RBT6
USB=1
SAVE_ON_FLASH=1
FAMILY=STM32F1
CHIP=STM32F103RB
BOARD=LCTECH_STM32F103RBT6
STLIB=STM32F10X_MD
PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f1/lib/startup_stm32f10x_md.o
OPTIMIZEFLAGS+=-Os
else
BOARD=LINUX
LINUX=1
USE_FILESYSTEM=1
USB=1
USE_GRAPHICS=1
#USE_LCD_SDL=1
ifndef MACOSX
# http libs need some tweaks before net can compile
USE_NET=1
endif
endif

PROJ_NAME=$(shell python scripts/get_binary_name.py $(BOARD)  | sed -e "s/.bin$$//")
ifeq ($(PROJ_NAME),)
$(error Unable to work out binary name (PROJ_NAME)) 
endif
ifeq ($(BOARD),LINUX)
PROJ_NAME=espruino
endif



ifdef DEBUG
#OPTIMIZEFLAGS=-Os -g
OPTIMIZEFLAGS=-g
endif

ifdef PROFILE
OPTIMIZEFLAGS+=-pg
endif

WRAPPERFILE=gen/jswrapper.c
WRAPPERSOURCES = \
src/jswrap_pin.c \
src/jswrap_functions.c \
src/jswrap_modules.c \
src/jswrap_process.c \
src/jswrap_interactive.c \
src/jswrap_json.c \
src/jswrap_object.c \
src/jswrap_string.c \
src/jswrap_array.c \
src/jswrap_arraybuffer.c \
src/jswrap_serial.c \
src/jswrap_spi_i2c.c \
src/jswrap_onewire.c \
src/jswrap_io.c
# it is important that _pin comes before stuff which uses
# integers (as the check for int *includes* the chek for pin)

SOURCES = \
src/jslex.c \
src/jsvar.c \
src/jsutils.c \
src/jsparse.c \
src/jspin.c \
src/jsinteractive.c \
src/jsdevices.c \
$(WRAPPERFILE)
CPPSOURCES =

ifdef BOOTLOADER
ifndef USE_BOOTLOADER
$(error Using bootloader on device that is not expecting one)
endif
BUILD_LINKER_FLAGS+=--bootloader
PROJ_NAME=$(BOOTLOADER_PROJ_NAME)
WRAPPERSOURCES =
SOURCES = \
targets/stm32_boot/main.c \
targets/stm32_boot/utils.c
 ifndef DEBUG
  OPTIMIZEFLAGS=-Os
 endif
else # !BOOTLOADER
 ifdef USE_BOOTLOADER
  BUILD_LINKER_FLAGS+=--using_bootloader
  STM32LOADER_FLAGS+=-p /dev/ttyACM0
  BASEADDRESS=$(shell python -c "import sys;sys.path.append('scripts');import common;print hex(0x08000000+common.get_bootloader_size())")
 endif
endif

ifdef USB_PRODUCT_ID
DEFINES+=-DUSB_PRODUCT_ID=$(USB_PRODUCT_ID)
endif

ifdef SAVE_ON_FLASH
DEFINES+=-DSAVE_ON_FLASH
endif

ifdef USE_FILESYSTEM
DEFINES += -DUSE_FILESYSTEM
WRAPPERSOURCES += libs/jswrap_fat.c
ifndef LINUX 
INCLUDE += -I$(ROOT)/libs/fat_sd
SOURCES += \
libs/fat_sd/fattime.c \
libs/fat_sd/ff.c
#libs/fat_sd/option/ccsbcs.c # for LFN support (see _USE_LFN in ff.h)

ifdef USE_FILESYSTEM_SDIO
DEFINES += -DUSE_FILESYSTEM_SDIO
SOURCES += \
libs/fat_sd/sdio_diskio.c \
libs/fat_sd/sdio_sdcard.c
else #USE_FILESYSTEM_SDIO
SOURCES += \
libs/fat_sd/spi_diskio.c
endif #USE_FILESYSTEM_SDIO
endif #!LINUX
endif #USE_FILESYSTEM

ifdef USE_MATH
DEFINES += -DUSE_MATH
WRAPPERSOURCES += libs/jswrap_math.c

ifndef LINUX 
INCLUDE += -I$(ROOT)/libs/math
SOURCES += \
libs/math/acosh.c \
libs/math/asin.c \
libs/math/asinh.c \
libs/math/atan.c \
libs/math/atanh.c \
libs/math/cbrt.c \
libs/math/chbevl.c \
libs/math/clog.c \
libs/math/cmplx.c \
libs/math/const.c \
libs/math/cosh.c \
libs/math/drand.c \
libs/math/exp10.c \
libs/math/exp2.c \
libs/math/exp.c \
libs/math/fabs.c \
libs/math/floor.c \
libs/math/isnan.c \
libs/math/log10.c \
libs/math/log2.c \
libs/math/log.c \
libs/math/mtherr.c \
libs/math/polevl.c \
libs/math/pow.c \
libs/math/powi.c \
libs/math/round.c \
libs/math/setprec.c \
libs/math/sin.c \
libs/math/sincos.c \
libs/math/sindg.c \
libs/math/sinh.c \
libs/math/sqrt.c \
libs/math/tan.c \
libs/math/tandg.c \
libs/math/tanh.c \
libs/math/unity.c
#libs/math/mod2pi.c 
#libs/math/mtst.c 
#libs/math/dtestvec.c 
endif
endif

ifdef USE_GRAPHICS
DEFINES += -DUSE_GRAPHICS
WRAPPERSOURCES += libs/graphics/jswrap_graphics.c
INCLUDE += -I$(ROOT)/libs/graphics
SOURCES += \
libs/graphics/bitmap_font_8x8.c \
libs/graphics/graphics.c \
libs/graphics/lcd_arraybuffer.c \
libs/graphics/lcd_js.c

ifdef USE_LCD_SDL
DEFINES += -DUSE_LCD_SDL
SOURCES += libs/graphics/lcd_sdl.c
LIBS += -lSDL 
INCLUDE += -I/usr/include/SDL
endif

ifdef USE_LCD_FSMC
DEFINES += -DUSE_LCD_FSMC
SOURCES += libs/graphics/lcd_fsmc.c
endif

endif

ifdef USE_NET
DEFINES += -DUSE_NET
WRAPPERSOURCES += libs/network/http/jswrap_http.c
INCLUDE += -I$(ROOT)/libs/network/http
SOURCES += \
libs/network/http/httpserver.c 
ifdef LINUX
#LIBS += -l... 
#INCLUDE += -I...
endif
endif

ifdef USE_CC3000
DEFINES += -DUSE_CC3000 -DSEND_NON_BLOCKING
WRAPPERSOURCES += libs/network/cc3000/jswrap_cc3000.c
INCLUDE += -I$(ROOT)/libs/network/cc3000
SOURCES += \
libs/network/cc3000/board_spi.c \
libs/network/cc3000/cc3000_common.c \
libs/network/cc3000/evnt_handler.c \
libs/network/cc3000/hci.c \
libs/network/cc3000/netapp.c \
libs/network/cc3000/nvmem.c \
libs/network/cc3000/security.c \
libs/network/cc3000/socket.c \
libs/network/cc3000/wlan.c
endif

ifdef USE_TRIGGER
DEFINES += -DUSE_TRIGGER 
WRAPPERSOURCES += libs/trigger/jswrap_trigger.c
INCLUDE += -I$(ROOT)/libs/trigger
SOURCES += \
./libs/trigger/trigger.c
endif

ifdef USB
DEFINES += -DUSB
endif

ifeq ($(FAMILY), STM32F1)
ARCHFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3  -mfix-cortex-m3-ldrd  -mthumb-interwork -mfloat-abi=soft
ARM=1
STM32=1
INCLUDE += -I$(ROOT)/targetlibs/stm32f1 -I$(ROOT)/targetlibs/stm32f1/lib
DEFINES += -DSTM32F1
SOURCES +=                              \
targetlibs/stm32f1/lib/misc.c              \
targetlibs/stm32f1/lib/stm32f10x_adc.c     \
targetlibs/stm32f1/lib/stm32f10x_bkp.c     \
targetlibs/stm32f1/lib/stm32f10x_can.c     \
targetlibs/stm32f1/lib/stm32f10x_cec.c     \
targetlibs/stm32f1/lib/stm32f10x_crc.c     \
targetlibs/stm32f1/lib/stm32f10x_dac.c     \
targetlibs/stm32f1/lib/stm32f10x_dbgmcu.c  \
targetlibs/stm32f1/lib/stm32f10x_dma.c     \
targetlibs/stm32f1/lib/stm32f10x_exti.c    \
targetlibs/stm32f1/lib/stm32f10x_flash.c   \
targetlibs/stm32f1/lib/stm32f10x_fsmc.c    \
targetlibs/stm32f1/lib/stm32f10x_gpio.c    \
targetlibs/stm32f1/lib/stm32f10x_i2c.c     \
targetlibs/stm32f1/lib/stm32f10x_iwdg.c    \
targetlibs/stm32f1/lib/stm32f10x_pwr.c     \
targetlibs/stm32f1/lib/stm32f10x_rcc.c     \
targetlibs/stm32f1/lib/stm32f10x_rtc.c     \
targetlibs/stm32f1/lib/stm32f10x_sdio.c    \
targetlibs/stm32f1/lib/stm32f10x_spi.c     \
targetlibs/stm32f1/lib/stm32f10x_tim.c     \
targetlibs/stm32f1/lib/stm32f10x_usart.c   \
targetlibs/stm32f1/lib/stm32f10x_wwdg.c    \
targetlibs/stm32f1/lib/system_stm32f10x.c

ifdef USB
INCLUDE += -I$(ROOT)/targetlibs/stm32f1/usblib -I$(ROOT)/targetlibs/stm32f1/usb
SOURCES +=                              \
targetlibs/stm32f1/usblib/otgd_fs_cal.c       \
targetlibs/stm32f1/usblib/otgd_fs_dev.c       \
targetlibs/stm32f1/usblib/otgd_fs_int.c       \
targetlibs/stm32f1/usblib/otgd_fs_pcd.c       \
targetlibs/stm32f1/usblib/usb_core.c          \
targetlibs/stm32f1/usblib/usb_init.c          \
targetlibs/stm32f1/usblib/usb_int.c           \
targetlibs/stm32f1/usblib/usb_mem.c           \
targetlibs/stm32f1/usblib/usb_regs.c          \
targetlibs/stm32f1/usblib/usb_sil.c           \
targetlibs/stm32f1/usb/usb_desc.c              \
targetlibs/stm32f1/usb/usb_endp.c              \
targetlibs/stm32f1/usb/usb_istr.c              \
targetlibs/stm32f1/usb/usb_prop.c              \
targetlibs/stm32f1/usb/usb_pwr.c               \
targetlibs/stm32f1/usb/usb_utils.c
endif #USB

endif #STM32F1

ifeq ($(FAMILY), STM32F2)
ARCHFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3 -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
ARM=1
STM32=1
INCLUDE += -I$(ROOT)/targetlibs/stm32f2 -I$(ROOT)/targetlibs/stm32f2/lib
DEFINES += -DSTM32F2
SOURCES +=                                 \
targetlibs/stm32f2/lib/misc.c              \
targetlibs/stm32f2/lib/stm32f2xx_adc.c     \
targetlibs/stm32f2/lib/stm32f2xx_can.c     \
targetlibs/stm32f2/lib/stm32f2xx_crc.c     \
targetlibs/stm32f2/lib/stm32f2xx_cryp_aes.c\
targetlibs/stm32f2/lib/stm32f2xx_cryp.c    \
targetlibs/stm32f2/lib/stm32f2xx_cryp_des.c\
targetlibs/stm32f2/lib/stm32f2xx_cryp_tdes.c\
targetlibs/stm32f2/lib/stm32f2xx_dac.c     \
targetlibs/stm32f2/lib/stm32f2xx_dbgmcu.c     \
targetlibs/stm32f2/lib/stm32f2xx_dcmi.c     \
targetlibs/stm32f2/lib/stm32f2xx_dma.c     \
targetlibs/stm32f2/lib/stm32f2xx_exti.c     \
targetlibs/stm32f2/lib/stm32f2xx_flash.c     \
targetlibs/stm32f2/lib/stm32f2xx_fsmc.c     \
targetlibs/stm32f2/lib/stm32f2xx_gpio.c     \
targetlibs/stm32f2/lib/stm32f2xx_hash.c     \
targetlibs/stm32f2/lib/stm32f2xx_hash_md5.c     \
targetlibs/stm32f2/lib/stm32f2xx_hash_sha1.c     \
targetlibs/stm32f2/lib/stm32f2xx_i2c.c     \
targetlibs/stm32f2/lib/stm32f2xx_iwdg.c     \
targetlibs/stm32f2/lib/stm32f2xx_pwr.c     \
targetlibs/stm32f2/lib/stm32f2xx_rcc.c     \
targetlibs/stm32f2/lib/stm32f2xx_rng.c     \
targetlibs/stm32f2/lib/stm32f2xx_rtc.c     \
targetlibs/stm32f2/lib/stm32f2xx_sdio.c     \
targetlibs/stm32f2/lib/stm32f2xx_spi.c     \
targetlibs/stm32f2/lib/stm32f2xx_syscfg.c     \
targetlibs/stm32f2/lib/stm32f2xx_tim.c     \
targetlibs/stm32f2/lib/stm32f2xx_usart.c     \
targetlibs/stm32f2/lib/stm32f2xx_wwdg.c    \
targetlibs/stm32f2/lib/system_stm32f2xx.c


ifdef USB
INCLUDE += -I$(ROOT)/targetlibs/stm32f2/usblib -I$(ROOT)/targetlibs/stm32f2/usb
SOURCES +=                                 \
targetlibs/stm32f2/usb/usbd_cdc_vcp.c \
targetlibs/stm32f2/usb/usb_irq_handlers.c \
targetlibs/stm32f2/usb/usbd_desc.c \
targetlibs/stm32f2/usb/usbd_usr.c \
targetlibs/stm32f2/usb/usb_bsp.c \
targetlibs/stm32f2/usblib/usbd_req.c \
targetlibs/stm32f2/usblib/usb_dcd_int.c \
targetlibs/stm32f2/usblib/usbd_core.c \
targetlibs/stm32f2/usblib/usbd_cdc_core.c \
targetlibs/stm32f2/usblib/usbd_ioreq.c \
targetlibs/stm32f2/usblib/usb_core.c \
targetlibs/stm32f2/usblib/usb_dcd.c
#targetlibs/stm32f2/usblib/usb_otg.c \
#targetlibs/stm32f2/usblib/usb_bsp_template.c \
#targetlibs/stm32f2/usblib/usbd_cdc_if_template.c \
#targetlibs/stm32f2/usblib/usb_hcd.c \
#targetlibs/stm32f2/usblib/usb_hcd_int.c 
endif #USB
endif #STM32F2 

ifeq ($(FAMILY), STM32F3)
ARCHFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
ARM=1
STM32=1
INCLUDE += -I$(ROOT)/targetlibs/stm32f3 -I$(ROOT)/targetlibs/stm32f3/lib
DEFINES += -DSTM32F3
SOURCES +=                                 \
targetlibs/stm32f3/lib/stm32f30x_adc.c        \
targetlibs/stm32f3/lib/stm32f30x_can.c        \
targetlibs/stm32f3/lib/stm32f30x_comp.c       \
targetlibs/stm32f3/lib/stm32f30x_crc.c        \
targetlibs/stm32f3/lib/stm32f30x_dac.c        \
targetlibs/stm32f3/lib/stm32f30x_dbgmcu.c     \
targetlibs/stm32f3/lib/stm32f30x_dma.c        \
targetlibs/stm32f3/lib/stm32f30x_exti.c       \
targetlibs/stm32f3/lib/stm32f30x_flash.c      \
targetlibs/stm32f3/lib/stm32f30x_gpio.c       \
targetlibs/stm32f3/lib/stm32f30x_i2c.c        \
targetlibs/stm32f3/lib/stm32f30x_iwdg.c       \
targetlibs/stm32f3/lib/stm32f30x_misc.c       \
targetlibs/stm32f3/lib/stm32f30x_opamp.c      \
targetlibs/stm32f3/lib/stm32f30x_pwr.c        \
targetlibs/stm32f3/lib/stm32f30x_rcc.c        \
targetlibs/stm32f3/lib/stm32f30x_rtc.c        \
targetlibs/stm32f3/lib/stm32f30x_spi.c        \
targetlibs/stm32f3/lib/stm32f30x_syscfg.c     \
targetlibs/stm32f3/lib/stm32f30x_tim.c        \
targetlibs/stm32f3/lib/stm32f30x_usart.c      \
targetlibs/stm32f3/lib/stm32f30x_wwdg.c       \
targetlibs/stm32f3/lib/system_stm32f30x.c

ifdef USB
INCLUDE += -I$(ROOT)/targetlibs/stm32f3/usblib -I$(ROOT)/targetlibs/stm32f3/usb
SOURCES +=                                 \
targetlibs/stm32f3/usblib/usb_core.c          \
targetlibs/stm32f3/usblib/usb_init.c          \
targetlibs/stm32f3/usblib/usb_int.c           \
targetlibs/stm32f3/usblib/usb_mem.c           \
targetlibs/stm32f3/usblib/usb_regs.c          \
targetlibs/stm32f3/usblib/usb_sil.c           \
targetlibs/stm32f3/usb/usb_desc.c              \
targetlibs/stm32f3/usb/usb_endp.c              \
targetlibs/stm32f3/usb/usb_istr.c              \
targetlibs/stm32f3/usb/usb_prop.c              \
targetlibs/stm32f3/usb/usb_pwr.c               \
targetlibs/stm32f3/usb/usb_utils.c  
endif #USB
endif #STM32F3 

ifeq ($(FAMILY), STM32F4)
ARCHFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
ARM=1
STM32=1
INCLUDE += -I$(ROOT)/targetlibs/stm32f4 -I$(ROOT)/targetlibs/stm32f4/lib
DEFINES += -DSTM32F4
SOURCES +=                                 \
targetlibs/stm32f4/lib/misc.c                 \
targetlibs/stm32f4/lib/stm32f4xx_adc.c        \
targetlibs/stm32f4/lib/stm32f4xx_can.c        \
targetlibs/stm32f4/lib/stm32f4xx_crc.c        \
targetlibs/stm32f4/lib/stm32f4xx_cryp_aes.c   \
targetlibs/stm32f4/lib/stm32f4xx_cryp.c       \
targetlibs/stm32f4/lib/stm32f4xx_cryp_des.c   \
targetlibs/stm32f4/lib/stm32f4xx_cryp_tdes.c  \
targetlibs/stm32f4/lib/stm32f4xx_dac.c        \
targetlibs/stm32f4/lib/stm32f4xx_dbgmcu.c     \
targetlibs/stm32f4/lib/stm32f4xx_dcmi.c       \
targetlibs/stm32f4/lib/stm32f4xx_dma.c        \
targetlibs/stm32f4/lib/stm32f4xx_exti.c       \
targetlibs/stm32f4/lib/stm32f4xx_flash.c      \
targetlibs/stm32f4/lib/stm32f4xx_fsmc.c       \
targetlibs/stm32f4/lib/stm32f4xx_gpio.c       \
targetlibs/stm32f4/lib/stm32f4xx_hash.c       \
targetlibs/stm32f4/lib/stm32f4xx_hash_md5.c   \
targetlibs/stm32f4/lib/stm32f4xx_hash_sha1.c  \
targetlibs/stm32f4/lib/stm32f4xx_i2c.c        \
targetlibs/stm32f4/lib/stm32f4xx_iwdg.c       \
targetlibs/stm32f4/lib/stm32f4xx_pwr.c        \
targetlibs/stm32f4/lib/stm32f4xx_rcc.c        \
targetlibs/stm32f4/lib/stm32f4xx_rng.c        \
targetlibs/stm32f4/lib/stm32f4xx_rtc.c        \
targetlibs/stm32f4/lib/stm32f4xx_sdio.c       \
targetlibs/stm32f4/lib/stm32f4xx_spi.c        \
targetlibs/stm32f4/lib/stm32f4xx_syscfg.c     \
targetlibs/stm32f4/lib/stm32f4xx_tim.c        \
targetlibs/stm32f4/lib/stm32f4xx_usart.c      \
targetlibs/stm32f4/lib/stm32f4xx_wwdg.c       \
targetlibs/stm32f4/lib/system_stm32f4xx.c

ifdef USB
INCLUDE += -I$(ROOT)/targetlibs/stm32f4/usblib -I$(ROOT)/targetlibs/stm32f4/usb
SOURCES +=                                 \
targetlibs/stm32f4/usblib/usb_core.c          \
targetlibs/stm32f4/usblib/usbd_cdc_core.c     \
targetlibs/stm32f4/usblib/usb_dcd.c           \
targetlibs/stm32f4/usblib/usb_dcd_int.c       \
targetlibs/stm32f4/usblib/usbd_core.c         \
targetlibs/stm32f4/usblib/usbd_ioreq.c        \
targetlibs/stm32f4/usblib/usbd_req.c          \
targetlibs/stm32f4/usb/usb_bsp.c              \
targetlibs/stm32f4/usb/usbd_cdc_vcp.c         \
targetlibs/stm32f4/usb/usbd_desc.c            \
targetlibs/stm32f4/usb/usbd_usr.c
#targetlibs/stm32f4/usblib/usb_hcd.c           
#targetlibs/stm32f4/usblib/usb_hcd_int.c
#targetlibs/stm32f4/usblib/usb_otg.c           
endif #USB
endif #STM32F4


ifdef MBED
ARCHFLAGS += -mcpu=cortex-m3 -mthumb
ARM=1
INCLUDE+=-I$(ROOT)/targetlibs/libmbed -I$(ROOT)/targetlibs/libmbed/$(CHIP) -I$(ROOT)/targetlibs/libmbed/$(CHIP)/GCC_CS
DEFINES += -DMBED
INCLUDE += -I$(ROOT)/targetlibs/mbed
SOURCES += targets/mbed/main.c                     
CPPSOURCES += targets/mbed/jshardware.cpp             
endif

ifdef ARM
LINKER_FILE = gen/linker.ld
DEFINES += -DARM 
INCLUDE += -I$(ROOT)/targetlibs/arm
OPTIMIZEFLAGS += -fno-common -fno-exceptions -fdata-sections -ffunction-sections
# -flto -fuse-linker-plugin
# -flto  - link time optimisation - could be good for ST's libs
#          GCC suggests use of -fuse-linker-plugin with flto
#          Does not work - get errors like : `sqrt' referenced in section `.text.asin' of /tmp/ccJheOub.ltrans9.ltrans.o: defined in discarded section `.text' of libs/math/sqrt.o (symbol from plugin)


# 4.6
#export CCPREFIX=arm-linux-gnueabi-
# 4.5
#export CCPREFIX=~/sat/bin/arm-none-eabi-
# 4.4
export CCPREFIX=arm-none-eabi-
endif # ARM

PININFOFILE=$(ROOT)/gen/jspininfo
ifdef PININFOFILE
SOURCES += $(PININFOFILE).c
endif

ifdef CARAMBOLA
TOOLCHAIN_DIR=$(shell cd ~/workspace/carambola/staging_dir/toolchain-*/bin;pwd)
export STAGING_DIR=$(TOOLCHAIN_DIR)
export CCPREFIX=$(TOOLCHAIN_DIR)/mipsel-openwrt-linux-
endif

ifdef RASPBERRYPI
  ifneq ($(shell uname -m),armv6l)
    # eep. let's cross compile
    export CCPREFIX=targetlibs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-
  else
    # compiling in-place, so give it a normal name
    PROJ_NAME=espruino
  endif
endif


ifdef STM32
DEFINES += -DFAKE_STDLIB
# FAKE_STDLIB is for Espruino - it uses its own standard library so we don't have to link in the normal one + get bloated 
DEFINES += -DSTM32 -DUSE_STDPERIPH_DRIVER=1 -D$(CHIP) -D$(BOARD) -D$(STLIB)
INCLUDE += -I$(ROOT)/targets/stm32
ifndef BOOTLOADER
SOURCES +=                              \
targets/stm32/main.c                    \
targets/stm32/jshardware.c              \
targets/stm32/stm32_it.c
endif
endif

ifdef LINUX
DEFINES += -DLINUX
INCLUDE += -I$(ROOT)/targets/linux 
SOURCES +=                              \
targets/linux/main.c                    \
targets/linux/jshardware.c  
LIBS += -lm # maths lib
endif

SOURCES += $(WRAPPERSOURCES)
SOURCEOBJS = $(SOURCES:.c=.o) $(CPPSOURCES:.cpp=.o)
OBJS = $(SOURCEOBJS) $(PRECOMPILED_OBJS)


# -ffreestanding -nodefaultlibs -nostdlib -fno-common
# -nodefaultlibs -nostdlib -nostartfiles

# -fdata-sections -ffunction-sections are to help remove unused code
CFLAGS += $(OPTIMIZEFLAGS) -c $(ARCHFLAGS) $(DEFINES) $(INCLUDE)

# -Wl,--gc-sections helps remove unused code
# -Wl,--whole-archive checks for duplicates
LDFLAGS += $(OPTIMIZEFLAGS) $(ARCHFLAGS)
ifndef MACOSX
LDFLAGS += -Wl,--gc-sections
endif

ifdef LINKER_FILE 
LDFLAGS += -T$(LINKER_FILE)
endif 

export CC=$(CCPREFIX)gcc
export LD=$(CCPREFIX)gcc
export AR=$(CCPREFIX)ar
export AS=$(CCPREFIX)as
export OBJCOPY=$(CCPREFIX)objcopy
export OBJDUMP=$(CCPREFIX)objdump
export GDB=$(CCPREFIX)gdb


.PHONY:  proj

all: 	 proj

ifeq ($(V),1)
        quiet_=
        Q=
else
        quiet_=quiet_
        Q=@
	export SILENT=1
endif


$(WRAPPERFILE): scripts/build_jswrapper.py $(WRAPPERSOURCES)
	@echo Generating JS wrappers
	$(Q)echo WRAPPERSOURCES = $(WRAPPERSOURCES)
	$(Q)echo DEFINES =  $(DEFINES)
	$(Q)python scripts/build_jswrapper.py $(WRAPPERSOURCES) $(DEFINES)

ifdef PININFOFILE
$(PININFOFILE).c $(PININFOFILE).h: scripts/build_pininfo.py 
	@echo Generating pin info
	$(Q)python scripts/build_pininfo.py $(BOARD) $(PININFOFILE).c $(PININFOFILE).h
endif

$(LINKER_FILE): scripts/build_linker.py 
	@echo Generating linker scripts
	$(Q)python scripts/build_linker.py $(BOARD) $(LINKER_FILE) $(BUILD_LINKER_FLAGS)

$(PLATFORM_CONFIG_FILE): boards/$(BOARD).py scripts/build_platform_config.py
	@echo Generating platform configs
	$(Q)python scripts/build_platform_config.py $(BOARD)

compile=$(CC) $(CFLAGS) $(DEFINES) $< -o $@
link=$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)
obj_dump=$(OBJDUMP) -x -S $(PROJ_NAME).elf > $(PROJ_NAME).lst
obj_to_bin=$(OBJCOPY) -O $1 $(PROJ_NAME).elf $(PROJ_NAME).$2

quiet_compile= CC $@
quiet_link= LD $@
quiet_obj_dump= GEN $(PROJ_NAME).lst
quiet_obj_to_bin= GEN $(PROJ_NAME).$2

%.o: %.c $(PLATFORM_CONFIG_FILE) $(PININFOFILE).h
	@echo $($(quiet_)compile)
	@$(call compile)

.cpp.o: $(PLATFORM_CONFIG_FILE) $(PININFOFILE).h
	@echo $($(quiet_)compile)
	@$(call compile)

.s.o:
	@echo $($(quiet_)compile)
	@$(call compile)
	
ifdef LINUX # ---------------------------------------------------
proj: 	$(PLATFORM_CONFIG_FILE) $(PROJ_NAME)

$(PROJ_NAME): $(OBJS)
	@echo $($(quiet_)link)
	@$(call link)

else # embedded, so generate bin, etc ---------------------------

$(PROJ_NAME).elf: $(OBJS) $(LINKER_FILE)
	@echo $($(quiet_)link)
	@$(call link)

$(PROJ_NAME).lst : $(PROJ_NAME).elf
	@echo $($(quiet_)obj_dump)
	@$(call obj_dump)

$(PROJ_NAME).hex: $(PROJ_NAME).elf
	@echo $(call $(quiet_)obj_to_bin,ihex,hex)
	@$(call obj_to_bin,ihex,hex)

$(PROJ_NAME).srec : $(PROJ_NAME).elf
	@echo $(call $(quiet_)obj_to_bin,srec,srec)
	@$(call obj_to_bin,srec,srec)

$(PROJ_NAME).bin : $(PROJ_NAME).elf
	@echo $(call $(quiet_)obj_to_bin,binary,bin)
	@$(call obj_to_bin,binary,bin)
	bash scripts/check_size.sh $(PROJ_NAME).bin

proj: $(PROJ_NAME).lst $(PROJ_NAME).bin
#proj: $(PROJ_NAME).lst $(PROJ_NAME).hex $(PROJ_NAME).srec $(PROJ_NAME).bin

flash: all
ifdef OLIMEXINO_STM32_BOOTLOADER
	echo Olimexino Serial bootloader
	dfu-util -a1 -d 0x1EAF:0x0003 -D $(PROJ_NAME).bin
else
ifdef MBED
	cp $(PROJ_NAME).bin /media/MBED;sync
else
	echo ST-LINK flash
	~/bin/st-flash write $(PROJ_NAME).bin $(BASEADDRESS)
endif	
endif	

serialflash: all
	echo STM32 inbuilt serial bootloader, set BOOT0=1, BOOT1=0
	python scripts/stm32loader.py -b 460800 -a $(BASEADDRESS) -ew $(STM32LOADER_FLAGS) $(PROJ_NAME).bin
#	python scripts/stm32loader.py -b 460800 -a $(BASEADDRESS) -ewv $(STM32LOADER_FLAGS) $(PROJ_NAME).bin
		
gdb: 
	echo "target extended-remote :4242" > gdbinit
	echo "file $(PROJ_NAME).elf" >> gdbinit
	#echo "load" >> gdbinit
	echo "break main" >> gdbinit
	echo "break HardFault_Handler" >> gdbinit
	$(GDB) -x gdbinit
	rm gdbinit
endif	    # ---------------------------------------------------
 
clean:
	@echo Cleaning targets
	$(Q)find . -name *.o | grep -v libmbed | grep -v arm-bcm2708 | xargs rm -f
	$(Q)rm -f $(ROOT)/gen/*.c $(ROOT)/gen/*.h $(ROOT)/gen/*.ld
	$(Q)rm -f $(PROJ_NAME).elf
	$(Q)rm -f $(PROJ_NAME).hex
	$(Q)rm -f $(PROJ_NAME).bin
	$(Q)rm -f $(PROJ_NAME).srec
	$(Q)rm -f $(PROJ_NAME).lst
