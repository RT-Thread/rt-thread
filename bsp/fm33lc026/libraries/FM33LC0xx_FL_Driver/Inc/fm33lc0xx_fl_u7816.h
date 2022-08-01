/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_u7816.h
  * @author  FMSH Application Team
  * @brief   Head file of U7816 FL Module
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
#ifndef __FM33LC0XX_FL_U7816_H
#define __FM33LC0XX_FL_U7816_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup U7816 U7816
  * @brief U7816 FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup U7816_FL_ES_INIT U7816 Exported Init structures
  * @{
  */

/**
  * @brief U7816 Init Sturcture definition
  */
typedef struct
{
    /** 卡时钟频率 */
    uint32_t outputClockFreqence;

    /** 接口发送失败后自动重装使能 */
    uint32_t txAutoRetry;

    /** 自动重装次数 */
    uint32_t retryCnt;

    /** 插入BGT使能 */
    uint32_t blockGuard;

    /** 强上拉使能 */
    uint32_t strongPullUp;

    /** 帧格式奇偶校验模式 */
    uint32_t parity;

    /** 帧格式接收Guard时间 */
    uint32_t rxGuardTime;

    /** 帧格式发送Guard时间 */
    uint32_t txGuardTime;
    /** 帧格式错误Guard时间 */
    uint32_t errorGuardTime;

    /** 帧错误信号长度 */
    uint32_t errorSignalWidth;

    /** 接收校验错误自动回发error signal使能 */
    uint32_t rxAutoErrorSignal;

    /** 传输BIT顺序 */
    uint32_t transferOrder;

    /** 通讯速率 */
    uint32_t baud;

    /** 额外发送Guard时间 */
    uint32_t extraGuardTime;

} FL_U7816_InitTypeDef;

/**
  * @}
  */

/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup U7816_FL_Exported_Constants U7816 Exported Constants
  * @{
  */

#define    U7816_CR_TXEN_Pos                                      (5U)
#define    U7816_CR_TXEN_Msk                                      (0x1U << U7816_CR_TXEN_Pos)
#define    U7816_CR_TXEN                                          U7816_CR_TXEN_Msk

#define    U7816_CR_RXEN_Pos                                      (4U)
#define    U7816_CR_RXEN_Msk                                      (0x1U << U7816_CR_RXEN_Pos)
#define    U7816_CR_RXEN                                          U7816_CR_RXEN_Msk

#define    U7816_CR_CKOEN_Pos                                     (3U)
#define    U7816_CR_CKOEN_Msk                                     (0x1U << U7816_CR_CKOEN_Pos)
#define    U7816_CR_CKOEN                                         U7816_CR_CKOEN_Msk

#define    U7816_CR_HPUAT_Pos                                     (2U)
#define    U7816_CR_HPUAT_Msk                                     (0x1U << U7816_CR_HPUAT_Pos)
#define    U7816_CR_HPUAT                                         U7816_CR_HPUAT_Msk

#define    U7816_CR_HPUEN_Pos                                     (1U)
#define    U7816_CR_HPUEN_Msk                                     (0x1U << U7816_CR_HPUEN_Pos)
#define    U7816_CR_HPUEN                                         U7816_CR_HPUEN_Msk

#define    U7816_FFR_SFREN_Pos                                    (11U)
#define    U7816_FFR_SFREN_Msk                                    (0x1U << U7816_FFR_SFREN_Pos)
#define    U7816_FFR_SFREN                                        U7816_FFR_SFREN_Msk

#define    U7816_FFR_ERSW_Pos                                     (9U)
#define    U7816_FFR_ERSW_Msk                                     (0x3U << U7816_FFR_ERSW_Pos)
#define    U7816_FFR_ERSW                                         U7816_FFR_ERSW_Msk

#define    U7816_FFR_ERSGD_Pos                                    (8U)
#define    U7816_FFR_ERSGD_Msk                                    (0x1U << U7816_FFR_ERSGD_Pos)
#define    U7816_FFR_ERSGD                                        U7816_FFR_ERSGD_Msk

#define    U7816_FFR_BGTEN_Pos                                    (7U)
#define    U7816_FFR_BGTEN_Msk                                    (0x1U << U7816_FFR_BGTEN_Pos)
#define    U7816_FFR_BGTEN                                        U7816_FFR_BGTEN_Msk

#define    U7816_FFR_REP_T_Pos                                    (6U)
#define    U7816_FFR_REP_T_Msk                                    (0x1U << U7816_FFR_REP_T_Pos)
#define    U7816_FFR_REP_T                                        U7816_FFR_REP_T_Msk

#define    U7816_FFR_PAR_Pos                                      (4U)
#define    U7816_FFR_PAR_Msk                                      (0x3U << U7816_FFR_PAR_Pos)
#define    U7816_FFR_PAR                                          U7816_FFR_PAR_Msk

#define    U7816_FFR_RFREN_Pos                                    (3U)
#define    U7816_FFR_RFREN_Msk                                    (0x1U << U7816_FFR_RFREN_Pos)
#define    U7816_FFR_RFREN                                        U7816_FFR_RFREN_Msk

#define    U7816_FFR_TREPEN_Pos                                   (2U)
#define    U7816_FFR_TREPEN_Msk                                   (0x1U << U7816_FFR_TREPEN_Pos)
#define    U7816_FFR_TREPEN                                       U7816_FFR_TREPEN_Msk

#define    U7816_FFR_RREPEN_Pos                                   (1U)
#define    U7816_FFR_RREPEN_Msk                                   (0x1U << U7816_FFR_RREPEN_Pos)
#define    U7816_FFR_RREPEN                                       U7816_FFR_RREPEN_Msk

#define    U7816_FFR_DICONV_Pos                                   (0U)
#define    U7816_FFR_DICONV_Msk                                   (0x1U << U7816_FFR_DICONV_Pos)
#define    U7816_FFR_DICONV                                       U7816_FFR_DICONV_Msk

#define    U7816_IER_RXIE_Pos                                     (2U)
#define    U7816_IER_RXIE_Msk                                     (0x1U << U7816_IER_RXIE_Pos)
#define    U7816_IER_RXIE                                         U7816_IER_RXIE_Msk

#define    U7816_IER_TXIE_Pos                                     (1U)
#define    U7816_IER_TXIE_Msk                                     (0x1U << U7816_IER_TXIE_Pos)
#define    U7816_IER_TXIE                                         U7816_IER_TXIE_Msk

#define    U7816_IER_LSIE_Pos                                     (0U)
#define    U7816_IER_LSIE_Msk                                     (0x1U << U7816_IER_LSIE_Pos)
#define    U7816_IER_LSIE                                         U7816_IER_LSIE_Msk

#define    U7816_ISR_WAIT_RPT_Pos                                 (18U)
#define    U7816_ISR_WAIT_RPT_Msk                                 (0x1U << U7816_ISR_WAIT_RPT_Pos)
#define    U7816_ISR_WAIT_RPT                                     U7816_ISR_WAIT_RPT_Msk

#define    U7816_ISR_TXBUSY_Pos                                   (17U)
#define    U7816_ISR_TXBUSY_Msk                                   (0x1U << U7816_ISR_TXBUSY_Pos)
#define    U7816_ISR_TXBUSY                                       U7816_ISR_TXBUSY_Msk

#define    U7816_ISR_RXBUSY_Pos                                   (16U)
#define    U7816_ISR_RXBUSY_Msk                                   (0x1U << U7816_ISR_RXBUSY_Pos)
#define    U7816_ISR_RXBUSY                                       U7816_ISR_RXBUSY_Msk

#define    U7816_ISR_TPARERR_Pos                                  (11U)
#define    U7816_ISR_TPARERR_Msk                                  (0x1U << U7816_ISR_TPARERR_Pos)
#define    U7816_ISR_TPARERR                                      U7816_ISR_TPARERR_Msk

#define    U7816_ISR_RPARERR_Pos                                  (10U)
#define    U7816_ISR_RPARERR_Msk                                  (0x1U << U7816_ISR_RPARERR_Pos)
#define    U7816_ISR_RPARERR                                      U7816_ISR_RPARERR_Msk

#define    U7816_ISR_FRERR_Pos                                    (9U)
#define    U7816_ISR_FRERR_Msk                                    (0x1U << U7816_ISR_FRERR_Pos)
#define    U7816_ISR_FRERR                                        U7816_ISR_FRERR_Msk

#define    U7816_ISR_OVERR_Pos                                    (8U)
#define    U7816_ISR_OVERR_Msk                                    (0x1U << U7816_ISR_OVERR_Pos)
#define    U7816_ISR_OVERR                                        U7816_ISR_OVERR_Msk

#define    U7816_ISR_RXIF_Pos                                     (2U)
#define    U7816_ISR_RXIF_Msk                                     (0x1U << U7816_ISR_RXIF_Pos)
#define    U7816_ISR_RXIF                                         U7816_ISR_RXIF_Msk

#define    U7816_ISR_TXIF_Pos                                     (1U)
#define    U7816_ISR_TXIF_Msk                                     (0x1U << U7816_ISR_TXIF_Pos)
#define    U7816_ISR_TXIF                                         U7816_ISR_TXIF_Msk

#define    U7816_ISR_ERRIF_Pos                                    (0U)
#define    U7816_ISR_ERRIF_Msk                                    (0x1U << U7816_ISR_ERRIF_Pos)
#define    U7816_ISR_ERRIF                                        U7816_ISR_ERRIF_Msk






#define    FL_U7816_TX_GUARD_TIME_2ETU                            (0x0U << U7816_FFR_SFREN_Pos)
#define    FL_U7816_TX_GUARD_TIME_3ETU                            (0x1U << U7816_FFR_SFREN_Pos)


#define    FL_U7816_ERROR_SIGNAL_WIDTH_2ETU                       (0x1U << U7816_FFR_ERSW_Pos)
#define    FL_U7816_ERROR_SIGNAL_WIDTH_1P5ETU                     (0x2U << U7816_FFR_ERSW_Pos)
#define    FL_U7816_ERROR_SIGNAL_WIDTH_1ETU                       (0x3U << U7816_FFR_ERSW_Pos)


#define    FL_U7816_ERROR_GUARD_TIME_2ETU                         (0x0U << U7816_FFR_ERSGD_Pos)
#define    FL_U7816_ERROR_GUARD_TIME_1ETU                         (0x1U << U7816_FFR_ERSGD_Pos)


#define    FL_U7816_RETRY_COUNT_1                                 (0x0U << U7816_FFR_REP_T_Pos)
#define    FL_U7816_RETRY_COUNT_3                                 (0x1U << U7816_FFR_REP_T_Pos)


#define    FL_U7816_PARITY_EVEN                                   (0x0U << U7816_FFR_PAR_Pos)
#define    FL_U7816_PARITY_ODD                                    (0x1U << U7816_FFR_PAR_Pos)
#define    FL_U7816_PARITY_ALWAYS_1                               (0x2U << U7816_FFR_PAR_Pos)
#define    FL_U7816_PARITY_NONE                                   (0x3U << U7816_FFR_PAR_Pos)


#define    FL_U7816_RX_GUARD_TIME_2ETU                            (0x0U << U7816_FFR_RFREN_Pos)
#define    FL_U7816_RX_GUARD_TIME_1ETU                            (0x1U << U7816_FFR_RFREN_Pos)


#define    FL_U7816_BIT_ORDER_LSB_FIRST                           (0x0U << U7816_FFR_DICONV_Pos)
#define    FL_U7816_BIT_ORDER_MSB_FIRST                           (0x1U << U7816_FFR_DICONV_Pos)

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup U7816_FL_Exported_Functions U7816 Exported Functions
  * @{
  */

/**
  * @brief    Enable U7816 Transmit
  * @rmtoll   CR    TXEN    FL_U7816_EnableTX
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_EnableTX(U7816_Type *U7816x)
{
    SET_BIT(U7816x->CR, U7816_CR_TXEN_Msk);
}

/**
  * @brief    Get U7816 Transmit Enable Status
  * @rmtoll   CR    TXEN    FL_U7816_IsEnabledTX
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsEnabledTX(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->CR, U7816_CR_TXEN_Msk) == U7816_CR_TXEN_Msk);
}

/**
  * @brief    Disable U7816 Transmit
  * @rmtoll   CR    TXEN    FL_U7816_DisableTX
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_DisableTX(U7816_Type *U7816x)
{
    CLEAR_BIT(U7816x->CR, U7816_CR_TXEN_Msk);
}

/**
  * @brief    Enable U7816 Receive
  * @rmtoll   CR    RXEN    FL_U7816_EnableRX
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_EnableRX(U7816_Type *U7816x)
{
    SET_BIT(U7816x->CR, U7816_CR_RXEN_Msk);
}

/**
  * @brief    Get U7816 Receive Enable Status
  * @rmtoll   CR    RXEN    FL_U7816_IsEnabledRX
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsEnabledRX(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->CR, U7816_CR_RXEN_Msk) == U7816_CR_RXEN_Msk);
}

/**
  * @brief    Disable U7816 Receive
  * @rmtoll   CR    RXEN    FL_U7816_DisableRX
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_DisableRX(U7816_Type *U7816x)
{
    CLEAR_BIT(U7816x->CR, U7816_CR_RXEN_Msk);
}

/**
  * @brief    Enable U7816 Clock Output
  * @rmtoll   CR    CKOEN    FL_U7816_EnableClockOutput
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_EnableClockOutput(U7816_Type *U7816x)
{
    SET_BIT(U7816x->CR, U7816_CR_CKOEN_Msk);
}

/**
  * @brief    Get U7816 Clock Output Enable Status
  * @rmtoll   CR    CKOEN    FL_U7816_IsEnabledClockOutput
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsEnabledClockOutput(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->CR, U7816_CR_CKOEN_Msk) == U7816_CR_CKOEN_Msk);
}

/**
  * @brief    Disable U7816 Clock Output
  * @rmtoll   CR    CKOEN    FL_U7816_DisableClockOutput
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_DisableClockOutput(U7816_Type *U7816x)
{
    CLEAR_BIT(U7816x->CR, U7816_CR_CKOEN_Msk);
}

/**
  * @brief    Enable U7816 Automatically High-Pullup
  * @rmtoll   CR    HPUAT    FL_U7816_EnableTXAutoPullup
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_EnableTXAutoPullup(U7816_Type *U7816x)
{
    SET_BIT(U7816x->CR, U7816_CR_HPUAT_Msk);
}

/**
  * @brief    Get U7816 Automatically High-Pullup Enable Status
  * @rmtoll   CR    HPUAT    FL_U7816_IsEnabledTXAutoPullup
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsEnabledTXAutoPullup(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->CR, U7816_CR_HPUAT_Msk) == U7816_CR_HPUAT_Msk);
}

/**
  * @brief    Disable U7816 Automatically High-Pullup
  * @rmtoll   CR    HPUAT    FL_U7816_DisableTXAutoPullup
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_DisableTXAutoPullup(U7816_Type *U7816x)
{
    CLEAR_BIT(U7816x->CR, U7816_CR_HPUAT_Msk);
}

/**
  * @brief    Enable U7816 High-Pullup
  * @rmtoll   CR    HPUEN    FL_U7816_EnablePullup
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_EnablePullup(U7816_Type *U7816x)
{
    SET_BIT(U7816x->CR, U7816_CR_HPUEN_Msk);
}

/**
  * @brief    Disable U7816 High-Pullup
  * @rmtoll   CR    HPUEN    FL_U7816_DisablePullup
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_DisablePullup(U7816_Type *U7816x)
{
    CLEAR_BIT(U7816x->CR, U7816_CR_HPUEN_Msk);
}

/**
  * @brief    Set U7816 TX Guard Time Length
  * @rmtoll   FFR    SFREN    FL_U7816_SetTXGuardTime
  * @param    U7816x U7816 instance
  * @param    config This parameter can be one of the following values:
  *           @arg @ref FL_U7816_TX_GUARD_TIME_2ETU
  *           @arg @ref FL_U7816_TX_GUARD_TIME_3ETU
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_SetTXGuardTime(U7816_Type *U7816x, uint32_t config)
{
    MODIFY_REG(U7816x->FFR, U7816_FFR_SFREN_Msk, config);
}

/**
  * @brief    Get U7816 TX Guard Time Length
  * @rmtoll   FFR    SFREN    FL_U7816_GetTXGuardTime
  * @param    U7816x U7816 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_U7816_TX_GUARD_TIME_2ETU
  *           @arg @ref FL_U7816_TX_GUARD_TIME_3ETU
  */
__STATIC_INLINE uint32_t FL_U7816_GetTXGuardTime(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->FFR, U7816_FFR_SFREN_Msk));
}

/**
  * @brief    Set U7816 TX Error Signal Length
  * @rmtoll   FFR    ERSW    FL_U7816_SetErrorSignalWidth
  * @param    U7816x U7816 instance
  * @param    width This parameter can be one of the following values:
  *           @arg @ref FL_U7816_ERROR_SIGNAL_WIDTH_2ETU
  *           @arg @ref FL_U7816_ERROR_SIGNAL_WIDTH_1P5ETU
  *           @arg @ref FL_U7816_ERROR_SIGNAL_WIDTH_1ETU
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_SetErrorSignalWidth(U7816_Type *U7816x, uint32_t width)
{
    MODIFY_REG(U7816x->FFR, U7816_FFR_ERSW_Msk, width);
}

/**
  * @brief    Get U7816 TX Error Signal Length
  * @rmtoll   FFR    ERSW    FL_U7816_GetErrorSignalWidth
  * @param    U7816x U7816 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_U7816_ERROR_SIGNAL_WIDTH_2ETU
  *           @arg @ref FL_U7816_ERROR_SIGNAL_WIDTH_1P5ETU
  *           @arg @ref FL_U7816_ERROR_SIGNAL_WIDTH_1ETU
  */
__STATIC_INLINE uint32_t FL_U7816_GetErrorSignalWidth(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->FFR, U7816_FFR_ERSW_Msk));
}

