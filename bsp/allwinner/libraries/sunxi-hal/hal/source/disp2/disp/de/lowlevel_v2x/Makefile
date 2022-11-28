#
# Copyright (c) 2015 Allwinnertech, Inc.
# Tyle <tyle at allwinnertech.com>
#
#

mydir = de/lowlevel_v2x

ifeq ($(MIPI_DSI_IP_VERSION),40)
dsi_obj:=$(mydir)/de_dsi.o
else
dsi_obj:=$(mydir)/de_dsi_28.o
endif

ifeq ($(CONFIG_EINK_PANEL_USED),y)
eink_obj:=$(mydir)/de_eink.o $(mydir)/disp_eink_data.o \
		$(mydir)/disp_waveform.o $(mydir)/rtmx_eink.o
endif

ifneq ($(CONFIG_EINK200_SUNXI),y)
wb_obj:=$(mydir)/de_wb.o
endif

ifeq ($(CONFIG_ARCH_SUN20IW1),y)
lcd_obj:=$(mydir)/de_lcd_sun50iw10.o
else
lcd_obj:=$(mydir)/de_lcd.o
endif

obj_low = $(mydir)/de_fcc.o $(mydir)/de_gsu.o $(mydir)/de_hal.o $(mydir)/disp_al.o \
		$(mydir)/de_peak.o $(mydir)/de_rtmx.o $(mydir)/de_scaler_table.o\
		$(mydir)/de_vep_table.o $(mydir)/de_vsu.o $(mydir)/de_feat.o \
		$(mydir)/de_lti.o $(mydir)/de_fce.o \
		$(mydir)/de_ase.o $(mydir)/de_bws.o $(mydir)/de_enhance.o \
		$(mydir)/de_smbl.o $(mydir)/de_ccsc.o $(mydir)/de_dcsc.o \
		$(wb_obj) $(mydir)/de_clock.o $(eink_obj) $(dsi_obj) $(lcd_obj)

