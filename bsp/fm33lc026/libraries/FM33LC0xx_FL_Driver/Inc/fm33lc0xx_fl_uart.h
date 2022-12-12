/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_uart.h
  * @author  FMSH Application Team
  * @brief   Head file of UART FL Module
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
#ifndef __FM33LC0XX_FL_UART_H
#define __FM33LC0XX_FL_UART_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup UART UART
  * @brief UART FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup UART_FL_ES_INIT UART Exported Init structures
  * @{
  */

/**
  * @brief FL UART Init Sturcture definition
  */
typedef struct
{
    /** 时钟源选择 */
    uint32_t clockSrc;

    /** 通信波特率 */
    uint32_t baudRate;

    /** 数据宽度 */
    uint32_t dataWidth;

    /** 停止位 */
    uint32_t stopBits;

    /** 奇偶校验位 */
    uint32_t parity;

    /** 传输反向 */
    uint32_t transferDirection;

} FL_UART_InitTypeDef;

/**
  * @brief FL UART InfraRed Init Sturcture definition
  */
typedef struct
{
    /** 调制极性默认bit1调制 */
    uint32_t polarity;
    /** 红外调制占空比 */
    uint32_t modulationDuty;
    /** 红外调制频率*/
    uint32_t modulationFrequency;

} FL_UART_InfraRed_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup UART_FL_Exported_Constants UART Exported Constants
  * @{
  */

#define    UART_IRCR_IRFLAG_Pos                                   (15U)
#define    UART_IRCR_IRFLAG_Msk                                   (0x1U << UART_IRCR_IRFLAG_Pos)
#define    UART_IRCR_IRFLAG                                       UART_IRCR_IRFLAG_Msk

#define    UART_IRCR_TH_Pos                                       (11U)
#define    UART_IRCR_TH_Msk                                       (0xfU << UART_IRCR_TH_Pos)
#define    UART_IRCR_TH                                           UART_IRCR_TH_Msk

#define    UART_IRCR_TZBRG_Pos                                    (0U)
#define    UART_IRCR_TZBRG_Msk                                    (0x7ffU << UART_IRCR_TZBRG_Pos)
#define    UART_IRCR_TZBRG                                        UART_IRCR_TZBRG_Msk

#define    UART_CSR_BUSY_Pos                                      (21U)
#define    UART_CSR_BUSY_Msk                                      (0x1U << UART_CSR_BUSY_Pos)
#define    UART_CSR_BUSY                                          UART_CSR_BUSY_Msk

#define    UART_CSR_TXIREN_Pos                                    (17U)
#define    UART_CSR_TXIREN_Msk                                    (0x1U << UART_CSR_TXIREN_Pos)
#define    UART_CSR_TXIREN                                        UART_CSR_TXIREN_Msk

#define    UART_CSR_RXTOEN_Pos                                    (16U)
#define    UART_CSR_RXTOEN_Msk                                    (0x1U << UART_CSR_RXTOEN_Pos)
#define    UART_CSR_RXTOEN                                        UART_CSR_RXTOEN_Msk

#define    UART_CSR_IOSWAP_Pos                                    (12U)
#define    UART_CSR_IOSWAP_Msk                                    (0x1U << UART_CSR_IOSWAP_Pos)
#define    UART_CSR_IOSWAP                                        UART_CSR_IOSWAP_Msk

#define    UART_CSR_NEWUP_Pos                                     (11U)
#define    UART_CSR_NEWUP_Msk                                     (0x1U << UART_CSR_NEWUP_Pos)
#define    UART_CSR_NEWUP                                         UART_CSR_NEWUP_Msk

#define    UART_CSR_DMATXIFCFG_Pos                                (10U)
#define    UART_CSR_DMATXIFCFG_Msk                                (0x1U << UART_CSR_DMATXIFCFG_Pos)
#define    UART_CSR_DMATXIFCFG                                    UART_CSR_DMATXIFCFG_Msk

#define    UART_CSR_BITORD_Pos                                    (9U)
#define    UART_CSR_BITORD_Msk                                    (0x1U << UART_CSR_BITORD_Pos)
#define    UART_CSR_BITORD                                        UART_CSR_BITORD_Msk

#define    UART_CSR_STOPCFG_Pos                                   (8U)
#define    UART_CSR_STOPCFG_Msk                                   (0x1U << UART_CSR_STOPCFG_Pos)
#define    UART_CSR_STOPCFG                                       UART_CSR_STOPCFG_Msk

#define    UART_CSR_PDSEL_Pos                                     (6U)
#define    UART_CSR_PDSEL_Msk                                     (0x3U << UART_CSR_PDSEL_Pos)
#define    UART_CSR_PDSEL                                         UART_CSR_PDSEL_Msk

#define    UART_CSR_PARITY_Pos                                    (4U)
#define    UART_CSR_PARITY_Msk                                    (0x3U << UART_CSR_PARITY_Pos)
#define    UART_CSR_PARITY                                        UART_CSR_PARITY_Msk

#define    UART_CSR_RXPOL_Pos                                     (3U)
#define    UART_CSR_RXPOL_Msk                                     (0x1U << UART_CSR_RXPOL_Pos)
#define    UART_CSR_RXPOL                                         UART_CSR_RXPOL_Msk

#define    UART_CSR_TXPOL_Pos                                     (2U)
#define    UART_CSR_TXPOL_Msk                                     (0x1U << UART_CSR_TXPOL_Pos)
#define    UART_CSR_TXPOL                                         UART_CSR_TXPOL_Msk

#define    UART_CSR_RXEN_Pos                                      (1U)
#define    UART_CSR_RXEN_Msk                                      (0x1U << UART_CSR_RXEN_Pos)
#define    UART_CSR_RXEN                                          UART_CSR_RXEN_Msk

#define    UART_CSR_TXEN_Pos                                      (0U)
#define    UART_CSR_TXEN_Msk                                      (0x1U << UART_CSR_TXEN_Pos)
#define    UART_CSR_TXEN                                          UART_CSR_TXEN_Msk

#define    UART_IER_RXTOIE_Pos                                    (11U)
#define    UART_IER_RXTOIE_Msk                                    (0x1U << UART_IER_RXTOIE_Pos)
#define    UART_IER_RXTOIE                                        UART_IER_RXTOIE_Msk

#define    UART_IER_RXERRIE_Pos                                   (10U)
#define    UART_IER_RXERRIE_Msk                                   (0x1U << UART_IER_RXERRIE_Pos)
#define    UART_IER_RXERRIE                                       UART_IER_RXERRIE_Msk

#define    UART_IER_RXBFIE_Pos                                    (8U)
#define    UART_IER_RXBFIE_Msk                                    (0x1U << UART_IER_RXBFIE_Pos)
#define    UART_IER_RXBFIE                                        UART_IER_RXBFIE_Msk

#define    UART_IER_NEWUPIE_Pos                                   (7U)
#define    UART_IER_NEWUPIE_Msk                                   (0x1U << UART_IER_NEWUPIE_Pos)
#define    UART_IER_NEWUPIE                                       UART_IER_NEWUPIE_Msk

#define    UART_IER_TXBEIE_Pos                                    (1U)
#define    UART_IER_TXBEIE_Msk                                    (0x1U << UART_IER_TXBEIE_Pos)
#define    UART_IER_TXBEIE                                        UART_IER_TXBEIE_Msk

#define    UART_IER_TXSEIE_Pos                                    (0U)
#define    UART_IER_TXSEIE_Msk                                    (0x1U << UART_IER_TXSEIE_Pos)
#define    UART_IER_TXSEIE                                        UART_IER_TXSEIE_Msk

#define    UART_ISR_PERR_Pos                                      (18U)
#define    UART_ISR_PERR_Msk                                      (0x1U << UART_ISR_PERR_Pos)
#define    UART_ISR_PERR                                          UART_ISR_PERR_Msk

#define    UART_ISR_FERR_Pos                                      (17U)
#define    UART_ISR_FERR_Msk                                      (0x1U << UART_ISR_FERR_Pos)
#define    UART_ISR_FERR                                          UART_ISR_FERR_Msk

#define    UART_ISR_OERR_Pos                                      (16U)
#define    UART_ISR_OERR_Msk                                      (0x1U << UART_ISR_OERR_Pos)
#define    UART_ISR_OERR                                          UART_ISR_OERR_Msk

#define    UART_ISR_RXTO_Pos                                      (11U)
#define    UART_ISR_RXTO_Msk                                      (0x1U << UART_ISR_RXTO_Pos)
#define    UART_ISR_RXTO                                          UART_ISR_RXTO_Msk

#define    UART_ISR_RXBF_Pos                                      (8U)
#define    UART_ISR_RXBF_Msk                                      (0x1U << UART_ISR_RXBF_Pos)
#define    UART_ISR_RXBF                                          UART_ISR_RXBF_Msk

#define    UART_ISR_NEWKF_Pos                                     (7U)
#define    UART_ISR_NEWKF_Msk                                     (0x1U << UART_ISR_NEWKF_Pos)
#define    UART_ISR_NEWKF                                         UART_ISR_NEWKF_Msk

#define    UART_ISR_TXBE_Pos                                      (1U)
#define    UART_ISR_TXBE_Msk                                      (0x1U << UART_ISR_TXBE_Pos)
#define    UART_ISR_TXBE                                          UART_ISR_TXBE_Msk

#define    UART_ISR_TXSE_Pos                                      (0U)
#define    UART_ISR_TXSE_Msk                                      (0x1U << UART_ISR_TXSE_Pos)
#define    UART_ISR_TXSE                                          UART_ISR_TXSE_Msk

#define    UART_TODR_TXDLY_LEN_Pos                                (8U)
#define    UART_TODR_TXDLY_LEN_Msk                                (0xffU << UART_TODR_TXDLY_LEN_Pos)
#define    UART_TODR_TXDLY_LEN                                    UART_TODR_TXDLY_LEN_Msk

#define    UART_TODR_RXTO_LEN_Pos                                 (0U)
#define    UART_TODR_RXTO_LEN_Msk                                 (0xffU << UART_TODR_RXTO_LEN_Pos)
#define    UART_TODR_RXTO_LEN                                     UART_TODR_RXTO_LEN_Msk



#define    FL_UART_INFRARED_POLARITY_NORMAL                       (0x0U << UART_IRCR_IRFLAG_Pos)
#define    FL_UART_INFRARED_POLARITY_INVERT                       (0x1U << UART_IRCR_IRFLAG_Pos)


#define    FL_UART_TXIF_MODE_ALWAYS                               (0x0U << UART_CSR_DMATXIFCFG_Pos)
#define    FL_UART_TXIF_MODE_AFTER_DMA                            (0x1U << UART_CSR_DMATXIFCFG_Pos)


#define    FL_UART_BIT_ORDER_LSB_FIRST                            (0x0U << UART_CSR_BITORD_Pos)
#define    FL_UART_BIT_ORDER_MSB_FIRST                            (0x1U << UART_CSR_BITORD_Pos)


#define    FL_UART_STOP_BIT_WIDTH_1B                              (0x0U << UART_CSR_STOPCFG_Pos)
#define    FL_UART_STOP_BIT_WIDTH_2B                              (0x1U << UART_CSR_STOPCFG_Pos)


#define    FL_UART_DATA_WIDTH_7B                                  (0x0U << UART_CSR_PDSEL_Pos)
#define    FL_UART_DATA_WIDTH_8B                                  (0x1U << UART_CSR_PDSEL_Pos)
#define    FL_UART_DATA_WIDTH_9B                                  (0x2U << UART_CSR_PDSEL_Pos)
#define    FL_UART_DATA_WIDTH_6B                                  (0x3U << UART_CSR_PDSEL_Pos)


#define    FL_UART_PARITY_NONE                                    (0x0U << UART_CSR_PARITY_Pos)
#define    FL_UART_PARITY_EVEN                                    (0x1U << UART_CSR_PARITY_Pos)
#define    FL_UART_PARITY_ODD                                     (0x2U << UART_CSR_PARITY_Pos)


#define    FL_UART_RX_POLARITY_NORMAL                             (0x0U << UART_CSR_RXPOL_Pos)
#define    FL_UART_RX_POLARITY_INVERT                             (0x1U << UART_CSR_RXPOL_Pos)


#define    FL_UART_TX_POLARITY_NORMAL                             (0x0U << UART_CSR_TXPOL_Pos)
#define    FL_UART_TX_POLARITY_INVERT                             (0x1U << UART_CSR_TXPOL_Pos)


#define    FL_UART_DIRECTION_NONE                                 0x00000000U
#define    FL_UART_DIRECTION_RX                                   UART_CSR_RXEN
#define    FL_UART_DIRECTION_TX                                   UART_CSR_TXEN
#define    FL_UART_DIRECTION_TX_RX                               (UART_CSR_RXEN | UART_CSR_TXEN)

/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup UART_FL_Exported_Functions UART Exported Functions
  * @{
  */

/**
  * @brief    Set Infrared Polarity
  * @rmtoll   IRCR    IRFLAG    FL_UART_SetIRPolarity
  * @param    UARTx UART instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_UART_INFRARED_POLARITY_NORMAL
  *           @arg @ref FL_UART_INFRARED_POLARITY_INVERT
  * @retval   None
  */
__STATIC_INLINE void FL_UART_SetIRPolarity(UART_COMMON_Type *UARTx, uint32_t polarity)
{
    MODIFY_REG(UARTx->IRCR, UART_IRCR_IRFLAG_Msk, polarity);
}

/**
  * @brief    Get Infrared Polarity
  * @rmtoll   IRCR    IRFLAG    FL_UART_GetIRPolarity
  * @param    UARTx UART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_UART_INFRARED_POLARITY_NORMAL
  *           @arg @ref FL_UART_INFRARED_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_UART_GetIRPolarity(UART_COMMON_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->IRCR, UART_IRCR_IRFLAG_Msk));
}

/**
  * @brief    Set Infrared Modulation Duty
  * @rmtoll   IRCR    TH    FL_UART_WriteIRModulationDuty
  * @param    UARTx UART instance
  * @param    duty
  * @retval   None
  */
__STATIC_INLINE void FL_UART_WriteIRModulationDuty(UART_COMMON_Type *UARTx, uint32_t duty)
{
    MODIFY_REG(UARTx->IRCR, (0xfU << 11U), (duty << 11U));
}

/**
  * @brief    Get Infrared Modulation Duty
  * @rmtoll   IRCR    TH    FL_UART_ReadIRModulationDuty
  * @param    UARTx UART instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_UART_ReadIRModulationDuty(UART_COMMON_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->IRCR, (0xfU << 11U)) >> 11U);
}

/**
  * @brief    Set Infrared Modulation Frequency
  * @rmtoll   IRCR    TZBRG    FL_UART_WriteIRModulationFrequency
  * @param    UARTx UART instance
  * @param    freq
  * @retval   None
  */
__STATIC_INLINE void FL_UART_WriteIRModulationFrequency(UART_COMMON_Type *UARTx, uint32_t freq)
{
    MODIFY_REG(UARTx->IRCR, (0x7ffU << 0U), (freq << 0U));
}

/**
  * @brief    Get Infrared Modulation Frequency
  * @rmtoll   IRCR    TZBRG    FL_UART_ReadIRModulationFrequency
  * @param    UARTx UART instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_UART_ReadIRModulationFrequency(UART_COMMON_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->IRCR, (0x7ffU << 0U)) >> 0U);
}

/**
  * @brief    Get UART Busy Flag
  * @rmtoll   CSR    BUSY    FL_UART_IsActiveFlag_Busy
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsActiveFlag_Busy(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_BUSY_Msk) == (UART_CSR_BUSY_Msk));
}

/**
  * @brief    Enable UART Infrared Modulation
  * @rmtoll   CSR    TXIREN    FL_UART_EnableIRModulation
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_EnableIRModulation(UART_Type *UARTx)
{
    SET_BIT(UARTx->CSR, UART_CSR_TXIREN_Msk);
}

/**
  * @brief    Disable UART Infrared Modulation
  * @rmtoll   CSR    TXIREN    FL_UART_DisableIRModulation
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_DisableIRModulation(UART_Type *UARTx)
{
    CLEAR_BIT(UARTx->CSR, UART_CSR_TXIREN_Msk);
}

/**
  * @brief    Get UART Infrared Modulation Enable Status
  * @rmtoll   CSR    TXIREN    FL_UART_IsEnabledIRModulation
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsEnabledIRModulation(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_TXIREN_Msk) == UART_CSR_TXIREN_Msk);
}

/**
  * @brief    Enable UART Receive Time-Out Function
  * @rmtoll   CSR    RXTOEN    FL_UART_EnableRXTimeout
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_EnableRXTimeout(UART_Type *UARTx)
{
    SET_BIT(UARTx->CSR, UART_CSR_RXTOEN_Msk);
}

/**
  * @brief    Disable UART Receive Time-Out Function
  * @rmtoll   CSR    RXTOEN    FL_UART_DisableRXTimeout
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_DisableRXTimeout(UART_Type *UARTx)
{
    CLEAR_BIT(UARTx->CSR, UART_CSR_RXTOEN_Msk);
}

/**
  * @brief    Get UART Receive Time-Out Function Enable Status
  * @rmtoll   CSR    RXTOEN    FL_UART_IsEnabledRXTimeout
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsEnabledRXTimeout(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_RXTOEN_Msk) == UART_CSR_RXTOEN_Msk);
}

/**
  * @brief    Enable UART Pin Swap Between UART TX Pin and RX Pin
  * @rmtoll   CSR    IOSWAP    FL_UART_EnablePinSwap
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_EnablePinSwap(UART_Type *UARTx)
{
    SET_BIT(UARTx->CSR, UART_CSR_IOSWAP_Msk);
}

/**
  * @brief    Disable UART Pin Swap Between UART TX Pin and RX Pin
  * @rmtoll   CSR    IOSWAP    FL_UART_DisablePinSwap
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_DisablePinSwap(UART_Type *UARTx)
{
    CLEAR_BIT(UARTx->CSR, UART_CSR_IOSWAP_Msk);
}

/**
  * @brief    Get UART Pin Swap Enable Status Between UART TX Pin and RX Pin
  * @rmtoll   CSR    IOSWAP    FL_UART_IsEnabledPinSwap
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsEnabledPinSwap(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_IOSWAP_Msk) == UART_CSR_IOSWAP_Msk);
}

/**
  * @brief    Enable UART Negtive Edge Wakeup Function
  * @note     Only UART0 and UART1 Available
  * @rmtoll   CSR    NEWUP    FL_UART_EnableFallingEdgeWakeup
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_EnableFallingEdgeWakeup(UART_Type *UARTx)
{
    SET_BIT(UARTx->CSR, UART_CSR_NEWUP_Msk);
}

/**
  * @brief    Disable UART Negtive Edge Wakeup Function
  * @rmtoll   CSR    NEWUP    FL_UART_DisableFallingEdgeWakeup
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_DisableFallingEdgeWakeup(UART_Type *UARTx)
{
    CLEAR_BIT(UARTx->CSR, UART_CSR_NEWUP_Msk);
}

/**
  * @brief    Get UART Negtive Edge Wakeup Function Enable Status
  * @rmtoll   CSR    NEWUP    FL_UART_IsEnabledFallingEdgeWakeup
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsEnabledFallingEdgeWakeup(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_NEWUP_Msk) == UART_CSR_NEWUP_Msk);
}

/**
  * @brief    Set UART DMA Transmit Finish Interrupt
  * @note     Only DMA Mode Available
  * @rmtoll   CSR    DMATXIFCFG    FL_UART_SetTXIFMode
  * @param    UARTx UART instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_UART_TXIF_MODE_ALWAYS
  *           @arg @ref FL_UART_TXIF_MODE_AFTER_DMA
  * @retval   None
  */
__STATIC_INLINE void FL_UART_SetTXIFMode(UART_Type *UARTx, uint32_t mode)
{
    MODIFY_REG(UARTx->CSR, UART_CSR_DMATXIFCFG_Msk, mode);
}

/**
  * @brief    Get UART DMA Transmit Finish Interrupt
  * @rmtoll   CSR    DMATXIFCFG    FL_UART_GetTXIFMode
  * @param    UARTx UART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_UART_TXIF_MODE_ALWAYS
  *           @arg @ref FL_UART_TXIF_MODE_AFTER_DMA
  */
__STATIC_INLINE uint32_t FL_UART_GetTXIFMode(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_DMATXIFCFG_Msk));
}

/**
  * @brief    Set UART Transfer Bit Order
  * @rmtoll   CSR    BITORD    FL_UART_SetBitOrder
  * @param    UARTx UART instance
  * @param    order This parameter can be one of the following values:
  *           @arg @ref FL_UART_BIT_ORDER_LSB_FIRST
  *           @arg @ref FL_UART_BIT_ORDER_MSB_FIRST
  * @retval   None
  */
__STATIC_INLINE void FL_UART_SetBitOrder(UART_Type *UARTx, uint32_t order)
{
    MODIFY_REG(UARTx->CSR, UART_CSR_BITORD_Msk, order);
}

/**
  * @brief    Get UART Transfer Bit Order
  * @rmtoll   CSR    BITORD    FL_UART_GetBitOrder
  * @param    UARTx UART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_UART_BIT_ORDER_LSB_FIRST
  *           @arg @ref FL_UART_BIT_ORDER_MSB_FIRST
  */
__STATIC_INLINE uint32_t FL_UART_GetBitOrder(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_BITORD_Msk));
}

