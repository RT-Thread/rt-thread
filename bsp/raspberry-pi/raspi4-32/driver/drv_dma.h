/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-12-02    bigmagic       first version
 */
#ifndef __DRV_DMA_H__
#define __DRV_DMA_H__

#include <rthw.h>

#define DMA_PER_BASE                    (0xFE000000)

//DMA
#define DMA_BASE        (DMA_PER_BASE+0x7000)
#define DMA_INT_STATUS  (DMA_BASE + 0xFE0)          //Interrupt Status of each DMA Channel
#define DMA_ENABLE      (DMA_BASE + 0xFF0)          //Global Enable bits for each DMA Channel */
#define DMA15_BASE      (DMA_PER_BASE+0xE05000)     //DMA Channel 15 Register Set */


#define DMA_INT_STATUS_REG          __REG32(DMA_INT_STATUS)
#define DMA_ENABLE_REG              __REG32(DMA_ENABLE)
//DMA dch 1~14
#define DMA_CS(dch)                 __REG32(DMA_BASE + dch*0x100 + 0x000)    /* Control and Status */
#define DMA_CONBLK_AD(dch)          __REG32(DMA_BASE + dch*0x100 + 0x004)    /* Control Block Address */
#define DMA_TI(dch)                 __REG32(DMA_BASE + dch*0x100 + 0x008)    /* CB Word 0(Transfer Information) */
#define DMA_SOURCE_AD(dch)          __REG32(DMA_BASE + dch*0x100 + 0x00c)    /* CB Word 1(Source Address) */
#define DMA_DEST_AD(dch)            __REG32(DMA_BASE + dch*0x100 + 0x010)    /* CB Word 2(Destination Address) */
#define DMA_TXFR_LEN(dch)           __REG32(DMA_BASE + dch*0x100 + 0x014)    /* CB Word 3(Transfer Length) */
#define DMA_STRIDE(dch)             __REG32(DMA_BASE + dch*0x100 + 0x018)    /* CB Word 4(2D Stride) */
#define DMA_NEXTCONBK(dch)          __REG32(DMA_BASE + dch*0x100 + 0x01c)    /* CB Word 5(Next CB Address) */
#define DMA_DEBUG(dch)              __REG32(DMA_BASE + dch*0x100 + 0x01c)    /* Debug */

//DMA dch 15
#define DMA15_CS                    __REG32(DMA15_BASE + 0x000)    /* Control and Status */
#define DMA15_CONBLK_AD             __REG32(DMA15_BASE + 0x004)    /* Control Block Address */
#define DMA15_TI                    __REG32(DMA15_BASE + 0x008)    /* CB Word 0(Transfer Information) */
#define DMA15_SOURCE_AD             __REG32(DMA15_BASE + 0x00c)    /* CB Word 1(Source Address) */
#define DMA15_DEST_AD               __REG32(DMA15_BASE + 0x010)    /* CB Word 2(Destination Address) */
#define DMA15_TXFR_LEN              __REG32(DMA15_BASE + 0x014)    /* CB Word 3(Transfer Length) */
#define DMA15_STRIDE                __REG32(DMA15_BASE + 0x018)    /* CB Word 4(2D Stride) */
#define DMA15_NEXTCONBK             __REG32(DMA15_BASE + 0x01c)    /* CB Word 5(Next CB Address) */
#define DMA15_DEBUG                 __REG32(DMA15_BASE + 0x01c)    /* Debug */

#define DMA15_ENABLE             (1 << 15)
#define DMA14_ENABLE             (1 << 14)
#define DMA13_ENABLE             (1 << 13)
#define DMA12_ENABLE             (1 << 12)
#define DMA11_ENABLE             (1 << 11)
#define DMA10_ENABLE             (1 << 10)
#define DMA9_ENABLE              (1 << 9)
#define DMA8_ENABLE              (1 << 8)
#define DMA7_ENABLE              (1 << 7)
#define DMA6_ENABLE              (1 << 6)
#define DMA5_ENABLE              (1 << 5)
#define DMA4_ENABLE              (1 << 4)
#define DMA3_ENABLE              (1 << 3)
#define DMA2_ENABLE              (1 << 2)
#define DMA1_ENABLE              (1 << 1)
#define DMA0_ENABLE              (1 << 0)

