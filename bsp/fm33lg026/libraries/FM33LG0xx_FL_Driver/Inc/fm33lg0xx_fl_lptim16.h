/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_lptim16.h
  * @author  FMSH Application Team
  * @brief   Head file of LPTIM16 FL Module
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
#ifndef __FM33LG0XX_FL_LPTIM16_H
#define __FM33LG0XX_FL_LPTIM16_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup LPTIM16 LPTIM16
  * @brief LPTIM16 FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup LPTIM16_FL_ES_INIT LPTIM16 Exported Init structures
  * @{
  */

/**
  * @brief FL LPTIM16 Init Sturcture definition
  */

/**
  * @brief LPTIM16 Init Sturcture Definition
  */
typedef struct
{
    /* 内部时钟源 */
    uint32_t clockSource;

    /* 预分频器的时钟源 可选择内部时钟, 也可选择外部时钟 */
    uint32_t prescalerClockSource;

    /* 预分频系数 */
    uint32_t prescaler;

    /* 重装值 */
    uint32_t autoReload;

    /* 定时器工作模式选择 */
    uint32_t mode;

    /* 定时器编码器模式 */
    uint32_t encoderMode;

    /* 单次计数使能 */
    uint32_t onePulseMode;

    /* ETR异步计数边沿 */
    uint32_t countEdge;

    /* ETR触发计数边沿 */
    uint32_t triggerEdge;

} FL_LPTIM16_InitTypeDef;

/**
  * @brief  LPTIM16 Output Compare Configuration Structure Definition
  */
typedef struct
{
    uint32_t compareValue;

    uint32_t OCPolarity;

} FL_LPTIM16_OC_InitTypeDef;

/**
  * @brief  LPTIM16 Input Capture Configuration Structure Definition
  */
typedef struct
{
    uint32_t channel1Prescaler;

    uint32_t channel1CaptureSource;

    uint32_t ICInputDigitalFilter;

    uint32_t ICInputPolarity;

    uint32_t ICEdge;

} FL_LPTIM16_IC_InitTypeDef;
/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup LPTIM16_FL_Exported_Constants LPTIM16 Exported Constants
  * @{
  */

#define    LPTIM16_CR_EN_Pos                                      (0U)
#define    LPTIM16_CR_EN_Msk                                      (0x1U << LPTIM16_CR_EN_Pos)
#define    LPTIM16_CR_EN                                          LPTIM16_CR_EN_Msk

#define    LPTIM16_CFGR_ETR_AFEN_Pos                              (24U)
#define    LPTIM16_CFGR_ETR_AFEN_Msk                              (0x1U << LPTIM16_CFGR_ETR_AFEN_Pos)
#define    LPTIM16_CFGR_ETR_AFEN                                  LPTIM16_CFGR_ETR_AFEN_Msk

#define    LPTIM16_CFGR_PSCSEL_Pos                                (14U)
#define    LPTIM16_CFGR_PSCSEL_Msk                                (0x1U << LPTIM16_CFGR_PSCSEL_Pos)
#define    LPTIM16_CFGR_PSCSEL                                    LPTIM16_CFGR_PSCSEL_Msk

#define    LPTIM16_CFGR_DIVSEL_Pos                                (10U)
#define    LPTIM16_CFGR_DIVSEL_Msk                                (0x7U << LPTIM16_CFGR_DIVSEL_Pos)
#define    LPTIM16_CFGR_DIVSEL                                    LPTIM16_CFGR_DIVSEL_Msk

#define    LPTIM16_CFGR_EDGESEL_Pos                               (7U)
#define    LPTIM16_CFGR_EDGESEL_Msk                               (0x1U << LPTIM16_CFGR_EDGESEL_Pos)
#define    LPTIM16_CFGR_EDGESEL                                   LPTIM16_CFGR_EDGESEL_Msk

#define    LPTIM16_CFGR_TRIGCFG_Pos                               (5U)
#define    LPTIM16_CFGR_TRIGCFG_Msk                               (0x3U << LPTIM16_CFGR_TRIGCFG_Pos)
#define    LPTIM16_CFGR_TRIGCFG                                   LPTIM16_CFGR_TRIGCFG_Msk

#define    LPTIM16_CFGR_QEMD_Pos                                  (3U)
#define    LPTIM16_CFGR_QEMD_Msk                                  (0x3U << LPTIM16_CFGR_QEMD_Pos)
#define    LPTIM16_CFGR_QEMD                                      LPTIM16_CFGR_QEMD_Msk

#define    LPTIM16_CFGR_MMS_Pos                                   (16U)
#define    LPTIM16_CFGR_MMS_Msk                                   (0x7U << LPTIM16_CFGR_MMS_Pos)
#define    LPTIM16_CFGR_MMS                                       LPTIM16_CFGR_MMS_Msk

#define    LPTIM16_CFGR_ONST_Pos                                  (2U)
#define    LPTIM16_CFGR_ONST_Msk                                  (0x1U << LPTIM16_CFGR_ONST_Pos)
#define    LPTIM16_CFGR_ONST                                      LPTIM16_CFGR_ONST_Msk

#define    LPTIM16_CFGR_TMODE_Pos                                 (0U)
#define    LPTIM16_CFGR_TMODE_Msk                                 (0x3U << LPTIM16_CFGR_TMODE_Pos)
#define    LPTIM16_CFGR_TMODE                                     LPTIM16_CFGR_TMODE_Msk

#define    LPTIM16_IER_CCIE_Pos                                   (0U)
#define    LPTIM16_IER_CCIE_Msk                                   (0x3U << LPTIM16_IER_CCIE_Pos)
#define    LPTIM16_IER_CCIE                                       LPTIM16_IER_CCIE_Msk

#define    LPTIM16_IER_OVIE_Pos                                   (6U)
#define    LPTIM16_IER_OVIE_Msk                                   (0x1U << LPTIM16_IER_OVIE_Pos)
#define    LPTIM16_IER_OVIE                                       LPTIM16_IER_OVIE_Msk

#define    LPTIM16_IER_TRIGIE_Pos                                 (7U)
#define    LPTIM16_IER_TRIGIE_Msk                                 (0x1U << LPTIM16_IER_TRIGIE_Pos)
#define    LPTIM16_IER_TRIGIE                                     LPTIM16_IER_TRIGIE_Msk

#define    LPTIM16_IER_OVRIE_Pos                                  (8U)
#define    LPTIM16_IER_OVRIE_Msk                                  (0x3U << LPTIM16_IER_OVRIE_Pos)
#define    LPTIM16_IER_OVRIE                                      LPTIM16_IER_OVRIE_Msk

#define    LPTIM16_ISR_CCIF_Pos                                   (0U)
#define    LPTIM16_ISR_CCIF_Msk                                   (0x3U << LPTIM16_ISR_CCIF_Pos)
#define    LPTIM16_ISR_CCIF                                       LPTIM16_ISR_CCIF_Msk

#define    LPTIM16_ISR_OVIF_Pos                                   (6U)
#define    LPTIM16_ISR_OVIF_Msk                                   (0x1U << LPTIM16_ISR_OVIF_Pos)
#define    LPTIM16_ISR_OVIF                                       LPTIM16_ISR_OVIF_Msk

#define    LPTIM16_ISR_TRIGIF_Pos                                 (7U)
#define    LPTIM16_ISR_TRIGIF_Msk                                 (0x1U << LPTIM16_ISR_TRIGIF_Pos)
#define    LPTIM16_ISR_TRIGIF                                     LPTIM16_ISR_TRIGIF_Msk

#define    LPTIM16_ISR_OVRIF_Pos                                  (8U)
#define    LPTIM16_ISR_OVRIF_Msk                                  (0x3U << LPTIM16_ISR_OVRIF_Pos)
#define    LPTIM16_ISR_OVRIF                                      LPTIM16_ISR_OVRIF_Msk

#define    LPTIM16_CCSR_CAPCFG_Pos                                (8U)
#define    LPTIM16_CCSR_CAPCFG_Msk                                (0x3U << LPTIM16_CCSR_CAPCFG_Pos)
#define    LPTIM16_CCSR_CAPCFG                                    LPTIM16_CCSR_CAPCFG_Msk

#define    LPTIM16_CCSR_CCP_Pos                                   (16U)
#define    LPTIM16_CCSR_CCP_Msk                                   (0x1U << LPTIM16_CCSR_CCP_Pos)
#define    LPTIM16_CCSR_CCP                                       LPTIM16_CCSR_CCP_Msk

#define    LPTIM16_CCSR_CAP1PSC_Pos                               (26U)
#define    LPTIM16_CCSR_CAP1PSC_Msk                               (0x3fU << LPTIM16_CCSR_CAP1PSC_Pos)
#define    LPTIM16_CCSR_CAP1PSC                                   LPTIM16_CCSR_CAP1PSC_Msk

#define    LPTIM16_CCSR_CCS_Pos                                   (0U)
#define    LPTIM16_CCSR_CCS_Msk                                   (0x3U << LPTIM16_CCSR_CCS_Pos)
#define    LPTIM16_CCSR_CCS                                       LPTIM16_CCSR_CCS_Msk

#define    LPTIM16_CCSR_CAPEDGE_Pos                               (20U)
#define    LPTIM16_CCSR_CAPEDGE_Msk                               (0x1U << LPTIM16_CCSR_CAPEDGE_Pos)
#define    LPTIM16_CCSR_CAPEDGE                                   LPTIM16_CCSR_CAPEDGE_Msk

#define    LPTIM16_CCSR_CAP1SSEL_Pos                              (24U)
#define    LPTIM16_CCSR_CAP1SSEL_Msk                              (0x3U << LPTIM16_CCSR_CAP1SSEL_Pos)
#define    LPTIM16_CCSR_CAP1SSEL                                  LPTIM16_CCSR_CAP1SSEL_Msk



#define    FL_LPTIM16_CHANNEL_1                                   (0x1U << 0U)
#define    FL_LPTIM16_CHANNEL_2                                   (0x1U << 1U)



#define    FL_LPTIM16_CLK_SOURCE_INTERNAL                         (0x0U << LPTIM16_CFGR_PSCSEL_Pos)
#define    FL_LPTIM16_CLK_SOURCE_EXTERNAL                         (0x1U << LPTIM16_CFGR_PSCSEL_Pos)


#define    FL_LPTIM16_PSC_DIV1                                    (0x0U << LPTIM16_CFGR_DIVSEL_Pos)
#define    FL_LPTIM16_PSC_DIV2                                    (0x1U << LPTIM16_CFGR_DIVSEL_Pos)
#define    FL_LPTIM16_PSC_DIV4                                    (0x2U << LPTIM16_CFGR_DIVSEL_Pos)
#define    FL_LPTIM16_PSC_DIV8                                    (0x3U << LPTIM16_CFGR_DIVSEL_Pos)
#define    FL_LPTIM16_PSC_DIV16                                   (0x4U << LPTIM16_CFGR_DIVSEL_Pos)
#define    FL_LPTIM16_PSC_DIV32                                   (0x5U << LPTIM16_CFGR_DIVSEL_Pos)
#define    FL_LPTIM16_PSC_DIV64                                   (0x6U << LPTIM16_CFGR_DIVSEL_Pos)
#define    FL_LPTIM16_PSC_DIV128                                  (0x7U << LPTIM16_CFGR_DIVSEL_Pos)


#define    FL_LPTIM16_ETR_COUNT_EDGE_RISING                       (0x0U << LPTIM16_CFGR_EDGESEL_Pos)
#define    FL_LPTIM16_ETR_COUNT_EDGE_FALLING                      (0x1U << LPTIM16_CFGR_EDGESEL_Pos)


#define    FL_LPTIM16_ETR_TRIGGER_EDGE_RISING                     (0x0U << LPTIM16_CFGR_TRIGCFG_Pos)
#define    FL_LPTIM16_ETR_TRIGGER_EDGE_FALLING                    (0x1U << LPTIM16_CFGR_TRIGCFG_Pos)
#define    FL_LPTIM16_ETR_TRIGGER_EDGE_BOTH                       (0x2U << LPTIM16_CFGR_TRIGCFG_Pos)


#define    FL_LPTIM16_ENCODER_MODE_DISABLE                        (0x0U << LPTIM16_CFGR_QEMD_Pos)
#define    FL_LPTIM16_ENCODER_MODE_TI1FP1_TI2FP2_CNT              (0x1U << LPTIM16_CFGR_QEMD_Pos)
#define    FL_LPTIM16_ENCODER_MODE_TI2FP2_TI1FP1_CNT              (0x2U << LPTIM16_CFGR_QEMD_Pos)
#define    FL_LPTIM16_ENCODER_MODE_TI2FP2_CNT_TI1FP1_CNT          (0x3U << LPTIM16_CFGR_QEMD_Pos)


#define    FL_LPTIM16_TRGO_ENABLE                                 (0x1U << LPTIM16_CFGR_MMS_Pos)
#define    FL_LPTIM16_TRGO_UPDATE                                 (0x2U << LPTIM16_CFGR_MMS_Pos)
#define    FL_LPTIM16_TRGO_OC1REF                                 (0x3U << LPTIM16_CFGR_MMS_Pos)
#define    FL_LPTIM16_TRGO_IC1                                    (0x4U << LPTIM16_CFGR_MMS_Pos)
#define    FL_LPTIM16_TRGO_IC2                                    (0x5U << LPTIM16_CFGR_MMS_Pos)


#define    FL_LPTIM16_ONE_PULSE_MODE_CONTINUOUS                   (0x0U << LPTIM16_CFGR_ONST_Pos)
#define    FL_LPTIM16_ONE_PULSE_MODE_SINGLE                       (0x1U << LPTIM16_CFGR_ONST_Pos)


#define    FL_LPTIM16_OPERATION_MODE_NORMAL                       (0x0U << LPTIM16_CFGR_TMODE_Pos)
#define    FL_LPTIM16_OPERATION_MODE_EXTERNAL_TRIGGER_CNT         (0x1U << LPTIM16_CFGR_TMODE_Pos)
#define    FL_LPTIM16_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT     (0x2U << LPTIM16_CFGR_TMODE_Pos)
#define    FL_LPTIM16_OPERATION_MODE_TIMEOUT                      (0x3U << LPTIM16_CFGR_TMODE_Pos)


#define    FL_LPTIM16_IC_EDGE_RISING                              (0x0U << LPTIM16_CCSR_CAPCFG_Pos)
#define    FL_LPTIM16_IC_EDGE_FALLING                             (0x1U << LPTIM16_CCSR_CAPCFG_Pos)
#define    FL_LPTIM16_IC_EDGE_BOTH                                (0x2U << LPTIM16_CCSR_CAPCFG_Pos)


#define    FL_LPTIM16_OC_POLARITY_NORMAL                          (0x0U << LPTIM16_CCSR_CCP_Pos)
#define    FL_LPTIM16_OC_POLARITY_INVERT                          (0x1U << LPTIM16_CCSR_CCP_Pos)


#define    FL_LPTIM16_IC_POLARITY_NORMAL                          (0x0U << LPTIM16_CCSR_CCP_Pos)
#define    FL_LPTIM16_IC_POLARITY_INVERT                          (0x1U << LPTIM16_CCSR_CCP_Pos)


#define    FL_LPTIM16_CHANNEL_MODE_DISABLE                        (0x0U << LPTIM16_CCSR_CCS_Pos)
#define    FL_LPTIM16_CHANNEL_MODE_INPUT                          (0x1U << LPTIM16_CCSR_CCS_Pos)
#define    FL_LPTIM16_CHANNEL_MODE_OUTPUT                         (0x2U << LPTIM16_CCSR_CCS_Pos)


#define    FL_LPTIM16_IC_CAPCTURED_EDGE_RISING                    (0x0U << LPTIM16_CCSR_CAPEDGE_Pos)
#define    FL_LPTIM16_IC_CAPCTURED_EDGE_FALLING                   (0x1U << LPTIM16_CCSR_CAPEDGE_Pos)

#define    FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP0                   (0x0U << LPTIM16_CCSR_CAP1SSEL_Pos)
#define    FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP1                   (0x1U << LPTIM16_CCSR_CAP1SSEL_Pos)
#define    FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP2                   (0x2U << LPTIM16_CCSR_CAP1SSEL_Pos)
#define    FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP3                   (0x3U << LPTIM16_CCSR_CAP1SSEL_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup LPTIM16_FL_Exported_Functions LPTIM16 Exported Functions
  * @{
  */

/**
  * @brief    Enable LPTIM16
  * @rmtoll   CR    EN    FL_LPTIM16_Enable
  * @param    LPTIM16x LPTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_Enable(LPTIM16_Type *LPTIM16x)
{
    SET_BIT(LPTIM16x->CR, LPTIM16_CR_EN_Msk);
}

/**
  * @brief    Disable LPTIM16
  * @rmtoll   CR    EN    FL_LPTIM16_Disable
  * @param    LPTIM16x LPTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_Disable(LPTIM16_Type *LPTIM16x)
{
    CLEAR_BIT(LPTIM16x->CR, LPTIM16_CR_EN_Msk);
}

/**
  * @brief    Get LPTIM16 Enable Status
  * @rmtoll   CR    EN    FL_LPTIM16_IsEnabled
  * @param    LPTIM16x LPTIM16 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IsEnabled(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CR, LPTIM16_CR_EN_Msk) == LPTIM16_CR_EN_Msk);
}

/**
  * @brief    Enable External Input Analog Filter
  * @rmtoll   CFGR    ETR_AFEN    FL_LPTIM16_EnableETRFilter
  * @param    LPTIM16x LPTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_EnableETRFilter(LPTIM16_Type *LPTIM16x)
{
    SET_BIT(LPTIM16x->CFGR, LPTIM16_CFGR_ETR_AFEN_Msk);
}

/**
  * @brief    Disable External Input Analog Filter
  * @rmtoll   CFGR    ETR_AFEN    FL_LPTIM16_DisableETRFilter
  * @param    LPTIM16x LPTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_DisableETRFilter(LPTIM16_Type *LPTIM16x)
{
    CLEAR_BIT(LPTIM16x->CFGR, LPTIM16_CFGR_ETR_AFEN_Msk);
}

/**
  * @brief    Get External Input Analog Filter Enable Status
  * @rmtoll   CFGR    ETR_AFEN    FL_LPTIM16_IsEnabledETRFilter
  * @param    LPTIM16x LPTIM16 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IsEnabledETRFilter(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CFGR, LPTIM16_CFGR_ETR_AFEN_Msk) == LPTIM16_CFGR_ETR_AFEN_Msk);
}

/**
  * @brief    Set Prescaler Input
  * @rmtoll   CFGR    PSCSEL    FL_LPTIM16_SetClockSource
  * @param    LPTIM16x LPTIM16 instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CLK_SOURCE_INTERNAL
  *           @arg @ref FL_LPTIM16_CLK_SOURCE_EXTERNAL
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_SetClockSource(LPTIM16_Type *LPTIM16x, uint32_t source)
{
    MODIFY_REG(LPTIM16x->CFGR, LPTIM16_CFGR_PSCSEL_Msk, source);
}

/**
  * @brief    Get Prescaler Input Setting
  * @rmtoll   CFGR    PSCSEL    FL_LPTIM16_GetClockSource
  * @param    LPTIM16x LPTIM16 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_CLK_SOURCE_INTERNAL
  *           @arg @ref FL_LPTIM16_CLK_SOURCE_EXTERNAL
  */
__STATIC_INLINE uint32_t FL_LPTIM16_GetClockSource(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CFGR, LPTIM16_CFGR_PSCSEL_Msk));
}

/**
  * @brief    Set Counter Clock Division
  * @rmtoll   CFGR    DIVSEL    FL_LPTIM16_SetPrescaler
  * @param    LPTIM16x LPTIM16 instance
  * @param    psc This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_PSC_DIV1
  *           @arg @ref FL_LPTIM16_PSC_DIV2
  *           @arg @ref FL_LPTIM16_PSC_DIV4
  *           @arg @ref FL_LPTIM16_PSC_DIV8
  *           @arg @ref FL_LPTIM16_PSC_DIV16
  *           @arg @ref FL_LPTIM16_PSC_DIV32
  *           @arg @ref FL_LPTIM16_PSC_DIV64
  *           @arg @ref FL_LPTIM16_PSC_DIV128
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_SetPrescaler(LPTIM16_Type *LPTIM16x, uint32_t psc)
{
    MODIFY_REG(LPTIM16x->CFGR, LPTIM16_CFGR_DIVSEL_Msk, psc);
}

/**
  * @brief    Get Counter Clock Division Setting
  * @rmtoll   CFGR    DIVSEL    FL_LPTIM16_GetPrescaler
  * @param    LPTIM16x LPTIM16 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_PSC_DIV1
  *           @arg @ref FL_LPTIM16_PSC_DIV2
  *           @arg @ref FL_LPTIM16_PSC_DIV4
  *           @arg @ref FL_LPTIM16_PSC_DIV8
  *           @arg @ref FL_LPTIM16_PSC_DIV16
  *           @arg @ref FL_LPTIM16_PSC_DIV32
  *           @arg @ref FL_LPTIM16_PSC_DIV64
  *           @arg @ref FL_LPTIM16_PSC_DIV128
  */
__STATIC_INLINE uint32_t FL_LPTIM16_GetPrescaler(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CFGR, LPTIM16_CFGR_DIVSEL_Msk));
}