/**
  * @brief    Set UART Stop Bits Length
  * @rmtoll   CSR    STOPCFG    FL_UART_SetStopBitsWidth
  * @param    UARTx UART instance
  * @param    length This parameter can be one of the following values:
  *           @arg @ref FL_UART_STOP_BIT_WIDTH_1B
  *           @arg @ref FL_UART_STOP_BIT_WIDTH_2B
  * @retval   None
  */
__STATIC_INLINE void FL_UART_SetStopBitsWidth(UART_Type *UARTx, uint32_t length)
{
    MODIFY_REG(UARTx->CSR, UART_CSR_STOPCFG_Msk, length);
}

/**
  * @brief    Get UART Stop Bits Length
  * @rmtoll   CSR    STOPCFG    FL_UART_GetStopBitsWidth
  * @param    UARTx UART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_UART_STOP_BIT_WIDTH_1B
  *           @arg @ref FL_UART_STOP_BIT_WIDTH_2B
  */
__STATIC_INLINE uint32_t FL_UART_GetStopBitsWidth(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_STOPCFG_Msk));
}

/**
  * @brief    Set UART Data Width
  * @rmtoll   CSR    PDSEL    FL_UART_SetDataWidth
  * @param    UARTx UART instance
  * @param    dataWidth This parameter can be one of the following values:
  *           @arg @ref FL_UART_DATA_WIDTH_7B
  *           @arg @ref FL_UART_DATA_WIDTH_8B
  *           @arg @ref FL_UART_DATA_WIDTH_9B
  *           @arg @ref FL_UART_DATA_WIDTH_6B
  * @retval   None
  */
