#-------------------------------------------------------------------------------
# Copyright (C) 2012 Freescale Semiconductor, Inc. All Rights Reserved.
#
# THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
# SHALL FREESCALE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
# OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
# OF SUCH DAMAGE.
#-------------------------------------------------------------------------------

#
# Top-level Makefile.
#
# This file is responsible for building all libraries and applications.
#
# Targets:
#  - all
#  - sdk
#  - board
#  - sdk_unit_test
#  - power_modes_test
#  - obds
#  - gpu_demo
#  - smp_primes
#  - stream
#  - usb_hid_mouse
#  - httpd
#  - ping
#  - clean
#  - clean_sdk
#  - clean_board
#  - clean_sdk_unit_test
#  - clean_power_modes_test
#  - clean_obds
#  - clean_gpu_demo
#  - clean_smp_primes
#  - clean_stream
#  - clean_usb_hid_mouse
#  - clean_httpd
#  - clean_ping
#
# The clean targets work with any combination of configuration variables. For
# example, clean_sdk with TARGET set will clean libsdk for only that TARGET, while
# clean_sdk without TARGET set will clean libsdk in all targets.
#

include mk/common.mk

# Turn off parallel jobs for this makefile only. Child makefiles will still use the
# specified number of jobs. This isn't strictly necessary, and actually slows the build
# a little bit, but greatly improves the readability of the log output.
.NOTPARALLEL:

# Determine if the target is either the MX6DQ or MX6SDL.
ifeq "$(TARGET)" "mx6dq"
is_dq_or_sdl = 1
else ifeq "$(TARGET)" "mx6sdl"
is_dq_or_sdl = 1
endif

# Library subdirectories that the apps depend upon. Handled automatically by targets.mk.
SUBDIRS = \
    sdk \
    lwip \
    $(BOARD_ROOT)

# List of all applications to build. Applications must reside in the apps directory.
ALL_APPS = \
    filesystem \
    httpd \
    obds \
    ping \
    power_modes_test \
    sdk_unit_test \
    stream \
    usb_hid_mouse

# Apps that are only built for MX6DQ and MX6SDL.
ifdef is_dq_or_sdl
ALL_APPS += \
    caam_blob_gen \
    gpu_demo \
    smp_primes
endif

# Default target.
.PHONY: all
all: $(sort $(ALL_APPS)) ;

# App targets. All apps depend on the listed subdirectories.
.PHONY: ALL_APPS
$(ALL_APPS): $(SUBDIRS)
	@$(call printmessage,build,Building, $@ ,gray,[$(TARGET) $(BOARD) $(BOARD_REVISION)],,\n)
	@$(MAKE) $(silent_make) -r -C apps/$@

# Print message before recursive into subdirs.
$(SUBDIRS)::
	@$(call printmessage,build,Building, $(@F) ,gray,[$(TARGET) $(BOARD) $(BOARD_REVISION)],,\n)

# Target with a simple name for building the board package.
.PHONY: board
board: $(BOARD_ROOT)

# Target to clean everything.
.PHONY: clean
clean:
	@echo "Deleting output directory..."
	@rm -rf output
	@echo "done."

# Target to clean just the sdk library and objects.
.PHONY: clean_sdk
clean_sdk:
ifdef TARGET
	rm -rf $(LIBSDK) $(OUTPUT_ROOT)/lib/obj/sdk
else
	rm -rf $(SDK_ROOT)/output/*/lib/libsdk.a $(SDK_ROOT)/output/*/lib/obj/sdk
endif

# Target to clean the board library and objects.
.PHONY: clean_board
clean_board:
ifdef TARGET
 ifdef BOARD
	rm -rf $(LIBBOARD) $(OUTPUT_ROOT)/lib/obj/board_$(BOARD_WITH_REV)
 else
	rm -rf $(OUTPUT_ROOT)/lib/libboard* $(OUTPUT_ROOT)/lib/obj/board_*
 endif
else
	rm -rf $(SDK_ROOT)/output/*/lib/libboard* $(SDK_ROOT)/output/*/lib/obj/board_*
endif

# Set up targets to clean each of the applications. For an app "foo", the target to clean
# just that app is "clean_foo". If no TARGET is passed to make, the app is cleaned
# for all targets.
ALL_APP_CLEAN_TARGETS := $(addprefix clean_,$(ALL_APPS))
.PHONY: $(ALL_APP_CLEAN_TARGETS)
$(ALL_APP_CLEAN_TARGETS):
ifdef TARGET
 ifdef BOARD
  ifdef BOARD_REVISION
   ifdef BOARD_REVISION_IS_DEFAULT
# Clean all revs of the board.
	rm -rf $(OUTPUT_ROOT)/$(patsubst clean_%,%,$@)/$(BOARD)_rev_*
   else
# Specific rev specified so clean just that one rev.
	rm -rf $(OUTPUT_ROOT)/$(patsubst clean_%,%,$@)/$(BOARD_WITH_REV)
   endif
  else
# Clean all revs of the board.
	rm -rf $(OUTPUT_ROOT)/$(patsubst clean_%,%,$@)/$(BOARD)_rev_*
  endif
 else
# Clean all boards of the app.
	rm -rf $(OUTPUT_ROOT)/$(patsubst clean_%,%,$@)
 endif
else
# Clean all boards and targets of the app.
	rm -rf $(SDK_ROOT)/output/*/$(patsubst clean_%,%,$@)
endif

include mk/targets.mk
