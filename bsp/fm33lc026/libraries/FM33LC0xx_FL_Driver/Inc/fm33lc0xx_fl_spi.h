/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_spi.h
  * @author  FMSH Application Team
  * @brief   Head file of SPI FL Module
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  *******************************************************************************************************
  */


/* Define to prevent recursive inclusion---------------------------------------------------------------*/
#ifndef __FM33LC0XX_FL_SPI_H
#define __FM33LC0XX_FL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup SPI SPI
  * @brief SPI FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup SPI_FL_ES_INIT SPI Exported Init structures
  * @{
  */

/**
  * @brief FL SPI Init Sturcture definition
  */
typedef struct
{
    /*! 传输模式 单双工 */
    uint32_t transferMode;
    /*! 主从模式 */
    uint32_t mode;
    /*! 数据位宽 */
    uint32_t dataWidth;
    /*! 时钟极性 */
    uint32_t clockPolarity;
    /*! 时钟相位 */
    uint32_t clockPhase;
    /*! NSS 脚使能软件控制 */
    uint32_t softControl;
    /*! 通讯速率 */
    uint32_t baudRate;
    /*! Bit方向 */
    uint32_t bitOrder;

} FL_SPI_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup SPI_FL_Exported_Constants SPI Exported Constants
  * @{
  */

#define    SPI_CR1_IOSWAP_Pos                                     (11U)
#define    SPI_CR1_IOSWAP_Msk                                     (0x1U << SPI_CR1_IOSWAP_Pos)
#define    SPI_CR1_IOSWAP                                         SPI_CR1_IOSWAP_Msk

#define    SPI_CR1_MSPA_Pos                                       (10U)
#define    SPI_CR1_MSPA_Msk                                       (0x1U << SPI_CR1_MSPA_Pos)
#define    SPI_CR1_MSPA                                           SPI_CR1_MSPA_Msk

#define    SPI_CR1_SSPA_Pos                                       (9U)
#define    SPI_CR1_SSPA_Msk                                       (0x1U << SPI_CR1_SSPA_Pos)
#define    SPI_CR1_SSPA                                           SPI_CR1_SSPA_Msk

#define    SPI_CR1_MM_Pos                                         (8U)
#define    SPI_CR1_MM_Msk                                         (0x1U << SPI_CR1_MM_Pos)
#define    SPI_CR1_MM                                             SPI_CR1_MM_Msk

#define    SPI_CR1_WAIT_Pos                                       (6U)
#define    SPI_CR1_WAIT_Msk                                       (0x3U << SPI_CR1_WAIT_Pos)
#define    SPI_CR1_WAIT                                           SPI_CR1_WAIT_Msk

#define    SPI_CR1_BAUD_Pos                                       (3U)
#define    SPI_CR1_BAUD_Msk                                       (0x7U << SPI_CR1_BAUD_Pos)
#define    SPI_CR1_BAUD                                           SPI_CR1_BAUD_Msk

#define    SPI_CR1_LSBF_Pos                                       (2U)
#define    SPI_CR1_LSBF_Msk                                       (0x1U << SPI_CR1_LSBF_Pos)
#define    SPI_CR1_LSBF                                           SPI_CR1_LSBF_Msk

#define    SPI_CR1_CPOL_Pos                                       (1U)
#define    SPI_CR1_CPOL_Msk                                       (0x1U << SPI_CR1_CPOL_Pos)
#define    SPI_CR1_CPOL                                           SPI_CR1_CPOL_Msk

#define    SPI_CR1_CPHA_Pos                                       (0U)
#define    SPI_CR1_CPHA_Msk                                       (0x1U << SPI_CR1_CPHA_Pos)
#define    SPI_CR1_CPHA                                           SPI_CR1_CPHA_Msk

#define    SPI_CR2_DUMMY_EN_Pos                                   (15U)
#define    SPI_CR2_DUMMY_EN_Msk                                   (0x1U << SPI_CR2_DUMMY_EN_Pos)
#define    SPI_CR2_DUMMY_EN                                       SPI_CR2_DUMMY_EN_Msk

#define    SPI_CR2_RXO_Pos                                        (11U)
#define    SPI_CR2_RXO_Msk                                        (0x1U << SPI_CR2_RXO_Pos)
#define    SPI_CR2_RXO                                            SPI_CR2_RXO_Msk

#define    SPI_CR2_DLEN_Pos                                       (9U)
#define    SPI_CR2_DLEN_Msk                                       (0x3U << SPI_CR2_DLEN_Pos)
#define    SPI_CR2_DLEN                                           SPI_CR2_DLEN_Msk

#define    SPI_CR2_HALFDUPLEX_Pos                                 (8U)
#define    SPI_CR2_HALFDUPLEX_Msk                                 (0x1U << SPI_CR2_HALFDUPLEX_Pos)
#define    SPI_CR2_HALFDUPLEX                                     SPI_CR2_HALFDUPLEX_Msk

#define    SPI_CR2_HD_RW_Pos                                      (7U)
#define    SPI_CR2_HD_RW_Msk                                      (0x1U << SPI_CR2_HD_RW_Pos)
#define    SPI_CR2_HD_RW                                          SPI_CR2_HD_RW_Msk

#define    SPI_CR2_CMD8B_Pos                                      (6U)
#define    SPI_CR2_CMD8B_Msk                                      (0x1U << SPI_CR2_CMD8B_Pos)
#define    SPI_CR2_CMD8B                                          SPI_CR2_CMD8B_Msk

#define    SPI_CR2_SSNM_Pos                                       (5U)
#define    SPI_CR2_SSNM_Msk                                       (0x1U << SPI_CR2_SSNM_Pos)
#define    SPI_CR2_SSNM                                           SPI_CR2_SSNM_Msk

#define    SPI_CR2_TXO_AC_Pos                                     (4U)
#define    SPI_CR2_TXO_AC_Msk                                     (0x1U << SPI_CR2_TXO_AC_Pos)
#define    SPI_CR2_TXO_AC                                         SPI_CR2_TXO_AC_Msk

#define    SPI_CR2_TXO_Pos                                        (3U)
#define    SPI_CR2_TXO_Msk                                        (0x1U << SPI_CR2_TXO_Pos)
#define    SPI_CR2_TXO                                            SPI_CR2_TXO_Msk

#define    SPI_CR2_SSN_Pos                                        (2U)
#define    SPI_CR2_SSN_Msk                                        (0x1U << SPI_CR2_SSN_Pos)
#define    SPI_CR2_SSN                                            SPI_CR2_SSN_Msk

#define    SPI_CR2_SSNSEN_Pos                                     (1U)
#define    SPI_CR2_SSNSEN_Msk                                     (0x1U << SPI_CR2_SSNSEN_Pos)
#define    SPI_CR2_SSNSEN                                         SPI_CR2_SSNSEN_Msk

#define    SPI_CR2_SPIEN_Pos                                      (0U)
#define    SPI_CR2_SPIEN_Msk                                      (0x1U << SPI_CR2_SPIEN_Pos)
#define    SPI_CR2_SPIEN                                          SPI_CR2_SPIEN_Msk

#define    SPI_CR3_TXBFC_Pos                                      (3U)
#define    SPI_CR3_TXBFC_Msk                                      (0x1U << SPI_CR3_TXBFC_Pos)
#define    SPI_CR3_TXBFC                                          SPI_CR3_TXBFC_Msk

#define    SPI_CR3_RXBFC_Pos                                      (2U)
#define    SPI_CR3_RXBFC_Msk                                      (0x1U << SPI_CR3_RXBFC_Pos)
#define    SPI_CR3_RXBFC                                          SPI_CR3_RXBFC_Msk

#define    SPI_CR3_MERRC_Pos                                      (1U)
#define    SPI_CR3_MERRC_Msk                                      (0x1U << SPI_CR3_MERRC_Pos)
#define    SPI_CR3_MERRC                                          SPI_CR3_MERRC_Msk

#define    SPI_CR3_SERRC_Pos                                      (0U)
#define    SPI_CR3_SERRC_Msk                                      (0x1U << SPI_CR3_SERRC_Pos)
#define    SPI_CR3_SERRC                                          SPI_CR3_SERRC_Msk

#define    SPI_IER_ERRIE_Pos                                      (2U)
#define    SPI_IER_ERRIE_Msk                                      (0x1U << SPI_IER_ERRIE_Pos)
#define    SPI_IER_ERRIE                                          SPI_IER_ERRIE_Msk

#define    SPI_IER_TXIE_Pos                                       (1U)
#define    SPI_IER_TXIE_Msk                                       (0x1U << SPI_IER_TXIE_Pos)
#define    SPI_IER_TXIE                                           SPI_IER_TXIE_Msk

#define    SPI_IER_RXIE_Pos                                       (0U)
#define    SPI_IER_RXIE_Msk                                       (0x1U << SPI_IER_RXIE_Pos)
#define    SPI_IER_RXIE                                           SPI_IER_RXIE_Msk

#define    SPI_ISR_DCN_TX_Pos                                     (12U)
#define    SPI_ISR_DCN_TX_Msk                                     (0x1U << SPI_ISR_DCN_TX_Pos)
#define    SPI_ISR_DCN_TX                                         SPI_ISR_DCN_TX_Msk

#define    SPI_ISR_RXCOL_Pos                                      (10U)
#define    SPI_ISR_RXCOL_Msk                                      (0x1U << SPI_ISR_RXCOL_Pos)
#define    SPI_ISR_RXCOL                                          SPI_ISR_RXCOL_Msk

#define    SPI_ISR_TXCOL_Pos                                      (9U)
#define    SPI_ISR_TXCOL_Msk                                      (0x1U << SPI_ISR_TXCOL_Pos)
#define    SPI_ISR_TXCOL                                          SPI_ISR_TXCOL_Msk

#define    SPI_ISR_BUSY_Pos                                       (8U)
#define    SPI_ISR_BUSY_Msk                                       (0x1U << SPI_ISR_BUSY_Pos)
#define    SPI_ISR_BUSY                                           SPI_ISR_BUSY_Msk

#define    SPI_ISR_MERR_Pos                                       (6U)
#define    SPI_ISR_MERR_Msk                                       (0x1U << SPI_ISR_MERR_Pos)
#define    SPI_ISR_MERR                                           SPI_ISR_MERR_Msk

#define    SPI_ISR_SERR_Pos                                       (5U)
#define    SPI_ISR_SERR_Msk                                       (0x1U << SPI_ISR_SERR_Pos)
#define    SPI_ISR_SERR                                           SPI_ISR_SERR_Msk

#define    SPI_ISR_TXBE_Pos                                       (1U)
#define    SPI_ISR_TXBE_Msk                                       (0x1U << SPI_ISR_TXBE_Pos)
#define    SPI_ISR_TXBE                                           SPI_ISR_TXBE_Msk

#define    SPI_ISR_RXBF_Pos                                       (0U)
#define    SPI_ISR_RXBF_Msk                                       (0x1U << SPI_ISR_RXBF_Pos)
#define    SPI_ISR_RXBF                                           SPI_ISR_RXBF_Msk






#define    FL_SPI_MASTER_SAMPLING_NORMAL                          (0x0U << SPI_CR1_MSPA_Pos)
#define    FL_SPI_MASTER_SAMPLING_DELAY_HALFCLK                   (0x1U << SPI_CR1_MSPA_Pos)


#define    FL_SPI_SLAVE_SAMPLING_NORMAL                           (0x0U << SPI_CR1_SSPA_Pos)
#define    FL_SPI_SLAVE_SAMPLING_ADVANCE_HALFCLK                  (0x1U << SPI_CR1_SSPA_Pos)


#define    FL_SPI_WORK_MODE_SLAVE                                 (0x0U << SPI_CR1_MM_Pos)
#define    FL_SPI_WORK_MODE_MASTER                                (0x1U << SPI_CR1_MM_Pos)


#define    FL_SPI_SEND_WAIT_1                                     (0x0U << SPI_CR1_WAIT_Pos)
#define    FL_SPI_SEND_WAIT_2                                     (0x1U << SPI_CR1_WAIT_Pos)
#define    FL_SPI_SEND_WAIT_3                                     (0x2U << SPI_CR1_WAIT_Pos)
#define    FL_SPI_SEND_WAIT_4                                     (0x3U << SPI_CR1_WAIT_Pos)


#define    FL_SPI_CLK_DIV2                                        (0x0U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_CLK_DIV4                                        (0x1U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_CLK_DIV8                                        (0x2U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_CLK_DIV16                                       (0x3U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_CLK_DIV32                                       (0x4U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_CLK_DIV64                                       (0x5U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_CLK_DIV128                                      (0x6U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_CLK_DIV256                                      (0x7U << SPI_CR1_BAUD_Pos)

#define    FL_SPI_BAUDRATE_DIV2                                   (0x0U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_BAUDRATE_DIV4                                   (0x1U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_BAUDRATE_DIV8                                   (0x2U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_BAUDRATE_DIV16                                  (0x3U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_BAUDRATE_DIV32                                  (0x4U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_BAUDRATE_DIV64                                  (0x5U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_BAUDRATE_DIV128                                 (0x6U << SPI_CR1_BAUD_Pos)
#define    FL_SPI_BAUDRATE_DIV256                                 (0x7U << SPI_CR1_BAUD_Pos)

#define    FL_SPI_BIT_ORDER_MSB_FIRST                             (0x0U << SPI_CR1_LSBF_Pos)
#define    FL_SPI_BIT_ORDER_LSB_FIRST                             (0x1U << SPI_CR1_LSBF_Pos)


#define    FL_SPI_POLARITY_NORMAL                                 (0x0U << SPI_CR1_CPOL_Pos)
#define    FL_SPI_POLARITY_INVERT                                 (0x1U << SPI_CR1_CPOL_Pos)


#define    FL_SPI_PHASE_EDGE1                                     (0x0U << SPI_CR1_CPHA_Pos)
#define    FL_SPI_PHASE_EDGE2                                     (0x1U << SPI_CR1_CPHA_Pos)


#define    FL_SPI_DATA_WIDTH_8B                                   (0x0U << SPI_CR2_DLEN_Pos)
#define    FL_SPI_DATA_WIDTH_16B                                  (0x1U << SPI_CR2_DLEN_Pos)
#define    FL_SPI_DATA_WIDTH_24B                                  (0x2U << SPI_CR2_DLEN_Pos)
#define    FL_SPI_DATA_WIDTH_32B                                  (0x3U << SPI_CR2_DLEN_Pos)


#define    FL_SPI_TRANSFER_MODE_FULL_DUPLEX                       (0x0U << SPI_CR2_HALFDUPLEX_Pos)
#define    FL_SPI_TRANSFER_MODE_HALF_DUPLEX                       (0x1U << SPI_CR2_HALFDUPLEX_Pos)


#define    FL_SPI_HALF_DUPLEX_TX                                  (0x0U << SPI_CR2_HD_RW_Pos)
#define    FL_SPI_HALF_DUPLEX_RX                                  (0x1U << SPI_CR2_HD_RW_Pos)


#define    FL_SPI_HALF_DUPLEX_CMDLEN_DLEN                         (0x0U << SPI_CR2_CMD8B_Pos)
#define    FL_SPI_HALF_DUPLEX_CMDLEN_8B                           (0x1U << SPI_CR2_CMD8B_Pos)

#define    FL_SPI_HALFDUPLEX_CMDLEN_DLEN                          (0x0U << SPI_CR2_CMD8B_Pos)
#define    FL_SPI_HALFDUPLEX_CMDLEN_8B                            (0x1U << SPI_CR2_CMD8B_Pos)

#define    FL_SPI_HARDWARE_SSN_AUTO_HIGH                          (0x0U << SPI_CR2_SSNM_Pos)
#define    FL_SPI_HARDWARE_SSN_KEEP_LOW                           (0x1U << SPI_CR2_SSNM_Pos)


#define    FL_SPI_SSN_LOW                                         (0x0U << SPI_CR2_SSN_Pos)
#define    FL_SPI_SSN_HIGH                                        (0x1U << SPI_CR2_SSN_Pos)


#define    FL_SPI_FRAME_MODE_CMD                                  (0x0U << SPI_ISR_DCN_TX_Pos)
#define    FL_SPI_FRAME_MODE_DATA                                 (0x1U << SPI_ISR_DCN_TX_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup SPI_FL_Exported_Functions SPI Exported Functions
  * @{
  */

/**
  * @brief    Enable SPI IO Pin Swap
  * @rmtoll   CR1    IOSWAP    FL_SPI_EnablePinSwap
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_EnablePinSwap(SPI_Type *SPIx)
{
    SET_BIT(SPIx->CR1, SPI_CR1_IOSWAP_Msk);
}

/**
  * @brief    Get SPI IO Pin Swap State
  * @rmtoll   CR1    IOSWAP    FL_SPI_IsEnabledPinSwap
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsEnabledPinSwap(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_IOSWAP_Msk) == SPI_CR1_IOSWAP_Msk);
}

/**
  * @brief    Disable SPI IO Pin Swap
  * @rmtoll   CR1    IOSWAP    FL_SPI_DisablePinSwap
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_DisablePinSwap(SPI_Type *SPIx)
{
    CLEAR_BIT(SPIx->CR1, SPI_CR1_IOSWAP_Msk);
}

/**
  * @brief    Set Master Sampling Position Adjustment
  * @rmtoll   CR1    MSPA    FL_SPI_SetMasterSamplingAdjust
  * @param    SPIx SPI instance
  * @param    adjust This parameter can be one of the following values:
  *           @arg @ref FL_SPI_MASTER_SAMPLING_NORMAL
  *           @arg @ref FL_SPI_MASTER_SAMPLING_DELAY_HALFCLK
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetMasterSamplingAdjust(SPI_Type *SPIx, uint32_t adjust)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_MSPA_Msk, adjust);
}

/**
  * @brief    Get Master Sampling Position Adjustment
  * @rmtoll   CR1    MSPA    FL_SPI_GetMasterSamplingAdjust
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_MASTER_SAMPLING_NORMAL
  *           @arg @ref FL_SPI_MASTER_SAMPLING_DELAY_HALFCLK
  */
__STATIC_INLINE uint32_t FL_SPI_GetMasterSamplingAdjust(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_MSPA_Msk));
}

/**
  * @brief    Set Slave Sending Position Adjustment
  * @rmtoll   CR1    SSPA    FL_SPI_SetSlaveSamplingAdjust
  * @param    SPIx SPI instance
  * @param    adjust This parameter can be one of the following values:
  *           @arg @ref FL_SPI_SLAVE_SAMPLING_NORMAL
  *           @arg @ref FL_SPI_SLAVE_SAMPLING_ADVANCE_HALFCLK
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetSlaveSamplingAdjust(SPI_Type *SPIx, uint32_t adjust)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_SSPA_Msk, adjust);
}

/**
  * @brief    Get Slave Sending Position Adjustment
  * @rmtoll   CR1    SSPA    FL_SPI_GetSlaveSamplingAdjust
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_SLAVE_SAMPLING_NORMAL
  *           @arg @ref FL_SPI_SLAVE_SAMPLING_ADVANCE_HALFCLK
  */
__STATIC_INLINE uint32_t FL_SPI_GetSlaveSamplingAdjust(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_SSPA_Msk));
}

