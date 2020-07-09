################################################################################
# \file open.mk
# \version 1.0
#
# \brief
# Opens/launches a specified tool 
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


# Verify that the tool is supported
ifneq ($(CY_OPEN_TYPE),)
ifeq ($(filter $(CY_OPEN_TYPE),$(CY_OPEN_TYPE_LIST)),)
$(error Unsupported tool type - $(CY_OPEN_TYPE). $(CY_NEWLINE)Supported types are: $(CY_OPEN_TYPE_LIST))
endif
endif

# Extension construction from given file
ifneq ($(CY_OPEN_FILE)),)
CY_OPEN_EXT=$(subst .,,$(suffix $(CY_OPEN_FILE)))
endif


################################################################################
# New configurations
################################################################################

# Limit this as it can be a performance hit
ifneq ($(filter get_app_info open,$(MAKECMDGOALS)),)

# Look for tools that DISALLOW new configurations
CY_OPEN_NEWCFG_XML_TYPES+=$(shell \
	xmlFileArray=($$(find $(CY_INTERNAL_TOOLS) -maxdepth 2 -name "configurator.xml" \
					-exec grep "<new_configuration_enabled>false</new_configuration_enabled>" {} +));\
	for xmlFile in "$${xmlFileArray[@]}"; do\
		if [[ "$$xmlFile" == *"configurator.xml"* ]]; then\
			toolNameDir="$${xmlFile%/*}";\
			toolName="$${toolNameDir\#\#*/}";\
			echo "$$toolName";\
		fi;\
	done;\
)

endif

# Tools for existing files
CY_OPEN_NEWCFG_EXISTING_TYPES=$(foreach ext,$(subst .,,$(suffix $(CY_CONFIG_FILES))),$($(addsuffix _DEFAULT_TYPE,$(ext))))
# Tools that do not have an existing file
CY_OPEN_NEWCFG_POSSIBLE_TYPES=$(filter-out $(CY_OPEN_NEWCFG_EXISTING_TYPES) $(CY_OPEN_NEWCFG_XML_TYPES),$(CY_SUPPORTED_TOOL_TYPES))
# Complete list of supported files
CY_OPEN_FILTERED_SUPPORTED_TYPES=$(sort $(CY_OPEN_NEWCFG_POSSIBLE_TYPES) $(CY_OPEN_NEWCFG_EXISTING_TYPES))


################################################################################
# Prepare tool launch
################################################################################

# Only file is given. Use the default type for that file extension
ifneq ($(CY_OPEN_FILE),)
ifeq ($(CY_OPEN_TYPE),)
CY_OPEN_TYPE=$(firstword $($(CY_OPEN_EXT)_DEFAULT_TYPE))
endif
endif

# Set the tool and its arguments
CY_OPEN_TOOL_FILE=$(CY_OPEN_$(subst -,_,$(CY_OPEN_TYPE))_FILE)
CY_OPEN_TOOL_LAUNCH=$(CY_OPEN_$(subst -,_,$(CY_OPEN_TYPE))_TOOL)
CY_OPEN_TOOL_FLAGS=$(CY_OPEN_$(subst -,_,$(CY_OPEN_TYPE))_TOOL_FLAGS)
CY_OPEN_TOOL_ARGS=$(CY_OPEN_$(subst -,_,$(CY_OPEN_TYPE))_TOOL_ARGS)
CY_OPEN_TOOL_NEWCFG_FLAGS=$(CY_OPEN_$(subst -,_,$(CY_OPEN_TYPE))_TOOL_NEWCFG_FLAGS)

# Use the file if provided
ifneq ($(CY_OPEN_FILE),)
CY_OPEN_TOOL_FILE=$(CY_OPEN_FILE)
endif

ifneq ($(CY_MAKE_IDE),)
CY_OPEN_STDOUT=>& /dev/null
endif


################################################################################
# Tool launch target
################################################################################

open:
ifeq ($(CY_OPEN_FILE),)
ifeq ($(CY_OPEN_TYPE),)
	$(error Neither tool type or file specified to launch a tool)
endif
endif
ifeq ($(CY_OPEN_TOOL_LAUNCH),)
	$(error Unable to find a default tool to launch .$(CY_OPEN_EXT) file extension)
endif
ifeq ($(CY_OPEN_TOOL_FILE),)
	$(info Launching $(notdir $(CY_OPEN_TOOL_LAUNCH)) tool for a new configuration)
	$(CY_NOISE) $(CY_OPEN_TOOL_LAUNCH) $(CY_OPEN_TOOL_ARGS) $(CY_OPEN_TOOL_NEWCFG_FLAGS) $(CY_OPEN_STDOUT) &
else
	$(info $(CY_NEWLINE)Launching $(notdir $(CY_OPEN_TOOL_LAUNCH)) tool on $(CY_OPEN_TOOL_FILE))
	$(CY_NOISE) $(CY_OPEN_TOOL_LAUNCH) $(CY_OPEN_TOOL_ARGS) $(CY_OPEN_TOOL_FLAGS) $(CY_OPEN_TOOL_FILE) $(CY_OPEN_STDOUT) &
endif

#
# Identify the phony targets
#
.PHONY: open
