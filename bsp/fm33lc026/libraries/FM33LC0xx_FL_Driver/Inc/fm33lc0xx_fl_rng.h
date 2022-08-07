/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_rng.h
  * @author  FMSH Application Team
  * @brief   Head file of RNG FL Module
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
#ifndef __FM33LC0XX_FL_RNG_H
#define __FM33LC0XX_FL_RNG_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup RNG RNG
  * @brief RNG FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup RNG_FL_ES_INIT RNG Exported Init structures
  * @{
  */

/**
  * @brief RNG Init Sturcture definition
  */

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup RNG_FL_Exported_Constants RNG Exported Constants
  * @{
  */

#define    RNG_CR_EN_Pos                                          (0U)
#define    RNG_CR_EN_Msk                                          (0x1U << RNG_CR_EN_Pos)
#define    RNG_CR_EN                                              RNG_CR_EN_Msk

#define    RNG_SR_RBUSY_Pos                                       (1U)
#define    RNG_SR_RBUSY_Msk                                       (0x1U << RNG_SR_RBUSY_Pos)
#define    RNG_SR_RBUSY                                           RNG_SR_RBUSY_Msk

#define    RNG_SR_RNF_Pos                                         (0U)
#define    RNG_SR_RNF_Msk                                         (0x1U << RNG_SR_RNF_Pos)
#define    RNG_SR_RNF                                             RNG_SR_RNF_Msk

#define    RNG_CRCCR_CRCEN_Pos                                    (0U)
#define    RNG_CRCCR_CRCEN_Msk                                    (0x1U << RNG_CRCCR_CRCEN_Pos)
#define    RNG_CRCCR_CRCEN                                        RNG_CRCCR_CRCEN_Msk

#define    RNG_CRCSR_CRCDONE_Pos                                  (0U)
#define    RNG_CRCSR_CRCDONE_Msk                                  (0x1U << RNG_CRCSR_CRCDONE_Pos)
#define    RNG_CRCSR_CRCDONE                                      RNG_CRCSR_CRCDONE_Msk






/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup RNG_FL_Exported_Functions RNG Exported Functions
  * @{
  */

/**
  * @brief    RNG enable
  * @rmtoll   CR    EN    FL_RNG_Enable
  * @param    RNGCTLx RNGCTL instance
  * @retval   None
  */
__STATIC_INLINE void FL_RNG_Enable(RNGCTL_Type *RNGCTLx)
{
    SET_BIT(RNGCTLx->CR, RNG_CR_EN_Msk);
}

/**
  * @brief    RNG enable status
  * @rmtoll   CR    EN    FL_RNG_IsEnabled
  * @param    RNGCTLx RNGCTL instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RNG_IsEnabled(RNGCTL_Type *RNGCTLx)
{
    return (uint32_t)(READ_BIT(RNGCTLx->CR, RNG_CR_EN_Msk) == RNG_CR_EN_Msk);
}

/**
  * @brief    RNG disable
  * @rmtoll   CR    EN    FL_RNG_Disable
  * @param    RNGCTLx RNGCTL instance
  * @retval   None
  */
__STATIC_INLINE void FL_RNG_Disable(RNGCTL_Type *RNGCTLx)
{
    CLEAR_BIT(RNGCTLx->CR, RNG_CR_EN_Msk);
}

/**
  * @brief    Read RNG output data register
  * @rmtoll   DOR        FL_RNG_ReadData
  * @param    RNGx RNG instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RNG_ReadData(RNG_Type *RNGx)
{
    return (uint32_t)(READ_BIT(RNGx->DOR, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Get LFSR Flag
  * @rmtoll   SR    RBUSY    FL_RNG_IsActiveFlag_Busy
  * @param    RNGx RNG instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RNG_IsActiveFlag_Busy(RNG_Type *RNGx)
{
    return (uint32_t)(READ_BIT(RNGx->SR, RNG_SR_RBUSY_Msk) == (RNG_SR_RBUSY_Msk));
}

/**
  * @brief    Get random number fail flag
  * @rmtoll   SR    RNF    FL_RNG_IsActiveFlag_RandomFail
  * @param    RNGx RNG instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RNG_IsActiveFlag_RandomFail(RNG_Type *RNGx)
{
    return (uint32_t)(READ_BIT(RNGx->SR, RNG_SR_RNF_Msk) == (RNG_SR_RNF_Msk));
}

/**
  * @brief    Clear random number fail flag
  * @rmtoll   SR    RNF    FL_RNG_ClearFlag_RandomFail
  * @param    RNGx RNG instance
  * @retval   None
  */
__STATIC_INLINE void FL_RNG_ClearFlag_RandomFail(RNG_Type *RNGx)
{
    WRITE_REG(RNGx->SR, RNG_SR_RNF_Msk);
}

/**
  * @brief    CRC enable
  * @rmtoll   CRCCR    CRCEN    FL_RNG_CRC_Enable
  * @param    RNGx RNG instance
  * @retval   None
  */
__STATIC_INLINE void FL_RNG_CRC_Enable(RNG_Type *RNGx)
{
    SET_BIT(RNGx->CRCCR, RNG_CRCCR_CRCEN_Msk);
}

/**
  * @brief    Get CRC enable status
  * @rmtoll   CRCCR    CRCEN    FL_RNG_CRC_IsEnabled
  * @param    RNGx RNG instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RNG_CRC_IsEnabled(RNG_Type *RNGx)
{
    return (uint32_t)(READ_BIT(RNGx->CRCCR, RNG_CRCCR_CRCEN_Msk) == RNG_CRCCR_CRCEN_Msk);
}

/**
  * @brief    Write CRC data input
  * @rmtoll   CRCDIR        FL_RNG_CRC_WriteData
  * @param    RNGx RNG instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_RNG_CRC_WriteData(RNG_Type *RNGx, uint32_t data)
{
    MODIFY_REG(RNGx->CRCDIR, (0xffffffffU << 0U), (data << 0U));
}

/**
  * @brief    Get CRC calculation done Flag
  * @rmtoll   CRCSR    CRCDONE    FL_RNG_IsActiveFlag_CRCComplete
  * @param    RNGx RNG instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RNG_IsActiveFlag_CRCComplete(RNG_Type *RNGx)
{
    return (uint32_t)(READ_BIT(RNGx->CRCSR, RNG_CRCSR_CRCDONE_Msk) == (RNG_CRCSR_CRCDONE_Msk));
}

/**
  * @brief    Clear CRC calculation done Flag
  * @rmtoll   CRCSR    CRCDONE    FL_RNG_ClearFlag_CRCComplete
  * @param    RNGx RNG instance
  * @retval   None
  */
__STATIC_INLINE void FL_RNG_ClearFlag_CRCComplete(RNG_Type *RNGx)
{
    CLEAR_BIT(RNGx->CRCSR, RNG_CRCSR_CRCDONE_Msk);
}

/**
  * @}
  */

/** @defgroup RNG_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_RNG_DeInit(RNG_Type *RNGx);
FL_ErrorStatus FL_RNG_Init(RNG_Type *RNGx);

/**
  * @}
  */

/** @defgroup RNG_FL_EF_Operation Opeartion functions
  * @{
  */

uint32_t GetRandomNumber(void);
uint32_t GetCrc32(uint32_t dataIn);

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

#endif /* __FM33LC0XX_FL_RNG_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.2 @ 2020-09-23*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
