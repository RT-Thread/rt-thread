/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_lpuart.h
  * @author  FMSH Application Team
  * @brief   Head file of LPUART FL Module
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
#ifndef __FM33LC0XX_FL_LPUART_H
#define __FM33LC0XX_FL_LPUART_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup LPUART LPUART
  * @brief LPUART FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup LPUART_FL_ES_INIT LPUART Exported Init structures
  * @{
  */

/**
  * @brief LPUART Init Sturcture definition
  */
typedef struct
{
    /** 时钟源选择 */
    uint32_t clockSrc;
    /** 通讯波特率*/
    uint32_t baudRate;
    /**  数据位宽*/
    uint32_t dataWidth;
    /** 停止位 */
    uint32_t stopBits;
    /** 奇偶校验 */
    uint32_t parity;
    /** 传输方向 */
    uint32_t transferDirection;

} FL_LPUART_InitTypeDef;

/**
  * @}
  */

/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup LPUART_FL_Exported_Constants LPUART Exported Constants
  * @{
  */

#define    LPUART_CSR_BUSY_Pos                                    (24U)
#define    LPUART_CSR_BUSY_Msk                                    (0x1U << LPUART_CSR_BUSY_Pos)
#define    LPUART_CSR_BUSY                                        LPUART_CSR_BUSY_Msk

#define    LPUART_CSR_WKBYTE_CFG_Pos                              (19U)
#define    LPUART_CSR_WKBYTE_CFG_Msk                              (0x1U << LPUART_CSR_WKBYTE_CFG_Pos)
#define    LPUART_CSR_WKBYTE_CFG                                  LPUART_CSR_WKBYTE_CFG_Msk

#define    LPUART_CSR_RXEV_Pos                                    (16U)
#define    LPUART_CSR_RXEV_Msk                                    (0x3U << LPUART_CSR_RXEV_Pos)
#define    LPUART_CSR_RXEV                                        LPUART_CSR_RXEV_Msk

#define    LPUART_CSR_IOSWAP_Pos                                  (11U)
#define    LPUART_CSR_IOSWAP_Msk                                  (0x1U << LPUART_CSR_IOSWAP_Pos)
#define    LPUART_CSR_IOSWAP                                      LPUART_CSR_IOSWAP_Msk

#define    LPUART_CSR_DMATXIFCFG_Pos                              (10U)
#define    LPUART_CSR_DMATXIFCFG_Msk                              (0x1U << LPUART_CSR_DMATXIFCFG_Pos)
#define    LPUART_CSR_DMATXIFCFG                                  LPUART_CSR_DMATXIFCFG_Msk

#define    LPUART_CSR_BITORD_Pos                                  (9U)
#define    LPUART_CSR_BITORD_Msk                                  (0x1U << LPUART_CSR_BITORD_Pos)
#define    LPUART_CSR_BITORD                                      LPUART_CSR_BITORD_Msk

#define    LPUART_CSR_STOPCFG_Pos                                 (8U)
#define    LPUART_CSR_STOPCFG_Msk                                 (0x1U << LPUART_CSR_STOPCFG_Pos)
#define    LPUART_CSR_STOPCFG                                     LPUART_CSR_STOPCFG_Msk

#define    LPUART_CSR_PDSEL_Pos                                   (6U)
#define    LPUART_CSR_PDSEL_Msk                                   (0x3U << LPUART_CSR_PDSEL_Pos)
#define    LPUART_CSR_PDSEL                                       LPUART_CSR_PDSEL_Msk

#define    LPUART_CSR_PARITY_Pos                                  (4U)
#define    LPUART_CSR_PARITY_Msk                                  (0x3U << LPUART_CSR_PARITY_Pos)
#define    LPUART_CSR_PARITY                                      LPUART_CSR_PARITY_Msk

#define    LPUART_CSR_RXPOL_Pos                                   (3U)
#define    LPUART_CSR_RXPOL_Msk                                   (0x1U << LPUART_CSR_RXPOL_Pos)
#define    LPUART_CSR_RXPOL                                       LPUART_CSR_RXPOL_Msk

#define    LPUART_CSR_TXPOL_Pos                                   (2U)
#define    LPUART_CSR_TXPOL_Msk                                   (0x1U << LPUART_CSR_TXPOL_Pos)
#define    LPUART_CSR_TXPOL                                       LPUART_CSR_TXPOL_Msk

#define    LPUART_CSR_RXEN_Pos                                    (1U)
#define    LPUART_CSR_RXEN_Msk                                    (0x1U << LPUART_CSR_RXEN_Pos)
#define    LPUART_CSR_RXEN                                        LPUART_CSR_RXEN_Msk

#define    LPUART_CSR_TXEN_Pos                                    (0U)
#define    LPUART_CSR_TXEN_Msk                                    (0x1U << LPUART_CSR_TXEN_Pos)
#define    LPUART_CSR_TXEN                                        LPUART_CSR_TXEN_Msk

#define    LPUART_IER_RXEV_IE_Pos                                 (12U)
#define    LPUART_IER_RXEV_IE_Msk                                 (0x1U << LPUART_IER_RXEV_IE_Pos)
#define    LPUART_IER_RXEV_IE                                     LPUART_IER_RXEV_IE_Msk

#define    LPUART_IER_RXERR_IE_Pos                                (10U)
#define    LPUART_IER_RXERR_IE_Msk                                (0x1U << LPUART_IER_RXERR_IE_Pos)
#define    LPUART_IER_RXERR_IE                                    LPUART_IER_RXERR_IE_Msk

#define    LPUART_IER_RXBF_IE_Pos                                 (8U)
#define    LPUART_IER_RXBF_IE_Msk                                 (0x1U << LPUART_IER_RXBF_IE_Pos)
#define    LPUART_IER_RXBF_IE                                     LPUART_IER_RXBF_IE_Msk

#define    LPUART_IER_TXBE_IE_Pos                                 (1U)
#define    LPUART_IER_TXBE_IE_Msk                                 (0x1U << LPUART_IER_TXBE_IE_Pos)
#define    LPUART_IER_TXBE_IE                                     LPUART_IER_TXBE_IE_Msk

#define    LPUART_IER_TXSE_IE_Pos                                 (0U)
#define    LPUART_IER_TXSE_IE_Msk                                 (0x1U << LPUART_IER_TXSE_IE_Pos)
#define    LPUART_IER_TXSE_IE                                     LPUART_IER_TXSE_IE_Msk

#define    LPUART_ISR_RXEVF_Pos                                   (24U)
#define    LPUART_ISR_RXEVF_Msk                                   (0x1U << LPUART_ISR_RXEVF_Pos)
#define    LPUART_ISR_RXEVF                                       LPUART_ISR_RXEVF_Msk

#define    LPUART_ISR_TXOV_Pos                                    (19U)
#define    LPUART_ISR_TXOV_Msk                                    (0x1U << LPUART_ISR_TXOV_Pos)
#define    LPUART_ISR_TXOV                                        LPUART_ISR_TXOV_Msk

#define    LPUART_ISR_PERR_Pos                                    (18U)
#define    LPUART_ISR_PERR_Msk                                    (0x1U << LPUART_ISR_PERR_Pos)
#define    LPUART_ISR_PERR                                        LPUART_ISR_PERR_Msk

#define    LPUART_ISR_FERR_Pos                                    (17U)
#define    LPUART_ISR_FERR_Msk                                    (0x1U << LPUART_ISR_FERR_Pos)
#define    LPUART_ISR_FERR                                        LPUART_ISR_FERR_Msk

#define    LPUART_ISR_OERR_Pos                                    (16U)
#define    LPUART_ISR_OERR_Msk                                    (0x1U << LPUART_ISR_OERR_Pos)
#define    LPUART_ISR_OERR                                        LPUART_ISR_OERR_Msk

#define    LPUART_ISR_RXBF_Pos                                    (8U)
#define    LPUART_ISR_RXBF_Msk                                    (0x1U << LPUART_ISR_RXBF_Pos)
#define    LPUART_ISR_RXBF                                        LPUART_ISR_RXBF_Msk

#define    LPUART_ISR_TXBE_Pos                                    (1U)
#define    LPUART_ISR_TXBE_Msk                                    (0x1U << LPUART_ISR_TXBE_Pos)
#define    LPUART_ISR_TXBE                                        LPUART_ISR_TXBE_Msk

#define    LPUART_ISR_TXSE_Pos                                    (0U)
#define    LPUART_ISR_TXSE_Msk                                    (0x1U << LPUART_ISR_TXSE_Pos)
#define    LPUART_ISR_TXSE                                        LPUART_ISR_TXSE_Msk

#define    LPUART_BMR_BAUD_Pos                                    (0U)
#define    LPUART_BMR_BAUD_Msk                                    (0x7U << LPUART_BMR_BAUD_Pos)
#define    LPUART_BMR_BAUD                                        LPUART_BMR_BAUD_Msk

#define    LPUART_BMR_MCTL_Pos                                    (16U)
#define    LPUART_BMR_MCTL_Msk                                    (0xfffU << LPUART_BMR_MCTL_Pos)
#define    LPUART_BMR_MCTL                                        LPUART_BMR_MCTL_Msk






#define    FL_LPUART_WAKEUP_NO_CHECK                              (0x0U << LPUART_CSR_WKBYTE_CFG_Pos)
#define    FL_LPUART_WAKEUP_CHECK                                 (0x1U << LPUART_CSR_WKBYTE_CFG_Pos)


#define    FL_LPUART_WAKEUP_EVENT_START                           (0x0U << LPUART_CSR_RXEV_Pos)
#define    FL_LPUART_WAKEUP_EVENT_RECV_1BYTE                      (0x1U << LPUART_CSR_RXEV_Pos)
#define    FL_LPUART_WAKEUP_EVENT_RECV_MATCH                      (0x2U << LPUART_CSR_RXEV_Pos)
#define    FL_LPUART_WAKEUP_EVENT_RX_FALLING                      (0x3U << LPUART_CSR_RXEV_Pos)


#define    FL_LPUART_TXIF_MODE_ALWAYS                             (0x0U << LPUART_CSR_DMATXIFCFG_Pos)
#define    FL_LPUART_TXIF_MODE_AFTER_DMA                          (0x1U << LPUART_CSR_DMATXIFCFG_Pos)


#define    FL_LPUART_BIT_ORDER_LSB_FIRST                          (0x0U << LPUART_CSR_BITORD_Pos)
#define    FL_LPUART_BIT_ORDER_MSB_FIRST                          (0x1U << LPUART_CSR_BITORD_Pos)


#define    FL_LPUART_STOP_BIT_WIDTH_1B                            (0x0U << LPUART_CSR_STOPCFG_Pos)
#define    FL_LPUART_STOP_BIT_WIDTH_2B                            (0x1U << LPUART_CSR_STOPCFG_Pos)


#define    FL_LPUART_DATA_WIDTH_7B                                (0x0U << LPUART_CSR_PDSEL_Pos)
#define    FL_LPUART_DATA_WIDTH_8B                                (0x1U << LPUART_CSR_PDSEL_Pos)
#define    FL_LPUART_DATA_WIDTH_9B                                (0x2U << LPUART_CSR_PDSEL_Pos)
#define    FL_LPUART_DATA_WIDTH_6B                                (0x3U << LPUART_CSR_PDSEL_Pos)


#define    FL_LPUART_PARITY_NONE                                  (0x0U << LPUART_CSR_PARITY_Pos)
#define    FL_LPUART_PARITY_EVEN                                  (0x1U << LPUART_CSR_PARITY_Pos)
#define    FL_LPUART_PARITY_ODD                                   (0x2U << LPUART_CSR_PARITY_Pos)


#define    FL_LPUART_RX_POLARITY_NORMAL                           (0x0U << LPUART_CSR_RXPOL_Pos)
#define    FL_LPUART_RX_POLARITY_INVERT                           (0x1U << LPUART_CSR_RXPOL_Pos)


#define    FL_LPUART_TX_POLARITY_NORMAL                           (0x0U << LPUART_CSR_TXPOL_Pos)
#define    FL_LPUART_TX_POLARITY_INVERT                           (0x1U << LPUART_CSR_TXPOL_Pos)


#define    FL_LPUART_BAUDRATE_9600                                (0x0U << LPUART_BMR_BAUD_Pos)
#define    FL_LPUART_BAUDRATE_4800                                (0x1U << LPUART_BMR_BAUD_Pos)
#define    FL_LPUART_BAUDRATE_2400                                (0x2U << LPUART_BMR_BAUD_Pos)
#define    FL_LPUART_BAUDRATE_1200                                (0x3U << LPUART_BMR_BAUD_Pos)
#define    FL_LPUART_BAUDRATE_600                                 (0x4U << LPUART_BMR_BAUD_Pos)
#define    FL_LPUART_BAUDRATE_300                                 (0x5U << LPUART_BMR_BAUD_Pos)


#define    FL_LPUART_DIRECTION_NONE                               0x00000000U
#define    FL_LPUART_DIRECTION_RX                                 LPUART_CSR_RXEN
#define    FL_LPUART_DIRECTION_TX                                 LPUART_CSR_TXEN
#define    FL_LPUART_DIRECTION_TX_RX                              (LPUART_CSR_RXEN|LPUART_CSR_TXEN)
/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup LPUART_FL_Exported_Functions LPUART Exported Functions
  * @{
  */

/**
  * @brief    Get LPUART Busy Flag
  * @rmtoll   CSR    BUSY    FL_LPUART_IsActiveFlag_Busy
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsActiveFlag_Busy(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_BUSY_Msk) == (LPUART_CSR_BUSY_Msk));
}

/**
  * @brief    Set Data Receive Wakeup Mode
  * @rmtoll   CSR    WKBYTE_CFG    FL_LPUART_SetRXWakeupMode
  * @param    LPUARTx LPUART instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_LPUART_WAKEUP_NO_CHECK
  *           @arg @ref FL_LPUART_WAKEUP_CHECK
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_SetRXWakeupMode(LPUART_Type *LPUARTx, uint32_t mode)
{
    MODIFY_REG(LPUARTx->CSR, LPUART_CSR_WKBYTE_CFG_Msk, mode);
}

/**
  * @brief    Get Data Receive Wakeup Mode Setting
  * @rmtoll   CSR    WKBYTE_CFG    FL_LPUART_GetRXWakeupMode
  * @param    LPUARTx LPUART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPUART_WAKEUP_NO_CHECK
  *           @arg @ref FL_LPUART_WAKEUP_CHECK
  */
__STATIC_INLINE uint32_t FL_LPUART_GetRXWakeupMode(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_WKBYTE_CFG_Msk));
}

/**
  * @brief    Set Receive Wakeup Event
  * @rmtoll   CSR    RXEV    FL_LPUART_SetWakeup
  * @param    LPUARTx LPUART instance
  * @param    event This parameter can be one of the following values:
  *           @arg @ref FL_LPUART_WAKEUP_EVENT_START
  *           @arg @ref FL_LPUART_WAKEUP_EVENT_RECV_1BYTE
  *           @arg @ref FL_LPUART_WAKEUP_EVENT_RECV_MATCH
  *           @arg @ref FL_LPUART_WAKEUP_EVENT_RX_FALLING
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_SetWakeup(LPUART_Type *LPUARTx, uint32_t event)
{
    MODIFY_REG(LPUARTx->CSR, LPUART_CSR_RXEV_Msk, event);
}

/**
  * @brief    Get Receive Wakeup Event Setting
  * @rmtoll   CSR    RXEV    FL_LPUART_GetWakeup
  * @param    LPUARTx LPUART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPUART_WAKEUP_EVENT_START
  *           @arg @ref FL_LPUART_WAKEUP_EVENT_RECV_1BYTE
  *           @arg @ref FL_LPUART_WAKEUP_EVENT_RECV_MATCH
  *           @arg @ref FL_LPUART_WAKEUP_EVENT_RX_FALLING
  */
__STATIC_INLINE uint32_t FL_LPUART_GetWakeup(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_RXEV_Msk));
}

