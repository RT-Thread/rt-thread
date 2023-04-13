/**
  ******************************************************************************
  * @file    uart_reg.h
  * @version V1.0
  * @date    2022-06-10
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
#ifndef __HARDWARE_UART_H__
#define __HARDWARE_UART_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define UART_UTX_CONFIG_OFFSET  (0x0) /* utx_config */
#define UART_URX_CONFIG_OFFSET  (0x4) /* urx_config */
#define UART_BIT_PRD_OFFSET     (0x8) /* uart_bit_prd */
#define UART_DATA_CONFIG_OFFSET (0xC) /* data_config */
#if !defined(BL702L)
#define UART_UTX_IR_POSITION_OFFSET (0x10) /* utx_ir_position */
#define UART_URX_IR_POSITION_OFFSET (0x14) /* urx_ir_position */
#endif
#define UART_URX_RTO_TIMER_OFFSET (0x18) /* urx_rto_timer */
#if !defined(BL602)
#define UART_SW_MODE_OFFSET (0x1C) /* uart_sw_mode */
#endif
#define UART_INT_STS_OFFSET         (0x20) /* UART interrupt status */
#define UART_INT_MASK_OFFSET        (0x24) /* UART interrupt mask */
#define UART_INT_CLEAR_OFFSET       (0x28) /* UART interrupt clear */
#define UART_INT_EN_OFFSET          (0x2C) /* UART interrupt enable */
#define UART_STATUS_OFFSET          (0x30) /* uart_status */
#define UART_STS_URX_ABR_PRD_OFFSET (0x34) /* sts_urx_abr_prd */
#if !defined(BL602) && !defined(BL702)
#define UART_URX_ABR_PRD_B01_OFFSET (0x38) /* urx_abr_prd_b01 */
#define UART_URX_ABR_PRD_B23_OFFSET (0x3C) /* urx_abr_prd_b23 */
#define UART_URX_ABR_PRD_B45_OFFSET (0x40) /* urx_abr_prd_b45 */
#define UART_URX_ABR_PRD_B67_OFFSET (0x44) /* urx_abr_prd_b67 */
#define UART_URX_ABR_PW_TOL_OFFSET  (0x48) /* urx_abr_pw_tol */
#define UART_URX_BCR_INT_CFG_OFFSET (0x50) /* urx_bcr_int_cfg */
#define UART_UTX_RS485_CFG_OFFSET   (0x54) /* utx_rs485_cfg */
#endif
#define UART_FIFO_CONFIG_0_OFFSET (0x80) /* uart_fifo_config_0 */
#define UART_FIFO_CONFIG_1_OFFSET (0x84) /* uart_fifo_config_1 */
#define UART_FIFO_WDATA_OFFSET    (0x88) /* uart_fifo_wdata */
#define UART_FIFO_RDATA_OFFSET    (0x8C) /* uart_fifo_rdata */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : utx_config */
#define UART_CR_UTX_EN     (1 << 0U)
#define UART_CR_UTX_CTS_EN (1 << 1U)
#define UART_CR_UTX_FRM_EN (1 << 2U)
#if !defined(BL602)
#define UART_CR_UTX_LIN_EN (1 << 3U)
#endif
#define UART_CR_UTX_PRT_EN  (1 << 4U)
#define UART_CR_UTX_PRT_SEL (1 << 5U)
#if !defined(BL702L)
#define UART_CR_UTX_IR_EN  (1 << 6U)
#define UART_CR_UTX_IR_INV (1 << 7U)
#endif
#define UART_CR_UTX_BIT_CNT_D_SHIFT (8U)
#define UART_CR_UTX_BIT_CNT_D_MASK  (0x7 << UART_CR_UTX_BIT_CNT_D_SHIFT)
#if defined(BL602)
#define UART_CR_UTX_BIT_CNT_P_SHIFT (12U)
#else
#define UART_CR_UTX_BIT_CNT_P_SHIFT (11U)
#endif
#define UART_CR_UTX_BIT_CNT_P_MASK (0x3 << UART_CR_UTX_BIT_CNT_P_SHIFT)
#if !defined(BL602)
#define UART_CR_UTX_BIT_CNT_B_SHIFT (13U)
#define UART_CR_UTX_BIT_CNT_B_MASK  (0x7 << UART_CR_UTX_BIT_CNT_B_SHIFT)
#endif
#define UART_CR_UTX_LEN_SHIFT (16U)
#define UART_CR_UTX_LEN_MASK  (0xffff << UART_CR_UTX_LEN_SHIFT)