/**
  * @brief    Set Error Signal Guard Time
  * @rmtoll   FFR    ERSGD    FL_U7816_SetErrorGuardTime
  * @param    U7816x U7816 instance
  * @param    config This parameter can be one of the following values:
  *           @arg @ref FL_U7816_ERROR_GUARD_TIME_2ETU
  *           @arg @ref FL_U7816_ERROR_GUARD_TIME_1ETU
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_SetErrorGuardTime(U7816_Type *U7816x, uint32_t config)
{
    MODIFY_REG(U7816x->FFR, U7816_FFR_ERSGD_Msk, config);
}

/**
  * @brief    Get Error Signal Guard Time
  * @rmtoll   FFR    ERSGD    FL_U7816_GetErrorGuardTime
  * @param    U7816x U7816 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_U7816_ERROR_GUARD_TIME_2ETU
  *           @arg @ref FL_U7816_ERROR_GUARD_TIME_1ETU
  */
__STATIC_INLINE uint32_t FL_U7816_GetErrorGuardTime(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->FFR, U7816_FFR_ERSGD_Msk));
}

/**
  * @brief    Enable U7816 to Insert Block Guard Time
  * @rmtoll   FFR    BGTEN    FL_U7816_EnableBlockGuardTime
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_EnableBlockGuardTime(U7816_Type *U7816x)
{
    SET_BIT(U7816x->FFR, U7816_FFR_BGTEN_Msk);
}

/**
  * @brief    Get U7816 Block Guard Time Enable Status
  * @rmtoll   FFR    BGTEN    FL_U7816_IsEnabledBlockGuardTime
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsEnabledBlockGuardTime(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->FFR, U7816_FFR_BGTEN_Msk) == U7816_FFR_BGTEN_Msk);
}

/**
  * @brief    Disable U7816 to Insert Block Guard Time
  * @rmtoll   FFR    BGTEN    FL_U7816_DisableBlockGuardTime
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_DisableBlockGuardTime(U7816_Type *U7816x)
{
    CLEAR_BIT(U7816x->FFR, U7816_FFR_BGTEN_Msk);
}

/**
  * @brief    Set U7816 Retry Counts When Parity Error Occurred
  * @rmtoll   FFR    REP_T    FL_U7816_SetRetryCount
  * @param    U7816x U7816 instance
  * @param    cnt This parameter can be one of the following values:
  *           @arg @ref FL_U7816_RETRY_COUNT_1
  *           @arg @ref FL_U7816_RETRY_COUNT_3
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_SetRetryCount(U7816_Type *U7816x, uint32_t cnt)
{
    MODIFY_REG(U7816x->FFR, U7816_FFR_REP_T_Msk, cnt);
}

/**
  * @brief    Get U7816 Retry Counts When Parity Error Occurred
  * @rmtoll   FFR    REP_T    FL_U7816_GetRetryCount
  * @param    U7816x U7816 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_U7816_RETRY_COUNT_1
  *           @arg @ref FL_U7816_RETRY_COUNT_3
  */
