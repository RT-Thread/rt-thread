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
# Target and board configuration
#-------------------------------------------------------------------------------

# Handle lower-case versions of the config variables. These are really meant to ease
# manual invocation of make via the command line.
ifdef target
TARGET = $(target)
endif
ifdef board
BOARD = $(board)
endif
ifdef boardrev
BOARD_REVISION = $(boardrev)
endif

# Target
ifeq "$(TARGET)" "mx6dq"
DEFINES += -DCHIP_MX6DQ
CPU	= cortex-a9
else ifeq "$(TARGET)" "mx6sdl"
DEFINES += -DCHIP_MX6SDL
CPU	= cortex-a9
else ifeq "$(TARGET)" "mx6sl"
DEFINES += -DCHIP_MX6SL
CPU	= cortex-a9
else ifdef TARGET
$(error Unknown target $(TARGET))
endif

# Board
ifeq "$(BOARD)" "evb"
DEFINES += -DBOARD_EVB
else ifeq "$(BOARD)" "evk"
DEFINES += -DBOARD_EVK
else ifeq "$(BOARD)" "sabre_ai"
DEFINES += -DBOARD_SABRE_AI
else ifeq "$(BOARD)" "smart_device"
DEFINES += -DBOARD_SMART_DEVICE
else ifdef BOARD
$(error Unknown board $(BOARD))
endif

# Board revision, defaults to a if not specified.
ifndef BOARD_REVISION
BOARD_REVISION = a
BOARD_REVISION_IS_DEFAULT = yes
endif
ifeq "$(BOARD_REVISION)" "c"
DEFINES +=-DBOARD_REV_C
else ifeq "$(BOARD_REVISION)" "b"
DEFINES +=-DBOARD_REV_B
else ifeq "$(BOARD_REVISION)" "a"
DEFINES +=-DBOARD_REV_A
else ifdef BOARD_REVISION
$(error Unknown board revision $(BOARD_REVISION))
endif

# Only define this variable if a board is specified.
ifdef BOARD
BOARD_WITH_REV := $(BOARD)_rev_$(BOARD_REVISION)
endif

# Set this define to 1 if we want to build thumb binaries, or 0 for ARM.
USE_THUMB ?= 0

# Enable debug build by default.
DEBUG ?= 1

