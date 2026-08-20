/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_lptim32.h
  * @author  FMSH Application Team
  * @brief   Head file of LPTIM32 FL Module
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
#ifndef __FM33LG0XX_FL_LPTIM32_H
#define __FM33LG0XX_FL_LPTIM32_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup LPTIM32 LPTIM32
  * @brief LPTIM32 FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup LPTIM32_FL_ES_INIT LPTIM32 Exported Init structures
  * @{
  */

/**
  * @brief FL LPTIM32 Init Sturcture definition
  */

/**
  * @brief LPTIM32 Init Sturcture Definition
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

    /* 单次计数使能 */
    uint32_t onePulseMode;

    /* ETR异步计数边沿 */
    uint32_t countEdge;

    /* ETR触发计数边沿 */
    uint32_t triggerEdge;

} FL_LPTIM32_InitTypeDef;

/**
  * @brief  LPTIM32 Output Compare Configuration Structure Definition
  */
typedef struct
{
    /* 比较值 */
    uint32_t compareValue;

    /* 比较输出极性 */
    uint32_t OCPolarity;

} FL_LPTIM32_OC_InitTypeDef;

/**
  * @brief  LPTIM32 Input Capture Configuration Structure Definition
  */
typedef struct
{
    /* 通道1捕获源 */
    uint32_t ICSource;

    /* 输入捕获极性 */
    uint32_t ICEdge;

} FL_LPTIM32_IC_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup LPTIM32_FL_Exported_Constants LPTIM32 Exported Constants
  * @{
  */

#define    LPTIM32_CR_EN_Pos                                      (0U)
#define    LPTIM32_CR_EN_Msk                                      (0x1U << LPTIM32_CR_EN_Pos)
#define    LPTIM32_CR_EN                                          LPTIM32_CR_EN_Msk

#define    LPTIM32_CFGR_ETR_AFEN_Pos                              (24U)
#define    LPTIM32_CFGR_ETR_AFEN_Msk                              (0x1U << LPTIM32_CFGR_ETR_AFEN_Pos)
#define    LPTIM32_CFGR_ETR_AFEN                                  LPTIM32_CFGR_ETR_AFEN_Msk

#define    LPTIM32_CFGR_PSCSEL_Pos                                (14U)
#define    LPTIM32_CFGR_PSCSEL_Msk                                (0x1U << LPTIM32_CFGR_PSCSEL_Pos)
#define    LPTIM32_CFGR_PSCSEL                                    LPTIM32_CFGR_PSCSEL_Msk

#define    LPTIM32_CFGR_DIVSEL_Pos                                (10U)
#define    LPTIM32_CFGR_DIVSEL_Msk                                (0x7U << LPTIM32_CFGR_DIVSEL_Pos)
#define    LPTIM32_CFGR_DIVSEL                                    LPTIM32_CFGR_DIVSEL_Msk

#define    LPTIM32_CFGR_EDGESEL_Pos                               (7U)
#define    LPTIM32_CFGR_EDGESEL_Msk                               (0x1U << LPTIM32_CFGR_EDGESEL_Pos)
#define    LPTIM32_CFGR_EDGESEL                                   LPTIM32_CFGR_EDGESEL_Msk

#define    LPTIM32_CFGR_TRIGCFG_Pos                               (5U)
#define    LPTIM32_CFGR_TRIGCFG_Msk                               (0x3U << LPTIM32_CFGR_TRIGCFG_Pos)
#define    LPTIM32_CFGR_TRIGCFG                                   LPTIM32_CFGR_TRIGCFG_Msk

#define    LPTIM32_CFGR_ONST_Pos                                  (2U)
#define    LPTIM32_CFGR_ONST_Msk                                  (0x1U << LPTIM32_CFGR_ONST_Pos)
#define    LPTIM32_CFGR_ONST                                      LPTIM32_CFGR_ONST_Msk

#define    LPTIM32_CFGR_TMOD_Pos                                  (0U)
#define    LPTIM32_CFGR_TMOD_Msk                                  (0x3U << LPTIM32_CFGR_TMOD_Pos)
#define    LPTIM32_CFGR_TMOD                                      LPTIM32_CFGR_TMOD_Msk

#define    LPTIM32_IER_CCIE_Pos                                   (0U)
#define    LPTIM32_IER_CCIE_Msk                                   (0xfU << LPTIM32_IER_CCIE_Pos)
#define    LPTIM32_IER_CCIE                                       LPTIM32_IER_CCIE_Msk

#define    LPTIM32_IER_OVIE_Pos                                   (6U)
#define    LPTIM32_IER_OVIE_Msk                                   (0x1U << LPTIM32_IER_OVIE_Pos)
#define    LPTIM32_IER_OVIE                                       LPTIM32_IER_OVIE_Msk

#define    LPTIM32_IER_TRIGIE_Pos                                 (7U)
#define    LPTIM32_IER_TRIGIE_Msk                                 (0x1U << LPTIM32_IER_TRIGIE_Pos)
#define    LPTIM32_IER_TRIGIE                                     LPTIM32_IER_TRIGIE_Msk

#define    LPTIM32_IER_OVRIE_Pos                                  (8U)
#define    LPTIM32_IER_OVRIE_Msk                                  (0xfU << LPTIM32_IER_OVRIE_Pos)
#define    LPTIM32_IER_OVRIE                                      LPTIM32_IER_OVRIE_Msk

#define    LPTIM32_ISR_CCIF_Pos                                   (0U)
#define    LPTIM32_ISR_CCIF_Msk                                   (0xfU << LPTIM32_ISR_CCIF_Pos)
#define    LPTIM32_ISR_CCIF                                       LPTIM32_ISR_CCIF_Msk

#define    LPTIM32_ISR_OVIF_Pos                                   (6U)
#define    LPTIM32_ISR_OVIF_Msk                                   (0x1U << LPTIM32_ISR_OVIF_Pos)
#define    LPTIM32_ISR_OVIF                                       LPTIM32_ISR_OVIF_Msk

#define    LPTIM32_ISR_TRIGIF_Pos                                 (7U)
#define    LPTIM32_ISR_TRIGIF_Msk                                 (0x1U << LPTIM32_ISR_TRIGIF_Pos)
#define    LPTIM32_ISR_TRIGIF                                     LPTIM32_ISR_TRIGIF_Msk

#define    LPTIM32_ISR_OVRIF_Pos                                  (8U)
#define    LPTIM32_ISR_OVRIF_Msk                                  (0xfU << LPTIM32_ISR_OVRIF_Pos)
#define    LPTIM32_ISR_OVRIF                                      LPTIM32_ISR_OVRIF_Msk

#define    LPTIM32_CCSR_CAPCFG_Pos                                (8U)
#define    LPTIM32_CCSR_CAPCFG_Msk                                (0x3U << LPTIM32_CCSR_CAPCFG_Pos)
#define    LPTIM32_CCSR_CAPCFG                                    LPTIM32_CCSR_CAPCFG_Msk

#define    LPTIM32_CCSR_CCS_Pos                                   (0U)
#define    LPTIM32_CCSR_CCS_Msk                                   (0x3U << LPTIM32_CCSR_CCS_Pos)
#define    LPTIM32_CCSR_CCS                                       LPTIM32_CCSR_CCS_Msk

#define    LPTIM32_CCSR_CAPEDGE_Pos                               (20U)
#define    LPTIM32_CCSR_CAPEDGE_Msk                               (0x1U << LPTIM32_CCSR_CAPEDGE_Pos)
#define    LPTIM32_CCSR_CAPEDGE                                   LPTIM32_CCSR_CAPEDGE_Msk

#define    LPTIM32_CCSR_CAP1SSEL_Pos                              (24U)
#define    LPTIM32_CCSR_CAP1SSEL_Msk                              (0x3U << LPTIM32_CCSR_CAP1SSEL_Pos)
#define    LPTIM32_CCSR_CAP1SSEL                                  LPTIM32_CCSR_CAP1SSEL_Msk

#define    LPTIM32_CCSR_POLAR_Pos                                 (16U)
#define    LPTIM32_CCSR_POLAR_Msk                                 (0x1U << LPTIM32_CCSR_POLAR_Pos)
#define    LPTIM32_CCSR_POLAR                                     LPTIM32_CCSR_POLAR_Msk

#define    LPTIM32_CFGR_MMS_Pos                                   (16U)
#define    LPTIM32_CFGR_MMS_Msk                                   (0x7U << LPTIM32_CFGR_MMS_Pos)
#define    LPTIM32_CFGR_MMS                                       LPTIM32_CFGR_MMS_Msk



#define    FL_LPTIM32_CHANNEL_1                                   (0x1U << 0U)
#define    FL_LPTIM32_CHANNEL_2                                   (0x1U << 1U)
#define    FL_LPTIM32_CHANNEL_3                                   (0x1U << 2U)
#define    FL_LPTIM32_CHANNEL_4                                   (0x1U << 3U)



#define    FL_LPTIM32_CLK_SOURCE_INTERNAL                         (0x0U << LPTIM32_CFGR_PSCSEL_Pos)
#define    FL_LPTIM32_CLK_SOURCE_EXTERNAL                         (0x1U << LPTIM32_CFGR_PSCSEL_Pos)


#define    FL_LPTIM32_PSC_DIV1                                    (0x0U << LPTIM32_CFGR_DIVSEL_Pos)
#define    FL_LPTIM32_PSC_DIV2                                    (0x1U << LPTIM32_CFGR_DIVSEL_Pos)
#define    FL_LPTIM32_PSC_DIV4                                    (0x2U << LPTIM32_CFGR_DIVSEL_Pos)
#define    FL_LPTIM32_PSC_DIV8                                    (0x3U << LPTIM32_CFGR_DIVSEL_Pos)
#define    FL_LPTIM32_PSC_DIV16                                   (0x4U << LPTIM32_CFGR_DIVSEL_Pos)
#define    FL_LPTIM32_PSC_DIV32                                   (0x5U << LPTIM32_CFGR_DIVSEL_Pos)
#define    FL_LPTIM32_PSC_DIV64                                   (0x6U << LPTIM32_CFGR_DIVSEL_Pos)
#define    FL_LPTIM32_PSC_DIV128                                  (0x7U << LPTIM32_CFGR_DIVSEL_Pos)


#define    FL_LPTIM32_ETR_COUNT_EDGE_RISING                       (0x0U << LPTIM32_CFGR_EDGESEL_Pos)
#define    FL_LPTIM32_ETR_COUNT_EDGE_FALLING                      (0x1U << LPTIM32_CFGR_EDGESEL_Pos)


#define    FL_LPTIM32_ETR_TRIGGER_EDGE_RISING                     (0x0U << LPTIM32_CFGR_TRIGCFG_Pos)
#define    FL_LPTIM32_ETR_TRIGGER_EDGE_FALLING                    (0x1U << LPTIM32_CFGR_TRIGCFG_Pos)
#define    FL_LPTIM32_ETR_TRIGGER_EDGE_BOTH                       (0x2U << LPTIM32_CFGR_TRIGCFG_Pos)


#define    FL_LPTIM32_ONE_PULSE_MODE_CONTINUOUS                   (0x0U << LPTIM32_CFGR_ONST_Pos)
#define    FL_LPTIM32_ONE_PULSE_MODE_SINGLE                       (0x1U << LPTIM32_CFGR_ONST_Pos)


#define    FL_LPTIM32_OPERATION_MODE_NORMAL                       (0x0U << LPTIM32_CFGR_TMOD_Pos)
#define    FL_LPTIM32_OPERATION_MODE_EXTERNAL_TRIGGER_CNT         (0x1U << LPTIM32_CFGR_TMOD_Pos)
#define    FL_LPTIM32_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT     (0x2U << LPTIM32_CFGR_TMOD_Pos)
#define    FL_LPTIM32_OPERATION_MODE_TIMEOUT                      (0x3U << LPTIM32_CFGR_TMOD_Pos)


#define    FL_LPTIM32_IC_EDGE_RISING                              (0x0U << LPTIM32_CCSR_CAPCFG_Pos)
#define    FL_LPTIM32_IC_EDGE_FALLING                             (0x1U << LPTIM32_CCSR_CAPCFG_Pos)
#define    FL_LPTIM32_IC_EDGE_BOTH                                (0x2U << LPTIM32_CCSR_CAPCFG_Pos)


#define    FL_LPTIM32_CHANNEL_MODE_DISABLE                        (0x0U << LPTIM32_CCSR_CCS_Pos)
#define    FL_LPTIM32_CHANNEL_MODE_INPUT                          (0x1U << LPTIM32_CCSR_CCS_Pos)
#define    FL_LPTIM32_CHANNEL_MODE_OUTPUT                         (0x2U << LPTIM32_CCSR_CCS_Pos)


#define    FL_LPTIM32_IC_CAPTURED_EDGE_RISING                     (0x0U << LPTIM32_CCSR_CAPEDGE_Pos)
#define    FL_LPTIM32_IC_CAPTURED_EDGE_FALLING                    (0x1U << LPTIM32_CCSR_CAPEDGE_Pos)

#define    FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP0                   (0x0U << LPTIM32_CCSR_CAP1SSEL_Pos)
#define    FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP1                   (0x1U << LPTIM32_CCSR_CAP1SSEL_Pos)
#define    FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP2                   (0x2U << LPTIM32_CCSR_CAP1SSEL_Pos)
#define    FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP3                   (0x3U << LPTIM32_CCSR_CAP1SSEL_Pos)


#define    FL_LPTIM32_OC_POLARITY_NORMAL                          (0x0U << LPTIM32_CCSR_POLAR_Pos)
#define    FL_LPTIM32_OC_POLARITY_INVERT                          (0x1U << LPTIM32_CCSR_POLAR_Pos)


#define    FL_LPTIM32_TRGO_ENABLE                                 (0x1U << LPTIM32_CFGR_MMS_Pos)
#define    FL_LPTIM32_TRGO_UPDATE                                 (0x2U << LPTIM32_CFGR_MMS_Pos)
#define    FL_LPTIM32_TRGO_OC1REF                                 (0x3U << LPTIM32_CFGR_MMS_Pos)
#define    FL_LPTIM32_TRGO_IC1                                    (0x4U << LPTIM32_CFGR_MMS_Pos)
#define    FL_LPTIM32_TRGO_IC2                                    (0x5U << LPTIM32_CFGR_MMS_Pos)
#define    FL_LPTIM32_TRGO_IC3                                    (0x6U << LPTIM32_CFGR_MMS_Pos)
#define    FL_LPTIM32_TRGO_IC4                                    (0x7U << LPTIM32_CFGR_MMS_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup LPTIM32_FL_Exported_Functions LPTIM32 Exported Functions
  * @{
  */

/**
  * @brief    Enable LPTIM32
  * @rmtoll   CR    EN    FL_LPTIM32_Enable
  * @param    LPTIM32x LPTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_Enable(LPTIM32_Type *LPTIM32x)
{
    SET_BIT(LPTIM32x->CR, LPTIM32_CR_EN_Msk);
}

/**
  * @brief    Disable LPTIM32
  * @rmtoll   CR    EN    FL_LPTIM32_Disable
  * @param    LPTIM32x LPTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_Disable(LPTIM32_Type *LPTIM32x)
{
    CLEAR_BIT(LPTIM32x->CR, LPTIM32_CR_EN_Msk);
}

/**
  * @brief    Get LPTIM32 Enable Status
  * @rmtoll   CR    EN    FL_LPTIM32_IsEnabled
  * @param    LPTIM32x LPTIM32 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IsEnabled(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CR, LPTIM32_CR_EN_Msk) == LPTIM32_CR_EN_Msk);
}

/**
  * @brief    Enable External Input Analog Filter
  * @rmtoll   CFGR    ETR_AFEN    FL_LPTIM32_EnableETRFilter
  * @param    LPTIM32x LPTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_EnableETRFilter(LPTIM32_Type *LPTIM32x)
{
    SET_BIT(LPTIM32x->CFGR, LPTIM32_CFGR_ETR_AFEN_Msk);
}

/**
  * @brief    Disable External Input Analog Filter
  * @rmtoll   CFGR    ETR_AFEN    FL_LPTIM32_DisableETRFilter
  * @param    LPTIM32x LPTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_DisableETRFilter(LPTIM32_Type *LPTIM32x)
{
    CLEAR_BIT(LPTIM32x->CFGR, LPTIM32_CFGR_ETR_AFEN_Msk);
}

/**
  * @brief    Get External Input Analog Filter Enable Status
  * @rmtoll   CFGR    ETR_AFEN    FL_LPTIM32_IsEnabledETRFilter
  * @param    LPTIM32x LPTIM32 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IsEnabledETRFilter(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CFGR, LPTIM32_CFGR_ETR_AFEN_Msk) == LPTIM32_CFGR_ETR_AFEN_Msk);
}

/**
  * @brief    Set Clock Source
  * @rmtoll   CFGR    PSCSEL    FL_LPTIM32_SetClockSource
  * @param    LPTIM32x LPTIM32 instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CLK_SOURCE_INTERNAL
  *           @arg @ref FL_LPTIM32_CLK_SOURCE_EXTERNAL
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_SetClockSource(LPTIM32_Type *LPTIM32x, uint32_t source)
{
    MODIFY_REG(LPTIM32x->CFGR, LPTIM32_CFGR_PSCSEL_Msk, source);
}

/**
  * @brief    Get Clock Source Setting
  * @rmtoll   CFGR    PSCSEL    FL_LPTIM32_GetClockSource
  * @param    LPTIM32x LPTIM32 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM32_CLK_SOURCE_INTERNAL
  *           @arg @ref FL_LPTIM32_CLK_SOURCE_EXTERNAL
  */
__STATIC_INLINE uint32_t FL_LPTIM32_GetClockSource(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CFGR, LPTIM32_CFGR_PSCSEL_Msk));
}

