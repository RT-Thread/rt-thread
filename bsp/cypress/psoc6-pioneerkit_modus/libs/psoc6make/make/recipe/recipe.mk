################################################################################
# \file recipe.mk
# \version 1.0
#
# \brief
# Set up a set of defines, includes, software components, linker script, 
# Pre and Post build steps and call a macro to create a specific ELF file.
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
# linker script construction
#
ifeq ($(LINKER_SCRIPT),)
LINKER_SCRIPT=$(CY_TARGET_DIR)/linker/TOOLCHAIN_$(TOOLCHAIN)/$(CY_LINKER_SCRIPT_NAME)_$(CY_LINKERSCRIPT_SUFFIX).$(CY_TOOLCHAIN_SUFFIX_LS)
endif

ifeq ($(shell if [ -f $(LINKER_SCRIPT) ]; then echo 1; else echo 0; fi;),0)
$(error The specified linker script could not be found at $(LINKER_SCRIPT))
endif

ifeq ($(TOOLCHAIN),A_Clang)
include $(LINKER_SCRIPT)
else
CY_RECIPE_LSFLAG=$(CY_TOOLCHAIN_LSFLAGS)$(LINKER_SCRIPT)
endif

#
# Flags construction
#
CY_RECIPE_CFLAGS?=\
	$(CFLAGS)\
	$(CY_TOOLCHAIN_CFLAGS)

CY_RECIPE_CXXFLAGS?=\
	$(CXXFLAGS)\
	$(CY_TOOLCHAIN_CXXFLAGS)

CY_RECIPE_ASFLAGS?=\
	$(ASFLAGS)\
	$(CY_TOOLCHAIN_ASFLAGS)

CY_RECIPE_ARFLAGS?=\
	$(CY_TOOLCHAIN_ARFLAGS)
		
CY_RECIPE_LDFLAGS?=\
	$(LDFLAGS)\
	$(CY_TOOLCHAIN_LDFLAGS)\
	$(CY_RECIPE_LSFLAG)

#
# Defines construction
#
ifneq ($(DEFINES),)
CY_RECIPE_USER_DEFINES=$(addprefix -D,$(DEFINES))
endif
ifneq ($(LIBNAME),)
CY_RECIPE_USER_NAME=-DCY_LIBNAME_$(subst -,_,$(LIBNAME))
else
CY_RECIPE_USER_NAME=-DCY_APPNAME_$(subst -,_,$(APPNAME))
endif

CY_RECIPE_DEFINES=\
	$(CY_RECIPE_USER_DEFINES)\
	$(CY_RECIPE_USER_NAME)\
	-D$(subst -,_,$(DEVICE))\
	-DCY_TARGET_DEVICE=$(subst -,_,$(DEVICE))\
	-DTARGET_$(subst -,_,$(TARGET))\
	-DCY_TARGET_BOARD=$(subst -,_,$(TARGET))\
	$(foreach feature,$(CY_COMPONENT_LIST),-DCOMPONENT_$(subst -,_,$(feature)))\
	$(CY_TOOLCHAIN_DEBUG_FLAG)\
	$(CY_TOOLCHAIN_DEFINES)

#
# Includes construction
#
CY_RECIPE_INCLUDES=\
	$(addprefix -I,$(INCLUDES))\
	$(addprefix -I,$(CY_SEARCH_APP_INCLUDES))\
	$(addprefix -I,$(CY_TOOLCHAIN_INCLUDES))

#
# Sources construction
#
CY_RECIPE_SOURCE=$(CY_SEARCH_APP_SOURCE)

#
# Libraries construction
#
CY_RECIPE_LIBS=$(LDLIBS) $(CY_SEARCH_APP_LIBS)

#
# Generate source step
#
ifneq ($(CY_SEARCH_RESOURCE_FILES),)
CY_RECIPE_RESOURCE_FILES=$(CY_SEARCH_RESOURCE_FILES)
CY_RECIPE_GENERATED_FLAG=TRUE

# Define the generated source file. Use := for better performance
CY_RECIPE_GENERATED:=$(addprefix $(CY_GENERATED_DIR)/,$(addsuffix .$(CY_TOOLCHAIN_SUFFIX_C),\
					$(basename $(notdir $(subst .,_,$(CY_SEARCH_RESOURCE_FILES))))))

