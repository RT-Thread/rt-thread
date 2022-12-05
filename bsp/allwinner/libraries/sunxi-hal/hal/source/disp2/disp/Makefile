include $(obj)/de/Makefile

obj-y += dev_disp.o
obj-y += disp_sys_intf.o
obj-y += disp_debug.o

obj-y += de/disp_display.o de/disp_features.o de/disp_device.o \
	     de/disp_lcd.o de/disp_manager.o de/disp_private.o de/disp_capture.o
	     #de/disp_hdmi.o de/disp_tv.o de/disp_vdevice.o

obj-$(CONFIG_DISP2_SUNXI_SUPPORT_SMBL) += de/disp_smart_backlight.o
obj-$(CONFIG_DISP2_SUNXI_SUPPORT_ENAHNCE) += de/disp_enhance.o

obj-y  += lcd/panels.o lcd/lcd_source.o lcd/default_panel.o


obj-$(CONFIG_LCD_SUPPORT_HE0801A068) += lcd/he0801a068.o
obj-$(CONFIG_EINK_PANEL_USED) += lcd/default_eink.o
obj-$(CONFIG_LCD_SUPPORT_LT070ME05000) += lcd/lt070me05000.o
obj-$(CONFIG_LCD_SUPPORT_WTQ05027D01) += lcd/wtq05027d01.o
obj-$(CONFIG_LCD_SUPPORT_T27P06) += lcd/t27p06.o
obj-$(CONFIG_LCD_SUPPORT_DX0960BE40A1) += lcd/dx0960be40a1.o
obj-$(CONFIG_LCD_SUPPORT_TFT720_1280) += lcd/tft720x1280.o
obj-$(CONFIG_LCD_SUPPORT_TFT08006) += lcd/tft08006.o
obj-$(CONFIG_LCD_SUPPORT_S6D7AA0X01) += lcd/S6D7AA0X01.o
obj-$(CONFIG_LCD_SUPPORT_GG1P4062UTSW) += lcd/cpu_gg1p4062utsw.o
obj-$(CONFIG_LCD_SUPPORT_LS029B3SX02) +=  lcd/ls029b3sx02.o
obj-$(CONFIG_LCD_SUPPORT_FD055HD003S) += lcd/fd055hd003s.o
obj-$(CONFIG_LCD_SUPPORT_FRD450H40014) += lcd/frd450h40014.o
obj-$(CONFIG_LCD_SUPPORT_H245QBN02) += lcd/h245qbn02.o
obj-$(CONFIG_LCD_SUPPORT_ILI9341) += lcd/ili9341.o
obj-$(CONFIG_LCD_SUPPORT_LH219WQ1) += lcd/lh219wq1.o
obj-$(CONFIG_LCD_SUPPORT_ST7789V) += lcd/st7789v.o
obj-$(CONFIG_LCD_SUPPORT_ST7796S) += lcd/st7796s.o
obj-$(CONFIG_LCD_SUPPORT_ST7701S) += lcd/st7701s.o
obj-$(CONFIG_LCD_SUPPORT_WTL096601G03) += lcd/wtl096601g03.o
obj-$(CONFIG_LCD_SUPPORT_T30P106) += lcd/t30p106.o
obj-$(CONFIG_LCD_SUPPORT_TO20T20000) += lcd/to20t20000.o
obj-$(CONFIG_LCD_SUPPORT_S2003T46G) += lcd/s2003t46g.o
obj-$(CONFIG_LCD_SUPPORT_WILLIAMLCD) += lcd/WilliamLcd.o
obj-$(CONFIG_LCD_SUPPORT_LQ101R1SX03) += lcd/lq101r1sx03.o
obj-$(CONFIG_LCD_SUPPORT_INET_DSI_PANEL) += lcd/inet_dsi_panel.o
obj-$(CONFIG_LCD_SUPPORT_RT13QV005D) += lcd/rt13qv005d.o
obj-$(CONFIG_LCD_SUPPORT_ILI9881C) += lcd/ili9881c.o
obj-$(CONFIG_LCD_SUPPORT_TM_DSI_PANEL) += lcd/tm_dsi_panel.o
obj-$(CONFIG_LCD_SUPPORT_ST7789V_CPU) += lcd/st7789v_cpu.o
obj-$(CONFIG_LCD_SUPPORT_VVX07H005A10) += lcd/VVX07H005A10.o

obj-y += $(obj_low)
