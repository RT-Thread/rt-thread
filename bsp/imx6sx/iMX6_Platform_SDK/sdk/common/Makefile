include $(SDK_ROOT)/mk/common.mk


SUBDIRS = filesystem usb_stack

# Determine if the target is either the MX6DQ or MX6SDL.
ifeq "$(TARGET)" "mx6dq"
is_dq_or_sdl = 1
endif
ifeq "$(TARGET)" "mx6sdl"
is_dq_or_sdl = 1
endif
ifeq "$(TARGET)" "mx6sl"
is_sl = 1
endif

# Compile these sources directly.
SOURCES = \
	profile/profile.c 

ifdef is_dq_or_sdl
SOURCES += \
	ioexpander/src/max7310.c
endif

ifdef is_sl
SOURCES += \
	pmic/pfuse/pf0100.c
endif

include $(SDK_ROOT)/mk/targets.mk