/* 0x4 : urx_config */
#define UART_CR_URX_EN (1 << 0U)
#if defined(BL602)
#define UART_CR_URX_RTS_SW_MODE (1 << 1U)
#define UART_CR_URX_RTS_SW_VAL  (1 << 2U)
#define UART_CR_URX_ABR_EN      (1 << 3U)
#else
#define UART_CR_URX_ABR_EN (1 << 1U)
#define UART_CR_URX_LIN_EN (1 << 3U)
#endif
#define UART_CR_URX_PRT_EN  (1 << 4U)
#define UART_CR_URX_PRT_SEL (1 << 5U)
#if !defined(BL702L)
#define UART_CR_URX_IR_EN  (1 << 6U)
#define UART_CR_URX_IR_INV (1 << 7U)
#endif
#define UART_CR_URX_BIT_CNT_D_SHIFT (8U)
#define UART_CR_URX_BIT_CNT_D_MASK  (0x7 << UART_CR_URX_BIT_CNT_D_SHIFT)
#define UART_CR_URX_DEG_EN          (1 << 11U)
#define UART_CR_URX_DEG_CNT_SHIFT   (12U)
#define UART_CR_URX_DEG_CNT_MASK    (0xf << UART_CR_URX_DEG_CNT_SHIFT)
#define UART_CR_URX_LEN_SHIFT       (16U)
#define UART_CR_URX_LEN_MASK        (0xffff << UART_CR_URX_LEN_SHIFT)

/* 0x8 : uart_bit_prd */
#define UART_CR_UTX_BIT_PRD_SHIFT (0U)
#define UART_CR_UTX_BIT_PRD_MASK  (0xffff << UART_CR_UTX_BIT_PRD_SHIFT)
#define UART_CR_URX_BIT_PRD_SHIFT (16U)
#define UART_CR_URX_BIT_PRD_MASK  (0xffff << UART_CR_URX_BIT_PRD_SHIFT)

/* 0xC : data_config */
#define UART_CR_UART_BIT_INV (1 << 0U)

#if !defined(BL702L)
/* 0x10 : utx_ir_position */
#define UART_CR_UTX_IR_POS_S_SHIFT (0U)
#define UART_CR_UTX_IR_POS_S_MASK  (0xffff << UART_CR_UTX_IR_POS_S_SHIFT)
#define UART_CR_UTX_IR_POS_P_SHIFT (16U)
#define UART_CR_UTX_IR_POS_P_MASK  (0xffff << UART_CR_UTX_IR_POS_P_SHIFT)

/* 0x14 : urx_ir_position */
#define UART_CR_URX_IR_POS_S_SHIFT (0U)
#define UART_CR_URX_IR_POS_S_MASK  (0xffff << UART_CR_URX_IR_POS_S_SHIFT)
#endif

/* 0x18 : urx_rto_timer */
#define UART_CR_URX_RTO_VALUE_SHIFT (0U)
#define UART_CR_URX_RTO_VALUE_MASK  (0xff << UART_CR_URX_RTO_VALUE_SHIFT)

#if !defined(BL602)
/* 0x1C : uart_sw_mode */
#define UART_CR_UTX_TXD_SW_MODE (1 << 0U)
#define UART_CR_UTX_TXD_SW_VAL  (1 << 1U)
#define UART_CR_URX_RTS_SW_MODE (1 << 2U)
#define UART_CR_URX_RTS_SW_VAL  (1 << 3U)
#endif