/**
  * @brief    Set SPI Working Mode
  * @rmtoll   CR1    MM    FL_SPI_SetWorkMode
  * @param    SPIx SPI instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_SPI_WORK_MODE_SLAVE
  *           @arg @ref FL_SPI_WORK_MODE_MASTER
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetWorkMode(SPI_Type *SPIx, uint32_t mode)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_MM_Msk, mode);
}

/**
  * @brief    Get SPI Working Mode
  * @rmtoll   CR1    MM    FL_SPI_GetWorkMode
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_WORK_MODE_SLAVE
  *           @arg @ref FL_SPI_WORK_MODE_MASTER
  */
__STATIC_INLINE uint32_t FL_SPI_GetWorkMode(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_MM_Msk));
}

/**
  * @brief    Set SPI Send Wait Cycle Length in Master Mode
  * @rmtoll   CR1    WAIT    FL_SPI_SetSendWait
  * @param    SPIx SPI instance
  * @param    wait This parameter can be one of the following values:
  *           @arg @ref FL_SPI_SEND_WAIT_1
  *           @arg @ref FL_SPI_SEND_WAIT_2
  *           @arg @ref FL_SPI_SEND_WAIT_3
  *           @arg @ref FL_SPI_SEND_WAIT_4
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetSendWait(SPI_Type *SPIx, uint32_t wait)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_WAIT_Msk, wait);
}

/**
  * @brief    Get SPI Send Wait Cycle Length in Master Mode
  * @rmtoll   CR1    WAIT    FL_SPI_GetSendWait
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_SPI_GetSendWait(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_WAIT_Msk));
}

/**
  * @brief    Set SPI Baudrate in Master Mode
  * @rmtoll   CR1    BAUD    FL_SPI_SetClockDivision
  * @param    SPIx SPI instance
  * @param    clock This parameter can be one of the following values:
  *           @arg @ref FL_SPI_CLK_DIV2
  *           @arg @ref FL_SPI_CLK_DIV4
  *           @arg @ref FL_SPI_CLK_DIV8
  *           @arg @ref FL_SPI_CLK_DIV16
  *           @arg @ref FL_SPI_CLK_DIV32
  *           @arg @ref FL_SPI_CLK_DIV64
  *           @arg @ref FL_SPI_CLK_DIV128
  *           @arg @ref FL_SPI_CLK_DIV256
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetClockDivision(SPI_Type *SPIx, uint32_t clock)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_BAUD_Msk, clock);
}

/**
  * @brief    Get SPI Baudrate in Master Mode
  * @rmtoll   CR1    BAUD    FL_SPI_GetClockDivision
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_BAUDRATE_DIV2
  *           @arg @ref FL_SPI_BAUDRATE_DIV4
  *           @arg @ref FL_SPI_BAUDRATE_DIV8
  *           @arg @ref FL_SPI_BAUDRATE_DIV16
  *           @arg @ref FL_SPI_BAUDRATE_DIV32
  *           @arg @ref FL_SPI_BAUDRATE_DIV64
  *           @arg @ref FL_SPI_BAUDRATE_DIV128
  *           @arg @ref FL_SPI_BAUDRATE_DIV256
  */