/**
  * @brief    Set ETR Count Edge
  * @rmtoll   CFGR    EDGESEL    FL_LPTIM16_SetETRCountEdge
  * @param    LPTIM16x LPTIM16 instance
  * @param    edge This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_ETR_COUNT_EDGE_RISING
  *           @arg @ref FL_LPTIM16_ETR_COUNT_EDGE_FALLING
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_SetETRCountEdge(LPTIM16_Type *LPTIM16x, uint32_t edge)
{
    MODIFY_REG(LPTIM16x->CFGR, LPTIM16_CFGR_EDGESEL_Msk, edge);
}

/**
  * @brief    Get ETR Count Edge Setting
  * @rmtoll   CFGR    EDGESEL    FL_LPTIM16_GetETRCountEdge
  * @param    LPTIM16x LPTIM16 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_ETR_COUNT_EDGE_RISING
  *           @arg @ref FL_LPTIM16_ETR_COUNT_EDGE_FALLING
  */
__STATIC_INLINE uint32_t FL_LPTIM16_GetETRCountEdge(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CFGR, LPTIM16_CFGR_EDGESEL_Msk));
}

/**
  * @brief    Set ETR Trigger Edge
  * @rmtoll   CFGR    TRIGCFG    FL_LPTIM16_SetETRTriggerEdge
  * @param    LPTIM16x LPTIM16 instance
  * @param    edge This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_ETR_TRIGGER_EDGE_RISING
  *           @arg @ref FL_LPTIM16_ETR_TRIGGER_EDGE_FALLING
  *           @arg @ref FL_LPTIM16_ETR_TRIGGER_EDGE_BOTH
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_SetETRTriggerEdge(LPTIM16_Type *LPTIM16x, uint32_t edge)
{
    MODIFY_REG(LPTIM16x->CFGR, LPTIM16_CFGR_TRIGCFG_Msk, edge);
}

/**
  * @brief    Get ETR Trigger Edge Setting
  * @rmtoll   CFGR    TRIGCFG    FL_LPTIM16_GetETRTriggerEdge
  * @param    LPTIM16x LPTIM16 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_ETR_TRIGGER_EDGE_RISING
  *           @arg @ref FL_LPTIM16_ETR_TRIGGER_EDGE_FALLING
  *           @arg @ref FL_LPTIM16_ETR_TRIGGER_EDGE_BOTH
  */
