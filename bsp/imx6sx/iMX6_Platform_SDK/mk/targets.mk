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
# Sources and objects
#-------------------------------------------------------------------------------

# Select our object root depending on whether we're building an app or lib.
ifneq "$(APP_NAME)" ""
OBJS_ROOT = $(APP_OBJS_ROOT)
else
OBJS_ROOT = $(LIB_OBJS_ROOT)
endif

# Strip sources.
SOURCES := $(strip $(SOURCES))

# Convert sources list to absolute paths and root-relative paths.
SOURCES_ABS := $(foreach s,$(SOURCES),$(abspath $(s)))
SOURCES_REL := $(subst $(SDK_ROOT)/,,$(SOURCES_ABS))

# Get a list of unique directories containing the source files.
SOURCE_DIRS_ABS := $(sort $(foreach f,$(SOURCES_ABS),$(dir $(f))))
SOURCE_DIRS_REL := $(subst $(SDK_ROOT)/,,$(SOURCE_DIRS_ABS))

OBJECTS_DIRS := $(addprefix $(OBJS_ROOT)/,$(SOURCE_DIRS_REL))

# Filter source files list into separate source types.
C_SOURCES = $(filter %.c,$(SOURCES_REL))
CXX_SOURCES = $(filter %.cpp,$(SOURCES_REL))
ASM_s_SOURCES = $(filter %.s,$(SOURCES_REL))
ASM_S_SOURCES = $(filter %.S,$(SOURCES_REL))

# Convert sources to objects.
OBJECTS_C := $(addprefix $(OBJS_ROOT)/,$(C_SOURCES:.c=.o))
OBJECTS_CXX := $(addprefix $(OBJS_ROOT)/,$(CXX_SOURCES:.cpp=.o))
OBJECTS_ASM := $(addprefix $(OBJS_ROOT)/,$(ASM_s_SOURCES:.s=.o))
OBJECTS_ASM_S := $(addprefix $(OBJS_ROOT)/,$(ASM_S_SOURCES:.S=.o))

PREBUILT_OBJECTS = $(addprefix $(SDK_ROOT)/,$(filter %.o,$(SOURCES_REL)))

# Complete list of all object files.
OBJECTS_ALL := $(sort $(OBJECTS_C) $(OBJECTS_CXX) $(OBJECTS_ASM) $(OBJECTS_ASM_S) $(PREBUILT_OBJECTS))

#-------------------------------------------------------------------------------
# Target library
#-------------------------------------------------------------------------------

# Library where app objects are archived, if used.
LIBAPP = $(APP_OUTPUT_ROOT)/lib$(APP_NAME).a

# Build the target lib path from the lib name.
ifneq "$(TARGET_LIB_NAME)" ""
TARGET_LIB ?= $(LIBS_ROOT)/lib$(TARGET_LIB_NAME).a
else ifeq "$(ARCHIVE_APP_OBJECTS)" "1"
TARGET_LIB ?= $(LIBAPP)
endif

# Construct full path name to application output ELF file.
ifneq "$(APP_NAME)" ""
APP_ELF ?= $(APP_OUTPUT_ROOT)/$(APP_NAME).elf
endif

# Select the output target.
ifneq "$(TARGET_LIB)" ""
# Only use the target lib if there are actually objects to put into it.
ifneq "$(strip $(OBJECTS_ALL))" ""
archive_or_objs = $(TARGET_LIB)($(OBJECTS_ALL))
endif
else
archive_or_objs = $(OBJECTS_ALL)
endif

#-------------------------------------------------------------------------------
# Default target
#-------------------------------------------------------------------------------

# Note that prerequisite order is important here. The subdirectories must be built first, or you
# may end up with files in the current directory not getting added to libraries. This would happen
# if subdirs modified the library file after local files were compiled but before they were added
# to the library.
.PHONY: all
all : $(SUBDIRS) $(archive_or_objs) $(APP_ELF)

# Recipe to create the output object file directories.
$(OBJECTS_DIRS) :
	$(at)mkdir -p $@

# Everything depends upon the current makefile.
$(OBJECTS_ALL) $(APP_ELF): $(this_makefile)

# Object files depend on the directories where they will be created.
#
# The dirs are made order-only prerequisites (by being listed after the '|') so they won't cause
# the objects to be rebuilt, as the modification date on a directory changes whenver its contents
# change. This would cause the objects to always be rebuilt if the dirs were normal prerequisites.
$(OBJECTS_ALL): | $(OBJECTS_DIRS)

#-------------------------------------------------------------------------------
# Pattern rules for compilation
#-------------------------------------------------------------------------------
# We cd into the source directory before calling the appropriate compiler. This must be done
# on a single command line since make calls individual recipe lines in separate shells, so
# '&&' is used to chain the commands.
#
# Generate make dependencies while compiling using the -MMD option, which excludes system headers.
# If system headers are included, there are path problems on cygwin. The -MP option creates empty
# targets for each header file so that a rebuild will be forced if the file goes missing, but
# no error will occur.

# Compile C sources.
$(OBJS_ROOT)/%.o: $(SDK_ROOT)/%.c
	@$(call printmessage,c,Compiling, $(subst $(SDK_ROOT)/,,$<))
	$(at)cd $(dir $<) && $(CC) $(CFLAGS) $(SYSTEM_INC) $(INCLUDES) $(DEFINES) -MMD -MF $(basename $@).d -MP -o $@ -c $<