/**
  * @brief    Enable LPUART Pin Swap Between TX Pin and RX Pin
  * @rmtoll   CSR    IOSWAP    FL_LPUART_EnablePinSwap
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_EnablePinSwap(LPUART_Type *LPUARTx)
{
    SET_BIT(LPUARTx->CSR, LPUART_CSR_IOSWAP_Msk);
}

/**
  * @brief    Disable LPUART Pin Swap Between TX Pin and RX Pin
  * @rmtoll   CSR    IOSWAP    FL_LPUART_DisablePinSwap
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_DisablePinSwap(LPUART_Type *LPUARTx)
{
    CLEAR_BIT(LPUARTx->CSR, LPUART_CSR_IOSWAP_Msk);
}

/**
  * @brief    Get UART Pin Swap Enable Status Between UART TX Pin and RX Pin

  * @rmtoll   CSR    IOSWAP    FL_LPUART_IsEnabledPinSwap
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsEnabledPinSwap(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_IOSWAP_Msk) == LPUART_CSR_IOSWAP_Msk);
}

/**
  * @brief    Enable DMA TX Complete Interrupt
  * @rmtoll   CSR    DMATXIFCFG    FL_LPUART_SetTXIFMode
  * @param    LPUARTx LPUART instance
  * @param    txifMode This parameter can be one of the following values:
  *           @arg @ref FL_LPUART_TXIF_MODE_ALWAYS
  *           @arg @ref FL_LPUART_TXIF_MODE_AFTER_DMA
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_SetTXIFMode(LPUART_Type *LPUARTx, uint32_t txifMode)
{
    MODIFY_REG(LPUARTx->CSR, LPUART_CSR_DMATXIFCFG_Msk, txifMode);
}

/**
  * @brief    Disable DMA TX Complete Interrupt
  * @rmtoll   CSR    DMATXIFCFG    FL_LPUART_GetTXIFMode
  * @param    LPUARTx LPUART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPUART_TXIF_MODE_ALWAYS
  *           @arg @ref FL_LPUART_TXIF_MODE_AFTER_DMA
  */