/**
  * @brief    Set Counter Clock Prescaler
  * @rmtoll   CFGR    DIVSEL    FL_LPTIM32_SetPrescaler
  * @param    LPTIM32x LPTIM32 instance
  * @param    psc This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_PSC_DIV1
  *           @arg @ref FL_LPTIM32_PSC_DIV2
  *           @arg @ref FL_LPTIM32_PSC_DIV4
  *           @arg @ref FL_LPTIM32_PSC_DIV8
  *           @arg @ref FL_LPTIM32_PSC_DIV16
  *           @arg @ref FL_LPTIM32_PSC_DIV32
  *           @arg @ref FL_LPTIM32_PSC_DIV64
  *           @arg @ref FL_LPTIM32_PSC_DIV128
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_SetPrescaler(LPTIM32_Type *LPTIM32x, uint32_t psc)
{
    MODIFY_REG(LPTIM32x->CFGR, LPTIM32_CFGR_DIVSEL_Msk, psc);
}

/**
  * @brief    Get Counter Clock Prescaler Setting
  * @rmtoll   CFGR    DIVSEL    FL_LPTIM32_GetPrescaler
  * @param    LPTIM32x LPTIM32 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM32_PSC_DIV1
  *           @arg @ref FL_LPTIM32_PSC_DIV2
  *           @arg @ref FL_LPTIM32_PSC_DIV4
  *           @arg @ref FL_LPTIM32_PSC_DIV8
  *           @arg @ref FL_LPTIM32_PSC_DIV16
  *           @arg @ref FL_LPTIM32_PSC_DIV32
  *           @arg @ref FL_LPTIM32_PSC_DIV64
  *           @arg @ref FL_LPTIM32_PSC_DIV128
  */