__STATIC_INLINE uint32_t FL_LPTIM16_GetETRTriggerEdge(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CFGR, LPTIM16_CFGR_TRIGCFG_Msk));
}

/**
  * @brief    Set Quad Encoder Mode
  * @rmtoll   CFGR    QEMD    FL_LPTIM16_SetEncoderMode
  * @param    LPTIM16x LPTIM16 instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_ENCODER_MODE_DISABLE
  *           @arg @ref FL_LPTIM16_ENCODER_MODE_TI1FP1_TI2FP2_CNT
  *           @arg @ref FL_LPTIM16_ENCODER_MODE_TI2FP2_TI1FP1_CNT
  *           @arg @ref FL_LPTIM16_ENCODER_MODE_TI2FP2_CNT_TI1FP1_CNT
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_SetEncoderMode(LPTIM16_Type *LPTIM16x, uint32_t mode)
{
    MODIFY_REG(LPTIM16x->CFGR, LPTIM16_CFGR_QEMD_Msk, mode);
}

/**
  * @brief    Get Quad Encoder Mode Setting
  * @rmtoll   CFGR    QEMD    FL_LPTIM16_GetEncoderMode
  * @param    LPTIM16x LPTIM16 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_ENCODER_MODE_DISABLE
  *           @arg @ref FL_LPTIM16_ENCODER_MODE_TI1FP1_TI2FP2_CNT
  *           @arg @ref FL_LPTIM16_ENCODER_MODE_TI2FP2_TI1FP1_CNT
  *           @arg @ref FL_LPTIM16_ENCODER_MODE_TI2FP2_CNT_TI1FP1_CNT
  */
