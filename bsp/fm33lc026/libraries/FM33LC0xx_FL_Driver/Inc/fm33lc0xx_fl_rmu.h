/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_rmu.h
  * @author  FMSH Application Team
  * @brief   Head file of RMU FL Module
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
#ifndef __FM33LC0XX_FL_RMU_H
#define __FM33LC0XX_FL_RMU_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup RMU RMU
  * @brief RMU FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup RMU_FL_ES_INIT RMU Exported Init structures
  * @{
  */

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup RMU_FL_Exported_Constants RMU Exported Constants
  * @{
  */

#define    RMU_PDRCR_CFG_Pos                                      (1U)
#define    RMU_PDRCR_CFG_Msk                                      (0x3U << RMU_PDRCR_CFG_Pos)
#define    RMU_PDRCR_CFG                                          RMU_PDRCR_CFG_Msk

#define    RMU_PDRCR_EN_Pos                                       (0U)
#define    RMU_PDRCR_EN_Msk                                       (0x1U << RMU_PDRCR_EN_Pos)
#define    RMU_PDRCR_EN                                           RMU_PDRCR_EN_Msk

#define    RMU_BORCR_CFG_Pos                                      (2U)
#define    RMU_BORCR_CFG_Msk                                      (0x3U << RMU_BORCR_CFG_Pos)
#define    RMU_BORCR_CFG                                          RMU_BORCR_CFG_Msk

#define    RMU_BORCR_OFF_BOR_1P2_Pos                              (0U)
#define    RMU_BORCR_OFF_BOR_1P2_Msk                              (0x1U << RMU_BORCR_OFF_BOR_1P2_Pos)
#define    RMU_BORCR_OFF_BOR_1P2                                  RMU_BORCR_OFF_BOR_1P2_Msk

#define    RMU_BORCR_OFF_BOR_1P0_Pos                              (1U)
#define    RMU_BORCR_OFF_BOR_1P0_Msk                              (0x1U << RMU_BORCR_OFF_BOR_1P0_Pos)
#define    RMU_BORCR_OFF_BOR_1P0                                  RMU_BORCR_OFF_BOR_1P0_Msk






#define    FL_RMU_PDR_THRESHOLD_1P5V                              (0x0U << RMU_PDRCR_CFG_Pos)
#define    FL_RMU_PDR_THRESHOLD_1P25V                             (0x1U << RMU_PDRCR_CFG_Pos)
#define    FL_RMU_PDR_THRESHOLD_1P35V                             (0x2U << RMU_PDRCR_CFG_Pos)
#define    FL_RMU_PDR_THRESHOLD_1P4V                              (0x3U << RMU_PDRCR_CFG_Pos)


#define    FL_RMU_BOR_THRESHOLD_1P7V                              (0x0U << RMU_BORCR_CFG_Pos)
#define    FL_RMU_BOR_THRESHOLD_1P6V                              (0x1U << RMU_BORCR_CFG_Pos)
#define    FL_RMU_BOR_THRESHOLD_1P65V                             (0x2U << RMU_BORCR_CFG_Pos)
#define    FL_RMU_BOR_THRESHOLD_1P75V                             (0x3U << RMU_BORCR_CFG_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup RMU_FL_Exported_Functions RMU Exported Functions
  * @{
  */

/**
  * @brief    Set PDR Power Down Reset Voltage
  * @rmtoll   PDRCR    CFG    FL_RMU_PDR_SetThreshold
  * @param    RMUx RMU instance
  * @param    threshold This parameter can be one of the following values:
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P5V
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P25V
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P35V
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P4V
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_PDR_SetThreshold(RMU_Type *RMUx, uint32_t threshold)
{
    MODIFY_REG(RMUx->PDRCR, RMU_PDRCR_CFG_Msk, threshold);
}

/**
  * @brief    Get PDR Power Down Reset Voltage Setting
  * @rmtoll   PDRCR    CFG    FL_RMU_PDR_GetThreshold
  * @param    RMUx RMU instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P5V
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P25V
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P35V
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P4V
  */
__STATIC_INLINE uint32_t FL_RMU_PDR_GetThreshold(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->PDRCR, RMU_PDRCR_CFG_Msk));
}

/**
  * @brief    Get PDR Power Down Reset Enable Status
  * @rmtoll   PDRCR    EN    FL_RMU_PDR_IsEnabled
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_PDR_IsEnabled(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->PDRCR, RMU_PDRCR_EN_Msk) == RMU_PDRCR_EN_Msk);
}

/**
  * @brief    Disable PDR Power Down Reset
  * @rmtoll   PDRCR    EN    FL_RMU_PDR_Disable
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_PDR_Disable(RMU_Type *RMUx)
{
    CLEAR_BIT(RMUx->PDRCR, RMU_PDRCR_EN_Msk);
}

/**
  * @brief    Enable PDR Power Down Reset
  * @rmtoll   PDRCR    EN    FL_RMU_PDR_Enable
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_PDR_Enable(RMU_Type *RMUx)
{
    SET_BIT(RMUx->PDRCR, RMU_PDRCR_EN_Msk);
}

/**
  * @brief    Set BOR Power Down Reset Voltage
  * @rmtoll   BORCR    CFG    FL_RMU_BOR_SetThreshold
  * @param    RMUx RMU instance
  * @param    threshold This parameter can be one of the following values:
  *           @arg @ref FL_RMU_BOR_THRESHOLD_1P7V
  *           @arg @ref FL_RMU_BOR_THRESHOLD_1P6V
  *           @arg @ref FL_RMU_BOR_THRESHOLD_1P65V
  *           @arg @ref FL_RMU_BOR_THRESHOLD_1P75V
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_BOR_SetThreshold(RMU_Type *RMUx, uint32_t threshold)
{
    MODIFY_REG(RMUx->BORCR, RMU_BORCR_CFG_Msk, threshold);
}

/**
  * @brief    Get BOR Power Down Reset Voltage Setting
  * @rmtoll   BORCR    CFG    FL_RMU_BOR_GetThreshold
  * @param    RMUx RMU instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RMU_BOR_THRESHOLD_1P7V
  *           @arg @ref FL_RMU_BOR_THRESHOLD_1P6V
  *           @arg @ref FL_RMU_BOR_THRESHOLD_1P65V
  *           @arg @ref FL_RMU_BOR_THRESHOLD_1P75V
  */
__STATIC_INLINE uint32_t FL_RMU_BOR_GetThreshold(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->BORCR, RMU_BORCR_CFG_Msk));
}

