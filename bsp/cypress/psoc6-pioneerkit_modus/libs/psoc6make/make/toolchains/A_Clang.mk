################################################################################
# \file AppleClang.mk
# \version 1.0
#
# \brief
# Apple Clang toolchain configuration
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
# The base path to the Clang cross compilation executables
#
ifeq ($(CY_COMPILER_PATH),)
CY_CROSSPATH=$(CY_COMPILER_A_Clang_DIR)
else
CY_CROSSPATH=$(CY_COMPILER_PATH)
endif

#
# Build tools
#
CC=clang
CXX=$(CC)
AS=$(CC)
AR=libtool
LD=ld

#
# DEBUG/NDEBUG selection
#
ifeq ($(CONFIG),Debug)
CY_TOOLCHAIN_DEBUG_FLAG=-DDEBUG
CY_TOOLCHAIN_OPTIMIZATION=-Og
else ifeq ($(CONFIG),Release)
CY_TOOLCHAIN_DEBUG_FLAG=-DNDEBUG
CY_TOOLCHAIN_OPTIMIZATION=-Os
else
CY_TOOLCHAIN_DEBUG_FLAG=
CY_TOOLCHAIN_OPTIMIZATION=
endif

#
# Flags common to compile and link
#
CY_TOOLCHAIN_COMMON_FLAGS=\
	-mthumb\
	-ffunction-sections\
	-fdata-sections\
	-g\
	-Wall

#
# CPU core specifics
#
ifeq ($(CORE),CM0P)
CY_TOOLCHAIN_FLAGS_CORE=\
	-arch armv6m\
	-mcpu=cortex-m0plus\
	--target=arm-none-macho
CY_TOOLCHAIN_LDFLAGS_CORE=\
	-arch armv6m\
	-lclang_rt.soft_static
CY_TOOLCHAIN_VFP_FLAGS=
else
ifeq ($(VFP_SELECT),hardfp)
CY_TOOLCHAIN_LD_VFP_FLAGS=-lclang_rt.hard_static
CY_TOOLCHAIN_VFP_FLAGS=-mfloat-abi=hard -mfpu=fpv4-sp-d16
else
CY_TOOLCHAIN_LD_VFP_FLAGS=-lclang_rt.soft_static
CY_TOOLCHAIN_VFP_FLAGS=-mfloat-abi=softfp -mfpu=fpv4-sp-d16
endif # ($(VFP_SELECT),hardfp)
CY_TOOLCHAIN_FLAGS_CORE=\
	-arch armv7em\
	-mcpu=cortex-m4\
	--target=armv7m-none-macho
CY_TOOLCHAIN_LDFLAGS_CORE=\
	-arch armv7em\
	$(CY_TOOLCHAIN_LD_VFP_FLAGS)
endif # ($(CORE),CM0P)

#
# Command line flags for c-files
#
CY_TOOLCHAIN_CFLAGS=\
	-c\
	$(CY_TOOLCHAIN_FLAGS_CORE)\
	$(CY_TOOLCHAIN_OPTIMIZATION)\
	$(CY_TOOLCHAIN_VFP_FLAGS)\
	$(CY_TOOLCHAIN_COMMON_FLAGS)\
	--no-standard-includes\
	-fasm-blocks\
	-integrated-as\
	-Wall\
	-Wno-int-to-pointer-cast\
	-static\
	-fno-stack-protector\
	-fno-common\
	-ffreestanding\
	-mlong-calls

#
# Command line flags for cpp-files
#
CY_TOOLCHAIN_CXXFLAGS=$(CY_TOOLCHAIN_CFLAGS)

#
# Command line flags for s-files
#
CY_TOOLCHAIN_ASFLAGS=\
	-c\
	$(CY_TOOLCHAIN_FLAGS_CORE)\
	$(CY_TOOLCHAIN_COMMON_FLAGS)\
	-fasm-blocks\
	-integrated-as\
	-Wall\
	-Wno-int-to-pointer-cast\
	-static\
	-fno-stack-protector\
	-fno-common\
	-ffreestanding\
	-mlong-calls

#
# Command line flags for linking
#
CY_TOOLCHAIN_LDFLAGS=\
	$(CY_TOOLCHAIN_LDFLAGS_CORE)\
	$(CY_TOOLCHAIN_LD_VFP_FLAGS)\
	-static\
	-segalign 4\
	-e Reset_Handler\
	-merge_zero_fill_sections\
	-pagezero_size 0\
	-ios_version_min 4.3\
	-preload\
	-v\
	-read_only_relocs suppress\
	-dead_strip\
	-dead_strip_dylibs\
	-no_branch_islands\
	-no_zero_fill_sections\
	-L$(CY_CROSSPATH)/lib/macho_embedded

#
# Command line flags for archiving
#
CY_TOOLCHAIN_ARFLAGS=rvs

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
CY_TOOLCHAIN_SUFFIX_A=a
CY_TOOLCHAIN_SUFFIX_D=d
CY_TOOLCHAIN_SUFFIX_LS=mk
CY_TOOLCHAIN_SUFFIX_MAP=map
CY_TOOLCHAIN_SUFFIX_TARGET=mach_o
CY_TOOLCHAIN_SUFFIX_ARCHIVE=a

#
# Toolchain specific flags
#
CY_TOOLCHAIN_OUTPUT_OPTION=-o
CY_TOOLCHAIN_MAPFILE=-map 
CY_TOOLCHAIN_LSFLAGS=
CY_TOOLCHAIN_INCRSPFILE=@
CY_TOOLCHAIN_INCRSPFILE_ASM=@
CY_TOOLCHAIN_OBJRSPFILE=-filelist 

#
# Produce a makefile dependency rule for each input file
#
CY_TOOLCHAIN_DEPENDENCIES=-MMD -MP -MF "$(subst .$(CY_TOOLCHAIN_SUFFIX_O),.$(CY_TOOLCHAIN_SUFFIX_D),$@)" -MT "$@"

#
# Additional includes in the compilation process based on this
# toolchain
#
CY_TOOLCHAIN_INCLUDES=\
	$(CY_COMPILER_GCC_ARM_DIR)/arm-none-eabi/include\
	$(CY_COMPILER_GCC_ARM_DIR)/lib/gcc/arm-none-eabi/7.2.1/include\
	$(CY_COMPILER_GCC_ARM_DIR)/lib/gcc/arm-none-eabi/7.2.1/include-fixed

#
# Additional libraries in the link process based on this toolchain
#
CY_TOOLCHAIN_DEFINES=

#
# M2BIN tool is used to convert Mach-O to binary
#
CY_TOOLCHAIN_M2BIN=$(CY_BASELIB_PATH)/make/scripts/m2bin