__STATIC_INLINE uint32_t FL_LPTIM16_GetEncoderMode(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CFGR, LPTIM16_CFGR_QEMD_Msk));
}

/**
  * @brief    Set Sync Trigger Signal Output Source
  * @rmtoll   CFGR    MMS    FL_LPTIM16_SetTriggerOutput
  * @param    LPTIM16x LPTIM16 instance
  * @param    triggerOutput This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_TRGO_ENABLE
  *           @arg @ref FL_LPTIM16_TRGO_UPDATE
  *           @arg @ref FL_LPTIM16_TRGO_OC1REF
  *           @arg @ref FL_LPTIM16_TRGO_IC1
  *           @arg @ref FL_LPTIM16_TRGO_IC2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_SetTriggerOutput(LPTIM16_Type *LPTIM16x, uint32_t triggerOutput)
{
    MODIFY_REG(LPTIM16x->CFGR, LPTIM16_CFGR_MMS_Msk, triggerOutput);
}

/**
  * @brief    Get Sync Trigger Signal Output Source Setting
  * @rmtoll   CFGR    MMS    FL_LPTIM16_GetTriggerOutput
  * @param    LPTIM16x LPTIM16 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_TRGO_ENABLE
  *           @arg @ref FL_LPTIM16_TRGO_UPDATE
  *           @arg @ref FL_LPTIM16_TRGO_OC1REF
  *           @arg @ref FL_LPTIM16_TRGO_IC1
  *           @arg @ref FL_LPTIM16_TRGO_IC2
  */
