################################################################################
# \file build.mk
# \version 1.0
#
# \brief
# Performs the compilation and linking steps.
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


################################################################################
# Target output
################################################################################

ifneq ($(LIBNAME),)
CY_BUILD_TARGET=$(CY_CONFIG_DIR)/$(LIBNAME).$(CY_TOOLCHAIN_SUFFIX_ARCHIVE)
else
CY_BUILD_TARGET=$(CY_CONFIG_DIR)/$(APPNAME).$(CY_TOOLCHAIN_SUFFIX_TARGET)
endif
CY_BUILD_MAPFILE=$(CY_CONFIG_DIR)/$(APPNAME).$(CY_TOOLCHAIN_SUFFIX_MAP)


################################################################################
# VPATH resolution
################################################################################

#
# Search for relative path patterns in source list
# $(1) : Pattern
# $(2) : Sources
#
CY_MACRO_VPATH_FIND=$(foreach level,$(1),$(if $(filter $(level)%,$(2)),$(level)))

#
# Search for relative paths in user sources and include them in the VPATH
#
CY_BUILD_VPATH_PATTERN=./ ./../ ./../../ ./../../../ ./../../../../ ./../../../../../ ./../../../../../../ ./../../../../../../../ \
					../ ../../ ../../../ ../../../../ ../../../../../ ../../../../../../ ../../../../../../../
VPATH+=$(call CY_MACRO_VPATH_FIND,$(CY_BUILD_VPATH_PATTERN),$(SOURCES))


##############################################################################
#
# Macro to construct recursive make for dependent lib apps
#
# Arguments:
# 1: The name of the target
# 2: The lib app directory
#
define CY_MACRO_SHAREDLIB_DEPENDENCIES

$(1)_SED_PATTERN=$(subst /,\/,$(subst .,\.,$(2)))
ifeq ($(CY_BUILD_LOC),$(CY_APP_LOCATION)/build)
$(1)_SHAREDLIB_BUILD_LOCATION?=$(2)/build/$(TARGET)/$(CONFIG)
else
$(1)_SHAREDLIB_BUILD_LOCATION?=$(CY_INTERNAL_BUILD_LOCATION)/$(1)/$(TARGET)/$(CONFIG)
endif

# Satisfy dependencies
$$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist.rsp: | shared_libs
$$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist.rsp: | shared_libs
$$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact.rsp: | shared_libs
$(1)_shared_lib: | $$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist.rsp $$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist.rsp $$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact.rsp

$(1)_shared_lib:
	 @inclist_read=$$$$(cat $$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist.rsp | sed -e "s/I\.\//I$$($(1)_SED_PATTERN)\//g" | tr " " "\n"); \
	 if [ -f "$$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist_export.rsp" ]; then \
	 	inclist_export_read=$$$$(cat $$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist_export.rsp | tr " " "\n"); \
	 else \
		 echo $$$$inclist_read > $$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist_export.rsp ;\
	 fi;\
	 if [[ "$$$$inclist_read" != "$$$$inclist_export_read" ]]; then \
		echo $$$$inclist_read > $$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist_export.rsp ;\
	 fi; \
	 liblist_read=$$$$(cat $$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist.rsp | sed -e "s/\.\//$$($(1)_SED_PATTERN)\//g" | tr " " "\n"); \
	 if [ -f "$$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist_export.rsp" ]; then \
	 	liblist_export_read=$$$$(cat $$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist_export.rsp | tr " " "\n"); \
	 else \
	  	echo $$$$liblist_read > $$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist_export.rsp ;\
	 fi;\
	 if [[ "$$$$liblist_read" != "$$$$liblist_export_read" ]]; then \
		echo $$$$liblist_read > $$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist_export.rsp ;\
	 fi; \
	 artifact_read=$$$$(sed '1s;^;$$($(1)_SHAREDLIB_BUILD_LOCATION)/;' $$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact.rsp); \
	 if [ -f "$$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact_export.rsp" ]; then \
 		artifact_export_read=$$$$(cat $$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact_export.rsp); \
	 else \
		echo $$$$artifact_read > $$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact_export.rsp;\
	 fi;\
	 if [[ "$$$$artifact_read" -nt "$(CY_BUILD_TARGET)" ]] || [[ "$$$$artifact_read" != "$$$$artifact_export_read" ]]; then\
		echo $$$$artifact_read > $$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact_export.rsp;\
	 fi;