__STATIC_INLINE uint32_t FL_LPTIM32_GetPrescaler(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CFGR, LPTIM32_CFGR_DIVSEL_Msk));
}

/**
  * @brief    Set ETR Count Edge
  * @rmtoll   CFGR    EDGESEL    FL_LPTIM32_SetETRCountEdge
  * @param    LPTIM32x LPTIM32 instance
  * @param    edge This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_ETR_COUNT_EDGE_RISING
  *           @arg @ref FL_LPTIM32_ETR_COUNT_EDGE_FALLING
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_SetETRCountEdge(LPTIM32_Type *LPTIM32x, uint32_t edge)
{
    MODIFY_REG(LPTIM32x->CFGR, LPTIM32_CFGR_EDGESEL_Msk, edge);
}

/**
  * @brief    Get ETR Count Edge Setting
  * @rmtoll   CFGR    EDGESEL    FL_LPTIM32_GetETRCountEdge
  * @param    LPTIM32x LPTIM32 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM32_ETR_COUNT_EDGE_RISING
  *           @arg @ref FL_LPTIM32_ETR_COUNT_EDGE_FALLING
  */
__STATIC_INLINE uint32_t FL_LPTIM32_GetETRCountEdge(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CFGR, LPTIM32_CFGR_EDGESEL_Msk));
}

