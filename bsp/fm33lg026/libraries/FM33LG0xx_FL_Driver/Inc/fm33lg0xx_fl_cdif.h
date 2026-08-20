/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_cdif.h
  * @author  FMSH Application Team
  * @brief   Head file of CDIF FL Module
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
#ifndef __FM33LG0XX_FL_CDIF_H
#define __FM33LG0XX_FL_CDIF_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup CDIF CDIF
  * @brief CDIF FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup CDIF_FL_ES_INIT CDIF Exported Init structures
  * @{
  */

/**
  * @brief FL CDIF Init Sturcture definition
  */

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup CDIF_FL_Exported_Constants CDIF Exported Constants
  * @{
  */

#define    CDIF_CR_INTF_IEN_Pos                                   (1U)
#define    CDIF_CR_INTF_IEN_Msk                                   (0x1U << CDIF_CR_INTF_IEN_Pos)
#define    CDIF_CR_INTF_IEN                                       CDIF_CR_INTF_IEN_Msk

#define    CDIF_CR_INTF_OEN_Pos                                   (0U)
#define    CDIF_CR_INTF_OEN_Msk                                   (0x1U << CDIF_CR_INTF_OEN_Pos)
#define    CDIF_CR_INTF_OEN                                       CDIF_CR_INTF_OEN_Msk

#define    CDIF_PRSC_PRSC_Pos                                     (0U)
#define    CDIF_PRSC_PRSC_Msk                                     (0x7U << CDIF_PRSC_PRSC_Pos)
#define    CDIF_PRSC_PRSC                                         CDIF_PRSC_PRSC_Msk



#define    FL_CDIF_PSC_DIV1                                       (0x0U << CDIF_PRSC_PRSC_Pos)
#define    FL_CDIF_PSC_DIV2                                       (0x1U << CDIF_PRSC_PRSC_Pos)
#define    FL_CDIF_PSC_DIV4                                       (0x2U << CDIF_PRSC_PRSC_Pos)
#define    FL_CDIF_PSC_DIV8                                       (0x3U << CDIF_PRSC_PRSC_Pos)
#define    FL_CDIF_PSC_DIV16                                      (0x4U << CDIF_PRSC_PRSC_Pos)
#define    FL_CDIF_PSC_DIV32                                      (0x5U << CDIF_PRSC_PRSC_Pos)
#define    FL_CDIF_PSC_DIV64                                      (0x6U << CDIF_PRSC_PRSC_Pos)
#define    FL_CDIF_PSC_DIV128                                     (0x7U << CDIF_PRSC_PRSC_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup CDIF_FL_Exported_Functions CDIF Exported Functions
  * @{
  */

/**
  * @brief    VAO To CPU input enable
  * @rmtoll   CR    INTF_IEN    FL_CDIF_EnableVAOToCPU
  * @param    CDIFx CDIF instance
  * @retval   None
  */
__STATIC_INLINE void FL_CDIF_EnableVAOToCPU(CDIF_Type *CDIFx)
{
    SET_BIT(CDIFx->CR, CDIF_CR_INTF_IEN_Msk);
}

/**
  * @brief    Get VAO To CPU input enable status
  * @rmtoll   CR    INTF_IEN    FL_CDIF_IsEnabledVAOToCPU
  * @param    CDIFx CDIF instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CDIF_IsEnabledVAOToCPU(CDIF_Type *CDIFx)
{
    return (uint32_t)(READ_BIT(CDIFx->CR, CDIF_CR_INTF_IEN_Msk) == CDIF_CR_INTF_IEN_Msk);
}

/**
  * @brief    VAO To CPU input disable
  * @rmtoll   CR    INTF_IEN    FL_CDIF_DisableVAOToCPU
  * @param    CDIFx CDIF instance
  * @retval   None
  */
__STATIC_INLINE void FL_CDIF_DisableVAOToCPU(CDIF_Type *CDIFx)
{
    CLEAR_BIT(CDIFx->CR, CDIF_CR_INTF_IEN_Msk);
}

/**
  * @brief    CPU To VAO enable
  * @rmtoll   CR    INTF_OEN    FL_CDIF_EnableCPUToVAO
  * @param    CDIFx CDIF instance
  * @retval   None
  */
__STATIC_INLINE void FL_CDIF_EnableCPUToVAO(CDIF_Type *CDIFx)
{
    SET_BIT(CDIFx->CR, CDIF_CR_INTF_OEN_Msk);
}

/**
  * @brief    Get CPU To VAO output enable status
  * @rmtoll   CR    INTF_OEN    FL_CDIF_IsEnabledCPUToVAO
  * @param    CDIFx CDIF instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CDIF_IsEnabledCPUToVAO(CDIF_Type *CDIFx)
{
    return (uint32_t)(READ_BIT(CDIFx->CR, CDIF_CR_INTF_OEN_Msk) == CDIF_CR_INTF_OEN_Msk);
}

/**
  * @brief    CPU To VAO output disable
  * @rmtoll   CR    INTF_OEN    FL_CDIF_DisableCPUToVAO
  * @param    CDIFx CDIF instance
  * @retval   None
  */
__STATIC_INLINE void FL_CDIF_DisableCPUToVAO(CDIF_Type *CDIFx)
{
    CLEAR_BIT(CDIFx->CR, CDIF_CR_INTF_OEN_Msk);
}

/**
  * @brief    Set CDIF prescaler
  * @rmtoll   PRSC    PRSC    FL_CDIF_SetPrescaler
  * @param    CDIFx CDIF instance
  * @param    psc This parameter can be one of the following values:
  *           @arg @ref FL_CDIF_PSC_DIV1
  *           @arg @ref FL_CDIF_PSC_DIV2
  *           @arg @ref FL_CDIF_PSC_DIV4
  *           @arg @ref FL_CDIF_PSC_DIV8
  *           @arg @ref FL_CDIF_PSC_DIV16
  *           @arg @ref FL_CDIF_PSC_DIV32
  *           @arg @ref FL_CDIF_PSC_DIV64
  *           @arg @ref FL_CDIF_PSC_DIV128
  * @retval   None
  */
__STATIC_INLINE void FL_CDIF_SetPrescaler(CDIF_Type *CDIFx, uint32_t psc)
{
    MODIFY_REG(CDIFx->PRSC, CDIF_PRSC_PRSC_Msk, psc);
}

/**
  * @brief    Get CDIF prescaler
  * @rmtoll   PRSC    PRSC    FL_CDIF_GetPrescaler
  * @param    CDIFx CDIF instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CDIF_PSC_DIV1
  *           @arg @ref FL_CDIF_PSC_DIV2
  *           @arg @ref FL_CDIF_PSC_DIV4
  *           @arg @ref FL_CDIF_PSC_DIV8
  *           @arg @ref FL_CDIF_PSC_DIV16
  *           @arg @ref FL_CDIF_PSC_DIV32
  *           @arg @ref FL_CDIF_PSC_DIV64
  *           @arg @ref FL_CDIF_PSC_DIV128
  */
__STATIC_INLINE uint32_t FL_CDIF_GetPrescaler(CDIF_Type *CDIFx)
{
    return (uint32_t)(READ_BIT(CDIFx->PRSC, CDIF_PRSC_PRSC_Msk));
}

/**
  * @}
  */

/** @defgroup CDIF_FL_EF_Init Initialization and de-initialization functions
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

#endif /* __FM33LG0XX_FL_CDIF_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-11*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
