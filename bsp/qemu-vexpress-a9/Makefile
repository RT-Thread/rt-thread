phony := all
all:

include config.mk

ifneq ($(MAKE_LIB),1)
TARGET := rtthread.elf
include src.mk
endif

$(if $(strip $(RTT_ROOT)),,$(error RTT_ROOT not defined))

include $(RTT_ROOT)/tools/rtthread.mk
