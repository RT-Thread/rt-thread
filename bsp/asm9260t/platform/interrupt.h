/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-04-14     ArdaFu      first version
 */
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#define INT_IRQ     0x00
#define INT_FIQ     0x01


// IRQ Source
#define INT_ARM_COMMRX                    0
#define INT_ARM_COMMTX                    1
#define INT_RTC                           2
#define INT_GPIO0                         3
#define INT_GPIO1                         4
#define INT_GPIO2                         5
#define INT_GPIO3                         6
#define INT_GPIO4_IIS1                    7
#define INT_USB0                          8
#define INT_USB1                          9
#define INT_USB0_DMA                      10
#define INT_USB1_DMA                      11
#define INT_MAC                           12
#define INT_MAC_PMT                       13
#define INT_NAND                          14
#define INT_UART0                         15
#define INT_UART1                         16
#define INT_UART2                         17
#define INT_UART3                         18
#define INT_UART4                         19
#define INT_UART5                         20
#define INT_UART6                         21
#define INT_UART7                         22
#define INT_UART8                         23
#define INT_UART9                         24
#define INT_I2S0                          25
#define INT_I2C0                          26
#define INT_I2C1                          27
#define INT_CAMIF                         28
#define INT_TIMER0                        29
#define INT_TIMER1                        30
#define INT_TIMER2                        31
#define INT_TIMER3                        32
#define INT_ADC0                          33
#define INT_DAC0                          34
#define INT_USB0_RESUME_HOSTDISCONNECT    35
#define INT_USB0_VBUSVALID                36
#define INT_USB1_RESUME_HOSTDISCONNECT    37
#define INT_USB1_VBUSVALID                38
#define INT_DMA0_CH0                      39
#define INT_DMA0_CH1                      40
#define INT_DMA0_CH2                      41
#define INT_DMA0_CH3                      42
#define INT_DMA0_CH4                      43
#define INT_DMA0_CH5                      44
#define INT_DMA0_CH6                      45
#define INT_DMA0_CH7                      46
#define INT_DMA1_CH0                      47
#define INT_DMA1_CH1                      48
#define INT_DMA1_CH2                      49
#define INT_DMA1_CH3                      50
#define INT_DMA1_CH4                      51
#define INT_DMA1_CH5                      52
#define INT_DMA1_CH6                      53
#define INT_DMA1_CH7                      54
#define INT_WATCHDOG                      55
#define INT_CAN0                          56
#define INT_CAN1                          57
#define INT_QEI                           58
#define INT_MCPWM                         59
#define INT_SPI0                          60
#define INT_SPI1                          61
#define INT_QUADSPI0                      62
#define INT_SSP0                          63

#endif
