################################################################################
# \file help.mk
# \version 1.0
#
# \brief
# Default help documentation
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
# General Targets
#
CY_HELP_all_VERBOSE=This target is equivalent to the "build" target.
CY_HELP_getlibs_VERBOSE=The repos are cloned to the libs directory. By default, this directory is\
					created in the application directory. It may be directed to other locations using\
					the CY_GETLIBS_PATH variable.
CY_HELP_build_VERBOSE=The build process involves source auto-discovery, code generation, prebuilds, and postbuilds.\
					For faster incremental builds, use the "qbuild" target to skip the auto-generation step. 
CY_HELP_qbuild_VERBOSE=When no other sources need to be auto-discovered, this target can be used to skip\
					the auto-discovery step for a faster incremental build.
CY_HELP_program_VERBOSE=The build process performs the same operations as the "build" target. Upon completion,\
					the artifact is programmed to the board.
CY_HELP_qprogram_VERBOSE=This target allows programming an existing artifact to the board without a build step.
CY_HELP_debug_VERBOSE=Once the GDB server is launched, another shell should be opened to launch a GDB client.
CY_HELP_qdebug_VERBOSE=Once the GDB server is launched, another shell should be opened to launch a GDB client.
CY_HELP_clean_VERBOSE=The directory and all its contents are deleted from disk.
CY_HELP_help_VERBOSE=Use the CY_HELP=<NAME of target of variable> to see the verbose documentation for a\
					particular target or a variable.

#
# Configurator Targets
#
CY_HELP_open_VERBOSE=This target accepts two variables – CY_OPEN_TYPE and CY_OPEN_FILE. At least one of\
					these must be provided. The tool can be specified by setting the CY_OPEN_TYPE variable.\
					A specific file can also be passed using the CY_OPEN_FILE variable. If only CY_OPEN_FILE is given,\
					the build system will launch the default tool associated with the file’s extension.
CY_HELP_config_VERBOSE=If no existing device-configuration files are found, the configurator is launched to create one.
CY_HELP_config_bt_VERBOSE=If no existing bt-configuration files are found, the configurator is launched to create one.
CY_HELP_config_usbdev_VERBOSE=If no existing usbdev-configuration files are found, the configurator is launched to create one.

#
# Utility Targets
#
CY_HELP_eclipse_VERBOSE=This target expects the CY_IDE_PRJNAME variable to be set to the name of the project\
					as defined in the eclipse IDE. E.g. "make eclipse CY_IDE_PRJNAME=AppV1". If this variable\
					is not defined, it will use the APPNAME for the launch configs.
CY_HELP_check_VERBOSE=Not all tools are necessary for every build recipe. This target allows the user\
					to get an idea of which tools are missing if a build fails in an unexpected way.
CY_HELP_get_app_info_VERBOSE=The file types can be specified by setting the\
					CY_CONFIG_FILE_EXT variable. E.g. "make get_app_info "CY_CONFIG_FILE_EXT=modus cybt cyusbdev"".
CY_HELP_get_env_info_VERBOSE=This allows a quick printout of the current app repo and the "make" and "git"\
					tool locations and versions.
CY_HELP_printlibs_VERBOSE=This target parses through the library repos and prints the SHA1 commit id for each library.\
					It also shows whether the repo is clean (no changes) or dirty (modified or new files).

#
# Basic configuration
#
CY_HELP_TARGET=Specifies the target board/kit. E.g. CY8CPROTO-062-4343W.
CY_HELP_TARGET_VERBOSE=Currently available target(s) in this application is/are, [ $(CY_TARGET_AVAILABLE) ].
CY_HELP_APPNAME=Specifies the name of the application. E.g. AppV1.
CY_HELP_APPNAME_VERBOSE=This variable signifies that the application will build an artifact that is\
				intended for a target board. For applications that need to build into an archive (library),\
				use the LIBNAME variable.
CY_HELP_LIBNAME=Specifies the name of the library application. E.g. LibV1.
CY_HELP_LIBNAME_VERBOSE=This variable signifies that the application will build an archive (library).\
				These library applications can be added as a dependency to an artifact producing application\
				using the SEARCH_LIBS_AND_INCLUDES variable.