__STATIC_INLINE uint32_t FL_LPUART_GetTXIFMode(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_DMATXIFCFG_Msk));
}

/**
  * @brief    Set LPUART Transfer Bit Order
  * @rmtoll   CSR    BITORD    FL_LPUART_SetBitOrder
  * @param    LPUARTx LPUART instance
  * @param    bitOrder This parameter can be one of the following values:
  *           @arg @ref FL_LPUART_BIT_ORDER_LSB_FIRST
  *           @arg @ref FL_LPUART_BIT_ORDER_MSB_FIRST
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_SetBitOrder(LPUART_Type *LPUARTx, uint32_t bitOrder)
{
    MODIFY_REG(LPUARTx->CSR, LPUART_CSR_BITORD_Msk, bitOrder);
}

/**
  * @brief    Get LPUART Transfer Bit Order Setting
  * @rmtoll   CSR    BITORD    FL_LPUART_GetBitOrder
  * @param    LPUARTx LPUART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPUART_BIT_ORDER_LSB_FIRST
  *           @arg @ref FL_LPUART_BIT_ORDER_MSB_FIRST
  */
__STATIC_INLINE uint32_t FL_LPUART_GetBitOrder(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_BITORD_Msk));
}

/**
  * @brief    Set LPUART Stop Bits Length
  * @rmtoll   CSR    STOPCFG    FL_LPUART_SetStopBitsWidth
  * @param    LPUARTx LPUART instance
  * @param    stopBits This parameter can be one of the following values:
  *           @arg @ref FL_LPUART_STOP_BIT_WIDTH_1B
  *           @arg @ref FL_LPUART_STOP_BIT_WIDTH_2B
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_SetStopBitsWidth(LPUART_Type *LPUARTx, uint32_t stopBits)
{
    MODIFY_REG(LPUARTx->CSR, LPUART_CSR_STOPCFG_Msk, stopBits);
}

/**
  * @brief    Get LPUART Stop Bits Length Setting
  * @rmtoll   CSR    STOPCFG    FL_LPUART_GetStopBitsWidth
  * @param    LPUARTx LPUART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPUART_STOP_BIT_WIDTH_1B
  *           @arg @ref FL_LPUART_STOP_BIT_WIDTH_2B
  */
