MIPI_DSI_IP_VERSION ?= 40

ifeq ($(CONFIG_ARCH_SUN8IW8),y)
sub_dir = lowlevel_sun8iw8
endif

ifeq ($(CONFIG_ARCH_SUN8IW11),y)
sub_dir = lowlevel_v2x
endif

ifeq ($(CONFIG_ARCH_SUN8IW12),y)
sub_dir = lowlevel_v2x
MIPI_DSI_IP_VERSION := 28
endif

ifeq ($(CONFIG_ARCH_SUN8IW15),y)
MIPI_DSI_IP_VERSION := 28
sub_dir = lowlevel_v2x
endif

ifeq ($(CONFIG_ARCH_SUN50IW10),y)
MIPI_DSI_IP_VERSION := 28
sub_dir = lowlevel_v2x
endif

ifeq ($(CONFIG_ARCH_SUN8IW6),y)
sub_dir = lowlevel_v2x
MIPI_DSI_IP_VERSION := 28
endif

ifeq ($(CONFIG_ARCH_SUN8IW7),y)
sub_dir = lowlevel_v2x
endif

ifeq ($(CONFIG_ARCH_SUN50IW1),y)
sub_dir = lowlevel_sun50iw1
endif

ifeq ($(CONFIG_ARCH_SUN50IW3),y)
sub_dir = lowlevel_v3x
MIPI_DSI_IP_VERSION := 28
endif

ifeq ($(CONFIG_ARCH_SUN50IW6),y)
sub_dir = lowlevel_v3x
endif


ifeq ($(CONFIG_ARCH_SUN50IW8),y)
sub_dir = lowlevel_v2x
endif

ifeq ($(CONFIG_ARCH_SUN8IW17),y)
sub_dir = lowlevel_v2x
endif

ifeq ($(CONFIG_ARCH_SUN8IW16),y)
sub_dir = lowlevel_v2x
MIPI_DSI_IP_VERSION := 28
endif

ifeq ($(CONFIG_ARCH_SUN8IW19),y)
sub_dir = lowlevel_v2x
MIPI_DSI_IP_VERSION := 28
endif

ifeq ($(CONFIG_ARCH_SUN20IW1),y)
sub_dir = lowlevel_v2x
MIPI_DSI_IP_VERSION := 40
endif

ifneq ($(sub_dir),)
-include $(obj)/de/$(sub_dir)/Makefile
endif