/* 0x20 : UART interrupt status */
#define UART_UTX_END_INT  (1 << 0U)
#define UART_URX_END_INT  (1 << 1U)
#define UART_UTX_FIFO_INT (1 << 2U)
#define UART_URX_FIFO_INT (1 << 3U)
#define UART_URX_RTO_INT  (1 << 4U)
#define UART_URX_PCE_INT  (1 << 5U)
#define UART_UTX_FER_INT  (1 << 6U)
#define UART_URX_FER_INT  (1 << 7U)
#if !defined(BL602)
#define UART_URX_LSE_INT (1 << 8U)
#endif
#if !defined(BL602) && !defined(BL702)
#define UART_URX_BCR_INT (1 << 9U)
#define UART_URX_ADS_INT (1 << 10U)
#define UART_URX_AD5_INT (1 << 11U)
#endif

/* 0x24 : UART interrupt mask */
#define UART_CR_UTX_END_MASK  (1 << 0U)
#define UART_CR_URX_END_MASK  (1 << 1U)
#define UART_CR_UTX_FIFO_MASK (1 << 2U)
#define UART_CR_URX_FIFO_MASK (1 << 3U)
#define UART_CR_URX_RTO_MASK  (1 << 4U)
#define UART_CR_URX_PCE_MASK  (1 << 5U)
#define UART_CR_UTX_FER_MASK  (1 << 6U)
#define UART_CR_URX_FER_MASK  (1 << 7U)
#if !defined(BL602)
#define UART_CR_URX_LSE_MASK (1 << 8U)
#endif
#if !defined(BL602) && !defined(BL702)
#define UART_CR_URX_BCR_MASK (1 << 9U)
#define UART_CR_URX_ADS_MASK (1 << 10U)
#define UART_CR_URX_AD5_MASK (1 << 11U)
#endif

/* 0x28 : UART interrupt clear */
#define UART_CR_UTX_END_CLR (1 << 0U)
#define UART_CR_URX_END_CLR (1 << 1U)
#define UART_CR_URX_RTO_CLR (1 << 4U)
#define UART_CR_URX_PCE_CLR (1 << 5U)
#if !defined(BL602)
#define UART_CR_URX_LSE_CLR (1 << 8U)
#endif
#if !defined(BL602) && !defined(BL702)
#define UART_CR_URX_BCR_CLR (1 << 9U)
#define UART_CR_URX_ADS_CLR (1 << 10U)
#define UART_CR_URX_AD5_CLR (1 << 11U)
#endif

/* 0x2C : UART interrupt enable */
#define UART_CR_UTX_END_EN  (1 << 0U)
#define UART_CR_URX_END_EN  (1 << 1U)
#define UART_CR_UTX_FIFO_EN (1 << 2U)
#define UART_CR_URX_FIFO_EN (1 << 3U)
#define UART_CR_URX_RTO_EN  (1 << 4U)
#define UART_CR_URX_PCE_EN  (1 << 5U)
#define UART_CR_UTX_FER_EN  (1 << 6U)
#define UART_CR_URX_FER_EN  (1 << 7U)
#if !defined(BL602)
#define UART_CR_URX_LSE_EN (1 << 8U)
#endif
#if !defined(BL602) && !defined(BL702)
#define UART_CR_URX_BCR_EN (1 << 9U)
#define UART_CR_URX_ADS_EN (1 << 10U)
#define UART_CR_URX_AD5_EN (1 << 11U)
#endif

/* 0x30 : uart_status */
#define UART_STS_UTX_BUS_BUSY (1 << 0U)
#define UART_STS_URX_BUS_BUSY (1 << 1U)

/* 0x34 : sts_urx_abr_prd */
#define UART_STS_URX_ABR_PRD_START_SHIFT (0U)
#define UART_STS_URX_ABR_PRD_START_MASK  (0xffff << UART_STS_URX_ABR_PRD_START_SHIFT)
#define UART_STS_URX_ABR_PRD_0X55_SHIFT  (16U)
#if defined(BL702L)
#define UART_STS_URX_ABR_PRD_0X55_MASK (0x3ff << UART_STS_URX_ABR_PRD_0X55_SHIFT)
#else
#define UART_STS_URX_ABR_PRD_0X55_MASK (0xffff << UART_STS_URX_ABR_PRD_0X55_SHIFT)
#endif

