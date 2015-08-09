#-------------------------------------------------------------------------------
# Copyright (c) 2012 Freescale Semiconductor, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# o Redistributions of source code must retain the above copyright notice, this list
#   of conditions and the following disclaimer.
#
# o Redistributions in binary form must reproduce the above copyright notice, this
#   list of conditions and the following disclaimer in the documentation and/or
#   other materials provided with the distribution.
#
# o Neither the name of Freescale Semiconductor, Inc. nor the names of its
#   contributors may be used to endorse or promote products derived from this
#   software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# Compiler flags
#-------------------------------------------------------------------------------

# Generate debug information.
# Add '-O0' at the end of this line to turn off optimizations.  This can make
# debugging (especially asm) much easier but it greatly increases the size of
# the code and reduces performance.
CDEBUG = -g -O0 -DDEBUG=1

# Turns on all -O2 except size increasers.
# Any CDEBUG settings will come after this and can be used to override.
COMMON_FLAGS += -Os
COMMON_FLAGS += -mno-unaligned-access

# Turn on dead code elimination.
COMMON_FLAGS += -fdce

# Enables all warnings and treat them as errors except those preceded with -Wno-
C_FLAGS_WARNINGS = -Wall -Werror -Wno-uninitialized -Wno-strict-aliasing -Wno-unused-function -fdiagnostics-show-option
C_FLAGS_WARNINGS += -Wno-unused-but-set-variable -Wno-format

# Turn on all warnings.
COMMON_FLAGS += $(C_FLAGS_WARNINGS)

# Don't use common symbols.  This is usually done in kernels.  Makes
# code size slightly larger and increases performance.
COMMON_FLAGS += -fno-common

# Use a freestanding build environment.  Standard for kernels, implies
# std library may not exist.
COMMON_FLAGS += -ffreestanding -fno-builtin

# Don't ever link anything against shared libs.
COMMON_FLAGS += -static

# Don't link against the system std library or compiler libraries.
# Everything we link against MUST be specified with -I/-L explicitly.
#COMMON_FLAGS += -nostdinc -nostdlib

# Set the C standard to C99 with GNU extensions.
# Use traditional GNU inline function semantics.
C99_FLAGS = -std=gnu99 -fgnu89-inline

# Generate code specifically for ARMv7-A, cortex-ax CPU.
# Use the ARM Procedure Call Standard.
ARM_FLAGS = -march=armv7-a -mcpu=$(CPU) -mtune=$(CPU) -mapcs

ifeq "$(USE_THUMB)" "1"
    # Generate thumb2 instructions (mixed 16/32-bit).
    ARM_FLAGS += -mthumb
    # Allow mixed ARM and thumb code.  All C code will generate thumb instructions
    # but there is hand-written asm that requires ARM.
    ARM_FLAGS += -mthumb-interwork
    # Indicate that we're using thumb.
    ARM_FLAGS += -DUSE_THUMB
    CC_LIB_POST = thumb2
else
    # Generate ARM-only code.
    ARM_FLAGS += -marm
    CC_LIB_POST =
endif

# Use NEON SIMD instructions for floating point.  Alternatively can specify
# VFP which gives IEEE 754-compliance (unlike NEON which can have errors).
ARM_FLAGS += -mfpu=neon
# Specify these options with NEON.
ARM_FLAGS += -ftree-vectorize
ARM_FLAGS += -fno-math-errno
ARM_FLAGS += -funsafe-math-optimizations
ARM_FLAGS += -fno-signed-zeros
# Use float-abi=softfp for soft floating point api with HW instructions.
# Alternatively, float-abi=hard for hw float instructions and pass float args in float regs.
ARM_FLAGS += -mfloat-abi=softfp

# Build common flags shared by C and C++.
COMMON_FLAGS += $(ARM_FLAGS)

# Add debug flags for debug builds.
ifeq "$(DEBUG)" "1"
COMMON_FLAGS += $(CDEBUG)
endif

# C flags. Set C99 mode.
CFLAGS += $(COMMON_FLAGS)
CFLAGS += $(C99_FLAGS)

# C++ flags. Disable exceptions and RTTI.
CXXFLAGS += $(COMMON_FLAGS)
CXXFLAGS += -fno-exceptions -fno-rtti

#-------------------------------------------------------------------------------
# Include paths
#-------------------------------------------------------------------------------

# Link against libc and libgcc. Specify paths to libc in newlib build
# directory.  Need to specify libgcc since our linker does not link
# against anything, even compiler libs because of -nostdlib.
LDADD += -lm -lstdc++ -lc -lgcc

# These include paths have to be quoted because they may contain spaces,
# particularly under cygwin.
LDINC += -L '$(LIBGCC_LDPATH)' -L '$(LIBC_LDPATH)'

# Indicate gcc and newlib std includes as -isystem so gcc tags and
# treats them as system directories.
SYSTEM_INC = \
    -isystem '$(CC_INCLUDE)' \
    -isystem '$(CC_INCLUDE_FIXED)' \
    -isystem '$(LIBC_INCLUDE)'

INCLUDES += \
    -I$(SDK_ROOT)/sdk \
    -I$(SDK_ROOT)/sdk/include  \
    -I$(SDK_ROOT)/sdk/include/$(TARGET) \
    -I$(SDK_ROOT)/sdk/drivers \
    -I$(SDK_ROOT)/sdk/common \
    -I$(SDK_ROOT)/sdk/core \
    -I$(SDK_ROOT)/sdk/utility \
    -I$(BOARD_ROOT) \
    -I$(SDK_ROOT)/board/$(TARGET)/common \
    -I$(SDK_ROOT)/board/common \
    -I$(LWIP_ROOT)/lwip/src/include \
    -I$(LWIP_ROOT)/lwip/src/include/ipv4 \
    -I$(LWIP_ROOT)/lwip/src/include/ipv6 \
    -I$(LWIP_ROOT)/mx6/include