# Satisfy dependencies
$$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist_export.rsp: | $(1)_shared_lib
$$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist_export.rsp: | $(1)_shared_lib
$$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact_export.rsp: | $(1)_shared_lib

endef


################################################################################
# Shared libraries
################################################################################

ifneq ($(SEARCH_LIBS_AND_INCLUDES),)

# Construct targets for all dependent lib apps
$(foreach lib,$(SEARCH_LIBS_AND_INCLUDES),$(eval $(call CY_MACRO_SHAREDLIB_DEPENDENCIES,$(notdir $(lib)),$(lib))))

CY_SHAREDLIB_LIST=$(foreach lib,$(SEARCH_LIBS_AND_INCLUDES),$(notdir $(lib)_shared_lib))
CY_SHAREDLIB_ARTIFACT_LIST=$(foreach lib,$(SEARCH_LIBS_AND_INCLUDES),$($(notdir $(lib))_SHAREDLIB_BUILD_LOCATION)/artifact.rsp)

CY_SHAREDLIB_INCLUDES_EXPORT_LIST=$(foreach lib,$(SEARCH_LIBS_AND_INCLUDES),$($(notdir $(lib))_SHAREDLIB_BUILD_LOCATION)/inclist_export.rsp)
CY_SHAREDLIB_LIBS_EXPORT_LIST=$(foreach lib,$(SEARCH_LIBS_AND_INCLUDES),$($(notdir $(lib))_SHAREDLIB_BUILD_LOCATION)/liblist_export.rsp)
CY_SHAREDLIB_ARTIFACT_EXPORT_LIST=$(foreach lib,$(SEARCH_LIBS_AND_INCLUDES),$($(notdir $(lib))_SHAREDLIB_BUILD_LOCATION)/artifact_export.rsp)

CY_BUILD_SHAREDLIB_INCLIST=$(foreach inc,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST),$(addprefix $(CY_TOOLCHAIN_INCRSPFILE),$(inc)))
CY_BUILD_SHAREDLIB_LIBLIST=$(foreach lib,$(CY_SHAREDLIB_LIBS_EXPORT_LIST),$(addprefix $(CY_TOOLCHAIN_OBJRSPFILE),$(lib)))\
							$(foreach artifact,$(CY_SHAREDLIB_ARTIFACT_EXPORT_LIST),$(addprefix $(CY_TOOLCHAIN_OBJRSPFILE),$(artifact)))

# Sentinel file to always trigger link step
CY_SHAREDLIB_TIMESTAMP=$(CY_CONFIG_DIR)/shared_libs.timestamp
$(shell touch $(CY_SHAREDLIB_TIMESTAMP))

endif


################################################################################
# Build arguments
################################################################################

#
# The list of C and S source files that come from the application and generated source
#
CY_BUILD_SRC_S_FILES=$(patsubst $(CY_INTERNAL_APP_PATH)/%,/%,$(patsubst $(CY_INTERNAL_EXTAPP_PATH)/%,/%,\
						$(filter %.$(CY_TOOLCHAIN_SUFFIX_S),$(CY_RECIPE_SOURCE))))
CY_BUILD_SRC_s_FILES=$(patsubst $(CY_INTERNAL_APP_PATH)/%,/%,$(patsubst $(CY_INTERNAL_EXTAPP_PATH)/%,/%,\
						$(filter %.$(CY_TOOLCHAIN_SUFFIX_s),$(CY_RECIPE_SOURCE))))
CY_BUILD_SRC_C_FILES=$(patsubst $(CY_INTERNAL_APP_PATH)/%,/%,$(patsubst $(CY_INTERNAL_EXTAPP_PATH)/%,/%,\
						$(filter %.$(CY_TOOLCHAIN_SUFFIX_C),$(CY_RECIPE_SOURCE))))
CY_BUILD_SRC_CPP_FILES=$(patsubst $(CY_INTERNAL_APP_PATH)/%,/%,$(patsubst $(CY_INTERNAL_EXTAPP_PATH)/%,/%,\
						$(filter %.$(CY_TOOLCHAIN_SUFFIX_CPP),$(CY_RECIPE_SOURCE))))
