/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2012-02-13   mojingxian  first version
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#define CLKIN           33333000LL
#define SPEED_MULTIPLE  16
#define BUS_DIVISOR     4
#define CCLKSPEED       (CLKIN * SPEED_MULTIPLE)
#define SCLKSPEED       (CLKIN * BUS_DIVISOR)
#define CLOCKS_PER_SECD CCLKSPEED
#define SCLOCKS_PER_SEC SCLKSPEED

//SIC_IMASK寄存器
#define PLL_WAKEUP_INT_MASK     0x00000001
#define DMA_ERROR_INT_MASK      0x00000002
#define PPI_ERROR_INT_MASK      0x00000004
#define SPORT0_ERROR_INT_MASK   0x00000008
#define SPORT1_ERROR_INT_MASK   0x00000010
#define SPI_ERROR_INT_MASK      0x00000020
#define UART_ERROR_INT_MASK     0x00000040
#define RTC_INT_MASK            0x00000080
#define DMA0_PPI_INT_MASK       0x00000100
#define DMA1_SPORT0_RX_INT_MASK 0x00000200
#define DMA2_SPORT0_TX_INT_MASK 0x00000400
#define DMA3_SPORT1_RX_INT_MASK 0x00000800
#define DMA4_SPORT1_TX_INT_MASK 0x00001000
#define DMA5_SPI_INT_MASK       0x00002000
#define DMA6_UART_RX_INT_MASK   0x00004000
#define DMA7_UART_TX_INT_MASK   0x00008000
#define TIMER0_INT_MASK         0x00010000
#define TIMER1_INT_MASK         0x00020000
#define TIMER2_INT_MASK         0x00040000
#define PF_INTA_MASK            0x00080000
#define PF_INTB_MASK            0x00100000
#define MEM_DMA_STREAM0_MASK    0x00200000
#define MEM_DMA_STREAM1_MASK    0x00400000
#define SOFT_WATCHDOG_TMER_MASK 0x00800000

//SIC_IAR0
#define IAR0_PLL_WAKEUP_INT_IVG      0x00
#define IAR0_DMA_ERROR_INT_IVG       0x01
#define IAR0_PPI_ERROR_INT_IVG       0x02
#define IAR0_SPORT0_ERROR_INT_IVG    0x03
#define IAR0_SPORT1_ERROR_INT_IVG    0x04
#define IAR0_SPI_ERROR_INT_IVG       0x05
#define IAR0_UART_ERROR_INT_IVG      0x06
#define IAR0_RTC_INT_IVG             0x07

//SIC_IAR1
#define IAR1_DMA0_PPI_INT_IVG        0x00
#define IAR1_DMA1_SPORT0RX_IVG       0x01
#define IAR1_DMA2_SPORT0TX_IVG       0x02
#define IAR1_DMA3_SPORT1RX_IVG       0x03
#define IAR1_DMA4_SPORT1TX_IVG       0x04
#define IAR1_DMA5_SPI_INT_IVG        0x05
#define IAR1_DMA6_UARTRX_IVG         0x06
#define IAR1_DMA7_UARTTX_IVG         0x07

//SIC_IAR2
#define IAR2_TIMER0_INT_IVG          0x00
#define IAR2_TIMER1_INT_IVG          0x01
#define IAR2_TIMER2_INT_IVG          0x02
#define IAR2_PF_A_INT_IVG            0x03
#define IAR2_PF_B_INT_IVG            0x04
#define IAR2_MEM_DMA_STREAM0_INT_IVG 0x05
#define IAR2_MEM_DMA_STREAM1_INT_IVG 0x06
#define IAR2_SWATCHDOG_TIMER_INT_IVG 0x07

#ifdef __cplusplus
extern "C" {
#endif

void rt_hw_core_timer_init(void);
void rt_hw_board_init(void);
void rt_hw_isr_install(void);

#ifdef __cplusplus
}
#endif

#endif /* _BSP_H_ */
