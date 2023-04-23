/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date               Author             Notes
 * 2011-08-08     lgnq                first version
 * 2015-07-06     chinesebear      modified for loongson 1c
 */

#ifndef __LS1C_H__
#define __LS1C_H__

#include <gs232.h>

#define LS1C_ACPI_IRQ    0
#define LS1C_HPET_IRQ    1
//#define LS1C_UART0_IRQ    3  // linux使用3，v1.4版本之前1c分配有问题，建议使用2，以确保正确
#define LS1C_UART1_IRQ   4
#define LS1C_UART2_IRQ   5
#define LS1C_CAN0_IRQ    6
#define LS1C_CAN1_IRQ    7
#define LS1C_SPI0_IRQ    8
#define LS1C_SPI1_IRQ    9
#define LS1C_AC97_IRQ    10
#define LS1C_MS_IRQ      11
#define LS1C_KB_IRQ      12
#define LS1C_DMA0_IRQ    13
#define LS1C_DMA1_IRQ    14
#define LS1C_DMA2_IRQ    15
#define LS1C_NAND_IRQ    16
#define LS1C_PWM0_IRQ    17
#define LS1C_PWM1_IRQ    18
#define LS1C_PWM2_IRQ    19
#define LS1C_PWM3_IRQ    20
#define LS1C_RTC_INT0_IRQ  21
#define LS1C_RTC_INT1_IRQ  22
#define LS1C_RTC_INT2_IRQ  23
#define LS1C_UART3_IRQ   29
#define LS1C_ADC_IRQ     30
#define LS1C_SDIO_IRQ    31


#define LS1C_EHCI_IRQ   (32+0)
#define LS1C_OHCI_IRQ   (32+1)
#define LS1C_OTG_IRQ    (32+2)
#define LS1C_MAC_IRQ    (32+3)
#define LS1C_CAM_IRQ    (32+4)
#define LS1C_UART4_IRQ  (32+5)
#define LS1C_UART5_IRQ  (32+6)
#define LS1C_UART6_IRQ  (32+7)
#define LS1C_UART7_IRQ  (32+8)
#define LS1C_UART8_IRQ  (32+9)
#define LS1C_UART9_IRQ  (32+13)
#define LS1C_UART10_IRQ (32+14)
#define LS1C_UART11_IRQ (32+15)
#define LS1C_I2C2_IRQ   (32+17)
#define LS1C_I2C1_IRQ   (32+18)
#define LS1C_I2C0_IRQ   (32+19)


#define LS1C_GPIO_IRQ       64
#define LS1C_GPIO_FIRST_IRQ 64
#define LS1C_GPIO_IRQ_COUNT 96
#define LS1C_GPIO_LAST_IRQ  (LS1C_GPIO_FIRST_IRQ + LS1C_GPIO_IRQ_COUNT-1)


#define LS1C_LAST_IRQ 159
#define LS1C_INTREG_BASE 0xbfd01040

// 将1c的中断分为五组，每组32个
#define LS1C_NR_IRQS    (32*5)


// GPIO引脚到中断号之间的转换
#define LS1C_GPIO_TO_IRQ(GPIOn)     (LS1C_GPIO_FIRST_IRQ + (GPIOn))
#define LS1C_IRQ_TO_GPIO(IRQn)      ((IRQn) - LS1C_GPIO_FIRST_IRQ)

#endif

