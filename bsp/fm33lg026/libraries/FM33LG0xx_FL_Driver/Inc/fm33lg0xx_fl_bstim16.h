/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_bstim16.h
  * @author  FMSH Application Team
  * @brief   Head file of BSTIM16 FL Module
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
#ifndef __FM33LG0XX_FL_BSTIM16_H
#define __FM33LG0XX_FL_BSTIM16_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup BSTIM16 BSTIM16
  * @brief BSTIM16 FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup BSTIM16_FL_ES_INIT BSTIM16 Exported Init structures
  * @{
  */

/**
  * @brief FL BSTIM16 Init Sturcture definition
  */

typedef struct
{
    /* 预分频系数 */
    uint32_t prescaler;
    /* 自动重装载值 */
    uint32_t autoReload;
    /* 自动重装载值 */
    uint32_t autoReloadState;

    uint32_t clockSource;

} FL_BSTIM16_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup BSTIM16_FL_Exported_Constants BSTIM16 Exported Constants
  * @{
  */

#define    BSTIM16_CR1_ARPE_Pos                                   (7U)
#define    BSTIM16_CR1_ARPE_Msk                                   (0x1U << BSTIM16_CR1_ARPE_Pos)
#define    BSTIM16_CR1_ARPE                                       BSTIM16_CR1_ARPE_Msk

#define    BSTIM16_CR1_OPM_Pos                                    (3U)
#define    BSTIM16_CR1_OPM_Msk                                    (0x1U << BSTIM16_CR1_OPM_Pos)
#define    BSTIM16_CR1_OPM                                        BSTIM16_CR1_OPM_Msk

#define    BSTIM16_CR1_URS_Pos                                    (2U)
#define    BSTIM16_CR1_URS_Msk                                    (0x1U << BSTIM16_CR1_URS_Pos)
#define    BSTIM16_CR1_URS                                        BSTIM16_CR1_URS_Msk

#define    BSTIM16_CR1_UDIS_Pos                                   (1U)
#define    BSTIM16_CR1_UDIS_Msk                                   (0x1U << BSTIM16_CR1_UDIS_Pos)
#define    BSTIM16_CR1_UDIS                                       BSTIM16_CR1_UDIS_Msk

#define    BSTIM16_CR1_CEN_Pos                                    (0U)
#define    BSTIM16_CR1_CEN_Msk                                    (0x1U << BSTIM16_CR1_CEN_Pos)
#define    BSTIM16_CR1_CEN                                        BSTIM16_CR1_CEN_Msk

#define    BSTIM16_CR2_MMS_Pos                                    (4U)
#define    BSTIM16_CR2_MMS_Msk                                    (0x7U << BSTIM16_CR2_MMS_Pos)
#define    BSTIM16_CR2_MMS                                        BSTIM16_CR2_MMS_Msk

#define    BSTIM16_IER_UIE_Pos                                    (0U)
#define    BSTIM16_IER_UIE_Msk                                    (0x1U << BSTIM16_IER_UIE_Pos)
#define    BSTIM16_IER_UIE                                        BSTIM16_IER_UIE_Msk

#define    BSTIM16_ISR_UIF_Pos                                    (0U)
#define    BSTIM16_ISR_UIF_Msk                                    (0x1U << BSTIM16_ISR_UIF_Pos)
#define    BSTIM16_ISR_UIF                                        BSTIM16_ISR_UIF_Msk

#define    BSTIM16_EGR_UG_Pos                                     (0U)
#define    BSTIM16_EGR_UG_Msk                                     (0x1U << BSTIM16_EGR_UG_Pos)
#define    BSTIM16_EGR_UG                                         BSTIM16_EGR_UG_Msk






#define    FL_BSTIM16_ONE_PULSE_MODE_CONTINUOUS                   (0x0U << BSTIM16_CR1_OPM_Pos)
#define    FL_BSTIM16_ONE_PULSE_MODE_SINGLE                       (0x1U << BSTIM16_CR1_OPM_Pos)


#define    FL_BSTIM16_UPDATE_SOURCE_REGULAR                       (0x0U << BSTIM16_CR1_URS_Pos)
#define    FL_BSTIM16_UPDATE_SOURCE_COUNTER                       (0x1U << BSTIM16_CR1_URS_Pos)


#define    FL_BSTIM16_TRGO_UG                                     (0x0U << BSTIM16_CR2_MMS_Pos)
#define    FL_BSTIM16_TRGO_ENABLE                                 (0x1U << BSTIM16_CR2_MMS_Pos)
#define    FL_BSTIM16_TRGO_UPDATE                                 (0x2U << BSTIM16_CR2_MMS_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup BSTIM16_FL_Exported_Functions BSTIM16 Exported Functions
  * @{
  */

/**
  * @brief    Auto-Reload preload enable
  * @rmtoll   CR1    ARPE    FL_BSTIM16_EnableARRPreload
  * @param    BSTIM16x BSTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_EnableARRPreload(BSTIM16_Type *BSTIM16x)
{
    SET_BIT(BSTIM16x->CR1, BSTIM16_CR1_ARPE_Msk);
}

/**
  * @brief    Get Auto-Reload preload enable status
  * @rmtoll   CR1    ARPE    FL_BSTIM16_IsEnabledARRPreload
  * @param    BSTIM16x BSTIM16 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_BSTIM16_IsEnabledARRPreload(BSTIM16_Type *BSTIM16x)
{
    return (uint32_t)(READ_BIT(BSTIM16x->CR1, BSTIM16_CR1_ARPE_Msk) == BSTIM16_CR1_ARPE_Msk);
}

/**
  * @brief    Auto-Reload preload disable
  * @rmtoll   CR1    ARPE    FL_BSTIM16_DisableARRPreload
  * @param    BSTIM16x BSTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_DisableARRPreload(BSTIM16_Type *BSTIM16x)
{
    CLEAR_BIT(BSTIM16x->CR1, BSTIM16_CR1_ARPE_Msk);
}

/**
  * @brief    Set one pulse mode
  * @rmtoll   CR1    OPM    FL_BSTIM16_SetOnePulseMode
  * @param    BSTIM16x BSTIM16 instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_BSTIM16_ONE_PULSE_MODE_CONTINUOUS
  *           @arg @ref FL_BSTIM16_ONE_PULSE_MODE_SINGLE
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_SetOnePulseMode(BSTIM16_Type *BSTIM16x, uint32_t mode)
{
    MODIFY_REG(BSTIM16x->CR1, BSTIM16_CR1_OPM_Msk, mode);
}

/**
  * @brief    Get one pulse mode
  * @rmtoll   CR1    OPM    FL_BSTIM16_GetOnePulseMode
  * @param    BSTIM16x BSTIM16 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_BSTIM16_ONE_PULSE_MODE_CONTINUOUS
  *           @arg @ref FL_BSTIM16_ONE_PULSE_MODE_SINGLE
  */
__STATIC_INLINE uint32_t FL_BSTIM16_GetOnePulseMode(BSTIM16_Type *BSTIM16x)
{
    return (uint32_t)(READ_BIT(BSTIM16x->CR1, BSTIM16_CR1_OPM_Msk));
}

/**
  * @brief    Set update request
  * @rmtoll   CR1    URS    FL_BSTIM16_SetUpdateSource
  * @param    BSTIM16x BSTIM16 instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_BSTIM16_UPDATE_SOURCE_REGULAR
  *           @arg @ref FL_BSTIM16_UPDATE_SOURCE_COUNTER
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_SetUpdateSource(BSTIM16_Type *BSTIM16x, uint32_t source)
{
    MODIFY_REG(BSTIM16x->CR1, BSTIM16_CR1_URS_Msk, source);
}

/**
  * @brief    Get update request status
  * @rmtoll   CR1    URS    FL_BSTIM16_GetUpdateSource
  * @param    BSTIM16x BSTIM16 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_BSTIM16_UPDATE_SOURCE_REGULAR
  *           @arg @ref FL_BSTIM16_UPDATE_SOURCE_COUNTER
  */
__STATIC_INLINE uint32_t FL_BSTIM16_GetUpdateSource(BSTIM16_Type *BSTIM16x)
{
    return (uint32_t)(READ_BIT(BSTIM16x->CR1, BSTIM16_CR1_URS_Msk));
}

/**
  * @brief    Update event enable
  * @rmtoll   CR1    UDIS    FL_BSTIM16_EnableUpdateEvent
  * @param    BSTIM16x BSTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_EnableUpdateEvent(BSTIM16_Type *BSTIM16x)
{
    CLEAR_BIT(BSTIM16x->CR1, BSTIM16_CR1_UDIS_Msk);
}

/**
  * @brief    Get update event disable status
  * @rmtoll   CR1    UDIS    FL_BSTIM16_IsEnabledUpdateEvent
  * @param    BSTIM16x BSTIM16 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_BSTIM16_IsEnabledUpdateEvent(BSTIM16_Type *BSTIM16x)
{
    return (uint32_t)!(READ_BIT(BSTIM16x->CR1, BSTIM16_CR1_UDIS_Msk) == BSTIM16_CR1_UDIS_Msk);
}

/**
  * @brief    Update event disable
  * @rmtoll   CR1    UDIS    FL_BSTIM16_DisableUpdateEvent
  * @param    BSTIM16x BSTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_DisableUpdateEvent(BSTIM16_Type *BSTIM16x)
{
    SET_BIT(BSTIM16x->CR1, BSTIM16_CR1_UDIS_Msk);
}

/**
  * @brief    Counter enable
  * @rmtoll   CR1    CEN    FL_BSTIM16_Enable
  * @param    BSTIM16x BSTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_Enable(BSTIM16_Type *BSTIM16x)
{
    SET_BIT(BSTIM16x->CR1, BSTIM16_CR1_CEN_Msk);
}

/**
  * @brief    Get counter enable status
  * @rmtoll   CR1    CEN    FL_BSTIM16_IsEnabled
  * @param    BSTIM16x BSTIM16 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_BSTIM16_IsEnabled(BSTIM16_Type *BSTIM16x)
{
    return (uint32_t)(READ_BIT(BSTIM16x->CR1, BSTIM16_CR1_CEN_Msk) == BSTIM16_CR1_CEN_Msk);
}

/**
  * @brief    Counter disable
  * @rmtoll   CR1    CEN    FL_BSTIM16_Disable
  * @param    BSTIM16x BSTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_Disable(BSTIM16_Type *BSTIM16x)
{
    CLEAR_BIT(BSTIM16x->CR1, BSTIM16_CR1_CEN_Msk);
}

/**
  * @brief    Set master Trigger Output mode
  * @rmtoll   CR2    MMS    FL_BSTIM16_SetTriggerOutput
  * @param    BSTIM16x BSTIM16 instance
  * @param    triggerOutput This parameter can be one of the following values:
  *           @arg @ref FL_BSTIM16_TRGO_UG
  *           @arg @ref FL_BSTIM16_TRGO_ENABLE
  *           @arg @ref FL_BSTIM16_TRGO_UPDATE
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_SetTriggerOutput(BSTIM16_Type *BSTIM16x, uint32_t triggerOutput)
{
    MODIFY_REG(BSTIM16x->CR2, BSTIM16_CR2_MMS_Msk, triggerOutput);
}

/**
  * @brief    Get  master Trigger Output mode
  * @rmtoll   CR2    MMS    FL_BSTIM16_GetTriggerOutput
  * @param    BSTIM16x BSTIM16 instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_BSTIM16_TRGO_UG
  *           @arg @ref FL_BSTIM16_TRGO_ENABLE
  *           @arg @ref FL_BSTIM16_TRGO_UPDATE
  */
__STATIC_INLINE uint32_t FL_BSTIM16_GetTriggerOutput(BSTIM16_Type *BSTIM16x)
{
    return (uint32_t)(READ_BIT(BSTIM16x->CR2, BSTIM16_CR2_MMS_Msk));
}

/**
  * @brief    Update event interrupt disable
  * @rmtoll   IER    UIE    FL_BSTIM16_DisableIT_Update
  * @param    BSTIM16x BSTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_DisableIT_Update(BSTIM16_Type *BSTIM16x)
{
    CLEAR_BIT(BSTIM16x->IER, BSTIM16_IER_UIE_Msk);
}

/**
  * @brief    Update event interrupt enable
  * @rmtoll   IER    UIE    FL_BSTIM16_EnableIT_Update
  * @param    BSTIM16x BSTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_EnableIT_Update(BSTIM16_Type *BSTIM16x)
{
    SET_BIT(BSTIM16x->IER, BSTIM16_IER_UIE_Msk);
}

/**
  * @brief    Get update event interrupt enable status
  * @rmtoll   IER    UIE    FL_BSTIM16_IsEnabledIT_Update
  * @param    BSTIM16x BSTIM16 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_BSTIM16_IsEnabledIT_Update(BSTIM16_Type *BSTIM16x)
{
    return (uint32_t)(READ_BIT(BSTIM16x->IER, BSTIM16_IER_UIE_Msk) == BSTIM16_IER_UIE_Msk);
}

/**
  * @brief    Get update event interrupt flag
  * @rmtoll   ISR    UIF    FL_BSTIM16_IsActiveFlag_Update
  * @param    BSTIM16x BSTIM16 instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_BSTIM16_IsActiveFlag_Update(BSTIM16_Type *BSTIM16x)
{
    return (uint32_t)(READ_BIT(BSTIM16x->ISR, BSTIM16_ISR_UIF_Msk) == (BSTIM16_ISR_UIF_Msk));
}

/**
  * @brief    Clear update event interrupt flag
  * @rmtoll   ISR    UIF    FL_BSTIM16_ClearFlag_Update
  * @param    BSTIM16x BSTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_ClearFlag_Update(BSTIM16_Type *BSTIM16x)
{
    WRITE_REG(BSTIM16x->ISR, BSTIM16_ISR_UIF_Msk);
}

/**
  * @brief    Software update event enable
  * @rmtoll   EGR    UG    FL_BSTIM16_GenerateUpdateEvent
  * @param    BSTIM16x BSTIM16 instance
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_GenerateUpdateEvent(BSTIM16_Type *BSTIM16x)
{
    SET_BIT(BSTIM16x->EGR, BSTIM16_EGR_UG_Msk);
}

/**
  * @brief    Set counter value
  * @rmtoll   CNT        FL_BSTIM16_WriteCounter
  * @param    BSTIM16x BSTIM16 instance
  * @param    count
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_WriteCounter(BSTIM16_Type *BSTIM16x, uint32_t count)
{
    MODIFY_REG(BSTIM16x->CNT, (0xffffU << 0U), (count << 0U));
}

/**
  * @brief    Get counter value
  * @rmtoll   CNT        FL_BSTIM16_ReadCounter
  * @param    BSTIM16x BSTIM16 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_BSTIM16_ReadCounter(BSTIM16_Type *BSTIM16x)
{
    return (uint32_t)(READ_BIT(BSTIM16x->CNT, 0xffffU) >> 0U);
}

/**
  * @brief    Set counter Clock prescaler value
  * @rmtoll   PSC        FL_BSTIM16_WritePrescaler
  * @param    BSTIM16x BSTIM16 instance
  * @param    psc
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_WritePrescaler(BSTIM16_Type *BSTIM16x, uint32_t psc)
{
    MODIFY_REG(BSTIM16x->PSC, (0xffffU << 0U), (psc << 0U));
}

/**
  * @brief    Get counter Clock prescaler value
  * @rmtoll   PSC        FL_BSTIM16_ReadPrescaler
  * @param    BSTIM16x BSTIM16 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_BSTIM16_ReadPrescaler(BSTIM16_Type *BSTIM16x)
{
    return (uint32_t)(READ_BIT(BSTIM16x->PSC, 0xffffU) >> 0U);
}

/**
  * @brief    Set Auto-Reload register value
  * @rmtoll   ARR        FL_BSTIM16_WriteAutoReload
  * @param    BSTIM16x BSTIM16 instance
  * @param    value
  * @retval   None
  */
__STATIC_INLINE void FL_BSTIM16_WriteAutoReload(BSTIM16_Type *BSTIM16x, uint32_t value)
{
    MODIFY_REG(BSTIM16x->ARR, (0xffffU << 0U), (value << 0U));
}

/**
  * @brief    Get  Auto-Reload register value
  * @rmtoll   ARR        FL_BSTIM16_ReadAutoReload
  * @param    BSTIM16x BSTIM16 instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_BSTIM16_ReadAutoReload(BSTIM16_Type *BSTIM16x)
{
    return (uint32_t)(READ_BIT(BSTIM16x->ARR, 0xffffU) >> 0U);
}

/**
  * @}
  */

/** @defgroup BSTIM16_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

FL_ErrorStatus FL_BSTIM16_DeInit(BSTIM16_Type *BSTIM16x);
FL_ErrorStatus FL_BSTIM16_Init(BSTIM16_Type *BSTIM16x, FL_BSTIM16_InitTypeDef *init);
void FL_BSTIM16_StructInit(FL_BSTIM16_InitTypeDef *init);

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

#endif /* __FM33LG0XX_FL_BSTIM16_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-12*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
