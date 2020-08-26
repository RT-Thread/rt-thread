############################################################################### 
# \file ARM.mk
# \version 1.0
#
# \brief
# ARM Compiler (Clang) toolchain configuration.
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
# The base path to the ARM Compiler (Clang) cross compilation executables
#
ifeq ($(CY_COMPILER_PATH),)
CY_CROSSPATH=$(CY_COMPILER_ARM_DIR)/bin
else
CY_CROSSPATH=$(CY_COMPILER_PATH)/bin
endif

#
# Build tools
#
CC=$(CY_CROSSPATH)/armclang
CXX=$(CC)
AS=$(CY_CROSSPATH)/armasm
AR=$(CY_CROSSPATH)/armar
LD=$(CY_CROSSPATH)/armlink

#
# DEBUG/NDEBUG selection
#
ifeq ($(CONFIG),Debug)
CY_TOOLCHAIN_DEBUG_FLAG=-DDEBUG
CY_TOOLCHAIN_OPTIMIZATION=-O1
else 
ifeq ($(CONFIG),Release)
CY_TOOLCHAIN_DEBUG_FLAG=-DNDEBUG
CY_TOOLCHAIN_OPTIMIZATION=-Oz
else
CY_TOOLCHAIN_DEBUG_FLAG=
CY_TOOLCHAIN_OPTIMIZATION=
endif
endif

#
# Flags common to compile and link
#
CY_TOOLCHAIN_COMMON_FLAGS=--target=arm-arm-none-eabi

#
# CPU core specifics
#
ifeq ($(CORE),CM0P)
CY_TOOLCHAIN_CFLAGS_CORE=-mcpu=cortex-m0plus
CY_TOOLCHAIN_FLAGS_CORE=--cpu=Cortex-M0plus
CY_TOOLCHAIN_VFP_FLAGS=
else
CY_TOOLCHAIN_CFLAGS_CORE=-mcpu=cortex-m4
CY_TOOLCHAIN_FLAGS_CORE=--cpu=Cortex-M4
ifeq ($(VFP_SELECT),hardfp)
CY_TOOLCHAIN_VFP_CFLAGS=-mfloat-abi=hard -mfpu=fpv4-sp-d16
CY_TOOLCHAIN_VFP_FLAGS=--fpu=FPv4-SP
else
CY_TOOLCHAIN_VFP_CFLAGS=-mfloat-abi=softfp -mfpu=fpv4-sp-d16
CY_TOOLCHAIN_VFP_FLAGS=--fpu=SoftVFP+FPv4-SP
endif
endif

#
# Command line flags for c-files
#
CY_TOOLCHAIN_CFLAGS=\
	-c\
	$(CY_TOOLCHAIN_CFLAGS_CORE)\
	$(CY_TOOLCHAIN_OPTIMIZATION)\
	$(CY_TOOLCHAIN_VFP_CFLAGS)\
	$(CY_TOOLCHAIN_COMMON_FLAGS)\
	-g\
	-fshort-enums\
	-fshort-wchar

#
# Command line flags for cpp-files
#
CY_TOOLCHAIN_CXXFLAGS=$(CY_TOOLCHAIN_CFLAGS)

#
# Command line flags for s-files
#
CY_TOOLCHAIN_ASFLAGS=\
	$(CY_TOOLCHAIN_FLAGS_CORE)\
	$(CY_TOOLCHAIN_VFP_FLAGS)

#
# Command line flags for linking
#
CY_TOOLCHAIN_LDFLAGS=\
	$(CY_TOOLCHAIN_FLAGS_CORE)\
	$(CY_TOOLCHAIN_VFP_FLAGS)\
	--info=totals\
	--stdlib=libc++

#
# Command line flags for archiving
#
CY_TOOLCHAIN_ARFLAGS=-rvs

#
# Toolchain-specific suffixes
#
CY_TOOLCHAIN_SUFFIX_S=S
CY_TOOLCHAIN_SUFFIX_s=s
CY_TOOLCHAIN_SUFFIX_C=c
CY_TOOLCHAIN_SUFFIX_H=h
CY_TOOLCHAIN_SUFFIX_CPP=cpp
CY_TOOLCHAIN_SUFFIX_HPP=hpp
CY_TOOLCHAIN_SUFFIX_O=o
CY_TOOLCHAIN_SUFFIX_A=ar
CY_TOOLCHAIN_SUFFIX_D=d
CY_TOOLCHAIN_SUFFIX_LS=sct
CY_TOOLCHAIN_SUFFIX_MAP=map
CY_TOOLCHAIN_SUFFIX_TARGET=elf
CY_TOOLCHAIN_SUFFIX_ARCHIVE=ar

#
# Toolchain specific flags
#
CY_TOOLCHAIN_OUTPUT_OPTION=-o
CY_TOOLCHAIN_MAPFILE=--map --list 
CY_TOOLCHAIN_LSFLAGS=--scatter 
CY_TOOLCHAIN_INCRSPFILE=@
CY_TOOLCHAIN_INCRSPFILE_ASM=--via 
CY_TOOLCHAIN_OBJRSPFILE=--via 

#
# Produce a makefile dependency rule for each input file
#
CY_TOOLCHAIN_DEPENDENCIES=-MMD -MP -MF "$(subst .$(CY_TOOLCHAIN_SUFFIX_O),.$(CY_TOOLCHAIN_SUFFIX_D),$@)" -MT "$@"

#
# Additional includes in the compilation process based on this
# toolchain
#
CY_TOOLCHAIN_INCLUDES=

#
# Additional libraries in the link process based on this toolchain
#
CY_TOOLCHAIN_DEFINES=