CY_RECIPE_GENSRC=\
	bash --norc --noprofile\
	$(CY_INTERNAL_BASELIB_PATH)/make/scripts/genresources.bash\
	$(CY_INTERNAL_BASELIB_PATH)/make/scripts\
	$(CY_GENERATED_DIR)/resources.cyrsc\
	$(CY_INTERNAL_APP_PATH)\
	$(CY_GENERATED_DIR)\
	"MEM"
endif

#
# Prebuild step
#
CY_RECIPE_PREBUILD?=

#
# Postbuild step
#
ifeq ($(LIBNAME),)

ifeq ($(TOOLCHAIN),A_Clang)
CY_RECIPE_POSTBUILD?=\
	$(CY_TOOLCHAIN_M2BIN)\
	--verbose --vect $(VECT_BASE_CM4) --text $(TEXT_BASE_CM4) --data $(RAM_BASE_CM4) --size $(TEXT_SIZE_CM4)\
	$(CY_CONFIG_DIR)/$(APPNAME).mach_o\
	$(CY_CONFIG_DIR)/$(APPNAME).bin

else ifeq ($(TOOLCHAIN),ARM)
ifeq ($(CY_COMPILER_PATH),)
CY_RECIPE_POSTBUILD?=$(CY_COMPILER_ARM_DIR)/bin/fromelf --output $(CY_CONFIG_DIR)/$(APPNAME).hex --i32combined $(CY_CONFIG_DIR)/$(APPNAME).elf
else
CY_RECIPE_POSTBUILD?=$(CY_COMPILER_PATH)/bin/fromelf --output $(CY_CONFIG_DIR)/$(APPNAME).hex --i32combined $(CY_CONFIG_DIR)/$(APPNAME).elf
endif

else ifeq ($(TOOLCHAIN),IAR)
CY_RECIPE_POSTBUILD?=$(CY_COMPILER_GCC_ARM_DIR)/bin/arm-none-eabi-objcopy -O ihex $(CY_CONFIG_DIR)/$(APPNAME).elf $(CY_CONFIG_DIR)/$(APPNAME).hex

else ifeq ($(TOOLCHAIN),GCC_ARM)
ifeq ($(CY_COMPILER_PATH),)
CY_RECIPE_POSTBUILD?=$(CY_COMPILER_GCC_ARM_DIR)/bin/arm-none-eabi-objcopy -O ihex $(CY_CONFIG_DIR)/$(APPNAME).elf $(CY_CONFIG_DIR)/$(APPNAME).hex
else
CY_RECIPE_POSTBUILD?=$(CY_COMPILER_PATH)/bin/arm-none-eabi-objcopy -O ihex $(CY_CONFIG_DIR)/$(APPNAME).elf $(CY_CONFIG_DIR)/$(APPNAME).hex
endif
endif

endif

################################################################################
# Memory Consumption
################################################################################

ifeq ($(TOOLCHAIN),A_Clang)
CY_GEN_READELF=
CY_MEMORY_CALC=
else
CY_GEN_READELF=$(CY_COMPILER_DIR)/bin/arm-none-eabi-readelf -Sl $(CY_CONFIG_DIR)/$(APPNAME).elf > $(CY_CONFIG_DIR)/$(APPNAME).readelf
CY_MEM_CALC=\
	bash --norc --noprofile\
	$(CY_INTERNAL_BASELIB_PATH)/make/scripts/memcalc.bash\
	$(CY_CONFIG_DIR)/$(APPNAME).readelf\
	$(CY_MEMORY_FLASH)\
	$(CY_MEMORY_SRAM)\
	$(CY_START_FLASH)\
	$(CY_START_SRAM)
endif

memcalc: app
ifneq ($(LIBNAME),)
else
	@echo Calculating memory consumption: $(DEVICE) $(TOOLCHAIN) $(CY_TOOLCHAIN_OPTIMIZATION)
	@echo
	$(CY_NOISE)$(CY_GEN_READELF)
	$(CY_NOISE)$(CY_MEM_CALC)
endif

#
# Identify the phony targets
#
.PHONY: memcalc