__STATIC_INLINE uint32_t FL_LPUART_GetStopBitsWidth(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_STOPCFG_Msk));
}

/**
  * @brief    Set LPUART Data Width
  * @rmtoll   CSR    PDSEL    FL_LPUART_SetDataWidth
  * @param    LPUARTx LPUART instance
  * @param    dataWidth This parameter can be one of the following values:
  *           @arg @ref FL_LPUART_DATA_WIDTH_7B
  *           @arg @ref FL_LPUART_DATA_WIDTH_8B
  *           @arg @ref FL_LPUART_DATA_WIDTH_9B
  *           @arg @ref FL_LPUART_DATA_WIDTH_6B
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_SetDataWidth(LPUART_Type *LPUARTx, uint32_t dataWidth)
{
    MODIFY_REG(LPUARTx->CSR, LPUART_CSR_PDSEL_Msk, dataWidth);
}

/**
  * @brief    Get LPUART Stop Bits Length Setting
  * @rmtoll   CSR    PDSEL    FL_LPUART_GetDataWidth
  * @param    LPUARTx LPUART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPUART_DATA_WIDTH_7B
  *           @arg @ref FL_LPUART_DATA_WIDTH_8B
  *           @arg @ref FL_LPUART_DATA_WIDTH_9B
  *           @arg @ref FL_LPUART_DATA_WIDTH_6B
  */