__STATIC_INLINE void FL_UART_SetDataWidth(UART_Type *UARTx, uint32_t dataWidth)
{
    MODIFY_REG(UARTx->CSR, UART_CSR_PDSEL_Msk, dataWidth);
}

/**
  * @brief    Get UART Data Width
  * @rmtoll   CSR    PDSEL    FL_UART_GetDataWidth
  * @param    UARTx UART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_UART_DATA_WIDTH_7B
  *           @arg @ref FL_UART_DATA_WIDTH_8B
  *           @arg @ref FL_UART_DATA_WIDTH_9B
  *           @arg @ref FL_UART_DATA_WIDTH_6B
  */
__STATIC_INLINE uint32_t FL_UART_GetDataWidth(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_PDSEL_Msk));
}

/**
  * @brief    Set UART Parity
  * @rmtoll   CSR    PARITY    FL_UART_SetParity
  * @param    UARTx UART instance
  * @param    parity This parameter can be one of the following values:
  *           @arg @ref FL_UART_PARITY_NONE
  *           @arg @ref FL_UART_PARITY_EVEN
  *           @arg @ref FL_UART_PARITY_ODD
  * @retval   None
  */
__STATIC_INLINE void FL_UART_SetParity(UART_Type *UARTx, uint32_t parity)
{
    MODIFY_REG(UARTx->CSR, UART_CSR_PARITY_Msk, parity);
}

