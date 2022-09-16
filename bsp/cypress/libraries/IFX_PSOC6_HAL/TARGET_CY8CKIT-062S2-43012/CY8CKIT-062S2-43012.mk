################################################################################
# \file CY8CKIT-062S2-43012.mk
#
# \brief
# Define the CY8CKIT-062S2-43012 target.
#
################################################################################
# \copyright
# Copyright 2018-2021 Cypress Semiconductor Corporation (an Infineon company) or
# an affiliate of Cypress Semiconductor Corporation
#
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

# Set the default build recipe for this board if not set by the user
include $(dir $(lastword $(MAKEFILE_LIST)))/locate_recipe.mk

# MCU device selection
#    Changing the device should be done using "make bsp" or "make update_bsp" with the "DEVICE_GEN"
#    variable set to the new MCU. If you change the device manually here you must also update the
#    design.modus file and re-run the device configurator.
DEVICE:=CY8C624ABZI-S2D44
# Additional devices on the board
#    If you change the additional device here you must also update the design.modus file and re-run
#    the device configurator. You may also need to update the COMPONENT variable to include the
#    correct Wi-Fi and Bluetooth firmware.
ADDITIONAL_DEVICES:=CYW43012C0WKWBG
# Default target core to CM4 if not already set
CORE?=CM4
# Basic architecture specific components
COMPONENTS+=$(TARGET) CAT1 CAT1A

ifeq ($(CORE),CM4)
# Additional features provided by the target
COMPONENTS+=CM0P_SLEEP BSP_DESIGN_MODUS PSOC6HAL 43012 MURATA-1LV HCI-UART
# Use CyHAL
DEFINES+=CY_USING_HAL
endif

# Expose the Power Estimator tool as supported for this board
CY_SUPPORTED_TOOL_TYPES+=cype-tool