__STATIC_INLINE uint32_t FL_SPI_GetClockDivision(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_BAUD_Msk));
}

/**
  * @brief    Set SPI Bit Order
  * @rmtoll   CR1    LSBF    FL_SPI_SetBitOrder
  * @param    SPIx SPI instance
  * @param    bitOrder This parameter can be one of the following values:
  *           @arg @ref FL_SPI_BIT_ORDER_MSB_FIRST
  *           @arg @ref FL_SPI_BIT_ORDER_LSB_FIRST
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetBitOrder(SPI_Type *SPIx, uint32_t bitOrder)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_LSBF_Msk, bitOrder);
}

/**
  * @brief    Get SPI Bit Order
  * @rmtoll   CR1    LSBF    FL_SPI_GetBitOrder
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_BIT_ORDER_MSB_FIRST
  *           @arg @ref FL_SPI_BIT_ORDER_LSB_FIRST
  */
__STATIC_INLINE uint32_t FL_SPI_GetBitOrder(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_LSBF_Msk));
}

/**
  * @brief    Set SPI Clock Polarity
  * @rmtoll   CR1    CPOL    FL_SPI_SetClockPolarity
  * @param    SPIx SPI instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_SPI_POLARITY_NORMAL
  *           @arg @ref FL_SPI_POLARITY_INVERT
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetClockPolarity(SPI_Type *SPIx, uint32_t polarity)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_CPOL_Msk, polarity);
}

/**
  * @brief    Get SPI Clock Polarity
  * @rmtoll   CR1    CPOL    FL_SPI_GetClockPolarity
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_POLARITY_NORMAL
  *           @arg @ref FL_SPI_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_SPI_GetClockPolarity(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_CPOL_Msk));
}

/**
  * @brief    Set SPI Clock Phase
  * @rmtoll   CR1    CPHA    FL_SPI_SetClockPhase
  * @param    SPIx SPI instance
  * @param    phase This parameter can be one of the following values:
  *           @arg @ref FL_SPI_PHASE_EDGE1
  *           @arg @ref FL_SPI_PHASE_EDGE2
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetClockPhase(SPI_Type *SPIx, uint32_t phase)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_CPHA_Msk, phase);
}

/**
  * @brief    Get SPI Clock Phase
  * @rmtoll   CR1    CPHA    FL_SPI_GetClockPhase
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_PHASE_EDGE1
  *           @arg @ref FL_SPI_PHASE_EDGE2
  */