/**
  * @brief    Set ETR Trigger Edge
  * @rmtoll   CFGR    TRIGCFG    FL_LPTIM32_SetETRTriggerEdge
  * @param    LPTIM32x LPTIM32 instance
  * @param    edge This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_ETR_TRIGGER_EDGE_RISING
  *           @arg @ref FL_LPTIM32_ETR_TRIGGER_EDGE_FALLING
  *           @arg @ref FL_LPTIM32_ETR_TRIGGER_EDGE_BOTH
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_SetETRTriggerEdge(LPTIM32_Type *LPTIM32x, uint32_t edge)
{
    MODIFY_REG(LPTIM32x->CFGR, LPTIM32_CFGR_TRIGCFG_Msk, edge);
}

/**
  * @brief    Get ETR Trigger Edge Setting
  * @rmtoll   CFGR    TRIGCFG    FL_LPTIM32_GetETRTriggerEdge
  * @param    LPTIM32x LPTIM32 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM32_ETR_TRIGGER_EDGE_RISING
  *           @arg @ref FL_LPTIM32_ETR_TRIGGER_EDGE_FALLING
  *           @arg @ref FL_LPTIM32_ETR_TRIGGER_EDGE_BOTH
  */
__STATIC_INLINE uint32_t FL_LPTIM32_GetETRTriggerEdge(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CFGR, LPTIM32_CFGR_TRIGCFG_Msk));
}

/**
  * @brief    Set One Pulse Mode
  * @rmtoll   CFGR    ONST    FL_LPTIM32_SetOnePulseMode
  * @param    LPTIM32x LPTIM32 instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_ONE_PULSE_MODE_CONTINUOUS
  *           @arg @ref FL_LPTIM32_ONE_PULSE_MODE_SINGLE
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_SetOnePulseMode(LPTIM32_Type *LPTIM32x, uint32_t mode)
{
    MODIFY_REG(LPTIM32x->CFGR, LPTIM32_CFGR_ONST_Msk, mode);
}

/**
  * @brief    Get One Pulse Mode Setting
  * @rmtoll   CFGR    ONST    FL_LPTIM32_GetOnePulseMode
  * @param    LPTIM32x LPTIM32 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM32_ONE_PULSE_MODE_CONTINUOUS
  *           @arg @ref FL_LPTIM32_ONE_PULSE_MODE_SINGLE
  */
__STATIC_INLINE uint32_t FL_LPTIM32_GetOnePulseMode(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CFGR, LPTIM32_CFGR_ONST_Msk));
}