CY_BUILD_GENSRC_S_FILES=$(filter %.$(CY_TOOLCHAIN_SUFFIX_S),$(CY_RECIPE_GENERATED))
CY_BUILD_GENSRC_s_FILES=$(filter %.$(CY_TOOLCHAIN_SUFFIX_s),$(CY_RECIPE_GENERATED))
CY_BUILD_GENSRC_C_FILES=$(filter %.$(CY_TOOLCHAIN_SUFFIX_C),$(CY_RECIPE_GENERATED))
CY_BUILD_GENSRC_CPP_FILES=$(filter %.$(CY_TOOLCHAIN_SUFFIX_CPP),$(CY_RECIPE_GENERATED))
CY_BUILD_EXTSRC_S_FILES=$(patsubst $(CY_INTERNAL_APP_PATH)/%,/%,$(subst ../,,$(filter %.$(CY_TOOLCHAIN_SUFFIX_S),$(SOURCES))))
CY_BUILD_EXTSRC_s_FILES=$(patsubst $(CY_INTERNAL_APP_PATH)/%,/%,$(subst ../,,$(filter %.$(CY_TOOLCHAIN_SUFFIX_s),$(SOURCES))))
CY_BUILD_EXTSRC_C_FILES=$(patsubst $(CY_INTERNAL_APP_PATH)/%,/%,$(subst ../,,$(filter %.$(CY_TOOLCHAIN_SUFFIX_C),$(SOURCES))))
CY_BUILD_EXTSRC_CPP_FILES=$(patsubst $(CY_INTERNAL_APP_PATH)/%,/%,$(subst ../,,$(filter %.$(CY_TOOLCHAIN_SUFFIX_CPP),$(SOURCES))))

#
# The list of object files
#
CY_BUILD_SRC_S_OBJ_FILES=$(addprefix $(CY_CONFIG_DIR)/,$(CY_BUILD_SRC_S_FILES:%.$(CY_TOOLCHAIN_SUFFIX_S)=%.$(CY_TOOLCHAIN_SUFFIX_O)))
CY_BUILD_SRC_s_OBJ_FILES=$(addprefix $(CY_CONFIG_DIR)/,$(CY_BUILD_SRC_s_FILES:%.$(CY_TOOLCHAIN_SUFFIX_s)=%.$(CY_TOOLCHAIN_SUFFIX_O)))
CY_BUILD_SRC_C_OBJ_FILES=$(addprefix $(CY_CONFIG_DIR)/,$(CY_BUILD_SRC_C_FILES:%.$(CY_TOOLCHAIN_SUFFIX_C)=%.$(CY_TOOLCHAIN_SUFFIX_O)))
CY_BUILD_SRC_CPP_OBJ_FILES=$(addprefix $(CY_CONFIG_DIR)/,$(CY_BUILD_SRC_CPP_FILES:%.$(CY_TOOLCHAIN_SUFFIX_CPP)=%.$(CY_TOOLCHAIN_SUFFIX_O)))
CY_BUILD_GENSRC_S_OBJ_FILES=$(patsubst $(CY_BUILDTARGET_DIR)/%,$(CY_CONFIG_DIR)/%,$(CY_BUILD_GENSRC_S_FILES:%.$(CY_TOOLCHAIN_SUFFIX_S)=%.$(CY_TOOLCHAIN_SUFFIX_O)))
CY_BUILD_GENSRC_s_OBJ_FILES=$(patsubst $(CY_BUILDTARGET_DIR)/%,$(CY_CONFIG_DIR)/%,$(CY_BUILD_GENSRC_s_FILES:%.$(CY_TOOLCHAIN_SUFFIX_s)=%.$(CY_TOOLCHAIN_SUFFIX_O)))
CY_BUILD_GENSRC_C_OBJ_FILES=$(patsubst $(CY_BUILDTARGET_DIR)/%,$(CY_CONFIG_DIR)/%,$(CY_BUILD_GENSRC_C_FILES:%.$(CY_TOOLCHAIN_SUFFIX_C)=%.$(CY_TOOLCHAIN_SUFFIX_O)))
CY_BUILD_GENSRC_CPP_OBJ_FILES=$(patsubst $(CY_BUILDTARGET_DIR)/%,$(CY_CONFIG_DIR)/%,$(CY_BUILD_GENSRC_CPP_FILES:%.$(CY_TOOLCHAIN_SUFFIX_CPP)=%.$(CY_TOOLCHAIN_SUFFIX_O)))
CY_BUILD_EXTSRC_S_OBJ_FILES=$(addprefix $(CY_CONFIG_DIR)/user/,$(CY_BUILD_EXTSRC_S_FILES:%.$(CY_TOOLCHAIN_SUFFIX_S)=%.$(CY_TOOLCHAIN_SUFFIX_O)))
CY_BUILD_EXTSRC_s_OBJ_FILES=$(addprefix $(CY_CONFIG_DIR)/user/,$(CY_BUILD_EXTSRC_s_FILES:%.$(CY_TOOLCHAIN_SUFFIX_s)=%.$(CY_TOOLCHAIN_SUFFIX_O)))
CY_BUILD_EXTSRC_C_OBJ_FILES=$(addprefix $(CY_CONFIG_DIR)/user/,$(CY_BUILD_EXTSRC_C_FILES:%.$(CY_TOOLCHAIN_SUFFIX_C)=%.$(CY_TOOLCHAIN_SUFFIX_O)))
CY_BUILD_EXTSRC_CPP_OBJ_FILES=$(addprefix $(CY_CONFIG_DIR)/user/,$(CY_BUILD_EXTSRC_CPP_FILES:%.$(CY_TOOLCHAIN_SUFFIX_CPP)=%.$(CY_TOOLCHAIN_SUFFIX_O)))

