/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     xuxinming    first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

/* RT_USING_UART */
#define RT_USING_UART1
#define RT_USING_UART2
#define RT_UART_RX_BUFFER_SIZE  64
void rt_hw_board_init(void);
void rt_hw_led_set(rt_uint32_t led);
void rt_hw_led_flash(void);

#ifdef RT_USING_FINSH
void rt_hw_finsh_init(void);
#endif

#define USE_USB                 0

#if USE_USB     /* 1 is USB, 0 is non-USB related */
#define PLL_MValue          11
#define PLL_NValue          0
#define CCLKDivValue        4
#define USBCLKDivValue      5

#define Fosc    12000000
#define Fcclk   57600000
#define Fcco    288000000
#else

#define PLL_MValue          12
#define PLL_NValue          1
#define CCLKDivValue        5

#define Fosc    12000000
#define Fcclk   72000000
#define Fcco    360000000

#endif

#if USE_USB
#define Fpclk   (Fcclk / 2)
#else
#define Fpclk   (Fcclk / 4)
#endif

/* IRQ define */
#define SYS32Mode       0x1F
#define IRQ32Mode       0x12
#define FIQ32Mode       0x11

#define HIGHEST_PRIORITY    0x01
#define LOWEST_PRIORITY     0x0F

#define WDT_INT         0
#define SWI_INT         1
#define ARM_CORE0_INT   2
#define ARM_CORE1_INT   3
#define TIMER0_INT      4
#define TIMER1_INT      5
#define UART0_INT       6
#define UART1_INT       7
#define PWM0_1_INT      8
#define I2C0_INT        9
#define SPI0_INT        10          /* SPI and SSP0 share VIC slot */
#define SSP0_INT        10
#define SSP1_INT        11
#define PLL_INT         12
#define RTC_INT         13
#define EINT0_INT       14
#define EINT1_INT       15
#define EINT2_INT       16
#define EINT3_INT       17
#define ADC0_INT        18
#define I2C1_INT        19
#define BOD_INT         20
#define EMAC_INT        21
#define USB_INT         22
#define CAN_INT         23
#define MCI_INT         24
#define GPDMA_INT       25
#define TIMER2_INT      26
#define TIMER3_INT      27
#define UART2_INT       28
#define UART3_INT       29
#define I2C2_INT        30
#define I2S_INT         31

#define VIC_SIZE        32

#define VECT_ADDR_INDEX 0x100
#define VECT_CNTL_INDEX 0x200

#define CCLK    60000000    /* Fosc = 12MHz, M = 5 */
#define PCLK    15000000    /* CCLK/4, use default */

/******************************************************************************
** Function name:       TargetInit
**
** Descriptions:        Initialize the target board; it is called in a
**              necessary place, change it as needed
**
** parameters:          None
** Returned value:      None
**
******************************************************************************/
extern void TargetInit(void);
extern void ConfigurePLL( void );
extern void TargetResetInit(void);

#endif