__STATIC_INLINE uint32_t FL_SPI_GetClockPhase(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_CPHA_Msk));
}

/**
  * @brief    Enable SPI Dummy Cycle Setting Under 4-lines Half Duplex Mode
  * @rmtoll   CR2    DUMMY_EN    FL_SPI_EnableDummyCycle
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_EnableDummyCycle(SPI_Type *SPIx)
{
    SET_BIT(SPIx->CR2, SPI_CR2_DUMMY_EN_Msk);
}

/**
  * @brief    Disable SPI Dummy Cycle Setting Under 4-lines Half Duplex Mode
  * @rmtoll   CR2    DUMMY_EN    FL_SPI_DisableDummyCycle
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_DisableDummyCycle(SPI_Type *SPIx)
{
    CLEAR_BIT(SPIx->CR2, SPI_CR2_DUMMY_EN_Msk);
}

/**
  * @brief    Get SPI Dummy Cycle Mode Setting
  * @rmtoll   CR2    DUMMY_EN    FL_SPI_IsEnabledDummyCycle
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsEnabledDummyCycle(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_DUMMY_EN_Msk) == SPI_CR2_DUMMY_EN_Msk);
}

/**
  * @brief    Enable SPI Receive Only Mode
  * @rmtoll   CR2    RXO    FL_SPI_EnableRXOnlyMode
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_EnableRXOnlyMode(SPI_Type *SPIx)
{
    SET_BIT(SPIx->CR2, SPI_CR2_RXO_Msk);
}

/**
  * @brief    Disable SPI Receive Only Mode Setting
  * @rmtoll   CR2    RXO    FL_SPI_DisableRXOnlyMode
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_DisableRXOnlyMode(SPI_Type *SPIx)
{
    CLEAR_BIT(SPIx->CR2, SPI_CR2_RXO_Msk);
}

/**
  * @brief    Get SPI Receive Only Mode state
  * @rmtoll   CR2    RXO    FL_SPI_IsEnabledRXOnlyMode
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsEnabledRXOnlyMode(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_RXO_Msk) == SPI_CR2_RXO_Msk);
}

/**
  * @brief    Set SPI Data Width
  * @rmtoll   CR2    DLEN    FL_SPI_SetDataWidth
  * @param    SPIx SPI instance
  * @param    width This parameter can be one of the following values:
  *           @arg @ref FL_SPI_DATA_WIDTH_8B
  *           @arg @ref FL_SPI_DATA_WIDTH_16B
  *           @arg @ref FL_SPI_DATA_WIDTH_24B
  *           @arg @ref FL_SPI_DATA_WIDTH_32B
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetDataWidth(SPI_Type *SPIx, uint32_t width)
{
    MODIFY_REG(SPIx->CR2, SPI_CR2_DLEN_Msk, width);
}

/**
  * @brief    Get SPI Data Width
  * @rmtoll   CR2    DLEN    FL_SPI_GetDataWidth
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_DATA_WIDTH_8B
  *           @arg @ref FL_SPI_DATA_WIDTH_16B
  *           @arg @ref FL_SPI_DATA_WIDTH_24B
  *           @arg @ref FL_SPI_DATA_WIDTH_32B
  */