__STATIC_INLINE uint32_t FL_LPTIM16_GetTriggerOutput(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CFGR, LPTIM16_CFGR_MMS_Msk));
}

/**
  * @brief    Set One Pulse Mode
  * @rmtoll   CFGR    ONST    FL_LPTIM16_SetOnePulseMode
  * @param    LPTIM16x LPTIM16 instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_ONE_PULSE_MODE_CONTINUOUS
  *           @arg @ref FL_LPTIM16_ONE_PULSE_MODE_SINGLE
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_SetOnePulseMode(LPTIM16_Type *LPTIM16x, uint32_t mode)
{
    MODIFY_REG(LPTIM16x->CFGR, LPTIM16_CFGR_ONST_Msk, mode);
}

/**
  * @brief    Get One Pulse Mode Setting
  * @rmtoll   CFGR    ONST    FL_LPTIM16_GetOnePulseMode
  * @param    LPTIM16x LPTIM16 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_ONE_PULSE_MODE_CONTINUOUS
  *           @arg @ref FL_LPTIM16_ONE_PULSE_MODE_SINGLE
  */
__STATIC_INLINE uint32_t FL_LPTIM16_GetOnePulseMode(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CFGR, LPTIM16_CFGR_ONST_Msk));
}

/**
  * @brief    Set Operation Mode
  * @rmtoll   CFGR    TMODE    FL_LPTIM16_SetOperationMode
  * @param    LPTIM16x LPTIM16 instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_OPERATION_MODE_NORMAL
  *           @arg @ref FL_LPTIM16_OPERATION_MODE_EXTERNAL_TRIGGER_CNT
  *           @arg @ref FL_LPTIM16_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT
  *           @arg @ref FL_LPTIM16_OPERATION_MODE_TIMEOUT
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_SetOperationMode(LPTIM16_Type *LPTIM16x, uint32_t mode)
{
    MODIFY_REG(LPTIM16x->CFGR, LPTIM16_CFGR_TMODE_Msk, mode);
}

/**
  * @brief    Get Operation Mode Setting
  * @rmtoll   CFGR    TMODE    FL_LPTIM16_GetOperationMode
  * @param    LPTIM16x LPTIM16 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_OPERATION_MODE_NORMAL
  *           @arg @ref FL_LPTIM16_OPERATION_MODE_EXTERNAL_TRIGGER_CNT
  *           @arg @ref FL_LPTIM16_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT
  *           @arg @ref FL_LPTIM16_OPERATION_MODE_TIMEOUT
  */
__STATIC_INLINE uint32_t FL_LPTIM16_GetOperationMode(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CFGR, LPTIM16_CFGR_TMODE_Msk));
}

