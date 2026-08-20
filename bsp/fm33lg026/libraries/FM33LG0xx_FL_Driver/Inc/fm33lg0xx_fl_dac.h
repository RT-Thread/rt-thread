/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_dac.h
  * @author  FMSH Application Team
  * @brief   Head file of DAC FL Module
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
#ifndef __FM33LG0XX_FL_DAC_H
#define __FM33LG0XX_FL_DAC_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup DAC DAC
  * @brief DAC FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup DAC_FL_ES_INIT DAC Exported Init structures
  * @{
  */

/**
  * @brief FL DAC Init Sturcture definition
  */
typedef struct
{
    /*DAC触发模式使能配置*/
    uint32_t triggerMode;
    /*DAC触发源配置*/
    uint32_t triggerSource;
    /*DAC采样保持模式配置*/
    uint32_t sampleHoldMode;
    /*DAC保持时间配置*/
    uint32_t holdTime;
    /*DAC采样时间配置*/
    uint32_t sampleTime;
    /*DAC_Buffer模式配置*/
    uint32_t bufferMode;
    /*DAC反馈开关配置*/
    uint32_t switchMode;


} FL_DAC_InitTypeDef;
/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup DAC_FL_Exported_Constants DAC Exported Constants
  * @{
  */

#define    DAC_CR1_EN_Pos                                         (0U)
#define    DAC_CR1_EN_Msk                                         (0x1U << DAC_CR1_EN_Pos)
#define    DAC_CR1_EN                                             DAC_CR1_EN_Msk

#define    DAC_CR2_DMAEN_Pos                                      (1U)
#define    DAC_CR2_DMAEN_Msk                                      (0x1U << DAC_CR2_DMAEN_Pos)
#define    DAC_CR2_DMAEN                                          DAC_CR2_DMAEN_Msk

#define    DAC_CR2_TRGEN_Pos                                      (0U)
#define    DAC_CR2_TRGEN_Msk                                      (0x1U << DAC_CR2_TRGEN_Pos)
#define    DAC_CR2_TRGEN                                          DAC_CR2_TRGEN_Msk

#define    DAC_CFGR_SHEN_Pos                                      (8U)
#define    DAC_CFGR_SHEN_Msk                                      (0x1U << DAC_CFGR_SHEN_Pos)
#define    DAC_CFGR_SHEN                                          DAC_CFGR_SHEN_Msk

#define    DAC_CFGR_BUFEN_Pos                                     (7U)
#define    DAC_CFGR_BUFEN_Msk                                     (0x1U << DAC_CFGR_BUFEN_Pos)
#define    DAC_CFGR_BUFEN                                         DAC_CFGR_BUFEN_Msk

#define    DAC_CFGR_TRGSEL_Pos                                    (2U)
#define    DAC_CFGR_TRGSEL_Msk                                    (0xfU << DAC_CFGR_TRGSEL_Pos)
#define    DAC_CFGR_TRGSEL                                        DAC_CFGR_TRGSEL_Msk

#define    DAC_CFGR_SWIEN_Pos                                     (0U)
#define    DAC_CFGR_SWIEN_Msk                                     (0x1U << DAC_CFGR_SWIEN_Pos)
#define    DAC_CFGR_SWIEN                                         DAC_CFGR_SWIEN_Msk

#define    DAC_SWTRGR_SWTRIG_Pos                                  (0U)
#define    DAC_SWTRGR_SWTRIG_Msk                                  (0x1U << DAC_SWTRGR_SWTRIG_Pos)
#define    DAC_SWTRGR_SWTRIG                                      DAC_SWTRGR_SWTRIG_Msk

#define    DAC_DHR_DHR_Pos                                        (0U)
#define    DAC_DHR_DHR_Msk                                        (0xfffU << DAC_DHR_DHR_Pos)
#define    DAC_DHR_DHR                                            DAC_DHR_DHR_Msk

#define    DAC_IER_DMAE_IE_Pos                                    (3U)
#define    DAC_IER_DMAE_IE_Msk                                    (0x1U << DAC_IER_DMAE_IE_Pos)
#define    DAC_IER_DMAE_IE                                        DAC_IER_DMAE_IE_Msk

#define    DAC_IER_EOH_IE_Pos                                     (2U)
#define    DAC_IER_EOH_IE_Msk                                     (0x1U << DAC_IER_EOH_IE_Pos)
#define    DAC_IER_EOH_IE                                         DAC_IER_EOH_IE_Msk

#define    DAC_IER_EOS_IE_Pos                                     (1U)
#define    DAC_IER_EOS_IE_Msk                                     (0x1U << DAC_IER_EOS_IE_Pos)
#define    DAC_IER_EOS_IE                                         DAC_IER_EOS_IE_Msk

#define    DAC_IER_DOU_IE_Pos                                     (0U)
#define    DAC_IER_DOU_IE_Msk                                     (0x1U << DAC_IER_DOU_IE_Pos)
#define    DAC_IER_DOU_IE                                         DAC_IER_DOU_IE_Msk

#define    DAC_ISR_DMAERR_Pos                                     (3U)
#define    DAC_ISR_DMAERR_Msk                                     (0x1U << DAC_ISR_DMAERR_Pos)
#define    DAC_ISR_DMAERR                                         DAC_ISR_DMAERR_Msk

#define    DAC_ISR_EOH_Pos                                        (2U)
#define    DAC_ISR_EOH_Msk                                        (0x1U << DAC_ISR_EOH_Pos)
#define    DAC_ISR_EOH                                            DAC_ISR_EOH_Msk

#define    DAC_ISR_EOS_Pos                                        (1U)
#define    DAC_ISR_EOS_Msk                                        (0x1U << DAC_ISR_EOS_Pos)
#define    DAC_ISR_EOS                                            DAC_ISR_EOS_Msk

#define    DAC_ISR_DOU_Pos                                        (0U)
#define    DAC_ISR_DOU_Msk                                        (0x1U << DAC_ISR_DOU_Pos)
#define    DAC_ISR_DOU                                            DAC_ISR_DOU_Msk

#define    DAC_SHTR_THLD_Pos                                      (8U)
#define    DAC_SHTR_THLD_Msk                                      (0xffffU << DAC_SHTR_THLD_Pos)
#define    DAC_SHTR_THLD                                          DAC_SHTR_THLD_Msk

#define    DAC_SHTR_TSMPL_Pos                                     (0U)
#define    DAC_SHTR_TSMPL_Msk                                     (0xffU << DAC_SHTR_TSMPL_Pos)
#define    DAC_SHTR_TSMPL                                         DAC_SHTR_TSMPL_Msk






#define    FL_DAC_TRGI_SOFTWARE                                   (0x0U << DAC_CFGR_TRGSEL_Pos)
#define    FL_DAC_TRGI_ATIM                                       (0x1U << DAC_CFGR_TRGSEL_Pos)
#define    FL_DAC_TRGI_GPTIM1                                     (0x2U << DAC_CFGR_TRGSEL_Pos)
#define    FL_DAC_TRGI_GPTIM2                                     (0x3U << DAC_CFGR_TRGSEL_Pos)
#define    FL_DAC_TRGI_BSTIM16                                    (0x4U << DAC_CFGR_TRGSEL_Pos)
#define    FL_DAC_TRGI_LPTIM16                                    (0x5U << DAC_CFGR_TRGSEL_Pos)
#define    FL_DAC_TRGI_EXTI0                                      (0xcU << DAC_CFGR_TRGSEL_Pos)
#define    FL_DAC_TRGI_EXTI4                                      (0xdU << DAC_CFGR_TRGSEL_Pos)
#define    FL_DAC_TRGI_EXTI8                                      (0xeU << DAC_CFGR_TRGSEL_Pos)
#define    FL_DAC_TRGI_EXTI12                                     (0xfU << DAC_CFGR_TRGSEL_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup DAC_FL_Exported_Functions DAC Exported Functions
  * @{
  */

/**
  * @brief    Enable DAC
  * @rmtoll   CR1    EN    FL_DAC_Enable
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_Enable(DAC_Type *DACx)
{
    SET_BIT(DACx->CR1, DAC_CR1_EN_Msk);
}

/**
  * @brief    Disable DAC
  * @rmtoll   CR1    EN    FL_DAC_Disable
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_Disable(DAC_Type *DACx)
{
    CLEAR_BIT(DACx->CR1, DAC_CR1_EN_Msk);
}

/**
  * @brief    Get DAC Enable Status
  * @rmtoll   CR1    EN    FL_DAC_IsEnabled
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsEnabled(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->CR1, DAC_CR1_EN_Msk) == DAC_CR1_EN_Msk);
}

/**
  * @brief    Enable DAC DMA
  * @rmtoll   CR2    DMAEN    FL_DAC_EnableDMAReq
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_EnableDMAReq(DAC_Type *DACx)
{
    SET_BIT(DACx->CR2, DAC_CR2_DMAEN_Msk);
}

/**
  * @brief    Disable DAC DMA
  * @rmtoll   CR2    DMAEN    FL_DAC_DisableDMAReq
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_DisableDMAReq(DAC_Type *DACx)
{
    CLEAR_BIT(DACx->CR2, DAC_CR2_DMAEN_Msk);
}

/**
  * @brief    Get DAC DMA Enable Status
  * @rmtoll   CR2    DMAEN    FL_DAC_IsEnabledDMAReq
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsEnabledDMAReq(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->CR2, DAC_CR2_DMAEN_Msk) == DAC_CR2_DMAEN_Msk);
}

/**
  * @brief    Enable DAC Trigger
  * @rmtoll   CR2    TRGEN    FL_DAC_EnableTriggerMode
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_EnableTriggerMode(DAC_Type *DACx)
{
    SET_BIT(DACx->CR2, DAC_CR2_TRGEN_Msk);
}

/**
  * @brief    Disable DAC Trigger
  * @rmtoll   CR2    TRGEN    FL_DAC_DisableTriggerMode
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_DisableTriggerMode(DAC_Type *DACx)
{
    CLEAR_BIT(DACx->CR2, DAC_CR2_TRGEN_Msk);
}

/**
  * @brief    Get DAC Trigger  Enable Status
  * @rmtoll   CR2    TRGEN    FL_DAC_IsEnabledTriggerMode
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsEnabledTriggerMode(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->CR2, DAC_CR2_TRGEN_Msk) == DAC_CR2_TRGEN_Msk);
}

/**
  * @brief    Enable DAC Sample Hold
  * @rmtoll   CFGR    SHEN    FL_DAC_EnableSampleHoldMode
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_EnableSampleHoldMode(DAC_Type *DACx)
{
    SET_BIT(DACx->CFGR, DAC_CFGR_SHEN_Msk);
}

/**
  * @brief    Disable DAC Sample Hold
  * @rmtoll   CFGR    SHEN    FL_DAC_DisableSampleHoldMode
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_DisableSampleHoldMode(DAC_Type *DACx)
{
    CLEAR_BIT(DACx->CFGR, DAC_CFGR_SHEN_Msk);
}

/**
  * @brief    Get DAC Sample Hold  Enable Status
  * @rmtoll   CFGR    SHEN    FL_DAC_IsEnabledSampleHoldMode
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsEnabledSampleHoldMode(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->CFGR, DAC_CFGR_SHEN_Msk) == DAC_CFGR_SHEN_Msk);
}

/**
  * @brief    Enable DAC Output Buffer
  * @rmtoll   CFGR    BUFEN    FL_DAC_EnableOutputBuffer
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_EnableOutputBuffer(DAC_Type *DACx)
{
    SET_BIT(DACx->CFGR, DAC_CFGR_BUFEN_Msk);
}

/**
  * @brief    Disable DAC Output Buffer
  * @rmtoll   CFGR    BUFEN    FL_DAC_DisableOutputBuffer
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_DisableOutputBuffer(DAC_Type *DACx)
{
    CLEAR_BIT(DACx->CFGR, DAC_CFGR_BUFEN_Msk);
}

/**
  * @brief    Get DAC Output Buffer Status
  * @rmtoll   CFGR    BUFEN    FL_DAC_IsEnabledOutputBuffer
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsEnabledOutputBuffer(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->CFGR, DAC_CFGR_BUFEN_Msk) == DAC_CFGR_BUFEN_Msk);
}

/**
  * @brief    Set DAC Trigger Source
  * @note     Can Only Be Modified When TRGEN=0
  * @rmtoll   CFGR    TRGSEL    FL_DAC_SetTriggerSource
  * @param    DACx DAC instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_DAC_TRGI_SOFTWARE
  *           @arg @ref FL_DAC_TRGI_ATIM
  *           @arg @ref FL_DAC_TRGI_GPTIM1
  *           @arg @ref FL_DAC_TRGI_GPTIM2
  *           @arg @ref FL_DAC_TRGI_BSTIM16
  *           @arg @ref FL_DAC_TRGI_LPTIM16
  *           @arg @ref FL_DAC_TRGI_EXTI0
  *           @arg @ref FL_DAC_TRGI_EXTI4
  *           @arg @ref FL_DAC_TRGI_EXTI8
  *           @arg @ref FL_DAC_TRGI_EXTI12
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_SetTriggerSource(DAC_Type *DACx, uint32_t source)
{
    MODIFY_REG(DACx->CFGR, DAC_CFGR_TRGSEL_Msk, source);
}

/**
  * @brief    Get DAC Trigger Source
  * @rmtoll   CFGR    TRGSEL    FL_DAC_GetTriggerSource
  * @param    DACx DAC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_DAC_TRGI_SOFTWARE
  *           @arg @ref FL_DAC_TRGI_ATIM
  *           @arg @ref FL_DAC_TRGI_GPTIM1
  *           @arg @ref FL_DAC_TRGI_GPTIM2
  *           @arg @ref FL_DAC_TRGI_BSTIM16
  *           @arg @ref FL_DAC_TRGI_LPTIM16
  *           @arg @ref FL_DAC_TRGI_EXTI0
  *           @arg @ref FL_DAC_TRGI_EXTI4
  *           @arg @ref FL_DAC_TRGI_EXTI8
  *           @arg @ref FL_DAC_TRGI_EXTI12
  */
__STATIC_INLINE uint32_t FL_DAC_GetTriggerSource(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->CFGR, DAC_CFGR_TRGSEL_Msk));
}

/**
  * @brief    Enable DAC DAC Feedback Switch
  * @rmtoll   CFGR    SWIEN    FL_DAC_EnableFeedbackSwitch
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_EnableFeedbackSwitch(DAC_Type *DACx)
{
    SET_BIT(DACx->CFGR, DAC_CFGR_SWIEN_Msk);
}

/**
  * @brief    Disable DAC DAC Feedback Switch
  * @rmtoll   CFGR    SWIEN    FL_DAC_DisableFeedbackSwitch
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_DisableFeedbackSwitch(DAC_Type *DACx)
{
    CLEAR_BIT(DACx->CFGR, DAC_CFGR_SWIEN_Msk);
}

/**
  * @brief    Get DAC Feedback Switch
  * @rmtoll   CFGR    SWIEN    FL_DAC_IsEnabledFeedbackSwitch
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsEnabledFeedbackSwitch(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->CFGR, DAC_CFGR_SWIEN_Msk) == DAC_CFGR_SWIEN_Msk);
}

/**
  * @brief    Trigger DAC
  * @rmtoll   SWTRGR    SWTRIG    FL_DAC_EnableSoftwareTrigger
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_EnableSoftwareTrigger(DAC_Type *DACx)
{
    SET_BIT(DACx->SWTRGR, DAC_SWTRGR_SWTRIG_Msk);
}

/**
  * @brief    Write DAC Data
  * @rmtoll   DHR    DHR    FL_DAC_WriteData
  * @param    DACx DAC instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_WriteData(DAC_Type *DACx, uint32_t data)
{
    MODIFY_REG(DACx->DHR, (0xfffU << 0U), (data << 0U));
}

/**
  * @brief    Read DAC Data
  * @rmtoll   DHR    DHR    FL_DAC_ReadData
  * @param    DACx DAC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_DAC_ReadData(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->DHR, 0xfffU) >> 0U);
}

/**
  * @brief    Enable DAC DMA Error interrupt
  * @rmtoll   IER    DMAE_IE    FL_DAC_EnableIT_DMAError
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_EnableIT_DMAError(DAC_Type *DACx)
{
    SET_BIT(DACx->IER, DAC_IER_DMAE_IE_Msk);
}

/**
  * @brief    Disable DAC DMA Error interrupt
  * @rmtoll   IER    DMAE_IE    FL_DAC_DisableIT_DMAError
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_DisableIT_DMAError(DAC_Type *DACx)
{
    CLEAR_BIT(DACx->IER, DAC_IER_DMAE_IE_Msk);
}

/**
  * @brief    Get DAC DMA Error interrupt Enable Status
  * @rmtoll   IER    DMAE_IE    FL_DAC_IsEnabledIT_DMAError
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsEnabledIT_DMAError(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->IER, DAC_IER_DMAE_IE_Msk) == DAC_IER_DMAE_IE_Msk);
}

/**
  * @brief    Enable DAC End Of Holding Phase Interrupt
  * @rmtoll   IER    EOH_IE    FL_DAC_EnableIT_EndOfHolding
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_EnableIT_EndOfHolding(DAC_Type *DACx)
{
    SET_BIT(DACx->IER, DAC_IER_EOH_IE_Msk);
}

/**
  * @brief    Disable DAC End Of Holding Phase Interrupt
  * @rmtoll   IER    EOH_IE    FL_DAC_DisableIT_EndOfHolding
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_DisableIT_EndOfHolding(DAC_Type *DACx)
{
    CLEAR_BIT(DACx->IER, DAC_IER_EOH_IE_Msk);
}

/**
  * @brief    Get  DAC End Of Holding Phase Interrupt Enable Status
  * @rmtoll   IER    EOH_IE    FL_DAC_IsEnabledIT_EndOfHolding
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsEnabledIT_EndOfHolding(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->IER, DAC_IER_EOH_IE_Msk) == DAC_IER_EOH_IE_Msk);
}

/**
  * @brief    Enable DAC End Of Sampling Phase Interrupt
  * @rmtoll   IER    EOS_IE    FL_DAC_EnableIT_EndOfSampling
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_EnableIT_EndOfSampling(DAC_Type *DACx)
{
    SET_BIT(DACx->IER, DAC_IER_EOS_IE_Msk);
}

/**
  * @brief    Disable DAC End Of Sampling Phase Interrupt
  * @rmtoll   IER    EOS_IE    FL_DAC_DisableIT_EndOfSampling
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_DisableIT_EndOfSampling(DAC_Type *DACx)
{
    CLEAR_BIT(DACx->IER, DAC_IER_EOS_IE_Msk);
}

/**
  * @brief    Get DAC End Of Sampling Phase Interrupt Enable Status
  * @rmtoll   IER    EOS_IE    FL_DAC_IsEnabledIT_EndOfSampling
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsEnabledIT_EndOfSampling(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->IER, DAC_IER_EOS_IE_Msk) == DAC_IER_EOS_IE_Msk);
}

/**
  * @brief    Enable DAC Data Output Updated Interrupt
  * @rmtoll   IER    DOU_IE    FL_DAC_EnableIT_DataOutputUpdate
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_EnableIT_DataOutputUpdate(DAC_Type *DACx)
{
    SET_BIT(DACx->IER, DAC_IER_DOU_IE_Msk);
}

/**
  * @brief    Disable DAC Data Output Updated Interrupt
  * @rmtoll   IER    DOU_IE    FL_DAC_DisableIT_DataOutputUpdate
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_DisableIT_DataOutputUpdate(DAC_Type *DACx)
{
    CLEAR_BIT(DACx->IER, DAC_IER_DOU_IE_Msk);
}

/**
  * @brief    Get DAC Data Output Updated Interrupt Enable Status
  * @rmtoll   IER    DOU_IE    FL_DAC_IsEnabledIT_DataOutputUpdate
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsEnabledIT_DataOutputUpdate(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->IER, DAC_IER_DOU_IE_Msk) == DAC_IER_DOU_IE_Msk);
}

/**
  * @brief    Get DAC DMA Error Flag
  * @rmtoll   ISR    DMAERR    FL_DAC_IsActiveFlag_DMAError
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsActiveFlag_DMAError(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->ISR, DAC_ISR_DMAERR_Msk) == (DAC_ISR_DMAERR_Msk));
}

/**
  * @brief    Clear DAC DMA Error Flag
  * @rmtoll   ISR    DMAERR    FL_DAC_ClearFlag_DMAError
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_ClearFlag_DMAError(DAC_Type *DACx)
{
    WRITE_REG(DACx->ISR, DAC_ISR_DMAERR_Msk);
}

/**
  * @brief    Get DAC End Of Holding Phase Flag
  * @rmtoll   ISR    EOH    FL_DAC_IsActiveFlag_EndOfHolding
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsActiveFlag_EndOfHolding(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->ISR, DAC_ISR_EOH_Msk) == (DAC_ISR_EOH_Msk));
}

/**
  * @brief    Clear DAC End Of Holding Phase Flag
  * @rmtoll   ISR    EOH    FL_DAC_ClearFlag_EndOfHolding
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_ClearFlag_EndOfHolding(DAC_Type *DACx)
{
    WRITE_REG(DACx->ISR, DAC_ISR_EOH_Msk);
}

/**
  * @brief    Get DAC End Of Sampling Phase Flag
  * @rmtoll   ISR    EOS    FL_DAC_IsActiveFlag_EndOfSampling
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsActiveFlag_EndOfSampling(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->ISR, DAC_ISR_EOS_Msk) == (DAC_ISR_EOS_Msk));
}

/**
  * @brief    Clear DAC End Of Sampling Phase Flag
  * @rmtoll   ISR    EOS    FL_DAC_ClearFlag_EndOfSampling
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_ClearFlag_EndOfSampling(DAC_Type *DACx)
{
    WRITE_REG(DACx->ISR, DAC_ISR_EOS_Msk);
}

/**
  * @brief    Get DAC Data Output Updated Flag
  * @rmtoll   ISR    DOU    FL_DAC_IsActiveFlag_DataOutputUpdate
  * @param    DACx DAC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DAC_IsActiveFlag_DataOutputUpdate(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->ISR, DAC_ISR_DOU_Msk) == (DAC_ISR_DOU_Msk));
}

/**
  * @brief    Clear DAC Data Output Updated Flag
  * @rmtoll   ISR    DOU    FL_DAC_ClearFlag_DataOutputUpdate
  * @param    DACx DAC instance
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_ClearFlag_DataOutputUpdate(DAC_Type *DACx)
{
    WRITE_REG(DACx->ISR, DAC_ISR_DOU_Msk);
}

/**
  * @brief    Set DAC Holding Time
  * @note     Modification IS NOT ALLOWED When SHEN=1
  * @rmtoll   SHTR    THLD    FL_DAC_WriteHoldingTime
  * @param    DACx DAC instance
  * @param    time
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_WriteHoldingTime(DAC_Type *DACx, uint32_t time)
{
    MODIFY_REG(DACx->SHTR, (0xffffU << 8U), (time << 8U));
}

/**
  * @brief    Read DAC Holding Time
  * @rmtoll   SHTR    THLD    FL_DAC_ReadHoldingTime
  * @param    DACx DAC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_DAC_ReadHoldingTime(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->SHTR, 0xffffU) >> 8U);
}

/**
  * @brief    Set DAC Sampling Time Under Sample&Hold Mode
  * @note     Modification IS NOT ALLOWED When SHEN=1
  * @rmtoll   SHTR    TSMPL    FL_DAC_WriteSamplingTime
  * @param    DACx DAC instance
  * @param    time
  * @retval   None
  */
__STATIC_INLINE void FL_DAC_WriteSamplingTime(DAC_Type *DACx, uint32_t time)
{
    MODIFY_REG(DACx->SHTR, (0xffU << 0U), (time << 0U));
}

/**
  * @brief    Read DAC Sampling Time Under Sample&Hold Mode
  * @rmtoll   SHTR    TSMPL    FL_DAC_ReadSamplingTime
  * @param    DACx DAC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_DAC_ReadSamplingTime(DAC_Type *DACx)
{
    return (uint32_t)(READ_BIT(DACx->SHTR, 0xffU) >> 0U);
}


/**
  * @}
  */

/** @defgroup DAC_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus  FL_DAC_DeInit(DAC_Type *DACx);
FL_ErrorStatus FL_DAC_Init(DAC_Type *DACx, FL_DAC_InitTypeDef  *DAC_InitStruct);
void FL_DAC_StructInit(FL_DAC_InitTypeDef *DAC_InitStruct);

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

#endif /* __FM33LG0XX_FL_DAC_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-12*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