__STATIC_INLINE uint32_t FL_SPI_GetDataWidth(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_DLEN_Msk));
}

/**
  * @brief    Set SPI Transfer Mode
  * @rmtoll   CR2    HALFDUPLEX    FL_SPI_SetTransferMode
  * @param    SPIx SPI instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_SPI_TRANSFER_MODE_FULL_DUPLEX
  *           @arg @ref FL_SPI_TRANSFER_MODE_HALF_DUPLEX
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetTransferMode(SPI_Type *SPIx, uint32_t mode)
{
    MODIFY_REG(SPIx->CR2, SPI_CR2_HALFDUPLEX_Msk, mode);
}

/**
  * @brief    Get SPI Transfer Mode
  * @rmtoll   CR2    HALFDUPLEX    FL_SPI_GetTransferMode
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_TRANSFER_MODE_FULL_DUPLEX
  *           @arg @ref FL_SPI_TRANSFER_MODE_HALF_DUPLEX
  */
__STATIC_INLINE uint32_t FL_SPI_GetTransferMode(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_HALFDUPLEX_Msk));
}

/**
  * @brief    Set SPI Transfer Direction Under Half-Duplex Mode
  * @rmtoll   CR2    HD_RW    FL_SPI_SetTransferDirection
  * @param    SPIx SPI instance
  * @param    direction This parameter can be one of the following values:
  *           @arg @ref FL_SPI_HALF_DUPLEX_TX
  *           @arg @ref FL_SPI_HALF_DUPLEX_RX
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetTransferDirection(SPI_Type *SPIx, uint32_t direction)
{
    MODIFY_REG(SPIx->CR2, SPI_CR2_HD_RW_Msk, direction);
}

/**
  * @brief    Get SPI Transfer Direction Under Half-Duplex Mode
  * @rmtoll   CR2    HD_RW    FL_SPI_GetTransferDirection
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_HALF_DUPLEX_TX
  *           @arg @ref FL_SPI_HALF_DUPLEX_RX
  */