__STATIC_INLINE uint32_t FL_U7816_GetRetryCount(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->FFR, U7816_FFR_REP_T_Msk));
}

/**
  * @brief    Set U7816 Parity
  * @rmtoll   FFR    PAR    FL_U7816_SetParity
  * @param    U7816x U7816 instance
  * @param    parity This parameter can be one of the following values:
  *           @arg @ref FL_U7816_PARITY_EVEN
  *           @arg @ref FL_U7816_PARITY_ODD
  *           @arg @ref FL_U7816_PARITY_ALWAYS_1
  *           @arg @ref FL_U7816_PARITY_NONE
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_SetParity(U7816_Type *U7816x, uint32_t parity)
{
    MODIFY_REG(U7816x->FFR, U7816_FFR_PAR_Msk, parity);
}

/**
  * @brief    Get U7816 Parity
  * @rmtoll   FFR    PAR    FL_U7816_GetParity
  * @param    U7816x U7816 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_U7816_PARITY_EVEN
  *           @arg @ref FL_U7816_PARITY_ODD
  *           @arg @ref FL_U7816_PARITY_ALWAYS_1
  *           @arg @ref FL_U7816_PARITY_NONE
  */
__STATIC_INLINE uint32_t FL_U7816_GetParity(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->FFR, U7816_FFR_PAR_Msk));
}

