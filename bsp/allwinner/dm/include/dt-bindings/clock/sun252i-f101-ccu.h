/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DT_BINDINGS_CLOCK_SUN252I_F101_CCU_H__
#define __DT_BINDINGS_CLOCK_SUN252I_F101_CCU_H__

/* Keep these IDs aligned with Linux's sun252i-f101-ccu binding. */
#define SUN252I_F101_CLK_PLL_PERI             0
#define SUN252I_F101_CLK_PLL_PERI_2X          1
#define SUN252I_F101_CLK_PLL_PERI_1X          2
#define SUN252I_F101_CLK_PLL_PERI_800M        3
#define SUN252I_F101_CLK_PLL_PERI_480M        4
#define SUN252I_F101_CLK_PLL_VIDEO0_4X        5
#define SUN252I_F101_CLK_PLL_VIDEO0_2X        6
#define SUN252I_F101_CLK_PLL_VIDEO0_1X        7
#define SUN252I_F101_CLK_PLL_AUDIO1           8
#define SUN252I_F101_CLK_PLL_AUDIO1_DIV2      9
#define SUN252I_F101_CLK_PLL_AUDIO1_DIV5      10
#define SUN252I_F101_CLK_PSI                  11
#define SUN252I_F101_CLK_APB0                 12
#define SUN252I_F101_CLK_APB1                 13
#define SUN252I_F101_CLK_APB_UART             14
#define SUN252I_F101_CLK_MBUS                 15
#define SUN252I_F101_CLK_DE                   16
#define SUN252I_F101_CLK_BUS_DE               17
#define SUN252I_F101_CLK_DI                   18
#define SUN252I_F101_CLK_BUS_DI               19
#define SUN252I_F101_CLK_G2D                  20
#define SUN252I_F101_CLK_BUS_G2D              21
#define SUN252I_F101_CLK_CE                   22
#define SUN252I_F101_CLK_BUS_CE               23
#define SUN252I_F101_CLK_VE                   24
#define SUN252I_F101_CLK_BUS_VE               25
#define SUN252I_F101_CLK_BUS_DMA              26
#define SUN252I_F101_CLK_BUS_HSTIMER          27
#define SUN252I_F101_CLK_BUS_AVS              28
#define SUN252I_F101_CLK_BUS_DBGSYS           29
#define SUN252I_F101_CLK_PWM_BL               30
#define SUN252I_F101_CLK_BUS_PWM_BL           31
#define SUN252I_F101_CLK_BUS_PWM              32
#define SUN252I_F101_CLK_BUS_G2D_M            33
#define SUN252I_F101_CLK_BUS_CSI_M            34
#define SUN252I_F101_CLK_BUS_TVIN_M           35
#define SUN252I_F101_CLK_BUS_VE_M             36
#define SUN252I_F101_CLK_BUS_DMA_M            37
#define SUN252I_F101_CLK_BUS_DRAM             38
#define SUN252I_F101_CLK_SMHC0                39
#define SUN252I_F101_CLK_SMHC2                40
#define SUN252I_F101_CLK_BUS_SMHC2            41
#define SUN252I_F101_CLK_BUS_SMHC0            42
#define SUN252I_F101_CLK_BUS_UART5            43
#define SUN252I_F101_CLK_BUS_UART4            44
#define SUN252I_F101_CLK_BUS_UART3            45
#define SUN252I_F101_CLK_BUS_UART2            46
#define SUN252I_F101_CLK_BUS_UART1            47
#define SUN252I_F101_CLK_BUS_UART0            48
#define SUN252I_F101_CLK_BUS_TWI2             49
#define SUN252I_F101_CLK_BUS_TWI1             50
#define SUN252I_F101_CLK_BUS_TWI0             51
#define SUN252I_F101_CLK_SPI0                 52
#define SUN252I_F101_CLK_SPI1                 53
#define SUN252I_F101_CLK_BUS_SPI1             54
#define SUN252I_F101_CLK_BUS_SPI0             55
#define SUN252I_F101_CLK_SPIF                 56
#define SUN252I_F101_CLK_BUS_SPIF             57
#define SUN252I_F101_CLK_IRRX                 58
#define SUN252I_F101_CLK_BUS_IRRX             59
#define SUN252I_F101_CLK_CAN0                 60
#define SUN252I_F101_CLK_CAN1                 61
#define SUN252I_F101_CLK_BUS_GPADC            62
#define SUN252I_F101_CLK_BUS_THS              63
#define SUN252I_F101_CLK_I2S0                 64
#define SUN252I_F101_CLK_BUS_I2S0             65
#define SUN252I_F101_CLK_OWA_TX               66
#define SUN252I_F101_CLK_OWA_RX               67
#define SUN252I_F101_CLK_BUS_OWA              68
#define SUN252I_F101_CLK_AUDIO_CODEC_DAC      69
#define SUN252I_F101_CLK_AUDIO_CODEC_ADC      70
#define SUN252I_F101_CLK_BUS_AUDIO_CODEC      71
#define SUN252I_F101_CLK_BUS_USB              72
#define SUN252I_F101_CLK_BUS_USBOTG0          73
#define SUN252I_F101_CLK_BUS_USBEHCI0         74
#define SUN252I_F101_CLK_BUS_USBOHCI0         75
#define SUN252I_F101_CLK_COMBOPHY0            76
#define SUN252I_F101_CLK_BUS_COMBOPHY0        77
#define SUN252I_F101_CLK_BUS_DPSS_TOP         78
#define SUN252I_F101_CLK_DSI                  79
#define SUN252I_F101_CLK_BUS_DSI              80
#define SUN252I_F101_CLK_TCONLCD              81
#define SUN252I_F101_CLK_BUS_TCONLCD          82
#define SUN252I_F101_CLK_CSI                  83
#define SUN252I_F101_CLK_CSI_MASTER           84
#define SUN252I_F101_CLK_BUS_CSI              85
#define SUN252I_F101_CLK_TVIN_MASTER          86
#define SUN252I_F101_CLK_BUS_TVIN             87
#define SUN252I_F101_CLK_BUS_TVIN_TOP         88
#define SUN252I_F101_CLK_TPADC                89
#define SUN252I_F101_CLK_BUS_TPADC            90
#define SUN252I_F101_CLK_BUS_RISCV_CFG        91
#define SUN252I_F101_CLK_BUS_CLK32K           92
#define SUN252I_F101_CLK_BUS_CLK25M           93
#define SUN252I_F101_CLK_BUS_CLK16M           94
#define SUN252I_F101_CLK_BUS_CLK12M           95
#define SUN252I_F101_CLK_BUS_CLK24M           96
#define SUN252I_F101_CLK_PCLK                 97
#define SUN252I_F101_CLK_BUS_CLK_FANOUT2      98
#define SUN252I_F101_CLK_BUS_CLK_FANOUT1      99
#define SUN252I_F101_CLK_BUS_CLK_FANOUT0      100

#define SUN252I_F101_CLK_NUMBER               101

#endif /* __DT_BINDINGS_CLOCK_SUN252I_F101_CCU_H__ */
