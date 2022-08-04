################################################################################
# \file locate_recipe.mk
#
# \brief
# Helper file for the BSP to specify the path to the core & recipe makefiles
# that is includes as dependent libraries.
#
################################################################################
# \copyright
# Copyright 2020-2021 Cypress Semiconductor Corporation (an Infineon company) or
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
ifeq ($(CY_BASELIB_PATH),)

ifneq ($(SEARCH_core-make),)
CY_BASELIB_CORE_PATH=$(SEARCH_core-make)
else
CY_BASELIB_CORE_PATH=./libs/core-make
endif

ifneq ($(SEARCH_recipe-make-cat1a),)
CY_BASELIB_PATH=$(SEARCH_recipe-make-cat1a)
else
CY_BASELIB_PATH=./libs/recipe-make-cat1a
endif

endif #($(CY_BASELIB_PATH),)