__STATIC_INLINE uint32_t FL_LPUART_GetDataWidth(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_PDSEL_Msk));
}

/**
  * @brief    Set LPUART Parity
  * @rmtoll   CSR    PARITY    FL_LPUART_SetParity
  * @param    LPUARTx LPUART instance
  * @param    parity This parameter can be one of the following values:
  *           @arg @ref FL_LPUART_PARITY_NONE
  *           @arg @ref FL_LPUART_PARITY_EVEN
  *           @arg @ref FL_LPUART_PARITY_ODD
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_SetParity(LPUART_Type *LPUARTx, uint32_t parity)
{
    MODIFY_REG(LPUARTx->CSR, LPUART_CSR_PARITY_Msk, parity);
}

/**
  * @brief    Get LPUART Parity Setting
  * @rmtoll   CSR    PARITY    FL_LPUART_GetParity
  * @param    LPUARTx LPUART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPUART_PARITY_NONE
  *           @arg @ref FL_LPUART_PARITY_EVEN
  *           @arg @ref FL_LPUART_PARITY_ODD
  */
__STATIC_INLINE uint32_t FL_LPUART_GetParity(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_PARITY_Msk));
}

/**
  * @brief    Set LPUART Receive Polarity
  * @rmtoll   CSR    RXPOL    FL_LPUART_SetRXPolarity
  * @param    LPUARTx LPUART instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_LPUART_RX_POLARITY_NORMAL
  *           @arg @ref FL_LPUART_RX_POLARITY_INVERT
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_SetRXPolarity(LPUART_Type *LPUARTx, uint32_t polarity)
{
    MODIFY_REG(LPUARTx->CSR, LPUART_CSR_RXPOL_Msk, polarity);
}

/**
  * @brief    Get LPUART Receive Polarity Setting
  * @rmtoll   CSR    RXPOL    FL_LPUART_GetRXPolarity
  * @param    LPUARTx LPUART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPUART_RX_POLARITY_NORMAL
  *           @arg @ref FL_LPUART_RX_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_LPUART_GetRXPolarity(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_RXPOL_Msk));
}

/**
  * @brief    Set LPUART Transmit Polarity
  * @rmtoll   CSR    TXPOL    FL_LPUART_SetTXPolarity
  * @param    LPUARTx LPUART instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_LPUART_TX_POLARITY_NORMAL
  *           @arg @ref FL_LPUART_TX_POLARITY_INVERT
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_SetTXPolarity(LPUART_Type *LPUARTx, uint32_t polarity)
{
    MODIFY_REG(LPUARTx->CSR, LPUART_CSR_TXPOL_Msk, polarity);
}

/**
  * @brief    Get LPUART Transmit Polarity Setting
  * @rmtoll   CSR    TXPOL    FL_LPUART_GetTXPolarity
  * @param    LPUARTx LPUART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPUART_TX_POLARITY_NORMAL
  *           @arg @ref FL_LPUART_TX_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_LPUART_GetTXPolarity(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_TXPOL_Msk));
}

/**
  * @brief    Enable LPUART Receive
  * @rmtoll   CSR    RXEN    FL_LPUART_EnableRX
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_EnableRX(LPUART_Type *LPUARTx)
{
    SET_BIT(LPUARTx->CSR, LPUART_CSR_RXEN_Msk);
}

/**
  * @brief    Get LPUART Receive Enable Status
  * @rmtoll   CSR    RXEN    FL_LPUART_IsEnabledRX
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsEnabledRX(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_RXEN_Msk) == LPUART_CSR_RXEN_Msk);
}

/**
  * @brief    Disable LPUART Receive
  * @rmtoll   CSR    RXEN    FL_LPUART_DisableRX
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_DisableRX(LPUART_Type *LPUARTx)
{
    CLEAR_BIT(LPUARTx->CSR, LPUART_CSR_RXEN_Msk);
}

/**
  * @brief    Enable LPUART Receive
  * @rmtoll   CSR    TXEN    FL_LPUART_EnableTX
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_EnableTX(LPUART_Type *LPUARTx)
{
    SET_BIT(LPUARTx->CSR, LPUART_CSR_TXEN_Msk);
}

/**
  * @brief    Get LPUART Receive Enable Status
  * @rmtoll   CSR    TXEN    FL_LPUART_IsEnabledTX
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsEnabledTX(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->CSR, LPUART_CSR_TXEN_Msk) == LPUART_CSR_TXEN_Msk);
}

/**
  * @brief    Disable LPUART Receive
  * @rmtoll   CSR    TXEN    FL_LPUART_DisableTX
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_DisableTX(LPUART_Type *LPUARTx)
{
    CLEAR_BIT(LPUARTx->CSR, LPUART_CSR_TXEN_Msk);
}

/**
  * @brief    Enable LPUART Receive Event Interrupt
  * @rmtoll   IER    RXEV_IE    FL_LPUART_EnableIT_RXWakeup
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_EnableIT_RXWakeup(LPUART_Type *LPUARTx)
{
    SET_BIT(LPUARTx->IER, LPUART_IER_RXEV_IE_Msk);
}

/**
  * @brief    Get LPUART Receive Event Interrupt Enable Status
  * @rmtoll   IER    RXEV_IE    FL_LPUART_IsEnabledIT_RXWakeup
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsEnabledIT_RXWakeup(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->IER, LPUART_IER_RXEV_IE_Msk) == LPUART_IER_RXEV_IE_Msk);
}

/**
  * @brief    Disable LPUART Receive Event Interrupt
  * @rmtoll   IER    RXEV_IE    FL_LPUART_DisableIT_RXWakeup
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_DisableIT_RXWakeup(LPUART_Type *LPUARTx)
{
    CLEAR_BIT(LPUARTx->IER, LPUART_IER_RXEV_IE_Msk);
}

/**
  * @brief    Enable LPUART Receive Error Interrupt
  * @rmtoll   IER    RXERR_IE    FL_LPUART_EnableIT_RXError
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_EnableIT_RXError(LPUART_Type *LPUARTx)
{
    SET_BIT(LPUARTx->IER, LPUART_IER_RXERR_IE_Msk);
}

/**
  * @brief    Get LPUART Receive Error Interrupt Enable Status
  * @rmtoll   IER    RXERR_IE    FL_LPUART_IsEnabledIT_RXError
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsEnabledIT_RXError(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->IER, LPUART_IER_RXERR_IE_Msk) == LPUART_IER_RXERR_IE_Msk);
}

/**
  * @brief    Disable LPUART Receive Error Interrupt
  * @rmtoll   IER    RXERR_IE    FL_LPUART_DisableIT_RXError
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_DisableIT_RXError(LPUART_Type *LPUARTx)
{
    CLEAR_BIT(LPUARTx->IER, LPUART_IER_RXERR_IE_Msk);
}

/**
  * @brief    Enable LPUART Receive Buffer Full Interrupt
  * @rmtoll   IER    RXBF_IE    FL_LPUART_EnableIT_RXBuffFull
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_EnableIT_RXBuffFull(LPUART_Type *LPUARTx)
{
    SET_BIT(LPUARTx->IER, LPUART_IER_RXBF_IE_Msk);
}

/**
  * @brief    Get LPUART Receive Buffer Full Interrupt Enable Status
  * @rmtoll   IER    RXBF_IE    FL_LPUART_IsEnabledIT_RXBuffFull
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsEnabledIT_RXBuffFull(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->IER, LPUART_IER_RXBF_IE_Msk) == LPUART_IER_RXBF_IE_Msk);
}

/**
  * @brief    Disable LPUART Receive Buffer Full Interrupt
  * @rmtoll   IER    RXBF_IE    FL_LPUART_DisableIT_RXBufFull
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_DisableIT_RXBufFull(LPUART_Type *LPUARTx)
{
    CLEAR_BIT(LPUARTx->IER, LPUART_IER_RXBF_IE_Msk);
}

/**
  * @brief    Enable LPUART Transmit Buffer Empty Interrupt
  * @rmtoll   IER    TXBE_IE    FL_LPUART_EnableIT_TXBuffEmpty
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_EnableIT_TXBuffEmpty(LPUART_Type *LPUARTx)
{
    SET_BIT(LPUARTx->IER, LPUART_IER_TXBE_IE_Msk);
}

/**
  * @brief    Get LPUART Transmit Buffer Empty Interrupt Enable Status
  * @rmtoll   IER    TXBE_IE    FL_LPUART_IsEnabledIT_TXBuffEmpty
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsEnabledIT_TXBuffEmpty(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->IER, LPUART_IER_TXBE_IE_Msk) == LPUART_IER_TXBE_IE_Msk);
}

/**
  * @brief    Disable LPUART Transmit Buffer Empty Interrupt
  * @rmtoll   IER    TXBE_IE    FL_LPUART_DisableIT_TXBuffEmpty
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_DisableIT_TXBuffEmpty(LPUART_Type *LPUARTx)
{
    CLEAR_BIT(LPUARTx->IER, LPUART_IER_TXBE_IE_Msk);
}

/**
  * @brief    Enable LPUART Transmit Shift Register Interrupt
  * @rmtoll   IER    TXSE_IE    FL_LPUART_EnableIT_TXShiftBuffEmpty
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_EnableIT_TXShiftBuffEmpty(LPUART_Type *LPUARTx)
{
    SET_BIT(LPUARTx->IER, LPUART_IER_TXSE_IE_Msk);
}

/**
  * @brief    Get LPUART Transmit Shift Register Interrupt Enable Status
  * @rmtoll   IER    TXSE_IE    FL_LPUART_IsEnabledIT_TXShiftBuffEmpty
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsEnabledIT_TXShiftBuffEmpty(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->IER, LPUART_IER_TXSE_IE_Msk) == LPUART_IER_TXSE_IE_Msk);
}

/**
  * @brief    Disable LPUART Transmit Shift Register Interrupt
  * @rmtoll   IER    TXSE_IE    FL_LPUART_DisableIT_TXShiftBuffEmpty
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_DisableIT_TXShiftBuffEmpty(LPUART_Type *LPUARTx)
{
    CLEAR_BIT(LPUARTx->IER, LPUART_IER_TXSE_IE_Msk);
}

/**
  * @brief    Get LPUART Receive Event Interrupt Flag
  * @rmtoll   ISR    RXEVF    FL_LPUART_IsActiveFlag_RXWakeup
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsActiveFlag_RXWakeup(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->ISR, LPUART_ISR_RXEVF_Msk) == (LPUART_ISR_RXEVF_Msk));
}

/**
  * @brief    Clear LPUART Receive Event Interrupt Flag
  * @rmtoll   ISR    RXEVF    FL_LPUART_ClearFlag_RXWakeup
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_ClearFlag_RXWakeup(LPUART_Type *LPUARTx)
{
    WRITE_REG(LPUARTx->ISR, LPUART_ISR_RXEVF_Msk);
}

/**
  * @brief    Get LPUART Transmit Overflow Error Flag
  * @rmtoll   ISR    TXOV    FL_LPUART_IsActiveFlag_TXBuffOverflow
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsActiveFlag_TXBuffOverflow(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->ISR, LPUART_ISR_TXOV_Msk) == (LPUART_ISR_TXOV_Msk));
}

/**
  * @brief    Clear LPUART Transmit Overflow Error Flag
  * @rmtoll   ISR    TXOV    FL_LPUART_ClearFlag_TXBuffOverflow
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_ClearFlag_TXBuffOverflow(LPUART_Type *LPUARTx)
{
    WRITE_REG(LPUARTx->ISR, LPUART_ISR_TXOV_Msk);
}

/**
  * @brief    Get LPUART Parity Error Flag
  * @rmtoll   ISR    PERR    FL_LPUART_IsActiveFlag_ParityError
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsActiveFlag_ParityError(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->ISR, LPUART_ISR_PERR_Msk) == (LPUART_ISR_PERR_Msk));
}

/**
  * @brief    Clear LPUART Parity Error Flag
  * @rmtoll   ISR    PERR    FL_LPUART_ClearFlag_ParityError
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_ClearFlag_ParityError(LPUART_Type *LPUARTx)
{
    WRITE_REG(LPUARTx->ISR, LPUART_ISR_PERR_Msk);
}

/**
  * @brief    Get LPUART Frame Error Flag
  * @rmtoll   ISR    FERR    FL_LPUART_IsActiveFlag_FrameError
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsActiveFlag_FrameError(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->ISR, LPUART_ISR_FERR_Msk) == (LPUART_ISR_FERR_Msk));
}

/**
  * @brief    Clear LPUART Frame Error Flag
  * @rmtoll   ISR    FERR    FL_LPUART_ClearFlag_FrameError
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_ClearFlag_FrameError(LPUART_Type *LPUARTx)
{
    WRITE_REG(LPUARTx->ISR, LPUART_ISR_FERR_Msk);
}

/**
  * @brief    Get LPUART Receive Buffer Overflow Error Flag
  * @rmtoll   ISR    OERR    FL_LPUART_IsActiveFlag_RXBuffOverflow
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsActiveFlag_RXBuffOverflow(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->ISR, LPUART_ISR_OERR_Msk) == (LPUART_ISR_OERR_Msk));
}

/**
  * @brief    Clear LPUART Receive Buffer Overflow Error Flag
  * @rmtoll   ISR    OERR    FL_LPUART_ClearFlag_RXBuffOverflow
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_ClearFlag_RXBuffOverflow(LPUART_Type *LPUARTx)
{
    WRITE_REG(LPUARTx->ISR, LPUART_ISR_OERR_Msk);
}

/**
  * @brief    Get LPUART Receive Buffer Full Flag
  * @rmtoll   ISR    RXBF    FL_LPUART_IsActiveFlag_RXBuffFull
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsActiveFlag_RXBuffFull(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->ISR, LPUART_ISR_RXBF_Msk) == (LPUART_ISR_RXBF_Msk));
}

/**
  * @brief    Clear LPUART Receive Buffer Full Flag
  * @rmtoll   ISR    RXBF    FL_LPUART_ClearFlag_RXBuffFull
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_ClearFlag_RXBuffFull(LPUART_Type *LPUARTx)
{
    WRITE_REG(LPUARTx->ISR, LPUART_ISR_RXBF_Msk);
}

/**
  * @brief    Get LPUART Transmit Buffer Empty Flag
  * @rmtoll   ISR    TXBE    FL_LPUART_IsActiveFlag_TXBuffEmpty
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsActiveFlag_TXBuffEmpty(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->ISR, LPUART_ISR_TXBE_Msk) == (LPUART_ISR_TXBE_Msk));
}

/**
  * @brief    Clear LPUART Transmit Buffer Empty Flag
  * @rmtoll   ISR    TXBE    FL_LPUART_ClearFlag_TXBuffEmpty
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_ClearFlag_TXBuffEmpty(LPUART_Type *LPUARTx)
{
    WRITE_REG(LPUARTx->ISR, LPUART_ISR_TXBE_Msk);
}

/**
  * @brief    Get LPUART Transmit Shift register Empty Flag
  * @rmtoll   ISR    TXSE    FL_LPUART_IsActiveFlag_TXShiftBuffEmpty
  * @param    LPUARTx LPUART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPUART_IsActiveFlag_TXShiftBuffEmpty(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->ISR, LPUART_ISR_TXSE_Msk) == (LPUART_ISR_TXSE_Msk));
}

/**
  * @brief    Clear LPUART Transmit Shift register Empty Flag
  * @rmtoll   ISR    TXSE    FL_LPUART_ClearFlag_TXShiftBuffEmpty
  * @param    LPUARTx LPUART instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_ClearFlag_TXShiftBuffEmpty(LPUART_Type *LPUARTx)
{
    WRITE_REG(LPUARTx->ISR, LPUART_ISR_TXSE_Msk);
}

/**
  * @brief    Set LPUART BaudRate
  * @rmtoll   BMR    BAUD    FL_LPUART_SetBaudRate
  * @param    LPUARTx LPUART instance
  * @param    baudRate This parameter can be one of the following values:
  *           @arg @ref FL_LPUART_BAUDRATE_9600
  *           @arg @ref FL_LPUART_BAUDRATE_4800
  *           @arg @ref FL_LPUART_BAUDRATE_2400
  *           @arg @ref FL_LPUART_BAUDRATE_1200
  *           @arg @ref FL_LPUART_BAUDRATE_600
  *           @arg @ref FL_LPUART_BAUDRATE_300
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_SetBaudRate(LPUART_Type *LPUARTx, uint32_t baudRate)
{
    MODIFY_REG(LPUARTx->BMR, LPUART_BMR_BAUD_Msk, baudRate);
}

/**
  * @brief    Get LPUART BaudRate
  * @rmtoll   BMR    BAUD    FL_LPUART_GetBaudRate
  * @param    LPUARTx LPUART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPUART_BAUDRATE_9600
  *           @arg @ref FL_LPUART_BAUDRATE_4800
  *           @arg @ref FL_LPUART_BAUDRATE_2400
  *           @arg @ref FL_LPUART_BAUDRATE_1200
  *           @arg @ref FL_LPUART_BAUDRATE_600
  *           @arg @ref FL_LPUART_BAUDRATE_300
  */
