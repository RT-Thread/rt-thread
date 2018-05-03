include $(SDK_ROOT)/mk/common.mk


define SOURCES
dec.c
enc.c
fb.c
utils.c
vpu_test.c
endef

INCLUDES += \
	-I$(SDK_ROOT)/sdk/common/filesystem/ \
    -I$(SDK_ROOT)/sdk/common/filesystem/include \
    -I$(SDK_ROOT)/sdk/common/filesystem/fat/include


include $(SDK_ROOT)/mk/targets.mk
