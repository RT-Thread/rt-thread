#-------------------------------------------------------------------------------
# Copyright (c) 2012-2013 Freescale Semiconductor, Inc.
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

include $(SDK_ROOT)/mk/common.mk


define SOURCES
Device/app/hid/mouse_button.c
Device/app/hid/usb_descriptor.c
Device/source/common/usb_framework.c
Device/source/common/usb_class.c
Device/source/class/usb_hid.c
Device/source/driver/usbevent.c
Device/source/driver/usb_driver.c
Device/source/driver/mx6x/usb_dci_imx6.c
endef

# Set defines used by the USB stack.
DEFINES += \
    -DMULTIPLE_DEVICES \
    -DHIGH_SPEED_DEVICE

# Extra include paths needed to build the USB stack.
INCLUDES += \
	-I$(SDK_ROOT)/sdk/common/usb_stack/Device/app/common \
	-I$(SDK_ROOT)/sdk/common/usb_stack/Device/source/common \
	-I$(SDK_ROOT)/sdk/common/usb_stack/Device/source/class \
	-I$(SDK_ROOT)/sdk/common/usb_stack/Device/source/driver \
	-I$(SDK_ROOT)/sdk/common/usb_stack/Device/source/driver/mx6x \
	-I$(SDK_ROOT)/sdk/common/usb_stack/Device/app/common/mx6x

# 	-I$(SDK_ROOT)/sdk/common/usb_stack/Device/app/hid \

C_FLAGS_WARNINGS = 

include $(SDK_ROOT)/mk/targets.mk