CY_BUILD_ALL_OBJ_FILES=\
	$(call CY_MACRO_REMOVE_DOUBLESLASH,\
	$(CY_BUILD_SRC_S_OBJ_FILES)\
	$(CY_BUILD_SRC_s_OBJ_FILES)\
	$(CY_BUILD_SRC_C_OBJ_FILES)\
	$(CY_BUILD_SRC_CPP_OBJ_FILES)\
	$(CY_BUILD_GENSRC_S_OBJ_FILES)\
	$(CY_BUILD_GENSRC_s_OBJ_FILES)\
	$(CY_BUILD_GENSRC_C_OBJ_FILES)\
	$(CY_BUILD_GENSRC_CPP_OBJ_FILES)\
	$(CY_BUILD_EXTSRC_S_OBJ_FILES)\
	$(CY_BUILD_EXTSRC_s_OBJ_FILES)\
	$(CY_BUILD_EXTSRC_C_OBJ_FILES)\
	$(CY_BUILD_EXTSRC_CPP_OBJ_FILES))

#
# Dependency files
#
CY_DEPENDENCY_FILES=$(CY_BUILD_ALL_OBJ_FILES:%.$(CY_TOOLCHAIN_SUFFIX_O)=%.$(CY_TOOLCHAIN_SUFFIX_D))

#
# The list of static libraries
#
CY_BUILD_ALL_LIB_FILES=$(CY_RECIPE_LIBS)

#
# Output directories
#
CY_BUILD_DIRS=$(sort $(call CY_MACRO_DIR,$(CY_BUILD_ALL_OBJ_FILES)) $(call CY_MACRO_DIR,$(CY_BUILD_TARGET)))

#
# Check Windows path length limit for build directories
#
ifeq ($(OS),Windows_NT)
CY_BUILD_CHECK_STRLEN:=$(shell \
	for directory in $(CY_BUILD_DIRS); do\
		if [ "$${\#directory}" -ge 260 ]; then\
			echo "$$directory";\
		fi;\
	done)

ifneq ($(strip $(CY_BUILD_CHECK_STRLEN)),)
$(error Detected path(s) that exceed the Windows path length: $(CY_BUILD_CHECK_STRLEN))
endif
endif

#
# Prints full/shortened source name
#
ifneq (,$(filter $(VERBOSE),true 1))
CY_COMPILE_PRINT=$<
else
CY_COMPILE_PRINT=$(notdir $<)
endif

# 
# Gather the includes in inclist_export.rsp files
# $(1) : List of inclist_export.rsp files
#
CY_MACRO_ECLIPSE_PRINT=$(shell \
						for incFile in $(1); do\
							incDirs="$$incDirs $$(cat $$incFile)";\
						done;\
						echo $$incDirs)

#
# Construct the full list of flags
#
CY_BUILD_ALL_ASFLAGS_UC=\
	$(CY_RECIPE_ASFLAGS)\
	$(CY_RECIPE_DEFINES)

CY_BUILD_ALL_ASFLAGS_LC=\
	$(CY_RECIPE_ASFLAGS)

CY_BUILD_ALL_CFLAGS=\
	$(CY_RECIPE_CFLAGS)\
	$(CY_RECIPE_DEFINES)

CY_BUILD_ALL_CXXFLAGS=\
	$(CY_RECIPE_CXXFLAGS)\
	$(CY_RECIPE_DEFINES)

#
# Compiler arguments
#
CY_BUILD_COMPILE_AS_UC=$(AS) $(CY_BUILD_ALL_ASFLAGS_UC) $(CY_TOOLCHAIN_INCRSPFILE_ASM)$(CY_CONFIG_DIR)/inclist.rsp \
						$(CY_BUILD_SHAREDLIB_INCLIST) $(CY_TOOLCHAIN_OUTPUT_OPTION)