//Peripheral DREQ Signals
#define DREQ_DSI0_PWM1        (1)
#define DREQ_PCM_TX           (2)
#define DREQ_PCM_RX           (3)
#define DREQ_SMI              (4)
#define DREQ_PWM0             (5)
#define DREQ_SPI0_TX          (6)
#define DREQ_SPI0_RX          (7)
#define DREQ_BSC_SPI_SLAVE_TX (8)
#define DREQ_BSC_SPI_SLAVE_RX (9)
#define DREQ_HSMI0            (10)
#define DREQ_EMMC             (11)
#define DREQ_UART0_TX         (12)
#define DREQ_SD_HOST          (13)
#define DREQ_UART0_RX         (14)
#define DREQ_DSI1             (15)
#define DREQ_SPI1_TX          (16)
#define DREQ_HDMI1            (17)
#define DREQ_SPI1_RX          (18)
#define DREQ_UART3_TX_SPI4_TX (19)
#define DREQ_UART3_RX_SPI4_RX (20)
#define DREQ_UART5_TX_SPI5_TX (21)
#define DREQ_UART5_RX_SPI5_RX (22)
#define DREQ_SPI6_TX          (23)
#define DREQ_SCALER_FIFO0_SMI (24)
#define DREQ_SCALER_FIFO1_SMI (25)
#define DREQ_SCALER_FIFO2_SMI (26)
#define DREQ_SPI6_RX          (27)
#define DREQ_UART2_TX         (28)
#define DREQ_UART2_RX         (29)
#define DREQ_UART4_TX         (30)
#define DREQ_UART4_RX         (31)

//IRQ
#define DMA_INT15           (1 << 15)
#define DMA_INT14           (1 << 14)
#define DMA_INT13           (1 << 13)
#define DMA_INT12           (1 << 12)
#define DMA_INT11           (1 << 11)
#define DMA_INT10           (1 << 10)
#define DMA_INT9            (1 << 9)
#define DMA_INT8            (1 << 8)
#define DMA_INT7            (1 << 7)
#define DMA_INT6            (1 << 6)
#define DMA_INT5            (1 << 5)
#define DMA_INT4            (1 << 4)
#define DMA_INT3            (1 << 3)
#define DMA_INT2            (1 << 2)
#define DMA_INT1            (1 << 1)
#define DMA_INT0            (1 << 0)

//IRQ_NUMBER
#define IRQ_DMA0            (96 + 16)
#define IRQ_DMA1            (96 + 17)
#define IRQ_DMA2            (96 + 18)
#define IRQ_DMA3            (96 + 19)
#define IRQ_DMA4            (96 + 20)
#define IRQ_DMA5            (96 + 21)
#define IRQ_DMA6            (96 + 22)
#define IRQ_DMA7_DMA8       (96 + 23)
#define IRQ_DMA9_DMA10      (96 + 24)
#define IRQ_DMA11           (96 + 25)
#define IRQ_DMA12           (96 + 26)
#define IRQ_DMA13           (96 + 27)
#define IRQ_DMA14           (96 + 28)
#define IRQ_DMA15           (96 + 31)

//CS
#define DMA_CS_RESET            (1 << 31)
#define DMA_CS_ABORT            (1 << 30)
#define DMA_CS_DISDEBUG         (1 << 29)
#define DMA_CS_DREQ_STOPS_DMA   (1 << 5)
#define DMA_CS_PAUSED           (1 << 4)
#define DMA_CS_DREQ             (1 << 3)
#define DMA_CS_INT              (1 << 2)
#define DMA_CS_END              (1 << 1)
#define DMA_CS_ACTIVE           (1 << 0)

//CONBLK_AD
//The address must be256-bit aligned, so the bottom 5 bits of the address mustbe zero.

//TI
//DMA Transfer Information.
#define DMA_TI_SRC_IGNORE       (1 << 11)
#define DMA_TI_SRC_DREQ         (1 << 10)
#define DMA_TI_SRC_WIDTH        (1 << 9)
#define DMA_TI_SRC_INC          (1 << 8)
#define DMA_TI_DEST_IGNORE      (1 << 7)
#define DMA_TI_DEST_DREQ        (1 << 6)
#define DMA_TI_DEST_WIDTH       (1 << 5)
#define DMA_TI_DEST_INC         (1 << 4)
#define DMA_TI_WAIT_RESP        (1 << 3)
#define DMA_TI_TDMODE           (1 << 1)
#define DMA_TI_INTEN            (1 << 0)

//SOURCE_AD
//DMA Source Address

//DEST_AD
//DMA Destination Address

//TXFR_LEN
//DMA Transfer Length

void dma_init(unsigned char dch);
rt_err_t dma_memcpy(void *src, void *dst, unsigned int size, unsigned int dch, unsigned int timeout);

#endif
