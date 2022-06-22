################################################################################
# \file main.mk
# \version 1.0
#
# \brief
# Defines the public facing build targets common to all recipes and includes
# the core makefiles.
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


################################################################################
# Paths
################################################################################

#
# Set the build location. Append app dir if CY_BUILD_LOCATION is defined
#
ifneq ($(CY_BUILD_LOCATION),)
CY_BUILD_LOC=$(CY_BUILD_LOCATION)/$(notdir $(CY_APP_LOCATION))
else
CY_BUILD_LOC=$(CY_APP_LOCATION)/build
endif

#
# Windows paths
#
ifeq ($(OS),Windows_NT)

#
# CygWin/MSYS
#
ifneq ($(CY_WHICH_CYGPATH),)
CY_INTERNAL_BUILD_LOC:=$(shell cygpath -m --absolute $(subst \,/,$(CY_BUILD_LOC)))
ifneq ($(CY_BUILD_LOCATION),)
CY_INTERNAL_BUILD_LOCATION:=$(shell cygpath -m --absolute $(subst \,/,$(CY_BUILD_LOCATION)))
endif
ifneq ($(CY_DEVICESUPPORT_PATH),)
CY_INTERNAL_DEVICESUPPORT_PATH:=$(shell cygpath -m --absolute $(subst \,/,$(CY_DEVICESUPPORT_PATH)))
endif

#
# Other Windows environments
#
else
CY_INTERNAL_BUILD_LOC:=$(subst \,/,$(CY_BUILD_LOC))
CY_INTERNAL_BUILD_LOCATION:=$(subst \,/,$(CY_BUILD_LOCATION))
CY_INTERNAL_DEVICESUPPORT_PATH:=$(abspath $(subst \,/,$(CY_DEVICESUPPORT_PATH)))
endif

#
# Linux and macOS paths
#
else
CY_INTERNAL_BUILD_LOC:=$(CY_BUILD_LOC)
CY_INTERNAL_BUILD_LOCATION:=$(CY_BUILD_LOCATION)
CY_INTERNAL_DEVICESUPPORT_PATH:=$(abspath $(CY_DEVICESUPPORT_PATH))
endif

#
# Build directories
#
CY_RECIPE_DIR=$(CY_INTERNAL_BUILD_LOC)
CY_BUILDTARGET_DIR=$(CY_RECIPE_DIR)/$(TARGET)
CY_CONFIG_DIR=$(CY_BUILDTARGET_DIR)/$(CONFIG)
CY_GENERATED_DIR=$(CY_BUILDTARGET_DIR)/generated

#
# Default toolchain locations
#
CY_COMPILER_GCC_ARM_DEFAULT_DIR=$(CY_COMPILER_DEFAULT_DIR)
CY_COMPILER_IAR_DEFAULT_DIR="C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.2/arm"
CY_COMPILER_ARM_DEFAULT_DIR="C:/Program Files/ARMCompiler6.11"
CY_COMPILER_A_Clang_DEFAULT_DIR=/Library/Developer/CommandLineTools/usr/lib/clang/10.0.0

#
# Toolchain locations
#
CY_COMPILER_GCC_ARM_DIR?=$(CY_COMPILER_GCC_ARM_DEFAULT_DIR)
CY_COMPILER_IAR_DIR?=$(CY_COMPILER_IAR_DEFAULT_DIR)
CY_COMPILER_ARM_DIR?=$(CY_COMPILER_ARM_DEFAULT_DIR)
CY_COMPILER_A_Clang_DIR?=$(CY_COMPILER_A_Clang_DEFAULT_DIR)


################################################################################
# User-facing make targets
################################################################################

CY_HELP_all=Same as build. i.e. Builds the application.
all: build

CY_HELP_getlibs=Clones the repositories, and checks out the identified commit.
getlibs:

CY_HELP_build=Builds the application.
build: app memcalc

CY_HELP_qbuild=Builds the application using the previous build's source list.
qbuild: app memcalc

CY_HELP_program=Builds the application and programs it to the target device.
program:

CY_HELP_qprogram=Programs a built application to the target device without rebuilding.
qprogram:

CY_HELP_debug=Builds and programs. Then launches a GDB server.
debug:

CY_HELP_qdebug=Skips the build and program step. Launches a GDB server.
qdebug:

CY_HELP_clean=Cleans the /build/<TARGET> directory.
clean: shared_libs
	rm -rf $(CY_BUILDTARGET_DIR)

# Note: Define the help target in BSP/recipe for custom help
CY_HELP_help=Prints the help documentation.
help: help_default

CY_HELP_open=Opens/launches a specified tool.
open:

CY_HELP_config=Runs the configurator on the target .modus file.
config:

CY_HELP_config_bt=Runs the bt-configurator on the target .cybt file.
config_bt:

CY_HELP_config_usbdev=Runs the usbdev-configurator on the target .cyusbdev file.
config_usbdev:


################################################################################
# Include make files
################################################################################

