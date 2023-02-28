// SPDX-License-Identifier: (GPL-2.0+ or MIT)
/*
 * Copyright (c) 2020 huangzhenwei@allwinnertech.com
 */

#ifndef _DT_BINDINGS_RESET_SUN8IW20_H_
#define _DT_BINDINGS_RESET_SUN8IW20_H_

#define RST_MBUS        0
#define RST_BUS_DE0     1
#define RST_BUS_DI      2
#define RST_BUS_G2D     3
#define RST_BUS_CE      4
#define RST_BUS_VE      5
#define RST_BUS_DMA     6
#define RST_BUS_MSGBOX0     7
#define RST_BUS_MSGBOX1     8
#define RST_BUS_MSGBOX2     9
#define RST_BUS_SPINLOCK    10
#define RST_BUS_HSTIMER     11
#define RST_BUS_DBG     12
#define RST_BUS_PWM     13
#define RST_BUS_DRAM        14
#define RST_BUS_MMC0        15
#define RST_BUS_MMC1        16
#define RST_BUS_MMC2        17
#define RST_BUS_UART0       18
#define RST_BUS_UART1       19
#define RST_BUS_UART2       20
#define RST_BUS_UART3       21
#define RST_BUS_UART4       22
#define RST_BUS_UART5       23
#define RST_BUS_I2C0        24
#define RST_BUS_I2C1        25
#define RST_BUS_I2C2        26
#define RST_BUS_I2C3        27
#define RST_BUS_CAN0        28
#define RST_BUS_CAN1        29
#define RST_BUS_SPI0        30
#define RST_BUS_SPI1        31
#define RST_BUS_EMAC0       32
#define RST_BUS_IR_TX       33
#define RST_BUS_GPADC       34
#define RST_BUS_THS     35
#define RST_BUS_I2S0        36
#define RST_BUS_I2S1        37
#define RST_BUS_I2S2        38
#define RST_BUS_SPDIF       39
#define RST_BUS_DMIC        40
#define RST_BUS_AUDIO_CODEC 41
#define RST_USB_PHY0        42
#define RST_USB_PHY1        43
#define RST_BUS_OHCI0       44
#define RST_BUS_OHCI1       45
#define RST_BUS_EHCI0       46
#define RST_BUS_EHCI1       47
#define RST_BUS_OTG     48
#define RST_BUS_LRADC       49
#define RST_BUS_DPSS_TOP0   50
#define RST_BUS_HDMI_SUB    51
#define RST_BUS_HDMI_MAIN   52
#define RST_BUS_MIPI_DSI    53
#define RST_BUS_TCON_LCD0   54
#define RST_BUS_TCON_TV     55
#define RST_BUS_LVDS0       56
#define RST_BUS_TVE     57
#define RST_BUS_TVE_TOP     58
#define RST_BUS_TVD     59
#define RST_BUS_TVD_TOP     60
#define RST_BUS_LEDC        61
#define RST_BUS_CSI     62
#define RST_BUS_TPADC       63
#define RST_BUS_DSP     64
#define RST_BUS_DSP_CFG     65
#define RST_BUS_DSP_DBG     66
#define RST_BUS_RISCV_CFG   67
#define RST_BUS_RISCV_SOFT  69
#define RST_BUS_RISCV_CPU_SOFT  70

#define RST_BUS_NUMBER (RST_BUS_RISCV_CFG + 1)


#endif /* _DT_BINDINGS_RESET_SUN8IW20_H_ */