/**
  * @brief    Get BOR Power Down Reset Enable Status
  * @rmtoll   BORCR    OFF_BOR_1P2    FL_RMU_BORPowerDown_IsEnabled
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_BORPowerDown_IsEnabled(RMU_Type *RMUx)
{
    return (uint32_t)!(READ_BIT(RMUx->BORCR, RMU_BORCR_OFF_BOR_1P2_Msk) == RMU_BORCR_OFF_BOR_1P2_Msk);
}

/**
  * @brief    Disable BOR Power Down Reset
  * @rmtoll   BORCR    OFF_BOR_1P2    FL_RMU_BORPowerDown_Disable
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_BORPowerDown_Disable(RMU_Type *RMUx)
{
    SET_BIT(RMUx->BORCR, RMU_BORCR_OFF_BOR_1P2_Msk);
}

/**
  * @brief    Enable BOR Power Down Reset
  * @rmtoll   BORCR    OFF_BOR_1P2    FL_RMU_BORPowerDown_Enable
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_BORPowerDown_Enable(RMU_Type *RMUx)
{
    CLEAR_BIT(RMUx->BORCR, RMU_BORCR_OFF_BOR_1P2_Msk);
}

/**
  * @brief    Get BOR Power On Reset Enable Status
  * @rmtoll   BORCR    OFF_BOR_1P0    FL_RMU_BORPowerUp_IsEnabled
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_BORPowerUp_IsEnabled(RMU_Type *RMUx)
{
    return (uint32_t)!(READ_BIT(RMUx->BORCR, RMU_BORCR_OFF_BOR_1P0_Msk) == RMU_BORCR_OFF_BOR_1P0_Msk);
}

/**
  * @brief    Disable BOR Power On Reset
  * @rmtoll   BORCR    OFF_BOR_1P0    FL_RMU_BORPowerUp_Disable
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_BORPowerUp_Disable(RMU_Type *RMUx)
{
    SET_BIT(RMUx->BORCR, RMU_BORCR_OFF_BOR_1P0_Msk);
}

/**
  * @brief    Enable BOR Power On Reset
  * @rmtoll   BORCR    OFF_BOR_1P0    FL_RMU_BORPowerUp_Enable
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_BORPowerUp_Enable(RMU_Type *RMUx)
{
    CLEAR_BIT(RMUx->BORCR, RMU_BORCR_OFF_BOR_1P0_Msk);
}

/**
  * @}
  */

/** @defgroup RMU_FL_EF_Init Initialization and de-initialization functions
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

#endif /* __FM33LC0XX_FL_RMU_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.2 @ 2020-09-23*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
