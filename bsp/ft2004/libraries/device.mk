

include $(DEVICE_PATH)/bsp/bsp.mk
include $(DEVICE_PATH)/drivers/drivers.mk
include $(DEVICE_PATH)/component/component.mk

INCDIRS 		+=  $(DEVICE_PATH)/include \
					 $(DEVICE_PATH)/cpu
SRCDIRS			+= $(DEVICE_PATH)/gcc
				   
# EXCLOUDLE_CFILES +=  $(DEVICE_PATH)/utilities/test_print.c

