################################################################################
# \file defines.mk
# \version 1.0
#
# \brief
# Defines, needed for the PSoC 6 build recipe.
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


#
# List the supported toolchains
#
CY_SUPPORTED_TOOLCHAINS=GCC_ARM IAR ARM A_Clang

#
# Define the default core
#
CORE?=CM4
CY_START_FLASH=0x10000000
CY_START_SRAM=0x08000000

CY_OPEN_bt_configurator_DEVICE=--device PSoC6 
CY_OPENOCD_CHIP_NAME=psoc6
CY_OPENOCD_SECOND_RESET_TYPE=run
CY_OPENOCD_OTHER_RUN_CMD=mon psoc6 reset_halt sysresetreq
CY_OPENOCD_OTHER_RUN_CMD_ECLIPSE=$(CY_OPENOCD_OTHER_RUN_CMD)\&\#13;\&\#10;

#
# Core specifics
#
ifeq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_M0P)))
ifeq ($(CORE),CM0P)
$(call CY_MACRO_ERROR,$(DEVICE) does not have a CM0+ core)
endif
CY_LINKERSCRIPT_SUFFIX=cm4
CY_OPENOCD_EXTRA_PORT_FLAG=
CY_OPENOCD_EXTRA_PORT_ECLIPSE=
CY_OPENOCD_CM0_DISABLE_FLAG=set ENABLE_CM0 0
CY_OPENOCD_CM0_DISABLE_ECLIPSE=-c \&quot;$(CY_OPENOCD_CM0_DISABLE_FLAG)\&quot;\&\#13;\&\#10;
else
ifeq ($(CORE),CM0P)
CY_LINKERSCRIPT_SUFFIX=cm0plus
else
CY_LINKERSCRIPT_SUFFIX=cm4_dual
CY_OPENOCD_EXTRA_PORT_FLAG=gdb_port 3332
CY_OPENOCD_EXTRA_PORT_ECLIPSE=-c \&quot;$(CY_OPENOCD_EXTRA_PORT_FLAG)\&quot;\&\#13;\&\#10;
CY_OPENOCD_CM0_DISABLE_FLAG=
CY_OPENOCD_CM0_DISABLE_ECLIPSE=
endif
endif

#
# Architecure specifics
#
ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_DIE_PSOC6ABLE2)))

CY_PSOC_ARCH=psoc6_01
CY_PSOC_DIE_NAME=PSoC6ABLE2
CY_OPENOCD_DEVICE_CFG=psoc6.cfg
CY_JLINK_DEVICE_CFG_PROGRAM=CY8C6xx7_CM0p_sect256KB_tm
CY_JLINK_DEVICE_CFG_DEBUG=CY8C6xx7_CM4_sect256KB
ifeq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_M0P)))
CY_JLINK_DEVICE_CFG_PROGRAM=CY8C6xx6_CM4_sect256KB
CY_JLINK_DEVICE_CFG_DEBUG=CY8C6xx6_CM4_sect256KB
endif
ifneq (,$(findstring CYB0,$(DEVICE)))
CY_PSOC_ARCH=psoc6_secure
CY_PSOC_DIE_NAME=PSoC6ABLE2Secure
CY_OPENOCD_CHIP_NAME=psoc64
CY_OPENOCD_DEVICE_CFG=psoc6_secure.cfg
CY_OPENOCD_CM0_DISABLE_FLAG=set TARGET_AP cm4_ap
CY_OPENOCD_EXTRA_PORT_FLAG=
CY_OPENOCD_CM0_DISABLE_ECLIPSE=-c \&quot;$(CY_OPENOCD_CM0_DISABLE_FLAG)\&quot;\&\#13;\&\#10;
CY_OPENOCD_EXTRA_PORT_ECLIPSE=
CY_OPENOCD_SECOND_RESET_TYPE=init
CY_OPENOCD_OTHER_RUN_CMD=
CY_OPENOCD_OTHER_RUN_CMD_ECLIPSE=
CY_OPENOCD_SMIF_DISABLE=set DISABLE_SMIF 1
CY_OPENOCD_SMIF_DISABLE_ECLIPSE=-c \&quot;$(CY_OPENOCD_SMIF_DISABLE)\&quot;\&\#13;\&\#10;
endif

else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_DIE_PSOC6A2M)))