CY_HELP_TOOLCHAIN=Specifies the toolchain for building the application. E.g. GCC_ARM.
CY_HELP_TOOLCHAIN_VERBOSE=Supported toolchains for this target are, [ $(CY_SUPPORTED_TOOLCHAINS) ].
CY_HELP_CONFIG=Specifies the configuration option for the build [Debug Release].
CY_HELP_CONFIG_VERBOSE=The CONFIG variable is not limited to Debug/Release. It can be\
						other values. However in those instances, the build system will not configure the optimization flags.\
						Debug=lowest optimization, Release=highest optimization. The optimization flags are toolchain-specific.\
						If you go with your custom config then you can manually set the optimization flag in the CFLAGS.
CY_HELP_VERBOSE=Specifies whether the build is silent [false] or verbose [true].
CY_HELP_VERBOSE_VERBOSE=Setting VERBOSE to true may help in debuggging build errors/warnings.

#
# Advanced configuration
#
CY_HELP_SOURCES=Specifies C/C++ and assembly files not under the working directory.
CY_HELP_SOURCES_VERBOSE=This can be used to include files external to the application directory.
CY_HELP_INCLUDES=Specifies include paths not under the working directory.
CY_HELP_INCLUDES_VERBOSE=Note: These MUST NOT have -I prepended.
CY_HELP_DEFINES=Specifies additional defines passed to the compiler.
CY_HELP_DEFINES_VERBOSE=Note: These MUST NOT have -D prepended.
CY_HELP_VFP_SELECT=Selects hard/soft ABI for floating-point operations [softfp hardfp].
CY_HELP_VFP_SELECT_VERBOSE=If not defined, this value defaults to softfp.
CY_HELP_CFLAGS=Prepends additional C compiler flags. 
CY_HELP_CFLAGS_VERBOSE=Note: If the entire C compiler flags list needs to be replaced, define the\
						CY_RECIPE_CFLAGS make variable with the desired C flags.
CY_HELP_CXXFLAGS=Prepends additional C++ compiler flags. 
CY_HELP_CXXFLAGS_VERBOSE=Note: If the entire C++ compiler flags list needs to be replaced, define the\
						CY_RECIPE_CXXFLAGS make variable with the desired C++ flags.
CY_HELP_ASFLAGS=Prepends additional assembler flags. 
CY_HELP_ASFLAGS_VERBOSE=Note: If the entire assembler flags list needs to be replaced, define the\
						CY_RECIPE_ASFLAGS make variable with the desired assembly flags.
CY_HELP_LDFLAGS=Prepends additional linker flags. 
CY_HELP_LDFLAGS_VERBOSE=Note: If the entire linker flags list needs to be replaced, define the\
						CY_RECIPE_LDFLAGS make variable with the desired linker flags.
CY_HELP_LDLIBS=Includes application-specific prebuilt libraries.
CY_HELP_LDLIBS_VERBOSE=Note: If additional libraries need to be added using -l or -L, add to the\
						CY_RECIPE_EXTRA_LIBS make variable.
CY_HELP_LINKER_SCRIPT=Specifies a custom linker script location.
CY_HELP_LINKER_SCRIPT_VERBOSE=This linker script overrides the default. Note: Additional\
					linker scripts can be added for GCC via the LDFLAGS variable as a -L option.
CY_HELP_PREBUILD=Specifies the location of a custom prebuild step and its arguments.
CY_HELP_PREBUILD_VERBOSE=This operation runs before the build recipe's prebuild step.\
					$(CY_NEWLINE)Note: BSPs can also define a prebuild step. This runs before the\
					application prebuild step.\
					$(CY_NEWLINE)Note: If the default prebuild step needs to be replaced, define the\
					CY_RECIPE_PREBUILD make variable with the desired prebuild step.
