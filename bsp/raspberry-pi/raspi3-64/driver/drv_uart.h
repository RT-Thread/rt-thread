/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30      Bernard      the first version
 */


#ifndef DRV_UART_H__
#define DRV_UART_H__

/*
 *  Auxiliary
 */
#define AUX_IRQ(BASE)             HWREG32(BASE + 0x00)   /* Auxiliary Interrupt status 3 */
#define AUX_ENABLES(BASE)         HWREG32(BASE + 0x04)   /* Auxiliary enables 3bit */
#define AUX_MU_IO_REG(BASE)       HWREG32(BASE + 0x40)   /* Mini Uart I/O Data 8bit */
#define AUX_MU_IER_REG(BASE)      HWREG32(BASE + 0x44)   /* Mini Uart Interrupt Enable 8bit */
#define AUX_MU_IIR_REG(BASE)      HWREG32(BASE + 0x48)   /* Mini Uart Interrupt Identify 8bit */
#define AUX_MU_LCR_REG(BASE)      HWREG32(BASE + 0x4C)   /* Mini Uart Line Control 8bit */
#define AUX_MU_MCR_REG(BASE)      HWREG32(BASE + 0x50)   /* Mini Uart Modem Control 8bit */
#define AUX_MU_LSR_REG(BASE)      HWREG32(BASE + 0x54)   /* Mini Uart Line Status 8bit */
#define AUX_MU_MSR_REG(BASE)      HWREG32(BASE + 0x58)   /* Mini Uart Modem Status 8bit */
#define AUX_MU_SCRATCH(BASE)      HWREG32(BASE + 0x5C)   /* Mini Uart Scratch 8bit */
#define AUX_MU_CNTL_REG(BASE)     HWREG32(BASE + 0x60)   /* Mini Uart Extra Control 8bit */
#define AUX_MU_STAT_REG(BASE)     HWREG32(BASE + 0x64)   /* Mini Uart Extra Status 32bit */
#define AUX_MU_BAUD_REG(BASE)     HWREG32(BASE + 0x68)   /* Mini Uart Baudrate 16bit */
#define AUX_SPI0_CNTL0_REG(BASE)  HWREG32(BASE + 0x80)   /* SPI 1 Control register 0 32bit */
#define AUX_SPI0_CNTL1_REG(BASE)  HWREG32(BASE + 0x84)   /* SPI 1 Control register 1 8bit */
#define AUX_SPI0_STAT_REG(BASE)   HWREG32(BASE + 0x88)   /* SPI 1 Status 32bit */
#define AUX_SPI0_IO_REG(BASE)     HWREG32(BASE + 0x90)   /* SPI 1 Data 32bit */
#define AUX_SPI0_PEEK_REG(BASE)   HWREG32(BASE + 0x94)   /* SPI 1 Peek 16bit */
#define AUX_SPI1_CNTL0_REG(BASE)  HWREG32(BASE + 0xC0)   /* SPI 2 Control register 0 32bit */
#define AUX_SPI1_CNTL1_REG(BASE)  HWREG32(BASE + 0xC4)   /* SPI 2 Control register 1 8bit */

int rt_hw_uart_init(void);

#endif /* DRV_UART_H__ */