/**
  * @brief    Set Channel 1 Output Compare Value
  * @rmtoll   CCR1        FL_LPTIM16_WriteCompareCH1
  * @param    LPTIM16x LPTIM16 instance
  * @param    compareValue
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_WriteCompareCH1(LPTIM16_Type *LPTIM16x, uint32_t compareValue)
{
    MODIFY_REG(LPTIM16x->CCR1, (0xffffU << 0U), (compareValue << 0U));
}

/**
  * @brief    Get Channel 1 Output Compare Value
  * @rmtoll   CCR1        FL_LPTIM16_ReadCompareCH1
  * @param    LPTIM16x LPTIM16 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM16_ReadCompareCH1(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CCR1, (0xffffU << 0U)) >> 0U);
}

/**
  * @brief    Set Channel 2 Output Compare Value
  * @rmtoll   CCR2        FL_LPTIM16_WriteCompareCH2
  * @param    LPTIM16x LPTIM16 instance
  * @param    compareValue
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_WriteCompareCH2(LPTIM16_Type *LPTIM16x, uint32_t compareValue)
{
    MODIFY_REG(LPTIM16x->CCR2, (0xffffU << 0U), (compareValue << 0U));
}

/**
  * @brief    Get Channel 2 Output Compare Value
  * @rmtoll   CCR2        FL_LPTIM16_ReadCompareCH2
  * @param    LPTIM16x LPTIM16 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM16_ReadCompareCH2(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CCR2, (0xffffU << 0U)) >> 0U);
}

/**
  * @brief    Get Channel 1 Input Capture Value
  * @rmtoll   CCR1        FL_LPTIM16_ReadCaptureCH1
  * @param    LPTIM16x LPTIM16 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM16_ReadCaptureCH1(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CCR1, (0xffffU << 0U)) >> 0U);
}

/**
  * @brief    Get Channel 2 Input Capture Value
  * @rmtoll   CCR2        FL_LPTIM16_ReadCaptureCH2
  * @param    LPTIM16x LPTIM16 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM16_ReadCaptureCH2(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CCR2, (0xffffU << 0U)) >> 0U);
}

/**
  * @brief    Enable Channel Capture/Compare Interrupt
  * @rmtoll   IER    CCIE    FL_LPTIM16_EnableIT_CC
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_EnableIT_CC(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    SET_BIT(LPTIM16x->IER, ((channel & 0x3) << 0x0U));
}

/**
  * @brief    Enable Update Event Interrupt
  * @rmtoll   IER    OVIE    FL_LPTIM16_EnableIT_Update
  * @param    LPTIM16x LPTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_EnableIT_Update(LPTIM16_Type *LPTIM16x)
{
    SET_BIT(LPTIM16x->IER, LPTIM16_IER_OVIE_Msk);
}

/**
  * @brief    Enable External Trigger Interrupt
  * @rmtoll   IER    TRIGIE    FL_LPTIM16_EnableIT_Trigger
  * @param    LPTIM16x LPTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_EnableIT_Trigger(LPTIM16_Type *LPTIM16x)
{
    SET_BIT(LPTIM16x->IER, LPTIM16_IER_TRIGIE_Msk);
}

/**
  * @brief    Enable Channel Capture Overflow Interrupt
  * @rmtoll   IER    OVRIE    FL_LPTIM16_EnableIT_CCOverflow
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_EnableIT_CCOverflow(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    SET_BIT(LPTIM16x->IER, ((channel & 0x3) << 0x8U));
}

/**
  * @brief    Disable Channel Capture/Compare Interrupt
  * @rmtoll   IER    CCIE    FL_LPTIM16_DisableIT_CC
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_DisableIT_CC(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    CLEAR_BIT(LPTIM16x->IER, ((channel & 0x3) << 0x0U));
}

/**
  * @brief    Disable Update Event Interrupt
  * @rmtoll   IER    OVIE    FL_LPTIM16_DisableIT_Update
  * @param    LPTIM16x LPTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_DisableIT_Update(LPTIM16_Type *LPTIM16x)
{
    CLEAR_BIT(LPTIM16x->IER, LPTIM16_IER_OVIE_Msk);
}

/**
  * @brief    Disable External Trigger Interrupt
  * @rmtoll   IER    TRIGIE    FL_LPTIM16_DisableIT_Trigger
  * @param    LPTIM16x LPTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_DisableIT_Trigger(LPTIM16_Type *LPTIM16x)
{
    CLEAR_BIT(LPTIM16x->IER, LPTIM16_IER_TRIGIE_Msk);
}

/**
  * @brief    Disable Channel Capture Overflow Interrupt
  * @rmtoll   IER    OVRIE    FL_LPTIM16_DisableIT_CCOverflow
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_DisableIT_CCOverflow(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    CLEAR_BIT(LPTIM16x->IER, ((channel & 0x3) << 0x8U));
}

/**
  * @brief    Get Channel Capture/Compare Interrupt Enable Status
  * @rmtoll   IER    CCIE    FL_LPTIM16_IsEnabledIT_CC
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IsEnabledIT_CC(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    return (uint32_t)(READ_BIT(LPTIM16x->IER, ((channel & 0x3) << 0x0U)) == ((channel & 0x3) << 0x0U));
}

/**
  * @brief    Get Counter Update Event Interrupt Enable Status
  * @rmtoll   IER    OVIE    FL_LPTIM16_IsEnabledIT_Update
  * @param    LPTIM16x LPTIM16 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IsEnabledIT_Update(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->IER, LPTIM16_IER_OVIE_Msk) == LPTIM16_IER_OVIE_Msk);
}

/**
  * @brief    Get External Trigger Interrupt Enable Status
  * @rmtoll   IER    TRIGIE    FL_LPTIM16_IsEnabledIT_Trigger
  * @param    LPTIM16x LPTIM16 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IsEnabledIT_Trigger(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->IER, LPTIM16_IER_TRIGIE_Msk) == LPTIM16_IER_TRIGIE_Msk);
}

/**
  * @brief    Get Channel Capture Overflow Interrupt Enable Status
  * @rmtoll   IER    OVRIE    FL_LPTIM16_IsEnabledIT_CCOverflow
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IsEnabledIT_CCOverflow(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    return (uint32_t)(READ_BIT(LPTIM16x->IER, ((channel & 0x3) << 0x8U)) == ((channel & 0x3) << 0x8U));
}

/**
  * @brief    Get Capture/Compare Channel Interrupt Flag
  * @rmtoll   ISR    CCIF    FL_LPTIM16_IsActiveFlag_CC
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IsActiveFlag_CC(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    return (uint32_t)(READ_BIT(LPTIM16x->ISR, ((channel & 0x3) << 0x0U)) == ((channel & 0x3) << 0x0U));
}

/**
  * @brief    Get Update Event Interrupt Flag
  * @rmtoll   ISR    OVIF    FL_LPTIM16_IsActiveFlag_Update
  * @param    LPTIM16x LPTIM16 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IsActiveFlag_Update(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->ISR, LPTIM16_ISR_OVIF_Msk) == (LPTIM16_ISR_OVIF_Msk));
}

/**
  * @brief    Get External Trigger Interrupt Flag
  * @rmtoll   ISR    TRIGIF    FL_LPTIM16_IsActiveFlag_Trigger
  * @param    LPTIM16x LPTIM16 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IsActiveFlag_Trigger(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->ISR, LPTIM16_ISR_TRIGIF_Msk) == (LPTIM16_ISR_TRIGIF_Msk));
}

/**
  * @brief    Get Channel Capture Overflow Interrupt Flag
  * @rmtoll   ISR    OVRIF    FL_LPTIM16_IsActiveFlag_CCOverflow
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IsActiveFlag_CCOverflow(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    return (uint32_t)(READ_BIT(LPTIM16x->ISR, ((channel & 0x3) << 0x8U)) == ((channel & 0x3) << 0x8U));
}

/**
  * @brief    Clear Capture/Compare Channel Interrupt Flag
  * @rmtoll   ISR    CCIF    FL_LPTIM16_ClearFlag_CC
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_ClearFlag_CC(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    WRITE_REG(LPTIM16x->ISR, ((channel & 0x3) << 0x0U));
}

/**
  * @brief    Clear Update Event Interrupt Flag
  * @rmtoll   ISR    OVIF    FL_LPTIM16_ClearFlag_Update
  * @param    LPTIM16x LPTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_ClearFlag_Update(LPTIM16_Type *LPTIM16x)
{
    WRITE_REG(LPTIM16x->ISR, LPTIM16_ISR_OVIF_Msk);
}

/**
  * @brief    Clear External Trigger Interrupt Flag
  * @rmtoll   ISR    TRIGIF    FL_LPTIM16_ClearFlag_Trigger
  * @param    LPTIM16x LPTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_ClearFlag_Trigger(LPTIM16_Type *LPTIM16x)
{
    WRITE_REG(LPTIM16x->ISR, LPTIM16_ISR_TRIGIF_Msk);
}

/**
  * @brief    Clear Channel Capture Overflow Interrupt Flag
  * @rmtoll   ISR    OVRIF    FL_LPTIM16_ClearFlag_CCOverflow
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_ClearFlag_CCOverflow(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    WRITE_REG(LPTIM16x->ISR, ((channel & 0x3) << 0x8U));
}

/**
  * @brief    Set Auto Reload Value
  * @rmtoll   ARR        FL_LPTIM16_WriteAutoReload
  * @param    LPTIM16x LPTIM16 instance
  * @param    autoReload
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_WriteAutoReload(LPTIM16_Type *LPTIM16x, uint32_t autoReload)
{
    MODIFY_REG(LPTIM16x->ARR, (0xffffU << 0U), (autoReload << 0U));
}

/**
  * @brief    Get Auto Reload Value
  * @rmtoll   ARR        FL_LPTIM16_ReadAutoReload
  * @param    LPTIM16x LPTIM16 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM16_ReadAutoReload(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->ARR, (0xffffU << 0U)) >> 0U);
}

/**
  * @brief    Set Input Capture Channel Capture Edge
  * @rmtoll   CCSR    CAPCFG    FL_LPTIM16_IC_SetCaptureEdge
  * @param    LPTIM16x LPTIM16 instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_IC_EDGE_RISING
  *           @arg @ref FL_LPTIM16_IC_EDGE_FALLING
  *           @arg @ref FL_LPTIM16_IC_EDGE_BOTH
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_IC_SetCaptureEdge(LPTIM16_Type *LPTIM16x, uint32_t polarity, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM16_CHANNEL_1:
            MODIFY_REG(LPTIM16x->CCSR, (0x3U << 8U), (polarity << 0U));
            break;
        case FL_LPTIM16_CHANNEL_2:
            MODIFY_REG(LPTIM16x->CCSR, (0x3U << 10U), (polarity << 2U));
            break;
    }
}

/**
  * @brief    Get Input Capture Channel Capture Edge
  * @rmtoll   CCSR    CAPCFG    FL_LPTIM16_IC_GetCaptureEdge
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_IC_EDGE_RISING
  *           @arg @ref FL_LPTIM16_IC_EDGE_FALLING
  *           @arg @ref FL_LPTIM16_IC_EDGE_BOTH
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IC_GetCaptureEdge(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM16_CHANNEL_1:
            return (uint32_t)(READ_BIT(LPTIM16x->CCSR, (0x3U << 8U)) >> 0U);
        case FL_LPTIM16_CHANNEL_2:
            return (uint32_t)(READ_BIT(LPTIM16x->CCSR, (0x3U << 10U)) >> 2U);
        default:
            return 0;
    }
}

/**
  * @brief    Set Channel Output Compare Polarity
  * @rmtoll   CCSR    CCP    FL_LPTIM16_OC_SetPolarity
  * @param    LPTIM16x LPTIM16 instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_OC_POLARITY_NORMAL
  *           @arg @ref FL_LPTIM16_OC_POLARITY_INVERT
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_OC_SetPolarity(LPTIM16_Type *LPTIM16x, uint32_t polarity, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM16_CHANNEL_1:
            MODIFY_REG(LPTIM16x->CCSR, (0x1U << 16U), (polarity << 0U));
            break;
        case FL_LPTIM16_CHANNEL_2:
            MODIFY_REG(LPTIM16x->CCSR, (0x1U << 17U), (polarity << 1U));
            break;
    }
}

/**
  * @brief    Get Channel Output Compare Polarity
  * @rmtoll   CCSR    CCP    FL_LPTIM16_OC_GetPolarity
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_OC_POLARITY_NORMAL
  *           @arg @ref FL_LPTIM16_OC_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_LPTIM16_OC_GetPolarity(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM16_CHANNEL_1:
            return (uint32_t)(READ_BIT(LPTIM16x->CCSR, (0x1U << 16U)) >> 0U);
        case FL_LPTIM16_CHANNEL_2:
            return (uint32_t)(READ_BIT(LPTIM16x->CCSR, (0x1U << 17U)) >> 1U);
        default:
            return 0;
    }
}

/**
  * @brief    Set Input Capture Channel Input Polarity
  * @rmtoll   CCSR    CCP    FL_LPTIM16_IC_SetInputPolarity
  * @param    LPTIM16x LPTIM16 instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_IC_POLARITY_NORMAL
  *           @arg @ref FL_LPTIM16_IC_POLARITY_INVERT
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_IC_SetInputPolarity(LPTIM16_Type *LPTIM16x, uint32_t polarity, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM16_CHANNEL_1:
            MODIFY_REG(LPTIM16x->CCSR, (0x1U << 16U), (polarity << 0U));
            break;
        case FL_LPTIM16_CHANNEL_2:
            MODIFY_REG(LPTIM16x->CCSR, (0x1U << 17U), (polarity << 1U));
            break;
    }
}

/**
  * @brief    Get Input Capture Channel Input Polarity
  * @rmtoll   CCSR    CCP    FL_LPTIM16_IC_GetInputPolarity
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_IC_POLARITY_NORMAL
  *           @arg @ref FL_LPTIM16_IC_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IC_GetInputPolarity(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM16_CHANNEL_1:
            return (uint32_t)(READ_BIT(LPTIM16x->CCSR, (0x1U << 16U)) >> 0U);
        case FL_LPTIM16_CHANNEL_2:
            return (uint32_t)(READ_BIT(LPTIM16x->CCSR, (0x1U << 17U)) >> 1U);
        default:
            return 0;
    }
}

/**
  * @brief    Enable Channel Input Digital Filter
  * @rmtoll   CCSR        FL_LPTIM16_EnableDigitalFilter
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_EnableDigitalFilter(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    SET_BIT(LPTIM16x->CCSR, ((channel & 0x3) << 0xcU));
}

/**
  * @brief    Disable Channel Input Digital Filter
  * @rmtoll   CCSR        FL_LPTIM16_DisableDigitalFilter
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_DisableDigitalFilter(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    CLEAR_BIT(LPTIM16x->CCSR, ((channel & 0x3) << 0xcU));
}

/**
  * @brief    Get Channel Input Digital Filter Enable Status
  * @rmtoll   CCSR        FL_LPTIM16_IsEnabledDigitalFilter
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IsEnabledDigitalFilter(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CCSR, ((channel & 0x3) << 0xcU)) == ((channel & 0x3) << 0xcU));
}

/**
  * @brief    Set Channel 1 Input Prescaler
  * @rmtoll   CCSR    CAP1PSC    FL_LPTIM16_IC_WriteChannel1Prescaler
  * @param    LPTIM16x LPTIM16 instance
  * @param    psc
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_IC_WriteChannel1Prescaler(LPTIM16_Type *LPTIM16x, uint32_t psc)
{
    MODIFY_REG(LPTIM16x->CCSR, (0x3fU << 26U), (psc << 26U));
}

/**
  * @brief    Get Channel 1 Input Prescaler Setting
  * @rmtoll   CCSR    CAP1PSC    FL_LPTIM16_IC_ReadChannel1Prescaler
  * @param    LPTIM16x LPTIM16 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IC_ReadChannel1Prescaler(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CCSR, (0x3fU << 26U)) >> 26U);
}

/**
  * @brief    Set Channel Operation Mode
  * @rmtoll   CCSR    CCS    FL_LPTIM16_SetChannelMode
  * @param    LPTIM16x LPTIM16 instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_MODE_DISABLE
  *           @arg @ref FL_LPTIM16_CHANNEL_MODE_INPUT
  *           @arg @ref FL_LPTIM16_CHANNEL_MODE_OUTPUT
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_SetChannelMode(LPTIM16_Type *LPTIM16x, uint32_t mode, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM16_CHANNEL_1:
            MODIFY_REG(LPTIM16x->CCSR, (0x3U << 0U), (mode << 0U));
            break;
        case FL_LPTIM16_CHANNEL_2:
            MODIFY_REG(LPTIM16x->CCSR, (0x3U << 2U), (mode << 2U));
            break;
    }
}

/**
  * @brief    Get Channel Operation Mode
  * @rmtoll   CCSR    CCS    FL_LPTIM16_GetChannelMode
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_MODE_DISABLE
  *           @arg @ref FL_LPTIM16_CHANNEL_MODE_INPUT
  *           @arg @ref FL_LPTIM16_CHANNEL_MODE_OUTPUT
  */
