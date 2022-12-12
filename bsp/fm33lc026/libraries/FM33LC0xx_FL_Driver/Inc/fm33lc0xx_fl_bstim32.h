/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_bstim32.h
  * @author  FMSH Application Team
  * @brief   Head file of BSTIM32 FL Module
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
#ifndef __FM33LC0XX_FL_BSTIM32_H
#define __FM33LC0XX_FL_BSTIM32_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup BSTIM32 BSTIM32
  * @brief BSTIM32 FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup BSTIM32_FL_ES_INIT BSTIM32 Exported Init structures
  * @{
  */

/**
  * @brief BSTIM32 Init Sturcture Definition
  */

typedef struct
{
    /* 预分频系数 */
    uint32_t prescaler;

    /* 自动重装载值 */
    uint32_t autoReload;

    /* 自动重装载值 */
    uint32_t autoReloadState;

    /* 时钟源 */
    uint32_t clockSource;

} FL_BSTIM32_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup BSTIM32_FL_Exported_Constants BSTIM32 Exported Constants
  * @{
  */

#define    BSTIM32_CR1_ARPE_Pos                                   (7U)
#define    BSTIM32_CR1_ARPE_Msk                                   (0x1U << BSTIM32_CR1_ARPE_Pos)
#define    BSTIM32_CR1_ARPE                                       BSTIM32_CR1_ARPE_Msk

#define    BSTIM32_CR1_OPM_Pos                                    (3U)
#define    BSTIM32_CR1_OPM_Msk                                    (0x1U << BSTIM32_CR1_OPM_Pos)
#define    BSTIM32_CR1_OPM                                        BSTIM32_CR1_OPM_Msk

#define    BSTIM32_CR1_URS_Pos                                    (2U)
#define    BSTIM32_CR1_URS_Msk                                    (0x1U << BSTIM32_CR1_URS_Pos)
#define    BSTIM32_CR1_URS                                        BSTIM32_CR1_URS_Msk

#define    BSTIM32_CR1_UDIS_Pos                                   (1U)
#define    BSTIM32_CR1_UDIS_Msk                                   (0x1U << BSTIM32_CR1_UDIS_Pos)
#define    BSTIM32_CR1_UDIS                                       BSTIM32_CR1_UDIS_Msk

#define    BSTIM32_CR1_CEN_Pos                                    (0U)
#define    BSTIM32_CR1_CEN_Msk                                    (0x1U << BSTIM32_CR1_CEN_Pos)
#define    BSTIM32_CR1_CEN                                        BSTIM32_CR1_CEN_Msk

#define    BSTIM32_CR2_MMS_Pos                                    (4U)
#define    BSTIM32_CR2_MMS_Msk                                    (0x7U << BSTIM32_CR2_MMS_Pos)
#define    BSTIM32_CR2_MMS                                        BSTIM32_CR2_MMS_Msk

#define    BSTIM32_IER_UIE_Pos                                    (0U)
#define    BSTIM32_IER_UIE_Msk                                    (0x1U << BSTIM32_IER_UIE_Pos)
#define    BSTIM32_IER_UIE                                        BSTIM32_IER_UIE_Msk

#define    BSTIM32_ISR_UIF_Pos                                    (0U)
#define    BSTIM32_ISR_UIF_Msk                                    (0x1U << BSTIM32_ISR_UIF_Pos)
#define    BSTIM32_ISR_UIF                                        BSTIM32_ISR_UIF_Msk

#define    BSTIM32_EGR_UG_Pos                                     (0U)
#define    BSTIM32_EGR_UG_Msk                                     (0x1U << BSTIM32_EGR_UG_Pos)
#define    BSTIM32_EGR_UG                                         BSTIM32_EGR_UG_Msk






#define    FL_BSTIM32_ONE_PULSE_MODE_CONTINUOUS                   (0x0U << BSTIM32_CR1_OPM_Pos)
#define    FL_BSTIM32_ONE_PULSE_MODE_SINGLE                       (0x1U << BSTIM32_CR1_OPM_Pos)


#define    FL_BSTIM32_UPDATE_SOURCE_REGULAR                       (0x0U << BSTIM32_CR1_URS_Pos)
#define    FL_BSTIM32_UPDATE_SOURCE_COUNTER                       (0x1U << BSTIM32_CR1_URS_Pos)


#define    FL_BSTIM32_TRGO_UG                                     (0x0U << BSTIM32_CR2_MMS_Pos)
#define    FL_BSTIM32_TRGO_ENABLE                                 (0x1U << BSTIM32_CR2_MMS_Pos)
#define    FL_BSTIM32_TRGO_UPDATE                                 (0x2U << BSTIM32_CR2_MMS_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup BSTIM32_FL_Exported_Functions BSTIM32 Exported Functions
  * @{
  */

/**
  * @brief    Auto-Reload preload enable
  * @rmtoll   CR1    ARPE    FL_BSTIM32_EnableARRPreload
  * @param    BSTIM32x BSTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_EnableARRPreload(BSTIM32_Type *BSTIM32x)
{
    SET_BIT(BSTIM32x->CR1, BSTIM32_CR1_ARPE_Msk);
}

/**
  * @brief    Get Auto-Reload preload enable status
  * @rmtoll   CR1    ARPE    FL_BSTIM32_IsEnabledARRPreload
  * @param    BSTIM32x BSTIM32 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_BSTIM32_IsEnabledARRPreload(BSTIM32_Type *BSTIM32x)
{
    return (uint32_t)(READ_BIT(BSTIM32x->CR1, BSTIM32_CR1_ARPE_Msk) == BSTIM32_CR1_ARPE_Msk);
}

/**
  * @brief    Auto-Reload preload disable
  * @rmtoll   CR1    ARPE    FL_BSTIM32_DisableARRPreload
  * @param    BSTIM32x BSTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_DisableARRPreload(BSTIM32_Type *BSTIM32x)
{
    CLEAR_BIT(BSTIM32x->CR1, BSTIM32_CR1_ARPE_Msk);
}

/**
  * @brief    Set one pulse mode
  * @rmtoll   CR1    OPM    FL_BSTIM32_SetOnePulseMode
  * @param    BSTIM32x BSTIM32 instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_BSTIM32_ONE_PULSE_MODE_CONTINUOUS
  *           @arg @ref FL_BSTIM32_ONE_PULSE_MODE_SINGLE
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_SetOnePulseMode(BSTIM32_Type *BSTIM32x, uint32_t mode)
{
    MODIFY_REG(BSTIM32x->CR1, BSTIM32_CR1_OPM_Msk, mode);
}

/**
  * @brief    Get one pulse mode
  * @rmtoll   CR1    OPM    FL_BSTIM32_GetOnePulseMode
  * @param    BSTIM32x BSTIM32 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_BSTIM32_ONE_PULSE_MODE_CONTINUOUS
  *           @arg @ref FL_BSTIM32_ONE_PULSE_MODE_SINGLE
  */
__STATIC_INLINE uint32_t FL_BSTIM32_GetOnePulseMode(BSTIM32_Type *BSTIM32x)
{
    return (uint32_t)(READ_BIT(BSTIM32x->CR1, BSTIM32_CR1_OPM_Msk));
}

/**
  * @brief    Set update request
  * @rmtoll   CR1    URS    FL_BSTIM32_SetUpdateSource
  * @param    BSTIM32x BSTIM32 instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_BSTIM32_UPDATE_SOURCE_REGULAR
  *           @arg @ref FL_BSTIM32_UPDATE_SOURCE_COUNTER
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_SetUpdateSource(BSTIM32_Type *BSTIM32x, uint32_t source)
{
    MODIFY_REG(BSTIM32x->CR1, BSTIM32_CR1_URS_Msk, source);
}

/**
  * @brief    Get update request status
  * @rmtoll   CR1    URS    FL_BSTIM32_GetUpdateSource
  * @param    BSTIM32x BSTIM32 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_BSTIM32_UPDATE_SOURCE_REGULAR
  *           @arg @ref FL_BSTIM32_UPDATE_SOURCE_COUNTER
  */
__STATIC_INLINE uint32_t FL_BSTIM32_GetUpdateSource(BSTIM32_Type *BSTIM32x)
{
    return (uint32_t)(READ_BIT(BSTIM32x->CR1, BSTIM32_CR1_URS_Msk));
}

/**
  * @brief    Update event enable
  * @rmtoll   CR1    UDIS    FL_BSTIM32_EnableUpdateEvent
  * @param    BSTIM32x BSTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_EnableUpdateEvent(BSTIM32_Type *BSTIM32x)
{
    CLEAR_BIT(BSTIM32x->CR1, BSTIM32_CR1_UDIS_Msk);
}

/**
  * @brief    Get update event disable status
  * @rmtoll   CR1    UDIS    FL_BSTIM32_IsEnabledUpdateEvent
  * @param    BSTIM32x BSTIM32 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_BSTIM32_IsEnabledUpdateEvent(BSTIM32_Type *BSTIM32x)
{
    return (uint32_t)!(READ_BIT(BSTIM32x->CR1, BSTIM32_CR1_UDIS_Msk) == BSTIM32_CR1_UDIS_Msk);
}

/**
  * @brief    Update event disable
  * @rmtoll   CR1    UDIS    FL_BSTIM32_DisableUpdateEvent
  * @param    BSTIM32x BSTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_DisableUpdateEvent(BSTIM32_Type *BSTIM32x)
{
    CLEAR_BIT(BSTIM32x->CR1, BSTIM32_CR1_UDIS_Msk);
}

/**
  * @brief    Counter enable
  * @rmtoll   CR1    CEN    FL_BSTIM32_Enable
  * @param    BSTIM32x BSTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_Enable(BSTIM32_Type *BSTIM32x)
{
    SET_BIT(BSTIM32x->CR1, BSTIM32_CR1_CEN_Msk);
}

/**
  * @brief    Get counter enable status
  * @rmtoll   CR1    CEN    FL_BSTIM32_IsEnabled
  * @param    BSTIM32x BSTIM32 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_BSTIM32_IsEnabled(BSTIM32_Type *BSTIM32x)
{
    return (uint32_t)(READ_BIT(BSTIM32x->CR1, BSTIM32_CR1_CEN_Msk) == BSTIM32_CR1_CEN_Msk);
}

/**
  * @brief    Counter disable
  * @rmtoll   CR1    CEN    FL_BSTIM32_Disable
  * @param    BSTIM32x BSTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_Disable(BSTIM32_Type *BSTIM32x)
{
    CLEAR_BIT(BSTIM32x->CR1, BSTIM32_CR1_CEN_Msk);
}

/**
  * @brief    Set master mode
  * @rmtoll   CR2    MMS    FL_BSTIM32_SetTriggerOutput
  * @param    BSTIM32x BSTIM32 instance
  * @param    triggerOutput This parameter can be one of the following values:
  *           @arg @ref FL_BSTIM32_TRGO_UG
  *           @arg @ref FL_BSTIM32_TRGO_ENABLE
  *           @arg @ref FL_BSTIM32_TRGO_UPDATE
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_SetTriggerOutput(BSTIM32_Type *BSTIM32x, uint32_t triggerOutput)
{
    MODIFY_REG(BSTIM32x->CR2, BSTIM32_CR2_MMS_Msk, triggerOutput);
}

/**
  * @brief    Get master mode status
  * @rmtoll   CR2    MMS    FL_BSTIM32_GetTriggerOutput
  * @param    BSTIM32x BSTIM32 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_BSTIM32_TRGO_UG
  *           @arg @ref FL_BSTIM32_TRGO_ENABLE
  *           @arg @ref FL_BSTIM32_TRGO_UPDATE
  */
__STATIC_INLINE uint32_t FL_BSTIM32_GetTriggerOutput(BSTIM32_Type *BSTIM32x)
{
    return (uint32_t)(READ_BIT(BSTIM32x->CR2, BSTIM32_CR2_MMS_Msk));
}

/**
  * @brief    Update event interrupt disable
  * @rmtoll   IER    UIE    FL_BSTIM32_DisableIT_Update
  * @param    BSTIM32x BSTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_DisableIT_Update(BSTIM32_Type *BSTIM32x)
{
    CLEAR_BIT(BSTIM32x->IER, BSTIM32_IER_UIE_Msk);
}

/**
  * @brief    Update event interrupt enable
  * @rmtoll   IER    UIE    FL_BSTIM32_EnableIT_Update
  * @param    BSTIM32x BSTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_EnableIT_Update(BSTIM32_Type *BSTIM32x)
{
    SET_BIT(BSTIM32x->IER, BSTIM32_IER_UIE_Msk);
}

/**
  * @brief    Get update event interrupt enable status
  * @rmtoll   IER    UIE    FL_BSTIM32_IsEnabledIT_Update
  * @param    BSTIM32x BSTIM32 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_BSTIM32_IsEnabledIT_Update(BSTIM32_Type *BSTIM32x)
{
    return (uint32_t)(READ_BIT(BSTIM32x->IER, BSTIM32_IER_UIE_Msk) == BSTIM32_IER_UIE_Msk);
}

/**
  * @brief    Get update event interrupt flag
  * @rmtoll   ISR    UIF    FL_BSTIM32_IsActiveFlag_Update
  * @param    BSTIM32x BSTIM32 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_BSTIM32_IsActiveFlag_Update(BSTIM32_Type *BSTIM32x)
{
    return (uint32_t)(READ_BIT(BSTIM32x->ISR, BSTIM32_ISR_UIF_Msk) == (BSTIM32_ISR_UIF_Msk));
}

/**
  * @brief    Clear update event interrupt flag
  * @rmtoll   ISR    UIF    FL_BSTIM32_ClearFlag_Update
  * @param    BSTIM32x BSTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_ClearFlag_Update(BSTIM32_Type *BSTIM32x)
{
    WRITE_REG(BSTIM32x->ISR, BSTIM32_ISR_UIF_Msk);
}

/**
  * @brief    Software update event enable
  * @rmtoll   EGR    UG    FL_BSTIM32_GenerateUpdateEvent
  * @param    BSTIM32x BSTIM32 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_GenerateUpdateEvent(BSTIM32_Type *BSTIM32x)
{
    SET_BIT(BSTIM32x->EGR, BSTIM32_EGR_UG_Msk);
}

/**
  * @brief    Set counter value
  * @rmtoll   CNT        FL_BSTIM32_WriteCounter
  * @param    BSTIM32x BSTIM32 instance
  * @param    cnt
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_WriteCounter(BSTIM32_Type *BSTIM32x, uint32_t cnt)
{
    MODIFY_REG(BSTIM32x->CNT, (0xffffffffU << 0U), (cnt << 0U));
}

/**
  * @brief    Get counter value
  * @rmtoll   CNT        FL_BSTIM32_ReadCounter
  * @param    BSTIM32x BSTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_BSTIM32_ReadCounter(BSTIM32_Type *BSTIM32x)
{
    return (uint32_t)(READ_BIT(BSTIM32x->CNT, 0xffffffffU) >> 0U);
}

/**
  * @brief    Set counter Clock prescaler value
  * @rmtoll   PSC        FL_BSTIM32_WritePrescaler
  * @param    BSTIM32x BSTIM32 instance
  * @param    psc
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_WritePrescaler(BSTIM32_Type *BSTIM32x, uint32_t psc)
{
    MODIFY_REG(BSTIM32x->PSC, (0xffffffffU << 0U), (psc << 0U));
}

/**
  * @brief    Get counter Clock prescaler value
  * @rmtoll   PSC        FL_BSTIM32_ReadPrescaler
  * @param    BSTIM32x BSTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_BSTIM32_ReadPrescaler(BSTIM32_Type *BSTIM32x)
{
    return (uint32_t)(READ_BIT(BSTIM32x->PSC, 0xffffffffU) >> 0U);
}

/**
  * @brief    Set Auto-Reload register value
  * @rmtoll   ARR        FL_BSTIM32_WriteAutoReload
  * @param    BSTIM32x BSTIM32 instance
  * @param    value
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM32_WriteAutoReload(BSTIM32_Type *BSTIM32x, uint32_t value)
{
    MODIFY_REG(BSTIM32x->ARR, (0xffffffffU << 0U), (value << 0U));
}

/**
  * @brief    Get  Auto-Reload register value
  * @rmtoll   ARR        FL_BSTIM32_ReadAutoReload
  * @param    BSTIM32x BSTIM32 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_BSTIM32_ReadAutoReload(BSTIM32_Type *BSTIM32x)
{
    return (uint32_t)(READ_BIT(BSTIM32x->ARR, 0xffffffffU) >> 0U);
}

/**
  * @}
  */

/** @defgroup BSTIM32_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_BSTIM32_DeInit(BSTIM32_Type *BSTIM32x);
FL_ErrorStatus FL_BSTIM32_Init(BSTIM32_Type *BSTIM32x, FL_BSTIM32_InitTypeDef *initStruct);
void FL_BSTIM32_StructInit(FL_BSTIM32_InitTypeDef *initStruct);

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

#endif /* __FM33LC0XX_FL_BSTIM32_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.2 @ 2020-09-23*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