/**
  * @brief    Set Operation Mode
  * @rmtoll   CFGR    TMOD    FL_LPTIM32_SetOperationMode
  * @param    LPTIM32x LPTIM32 instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_OPERATION_MODE_NORMAL
  *           @arg @ref FL_LPTIM32_OPERATION_MODE_EXTERNAL_TRIGGER_CNT
  *           @arg @ref FL_LPTIM32_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT
  *           @arg @ref FL_LPTIM32_OPERATION_MODE_TIMEOUT
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_SetOperationMode(LPTIM32_Type *LPTIM32x, uint32_t mode)
{
    MODIFY_REG(LPTIM32x->CFGR, LPTIM32_CFGR_TMOD_Msk, mode);
}

/**
  * @brief    Get Operation Mode Setting
  * @rmtoll   CFGR    TMOD    FL_LPTIM32_GetOperationMode
  * @param    LPTIM32x LPTIM32 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM32_OPERATION_MODE_NORMAL
  *           @arg @ref FL_LPTIM32_OPERATION_MODE_EXTERNAL_TRIGGER_CNT
  *           @arg @ref FL_LPTIM32_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT
  *           @arg @ref FL_LPTIM32_OPERATION_MODE_TIMEOUT
  */
__STATIC_INLINE uint32_t FL_LPTIM32_GetOperationMode(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CFGR, LPTIM32_CFGR_TMOD_Msk));
}