__STATIC_INLINE uint32_t FL_SPI_GetTransferDirection(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_HD_RW_Msk));
}

/**
  * @brief    Set Command Frame Length Under Half-Duplex Mode
  * @rmtoll   CR2    CMD8B    FL_SPI_SetHalfDuplexCommandLength
  * @param    SPIx SPI instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_SPI_HALF_DUPLEX_CMDLEN_DLEN
  *           @arg @ref FL_SPI_HALF_DUPLEX_CMDLEN_8B
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetHalfDuplexCommandLength(SPI_Type *SPIx, uint32_t mode)
{
    MODIFY_REG(SPIx->CR2, SPI_CR2_CMD8B_Msk, mode);
}

/**
  * @brief    Get Command Frame Length Under Half-Duplex Mode
  * @rmtoll   CR2    CMD8B    FL_SPI_GetHalfDuplexCommandLength
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_HALFDUPLEX_CMDLEN_DLEN
  *           @arg @ref FL_SPI_HALFDUPLEX_CMDLEN_8B
  */
__STATIC_INLINE uint32_t FL_SPI_GetHalfDuplexCommandLength(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_CMD8B_Msk));
}

/**
  * @brief    Set SPI SSN Hard Pin Mode
  * @rmtoll   CR2    SSNM    FL_SPI_SetHardwareSSNMode
  * @param    SPIx SPI instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_SPI_HARDWARE_SSN_AUTO_HIGH
  *           @arg @ref FL_SPI_HARDWARE_SSN_KEEP_LOW
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetHardwareSSNMode(SPI_Type *SPIx, uint32_t mode)
{
    MODIFY_REG(SPIx->CR2, SPI_CR2_SSNM_Msk, mode);
}

/**
  * @brief    Get SPI SSN Hard Pin Mode
  * @rmtoll   CR2    SSNM    FL_SPI_GetHardwareSSNMode
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_HARDWARE_SSN_AUTO_HIGH
  *           @arg @ref FL_SPI_HARDWARE_SSN_KEEP_LOW
  */
__STATIC_INLINE uint32_t FL_SPI_GetHardwareSSNMode(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_SSNM_Msk));
}

/**
  * @brief    Enabel TX Only Mode Auto Disable
  * @rmtoll   CR2    TXO_AC    FL_SPI_EnableTXOnlyModeAutoDisable
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_EnableTXOnlyModeAutoDisable(SPI_Type *SPIx)
{
    SET_BIT(SPIx->CR2, SPI_CR2_TXO_AC_Msk);
}

/**
  * @brief    Disable TX Only Mode Auto Disable
  * @rmtoll   CR2    TXO_AC    FL_SPI_DisableTXOnlyModeAutoDisable
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_DisableTXOnlyModeAutoDisable(SPI_Type *SPIx)
{
    CLEAR_BIT(SPIx->CR2, SPI_CR2_TXO_AC_Msk);
}

/**
  * @brief    Get TX Only Mode Auto Disable Setting
  * @rmtoll   CR2    TXO_AC    FL_SPI_IsEnabledTXOnlyModeAutoDisable
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsEnabledTXOnlyModeAutoDisable(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_TXO_AC_Msk) == SPI_CR2_TXO_AC_Msk);
}

/**
  * @brief    EnableSPI TX Only Mode
  * @rmtoll   CR2    TXO    FL_SPI_EnableTXOnlyMode
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_EnableTXOnlyMode(SPI_Type *SPIx)
{
    SET_BIT(SPIx->CR2, SPI_CR2_TXO_Msk);
}

/**
  * @brief    Get SPI TX Only Mode Setting State
  * @rmtoll   CR2    TXO    FL_SPI_IsEnabledTXOnlyMode
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsEnabledTXOnlyMode(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_TXO_Msk) == SPI_CR2_TXO_Msk);
}

/**
  * @brief    Set SSN Pin
  * @rmtoll   CR2    SSN    FL_SPI_SetSSNPin
  * @param    SPIx SPI instance
  * @param    state This parameter can be one of the following values:
  *           @arg @ref FL_SPI_SSN_LOW
  *           @arg @ref FL_SPI_SSN_HIGH
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetSSNPin(SPI_Type *SPIx, uint32_t state)
{
    MODIFY_REG(SPIx->CR2, SPI_CR2_SSN_Msk, state);
}

/**
  * @brief    Reset SSN Pin
  * @rmtoll   CR2    SSN    FL_SPI_GetSSNPin
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_SSN_LOW
  *           @arg @ref FL_SPI_SSN_HIGH
  */
