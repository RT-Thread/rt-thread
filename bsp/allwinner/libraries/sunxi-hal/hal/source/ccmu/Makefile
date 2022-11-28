ccflags-y += 	-I$(obj)/ \
		-I$(srctree)/include/melis/kernel/drivers

obj-y += hal_clk.o hal_reset.o

obj-$(CONFIG_DRIVERS_SUNXI_CLK) += sunxi/
obj-$(CONFIG_DRIVERS_SUNXI_CCU) += sunxi-ng/