CY_HELP_POSTBUILD=Specifies the location of a custom postbuild step and its arguments.
CY_HELP_POSTBUILD_VERBOSE=This operation runs after the build recipe's postbuild step.\
					$(CY_NEWLINE)Note: BSPs can also define a postbuild step. This runs before the\
					application postbuild step.\
					$(CY_NEWLINE)Note: If the default postbuild step needs to be replaced, define the\
					CY_RECIPE_POSTBUILD make variable with the desired postbuild step.
CY_HELP_COMPONENTS=Adds component-specific files to the build.
CY_HELP_COMPONENTS_VERBOSE=Create a directory named COMPONENT_<VALUE> and place your files.\
					Then include the <VALUE> to this make variable to have that feature library\
					be included in the build. E.g. Create a directory named COMPONENT_ACCELEROMETER.\
					Then include it in the make variable. COMPONENT=ACCELEROMETER. If the make variable\
					does not include the <VALUE>, then that library will not be included in the build.\
					$(CY_NEWLINE)Note: If the default COMPONENT list must be overridden, defined the CY_COMPONENT_LIST\
					make variable with the list of component values.
CY_HELP_DISABLE_COMPONENTS=Removes component-specific files from the build.
CY_HELP_DISABLE_COMPONENTS_VERBOSE=Include a <VALUE> to this make variable to have that feature library\
					be excluded in the build. E.g. To exclude the contents of COMPONENT_BSP_DESIGN_MODUS\
					directory, set DISABLE_COMPONENTS=BSP_DESIGN_MODUS.
CY_HELP_SEARCH_LIBS_AND_INCLUDES=List of dependent library application paths. E.g. ../bspLib.
CY_HELP_SEARCH_LIBS_AND_INCLUDES_VERBOSE=An artifact producing application (Defined by setting APPNAME),\
					can have a dependency on library applications (Defined by setting LIBNAME). This variable\
					defines those dependencies for the artifact producing application. The actual build invocation\
					of those libraries are handled at the application level by defining the "shared_libs" target. E.g.\
					$(CY_NEWLINE)$(CY_NEWLINE)shared_libs: $(CY_NEWLINE)$(CY_INDENT)make -C ../bspLib build -j

#
# Path variables
#
CY_HELP_CY_APP_PATH=Relative path to the top-level of application. E.g. ./
CY_HELP_CY_APP_PATH_VERBOSE=Settings this path to other than ./ allows the auto-discovery mechanism\
					to search from a root directory location that is higher than the app directory.\
					E.g. CY_APP_PATH=../../ allows auto-discovery of files from a location that is\
					two directories above the location of ./Makefile.
CY_HELP_CY_BASELIB_PATH=Relative path to the base library. E.g. ./libs/psoc6make
CY_HELP_CY_BASELIB_PATH_VERBOSE=This directory must be relative to CY_APP_PATH. It defines the location\
					of the library containing the recipe make files, where the expected directory structure\
					is <CY_BASELIB_PATH>/make. All applications must set the location of the base library.
CY_HELP_CY_GETLIBS_PATH=Absolute path to the intended location of libs directory.
CY_HELP_CY_GETLIBS_PATH_VERBOSE=The library repos are cloned into a directory named, libs (Default: <CY_APP_PATH>/libs).\
					Setting this variable allows specifying the location of the libs directory to elsewhere on disk. 
CY_HELP_CY_GETLIBS_SEARCH_PATH=Relative path to the top directory for "getlibs" operation.
CY_HELP_CY_GETLIBS_SEARCH_PATH_VERBOSE=The getlibs operation by default executes at the location of the CY_APP_PATH. This can\
					be overridden by specifying this variable to point to a specific location.
CY_HELP_CY_DEVICESUPPORT_PATH=Relative path to the devicesupport.xml file.
CY_HELP_CY_DEVICESUPPORT_PATH_VERBOSE=This path specifies the location of the devicesupport.xml file for device-configurators.\
					It is used when the configurator needs to be run in a multi-app scenario.