/**
  * @brief    Set Channel 1 Output Compare Value
  * @rmtoll   CCR1        FL_LPTIM32_WriteCompareCH1
  * @param    LPTIM32x LPTIM32 instance
  * @param    compareVal
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_WriteCompareCH1(LPTIM32_Type *LPTIM32x, uint32_t compareVal)
{
    MODIFY_REG(LPTIM32x->CCR1, (0xffffffffU << 0U), (compareVal << 0U));
}

/**
  * @brief    Get Channel 1 Output Compare Value
  * @rmtoll   CCR1        FL_LPTIM32_ReadCompareCH1
  * @param    LPTIM32x LPTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM32_ReadCompareCH1(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CCR1, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Set Channel 2 Output Compare Value
  * @rmtoll   CCR2        FL_LPTIM32_WriteCompareCH2
  * @param    LPTIM32x LPTIM32 instance
  * @param    compareVal
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_WriteCompareCH2(LPTIM32_Type *LPTIM32x, uint32_t compareVal)
{
    MODIFY_REG(LPTIM32x->CCR2, (0xffffffffU << 0U), (compareVal << 0U));
}

/**
  * @brief    Get Channel 2 Output Compare Value
  * @rmtoll   CCR2        FL_LPTIM32_ReadCompareCH2
  * @param    LPTIM32x LPTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM32_ReadCompareCH2(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CCR2, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Set Channel 3 Output Compare Value
  * @rmtoll   CCR3        FL_LPTIM32_WriteCompareCH3
  * @param    LPTIM32x LPTIM32 instance
  * @param    compareVal
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_WriteCompareCH3(LPTIM32_Type *LPTIM32x, uint32_t compareVal)
{
    MODIFY_REG(LPTIM32x->CCR3, (0xffffffffU << 0U), (compareVal << 0U));
}

/**
  * @brief    Get Channel 3 Output Compare Value
  * @rmtoll   CCR3        FL_LPTIM32_ReadCompareCH3
  * @param    LPTIM32x LPTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM32_ReadCompareCH3(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CCR3, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Set Channel 4 Output Compare Value
  * @rmtoll   CCR4        FL_LPTIM32_WriteCompareCH4
  * @param    LPTIM32x LPTIM32 instance
  * @param    compareVal
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_WriteCompareCH4(LPTIM32_Type *LPTIM32x, uint32_t compareVal)
{
    MODIFY_REG(LPTIM32x->CCR4, (0xffffffffU << 0U), (compareVal << 0U));
}

/**
  * @brief    Get Channel 4 Output Compare Value
  * @rmtoll   CCR4        FL_LPTIM32_ReadCompareCH4
  * @param    LPTIM32x LPTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM32_ReadCompareCH4(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CCR4, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Get Channel 1 Input Capture Value
  * @rmtoll   CCR1        FL_LPTIM32_ReadCaptureCH1
  * @param    LPTIM32x LPTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM32_ReadCaptureCH1(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CCR1, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Get Channel 2 Input Capture Value
  * @rmtoll   CCR2        FL_LPTIM32_ReadCaptureCH2
  * @param    LPTIM32x LPTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM32_ReadCaptureCH2(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CCR2, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Get Channel 3 Input Capture Value
  * @rmtoll   CCR3        FL_LPTIM32_ReadCaptureCH3
  * @param    LPTIM32x LPTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM32_ReadCaptureCH3(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CCR3, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Get Channel 4 Input Capture Value
  * @rmtoll   CCR4        FL_LPTIM32_ReadCaptureCH4
  * @param    LPTIM32x LPTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM32_ReadCaptureCH4(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CCR4, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Enable Channel Capture/Compare Interrupt
  * @rmtoll   IER    CCIE    FL_LPTIM32_EnableIT_CC
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_EnableIT_CC(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    SET_BIT(LPTIM32x->IER, ((channel & 0xf) << 0x0U));
}

/**
  * @brief    Enable Update Event Interrupt
  * @rmtoll   IER    OVIE    FL_LPTIM32_EnableIT_Update
  * @param    LPTIM32x LPTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_EnableIT_Update(LPTIM32_Type *LPTIM32x)
{
    SET_BIT(LPTIM32x->IER, LPTIM32_IER_OVIE_Msk);
}

/**
  * @brief    Enable External Trigger Interrupt
  * @rmtoll   IER    TRIGIE    FL_LPTIM32_EnableIT_Trigger
  * @param    LPTIM32x LPTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_EnableIT_Trigger(LPTIM32_Type *LPTIM32x)
{
    SET_BIT(LPTIM32x->IER, LPTIM32_IER_TRIGIE_Msk);
}

/**
  * @brief    Enable Channel Capture Overflow Interrupt
  * @rmtoll   IER    OVRIE    FL_LPTIM32_EnableIT_CCOverflow
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_EnableIT_CCOverflow(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    SET_BIT(LPTIM32x->IER, ((channel & 0xf) << 0x8U));
}

/**
  * @brief    Disable Channel Capture/Compare Interrupt
  * @rmtoll   IER    CCIE    FL_LPTIM32_DisableIT_CC
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_DisableIT_CC(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    CLEAR_BIT(LPTIM32x->IER, ((channel & 0xf) << 0x0U));
}

/**
  * @brief    Disable Update Event Interrupt
  * @rmtoll   IER    OVIE    FL_LPTIM32_DisableIT_Update
  * @param    LPTIM32x LPTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_DisableIT_Update(LPTIM32_Type *LPTIM32x)
{
    CLEAR_BIT(LPTIM32x->IER, LPTIM32_IER_OVIE_Msk);
}

/**
  * @brief    Disable External Trigger Interrupt
  * @rmtoll   IER    TRIGIE    FL_LPTIM32_DisableIT_Trigger
  * @param    LPTIM32x LPTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_DisableIT_Trigger(LPTIM32_Type *LPTIM32x)
{
    CLEAR_BIT(LPTIM32x->IER, LPTIM32_IER_TRIGIE_Msk);
}

/**
  * @brief    Disable Channel Capture Overflow Interrupt
  * @rmtoll   IER    OVRIE    FL_LPTIM32_DisableIT_CCOverflow
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_DisableIT_CCOverflow(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    CLEAR_BIT(LPTIM32x->IER, ((channel & 0xf) << 0x8U));
}

/**
  * @brief    Get Channel Capture/Compare Interrupt Enable Status
  * @rmtoll   IER    CCIE    FL_LPTIM32_IsEnabledIT_CC
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IsEnabledIT_CC(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    return (uint32_t)(READ_BIT(LPTIM32x->IER, ((channel & 0xf) << 0x0U)) == ((channel & 0xf) << 0x0U));
}

/**
  * @brief    Get Counter Update Event Interrupt Enable Status
  * @rmtoll   IER    OVIE    FL_LPTIM32_IsEnabledIT_Update
  * @param    LPTIM32x LPTIM32 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IsEnabledIT_Update(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->IER, LPTIM32_IER_OVIE_Msk) == LPTIM32_IER_OVIE_Msk);
}

/**
  * @brief    Get External Trigger Interrupt Enable Status
  * @rmtoll   IER    TRIGIE    FL_LPTIM32_IsEnabledIT_Trigger
  * @param    LPTIM32x LPTIM32 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IsEnabledIT_Trigger(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->IER, LPTIM32_IER_TRIGIE_Msk) == LPTIM32_IER_TRIGIE_Msk);
}

/**
  * @brief    Get Channel Capture Overflow Interrupt Enable Status
  * @rmtoll   IER    OVRIE    FL_LPTIM32_IsEnabledIT_CCOverflow
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IsEnabledIT_CCOverflow(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    return (uint32_t)(READ_BIT(LPTIM32x->IER, ((channel & 0xf) << 0x8U)) == ((channel & 0xf) << 0x8U));
}

/**
  * @brief    Get Capture/Compare Channel Interrupt Flag
  * @rmtoll   ISR    CCIF    FL_LPTIM32_IsActiveFlag_CC
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IsActiveFlag_CC(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    return (uint32_t)(READ_BIT(LPTIM32x->ISR, ((channel & 0xf) << 0x0U)) == ((channel & 0xf) << 0x0U));
}

/**
  * @brief    Get Update Event Interrupt Flag
  * @rmtoll   ISR    OVIF    FL_LPTIM32_IsActiveFlag_Update
  * @param    LPTIM32x LPTIM32 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IsActiveFlag_Update(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->ISR, LPTIM32_ISR_OVIF_Msk) == (LPTIM32_ISR_OVIF_Msk));
}

/**
  * @brief    Get External Trigger Interrupt Flag
  * @rmtoll   ISR    TRIGIF    FL_LPTIM32_IsActiveFlag_Trigger
  * @param    LPTIM32x LPTIM32 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IsActiveFlag_Trigger(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->ISR, LPTIM32_ISR_TRIGIF_Msk) == (LPTIM32_ISR_TRIGIF_Msk));
}

/**
  * @brief    Get Channel Capture Overflow Interrupt Flag
  * @rmtoll   ISR    OVRIF    FL_LPTIM32_IsActiveFlag_CCOverflow
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IsActiveFlag_CCOverflow(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    return (uint32_t)(READ_BIT(LPTIM32x->ISR, ((channel & 0xf) << 0x8U)) == ((channel & 0xf) << 0x8U));
}

/**
  * @brief    Clear Capture/Compare Channel Interrupt Flag
  * @rmtoll   ISR    CCIF    FL_LPTIM32_ClearFlag_CC
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_ClearFlag_CC(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    WRITE_REG(LPTIM32x->ISR, ((channel & 0xf) << 0x0U));
}

/**
  * @brief    Clear Update Event Interrupt Flag
  * @rmtoll   ISR    OVIF    FL_LPTIM32_ClearFlag_Update
  * @param    LPTIM32x LPTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_ClearFlag_Update(LPTIM32_Type *LPTIM32x)
{
    WRITE_REG(LPTIM32x->ISR, LPTIM32_ISR_OVIF_Msk);
}

/**
  * @brief    Clear External Trigger Interrupt Flag
  * @rmtoll   ISR    TRIGIF    FL_LPTIM32_ClearFlag_Trigger
  * @param    LPTIM32x LPTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_ClearFlag_Trigger(LPTIM32_Type *LPTIM32x)
{
    WRITE_REG(LPTIM32x->ISR, LPTIM32_ISR_TRIGIF_Msk);
}

/**
  * @brief    Clear Channel Capture Overflow Interrupt Flag
  * @rmtoll   ISR    OVRIF    FL_LPTIM32_ClearFlag_CCOverflow
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_ClearFlag_CCOverflow(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    WRITE_REG(LPTIM32x->ISR, ((channel & 0xf) << 0x8U));
}

/**
  * @brief    Set Auto Reload Value
  * @rmtoll   ARR        FL_LPTIM32_WriteAutoReload
  * @param    LPTIM32x LPTIM32 instance
  * @param    autoReload
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_WriteAutoReload(LPTIM32_Type *LPTIM32x, uint32_t autoReload)
{
    MODIFY_REG(LPTIM32x->ARR, (0xffffffffU << 0U), (autoReload << 0U));
}

/**
  * @brief    Get Auto Reload Value
  * @rmtoll   ARR        FL_LPTIM32_ReadAutoReload
  * @param    LPTIM32x LPTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM32_ReadAutoReload(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->ARR, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Set Input Capture Channel Capture Edge
  * @rmtoll   CCSR    CAPCFG    FL_LPTIM32_IC_SetCaptureEdge
  * @param    LPTIM32x LPTIM32 instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_IC_EDGE_RISING
  *           @arg @ref FL_LPTIM32_IC_EDGE_FALLING
  *           @arg @ref FL_LPTIM32_IC_EDGE_BOTH
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_IC_SetCaptureEdge(LPTIM32_Type *LPTIM32x, uint32_t polarity, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM32_CHANNEL_1:
            MODIFY_REG(LPTIM32x->CCSR, (0x3U << 8U), (polarity << 0U));
            break;
        case FL_LPTIM32_CHANNEL_2:
            MODIFY_REG(LPTIM32x->CCSR, (0x3U << 10U), (polarity << 2U));
            break;
        case FL_LPTIM32_CHANNEL_3:
            MODIFY_REG(LPTIM32x->CCSR, (0x3U << 12U), (polarity << 4U));
            break;
        case FL_LPTIM32_CHANNEL_4:
            MODIFY_REG(LPTIM32x->CCSR, (0x3U << 14U), (polarity << 6U));
            break;
    }
}

/**
  * @brief    Get Input Capture Channel Capture Edge
  * @rmtoll   CCSR    CAPCFG    FL_LPTIM32_IC_GetCaptureEdge
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM32_IC_EDGE_RISING
  *           @arg @ref FL_LPTIM32_IC_EDGE_FALLING
  *           @arg @ref FL_LPTIM32_IC_EDGE_BOTH
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IC_GetCaptureEdge(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM32_CHANNEL_1:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x3U << 8U)) >> 0U);
        case FL_LPTIM32_CHANNEL_2:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x3U << 10U)) >> 2U);
        case FL_LPTIM32_CHANNEL_3:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x3U << 12U)) >> 4U);
        case FL_LPTIM32_CHANNEL_4:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x3U << 14U)) >> 6U);
        default:
            return 0;
    }
}

/**
  * @brief    Set Channel Operation Mode
  * @rmtoll   CCSR    CCS    FL_LPTIM32_SetChannelMode
  * @param    LPTIM32x LPTIM32 instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_MODE_DISABLE
  *           @arg @ref FL_LPTIM32_CHANNEL_MODE_INPUT
  *           @arg @ref FL_LPTIM32_CHANNEL_MODE_OUTPUT
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_SetChannelMode(LPTIM32_Type *LPTIM32x, uint32_t mode, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM32_CHANNEL_1:
            MODIFY_REG(LPTIM32x->CCSR, (0x3U << 0U), (mode << 0U));
            break;
        case FL_LPTIM32_CHANNEL_2:
            MODIFY_REG(LPTIM32x->CCSR, (0x3U << 2U), (mode << 2U));
            break;
        case FL_LPTIM32_CHANNEL_3:
            MODIFY_REG(LPTIM32x->CCSR, (0x3U << 4U), (mode << 4U));
            break;
        case FL_LPTIM32_CHANNEL_4:
            MODIFY_REG(LPTIM32x->CCSR, (0x3U << 6U), (mode << 6U));
            break;
    }
}

/**
  * @brief    Get Channel Operation Mode
  * @rmtoll   CCSR    CCS    FL_LPTIM32_GetChannelMode
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_MODE_DISABLE
  *           @arg @ref FL_LPTIM32_CHANNEL_MODE_INPUT
  *           @arg @ref FL_LPTIM32_CHANNEL_MODE_OUTPUT
  */
