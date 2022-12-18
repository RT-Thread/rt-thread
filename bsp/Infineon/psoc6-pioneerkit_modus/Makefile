################################################################################
# \file Makefile
# \version 1.0
#
# \brief
# Top-level application make file.
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


################################################################################
# Basic Configuration
################################################################################

# Target board/hardware
TARGET=CY8CKIT-062-BLE
# Name of application (used to derive name of final linked file).
APPNAME=mtb-example-psoc6-empty-app

# Name of toolchain to use. Options include:
#
# GCC_ARM -- GCC 7.2.1, provided with ModusToolbox IDE
# ARM     -- ARM Compiler (must be installed separately)
# IAR     -- IAR Compiler (must be installed separately)
#
# See also: CY_COMPILER_PATH below
TOOLCHAIN=GCC_ARM

# Default build configuration. Options include:
#
# Debug   -- build with minimal optimizations, focus on debugging.
# Release -- build with full optimizations
CONFIG=Debug

# If set to "true" or "1", display full command-lines when building.
VERBOSE=

# RT-Thread root directory
RTT_ROOT_DIR=../../../

################################################################################
# Advanced Configuration
################################################################################

# Enable optional code that is ordinarily disabled by default.
#
# Available components depend on the specific targeted hardware and firmware
# in use. In general, if you have
#
#    COMPONENTS=foo bar
#
# ... then code in directories named COMPONENT_foo and COMPONENT_bar will be
# added to the build
#
COMPONENTS=

# Like COMPONENTS, but disable optional code that was enabled by default.
DISABLE_COMPONENTS=

# By default the build system automatically looks in the Makefile's directory
# tree for source code and builds it. The SOURCES variable can be used to
# manually add source code to the build process from a location not searched
# by default, or otherwise not found by the build system.
SOURCES=$(wildcard $(RTT_ROOT_DIR)/libcpu/arm/cortex-m4/*.c) \
        $(wildcard $(RTT_ROOT_DIR)/libcpu/arm/common/*.c) \
        $(wildcard $(RTT_ROOT_DIR)/src/*.c) \
        $(wildcard $(RTT_ROOT_DIR)/components/drivers/src/*.c) \
        $(wildcard $(RTT_ROOT_DIR)/components/drivers/serial/*.c) \
        $(wildcard $(RTT_ROOT_DIR)/components/finsh/*.c)
ifeq ($(TOOLCHAIN),GCC_ARM)
 SOURCES+=$(RTT_ROOT_DIR)/libcpu/arm/cortex-m4/context_gcc.S
else ifeq ($(TOOLCHAIN),ARM)
 SOURCES+=$(RTT_ROOT_DIR)/libcpu/arm/cortex-m4/context_rvds.S
else
 SOURCES+=$(RTT_ROOT_DIR)/libcpu/arm/cortex-m4/context_iar.S
endif

# Like SOURCES, but for include directories. Value should be paths to
# directories (without a leading -I).
INCLUDES=$(RTT_ROOT_DIR)/include/ \
         $(RTT_ROOT_DIR)/components/finsh/ \
         $(RTT_ROOT_DIR)/components/drivers/include/

# Add additional defines to the build process (without a leading -D).
DEFINES=HAVE_SIGVAL HAVE_SIGEVENT HAVE_SIGINFO RT_USING_NEWLIBC

# Select softfp or hardfp floating point. Default is softfp.
VFP_SELECT=hardfp

# Additional / custom C compiler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
CFLAGS=

# Additional / custom C++ compiler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
CXXFLAGS=

# Additional / custom assembler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
ASFLAGS=-mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wa,-mimplicit-it=always

# Additional / custom linker flags.
LDFLAGS=

# Additional / custom libraries to link in to the application.
LDLIBS=

# Path to the linker script to use (if empty, use the default linker script).
LINKER_SCRIPT=

# Custom pre-build commands to run.
PREBUILD=

# Custom post-build commands to run.
POSTBUILD=


################################################################################
# Paths
################################################################################

# Relative path to the project directory (default is the Makefile's directory).
#
# This controls where automatic source code discovery looks for code.
CY_APP_PATH=

# Relative path to the "base" library. It provides the core makefile build
# infrastructure.
CY_BASELIB_PATH=libs/psoc6make

# Absolute path to the compiler's "bin" directory.
#
# The default depends on the selected TOOLCHAIN (GCC_ARM uses the ModusToolbox
# IDE provided compiler by default).
CY_COMPILER_PATH=


# Locate ModusToolbox IDE helper tools folders in default installation
# locations for Windows, Linux, and macOS.
CY_WIN_HOME=$(subst \,/,$(USERPROFILE))
CY_TOOLS_PATHS ?= $(wildcard \
    $(CY_WIN_HOME)/ModusToolbox/tools_* \
    $(HOME)/ModusToolbox/tools_* \
    /Applications/ModusToolbox/tools_*)

# If you install ModusToolbox IDE in a custom location, add the path to its
# "tools_X.Y" folder (where X and Y are the version number of the tools
# folder).
CY_TOOLS_PATHS+=

# Default to the newest installed tools folder, or the users override (if it's
# found).
CY_TOOLS_DIR=$(lastword $(sort $(wildcard $(CY_TOOLS_PATHS))))

ifeq ($(CY_TOOLS_DIR),)
$(error Unable to find any of the available CY_TOOLS_PATHS -- $(CY_TOOLS_PATHS))
endif

$(info Tools Directory: $(CY_TOOLS_DIR))

include $(CY_TOOLS_DIR)/make/start.mk