CY_BUILD_COMPILE_AS_LC=$(AS) $(CY_BUILD_ALL_ASFLAGS_LC) $(CY_TOOLCHAIN_INCRSPFILE_ASM)$(CY_CONFIG_DIR)/inclist.rsp \
						$(CY_BUILD_SHAREDLIB_INCLIST) $(CY_TOOLCHAIN_OUTPUT_OPTION)
CY_BUILD_COMPILE_C=$(CC) $(CY_BUILD_ALL_CFLAGS) $(CY_TOOLCHAIN_INCRSPFILE)$(CY_CONFIG_DIR)/inclist.rsp \
						$(CY_BUILD_SHAREDLIB_INCLIST) $(CY_TOOLCHAIN_DEPENDENCIES) $(CY_TOOLCHAIN_OUTPUT_OPTION) 
CY_BUILD_COMPILE_CPP=$(CXX) $(CY_BUILD_ALL_CXXFLAGS) $(CY_TOOLCHAIN_INCRSPFILE)$(CY_CONFIG_DIR)/inclist.rsp \
						$(CY_BUILD_SHAREDLIB_INCLIST) $(CY_TOOLCHAIN_DEPENDENCIES) $(CY_TOOLCHAIN_OUTPUT_OPTION)

#
# Linker arguments
#
CY_BUILD_LINK=$(LD) $(CY_RECIPE_LDFLAGS) $(CY_TOOLCHAIN_OUTPUT_OPTION) $@ $(CY_TOOLCHAIN_MAPFILE)$(CY_BUILD_MAPFILE) \
	$(CY_TOOLCHAIN_OBJRSPFILE)$(CY_CONFIG_DIR)/objlist.rsp \
	$(CY_TOOLCHAIN_STARTGROUP) $(CY_RECIPE_EXTRA_LIBS) $(CY_BUILD_ALL_LIB_FILES) $(CY_BUILD_SHAREDLIB_LIBLIST) $(CY_TOOLCHAIN_ENDGROUP)

#
# Archiver arguments
#
CY_BUILD_ARCHIVE=$(AR) $(CY_RECIPE_ARFLAGS) $(CY_TOOLCHAIN_OUTPUT_OPTION) $@ $(CY_TOOLCHAIN_OBJRSPFILE)$(CY_CONFIG_DIR)/objlist.rsp 


################################################################################
# Dependency construction
################################################################################

#
# Dependency variables for compilation
#
CY_BUILD_COMPILER_DEPS=\
	$(CY_BUILD_COMPILE_AS_UC)\
	$(CY_BUILD_COMPILE_AS_LC)\
	$(CY_BUILD_COMPILE_C)\
	$(CY_BUILD_COMPILE_CPP)\
	$(CY_RECIPE_INCLUDES)

#
# Dependency variables for link/archive
#
CY_BUILD_LINKER_DEPS=\
	$(CY_BUILD_LINK)\
	$(CY_BUILD_ARCHIVE)\
	$(CY_SHAREDLIB_ARTIFACT_EXPORT_LIST)

#
# Read previous build's configuration if one exists
#
CY_BUILD_COMPILER_PREV=$(shell if [ -f "$(CY_CONFIG_DIR)/.cycompiler" ]; then cat $(CY_CONFIG_DIR)/.cycompiler; fi)
CY_BUILD_LINKER_PREV=$(shell if [ -f "$(CY_CONFIG_DIR)/.cylinker" ]; then cat $(CY_CONFIG_DIR)/.cylinker; fi)