__STATIC_INLINE uint32_t FL_LPTIM32_GetChannelMode(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM32_CHANNEL_1:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x3U << 0U)) >> 0U);
        case FL_LPTIM32_CHANNEL_2:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x3U << 2U)) >> 2U);
        case FL_LPTIM32_CHANNEL_3:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x3U << 4U)) >> 4U);
        case FL_LPTIM32_CHANNEL_4:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x3U << 6U)) >> 6U);
        default:
            return 0;
    }
}

/**
  * @brief    Get Channel Captured Edge
  * @rmtoll   CCSR    CAPEDGE    FL_LPTIM32_IC_GetCapturedEdge
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM32_IC_CAPTURED_EDGE_RISING
  *           @arg @ref FL_LPTIM32_IC_CAPTURED_EDGE_FALLING
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IC_GetCapturedEdge(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM32_CHANNEL_1:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x1U << 20U)) >> 0U);
        case FL_LPTIM32_CHANNEL_2:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x1U << 21U)) >> 1U);
        case FL_LPTIM32_CHANNEL_3:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x1U << 22U)) >> 2U);
        case FL_LPTIM32_CHANNEL_4:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x1U << 23U)) >> 3U);
        default:
            return 0;
    }
}

/**
  * @brief    Set Channel 1 Capture Source
  * @rmtoll   CCSR    CAP1SSEL    FL_LPTIM32_IC_SetChannel1CaptureSource
  * @param    LPTIM32x LPTIM32 instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP0
  *           @arg @ref FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP1
  *           @arg @ref FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP2
  *           @arg @ref FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP3
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_IC_SetChannel1CaptureSource(LPTIM32_Type *LPTIM32x, uint32_t source)
{
    MODIFY_REG(LPTIM32x->CCSR, LPTIM32_CCSR_CAP1SSEL_Msk, source);
}

/**
  * @brief    Get Channel 1 Capture Source Setting
  * @rmtoll   CCSR    CAP1SSEL    FL_LPTIM32_IC_GetChannel1CaptureSource
  * @param    LPTIM32x LPTIM32 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP0
  *           @arg @ref FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP1
  *           @arg @ref FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP2
  *           @arg @ref FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP3
  */