/**
  * @brief    Get UART Parity
  * @rmtoll   CSR    PARITY    FL_UART_GetParity
  * @param    UARTx UART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_UART_PARITY_NONE
  *           @arg @ref FL_UART_PARITY_EVEN
  *           @arg @ref FL_UART_PARITY_ODD
  */
__STATIC_INLINE uint32_t FL_UART_GetParity(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_PARITY_Msk));
}

/**
  * @brief    Set UART Receive Polarity
  * @rmtoll   CSR    RXPOL    FL_UART_SetRXPolarity
  * @param    UARTx UART instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_UART_RX_POLARITY_NORMAL
  *           @arg @ref FL_UART_RX_POLARITY_INVERT
  * @retval   None
  */
__STATIC_INLINE void FL_UART_SetRXPolarity(UART_Type *UARTx, uint32_t polarity)
{
    MODIFY_REG(UARTx->CSR, UART_CSR_RXPOL_Msk, polarity);
}

/**
  * @brief    Get UART Receive Polarity
  * @rmtoll   CSR    RXPOL    FL_UART_GetRXPolarity
  * @param    UARTx UART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_UART_RX_POLARITY_NORMAL
  *           @arg @ref FL_UART_RX_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_UART_GetRXPolarity(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_RXPOL_Msk));
}

/**
  * @brief    Set UART Transmit Polarity
  * @rmtoll   CSR    TXPOL    FL_UART_SetTXPolarity
  * @param    UARTx UART instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_UART_TX_POLARITY_NORMAL
  *           @arg @ref FL_UART_TX_POLARITY_INVERT
  * @retval   None
  */
