#
# Copyright (c) 2013-2017, ARM Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

# Enable workarounds for selected Cortex-A53 errata
ERRATA_A53_835769	:=	1
ERRATA_A53_843419	:=	1
ERRATA_A53_855873	:=	1

PAGE_SIZE_64KB := 1
TEST_FROM_SPINOR1 := 0

DEFINES += -DLZ4_USER_MEMORY_FUNCTIONS=1

# ifeq ($(FSBL_SECURE_BOOT_SUPPORT),1)
DEFINES += \
	-DNO_ALLOCS \
	-DARGTYPE=3 \
	-DLTC_NO_FILE \
	-DLTM_NO_FILE \
	-DLTM_DESC \
	-DLTC_SOURCE

CRYPT_INCLUDES := \
	-Ilib/libtommath \
	-Ilib/libtomcrypt/src/headers \
	-Ilib/BigDigits

CRYPT_SOURCES := \
	lib/BigDigits/bigdigits.c \
	lib/libtomcrypt/src/hashes/sha2/sha256.c
# endif

INCLUDES += \
	-Iinclude \
	${CPU_INCLUDES} \
	-Iplat/ \
	-Iplat/${CHIP_ARCH}/include/uart \
	-Iplat/${CHIP_ARCH}/include/usb \
	-Iplat/${CHIP_ARCH}/include \
	-Iplat/${CHIP_ARCH}/include/${BOOT_CPU} \
	-Ilib/utils \
	-Ilib/lzma \
	-Ilib/lz4 \
	-Ilib/crc \
	${STDLIB_INCLUDES} \
	${CRYPT_INCLUDES}

#BL_COMMON_SOURCES = \
	${CPU_SOURCES} \
	lib/tf_printf/tf_printf.c \
	plat/${CHIP_ARCH}/platform.c \
	plat/${CHIP_ARCH}/security/security.c \
	${STDLIB_SRCS} \
	${CRYPT_SOURCES}

#DECOMPRESSION_SOURCES = \
	lib/lzma/LzmaDec.c \
	lib/lz4/lz4_all.c \
	lib/lz4/xxhash.c

#BL2_SRCS = \
	${BL_COMMON_SOURCES} \
	plat/${CHIP_ARCH}/platform_device.c \
	plat/${CHIP_ARCH}/bl2/bl2_opt.c \
	lib/utils/decompress.c \
	plat/${CHIP_ARCH}/usb/cps_cvi.c  \
	plat/${CHIP_ARCH}/usb/usb_tty.c  \
	plat/${CHIP_ARCH}/usb/dwc2_udc_otg.c  \
	plat/${CHIP_ARCH}/usb/dwc2_udc_otg_xfer_dma.c  \
	plat/${CHIP_ARCH}/usb/cv_usb.c  \
	lib/crc/crc16.c \
	${DECOMPRESSION_SOURCES}

BL2_SOURCES = \
	${BL2_CPU_SOURCES} \
	${BL2_SRCS} \
	plat/${CHIP_ARCH}/bl2/bl2_main.c

#include plat/${CHIP_ARCH}/ddr/ddr.mk

BL2_LINKERFILE := plat/${CHIP_ARCH}/bl2/bl2.ld.S
BL2_RLS_OBJS := plat/${CHIP_ARCH}/bl2_objs/${PROJECT_FULLNAME}/bl2/*.o