__STATIC_INLINE uint32_t FL_LPTIM32_IC_GetChannel1CaptureSource(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CCSR, LPTIM32_CCSR_CAP1SSEL_Msk));
}

/**
  * @brief    Set Channel Output Compare Polarity
  * @rmtoll   CCSR    POLAR    FL_LPTIM32_OC_SetPolarity
  * @param    LPTIM32x LPTIM32 instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_OC_POLARITY_NORMAL
  *           @arg @ref FL_LPTIM32_OC_POLARITY_INVERT
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_OC_SetPolarity(LPTIM32_Type *LPTIM32x, uint32_t polarity, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM32_CHANNEL_1:
            MODIFY_REG(LPTIM32x->CCSR, (0x1U << 16U), (polarity << 0U));
            break;
        case FL_LPTIM32_CHANNEL_2:
            MODIFY_REG(LPTIM32x->CCSR, (0x1U << 17U), (polarity << 1U));
            break;
        case FL_LPTIM32_CHANNEL_3:
            MODIFY_REG(LPTIM32x->CCSR, (0x1U << 18U), (polarity << 2U));
            break;
        case FL_LPTIM32_CHANNEL_4:
            MODIFY_REG(LPTIM32x->CCSR, (0x1U << 19U), (polarity << 3U));
            break;
    }
}

/**
  * @brief    Get Channel Output Compare Polarity
  * @rmtoll   CCSR    POLAR    FL_LPTIM32_OC_GetPolarity
  * @param    LPTIM32x LPTIM32 instance
  * @param    channel This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_CHANNEL_1
  *           @arg @ref FL_LPTIM32_CHANNEL_2
  *           @arg @ref FL_LPTIM32_CHANNEL_3
  *           @arg @ref FL_LPTIM32_CHANNEL_4
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM32_OC_POLARITY_NORMAL
  *           @arg @ref FL_LPTIM32_OC_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_LPTIM32_OC_GetPolarity(LPTIM32_Type *LPTIM32x, uint32_t channel)
{
    switch(channel)
    {
        case FL_LPTIM32_CHANNEL_1:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x1U << 16U)) >> 0U);
        case FL_LPTIM32_CHANNEL_2:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x1U << 17U)) >> 1U);
        case FL_LPTIM32_CHANNEL_3:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x1U << 18U)) >> 2U);
        case FL_LPTIM32_CHANNEL_4:
            return (uint32_t)(READ_BIT(LPTIM32x->CCSR, (0x1U << 19U)) >> 3U);
        default:
            return 0;
    }
}

/**
  * @brief    Set Sync Trigger Signal Output Source
  * @rmtoll   CFGR    MMS    FL_LPTIM32_SetTriggerOutput
  * @param    LPTIM32x LPTIM32 instance
  * @param    triggerOutput This parameter can be one of the following values:
  *           @arg @ref FL_LPTIM32_TRGO_ENABLE
  *           @arg @ref FL_LPTIM32_TRGO_UPDATE
  *           @arg @ref FL_LPTIM32_TRGO_OC1REF
  *           @arg @ref FL_LPTIM32_TRGO_IC1
  *           @arg @ref FL_LPTIM32_TRGO_IC2
  *           @arg @ref FL_LPTIM32_TRGO_IC3
  *           @arg @ref FL_LPTIM32_TRGO_IC4
  * @retval   None
  */
__STATIC_INLINE void FL_LPTIM32_SetTriggerOutput(LPTIM32_Type *LPTIM32x, uint32_t triggerOutput)
{
    MODIFY_REG(LPTIM32x->CFGR, LPTIM32_CFGR_MMS_Msk, triggerOutput);
}

/**
  * @brief    Get Sync Trigger Signal Output Source Setting
  * @rmtoll   CFGR    MMS    FL_LPTIM32_GetTriggerOutput
  * @param    LPTIM32x LPTIM32 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LPTIM32_TRGO_ENABLE
  *           @arg @ref FL_LPTIM32_TRGO_UPDATE
  *           @arg @ref FL_LPTIM32_TRGO_OC1REF
  *           @arg @ref FL_LPTIM32_TRGO_IC1
  *           @arg @ref FL_LPTIM32_TRGO_IC2
  *           @arg @ref FL_LPTIM32_TRGO_IC3
  *           @arg @ref FL_LPTIM32_TRGO_IC4
  */
__STATIC_INLINE uint32_t FL_LPTIM32_GetTriggerOutput(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CFGR, LPTIM32_CFGR_MMS_Msk));
}

/**
  * @brief    Read LPTIM32 Counter Value
  * @rmtoll   CNT        FL_LPTIM32_ReadCounter
  * @param    LPTIM32x LPTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LPTIM32_ReadCounter(LPTIM32_Type *LPTIM32x)
{
    return (uint32_t)(READ_BIT(LPTIM32x->CNT, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @}
  */

/** @defgroup LPTIM32_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_LPTIM32_DeInit(LPTIM32_Type *LPTIM32x);
FL_ErrorStatus FL_LPTIM32_Init(LPTIM32_Type *LPTIM32x, FL_LPTIM32_InitTypeDef *init);
void FL_LPTIM32_StructInit(FL_LPTIM32_InitTypeDef *init);
FL_ErrorStatus FL_LPTIM32_IC_Init(LPTIM32_Type *LPTIM32x, uint32_t channel, FL_LPTIM32_IC_InitTypeDef *ic_init);
void FL_LPTIM32_IC_StructInit(FL_LPTIM32_IC_InitTypeDef *ic_init);
FL_ErrorStatus FL_LPTIM32_OC_Init(LPTIM32_Type *LPTIM32x, uint32_t channel, FL_LPTIM32_OC_InitTypeDef *oc_init);
void FL_LPTIM32_OC_StructInit(FL_LPTIM32_OC_InitTypeDef *oc_init);

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

#endif /* __FM33LG0XX_FL_LPTIM32_H*/

/*************************Py_Code_Generator Version: 0.1-0.14-0.1 @ 2020-12-14*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