#
# Take care of the quotes for the echo command
#
CY_BUILD_COMPILER_DEPS_FORMATTED=$(subst ',,$(subst ",,$(CY_BUILD_COMPILER_DEPS)))
CY_BUILD_LINKER_DEPS_FORMATTED=$(subst ',,$(subst ",,$(CY_BUILD_LINKER_DEPS)))

#
# Create compilation dependency file
#
ifneq ($(strip $(CY_BUILD_COMPILER_DEPS_FORMATTED)),$(strip $(CY_BUILD_COMPILER_PREV)))
ifeq ($(CY_BUILD_COMPILER_PREV),)
$(shell mkdir -p $(CY_CONFIG_DIR))
endif
$(shell echo "$(CY_BUILD_COMPILER_DEPS_FORMATTED)" > $(CY_CONFIG_DIR)/.cycompiler)
endif

#
# Create link dependency file
#
ifneq ($(strip $(CY_BUILD_LINKER_DEPS_FORMATTED)),$(strip $(CY_BUILD_LINKER_PREV)))
ifneq ($(CY_BUILD_LINKER_PREV),)
$(shell mkdir -p $(CY_CONFIG_DIR))
endif
$(shell echo "$(CY_BUILD_LINKER_DEPS_FORMATTED)" > $(CY_CONFIG_DIR)/.cylinker)
endif


################################################################################
# Application source Compilation
################################################################################

# Compile .S source
$(CY_CONFIG_DIR)/%.$(CY_TOOLCHAIN_SUFFIX_O) : $(CY_INTERNAL_APP_PATH)/%.$(CY_TOOLCHAIN_SUFFIX_S)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling app file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_AS_UC) $@ $<

# Compile .s source
$(CY_CONFIG_DIR)/%.$(CY_TOOLCHAIN_SUFFIX_O) : $(CY_INTERNAL_APP_PATH)/%.$(CY_TOOLCHAIN_SUFFIX_s)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling app file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_AS_LC) $@ $<

# Compile .c source
$(CY_CONFIG_DIR)/%.$(CY_TOOLCHAIN_SUFFIX_O) : $(CY_INTERNAL_APP_PATH)/%.$(CY_TOOLCHAIN_SUFFIX_C)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling app file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_C) $@ $<

# Compile .cpp source
$(CY_CONFIG_DIR)/%.$(CY_TOOLCHAIN_SUFFIX_O) : $(CY_INTERNAL_APP_PATH)/%.$(CY_TOOLCHAIN_SUFFIX_CPP)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling app file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_CPP) $@ $<


################################################################################
# ExtApp source Compilation
################################################################################

# Compile .S source
$(CY_CONFIG_DIR)/%.$(CY_TOOLCHAIN_SUFFIX_O) : $(CY_INTERNAL_EXTAPP_PATH)/%.$(CY_TOOLCHAIN_SUFFIX_S)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling extapp file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_AS_UC) $@ $<

# Compile .s source
$(CY_CONFIG_DIR)/%.$(CY_TOOLCHAIN_SUFFIX_O) : $(CY_INTERNAL_EXTAPP_PATH)/%.$(CY_TOOLCHAIN_SUFFIX_s)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling extapp file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_AS_LC) $@ $<

# Compile .c source
$(CY_CONFIG_DIR)/%.$(CY_TOOLCHAIN_SUFFIX_O) : $(CY_INTERNAL_EXTAPP_PATH)/%.$(CY_TOOLCHAIN_SUFFIX_C)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling extapp file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_C) $@ $<

# Compile .cpp source
$(CY_CONFIG_DIR)/%.$(CY_TOOLCHAIN_SUFFIX_O) : $(CY_INTERNAL_EXTAPP_PATH)/%.$(CY_TOOLCHAIN_SUFFIX_CPP)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling extapp file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_CPP) $@ $<


################################################################################
# Generated Source Compilation
################################################################################

# Compile .S source
$(CY_CONFIG_DIR)/generated/%.$(CY_TOOLCHAIN_SUFFIX_O) : $(CY_GENERATED_DIR)/%.$(CY_TOOLCHAIN_SUFFIX_S)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling generated file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_AS_UC) $@ $<

# Compile .s source
$(CY_CONFIG_DIR)/generated/%.$(CY_TOOLCHAIN_SUFFIX_O) : $(CY_GENERATED_DIR)/%.$(CY_TOOLCHAIN_SUFFIX_s)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling generated file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_AS_LC) $@ $<

# Compile .c source
$(CY_CONFIG_DIR)/generated/%.$(CY_TOOLCHAIN_SUFFIX_O) : $(CY_GENERATED_DIR)/%.$(CY_TOOLCHAIN_SUFFIX_C)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling generated file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_C) $@ $<

# Compile .cpp source
$(CY_CONFIG_DIR)/generated/%.$(CY_TOOLCHAIN_SUFFIX_O) : $(CY_GENERATED_DIR)/%.$(CY_TOOLCHAIN_SUFFIX_CPP)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling generated file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_CPP) $@ $<


################################################################################
# User source Compilation
################################################################################

# Compile .S source
$(CY_CONFIG_DIR)/user/%.$(CY_TOOLCHAIN_SUFFIX_O) : %.$(CY_TOOLCHAIN_SUFFIX_S)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling user file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_AS_UC) $@ $<

