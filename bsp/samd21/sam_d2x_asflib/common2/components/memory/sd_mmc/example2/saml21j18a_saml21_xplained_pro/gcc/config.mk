#
# Copyright (c) 2011 Atmel Corporation. All rights reserved.
#
# \asf_license_start
#
# \page License
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. The name of Atmel may not be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# 4. This software may only be redistributed and used in connection with an
#    Atmel microcontroller product.
#
# THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# \asf_license_stop
#

# Path to top level ASF directory relative to this project directory.
PRJ_PATH = ../../../../../../..

# Target CPU architecture: cortex-m3, cortex-m4
ARCH = cortex-m0plus

# Target part: none, sam3n4 or sam4l4aa
PART = saml21j18a

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET_FLASH = sd_mmc_example2_flash.elf
TARGET_SRAM = sd_mmc_example2_sram.elf

# List of C source files.
CSRCS = \
       common/services/storage/ctrl_access/ctrl_access.c  \
       common/utils/interrupt/interrupt_sam_nvic.c        \
       common2/components/memory/sd_mmc/example2/example.c \
       common2/components/memory/sd_mmc/sd_mmc.c          \
       common2/components/memory/sd_mmc/sd_mmc_mem.c      \
       common2/components/memory/sd_mmc/sd_mmc_spi.c      \
       common2/services/delay/sam0/cycle_counter.c        \
       sam0/boards/saml21_xplained_pro/board_init.c       \
       sam0/drivers/port/port.c                           \
       sam0/drivers/rtc/rtc_sam_l_c/rtc_calendar.c        \
       sam0/drivers/sercom/sercom.c                       \
       sam0/drivers/sercom/sercom_interrupt.c             \
       sam0/drivers/sercom/spi/spi.c                      \
       sam0/drivers/sercom/spi/spi_interrupt.c            \
       sam0/drivers/sercom/usart/usart.c                  \
       sam0/drivers/sercom/usart/usart_interrupt.c        \
       sam0/drivers/system/clock/clock_saml21/clock.c     \
       sam0/drivers/system/clock/clock_saml21/gclk.c      \
       sam0/drivers/system/interrupt/system_interrupt.c   \
       sam0/drivers/system/pinmux/pinmux.c                \
       sam0/drivers/system/system.c                       \
       sam0/utils/cmsis/saml21/source/gcc/startup_saml21.c \
       sam0/utils/cmsis/saml21/source/system_saml21.c     \
       sam0/utils/stdio/read.c                            \
       sam0/utils/stdio/write.c                           \
       sam0/utils/syscalls/gcc/syscalls.c                 \
       thirdparty/fatfs/fatfs-port-r0.09/diskio.c         \
       thirdparty/fatfs/fatfs-port-r0.09/sam0/fattime_rtc.c \
       thirdparty/fatfs/fatfs-r0.09/src/ff.c              \
       thirdparty/fatfs/fatfs-r0.09/src/option/ccsbcs.c

# List of assembler source files.
ASSRCS = 

# List of include paths.
INC_PATH = \
       common/boards                                      \
       common/services/serial                             \
       common/services/storage/ctrl_access                \
       common/utils                                       \
       common2/components/memory/sd_mmc                   \
       common2/components/memory/sd_mmc/example2          \
       common2/components/memory/sd_mmc/example2/saml21j18a_saml21_xplained_pro \
       common2/services/delay                             \
       common2/services/delay/sam0                        \
       sam0/boards                                        \
       sam0/boards/saml21_xplained_pro                    \
       sam0/drivers/port                                  \
       sam0/drivers/rtc                                   \
       sam0/drivers/rtc/rtc_sam_l_c                       \
       sam0/drivers/sercom                                \
       sam0/drivers/sercom/spi                            \
       sam0/drivers/sercom/usart                          \
       sam0/drivers/system                                \
       sam0/drivers/system/clock                          \
       sam0/drivers/system/clock/clock_saml21             \
       sam0/drivers/system/interrupt                      \
       sam0/drivers/system/interrupt/system_interrupt_saml21 \
       sam0/drivers/system/pinmux                         \
       sam0/drivers/system/power                          \
       sam0/drivers/system/power/power_sam_l              \
       sam0/drivers/system/reset                          \
       sam0/drivers/system/reset/reset_sam_l              \
       sam0/utils                                         \
       sam0/utils/cmsis/saml21/include                    \
       sam0/utils/cmsis/saml21/source                     \
       sam0/utils/header_files                            \
       sam0/utils/preprocessor                            \
       sam0/utils/stdio/stdio_serial                      \
       thirdparty/CMSIS/Include                           \
       thirdparty/CMSIS/Lib/GCC                           \
       thirdparty/fatfs/fatfs-port-r0.09/sam0             \
       thirdparty/fatfs/fatfs-r0.09/src \
       common2/components/memory/sd_mmc/example2/saml21j18a_saml21_xplained_pro/gcc

# Additional search paths for libraries.
LIB_PATH =  \
       thirdparty/CMSIS/Lib/GCC                          

# List of libraries to use during linking.
LIBS =  \
       arm_cortexM0l_math                                

# Path relative to top level directory pointing to a linker script.
LINKER_SCRIPT_FLASH = sam0/utils/linker_scripts/saml21/gcc/saml21j18a_flash.ld
LINKER_SCRIPT_SRAM  = sam0/utils/linker_scripts/saml21/gcc/saml21j18a_sram.ld

# Path relative to top level directory pointing to a linker script.
DEBUG_SCRIPT_FLASH = sam0/boards/saml21_xplained_pro/debug_scripts/gcc/saml21_xplained_pro_flash.gdb
DEBUG_SCRIPT_SRAM  = sam0/boards/saml21_xplained_pro/debug_scripts/gcc/saml21_xplained_pro_sram.gdb

# Project type parameter: all, sram or flash
PROJECT_TYPE        = flash

# Additional options for debugging. By default the common Makefile.in will
# add -g3.
DBGFLAGS = 

# Application optimization used during compilation and linking:
# -O0, -O1, -O2, -O3 or -Os
OPTIMIZATION = -O1

# Extra flags to use when archiving.
ARFLAGS = 

# Extra flags to use when assembling.
ASFLAGS = 

# Extra flags to use when compiling.
CFLAGS = 

# Extra flags to use when preprocessing.
#
# Preprocessor symbol definitions
#   To add a definition use the format "-D name[=definition]".
#   To cancel a definition use the format "-U name".
#
# The most relevant symbols to define for the preprocessor are:
#   BOARD      Target board in use, see boards/board.h for a list.
#   EXT_BOARD  Optional extension board in use, see boards/board.h for a list.
CPPFLAGS = \
       -D ARM_MATH_CM0PLUS=true                           \
       -D BOARD=SAML21_XPLAINED_PRO                       \
       -D CYCLE_MODE                                      \
       -D RTC_CALENDAR_ASYNC=false                        \
       -D SD_MMC_ENABLE                                   \
       -D SPI_CALLBACK_MODE=true                          \
       -D USART_CALLBACK_MODE=true                        \
       -D __SAML21J18A__

# Extra flags to use when linking
LDFLAGS = \
                                                          \
       -Wl,--defsym,STACK_SIZE=0x2000                     \
       -Wl,--defsym,__stack_size__=0x2000

# Pre- and post-build commands
PREBUILD_CMD = 
POSTBUILD_CMD = 