__STATIC_INLINE uint32_t FL_SPI_GetSSNPin(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_SSN_Msk));
}

/**
  * @brief    Enable SNN Sofe Control Under Master Mode
  * @rmtoll   CR2    SSNSEN    FL_SPI_EnableSSNSoftControl
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_EnableSSNSoftControl(SPI_Type *SPIx)
{
    SET_BIT(SPIx->CR2, SPI_CR2_SSNSEN_Msk);
}

/**
  * @brief    Get SNN Sofe Control State Under Master Mode
  * @rmtoll   CR2    SSNSEN    FL_SPI_IsEnabledSSNSoftControl
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsEnabledSSNSoftControl(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_SSNSEN_Msk) == SPI_CR2_SSNSEN_Msk);
}

/**
  * @brief    Disable SNN Sofe Control Under Master Mode
  * @rmtoll   CR2    SSNSEN    FL_SPI_DisableSSNSoftControl
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_DisableSSNSoftControl(SPI_Type *SPIx)
{
    CLEAR_BIT(SPIx->CR2, SPI_CR2_SSNSEN_Msk);
}

/**
  * @brief    Enable SPI
  * @rmtoll   CR2    SPIEN    FL_SPI_Enable
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_Enable(SPI_Type *SPIx)
{
    SET_BIT(SPIx->CR2, SPI_CR2_SPIEN_Msk);
}

/**
  * @brief    Get SPI Enable Status
  * @rmtoll   CR2    SPIEN    FL_SPI_IsEnabled
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsEnabled(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_SPIEN_Msk) == SPI_CR2_SPIEN_Msk);
}

/**
  * @brief    Disable SPI
  * @rmtoll   CR2    SPIEN    FL_SPI_Disable
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_Disable(SPI_Type *SPIx)
{
    CLEAR_BIT(SPIx->CR2, SPI_CR2_SPIEN_Msk);
}

/**
  * @brief    Clear SPI TX Buffer
  * @rmtoll   CR3    TXBFC    FL_SPI_ClearTXBuff
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_ClearTXBuff(SPI_Type *SPIx)
{
    WRITE_REG(SPIx->CR3, SPI_CR3_TXBFC_Msk);
}

/**
  * @brief    Clear SPI RX Buffer
  * @rmtoll   CR3    RXBFC    FL_SPI_ClearRXBuff
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_ClearRXBuff(SPI_Type *SPIx)
{
    WRITE_REG(SPIx->CR3, SPI_CR3_RXBFC_Msk);
}

/**
  * @brief    Clear SPI Master Error Flag
  * @rmtoll   CR3    MERRC    FL_SPI_ClearFlag_MasterError
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_ClearFlag_MasterError(SPI_Type *SPIx)
{
    WRITE_REG(SPIx->CR3, SPI_CR3_MERRC_Msk);
}

/**
  * @brief    Clear SPI Slave Error Flag
  * @rmtoll   CR3    SERRC    FL_SPI_ClearFlag_SlaveError
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_ClearFlag_SlaveError(SPI_Type *SPIx)
{
    WRITE_REG(SPIx->CR3, SPI_CR3_SERRC_Msk);
}

/**
  * @brief    Disable SPI Error Interrupt
  * @rmtoll   IER    ERRIE    FL_SPI_DisableIT_Error
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_DisableIT_Error(SPI_Type *SPIx)
{
    CLEAR_BIT(SPIx->IER, SPI_IER_ERRIE_Msk);
}

/**
  * @brief    Enable SPI Error Interrupt
  * @rmtoll   IER    ERRIE    FL_SPI_EnableIT_Error
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_EnableIT_Error(SPI_Type *SPIx)
{
    SET_BIT(SPIx->IER, SPI_IER_ERRIE_Msk);
}

/**
  * @brief    Get SPI Error Interrupt Enable Status
  * @rmtoll   IER    ERRIE    FL_SPI_IsEnabledIT_Error
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsEnabledIT_Error(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->IER, SPI_IER_ERRIE_Msk) == SPI_IER_ERRIE_Msk);
}

/**
  * @brief    Disable SPI Transmit Complete Interrupt
  * @rmtoll   IER    TXIE    FL_SPI_DisableIT_TXComplete
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_DisableIT_TXComplete(SPI_Type *SPIx)
{
    CLEAR_BIT(SPIx->IER, SPI_IER_TXIE_Msk);
}

/**
  * @brief    Enable SPI Transmit Complete Interrupt
  * @rmtoll   IER    TXIE    FL_SPI_EnableIT_TXComplete
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_EnableIT_TXComplete(SPI_Type *SPIx)
{
    SET_BIT(SPIx->IER, SPI_IER_TXIE_Msk);
}

/**
  * @brief    Get SPI Transmit Complete Interrupt Enable Status
  * @rmtoll   IER    TXIE    FL_SPI_IsEnabledIT_TXComplete
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsEnabledIT_TXComplete(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->IER, SPI_IER_TXIE_Msk) == SPI_IER_TXIE_Msk);
}

/**
  * @brief    Disable SPI Receive Complete Interrupt
  * @rmtoll   IER    RXIE    FL_SPI_DisableIT_RXComplete
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_DisableIT_RXComplete(SPI_Type *SPIx)
{
    CLEAR_BIT(SPIx->IER, SPI_IER_RXIE_Msk);
}

/**
  * @brief    Enable SPI Receive Complete Interrupt
  * @rmtoll   IER    RXIE    FL_SPI_EnableIT_RXComplete
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_EnableIT_RXComplete(SPI_Type *SPIx)
{
    SET_BIT(SPIx->IER, SPI_IER_RXIE_Msk);
}

/**
  * @brief    Get SPI Receive Complete Interrupt Enable Status
  * @rmtoll   IER    RXIE    FL_SPI_IsEnabledIT_RXComplete
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsEnabledIT_RXComplete(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->IER, SPI_IER_RXIE_Msk) == SPI_IER_RXIE_Msk);
}

/**
  * @brief    Set SPI Output Data/Command Under Half-Duplex Mode
  * @rmtoll   ISR    DCN_TX    FL_SPI_SetFrameMode
  * @param    SPIx SPI instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_SPI_FRAME_MODE_CMD
  *           @arg @ref FL_SPI_FRAME_MODE_DATA
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_SetFrameMode(SPI_Type *SPIx, uint32_t mode)
{
    WRITE_REG(SPIx->ISR, mode);
}

/**
  * @brief    Get SPI Output Data/Command Under Half-Duplex Mode Setting
  * @rmtoll   ISR    DCN_TX    FL_SPI_GetFrameMode
  * @param    SPIx SPI instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SPI_FRAME_MODE_CMD
  *           @arg @ref FL_SPI_FRAME_MODE_DATA
  */