CY_HELP_CY_SHARED_PATH=Relative path to the location of shared .lib files.
CY_HELP_CY_SHARED_PATH_VERBOSE=This variable is used in shared library applications to point to the location of external .lib files.
CY_HELP_CY_COMPILER_PATH=Absolute path to the compiler (Default: GCC_ARM in CY_TOOLS_DIR).
CY_HELP_CY_COMPILER_PATH_VERBOSE=Setting this path allows custom toolchains to be used instead of the defaults.\
					This should be the location of the /bin directory containing the compiler, assembler and\
					linker. E.g. CY_COMPILER_PATH="C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.2/arm/bin".
CY_HELP_CY_TOOLS_DIR=Absolute path to the tools root directory.
CY_HELP_CY_TOOLS_DIR_VERBOSE=Applications must specify the directory of the tools install, which contains the\
					root makefile and the necessary tools and scripts to build an application. Application Makefiles\
					are configured to automatically search in the standard locations for various platforms.\
					If the tools are not located in the standard location, you may explicitly set this.
CY_HELP_CY_BUILD_LOCATION=Absolute path to the build output directory (Default: pwd/build).
CY_HELP_CY_BUILD_LOCATION_VERBOSE=The build output directory is structured as /TARGET/CONFIG/. Setting this variable\
					allows the build artifacts to be located in the directory pointed to by this variable.
CY_HELP_CY_EXTAPP_PATH=Relative path to an external app directory. E.g. ../external
CY_HELP_CY_EXTAPP_PATH_VERBOSE=This directory must be relative to CY_APP_PATH. Setting this path\
					allows incorporating files external to CY_APP_PATH. E.g. CY_EXTAPP_PATH=../external\
					lets the auto-discovery to pull in the contents of ../external directory into the build.\
					$(CY_NEWLINE)Note: This variable is only supported in CLI. Use the shared_libs mechanism and\
					CY_HELP_SEARCH_LIBS_AND_INCLUDES for tools and IDE support.

#
# Miscellaneous variables
#
CY_HELP_CY_IGNORE=Adds to the directory and file ignore list. E.g. ./file1.c ./inc1
CY_HELP_CY_IGNORE_VERBOSE=Directories and files listed in this variable are ignored in the auto-discovery.\
					This mechanism works in combination with any existing .cyignore files in the application.
CY_HELP_CY_IDE_PRJNAME=Name of the eclipse IDE project.
CY_HELP_CY_IDE_PRJNAME_VERBOSE=This variable can be used to define the file and target project name when\
					generating eclipse launch configurations in the "eclipse" target.
CY_HELP_CY_CONFIG_FILE_EXT=Specifies the configurator file extension. E.g. modus
CY_HELP_CY_CONFIG_FILE_EXT_VERBOSE=This variable accepts a space-separated list of configurator file extensions\
					that should be searched for when running the "get_app_info" target.
CY_HELP_CY_SKIP_RECIPE=Skip including the recipe make files.
CY_HELP_CY_SKIP_RECIPE_VERBOSE=This allows the application to not include any recipe makefiles and only\
					include the start.mk file from the tools install.
CY_HELP_CY_SUPPORTED_TOOL_TYPES=Defines the supported tools for a BSP.
CY_HELP_CY_SUPPORTED_TOOL_TYPES_VERBOSE=BSPs can define the supported tools that can be launched using the\
					"open" target. The supported tool types are $(CY_OPEN_TYPE_LIST).
CY_HELP_CY_LIBS_SEARCH_DEPTH=Search depth for .lib files (Default: 5).
CY_HELP_CY_LIBS_SEARCH_DEPTH_VERBOSE=This variable controls how deep (directory) the search mechanism in getlibs looks for .lib files.\
					$(CY_NEWLINE)Note: Deeper searches take longer to process.
CY_HELP_CY_UTILS_SEARCH_DEPTH=Search depth for .cyignore and TARGET.mk files (Default: 5).
CY_HELP_CY_UTILS_SEARCH_DEPTH_VERBOSE=This variable controls how deep (directory) the search mechanism looks for .cyignore\
					and TARGET.mk files. Min=1, Max=9.\
					$(CY_NEWLINE)Note: Deeper searches take longer to process.