CY_PSOC_ARCH=psoc6_02
CY_PSOC_DIE_NAME=PSoC6A2M
CY_OPENOCD_DEVICE_CFG=psoc6_2m.cfg
CY_JLINK_DEVICE_CFG_PROGRAM=CY8C6xxA_CM0p_sect256KB_tm
CY_JLINK_DEVICE_CFG_DEBUG=CY8C6xxA_CM4_sect256KB
ifneq (,$(findstring CYB0,$(DEVICE)))
CY_PSOC_ARCH=psoc6_2m_secure
CY_PSOC_DIE_NAME=PSoC6A2MSecure
CY_OPENOCD_CHIP_NAME=psoc64_2m
CY_OPENOCD_DEVICE_CFG=psoc6_2m_secure.cfg
CY_OPENOCD_CM0_DISABLE_FLAG=set TARGET_AP cm4_ap
CY_OPENOCD_EXTRA_PORT_FLAG=
CY_OPENOCD_CM0_DISABLE_ECLIPSE=-c \&quot;$(CY_OPENOCD_CM0_DISABLE_FLAG)\&quot;\&\#13;\&\#10;
CY_OPENOCD_EXTRA_PORT_ECLIPSE=
CY_OPENOCD_SECOND_RESET_TYPE=init
CY_OPENOCD_OTHER_RUN_CMD=
CY_OPENOCD_OTHER_RUN_CMD_ECLIPSE=
CY_OPENOCD_SMIF_DISABLE=set DISABLE_SMIF 1
CY_OPENOCD_SMIF_DISABLE_ECLIPSE=-c \&quot;$(CY_OPENOCD_SMIF_DISABLE)\&quot;\&\#13;\&\#10;
endif

else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_DIE_PSOC6A512K)))

CY_PSOC_ARCH=psoc6_03
CY_PSOC_DIE_NAME=PSoC6A512K
CY_OPENOCD_DEVICE_CFG=psoc6_512k.cfg
CY_JLINK_DEVICE_CFG_PROGRAM=CY8C6xx5_CM0p_sect256KB_tm
CY_JLINK_DEVICE_CFG_DEBUG=CY8C6xx5_CM4_sect256KB

else
$(call CY_MACRO_ERROR,Incorrect part number $(DEVICE). Check DEVICE variable.)
endif

#
# Flash memory specifics
#
ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FLASH_KB_512)))
CY_MEMORY_FLASH=524288
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FLASH_KB_832)))
CY_MEMORY_FLASH=850944
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FLASH_KB_1024)))
CY_MEMORY_FLASH=1048576
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FLASH_KB_1856)))
CY_MEMORY_FLASH=1899520
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FLASH_KB_2048)))
CY_MEMORY_FLASH=2097152
else
$(call CY_MACRO_ERROR,No Flash memory size defined for $(DEVICE))
endif

#
# SRAM memory specifics
#
ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_SRAM_KB_128)))
CY_MEMORY_SRAM=129024
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_SRAM_KB_256)))
CY_MEMORY_SRAM=260096
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_SRAM_KB_288)))
CY_MEMORY_SRAM=292864
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_SRAM_KB_512)))
CY_MEMORY_SRAM=522240
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_SRAM_KB_1024)))
CY_MEMORY_SRAM=1046528
else
$(call CY_MACRO_ERROR,No SRAM memory size defined for $(DEVICE))
endif

#
# linker scripts
#

# Secure parts
ifneq (,$(findstring CYB06,$(DEVICE)))

ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_DIE_PSOC6ABLE2)))
ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FLASH_KB_832)))
CY_LINKER_SCRIPT_NAME=cyb06xx7
endif
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_DIE_PSOC6A2M)))
ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FLASH_KB_1856)))
CY_LINKER_SCRIPT_NAME=cyb06xxa
endif
endif

# Non-secure part
else

ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_DIE_PSOC6A512K)))
ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FLASH_KB_512)))
CY_LINKER_SCRIPT_NAME=cy8c6xx5
endif
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_DIE_PSOC6ABLE2)))
ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FLASH_KB_512)))
CY_LINKER_SCRIPT_NAME=cy8c6xx6
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FLASH_KB_1024)))
CY_LINKER_SCRIPT_NAME=cy8c6xx7
endif
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_DIE_PSOC6A2M)))
ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FLASH_KB_1024)))
CY_LINKER_SCRIPT_NAME=cy8c6xx8
else ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FLASH_KB_2048)))
CY_LINKER_SCRIPT_NAME=cy8c6xxa
endif
endif

endif

ifeq ($(CY_LINKER_SCRIPT_NAME),)
$(call CY_MACRO_ERROR,Could not resolve device series for linker script)
endif

#
# Paths used in program/debug
#
ifeq ($(CY_DEVICESUPPORT_PATH),)
CY_OPENOCD_SVD_PATH?=
else
CY_OPENOCD_SVD_PATH?=
endif
CY_OPENOCD_QSPI_CFG_PATH=$(CY_TARGET_DIR)/COMPONENT_BSP_DESIGN_MODUS/GeneratedSource

