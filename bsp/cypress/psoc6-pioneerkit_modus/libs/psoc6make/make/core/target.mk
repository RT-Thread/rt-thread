################################################################################
# \file target.mk
# \version 1.0
#
# \brief
# Finds available targets in the design.
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
# Search for target make files and BSPs. Use := assignment for better performance.
#
CY_TARGET_MAKEFILE_SEARCH:=$(call CY_MACRO_SEARCH,$(TARGET).mk,$(CY_INTERNAL_APP_PATH))\
                    $(if $(CY_INTERNAL_EXTAPP_PATH),$(call CY_MACRO_SEARCH,$(TARGET).mk,$(CY_INTERNAL_EXTAPP_PATH)))\
                    $(if $(SEARCH_LIBS_AND_INCLUDES),$(foreach d,$(SEARCH_LIBS_AND_INCLUDES),$(call CY_MACRO_SEARCH,$(TARGET).mk,$(d))))
CY_TARGET_AVAILABLE_SEARCH:=$(call CY_MACRO_SEARCH,.mk,$(CY_INTERNAL_APP_PATH))\
                    $(if $(CY_INTERNAL_EXTAPP_PATH),$(call CY_MACRO_SEARCH,.mk,$(CY_INTERNAL_EXTAPP_PATH)))\
                    $(if $(SEARCH_LIBS_AND_INCLUDES),$(foreach d,$(SEARCH_LIBS_AND_INCLUDES),$(call CY_MACRO_SEARCH,.mk,$(d))))\

# Gather and filter the found files
CY_SEARCH_PRUNED_MAKE_FILES:=$(filter-out $(foreach d,$(CY_IGNORE_DIRS),$(filter $(d)%,$(CY_TARGET_MAKEFILE_SEARCH))),$(CY_TARGET_MAKEFILE_SEARCH))
CY_SEARCH_PRUNED_AVAILABLEMAKE_FILES:=$(filter-out $(foreach d,$(CY_IGNORE_DIRS),$(filter $(d)%,$(CY_TARGET_AVAILABLE_SEARCH))),$(CY_TARGET_AVAILABLE_SEARCH))

# Target makefile
CY_TARGET_MAKEFILE=$(call CY_MACRO_FILTER_FILES,MAKE)

# Check if the TARGET.mk was brought in through CY_EXTRA_INCLUDES or directly in the app makefile
CY_TARGET_EXTRA_INCLUDES=$(filter %/$(TARGET).mk,$(MAKEFILE_LIST))
CY_TARGET_EXTRA_FILTERED=$(filter-out $(CY_TARGET_EXTRA_INCLUDES),$(CY_TARGET_MAKEFILE))

# Full list of available targets
CY_TARGET_AVAILABLE_DIRS=$(notdir $(call CY_MACRO_DIR,$(CY_SEARCH_PRUNED_AVAILABLEMAKE_FILES) $(CY_TARGET_EXTRA_INCLUDES)))
CY_TARGET_AVAILABLE=$(sort $(subst TARGET_,,$(foreach item,$(CY_TARGET_AVAILABLE_DIRS),$(if $(findstring /TARGET_,/$(item)),$(item),))))

#
# Set the target makefile and directory
#
ifneq ($(CY_TARGET_EXTRA_INCLUDES),)

ifneq ($(CY_TARGET_EXTRA_FILTERED),)
$(call CY_MACRO_ERROR,Found multiple identical targets: $(CY_TARGET_EXTRA_INCLUDES) $(CY_TARGET_EXTRA_FILTERED))
else
CY_TARGET_DIR=$(call CY_MACRO_DIR,$(CY_TARGET_EXTRA_INCLUDES))
endif

else

ifeq ($(words $(CY_TARGET_MAKEFILE)),0)
$(info Available target(s): $(CY_TARGET_AVAILABLE))
$(call CY_MACRO_ERROR,Target "$(TARGET)" not found)
else ifeq ($(words $(CY_TARGET_MAKEFILE)),1)
CY_TARGET_DIR=$(call CY_MACRO_DIR,$(CY_TARGET_MAKEFILE)$(CY_TARGET_MAKEFILE_SEARCH_LIBS))
include $(CY_TARGET_MAKEFILE) $(CY_TARGET_MAKEFILE_SEARCH_LIBS)  
else
$(call CY_MACRO_ERROR,Found multiple identical targets:$(CY_TARGET_MAKEFILE))
endif

endif
