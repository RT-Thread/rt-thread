################################################################################
# \file program.mk
# \version 1.0
#
# \brief
# This make file is called recursively and is used to build the
# resoures file system. It is expected to be run from the example directory.
#
################################################################################
# \copyright
# Copyright 2018-2019 Cypress Semiconductor Corporation
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################

ifeq ($(WHICHFILE),true)
$(info Processing $(lastword $(MAKEFILE_LIST)))
endif


CY_GDB_CLIENT=$(CY_COMPILER_DIR)/bin/arm-none-eabi-gdb
CY_GDB_ARGS=$(CY_INTERNAL_BASELIB_PATH)/make/scripts/gdbinit

ifeq ($(TOOLCHAIN),A_Clang)
CY_OPENOCD_PROGRAM_IMG=$(CY_CONFIG_DIR)/$(APPNAME).bin $(TOOLCHAIN_VECT_BASE_CM4)
else
CY_OPENOCD_SYMBOL_IMG=$(CY_CONFIG_DIR)/$(APPNAME).elf
CY_OPENOCD_PROGRAM_IMG=$(CY_CONFIG_DIR)/$(APPNAME).hex
endif

CY_OPENOCD_SCRIPTS=-s $(CY_OPENOCD_DIR)/scripts
CY_OPENOCD_QSPI=-s $(CY_OPENOCD_QSPI_CFG_PATH)
CY_OPENOCD_INTERFACE=source [find interface/kitprog3.cfg];
CY_OPENOCD_TARGET=source [find target/$(CY_OPENOCD_DEVICE_CFG)];
ifeq (,$(findstring CYB0,$(DEVICE)))
CY_OPENOCD_CUSTOM_COMMAND?=psoc6 allow_efuse_program off;
else
CY_GDB_ARGS=$(CY_INTERNAL_BASELIB_PATH)/make/scripts/gdbinit_secure
endif

CY_OPENOCD_ERASE=init; reset init; psoc6 sflash_restrictions 1; erase_all; exit;
CY_OPENOCD_PROGRAM=psoc6 sflash_restrictions 1; program $(CY_OPENOCD_PROGRAM_IMG) verify reset exit;
CY_OPENOCD_DEBUG=$(CY_OPENOCD_CHIP_NAME).cpu.cm4 configure -rtos auto -rtos-wipe-on-reset-halt 1; $(CY_OPENOCD_EXTRA_PORT_FLAG); init; reset init;

CY_OPENOCD_ERASE_ARGS=$(CY_OPENOCD_SCRIPTS) -c \
					"$(CY_OPENOCD_INTERFACE) $(CY_OPENOCD_CM0_DISABLE_FLAG); $(CY_OPENOCD_SMIF_DISABLE); $(CY_OPENOCD_TARGET) $(CY_OPENOCD_CUSTOM_COMMAND) $(CY_OPENOCD_ERASE)"
CY_OPENOCD_PROGRAM_ARGS=$(CY_OPENOCD_SCRIPTS) $(CY_OPENOCD_QSPI) -c \
					"$(CY_OPENOCD_INTERFACE) $(CY_OPENOCD_CM0_DISABLE_FLAG); $(CY_OPENOCD_TARGET) $(CY_OPENOCD_CUSTOM_COMMAND) $(CY_OPENOCD_PROGRAM)"
CY_OPENOCD_DEBUG_ARGS=$(CY_OPENOCD_SCRIPTS) $(CY_OPENOCD_QSPI) -c \
					"$(CY_OPENOCD_INTERFACE) $(CY_OPENOCD_CM0_DISABLE_FLAG); $(CY_OPENOCD_TARGET) $(CY_OPENOCD_CUSTOM_COMMAND) $(CY_OPENOCD_DEBUG)"

erase:
	@echo;\
	echo "Erasing target device... ";\
	$(CY_OPENOCD_DIR)/bin/openocd $(CY_OPENOCD_ERASE_ARGS)

program: build qprogram

qprogram: memcalc
ifeq ($(LIBNAME),)
	@echo;\
	echo "Programming target device... ";\
	$(CY_OPENOCD_DIR)/bin/openocd $(CY_OPENOCD_PROGRAM_ARGS)
else
	@echo "Library application detected. Skip programming... ";\
	echo
endif

debug: program qdebug

qdebug: qprogram
ifeq ($(LIBNAME),)
	@echo;\
	echo ==============================================================================;\
	echo "Instruction:";\
	echo "Open a separate shell and run the attach target (make attach)";\
	echo "to start the GDB client. Then use the GDB commands to debug.";\
	echo ==============================================================================;\
	echo;\
	echo "Opening GDB port ... ";\
	$(CY_OPENOCD_DIR)/bin/openocd $(CY_OPENOCD_DEBUG_ARGS)
else
	@echo "Library application detected. Skip debug... ";\
	echo
endif

attach:
	@echo;\
	echo "Starting GDB Client... ";\
	$(CY_GDB_CLIENT) $(CY_OPENOCD_SYMBOL_IMG) -x $(CY_GDB_ARGS)


.PHONY: erase program qprogram debug qdebug attach