# Compile .s source
$(CY_CONFIG_DIR)/user/%.$(CY_TOOLCHAIN_SUFFIX_O) : %.$(CY_TOOLCHAIN_SUFFIX_s)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling user file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_AS_LC) $@ $<

# Compile .c source
$(CY_CONFIG_DIR)/user/%.$(CY_TOOLCHAIN_SUFFIX_O) : %.$(CY_TOOLCHAIN_SUFFIX_C)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling user file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_C) $@ $<

# Compile .cpp source
$(CY_CONFIG_DIR)/user/%.$(CY_TOOLCHAIN_SUFFIX_O) : %.$(CY_TOOLCHAIN_SUFFIX_CPP)
ifneq ($(CY_MAKE_IDE),eclipse)
	$(info $(CY_INDENT)Compiling user file $(CY_COMPILE_PRINT))
else
	$(info Compiling $< $(CY_RECIPE_DEFINES) $(sort $(CY_RECIPE_INCLUDES) $(call CY_MACRO_ECLIPSE_PRINT,$(CY_SHAREDLIB_INCLUDES_EXPORT_LIST))))
endif
	$(CY_NOISE)$(CY_BUILD_COMPILE_CPP) $@ $<


################################################################################
# Prebuild, Postbuild and Link
################################################################################

#
# Top-level application dependency
#
app: CY_BUILD_sentinel

#
# Print information before we start the build
#
CY_BUILD_preprint: | $(CY_SHAREDLIB_INCLUDES_EXPORT_LIST) $(CY_SHAREDLIB_LIBS_EXPORT_LIST) $(CY_SHAREDLIB_ARTIFACT_EXPORT_LIST)
	$(info )
	$(info ==============================================================================)
	$(info = Building application =)
	$(info ==============================================================================)

#
# Create the directories needed to do the build
#
CY_BUILD_mkdirs: CY_BUILD_preprint
	$(CY_NOISE)mkdir -p $(CY_BUILD_DIRS) $(CY_CMD_TERM)
ifeq ($(CY_RECIPE_GENERATED_FLAG),TRUE)
	$(CY_NOISE)mkdir -p $(CY_GENERATED_DIR) $(CY_CMD_TERM)
endif

#
# Run BSP pre-build step
#
CY_BUILD_bsp_prebuild: CY_BUILD_mkdirs
	$(CY_BSP_PREBUILD)

#
# Run application pre-build step
#
CY_BUILD_app_prebuild: CY_BUILD_bsp_prebuild
	$(PREBUILD)

#
# Run generate source step
#
CY_BUILD_gensrc: CY_BUILD_app_prebuild
ifneq ($(CY_SEARCH_RESOURCE_FILES),)
	@echo $(CY_RECIPE_RESOURCE_FILES) > $(CY_GENERATED_DIR)/resources.cyrsc
endif
ifeq ($(CY_RECIPE_GENERATED_FLAG),TRUE)
	$(CY_NOISE)$(CY_RECIPE_GENSRC) $(CY_CMD_TERM)
	$(info Generated $(words $(CY_RECIPE_GENERATED)) source file(s))
endif

#
# Add dependancy to support parallel builds
#
$(CY_BUILD_GENSRC_C_FILES): | CY_BUILD_gensrc

#
# Run pre-build step
#
CY_BUILD_prebuild: CY_BUILD_gensrc
	$(CY_NOISE)$(CY_RECIPE_PREBUILD) $(CY_CMD_TERM)

#
# Print before compilation
#
CY_BUILD_precompile: CY_BUILD_prebuild
	$(info Building $(words $(CY_BUILD_ALL_OBJ_FILES)) file(s))
	@echo $(CY_RECIPE_INCLUDES) | tr " " "\n" > $(CY_CONFIG_DIR)/inclist.rsp; \
	 echo $(CY_BUILD_ALL_OBJ_FILES) | tr " " "\n"  > $(CY_CONFIG_DIR)/objlist.rsp; \
	 echo $(CY_BUILD_ALL_LIB_FILES) | tr " " "\n"  > $(CY_CONFIG_DIR)/liblist.rsp;

#
# Dependencies for compilation
#
$(CY_BUILD_ALL_OBJ_FILES): | CY_BUILD_precompile 
$(CY_BUILD_ALL_OBJ_FILES): $(CY_CONFIG_DIR)/.cycompiler $(CY_SHAREDLIB_INCLUDES_EXPORT_LIST)