__STATIC_INLINE uint32_t FL_LPUART_GetBaudRate(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->BMR, LPUART_BMR_BAUD_Msk));
}

/**
  * @brief    LPUART Receive 1 byte of data
  * @rmtoll   RXBUF        FL_LPUART_ReadRXBuff
  * @param    LPUARTx LPUART instance
  * @retval   The LPUart received data
  */
__STATIC_INLINE uint32_t FL_LPUART_ReadRXBuff(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->RXBUF, 0x1ffU));
}

/**
  * @brief    LPUART Transmit 1 byte of data
  * @rmtoll   TXBUF        FL_LPUART_WriteTXBuff
  * @param    LPUARTx LPUART instance
  * @param    data The data need to transmit through the LPUart
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_WriteTXBuff(LPUART_Type *LPUARTx, uint8_t data)
{
    MODIFY_REG(LPUARTx->TXBUF, 0x1ffU, data);
}

/**
  * @brief    Set LPUART Matched Data
  * @rmtoll   DMR        FL_LPUART_WriteMatchData
  * @param    LPUARTx LPUART instance
  * @param    data The value of match under SLEEP MODE
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_WriteMatchData(LPUART_Type *LPUARTx, uint8_t data)
{
    MODIFY_REG(LPUARTx->DMR, 0x1ffU, data);
}

/**
  * @brief    Get LPUART Matched Data
  * @rmtoll   DMR        FL_LPUART_ReadMatchData
  * @param    LPUARTx LPUART instance
  * @retval   The value of match data under SLEEP MODE
  */