/**
  * @brief    Set U7816 RX Guard Time Length
  * @rmtoll   FFR    RFREN    FL_U7816_SetRXGuardTime
  * @param    U7816x U7816 instance
  * @param    config This parameter can be one of the following values:
  *           @arg @ref FL_U7816_RX_GUARD_TIME_2ETU
  *           @arg @ref FL_U7816_RX_GUARD_TIME_1ETU
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_SetRXGuardTime(U7816_Type *U7816x, uint32_t config)
{
    MODIFY_REG(U7816x->FFR, U7816_FFR_RFREN_Msk, config);
}

/**
  * @brief    Get U7816 RX Guard Time Length
  * @rmtoll   FFR    RFREN    FL_U7816_GetRXGuardTime
  * @param    U7816x U7816 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_U7816_RX_GUARD_TIME_2ETU
  *           @arg @ref FL_U7816_RX_GUARD_TIME_1ETU
  */
__STATIC_INLINE uint32_t FL_U7816_GetRXGuardTime(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->FFR, U7816_FFR_RFREN_Msk));
}

/**
  * @brief    Set U7816 TX Auto Retry When Parity Error Occurred
  * @rmtoll   FFR    TREPEN    FL_U7816_EnableTXParityErrorAutoRetry
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_EnableTXParityErrorAutoRetry(U7816_Type *U7816x)
{
    SET_BIT(U7816x->FFR, U7816_FFR_TREPEN_Msk);
}

/**
  * @brief    Get U7816 TX Auto Retry When Parity Error Occurred
  * @rmtoll   FFR    TREPEN    FL_U7816_DisableTXParityErrorAutoRetry
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_DisableTXParityErrorAutoRetry(U7816_Type *U7816x)
{
    CLEAR_BIT(U7816x->FFR, U7816_FFR_TREPEN_Msk);
}

/**
  * @brief    Get U7816 TX Auto Retry When Parity Error Occurred
  * @rmtoll   FFR    TREPEN    FL_U7816_IsEnabledTXParityErrorAutoRetry
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsEnabledTXParityErrorAutoRetry(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->FFR, U7816_FFR_TREPEN_Msk) == U7816_FFR_TREPEN_Msk);
}

/**
  * @brief    Get U7816 RX Auto Retry When Parity Error Occurred
  * @rmtoll   FFR    RREPEN    FL_U7816_EnableRXParityErrorAutoRetry
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_EnableRXParityErrorAutoRetry(U7816_Type *U7816x)
{
    SET_BIT(U7816x->FFR, U7816_FFR_RREPEN_Msk);
}

/**
  * @brief    Get U7816 RX Auto Retry When Parity Error Occurred
  * @rmtoll   FFR    RREPEN    FL_U7816_DisableRXParityErrorAutoRetry
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_DisableRXParityErrorAutoRetry(U7816_Type *U7816x)
{
    CLEAR_BIT(U7816x->FFR, U7816_FFR_RREPEN_Msk);
}

/**
  * @brief    Get U7816 RX Auto Retry When Parity Error Occurred
  * @rmtoll   FFR    RREPEN    FL_U7816_IsEnabledRXParityErrorAutoRetry
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsEnabledRXParityErrorAutoRetry(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->FFR, U7816_FFR_RREPEN_Msk) == U7816_FFR_RREPEN_Msk);
}

/**
  * @brief    Set U7816 Bit Order
  * @rmtoll   FFR    DICONV    FL_U7816_SetBitOrder
  * @param    U7816x U7816 instance
  * @param    order This parameter can be one of the following values:
  *           @arg @ref FL_U7816_BIT_ORDER_LSB_FIRST
  *           @arg @ref FL_U7816_BIT_ORDER_MSB_FIRST
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_SetBitOrder(U7816_Type *U7816x, uint32_t order)
{
    MODIFY_REG(U7816x->FFR, U7816_FFR_DICONV_Msk, order);
}

/**
  * @brief    Get U7816 Bit Order
  * @rmtoll   FFR    DICONV    FL_U7816_GetBitOrder
  * @param    U7816x U7816 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_U7816_BIT_ORDER_LSB_FIRST
  *           @arg @ref FL_U7816_BIT_ORDER_MSB_FIRST
  */