CY_HELP_CY_EXTRA_INCLUDES=Specifies additional makefiles to add to the build.
CY_HELP_CY_EXTRA_INCLUDES_VERBOSE=The application Makefile cannot add additional make files directly. Instead, use\
					this variable to include these in the build. E.g. CY_EXTRA_INCLUDES=./custom1.mk ./custom2.mk
CY_HELP_TOOLCHAIN_MK_PATH=Specifies the location of a custom TOOLCHAIN makefile.
CY_HELP_TOOLCHAIN_MK_PATH_VERBOSE=Defining this path allows the build system to use a custom TOOLCHAIN.mk\
					pointed to by this variable.\
					$(CY_NEWLINE)Note: The make variables in this file should match the\
					variables used in existing TOOLCHAIN.mk files.  

# Pass these to CY_HELP to get the full verbose info
CY_HELP_TARGETS_ALL=all getlibs build qbuild program qprogram debug qdebug clean help open config config_bt config_usbdev \
					eclipse check get_app_info get_env_info printlibs
CY_HELP_BASIC_CFG_ALL=TARGET APPNAME LIBNAME TOOLCHAIN CONFIG VERBOSE
CY_HELP_ADVANCED_CFG_ALL=SOURCES INCLUDES DEFINES VFP_SELECT CFLAGS CXXFLAGS ASFLAGS LDFLAGS LDLIBS LINKER_SCRIPT \
					PREBUILD POSTBUILD COMPONENTS DISABLE_COMPONENTS SEARCH_LIBS_AND_INCLUDES
CY_HELP_PATHS_ALL=CY_APP_PATH CY_BASELIB_PATH CY_EXTAPP_PATH CY_GETLIBS_PATH CY_GETLIBS_SEARCH_PATH CY_DEVICESUPPORT_PATH \
					CY_SHARED_PATH CY_COMPILER_PATH CY_TOOLS_DIR CY_BUILD_LOCATION
CY_HELP_MISC_ALL=CY_IGNORE CY_IDE_PRJNAME CY_CONFIG_FILE_EXT CY_SKIP_RECIPE CY_SUPPORTED_TOOL_TYPES CY_LIBS_SEARCH_DEPTH \
					CY_UTILS_SEARCH_DEPTH CY_EXTRA_INCLUDES TOOLCHAIN_MK_PATH
CY_HELP_PRINT_ALL=$(CY_HELP_TARGETS_ALL) $(CY_HELP_BASIC_CFG_ALL) $(CY_HELP_ADVANCED_CFG_ALL) $(CY_HELP_PATHS_ALL) $(CY_HELP_MISC_ALL)


help_default:
ifneq ($(CY_HELP),)
	@echo 
	$(foreach topic,$(CY_HELP),\
	$(info $(CY_NEWLINE)Topic-specific help for "$(topic)")\
	$(info $(CY_SPACE)$(CY_SPACE)Brief: $(CY_HELP_$(topic)))\
	$(info $(CY_SPACE)$(CY_SPACE)Verbose: $(CY_HELP_$(topic)_VERBOSE)))