#if !defined(BL602) && !defined(BL702)
/* 0x38 : urx_abr_prd_b01 */
#define UART_STS_URX_ABR_PRD_BIT0_SHIFT (0U)
#if defined(BL702L)
#define UART_STS_URX_ABR_PRD_BIT0_MASK (0x3ff << UART_STS_URX_ABR_PRD_BIT0_SHIFT)
#else
#define UART_STS_URX_ABR_PRD_BIT0_MASK (0xffff << UART_STS_URX_ABR_PRD_BIT0_SHIFT)
#endif
#define UART_STS_URX_ABR_PRD_BIT1_SHIFT (16U)
#if defined(BL702L)
#define UART_STS_URX_ABR_PRD_BIT1_MASK (0x3ff << UART_STS_URX_ABR_PRD_BIT1_SHIFT)
#else
#define UART_STS_URX_ABR_PRD_BIT1_MASK (0xffff << UART_STS_URX_ABR_PRD_BIT1_SHIFT)
#endif

/* 0x3C : urx_abr_prd_b23 */
#define UART_STS_URX_ABR_PRD_BIT2_SHIFT (0U)
#if defined(BL702L)
#define UART_STS_URX_ABR_PRD_BIT2_MASK (0x3ff << UART_STS_URX_ABR_PRD_BIT2_SHIFT)
#else
#define UART_STS_URX_ABR_PRD_BIT2_MASK (0xffff << UART_STS_URX_ABR_PRD_BIT2_SHIFT)
#endif
#define UART_STS_URX_ABR_PRD_BIT3_SHIFT (16U)
#if defined(BL702L)
#define UART_STS_URX_ABR_PRD_BIT3_MASK (0x3ff << UART_STS_URX_ABR_PRD_BIT3_SHIFT)
#else
#define UART_STS_URX_ABR_PRD_BIT3_MASK (0xffff << UART_STS_URX_ABR_PRD_BIT3_SHIFT)
#endif

/* 0x40 : urx_abr_prd_b45 */
#define UART_STS_URX_ABR_PRD_BIT4_SHIFT (0U)
#if defined(BL702L)
#define UART_STS_URX_ABR_PRD_BIT4_MASK (0x3ff << UART_STS_URX_ABR_PRD_BIT4_SHIFT)
#else
#define UART_STS_URX_ABR_PRD_BIT4_MASK (0xffff << UART_STS_URX_ABR_PRD_BIT4_SHIFT)
#endif
#define UART_STS_URX_ABR_PRD_BIT5_SHIFT (16U)
#if defined(BL702L)
#define UART_STS_URX_ABR_PRD_BIT5_MASK (0x3ff << UART_STS_URX_ABR_PRD_BIT5_SHIFT)
#else
#define UART_STS_URX_ABR_PRD_BIT5_MASK (0xffff << UART_STS_URX_ABR_PRD_BIT5_SHIFT)
#endif

/* 0x44 : urx_abr_prd_b67 */
#define UART_STS_URX_ABR_PRD_BIT6_SHIFT (0U)
#if defined(BL702L)
#define UART_STS_URX_ABR_PRD_BIT6_MASK (0x3ff << UART_STS_URX_ABR_PRD_BIT6_SHIFT)
#else
#define UART_STS_URX_ABR_PRD_BIT6_MASK (0xffff << UART_STS_URX_ABR_PRD_BIT6_SHIFT)
#endif
#define UART_STS_URX_ABR_PRD_BIT7_SHIFT (16U)
#if defined(BL702L)
#define UART_STS_URX_ABR_PRD_BIT7_MASK (0x3ff << UART_STS_URX_ABR_PRD_BIT7_SHIFT)
#else
#define UART_STS_URX_ABR_PRD_BIT7_MASK (0xffff << UART_STS_URX_ABR_PRD_BIT7_SHIFT)
#endif