__STATIC_INLINE uint32_t FL_LPTIM16_GetChannelMode(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM16_CHANNEL_1:
            return (uint32_t)(READ_BIT(LPTIM16x->CCSR, (0x3U << 0U)) >> 0U);
        case FL_LPTIM16_CHANNEL_2:
            return (uint32_t)(READ_BIT(LPTIM16x->CCSR, (0x3U << 2U)) >> 2U);
        default:
            return 0;
    }
}

/**
  * @brief    Get Channel Captured Edge
  * @rmtoll   CCSR    CAPEDGE    FL_LPTIM16_IC_GetCapturedEdge
  * @param    LPTIM16x LPTIM16 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_CHANNEL_1
  *           @arg @ref FL_LPTIM16_CHANNEL_2
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_IC_CAPCTURED_EDGE_RISING
  *           @arg @ref FL_LPTIM16_IC_CAPCTURED_EDGE_FALLING
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IC_GetCapturedEdge(LPTIM16_Type *LPTIM16x, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM16_CHANNEL_1:
            return (uint32_t)(READ_BIT(LPTIM16x->CCSR, (0x1U << 20U)) >> 0U);
        case FL_LPTIM16_CHANNEL_2:
            return (uint32_t)(READ_BIT(LPTIM16x->CCSR, (0x1U << 21U)) >> 1U);
        default:
            return 0;
    }
}

/**
  * @brief    Set Channel 1 Capture Source
  * @rmtoll   CCSR    CAP1SSEL    FL_LPTIM16_IC_SetChannel1CaptureSource
  * @param    LPTIM16x LPTIM16 instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP0
  *           @arg @ref FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP1
  *           @arg @ref FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP2
  *           @arg @ref FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP3
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM16_IC_SetChannel1CaptureSource(LPTIM16_Type *LPTIM16x, uint32_t source)
{
    MODIFY_REG(LPTIM16x->CCSR, LPTIM16_CCSR_CAP1SSEL_Msk, source);
}

/**
  * @brief    Get Channel 1 Capture Source Setting
  * @rmtoll   CCSR    CAP1SSEL    FL_LPTIM16_IC_GetChannel1CaptureSource
  * @param    LPTIM16x LPTIM16 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP0
  *           @arg @ref FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP1
  *           @arg @ref FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP2
  *           @arg @ref FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP3
  */
