/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-14     Haley        first implementation
 */
#ifndef __BOARD_H_
#define __BOARD_H_

#include <rtthread.h>

// <o> Internal SRAM memory size[Kbytes] <8-256>
// <i>Default: 256
#define AM_SRAM_SIZE         256
#define AM_SRAM_END          (0x10000000 + AM_SRAM_SIZE * 1024)

/* USART driver select. */
#define RT_USING_UART0
//#define RT_USING_UART1

/* ADC driver select. */
#define RT_USING_ADC

/* I2C driver select. */
#define RT_USING_I2C0
//#define RT_USING_I2C2
//#define RT_USING_I2C4

/* SMBUS driver select. */
//#define RT_USING_SMBUS

/* SPI driver select. */
#define RT_USING_SPI1

/* LED driver select. */
#define RT_USING_LED0
//#define RT_USING_LED1
//#define RT_USING_LED2
//#define RT_USING_LED3

/* PWM driver select. */
//#define RT_USING_PWM

/* PDM driver select. */
//#define RT_USING_PDM

void rt_hw_board_init(void);

#endif /* __BOARD_H__ */