#
# Set the output file paths
#
ifneq ($(CY_BUILD_LOCATION),)
CY_SYM_FILE?=$(CY_INTERNAL_BUILD_LOCATION)/$(APPNAME)/$(TARGET)/$(CONFIG)/$(APPNAME).elf
CY_PROG_FILE?=$(CY_INTERNAL_BUILD_LOCATION)/$(APPNAME)/$(TARGET)/$(CONFIG)/$(APPNAME).hex
else
CY_SYM_FILE?=\$$\{cy_prj_path\}/$(notdir $(CY_INTERNAL_BUILD_LOC))/$(TARGET)/$(CONFIG)/$(APPNAME).elf
CY_PROG_FILE?=\$$\{cy_prj_path\}/$(notdir $(CY_INTERNAL_BUILD_LOC))/$(TARGET)/$(CONFIG)/$(APPNAME).hex
endif

#
# IDE specifics
#
ifneq (,$(findstring CYB0,$(DEVICE)))
CY_ECLIPSE_TEMPLATES_WILDCARD=*KitProg3*
endif

CY_VSCODE_ARGS="s|&&RELEASETARGET&&|build/$(TARGET)/Release/$(APPNAME).elf|g;"\
				"s|&&DEBUGTARGET&&|build/$(TARGET)/Debug/$(APPNAME).elf|g;"\
				"s|&&PSOCFAMILY&&|$(CY_PSOC_ARCH)|g;"\
				"s|&&MODUSSHELL&&|$(CY_MODUS_SHELL_DIR)|g;"\
				"s|&&OPENOCDFILE&&|$(CY_OPENOCD_DEVICE_CFG)|g;"\
				"s|&&SVDFILENAME&&|$(CY_OPENOCD_SVD_PATH)|g;"\
				"s|&&MODUSTOOLCHAIN&&|$(CY_COMPILER_DIR)|g;"\
				"s|&&MODUSTOOLCHAINVERSION&&|$(notdir $(CY_COMPILER_DIR))|g;"\
				"s|&&MODUSOPENCOD&&|$(CY_OPENOCD_DIR)|g;"\
				"s|&&MODUSLIBMANAGER&&|$(CY_LIBRARY_MANAGER_DIR)|g;"\

CY_ECLIPSE_ARGS="s|&&CY_OPENOCD_CFG&&|$(CY_OPENOCD_DEVICE_CFG)|;"\
				"s|&&CY_OPENOCD_CHIP&&|$(CY_OPENOCD_CHIP_NAME)|;"\
				"s|&&CY_OPENOCD_SECOND_RESET&&|$(CY_OPENOCD_SECOND_RESET_TYPE)|;"\
				"s|&&CY_OPENOCD_OTHER_RUN_CMD&&|$(CY_OPENOCD_OTHER_RUN_CMD_ECLIPSE)|;"\
				"s|&&CY_JLINK_CFG_PROGRAM&&|$(CY_JLINK_DEVICE_CFG_PROGRAM)|;"\
				"s|&&CY_JLINK_CFG_DEBUG&&|$(CY_JLINK_DEVICE_CFG_DEBUG)|;"\
				"s|&&CY_OPENOCD_PORT_SELECT&&|$(CY_OPENOCD_EXTRA_PORT_ECLIPSE)|;"\
				"s|&&CY_OPENOCD_CM0_FLAG&&|$(CY_OPENOCD_CM0_DISABLE_ECLIPSE)|;"\
				"s|&&CY_OPENOCD_SMIF_DISABLE&&|$(CY_OPENOCD_SMIF_DISABLE_ECLIPSE)|;"\
				"s|&&CY_APPNAME&&|$(CY_IDE_PRJNAME)|;"\
				"s|&&CY_CONFIG&&|$(CONFIG)|;"\
				"s|&&CY_QSPI_CFG_PATH&&|$(CY_OPENOCD_QSPI_CFG_PATH)|;"\
				"s|&&CY_SVD_PATH&&|$(CY_OPENOCD_SVD_PATH)|;"\
				"s|&&CY_SYM_FILE&&|$(CY_SYM_FILE)|;"\
				"s|&&CY_PROG_FILE&&|$(CY_PROG_FILE)|;"

#
# Tools specifics
#
ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_CAPSENSE)))
CY_SUPPORTED_TOOL_TYPES+=capsense-configurator capsense-tuner
endif
ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_BLE)))
CY_SUPPORTED_TOOL_TYPES+=bt-configurator
endif
ifneq (,$(findstring $(DEVICE),$(CY_DEVICES_WITH_FS_USB)))
CY_SUPPORTED_TOOL_TYPES+=usbdev-configurator
endif
CY_SUPPORTED_TOOL_TYPES+=\
	device-configurator\
	qspi-configurator\
	seglcd-configurator\
	smartio-configurator\
	cype-tool\
	dfuh-tool

# PSoC 6 smartio also uses the .modus extension
modus_DEFAULT_TYPE+=device-configurator smartio-configurator

# PSoC 6 capsense-tuner shares its existence with capsense-configurator
CY_OPEN_NEWCFG_XML_TYPES+=capsense-tuner