__STATIC_INLINE uint32_t FL_LPTIM16_IC_GetChannel1CaptureSource(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CCSR, LPTIM16_CCSR_CAP1SSEL_Msk));
}

/**
  * @brief    Read LPTIM16 Counter Value
  * @rmtoll   CNT        FL_LPTIM16_ReadCounter
  * @param    LPTIM16x LPTIM16 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM16_ReadCounter(LPTIM16_Type *LPTIM16x)
{
    return (uint32_t)(READ_BIT(LPTIM16x->CNT, (0xffffU << 0U)) >> 0U);
}

/**
  * @}
  */

/** @defgroup LPTIM16_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_LPTIM16_DeInit(LPTIM16_Type *LPTIM16x);
FL_ErrorStatus FL_LPTIM16_Init(LPTIM16_Type *LPTIM16x, FL_LPTIM16_InitTypeDef *init);
void FL_LPTIM16_StructInit(FL_LPTIM16_InitTypeDef *init);
FL_ErrorStatus FL_LPTIM16_IC_Init(LPTIM16_Type *LPTIM16x, uint32_t channel, FL_LPTIM16_IC_InitTypeDef *ic_init);
void FL_LPTIM16_IC_StructInit(FL_LPTIM16_IC_InitTypeDef *ic_init);
FL_ErrorStatus FL_LPTIM16_OC_Init(LPTIM16_Type *LPTIM16x, uint32_t channel, FL_LPTIM16_OC_InitTypeDef *oc_init);
void FL_LPTIM16_OC_StructInit(FL_LPTIM16_OC_InitTypeDef *oc_init);

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

#endif /* __FM33LG0XX_FL_LPTIM16_H*/

/*************************Py_Code_Generator Version: 0.1-0.14-0.1 @ 2020-12-14*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
