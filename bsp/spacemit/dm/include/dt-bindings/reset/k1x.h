/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DT_BINDINGS_RESET_K1X_H__
#define __DT_BINDINGS_RESET_K1X_H__

/* APBC */
#define RESET_UART1             1
#define RESET_UART2             2
#define RESET_GPIO              3
#define RESET_PWM0              4
#define RESET_PWM1              5
#define RESET_PWM2              6
#define RESET_PWM3              7
#define RESET_PWM4              8
#define RESET_PWM5              9
#define RESET_PWM6              10
#define RESET_PWM7              11
#define RESET_PWM8              12
#define RESET_PWM9              13
#define RESET_PWM10             14
#define RESET_PWM11             15
#define RESET_PWM12             16
#define RESET_PWM13             17
#define RESET_PWM14             18
#define RESET_PWM15             19
#define RESET_PWM16             20
#define RESET_PWM17             21
#define RESET_PWM18             22
#define RESET_PWM19             23
#define RESET_SSP3              24
#define RESET_UART3             25
#define RESET_RTC               26
#define RESET_TWSI0             27

#define RESET_TIMERS1           28
#define RESET_AIB               29
#define RESET_TIMERS2           30
#define RESET_ONEWIRE           31
#define RESET_SSPA0             32
#define RESET_SSPA1             33
#define RESET_DRO               34
#define RESET_IR                35
#define RESET_TWSI1             36

#define RESET_TSEN              37
#define RESET_TWSI2             38
#define RESET_TWSI4             39
#define RESET_TWSI5             40
#define RESET_TWSI6             41
#define RESET_TWSI7             42
#define RESET_TWSI8             43
#define RESET_IPC_AP2AUD        44
#define RESET_UART4             45
#define RESET_UART5             46
#define RESET_UART6             47
#define RESET_UART7             48
#define RESET_UART8             49
#define RESET_UART9             50
#define RESET_CAN0              51

/* MPMU */
#define RESET_WDT               52

/* APMU */
#define RESET_JPG               53
#define RESET_CSI               54
#define RESET_CCIC2_PHY         55
#define RESET_CCIC3_PHY         56
#define RESET_ISP               57
#define RESET_ISP_AHB           58
#define RESET_ISP_CI            59
#define RESET_ISP_CPP           60
#define RESET_LCD               61
#define RESET_DSI_ESC           62
#define RESET_V2D               63
#define RESET_MIPI              64
#define RESET_LCD_SPI           65
#define RESET_LCD_SPI_BUS       66
#define RESET_LCD_SPI_HBUS      67
#define RESET_LCD_MCLK          68
#define RESET_CCIC_4X           69
#define RESET_CCIC1_PHY         70
#define RESET_SDH_AXI           71
#define RESET_SDH0              72
#define RESET_SDH1              73
#define RESET_USB_AXI           74
#define RESET_USBP1_AXI         75
#define RESET_COMBO_PHY         76
#define RESET_USB3_0            77
#define RESET_QSPI              78
#define RESET_QSPI_BUS          79
#define RESET_DMA               80
#define RESET_AES               81
#define RESET_VPU               82
#define RESET_GPU               83
#define RESET_SDH2              84
#define RESET_MC                85
#define RESET_EM_AXI            86
#define RESET_EM                87
#define RESET_AUDIO_SYS         88
#define RESET_HDMI              89
#define RESET_PCIE0             90
#define RESET_PCIE1             91
#define RESET_PCIE2             92
#define RESET_EMAC0             93
#define RESET_EMAC1             94

/* APBC2 */
#define RESET_SEC_UART1         95
#define RESET_SEC_SSP2          96
#define RESET_SEC_TWSI3         97
#define RESET_SEC_RTC           98
#define RESET_SEC_TIMERS0       99
#define RESET_SEC_KPC           100
#define RESET_SEC_GPIO          101

#define RESET_RCPU_HDMIAUDIO    102
#define RESET_RCPU_CAN          103

#define RESET_RCPU_I2C0         104
#define RESET_RCPU_SSP0         105
#define RESET_RCPU_IR           106
#define RESET_RCPU_UART0        107
#define RESET_RCPU_UART1        108

#define RESET_RCPU2_PWM0        109
#define RESET_RCPU2_PWM1        110
#define RESET_RCPU2_PWM2        111
#define RESET_RCPU2_PWM3        112
#define RESET_RCPU2_PWM4        113
#define RESET_RCPU2_PWM5        114
#define RESET_RCPU2_PWM6        115
#define RESET_RCPU2_PWM7        116
#define RESET_RCPU2_PWM8        117
#define RESET_RCPU2_PWM9        118

#define RESET_NUMBER            119

#endif /* __DT_BINDINGS_RESET_K1X_H__ */
