################################################################################
# \file IAR.mk
# \version 1.0
#
# \brief
# IAR toolchain configuration.
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
# The base path to the IAR cross compilation executables
#
ifeq ($(CY_COMPILER_PATH),)
CY_CROSSPATH=$(CY_COMPILER_IAR_DIR)/bin
else
CY_CROSSPATH=$(CY_COMPILER_PATH)/bin
endif

#
# Build tools
#
CC=$(CY_CROSSPATH)/iccarm.exe
CXX=$(CC)
AS=$(CY_CROSSPATH)/iasmarm.exe
AR=$(CY_CROSSPATH)/iarchive.exe
LD=$(CY_CROSSPATH)/ilinkarm.exe

#
# DEBUG/NDEBUG selection
#
ifeq ($(CONFIG),Debug)
CY_TOOLCHAIN_DEBUG_FLAG=-DDEBUG
CY_TOOLCHAIN_OPTIMIZATION=-Ol
else 
ifeq ($(CONFIG),Release)
CY_TOOLCHAIN_DEBUG_FLAG=-DNDEBUG
CY_TOOLCHAIN_OPTIMIZATION=-Ohs
else
CY_TOOLCHAIN_DEBUG_FLAG=
CY_TOOLCHAIN_OPTIMIZATION=
endif
endif

#
# Flags common to compile and link
#
ifneq ($(VERBOSE),)
CY_TOOLCHAIN_SILENT_CFLAGS=
CY_TOOLCHAIN_SILENT_SFLAGS=
else
CY_TOOLCHAIN_SILENT_CFLAGS=--silent
CY_TOOLCHAIN_SILENT_SFLAGS=-S
endif

#
# CPU core specifics
#
ifeq ($(CORE),CM0P)
CY_TOOLCHAIN_FLAGS_CORE=--cpu Cortex-M0+
CY_TOOLCHAIN_VFP_FLAGS=
else
CY_TOOLCHAIN_FLAGS_CORE=--cpu Cortex-M4
CY_TOOLCHAIN_VFP_FLAGS=--fpu FPv4-SP
ifeq ($(VFP_SELECT),hardfp)
CY_TOOLCHAIN_VFP_CFLAGS=$(CY_TOOLCHAIN_VFP_FLAGS) --aapcs vfp
else
CY_TOOLCHAIN_VFP_CFLAGS=$(CY_TOOLCHAIN_VFP_FLAGS) --aapcs std
endif
endif

#
# Command line flags for c-files
#
CY_TOOLCHAIN_CFLAGS=\
	-c\
	$(CY_TOOLCHAIN_FLAGS_CORE)\
	$(CY_TOOLCHAIN_OPTIMIZATION)\
	$(CY_TOOLCHAIN_VFP_CFLAGS)\
	$(CY_TOOLCHAIN_SILENT_CFLAGS)\
	--endian=little\
	-e\
	--enable_restrict\
	--no_wrap_diagnostics

ifeq ($(CONFIG),Debug)
CY_TOOLCHAIN_CFLAGS+=--debug
endif

#
# Command line flags for cpp-files
#
CY_TOOLCHAIN_CXXFLAGS=\
	$(CY_TOOLCHAIN_CFLAGS)\
	--c++\
	--no_rtti\
	--no_exceptions

#
# Command line flags for s-files
#
CY_TOOLCHAIN_ASFLAGS=\
	-c\
	$(CY_TOOLCHAIN_FLAGS_CORE)\
	$(CY_TOOLCHAIN_VFP_FLAGS)\
	$(CY_TOOLCHAIN_SILENT_SFLAGS)\
	-s+\
	-w+\
	-r

#
# Command line flags for linking
#
CY_TOOLCHAIN_LDFLAGS=\
	$(CY_TOOLCHAIN_FLAGS_CORE)\
	$(CY_TOOLCHAIN_VFP_FLAGS)\
	$(CY_TOOLCHAIN_SILENT_CFLAGS)\

#
# Command line flags for archiving
#
CY_TOOLCHAIN_ARFLAGS=\
	--create\
	--verbose

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
CY_TOOLCHAIN_SUFFIX_LS=icf
CY_TOOLCHAIN_SUFFIX_MAP=map
CY_TOOLCHAIN_SUFFIX_TARGET=elf
CY_TOOLCHAIN_SUFFIX_ARCHIVE=a

#
# Toolchain specific flags
#
CY_TOOLCHAIN_OUTPUT_OPTION=-o
CY_TOOLCHAIN_MAPFILE=--map=
CY_TOOLCHAIN_LSFLAGS=--config=
CY_TOOLCHAIN_INCRSPFILE=-f 
CY_TOOLCHAIN_INCRSPFILE_ASM=-f 
CY_TOOLCHAIN_OBJRSPFILE=-f 

#
# Produce a makefile dependency rule for each input file
#
CY_TOOLCHAIN_DEPENDENCIES=--dependencies=m "$(subst .$(CY_TOOLCHAIN_SUFFIX_O),.$(CY_TOOLCHAIN_SUFFIX_D),$@)"

#
# Additional includes in the compilation process based on this
# toolchain
#
CY_TOOLCHAIN_INCLUDES=

#
# Additional libraries in the link process based on this toolchain
#
CY_TOOLCHAIN_DEFINES=