#
# Dependencies for link
#
$(CY_BUILD_TARGET): | CY_BUILD_precompile
$(CY_BUILD_TARGET): $(CY_CONFIG_DIR)/.cylinker $(CY_SHAREDLIB_LIBS_EXPORT_LIST) $(CY_SHAREDLIB_ARTIFACT_EXPORT_LIST)

#
# Link/archive the application
#
ifneq ($(LIBNAME),)
$(CY_BUILD_TARGET): $(CY_BUILD_ALL_OBJ_FILES) $(CY_BUILD_ALL_LIB_FILES)
ifneq ($(strip $(CY_BUILD_ALL_OBJ_FILES) $(CY_BUILD_ALL_LIB_FILES)),)
	$(info $(CY_INDENT)Archiving output file $(notdir $@))
	$(CY_NOISE)$(CY_BUILD_ARCHIVE) $(CY_CMD_TERM)
endif
else
$(CY_BUILD_TARGET): $(CY_BUILD_ALL_OBJ_FILES) $(CY_BUILD_ALL_LIB_FILES) $(LINKER_SCRIPT) $(CY_SHAREDLIB_TIMESTAMP)
ifneq ($(SEARCH_LIBS_AND_INCLUDES),)
	@libArray=($(CY_SHAREDLIB_LIBS_EXPORT_LIST)); \
	for libFile in "$${libArray[@]}"; do \
		if [ "$$libFile" -nt "$(CY_BUILD_TARGET)" ]; then \
			relink=true; \
		fi; \
	done; \
	artifactArray=($(CY_SHAREDLIB_ARTIFACT_EXPORT_LIST)); \
	for artifactFile in "$${artifactArray[@]}"; do \
		if [ "$$artifactFile" -nt "$(CY_BUILD_TARGET)" ]; then \
			relink=true; \
		fi; \
	done; \
	if [[ "$?" == *".$(CY_TOOLCHAIN_SUFFIX_O)"* ]] || [[ "$?" == *".$(CY_TOOLCHAIN_SUFFIX_A)"* ]]; then \
		relink=true; \
	fi; \
	if [ $$relink ]; then \
		echo "    Linking output file $(notdir $@)"; \
		$(CY_BUILD_LINK); \
	fi
else
	$(info $(CY_INDENT)Linking output file $(notdir $@))
	$(CY_NOISE)$(CY_BUILD_LINK)
endif
endif

#
# Perform post-build step
#
CY_BUILD_postbuild: $(CY_BUILD_TARGET)
	$(CY_NOISE)$(CY_RECIPE_POSTBUILD) $(CY_CMD_TERM)

#
# Run BSP post-build step
#
CY_BUILD_bsp_postbuild: CY_BUILD_postbuild
	$(CY_BSP_POSTBUILD)

#
# Perform application post-build step
#
CY_BUILD_app_postbuild: CY_BUILD_bsp_postbuild
	$(POSTBUILD)

#
# Perform the post build print step, basically stating we are done
#
CY_BUILD_postprint: CY_BUILD_app_postbuild
	$(info ==============================================================================)
	$(info = Build complete =)
	$(info ==============================================================================)
	$(info )

#
# Create an artifact sentinel file for shared libs
#
ifneq ($(LIBNAME),)
CY_BUILD_sentinel: CY_BUILD_postprint
ifneq ($(strip $(CY_BUILD_ALL_OBJ_FILES) $(CY_BUILD_ALL_LIB_FILES)),)
	@echo $(LIBNAME).$(CY_TOOLCHAIN_SUFFIX_ARCHIVE) > $(CY_CONFIG_DIR)/artifact.rsp
else
	@touch $(CY_CONFIG_DIR)/artifact.rsp
endif
else
CY_BUILD_sentinel: CY_BUILD_postprint

endif

#
# Include generated dependency files (if rebuilding)
#
-include $(CY_DEPENDENCY_FILES)

#
# Indicate all phony targets that should be built regardless
#
.PHONY: app $(CY_SHAREDLIB_LIST)
.PHONY: CY_BUILD_mkdirs
.PHONY: CY_BUILD_prebuild CY_BUILD_app_prebuild CY_BUILD_bsp_prebuild
.PHONY: CY_BUILD_postbuild CY_BUILD_app_postbuild CY_BUILD_bsp_postbuild
.PHONY: CY_BUILD_gensrc
.PHONY: CY_BUILD_genresource
.PHONY: CY_BUILD_preprint
.PHONY: CY_BUILD_postprint 
.PHONY: CY_BUILD_sentinel