__STATIC_INLINE uint32_t FL_U7816_GetBitOrder(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->FFR, U7816_FFR_DICONV_Msk));
}

/**
  * @brief    Set U7816 Extra Guard Time
  * @rmtoll   EGTR        FL_U7816_WriteExtraGuardTime
  * @param    U7816x U7816 instance
  * @param    time
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_WriteExtraGuardTime(U7816_Type *U7816x, uint32_t time)
{
    MODIFY_REG(U7816x->EGTR, (0xffU << 0U), (time << 0U));
}

/**
  * @brief    Get U7816 Extra Guard Time
  * @rmtoll   EGTR        FL_U7816_ReadExtraGuardTime
  * @param    U7816x U7816 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_U7816_ReadExtraGuardTime(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->EGTR, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    Set U7816 Clock Divide
  * @rmtoll   PSC        FL_U7816_WriteClockDivision
  * @param    U7816x U7816 instance
  * @param    div
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_WriteClockDivision(U7816_Type *U7816x, uint32_t div)
{
    MODIFY_REG(U7816x->PSC, (0x1fU << 0U), (div << 0U));
}

/**
  * @brief    Get U7816 Clock Divide
  * @rmtoll   PSC        FL_U7816_ReadClockDivision
  * @param    U7816x U7816 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_U7816_ReadClockDivision(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->PSC, (0x1fU << 0U)) >> 0U);
}

/**
  * @brief    Set U7816 BaudRate
  * @rmtoll   BGR        FL_U7816_WriteBaudRate
  * @param    U7816x U7816 instance
  * @param    baud
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_WriteBaudRate(U7816_Type *U7816x, uint32_t baud)
{
    MODIFY_REG(U7816x->BGR, (0xfffU << 0U), (baud << 0U));
}

/**
  * @brief    Get U7816 BaudRate
  * @rmtoll   BGR        FL_U7816_ReadBaudRate
  * @param    U7816x U7816 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_U7816_ReadBaudRate(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->BGR, (0xfffU << 0U)) >> 0U);
}

/**
  * @brief    U7816 Write 1 byte of data
  * @rmtoll   TXBUF        FL_U7816_WriteTXBuff
  * @param    U7816x U7816 instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_WriteTXBuff(U7816_Type *U7816x, uint32_t data)
{
    MODIFY_REG(U7816x->TXBUF, (0xffU << 0U), (data << 0U));
}

/**
  * @brief    U7816 Read 1 byte of data
  * @rmtoll   RXBUF        FL_U7816_ReadRXBuff
  * @param    U7816x U7816 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_U7816_ReadRXBuff(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->RXBUF, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    Disable U7816 Receive Complete Interrupt
  * @rmtoll   IER    RXIE    FL_U7816_DisableIT_RXComplete
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_DisableIT_RXComplete(U7816_Type *U7816x)
{
    CLEAR_BIT(U7816x->IER, U7816_IER_RXIE_Msk);
}

/**
  * @brief    Enable U7816 Receive Complete Interrupt
  * @rmtoll   IER    RXIE    FL_U7816_EnableIT_RXComplete
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_EnableIT_RXComplete(U7816_Type *U7816x)
{
    SET_BIT(U7816x->IER, U7816_IER_RXIE_Msk);
}

/**
  * @brief    Get U7816 Receive Complete Interrupt Enable Status
  * @rmtoll   IER    RXIE    FL_U7816_IsEnabledIT_RXComplete
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsEnabledIT_RXComplete(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->IER, U7816_IER_RXIE_Msk) == U7816_IER_RXIE_Msk);
}

/**
  * @brief    Disable U7816 Transmit Complete Interrupt
  * @rmtoll   IER    TXIE    FL_U7816_DisableIT_TXComplete
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_DisableIT_TXComplete(U7816_Type *U7816x)
{
    CLEAR_BIT(U7816x->IER, U7816_IER_TXIE_Msk);
}

/**
  * @brief    Enable U7816 Transmit Complete Interrupt
  * @rmtoll   IER    TXIE    FL_U7816_EnableIT_TXComplete
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_EnableIT_TXComplete(U7816_Type *U7816x)
{
    SET_BIT(U7816x->IER, U7816_IER_TXIE_Msk);
}

/**
  * @brief    Disable U7816 Line Status Interrupt
  * @rmtoll   IER    LSIE    FL_U7816_DisableIT_Error
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_DisableIT_Error(U7816_Type *U7816x)
{
    CLEAR_BIT(U7816x->IER, U7816_IER_LSIE_Msk);
}

/**
  * @brief    Enable U7816 Line Status Interrupt
  * @rmtoll   IER    LSIE    FL_U7816_EnableIT_Error
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_EnableIT_Error(U7816_Type *U7816x)
{
    SET_BIT(U7816x->IER, U7816_IER_LSIE_Msk);
}

/**
  * @brief    Get U7816 Line Status Interrupt Enable Status
  * @rmtoll   IER    LSIE    FL_U7816_IsEnabledIT_Error
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsEnabledIT_Error(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->IER, U7816_IER_LSIE_Msk) == U7816_IER_LSIE_Msk);
}

/**
  * @brief    Get U7816 Waiting for Retry Flag
  * @rmtoll   ISR    WAIT_RPT    FL_U7816_IsActiveFlag_WaitRetry
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsActiveFlag_WaitRetry(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->ISR, U7816_ISR_WAIT_RPT_Msk) == (U7816_ISR_WAIT_RPT_Msk));
}

/**
  * @brief    Get U7816 Transmission Busy Flag
  * @rmtoll   ISR    TXBUSY    FL_U7816_IsActiveFlag_TXBusy
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsActiveFlag_TXBusy(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->ISR, U7816_ISR_TXBUSY_Msk) == (U7816_ISR_TXBUSY_Msk));
}

/**
  * @brief    Get U7816 Receivement Busy Flag
  * @rmtoll   ISR    RXBUSY    FL_U7816_IsActiveFlag_RXBusy
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsActiveFlag_RXBusy(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->ISR, U7816_ISR_RXBUSY_Msk) == (U7816_ISR_RXBUSY_Msk));
}

/**
  * @brief    Get U7816 Transmit Parity Error Flag
  * @rmtoll   ISR    TPARERR    FL_U7816_IsActiveFlag_TXParityError
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsActiveFlag_TXParityError(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->ISR, U7816_ISR_TPARERR_Msk) == (U7816_ISR_TPARERR_Msk));
}

/**
  * @brief    Clear U7816 Transmit Parity Error Flag
  * @rmtoll   ISR    TPARERR    FL_U7816_ClearFlag_TXParityError
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_ClearFlag_TXParityError(U7816_Type *U7816x)
{
    WRITE_REG(U7816x->ISR, U7816_ISR_TPARERR_Msk);
}

/**
  * @brief    Get U7816 Receive Parity Error Flag
  * @rmtoll   ISR    RPARERR    FL_U7816_IsActiveFlag_RXParityError
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsActiveFlag_RXParityError(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->ISR, U7816_ISR_RPARERR_Msk) == (U7816_ISR_RPARERR_Msk));
}

/**
  * @brief    Clear U7816 Receive Parity Error Flag
  * @rmtoll   ISR    RPARERR    FL_U7816_ClearFlag_RXParityError
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_ClearFlag_RXParityError(U7816_Type *U7816x)
{
    WRITE_REG(U7816x->ISR, U7816_ISR_RPARERR_Msk);
}

/**
  * @brief    Get U7816 Receive Frame Error Flag
  * @rmtoll   ISR    FRERR    FL_U7816_IsActiveFlag_RXFrameError
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsActiveFlag_RXFrameError(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->ISR, U7816_ISR_FRERR_Msk) == (U7816_ISR_FRERR_Msk));
}

/**
  * @brief    Clear U7816 Receive Frame Error Flag
  * @rmtoll   ISR    FRERR    FL_U7816_ClearFlag_RXFrameError
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_ClearFlag_RXFrameError(U7816_Type *U7816x)
{
    WRITE_REG(U7816x->ISR, U7816_ISR_FRERR_Msk);
}

/**
  * @brief    Get U7816 Receive Overflow Error Flag
  * @rmtoll   ISR    OVERR    FL_U7816_IsActiveFlag_RXOverflow
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsActiveFlag_RXOverflow(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->ISR, U7816_ISR_OVERR_Msk) == (U7816_ISR_OVERR_Msk));
}

/**
  * @brief    Clear U7816 Receive Overflow Error Flag
  * @rmtoll   ISR    OVERR    FL_U7816_ClearFlag_RXOverflow
  * @param    U7816x U7816 instance
  * @retval   None
  */
