/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_vref.h
  * @author  FMSH Application Team
  * @brief   Head file of VREF FL Module
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
#ifndef __FM33LC0XX_FL_VREF_H
#define __FM33LC0XX_FL_VREF_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup VREF VREF
  * @brief VREF FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup VREF_FL_ES_INIT VREF Exported Init structures
  * @{
  */

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup VREF_FL_Exported_Constants VREF Exported Constants
  * @{
  */

#define    VREF_CR_VREF_EN_Pos                                    (0U)
#define    VREF_CR_VREF_EN_Msk                                    (0x1U << VREF_CR_VREF_EN_Pos)
#define    VREF_CR_VREF_EN                                        VREF_CR_VREF_EN_Msk

#define    VREF_CR_PTAT_EN_Pos                                    (1U)
#define    VREF_CR_PTAT_EN_Msk                                    (0x1U << VREF_CR_PTAT_EN_Pos)
#define    VREF_CR_PTAT_EN                                        VREF_CR_PTAT_EN_Msk

#define    VREF_SR_FLAG_Pos                                       (8U)
#define    VREF_SR_FLAG_Msk                                       (0x1U << VREF_SR_FLAG_Pos)
#define    VREF_SR_FLAG                                           VREF_SR_FLAG_Msk

#define    VREF_SR_RDY_Pos                                        (1U)
#define    VREF_SR_RDY_Msk                                        (0x1U << VREF_SR_RDY_Pos)
#define    VREF_SR_RDY                                            VREF_SR_RDY_Msk

#define    VREF_SR_IF_Pos                                         (0U)
#define    VREF_SR_IF_Msk                                         (0x1U << VREF_SR_IF_Pos)
#define    VREF_SR_IF                                             VREF_SR_IF_Msk

#define    VREF_IER_IE_Pos                                        (0U)
#define    VREF_IER_IE_Msk                                        (0x1U << VREF_IER_IE_Pos)
#define    VREF_IER_IE                                            VREF_IER_IE_Msk

#define    VREF_BUFCR_VPTATBUFFER_OUTEN_Pos                       (3U)
#define    VREF_BUFCR_VPTATBUFFER_OUTEN_Msk                       (0x1U << VREF_BUFCR_VPTATBUFFER_OUTEN_Pos)
#define    VREF_BUFCR_VPTATBUFFER_OUTEN                           VREF_BUFCR_VPTATBUFFER_OUTEN_Msk

#define    VREF_BUFCR_VPTATBUFFER_EN_Pos                          (2U)
#define    VREF_BUFCR_VPTATBUFFER_EN_Msk                          (0x1U << VREF_BUFCR_VPTATBUFFER_EN_Pos)
#define    VREF_BUFCR_VPTATBUFFER_EN                              VREF_BUFCR_VPTATBUFFER_EN_Msk

#define    VREF_BUFCR_VREFBUFFER_OUTEN_Pos                        (1U)
#define    VREF_BUFCR_VREFBUFFER_OUTEN_Msk                        (0x1U << VREF_BUFCR_VREFBUFFER_OUTEN_Pos)
#define    VREF_BUFCR_VREFBUFFER_OUTEN                            VREF_BUFCR_VREFBUFFER_OUTEN_Msk

#define    VREF_BUFCR_VREFBUFFER_EN_Pos                           (0U)
#define    VREF_BUFCR_VREFBUFFER_EN_Msk                           (0x1U << VREF_BUFCR_VREFBUFFER_EN_Pos)
#define    VREF_BUFCR_VREFBUFFER_EN                               VREF_BUFCR_VREFBUFFER_EN_Msk






/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup VREF_FL_Exported_Functions VREF Exported Functions
  * @{
  */

/**
  * @brief    Enable VREF
  * @rmtoll   CR    VREF_EN    FL_VREF_Enable
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_Enable(VREF_Type *VREFx)
{
    SET_BIT(VREFx->CR, VREF_CR_VREF_EN_Msk);
}

/**
  * @brief    Get VREF Enable Status
  * @rmtoll   CR    VREF_EN    FL_VREF_IsEnabled
  * @param    VREFx VREF instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREF_IsEnabled(VREF_Type *VREFx)
{
    return (uint32_t)(READ_BIT(VREFx->CR, VREF_CR_VREF_EN_Msk) == VREF_CR_VREF_EN_Msk);
}

/**
  * @brief    Disable VREF
  * @rmtoll   CR    VREF_EN    FL_VREF_Disable
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_Disable(VREF_Type *VREFx)
{
    CLEAR_BIT(VREFx->CR, VREF_CR_VREF_EN_Msk);
}

/**
  * @brief    Enable Temperatue Sensor
  * @rmtoll   CR    PTAT_EN    FL_VREF_EnableTemperatureSensor
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_EnableTemperatureSensor(VREF_Type *VREFx)
{
    SET_BIT(VREFx->CR, VREF_CR_PTAT_EN_Msk);
}

/**
  * @brief    Get Temperatue Sensor Enable Status
  * @rmtoll   CR    PTAT_EN    FL_VREF_IsEnabledTemperatureSensor
  * @param    VREFx VREF instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREF_IsEnabledTemperatureSensor(VREF_Type *VREFx)
{
    return (uint32_t)(READ_BIT(VREFx->CR, VREF_CR_PTAT_EN_Msk) == VREF_CR_PTAT_EN_Msk);
}

/**
  * @brief    Disable Temperatue Sensor
  * @rmtoll   CR    PTAT_EN    FL_VREF_DisableTemperatureSensor
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_DisableTemperatureSensor(VREF_Type *VREFx)
{
    CLEAR_BIT(VREFx->CR, VREF_CR_PTAT_EN_Msk);
}

/**
  * @brief    Get VREF Setable Flag From Analog
  * @rmtoll   SR    FLAG    FL_VREF_IsActiveFlag_AnalogReady
  * @param    VREFx VREF instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREF_IsActiveFlag_AnalogReady(VREF_Type *VREFx)
{
    return (uint32_t)(READ_BIT(VREFx->SR, VREF_SR_FLAG_Msk) == (VREF_SR_FLAG_Msk));
}

/**
  * @brief    Get VREF Ready Flag
  * @rmtoll   SR    RDY    FL_VREF_IsActiveFlag_DigitalReady
  * @param    VREFx VREF instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREF_IsActiveFlag_DigitalReady(VREF_Type *VREFx)
{
    return (uint32_t)(READ_BIT(VREFx->SR, VREF_SR_RDY_Msk) == (VREF_SR_RDY_Msk));
}

/**
  * @brief    Get VREF Ready Interrupt Flag
  * @rmtoll   SR    IF    FL_VREF_IsActiveFlag_Ready
  * @param    VREFx VREF instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREF_IsActiveFlag_Ready(VREF_Type *VREFx)
{
    return (uint32_t)(READ_BIT(VREFx->SR, VREF_SR_IF_Msk) == (VREF_SR_IF_Msk));
}

/**
  * @brief    Clear VREF Ready Interrupt Flag
  * @rmtoll   SR    IF    FL_VREF_ClearFlag_Ready
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_ClearFlag_Ready(VREF_Type *VREFx)
{
    WRITE_REG(VREFx->SR, VREF_SR_IF_Msk);
}

/**
  * @brief    Enable VREF Ready Interrupt
  * @rmtoll   IER    IE    FL_VREF_EnableIT_Ready
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_EnableIT_Ready(VREF_Type *VREFx)
{
    SET_BIT(VREFx->IER, VREF_IER_IE_Msk);
}

/**
  * @brief    Get VREF Ready Interrupt Enable Status
  * @rmtoll   IER    IE    FL_VREF_IsEnabledIT_Ready
  * @param    VREFx VREF instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREF_IsEnabledIT_Ready(VREF_Type *VREFx)
{
    return (uint32_t)(READ_BIT(VREFx->IER, VREF_IER_IE_Msk) == VREF_IER_IE_Msk);
}

/**
  * @brief    Disable VREF Ready Interrupt
  * @rmtoll   IER    IE    FL_VREF_DisableIT_Ready
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_DisableIT_Ready(VREF_Type *VREFx)
{
    CLEAR_BIT(VREFx->IER, VREF_IER_IE_Msk);
}

/**
  * @brief    Enable VPTAT Buffer Output
  * @rmtoll   BUFCR    VPTATBUFFER_OUTEN    FL_VREF_EnableVPTATBufferOutput
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_EnableVPTATBufferOutput(VREF_Type *VREFx)
{
    SET_BIT(VREFx->BUFCR, VREF_BUFCR_VPTATBUFFER_OUTEN_Msk);
}

/**
  * @brief    Get VPTAT Buffer Output Enable Status
  * @rmtoll   BUFCR    VPTATBUFFER_OUTEN    FL_VREF_IsEnabledVPTATBufferOutput
  * @param    VREFx VREF instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREF_IsEnabledVPTATBufferOutput(VREF_Type *VREFx)
{
    return (uint32_t)(READ_BIT(VREFx->BUFCR, VREF_BUFCR_VPTATBUFFER_OUTEN_Msk) == VREF_BUFCR_VPTATBUFFER_OUTEN_Msk);
}

/**
  * @brief    Disable VPTAT Buffer Output
  * @rmtoll   BUFCR    VPTATBUFFER_OUTEN    FL_VREF_DisableVPTATBufferOutput
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_DisableVPTATBufferOutput(VREF_Type *VREFx)
{
    CLEAR_BIT(VREFx->BUFCR, VREF_BUFCR_VPTATBUFFER_OUTEN_Msk);
}

/**
  * @brief    Enable VPTAT Buffer
  * @rmtoll   BUFCR    VPTATBUFFER_EN    FL_VREF_EnableVPTATBuffer
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_EnableVPTATBuffer(VREF_Type *VREFx)
{
    SET_BIT(VREFx->BUFCR, VREF_BUFCR_VPTATBUFFER_EN_Msk);
}

/**
  * @brief    Get VPTAT Buffer Enable Status
  * @rmtoll   BUFCR    VPTATBUFFER_EN    FL_VREF_IsEnabledVPTATBuffer
  * @param    VREFx VREF instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREF_IsEnabledVPTATBuffer(VREF_Type *VREFx)
{
    return (uint32_t)(READ_BIT(VREFx->BUFCR, VREF_BUFCR_VPTATBUFFER_EN_Msk) == VREF_BUFCR_VPTATBUFFER_EN_Msk);
}

/**
  * @brief    Disable VPTAT Buffer
  * @rmtoll   BUFCR    VPTATBUFFER_EN    FL_VREF_DisableVPTATBuffer
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_DisableVPTATBuffer(VREF_Type *VREFx)
{
    CLEAR_BIT(VREFx->BUFCR, VREF_BUFCR_VPTATBUFFER_EN_Msk);
}

/**
  * @brief    Enable VREF Buffer Output
  * @rmtoll   BUFCR    VREFBUFFER_OUTEN    FL_VREF_EnableVREFBufferOutput
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_EnableVREFBufferOutput(VREF_Type *VREFx)
{
    SET_BIT(VREFx->BUFCR, VREF_BUFCR_VREFBUFFER_OUTEN_Msk);
}

/**
  * @brief    Get VREF Buffer Output Enable Status
  * @rmtoll   BUFCR    VREFBUFFER_OUTEN    FL_VREF_IsEnabledVREFBufferOutput
  * @param    VREFx VREF instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREF_IsEnabledVREFBufferOutput(VREF_Type *VREFx)
{
    return (uint32_t)(READ_BIT(VREFx->BUFCR, VREF_BUFCR_VREFBUFFER_OUTEN_Msk) == VREF_BUFCR_VREFBUFFER_OUTEN_Msk);
}

/**
  * @brief    Disable VREF Buffer Output
  * @rmtoll   BUFCR    VREFBUFFER_OUTEN    FL_VREF_DisableVREFBufferOutput
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_DisableVREFBufferOutput(VREF_Type *VREFx)
{
    CLEAR_BIT(VREFx->BUFCR, VREF_BUFCR_VREFBUFFER_OUTEN_Msk);
}

/**
  * @brief    Enable VREF Buffer
  * @rmtoll   BUFCR    VREFBUFFER_EN    FL_VREF_EnableVREFBuffer
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_EnableVREFBuffer(VREF_Type *VREFx)
{
    SET_BIT(VREFx->BUFCR, VREF_BUFCR_VREFBUFFER_EN_Msk);
}

/**
  * @brief    Get VREF Buffer Enable Status
  * @rmtoll   BUFCR    VREFBUFFER_EN    FL_VREF_IsEnabledVREFBuffer
  * @param    VREFx VREF instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREF_IsEnabledVREFBuffer(VREF_Type *VREFx)
{
    return (uint32_t)(READ_BIT(VREFx->BUFCR, VREF_BUFCR_VREFBUFFER_EN_Msk) == VREF_BUFCR_VREFBUFFER_EN_Msk);
}

/**
  * @brief    Disable VREF Buffer
  * @rmtoll   BUFCR    VREFBUFFER_EN    FL_VREF_DisableVREFBuffer
  * @param    VREFx VREF instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREF_DisableVREFBuffer(VREF_Type *VREFx)
{
    CLEAR_BIT(VREFx->BUFCR, VREF_BUFCR_VREFBUFFER_EN_Msk);
}

/**
  * @}
  */

/** @defgroup VREF_FL_EF_Init Initialization and de-initialization functions
  * @{
  */


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

#endif /* __FM33LC0XX_FL_VREF_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.2 @ 2020-09-23*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