/* 0x48 : urx_abr_pw_tol */
#define UART_CR_URX_ABR_PW_TOL_SHIFT (0U)
#define UART_CR_URX_ABR_PW_TOL_MASK  (0xff << UART_CR_URX_ABR_PW_TOL_SHIFT)

/* 0x50 : urx_bcr_int_cfg */
#define UART_CR_URX_BCR_VALUE_SHIFT  (0U)
#define UART_CR_URX_BCR_VALUE_MASK   (0xffff << UART_CR_URX_BCR_VALUE_SHIFT)
#define UART_STS_URX_BCR_COUNT_SHIFT (16U)
#define UART_STS_URX_BCR_COUNT_MASK  (0xffff << UART_STS_URX_BCR_COUNT_SHIFT)

/* 0x54 : utx_rs485_cfg */
#define UART_CR_UTX_RS485_EN  (1 << 0U)
#define UART_CR_UTX_RS485_POL (1 << 1U)
#endif

/* 0x80 : uart_fifo_config_0 */
#define UART_DMA_TX_EN         (1 << 0U)
#define UART_DMA_RX_EN         (1 << 1U)
#define UART_TX_FIFO_CLR       (1 << 2U)
#define UART_RX_FIFO_CLR       (1 << 3U)
#define UART_TX_FIFO_OVERFLOW  (1 << 4U)
#define UART_TX_FIFO_UNDERFLOW (1 << 5U)
#define UART_RX_FIFO_OVERFLOW  (1 << 6U)
#define UART_RX_FIFO_UNDERFLOW (1 << 7U)

/* 0x84 : uart_fifo_config_1 */
#define UART_TX_FIFO_CNT_SHIFT (0U)
#if defined(BL702)
#define UART_TX_FIFO_CNT_MASK (0xff << UART_TX_FIFO_CNT_SHIFT)
#elif defined(BL702L)
#define UART_TX_FIFO_CNT_MASK (0x1f << UART_TX_FIFO_CNT_SHIFT)
#else
#define UART_TX_FIFO_CNT_MASK (0x3f << UART_TX_FIFO_CNT_SHIFT)
#endif
#define UART_RX_FIFO_CNT_SHIFT (8U)
#if defined(BL702)
#define UART_RX_FIFO_CNT_MASK (0xff << UART_RX_FIFO_CNT_SHIFT)
#elif defined(BL702L)
#define UART_RX_FIFO_CNT_MASK (0x1f << UART_RX_FIFO_CNT_SHIFT)
#else
#define UART_RX_FIFO_CNT_MASK (0x3f << UART_RX_FIFO_CNT_SHIFT)
#endif
#define UART_TX_FIFO_TH_SHIFT (16U)
#if defined(BL702)
#define UART_TX_FIFO_TH_MASK (0x7f << UART_TX_FIFO_TH_SHIFT)
#elif defined(BL702L)
#define UART_TX_FIFO_TH_MASK (0xf << UART_TX_FIFO_TH_SHIFT)
#else
#define UART_TX_FIFO_TH_MASK (0x1f << UART_TX_FIFO_TH_SHIFT)
#endif
#define UART_RX_FIFO_TH_SHIFT (24U)
#if defined(BL702)
#define UART_RX_FIFO_TH_MASK (0x7f << UART_RX_FIFO_TH_SHIFT)
#elif defined(BL702L)
#define UART_RX_FIFO_TH_MASK (0xf << UART_RX_FIFO_TH_SHIFT)
#else
#define UART_RX_FIFO_TH_MASK (0x1f << UART_RX_FIFO_TH_SHIFT)
#endif

/* 0x88 : uart_fifo_wdata */
#define UART_FIFO_WDATA_SHIFT (0U)
#define UART_FIFO_WDATA_MASK  (0xff << UART_FIFO_WDATA_SHIFT)

/* 0x8C : uart_fifo_rdata */
#define UART_FIFO_RDATA_SHIFT (0U)
#define UART_FIFO_RDATA_MASK  (0xff << UART_FIFO_RDATA_SHIFT)

#endif /* __HARDWARE_UART_H__ */
