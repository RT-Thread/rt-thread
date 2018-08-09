PROJECT_NAME     := ext_micro_ecc_nrf52nf_library_iar
TARGETS          := micro_ecc_lib
OUTPUT_DIRECTORY := _build

SDK_ROOT := ../../../..
PROJ_DIR := ../..


# Source files common to all targets
SRC_FILES += \
  $(PROJ_DIR)/micro-ecc/uECC.c \

# Include folders common to all targets
INC_FOLDERS += \
  $(SDK_ROOT)/components/toolchain/cmsis/include \

# Libraries common to all targets
LIB_FILES += \

# Optimization flags
OPT = -Os -g2
# Uncomment the line below to enable link time optimization
#OPT += -flto

# C flags common to all targets
CFLAGS += $(OPT)
CFLAGS += -DFLOAT_ABI_SOFT
CFLAGS += -DuECC_ENABLE_VLI_API=0
CFLAGS += -DuECC_OPTIMIZATION_LEVEL=3
CFLAGS += -DuECC_SQUARE_FUNC=0
CFLAGS += -DuECC_SUPPORT_COMPRESSED_POINT=0
CFLAGS += -DuECC_VLI_NATIVE_LITTLE_ENDIAN=1
CFLAGS += -mcpu=cortex-m4
CFLAGS += -mthumb -mabi=aapcs
CFLAGS += -Wall -Werror
CFLAGS += -mfloat-abi=soft
# keep every function in a separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin -fshort-enums -fshort-wchar -Wno-unused-function

# C++ flags common to all targets
CXXFLAGS += $(OPT)

# Assembler flags common to all targets
ASMFLAGS += -g2
ASMFLAGS += -mcpu=cortex-m4
ASMFLAGS += -mthumb -mabi=aapcs
ASMFLAGS += -mfloat-abi=soft
ASMFLAGS += -DFLOAT_ABI_SOFT
ASMFLAGS += -DuECC_ENABLE_VLI_API=0
ASMFLAGS += -DuECC_OPTIMIZATION_LEVEL=3
ASMFLAGS += -DuECC_SQUARE_FUNC=0
ASMFLAGS += -DuECC_SUPPORT_COMPRESSED_POINT=0
ASMFLAGS += -DuECC_VLI_NATIVE_LITTLE_ENDIAN=1


micro_ecc_lib: CFLAGS += -D__HEAP_SIZE=4096
micro_ecc_lib: CFLAGS += -D__STACK_SIZE=4096
micro_ecc_lib: ASMFLAGS += -D__HEAP_SIZE=4096
micro_ecc_lib: ASMFLAGS += -D__STACK_SIZE=4096

# Add standard libraries at the very end of the linker input, after all objects
# that may need symbols provided by these libraries.
LIB_FILES += -lc -lnosys -lm


.PHONY: default help

# Default target - first one defined
default: micro_ecc_lib

# Print all targets that can be built
help:
	@echo following targets are available:
	@echo		micro_ecc_lib

TEMPLATE_PATH := $(SDK_ROOT)/components/toolchain/gcc


include $(TEMPLATE_PATH)/Makefile.common

$(call define_library, $(TARGETS), $(PROJ_DIR)/nrf52nf_iar/armgcc/micro_ecc_lib_nrf52.a)

define create_library
@echo Creating library: $($@)
$(NO_ECHO)$(AR) $($@) $^
@echo Done
endef
micro_ecc_lib:
	$(create_library)

SDK_CONFIG_FILE := ../config/sdk_config.h
CMSIS_CONFIG_TOOL := $(SDK_ROOT)/external_tools/cmsisconfig/CMSIS_Configuration_Wizard.jar
sdk_config:
	java -jar $(CMSIS_CONFIG_TOOL) $(SDK_CONFIG_FILE)