__STATIC_INLINE void FL_U7816_ClearFlag_RXOverflow(U7816_Type *U7816x)
{
    WRITE_REG(U7816x->ISR, U7816_ISR_OVERR_Msk);
}

/**
  * @brief    Get U7816 Receive Complete Flag
  * @rmtoll   ISR    RXIF    FL_U7816_IsActiveFlag_RXComplete
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsActiveFlag_RXComplete(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->ISR, U7816_ISR_RXIF_Msk) == (U7816_ISR_RXIF_Msk));
}

/**
  * @brief    Get U7816 Transmit Buffer Empty Flag
  * @rmtoll   ISR    TXIF    FL_U7816_IsActiveFlag_TXBuffEmpty
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsActiveFlag_TXBuffEmpty(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->ISR, U7816_ISR_TXIF_Msk) == (U7816_ISR_TXIF_Msk));
}

/**
  * @brief    Get U7816 Error Flag
  * @rmtoll   ISR    ERRIF    FL_U7816_IsActiveFlag_Error
  * @param    U7816x U7816 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_U7816_IsActiveFlag_Error(U7816_Type *U7816x)
{
    return (uint32_t)(READ_BIT(U7816x->ISR, U7816_ISR_ERRIF_Msk) == (U7816_ISR_ERRIF_Msk));
}

/**
  * @}
  */

/** @defgroup U7816_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_U7816_DeInit(U7816_Type *U7816x);
FL_ErrorStatus FL_U7816_Init(U7816_Type *U7816x, FL_U7816_InitTypeDef *U7816_InitStruct);
void FL_U7816_StructInit(FL_U7816_InitTypeDef *U7816_InitStruct);

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

#endif /* __FM33LC0XX_FL_U7816_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.2 @ 2020-09-27*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