# Make a decision on including logic pertinent to builds.
# If it's not any of these targets, then it's an actual build.
CY_COMMENCE_BUILD=false
ifneq ($(findstring clean,$(MAKECMDGOALS)),clean)
ifneq ($(findstring qprogram,$(MAKECMDGOALS)),qprogram)
ifneq ($(findstring qdebug,$(MAKECMDGOALS)),qdebug)
ifneq ($(findstring erase,$(MAKECMDGOALS)),erase)
ifneq ($(findstring attach,$(MAKECMDGOALS)),attach)
ifneq ($(findstring eclipse,$(MAKECMDGOALS)),eclipse)
ifneq ($(findstring check,$(MAKECMDGOALS)),check)
ifneq ($(findstring get_env_info,$(MAKECMDGOALS)),get_env_info)
ifneq ($(findstring get_app_info,$(MAKECMDGOALS)),get_app_info)
ifneq ($(findstring help,$(MAKECMDGOALS)),help)
# Note: covers config config_bt and config_usbdev
ifneq ($(findstring config,$(MAKECMDGOALS)),config)
ifneq ($(findstring open,$(MAKECMDGOALS)),open)
CY_COMMENCE_BUILD=true
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif

ifeq ($(CY_COMMENCE_BUILD),true)
$(info )
$(info Initializing build: $(APPNAME)$(LIBNAME) $(CONFIG) $(TARGET) $(TOOLCHAIN))
ifeq ($(wildcard $(CY_INTERNAL_BASELIB_PATH)),)
$(info )
$(error Cannot find the base library. Run "make getlibs" and/or check\
that the library location is correct in the CY_BASELIB_PATH variable)
endif
endif

#
# Include utilities used by all make files
#
include $(CY_BASELIB_CORE_PATH)/make/core/utils.mk

#
# Include any extra makefiles defined by app
#
include $(CY_EXTRA_INCLUDES)

#
# Find the target and check that the device is valid
#
include $(CY_BASELIB_CORE_PATH)/make/core/target.mk
-include $(CY_INTERNAL_BASELIB_PATH)/make/udd/features.mk
include $(CY_INTERNAL_BASELIB_PATH)/make/recipe/defines.mk

#
# Check if the user-data is correct
#
ifneq ($(APPNAME),)
ifneq ($(LIBNAME),)
$(error An application cannot define both APPNAME and LIBNAME. Define one or the other)
endif
endif
ifneq ($(findstring -I,$(INCLUDES)),)
$(error INCLUDES must be directories without -I prepended)
endif
ifneq ($(findstring -D,$(DEFINES)),)
$(error DEFINES must be specified without -D prepended)
endif
ifneq ($(findstring -I,$(CFLAGS)),)
$(error Include paths must be specified in the INCLUDES variable instead\
of directly in CFLAGS. These must be directories without -I prepended)
endif
ifneq ($(findstring -D,$(CFLAGS)),)
$(error Defines must be specified in the DEFINES variable instead\
of directly in CFLAGS. These must be specified without -D prepended)
endif
ifneq ($(findstring -I,$(CXXFLAGS)),)
$(error Include paths must be specified in the INCLUDES variable instead\
of directly in CXXFLAGS. These must be directories without -I prepended)
endif
ifneq ($(findstring -D,$(CXXFLAGS)),)
$(error Defines must be specified in the DEFINES variable instead\
of directly in CXXFLAGS. These must be specified without -D prepended)
endif
ifneq ($(findstring -I,$(ASFLAGS)),)
$(error Include paths must be specified in the INCLUDES variable instead\
of directly in ASFLAGS. These must be directories without -I prepended)
endif
ifneq ($(findstring -D,$(ASFLAGS)),)
$(error Defines must be specified in the DEFINES variable instead\
of directly in ASFLAGS. These must be specified without -D prepended)
endif

#
# Choose local or default toolchain makefile
#
ifeq ($(TOOLCHAIN_MK_PATH),)
include $(CY_INTERNAL_BASELIB_PATH)/make/toolchains/$(TOOLCHAIN).mk
else
# Include the custom app-specific toolchain file
include $(TOOLCHAIN_MK_PATH)
endif

#
# Configurator-related routines
#
ifeq ($(CY_SKIP_CONFIGURATOR),)
include $(CY_BASELIB_CORE_PATH)/make/core/config.mk
endif

#
# Build-related routines
#
ifeq ($(CY_COMMENCE_BUILD),true)

ifneq ($(findstring qbuild,$(MAKECMDGOALS)),qbuild)
include $(CY_BASELIB_CORE_PATH)/make/core/search.mk
else
# Skip the auto-discovery and re-use the last build's source list
-include $(CY_CONFIG_DIR)/cyqbuild.mk
CY_QBUILD=$(shell if [ -f $(CY_CONFIG_DIR)/cyqbuild.mk ]; then echo "true"; fi;)
ifneq ($(CY_QBUILD),true)
$(info WARNING: Cannot find the auto-discovery make file. Run "make build" to generate it.)
endif
endif

include $(CY_INTERNAL_BASELIB_PATH)/make/recipe/recipe.mk

ifneq ($(findstring vscode,$(MAKECMDGOALS)),vscode)
include $(CY_BASELIB_CORE_PATH)/make/core/build.mk
endif

endif

#
# Optional recipe-specific program routine 
#
ifndef CY_BSP_PROGRAM
-include $(CY_INTERNAL_BASELIB_PATH)/make/recipe/program.mk
endif

#
# Launch tools
#
-include $(CY_INTERNAL_TOOLS)/make/tools.mk
include $(CY_BASELIB_CORE_PATH)/make/core/open.mk

#
# Help documentation
#
include $(CY_BASELIB_CORE_PATH)/make/core/help.mk

#
# Identify the phony targets
#
.PHONY: all build qbuild getlibs clean program quickprogram help
.PHONY: app memcalc