__STATIC_INLINE uint32_t FL_SPI_GetFrameMode(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->ISR, SPI_ISR_DCN_TX_Msk));
}

/**
  * @brief    Get SPI Receive Collision Flag
  * @rmtoll   ISR    RXCOL    FL_SPI_IsActiveFlag_RXBuffOverflow
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsActiveFlag_RXBuffOverflow(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->ISR, SPI_ISR_RXCOL_Msk) == (SPI_ISR_RXCOL_Msk));
}

/**
  * @brief    Clear SPI Receive Collision Flag
  * @rmtoll   ISR    RXCOL    FL_SPI_ClearFlag_RXBuffOverflow
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_ClearFlag_RXBuffOverflow(SPI_Type *SPIx)
{
    WRITE_REG(SPIx->ISR, SPI_ISR_RXCOL_Msk);
}

/**
  * @brief    Get SPI Transmit Collision Flag
  * @rmtoll   ISR    TXCOL    FL_SPI_IsActiveFlag_TXBuffOverflow
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsActiveFlag_TXBuffOverflow(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->ISR, SPI_ISR_TXCOL_Msk) == (SPI_ISR_TXCOL_Msk));
}

/**
  * @brief    Clear SPI Transmit Collision Flag
  * @rmtoll   ISR    TXCOL    FL_SPI_ClearFlag_TXBuffOverflow
  * @param    SPIx SPI instance
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_ClearFlag_TXBuffOverflow(SPI_Type *SPIx)
{
    WRITE_REG(SPIx->ISR, SPI_ISR_TXCOL_Msk);
}

/**
  * @brief    Get SPI Busy Flag
  * @rmtoll   ISR    BUSY    FL_SPI_IsActiveFlag_Busy
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsActiveFlag_Busy(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->ISR, SPI_ISR_BUSY_Msk) == (SPI_ISR_BUSY_Msk));
}

/**
  * @brief    Get SPI Master Error Flag
  * @rmtoll   ISR    MERR    FL_SPI_IsActiveFlag_MasterError
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsActiveFlag_MasterError(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->ISR, SPI_ISR_MERR_Msk) == (SPI_ISR_MERR_Msk));
}

/**
  * @brief    Get SPI Slave Error Flag
  * @rmtoll   ISR    SERR    FL_SPI_IsActiveFlag_SlaveError
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsActiveFlag_SlaveError(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->ISR, SPI_ISR_SERR_Msk) == (SPI_ISR_SERR_Msk));
}

/**
  * @brief    Get SPI TX Buffer Empty Flag
  * @rmtoll   ISR    TXBE    FL_SPI_IsActiveFlag_TXBuffEmpty
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsActiveFlag_TXBuffEmpty(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->ISR, SPI_ISR_TXBE_Msk) == (SPI_ISR_TXBE_Msk));
}

/**
  * @brief    Get SPI RX Buffer Full Flag
  * @rmtoll   ISR    RXBF    FL_SPI_IsActiveFlag_RXBuffFull
  * @param    SPIx SPI instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SPI_IsActiveFlag_RXBuffFull(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->ISR, SPI_ISR_RXBF_Msk) == (SPI_ISR_RXBF_Msk));
}

/**
  * @brief    Write SPI TX Buffer
  * @rmtoll   TXBUF        FL_SPI_WriteTXBuff
  * @param    SPIx SPI instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_SPI_WriteTXBuff(SPI_Type *SPIx, uint32_t data)
{
    MODIFY_REG(SPIx->TXBUF, (0xffffffffU << 0U), (data << 0U));
}

/**
  * @brief    Read SPI TX Buffer
  * @rmtoll   RXBUF        FL_SPI_ReadRXBuff
  * @param    SPIx SPI instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_SPI_ReadRXBuff(SPI_Type *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->RXBUF, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @}
  */

/** @defgroup SPI_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

FL_ErrorStatus FL_SPI_DeInit(SPI_Type *SPIx);
FL_ErrorStatus FL_SPI_Init(SPI_Type *SPIx, FL_SPI_InitTypeDef *initStruct);
void FL_SPI_StructInit(FL_SPI_InitTypeDef *initStruct);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FM33LC0XX_FL_SPI_H*/

/*************************Py_Code_Generator Version: 0.1-0.14-0.1 @ 2020-10-20*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