else
	@echo 
	$(info                                                                                    )
	$(info ==============================================================================     )
	$(info $(CY_SPACE)Cypress Build System                                                    )
	$(info ==============================================================================     )
	$(info $(CY_SPACE)Copyright 2018-2019 Cypress Semiconductor Corporation                   )
	$(info $(CY_SPACE)SPDX-License-Identifier: Apache-2.0                                     )
	$(info                                                                                    )
	$(info $(CY_SPACE)Licensed under the Apache License, Version 2.0 (the "License");         )
	$(info $(CY_SPACE)you may not use this file except in compliance with the License.        )
	$(info $(CY_SPACE)You may obtain a copy of the License at                                 )
	$(info                                                                                    )
	$(info $(CY_SPACE)$(CY_SPACE)    http://www.apache.org/licenses/LICENSE-2.0               )
	$(info                                                                                    )
	$(info $(CY_SPACE)Unless required by applicable law or agreed to in writing, software     )
	$(info $(CY_SPACE)distributed under the License is distributed on an "AS IS" BASIS,       )
	$(info $(CY_SPACE)WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.)
	$(info $(CY_SPACE)See the License for the specific language governing permissions and     )
	$(info $(CY_SPACE)limitations under the License.                                          )
	$(info ==============================================================================     )
	$(info                                                                                    )
	$(info $(CY_SPACE)This is the help documentation for the Cypress build system.            )
	$(info $(CY_SPACE)It lists the supported make targets and make variables.                 )
	$(info                                                                                    )
	$(info $(CY_SPACE)Usage:   make [target][variable]                                        )
	$(info $(CY_SPACE)Example: make help CY_HELP=TOOLCHAIN                                    )
	$(info                                                               )
	$(info =======================================                       )
	$(info $(CY_SPACE)General make targets                               )
	$(info =======================================                       )
	$(info $(CY_SPACE)all                 $(CY_HELP_all))
	$(info $(CY_SPACE)getlibs             $(CY_HELP_getlibs))
	$(info $(CY_SPACE)build               $(CY_HELP_build))
	$(info $(CY_SPACE)qbuild              $(CY_HELP_qbuild))
	$(info $(CY_SPACE)program             $(CY_HELP_program))
	$(info $(CY_SPACE)qprogram            $(CY_HELP_qprogram))
	$(info $(CY_SPACE)debug               $(CY_HELP_debug))
	$(info $(CY_SPACE)qdebug              $(CY_HELP_qdebug))
	$(info $(CY_SPACE)clean               $(CY_HELP_clean))
	$(info $(CY_SPACE)help                $(CY_HELP_help))
	$(info                                                               )
	$(info =======================================                       )
	$(info $(CY_SPACE)Tools make targets                                 )
	$(info =======================================                       )
	$(info $(CY_SPACE)open                $(CY_HELP_open))
	$(info $(CY_SPACE)config              $(CY_HELP_config))
	$(info $(CY_SPACE)config_bt           $(CY_HELP_config_bt))
	$(info $(CY_SPACE)config_usbdev       $(CY_HELP_config_usbdev))
	$(info                                                               )
	$(info =======================================                       )
	$(info $(CY_SPACE)Utility make targets                               )
	$(info =======================================                       )
	$(info $(CY_SPACE)eclipse             $(CY_HELP_eclipse))
	$(info $(CY_SPACE)check               $(CY_HELP_check))
	$(info $(CY_SPACE)get_app_info        $(CY_HELP_get_app_info))
	$(info $(CY_SPACE)get_env_info        $(CY_HELP_get_env_info))
	$(info $(CY_SPACE)printlibs           $(CY_HELP_printlibs))
	$(info                                                               )
	$(info =======================================                       )
	$(info $(CY_SPACE)Basic configuration make variables                 )
	$(info =======================================                       )
	$(info $(CY_SPACE)TARGET              $(CY_HELP_TARGET))
	$(info $(CY_SPACE)APPNAME             $(CY_HELP_APPNAME))
	$(info $(CY_SPACE)LIBNAME             $(CY_HELP_LIBNAME))
	$(info $(CY_SPACE)TOOLCHAIN           $(CY_HELP_TOOLCHAIN))
	$(info $(CY_SPACE)CONFIG              $(CY_HELP_CONFIG))
	$(info $(CY_SPACE)VERBOSE             $(CY_HELP_VERBOSE))
	$(info                                                               )
	$(info =======================================                       )
	$(info $(CY_SPACE)Advanced configuration make variables              )
	$(info =======================================                       )
	$(info $(CY_SPACE)SOURCES             $(CY_HELP_SOURCES))
	$(info $(CY_SPACE)INCLUDES            $(CY_HELP_INCLUDES))
	$(info $(CY_SPACE)DEFINES             $(CY_HELP_DEFINES))
	$(info $(CY_SPACE)VFP_SELECT          $(CY_HELP_VFP_SELECT))
	$(info $(CY_SPACE)CFLAGS              $(CY_HELP_CFLAGS))
	$(info $(CY_SPACE)CXXFLAGS            $(CY_HELP_CXXFLAGS))
	$(info $(CY_SPACE)ASFLAGS             $(CY_HELP_ASFLAGS))
	$(info $(CY_SPACE)LDFLAGS             $(CY_HELP_LDFLAGS))
	$(info $(CY_SPACE)LDLIBS              $(CY_HELP_LDLIBS))
	$(info $(CY_SPACE)LINKER_SCRIPT       $(CY_HELP_LINKER_SCRIPT))
	$(info $(CY_SPACE)PREBUILD            $(CY_HELP_PREBUILD))
	$(info $(CY_SPACE)POSTBUILD           $(CY_HELP_POSTBUILD))
	$(info $(CY_SPACE)COMPONENTS          $(CY_HELP_COMPONENTS))
	$(info $(CY_SPACE)DISABLE_COMPONENTS  $(CY_HELP_DISABLE_COMPONENTS))
	$(info $(CY_SPACE)SEARCH_LIBS_AND_INCLUDES  $(CY_HELP_SEARCH_LIBS_AND_INCLUDES))
	$(info                                                               )
	$(info =======================================                       )
	$(info $(CY_SPACE)Path make variables                                )
	$(info =======================================                       )
	$(info $(CY_SPACE)CY_APP_PATH         $(CY_HELP_CY_APP_PATH))
	$(info $(CY_SPACE)CY_BASELIB_PATH     $(CY_HELP_CY_BASELIB_PATH))
	$(info $(CY_SPACE)CY_EXTAPP_PATH      $(CY_HELP_CY_EXTAPP_PATH))
	$(info $(CY_SPACE)CY_GETLIBS_PATH     $(CY_HELP_CY_GETLIBS_PATH))
	$(info $(CY_SPACE)CY_GETLIBS_SEARCH_PATH  $(CY_HELP_CY_GETLIBS_SEARCH_PATH))
	$(info $(CY_SPACE)CY_DEVICESUPPORT_PATH  $(CY_HELP_CY_DEVICESUPPORT_PATH))
	$(info $(CY_SPACE)CY_SHARED_PATH      $(CY_HELP_CY_SHARED_PATH))
	$(info $(CY_SPACE)CY_COMPILER_PATH    $(CY_HELP_CY_COMPILER_PATH))
	$(info $(CY_SPACE)CY_TOOLS_DIR        $(CY_HELP_CY_TOOLS_DIR))
	$(info $(CY_SPACE)CY_BUILD_LOCATION   $(CY_HELP_CY_BUILD_LOCATION))
	$(info                                                               )
	$(info =======================================                       )
	$(info $(CY_SPACE)Miscellaneous make variables                       )
	$(info =======================================                       )
	$(info $(CY_SPACE)CY_IGNORE           $(CY_HELP_CY_IGNORE))
	$(info $(CY_SPACE)CY_IDE_PRJNAME      $(CY_HELP_CY_IDE_PRJNAME))
	$(info $(CY_SPACE)CY_CONFIG_FILE_EXT  $(CY_HELP_CY_CONFIG_FILE_EXT))
	$(info $(CY_SPACE)CY_SKIP_RECIPE      $(CY_HELP_CY_SKIP_RECIPE))
	$(info $(CY_SPACE)CY_SUPPORTED_TOOL_TYPES  $(CY_HELP_CY_SUPPORTED_TOOL_TYPES))
	$(info $(CY_SPACE)CY_LIBS_SEARCH_DEPTH  $(CY_HELP_CY_LIBS_SEARCH_DEPTH))
	$(info $(CY_SPACE)CY_UTILS_SEARCH_DEPTH  $(CY_HELP_CY_UTILS_SEARCH_DEPTH))
	$(info $(CY_SPACE)CY_EXTRA_INCLUDES   $(CY_HELP_CY_EXTRA_INCLUDES))
	$(info $(CY_SPACE)TOOLCHAIN_MK_PATH   $(CY_HELP_TOOLCHAIN_MK_PATH))
endif

#
# Identify the phony targets
#
.PHONY: help help_default
