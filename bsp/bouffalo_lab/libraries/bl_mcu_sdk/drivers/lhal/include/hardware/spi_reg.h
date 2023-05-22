/**
  ******************************************************************************
  * @file    spi_reg.h
  * @version V1.0
  * @date    2022-06-20
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __HARDWARE_SPI_H__
#define __HARDWARE_SPI_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define SPI_CONFIG_OFFSET        (0x0)  /* spi_config */
#define SPI_INT_STS_OFFSET       (0x4)  /* spi_int_sts */
#define SPI_BUS_BUSY_OFFSET      (0x8)  /* spi_bus_busy */
#define SPI_PRD_0_OFFSET         (0x10) /* spi_prd_0 */
#define SPI_PRD_1_OFFSET         (0x14) /* spi_prd_1 */
#define SPI_RXD_IGNR_OFFSET      (0x18) /* spi_rxd_ignr */
#define SPI_STO_VALUE_OFFSET     (0x1C) /* spi_sto_value */
#define SPI_FIFO_CONFIG_0_OFFSET (0x80) /* spi_fifo_config_0 */
#define SPI_FIFO_CONFIG_1_OFFSET (0x84) /* spi_fifo_config_1 */
#define SPI_FIFO_WDATA_OFFSET    (0x88) /* spi_fifo_wdata */
#define SPI_FIFO_RDATA_OFFSET    (0x8C) /* spi_fifo_rdata */
#if defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
#define SPI_BACKUP_IO_EN_OFFSET (0xFC) /* backup_io_en */
#endif
/* Register Bitfield definitions *****************************************************/

/* 0x0 : spi_config */
#define SPI_CR_SPI_M_EN             (1 << 0U)
#define SPI_CR_SPI_S_EN             (1 << 1U)
#define SPI_CR_SPI_FRAME_SIZE_SHIFT (2U)
#define SPI_CR_SPI_FRAME_SIZE_MASK  (0x3 << SPI_CR_SPI_FRAME_SIZE_SHIFT)
#define SPI_CR_SPI_SCLK_POL         (1 << 4U)
#define SPI_CR_SPI_SCLK_PH          (1 << 5U)
#define SPI_CR_SPI_BIT_INV          (1 << 6U)
#define SPI_CR_SPI_BYTE_INV         (1 << 7U)
#define SPI_CR_SPI_RXD_IGNR_EN      (1 << 8U)
#define SPI_CR_SPI_M_CONT_EN        (1 << 9U)
#define SPI_CR_SPI_S_3PIN_MODE      (1 << 10U)
#define SPI_CR_SPI_DEG_EN           (1 << 11U)
#define SPI_CR_SPI_DEG_CNT_SHIFT    (12U)
#define SPI_CR_SPI_DEG_CNT_MASK     (0xf << SPI_CR_SPI_DEG_CNT_SHIFT)

/* 0x4 : spi_int_sts */
#define SPI_END_INT         (1 << 0U)
#define SPI_TXF_INT         (1 << 1U)
#define SPI_RXF_INT         (1 << 2U)
#define SPI_STO_INT         (1 << 3U)
#define SPI_TXU_INT         (1 << 4U)
#define SPI_FER_INT         (1 << 5U)
#define SPI_CR_SPI_END_MASK (1 << 8U)
#define SPI_CR_SPI_TXF_MASK (1 << 9U)
#define SPI_CR_SPI_RXF_MASK (1 << 10U)
#define SPI_CR_SPI_STO_MASK (1 << 11U)
#define SPI_CR_SPI_TXU_MASK (1 << 12U)
#define SPI_CR_SPI_FER_MASK (1 << 13U)
#define SPI_CR_SPI_END_CLR  (1 << 16U)
#define SPI_CR_SPI_STO_CLR  (1 << 19U)
#define SPI_CR_SPI_TXU_CLR  (1 << 20U)
#define SPI_CR_SPI_END_EN   (1 << 24U)
#define SPI_CR_SPI_TXF_EN   (1 << 25U)
#define SPI_CR_SPI_RXF_EN   (1 << 26U)
#define SPI_CR_SPI_STO_EN   (1 << 27U)
#define SPI_CR_SPI_TXU_EN   (1 << 28U)
#define SPI_CR_SPI_FER_EN   (1 << 29U)

/* 0x8 : spi_bus_busy */
#define SPI_STS_SPI_BUS_BUSY (1 << 0U)

/* 0x10 : spi_prd_0 */
#define SPI_CR_SPI_PRD_S_SHIFT      (0U)
#define SPI_CR_SPI_PRD_S_MASK       (0xff << SPI_CR_SPI_PRD_S_SHIFT)
#define SPI_CR_SPI_PRD_P_SHIFT      (8U)
#define SPI_CR_SPI_PRD_P_MASK       (0xff << SPI_CR_SPI_PRD_P_SHIFT)
#define SPI_CR_SPI_PRD_D_PH_0_SHIFT (16U)
#define SPI_CR_SPI_PRD_D_PH_0_MASK  (0xff << SPI_CR_SPI_PRD_D_PH_0_SHIFT)
#define SPI_CR_SPI_PRD_D_PH_1_SHIFT (24U)
#define SPI_CR_SPI_PRD_D_PH_1_MASK  (0xff << SPI_CR_SPI_PRD_D_PH_1_SHIFT)