# Compile C++ sources.
$(OBJS_ROOT)/%.o: $(SDK_ROOT)/%.cpp
	@$(call printmessage,cxx,Compiling, $(subst $(SDK_ROOT)/,,$<))
	$(at)cd $(dir $<) && $(CXX) $(CXXFLAGS) $(SYSTEM_INC) $(INCLUDES) $(DEFINES) -MMD -MF $(basename $@).d -MP -o $@ -c $<

# For .S assembly files, first run through the C preprocessor then assemble.
$(OBJS_ROOT)/%.o: $(SDK_ROOT)/%.S
	@$(call printmessage,asm,Assembling, $(subst $(SDK_ROOT)/,,$<))
	$(at)cd $(dir $<) \
	&& $(CPP) -D__LANGUAGE_ASM__ $(INCLUDES) $(DEFINES) -o $(basename $@).s $< \
	&& $(AS) $(ASFLAGS) $(INCLUDES) -MD $(OBJS_ROOT)/$*.d -o $@ $(basename $@).s

# Assembler sources.
$(OBJS_ROOT)/%.o: $(SDK_ROOT)/%.s
	@$(call printmessage,asm,Assembling, $(subst $(SDK_ROOT)/,,$<))
	$(at)cd $(dir $<) && $(AS) $(ASFLAGS) $(INCLUDES) -MD $(basename $@).d -o $@ $<

# Add objects to the target library.
#
# We use mkdir to explicitly ensure that the archive's directory exists before calling
# the ar tool. The dir can't be made a dependancy because make will try to add it to the
# archive.
#
# flock is used to protect the archive file from multiple processes trying to write to it
# simultaneously, in case we're using parallel processes.
#
# The log message is disabled in order to reduce clutter in the build log, since you will get
# one message for every file that is archived.
$(TARGET_LIB)(%): %
#	@$(call printmessage,ar,Archiving, $(?F) in $(@F))
	$(at)mkdir -p $(dir $(@))
	$(at)flock $(@).lock $(AR) -rucs $@ $?

#-------------------------------------------------------------------------------
# Subdirs
#-------------------------------------------------------------------------------

# Recursively execute make in each of the subdirectories.
# Subdirs are double-colon rules to allow additional recipes to be added to them.
# This is used by the top-level makefile to print a message when starting to build
# the sdk library.
.PHONY: $(SUBDIRS)
$(SUBDIRS)::
	@$(MAKE) $(silent_make) -r -C $@

#-------------------------------------------------------------------------------
# Linking
#-------------------------------------------------------------------------------

# Only link the application if LINK_APP is defined.
ifeq "$(LINK_APP)" "1"

# If app objects are being archived into a library, we don't need to specify the
# actual .o files on the linker command line.
ifeq "$(ARCHIVE_APP_OBJECTS)" "1"
app_objs = $(TARGET_LIB)
else
app_objs = $(OBJECTS_ALL) $(TARGET_LIB)
endif

app_bin = $(basename $(APP_ELF)).bin
app_map = $(basename $(APP_ELF)).map

# Preprocess the linker script if it has an ".S" extension.
ifeq "$(filter %.S,$(LD_FILE))" ""
the_ld_file = $(LD_FILE)
else
rel_ld_file = $(basename $(subst $(SDK_ROOT)/,,$(abspath $(LD_FILE))))
the_ld_file = $(addprefix $(OBJS_ROOT)/,$(rel_ld_file))
the_ld_file_dir = $(dir $(the_ld_file))

# Rule to preprocess the ld file. The ld file's parent directory is made an order-only
# prerequisite so it cannot by itself cause this recipe to be invoked.
$(the_ld_file): $(LD_FILE) | $(the_ld_file_dir)
	@$(call printmessage,cpp,Preprocessing, $(subst $(SDK_ROOT)/,,$<))
	$(at)cd $(dir $<) && $(CC) -E -P $(INCLUDES) $(DEFINES) -o $@ $<
endif

# Link the application.
# Wrap the link objects in start/end group so that ld re-checks each
# file for dependencies.  Otherwise linking static libs can be a pain
# since order matters.
$(APP_ELF): $(SUBDIRS) $(app_objs) $(the_ld_file) $(LIBRARIES) $(APP_LIBS)
	@$(call printmessage,link,Linking, $(APP_NAME))
	$(at)$(LD) -Bstatic -nostartfiles -nostdlib $(LDFLAGS) \
	      -T $(the_ld_file) \
	      $(LDINC) \
	      --start-group \
	      $(app_objs) \
	      $(LIBRARIES) \
	      $(APP_LIBS) \
	      $(LDADD) \
	      --end-group \
	      -o $@ \
	      -Map $(app_map) --cref
	$(at)$(OBJCOPY) --gap-fill 0x00 -I elf32-little -O binary $@ $(app_bin)
	@echo "Output ELF:" ; echo "  $(APP_ELF)"
	@echo "Output binary:" ; echo "  $(app_bin)"

else
# Empty target to prevent an error. Needed because $(APP_ELF) is a prereq for the 'all' target.
$(APP_ELF): ;
endif

# Include dependency files.
-include $(OBJECTS_ALL:.o=.d)