__STATIC_INLINE void FL_UART_SetTXPolarity(UART_Type *UARTx, uint32_t polarity)
{
    MODIFY_REG(UARTx->CSR, UART_CSR_TXPOL_Msk, polarity);
}

/**
  * @brief    Get UART Transmit Polarity
  * @rmtoll   CSR    TXPOL    FL_UART_GetTXPolarity
  * @param    UARTx UART instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_UART_TX_POLARITY_NORMAL
  *           @arg @ref FL_UART_TX_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_UART_GetTXPolarity(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_TXPOL_Msk));
}

/**
  * @brief    Enable UART Receive
  * @rmtoll   CSR    RXEN    FL_UART_EnableRX
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_EnableRX(UART_Type *UARTx)
{
    SET_BIT(UARTx->CSR, UART_CSR_RXEN_Msk);
}

/**
  * @brief    Disable UART Receive
  * @rmtoll   CSR    RXEN    FL_UART_DisableRX
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_DisableRX(UART_Type *UARTx)
{
    CLEAR_BIT(UARTx->CSR, UART_CSR_RXEN_Msk);
}

/**
  * @brief    Get UART Receive Enable Status
  * @rmtoll   CSR    RXEN    FL_UART_IsEnabledRX
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsEnabledRX(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_RXEN_Msk) == UART_CSR_RXEN_Msk);
}

/**
  * @brief    Enable UART Transmit
  * @rmtoll   CSR    TXEN    FL_UART_EnableTX
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_EnableTX(UART_Type *UARTx)
{
    SET_BIT(UARTx->CSR, UART_CSR_TXEN_Msk);
}

/**
  * @brief    Disable UART Receive
  * @rmtoll   CSR    TXEN    FL_UART_DisableTX
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_DisableTX(UART_Type *UARTx)
{
    CLEAR_BIT(UARTx->CSR, UART_CSR_TXEN_Msk);
}

/**
  * @brief    Get UART Receive Enable Status
  * @rmtoll   CSR    TXEN    FL_UART_IsEnabledTX
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsEnabledTX(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CSR, UART_CSR_TXEN_Msk) == UART_CSR_TXEN_Msk);
}

/**
  * @brief    Enable UART Receive Time-Out Interrupt
  * @rmtoll   IER    RXTOIE    FL_UART_EnableIT_RXTimeout
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_EnableIT_RXTimeout(UART_Type *UARTx)
{
    SET_BIT(UARTx->IER, UART_IER_RXTOIE_Msk);
}

/**
  * @brief    Disable UART Receive Time-Out Interrupt
  * @rmtoll   IER    RXTOIE    FL_UART_DisableIT_RXTimeout
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_DisableIT_RXTimeout(UART_Type *UARTx)
{
    CLEAR_BIT(UARTx->IER, UART_IER_RXTOIE_Msk);
}

/**
  * @brief    Get UART Receive Time-Out Interrupt Enable Status
  * @rmtoll   IER    RXTOIE    FL_UART_IsEnabledIT_RXTimeout
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsEnabledIT_RXTimeout(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->IER, UART_IER_RXTOIE_Msk) == UART_IER_RXTOIE_Msk);
}

/**
  * @brief    Enable UART Receive Error Interrupt
  * @rmtoll   IER    RXERRIE    FL_UART_EnableIT_RXError
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_EnableIT_RXError(UART_Type *UARTx)
{
    SET_BIT(UARTx->IER, UART_IER_RXERRIE_Msk);
}

/**
  * @brief    Disable UART Receive Error Interrupt
  * @rmtoll   IER    RXERRIE    FL_UART_DisableIT_RXError
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_DisableIT_RXError(UART_Type *UARTx)
{
    CLEAR_BIT(UARTx->IER, UART_IER_RXERRIE_Msk);
}

/**
  * @brief    Get UART Receive Error Interrupt Enable Status
  * @rmtoll   IER    RXERRIE    FL_UART_IsEnabledIT_RXError
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsEnabledIT_RXError(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->IER, UART_IER_RXERRIE_Msk) == UART_IER_RXERRIE_Msk);
}

/**
  * @brief    Enable UART Receive Buffer Full Interrupt
  * @rmtoll   IER    RXBFIE    FL_UART_EnableIT_RXBuffFull
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_EnableIT_RXBuffFull(UART_Type *UARTx)
{
    SET_BIT(UARTx->IER, UART_IER_RXBFIE_Msk);
}

/**
  * @brief    Disable UART Receive Buffer Full Interrupt
  * @rmtoll   IER    RXBFIE    FL_UART_DisableIT_RXBuffFull
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_DisableIT_RXBuffFull(UART_Type *UARTx)
{
    CLEAR_BIT(UARTx->IER, UART_IER_RXBFIE_Msk);
}

/**
  * @brief    Get UART Receive Buffer Full Interrupt Enable Status
  * @rmtoll   IER    RXBFIE    FL_UART_IsEnabledIT_RXBuffFull
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsEnabledIT_RXBuffFull(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->IER, UART_IER_RXBFIE_Msk) == UART_IER_RXBFIE_Msk);
}

/**
  * @brief    Enable UART Negedge Wakeup Interrupt
  * @rmtoll   IER    NEWUPIE    FL_UART_EnableIT_FallingEdgeWakeup
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_EnableIT_FallingEdgeWakeup(UART_Type *UARTx)
{
    SET_BIT(UARTx->IER, UART_IER_NEWUPIE_Msk);
}

/**
  * @brief    Disable UART Negedge Wakeup Interrupt
  * @rmtoll   IER    NEWUPIE    FL_UART_DisableIT_FallingEdgeWakeup
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_DisableIT_FallingEdgeWakeup(UART_Type *UARTx)
{
    CLEAR_BIT(UARTx->IER, UART_IER_NEWUPIE_Msk);
}

/**
  * @brief    Get UART Negedge Wakeup Interrupt Enable Status
  * @rmtoll   IER    NEWUPIE    FL_UART_IsEnabledIT_FallingEdgeWakeup
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsEnabledIT_FallingEdgeWakeup(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->IER, UART_IER_NEWUPIE_Msk) == UART_IER_NEWUPIE_Msk);
}

/**
  * @brief    Enable UART Transmit Buffer Empty Interrupt
  * @rmtoll   IER    TXBEIE    FL_UART_EnableIT_TXBuffEmpty
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_EnableIT_TXBuffEmpty(UART_Type *UARTx)
{
    SET_BIT(UARTx->IER, UART_IER_TXBEIE_Msk);
}

/**
  * @brief    Disable UART Transmit Buffer Empty Interrupt
  * @rmtoll   IER    TXBEIE    FL_UART_DisableIT_TXBuffEmpty
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_DisableIT_TXBuffEmpty(UART_Type *UARTx)
{
    CLEAR_BIT(UARTx->IER, UART_IER_TXBEIE_Msk);
}

/**
  * @brief    Get UART Transmit Buffer Empty Interrupt Enable Status
  * @rmtoll   IER    TXBEIE    FL_UART_IsEnabledIT_TXBuffEmpty
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsEnabledIT_TXBuffEmpty(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->IER, UART_IER_TXBEIE_Msk) == UART_IER_TXBEIE_Msk);
}

/**
  * @brief    Enable UART Transmit Shift Register Empty Interrupt
  * @rmtoll   IER    TXSEIE    FL_UART_EnableIT_TXShiftBuffEmpty
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_EnableIT_TXShiftBuffEmpty(UART_Type *UARTx)
{
    SET_BIT(UARTx->IER, UART_IER_TXSEIE_Msk);
}

/**
  * @brief    Disable UART Transmit Shift Register Empty Interrupt
  * @rmtoll   IER    TXSEIE    FL_UART_DisableIT_TXShiftBuffEmpty
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_DisableIT_TXShiftBuffEmpty(UART_Type *UARTx)
{
    CLEAR_BIT(UARTx->IER, UART_IER_TXSEIE_Msk);
}

/**
  * @brief    Get UART Transmit Shift Register Empty Interrupt Enable Status
  * @rmtoll   IER    TXSEIE    FL_UART_IsEnabledIT_TXShiftBuffEmpty
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsEnabledIT_TXShiftBuffEmpty(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->IER, UART_IER_TXSEIE_Msk) == UART_IER_TXSEIE_Msk);
}

/**
  * @brief    Get UART Parity Error Flag
  * @rmtoll   ISR    PERR    FL_UART_IsActiveFlag_ParityError
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsActiveFlag_ParityError(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->ISR, UART_ISR_PERR_Msk) == (UART_ISR_PERR_Msk));
}

/**
  * @brief    Clear UART Parity Error Flag
  * @rmtoll   ISR    PERR    FL_UART_ClearFlag_ParityError
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_ClearFlag_ParityError(UART_Type *UARTx)
{
    WRITE_REG(UARTx->ISR, UART_ISR_PERR_Msk);
}

/**
  * @brief    Get UART Frame Error Flag
  * @rmtoll   ISR    FERR    FL_UART_IsActiveFlag_FrameError
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsActiveFlag_FrameError(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->ISR, UART_ISR_FERR_Msk) == (UART_ISR_FERR_Msk));
}

/**
  * @brief    Clear UART Frame Error Flag
  * @rmtoll   ISR    FERR    FL_UART_ClearFlag_FrameError
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_ClearFlag_FrameError(UART_Type *UARTx)
{
    WRITE_REG(UARTx->ISR, UART_ISR_FERR_Msk);
}

/**
  * @brief    Get UART RX buffer Overflow Error Flag
  * @rmtoll   ISR    OERR    FL_UART_IsActiveFlag_RXBuffOverflowError
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsActiveFlag_RXBuffOverflowError(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->ISR, UART_ISR_OERR_Msk) == (UART_ISR_OERR_Msk));
}

/**
  * @brief    Clear UART RX buffer Overflow Error Flag
  * @rmtoll   ISR    OERR    FL_UART_ClearFlag_RXBuffOverflowError
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_ClearFlag_RXBuffOverflowError(UART_Type *UARTx)
{
    WRITE_REG(UARTx->ISR, UART_ISR_OERR_Msk);
}

/**
  * @brief    Get UART Receive Time-Out Flag
  * @rmtoll   ISR    RXTO    FL_UART_IsActiveFlag_RXBuffTimeout
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsActiveFlag_RXBuffTimeout(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->ISR, UART_ISR_RXTO_Msk) == (UART_ISR_RXTO_Msk));
}

/**
  * @brief    Clear UART Receive Time-Out Flag
  * @rmtoll   ISR    RXTO    FL_UART_ClearFlag_RXBuffTimeout
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_ClearFlag_RXBuffTimeout(UART_Type *UARTx)
{
    WRITE_REG(UARTx->ISR, UART_ISR_RXTO_Msk);
}

/**
  * @brief    Get UART Receive Buffer Full Flag
  * @rmtoll   ISR    RXBF    FL_UART_IsActiveFlag_RXBuffFull
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsActiveFlag_RXBuffFull(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->ISR, UART_ISR_RXBF_Msk) == (UART_ISR_RXBF_Msk));
}

/**
  * @brief    Clear UART Receive Buffer Full Flag
  * @rmtoll   ISR    RXBF    FL_UART_ClearFlag_RXBuffFull
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_ClearFlag_RXBuffFull(UART_Type *UARTx)
{
    WRITE_REG(UARTx->ISR, UART_ISR_RXBF_Msk);
}

/**
  * @brief    Get UART Negedge Wakeup Flag
  * @rmtoll   ISR    NEWKF    FL_UART_IsActiveFlag_FallingEdgeWakeup
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsActiveFlag_FallingEdgeWakeup(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->ISR, UART_ISR_NEWKF_Msk) == (UART_ISR_NEWKF_Msk));
}

/**
  * @brief    Clear UART Negedge Wakeup Flag
  * @rmtoll   ISR    NEWKF    FL_UART_ClearFlag_FallingEdgeWakeup
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_ClearFlag_FallingEdgeWakeup(UART_Type *UARTx)
{
    WRITE_REG(UARTx->ISR, UART_ISR_NEWKF_Msk);
}

/**
  * @brief    Get UART Transmit Buffer Empty Flag
  * @rmtoll   ISR    TXBE    FL_UART_IsActiveFlag_TXBuffEmpty
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsActiveFlag_TXBuffEmpty(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->ISR, UART_ISR_TXBE_Msk) == (UART_ISR_TXBE_Msk));
}

/**
  * @brief    Clear UART Transmit Buffer Empty Flag
  * @rmtoll   ISR    TXBE    FL_UART_ClearFlag_TXBuffEmpty
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_ClearFlag_TXBuffEmpty(UART_Type *UARTx)
{
    WRITE_REG(UARTx->ISR, UART_ISR_TXBE_Msk);
}

/**
  * @brief    Get UART Transmit Shift register Empty  Flag
  * @rmtoll   ISR    TXSE    FL_UART_IsActiveFlag_TXShiftBuffEmpty
  * @param    UARTx UART instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_UART_IsActiveFlag_TXShiftBuffEmpty(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->ISR, UART_ISR_TXSE_Msk) == (UART_ISR_TXSE_Msk));
}

/**
  * @brief    Clear UART Transmit Shift register Empty Flag
  * @rmtoll   ISR    TXSE    FL_UART_ClearFlag_TXShiftBuffEmpty
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_UART_ClearFlag_TXShiftBuffEmpty(UART_Type *UARTx)
{
    WRITE_REG(UARTx->ISR, UART_ISR_TXSE_Msk);
}

/**
  * @brief    Set UART Transmit Delay Length
  * @rmtoll   TODR    TXDLY_LEN    FL_UART_WriteTXDelay
  * @param    UARTx UART instance
  * @param    time
  * @retval   None
  */
