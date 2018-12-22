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
# Root paths
#-------------------------------------------------------------------------------

# Build root directory paths.
SDK_LIB_ROOT = $(SDK_ROOT)/sdk
APPS_ROOT = $(SDK_ROOT)/apps
BOARD_ROOT = $(SDK_ROOT)/board/$(TARGET)/$(BOARD)
LWIP_ROOT = $(SDK_ROOT)/lwip

#-------------------------------------------------------------------------------
# Output file paths
#-------------------------------------------------------------------------------

# Build output directory paths.
#
# All output goes under the top-level 'output' directory. Libraries are not board-specific,
# but apps are. Everything is chip-specific. Objects for both libs and apps are placed in
# an 'obj' directory under either the app or lib output directory.
#
# Libs:     output/<chip>/lib/lib<foo>.a
# Lib objs: output/<chip>/lib/obj/<foo>/...
#
# Apps:     output/<chip>/<app>/<board>/<app>.elf
# App objs: output/<chip>/<app>/<board>/obj/...
#
OUTPUT_ROOT = $(SDK_ROOT)/output/$(TARGET)

LIBS_ROOT = $(OUTPUT_ROOT)/lib
LIB_OBJS_ROOT = $(LIBS_ROOT)/obj/$(TARGET_LIB_NAME)

# Put app build products in their own dir.
APP_OUTPUT_ROOT = $(OUTPUT_ROOT)/$(APP_NAME)/$(BOARD_WITH_REV)
APP_OBJS_ROOT = $(APP_OUTPUT_ROOT)/obj

#-------------------------------------------------------------------------------
# Standard library paths
#-------------------------------------------------------------------------------

LIBSDK = $(LIBS_ROOT)/libsdk.a
LIBBOARD = $(LIBS_ROOT)/libboard_$(BOARD_WITH_REV).a
LIBLWIP = $(LIBS_ROOT)/liblwip.a