/* 0x14 : spi_prd_1 */
#define SPI_CR_SPI_PRD_I_SHIFT (0U)
#define SPI_CR_SPI_PRD_I_MASK  (0xff << SPI_CR_SPI_PRD_I_SHIFT)

/* 0x18 : spi_rxd_ignr */
#define SPI_CR_SPI_RXD_IGNR_P_SHIFT (0U)
#define SPI_CR_SPI_RXD_IGNR_P_MASK  (0x1f << SPI_CR_SPI_RXD_IGNR_P_SHIFT)
#define SPI_CR_SPI_RXD_IGNR_S_SHIFT (16U)
#define SPI_CR_SPI_RXD_IGNR_S_MASK  (0x1f << SPI_CR_SPI_RXD_IGNR_S_SHIFT)

/* 0x1C : spi_sto_value */
#define SPI_CR_SPI_STO_VALUE_SHIFT (0U)
#define SPI_CR_SPI_STO_VALUE_MASK  (0xfff << SPI_CR_SPI_STO_VALUE_SHIFT)

/* 0x80 : spi_fifo_config_0 */
#define SPI_DMA_TX_EN         (1 << 0U)
#define SPI_DMA_RX_EN         (1 << 1U)
#define SPI_TX_FIFO_CLR       (1 << 2U)
#define SPI_RX_FIFO_CLR       (1 << 3U)
#define SPI_TX_FIFO_OVERFLOW  (1 << 4U)
#define SPI_TX_FIFO_UNDERFLOW (1 << 5U)
#define SPI_RX_FIFO_OVERFLOW  (1 << 6U)
#define SPI_RX_FIFO_UNDERFLOW (1 << 7U)

/* 0x84 : spi_fifo_config_1 */
#define SPI_TX_FIFO_CNT_SHIFT (0U)
#if defined(BL702) || defined(BL602)
#define SPI_TX_FIFO_CNT_MASK (0x7 << SPI_TX_FIFO_CNT_SHIFT)
#elif defined(BL702L)
#define SPI_TX_FIFO_CNT_MASK (0x1f << SPI_TX_FIFO_CNT_SHIFT)
#elif defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
#define SPI_TX_FIFO_CNT_MASK (0x3f << SPI_TX_FIFO_CNT_SHIFT)
#endif
#define SPI_RX_FIFO_CNT_SHIFT (8U)
#if defined(BL702) || defined(BL602)
#define SPI_RX_FIFO_CNT_MASK (0x7 << SPI_RX_FIFO_CNT_SHIFT)
#elif defined(BL702L)
#define SPI_RX_FIFO_CNT_MASK (0x1f << SPI_RX_FIFO_CNT_SHIFT)
#elif defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
#define SPI_RX_FIFO_CNT_MASK (0x3f << SPI_RX_FIFO_CNT_SHIFT)
#endif
#define SPI_TX_FIFO_TH_SHIFT (16U)
#if defined(BL702) || defined(BL602)
#define SPI_TX_FIFO_TH_MASK (0x3 << SPI_TX_FIFO_TH_SHIFT)
#elif defined(BL702L)
#define SPI_TX_FIFO_TH_MASK (0xf << SPI_TX_FIFO_TH_SHIFT)
#elif defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
#define SPI_TX_FIFO_TH_MASK (0x1f << SPI_TX_FIFO_TH_SHIFT)
#endif
#define SPI_RX_FIFO_TH_SHIFT (24U)
#if defined(BL702) || defined(BL602)
#define SPI_RX_FIFO_TH_MASK (0x3 << SPI_RX_FIFO_TH_SHIFT)
#elif defined(BL702L)
#define SPI_RX_FIFO_TH_MASK (0xf << SPI_RX_FIFO_TH_SHIFT)
#elif defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
#define SPI_RX_FIFO_TH_MASK (0x1f << SPI_RX_FIFO_TH_SHIFT)
#endif

/* 0x88 : spi_fifo_wdata */
#define SPI_FIFO_WDATA_SHIFT (0U)
#define SPI_FIFO_WDATA_MASK  (0xffffffff << SPI_FIFO_WDATA_SHIFT)

/* 0x8C : spi_fifo_rdata */
#define SPI_FIFO_RDATA_SHIFT (0U)
#define SPI_FIFO_RDATA_MASK  (0xffffffff << SPI_FIFO_RDATA_SHIFT)

#if defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
/* 0xFC : backup_io_en */
#define SPI_BACKUP_IO_EN (1 << 0U)
#endif

#endif /* __HARDWARE_SPI_H__ */