__STATIC_INLINE void FL_UART_WriteTXDelay(UART_Type *UARTx, uint32_t time)
{
    MODIFY_REG(UARTx->TODR, (0xffU << 8U), (time << 8U));
}

/**
  * @brief    Get UART Transmit Delay Length
  * @rmtoll   TODR    TXDLY_LEN    FL_UART_ReadTXDelay
  * @param    UARTx UART instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_UART_ReadTXDelay(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->TODR, (0xffU << 8U)) >> 8U);
}

/**
  * @brief    Set UART Receive Time-Out Length
  * @rmtoll   TODR    RXTO_LEN    FL_UART_WriteRXTimeout
  * @param    UARTx UART instance
  * @param    time
  * @retval   None
  */
__STATIC_INLINE void FL_UART_WriteRXTimeout(UART_Type *UARTx, uint32_t time)
{
    MODIFY_REG(UARTx->TODR, (0xffU << 0U), (time << 0U));
}

/**
  * @brief    Get UART Receive Time-Out Length
  * @rmtoll   TODR    RXTO_LEN    FL_UART_ReadRXTimeout
  * @param    UARTx UART instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_UART_ReadRXTimeout(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->TODR, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    UART Receive 1 byte of data
  * @rmtoll   RXBUF        FL_UART_ReadRXBuff
  * @param    UARTx UART instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_UART_ReadRXBuff(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->RXBUF, 0x1ffU));
}

/**
  * @brief    UART Transmit 1 byte of data
  * @rmtoll   TXBUF        FL_UART_WriteTXBuff
  * @param    UARTx UART instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_UART_WriteTXBuff(UART_Type *UARTx, uint32_t data)
{
    MODIFY_REG(UARTx->TXBUF, 0x1ffU, data);
}

/**
  * @brief    Set UART BaudRate
  * @rmtoll   BGR        FL_UART_WriteBaudRate
  * @param    UARTx UART instance
  * @param    baudRate
  * @retval   None
  */
__STATIC_INLINE void FL_UART_WriteBaudRate(UART_Type *UARTx, uint32_t baudRate)
{
    MODIFY_REG(UARTx->BGR, (0xffffU << 0U), (baudRate << 0U));
}

/**
  * @brief    Get UART BaudRate
  * @rmtoll   BGR        FL_UART_ReadBaudRate
  * @param    UARTx UART instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_UART_ReadBaudRate(UART_Type *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->BGR, (0xffffU << 0U)) >> 0U);
}

/**
  * @}
  */

/** @defgroup UART_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_UART_DeInit(UART_Type *UARTx);
FL_ErrorStatus FL_UART_Init(UART_Type *UARTx, FL_UART_InitTypeDef *initStruct);
FL_ErrorStatus FL_UART_InfraRed_Init(UART_Type *UARTx, FL_UART_InfraRed_InitTypeDef *initStruct);
void FL_UART_InfraRed_StructInit(FL_UART_InfraRed_InitTypeDef *initStruct);
void FL_UART_StructInit(FL_UART_InitTypeDef *initStruct);


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

#endif /* __FM33LC0XX_FL_UART_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.2 @ 2020-09-27*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