__STATIC_INLINE uint32_t FL_LPUART_ReadMatchData(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->DMR, 0x1ffU));
}

/**
  * @brief    Set LPUART Bit Modulation
  * @rmtoll   BMR    MCTL    FL_LPUART_WriteBitModulation
  * @param    LPUARTx LPUART instance
  * @param    bitModulation The value of Bit Modulation Control
  * @retval   None
  */
__STATIC_INLINE void FL_LPUART_WriteBitModulation(LPUART_Type *LPUARTx, uint32_t bitModulation)
{
    MODIFY_REG(LPUARTx->BMR, (0xfffU << 16U), (bitModulation << 16U));
}

/**
  * @brief    Get LPUART Bit Modulation
  * @rmtoll   BMR    MCTL    FL_LPUART_ReadBitModulation
  * @param    LPUARTx LPUART instance
  * @retval   The value of Bit Modulation Control
  */
__STATIC_INLINE uint32_t FL_LPUART_ReadBitModulation(LPUART_Type *LPUARTx)
{
    return (uint32_t)(READ_BIT(LPUARTx->BMR, (0xfffU << 16U)) >> 16U);
}

/**
  * @}
  */

/** @defgroup LPUART_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_LPUART_DeInit(LPUART_Type *LPUARTx);
void FL_LPUART_StructInit(FL_LPUART_InitTypeDef *initStruct);
FL_ErrorStatus FL_LPUART_Init(LPUART_Type *LPUARTx, FL_LPUART_InitTypeDef *initStruct);

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

#endif /* __FM33LC0XX_FL_LPUART_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-22*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
