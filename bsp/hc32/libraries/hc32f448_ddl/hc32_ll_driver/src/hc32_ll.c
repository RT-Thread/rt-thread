/**
 *******************************************************************************
 * @file  hc32_ll.c
 * @brief This file provides firmware functions to low-level drivers (LL).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_Global Global
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup LL_Global_Functions LL Global Functions
 * @{
 */
void LL_PERIPH_WE(uint32_t u32Peripheral)
{
#if (LL_EFM_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_EFM) != 0UL) {
        /* Unlock all EFM registers */
        EFM_REG_Unlock();
    }
#endif
#if (LL_FCG_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_FCG) != 0UL) {
        /* Unlock FCG register */
        PWC_FCG0_REG_Unlock();
    }
#endif
#if (LL_GPIO_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_GPIO) != 0UL) {
        /* Unlock GPIO register: PSPCR, PCCR, PINAER, PCRxy, PFSRxy */
        GPIO_REG_Unlock();
    }
#endif
#if (LL_MPU_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_MPU) != 0UL) {
        /* Unlock all MPU registers */
        MPU_REG_Unlock();
    }
#endif
#if (LL_PWC_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_LVD) != 0UL) {
        /* Unlock LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
        PWC_REG_Unlock(PWC_UNLOCK_CODE2);
    }
#endif
#if (LL_PWC_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_PWC_CLK_RMU) != 0UL) {
        /* Unlock PWC, CLK, RMU registers, @ref PWC_REG_Write_Unlock_Code for details */
        PWC_REG_Unlock(PWC_UNLOCK_CODE0 | PWC_UNLOCK_CODE1);
    }
#endif
#if (LL_SRAM_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_SRAM) != 0UL) {
        /* Unlock SRAM register: WTCR, CKCR */
        SRAM_REG_Unlock();
    }
#endif
}

void LL_PERIPH_WP(uint32_t u32Peripheral)
{
#if (LL_EFM_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_EFM) != 0UL) {
        /* Lock all EFM registers */
        EFM_REG_Lock();
    }
#endif
#if (LL_FCG_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_FCG) != 0UL) {
        /* Lock FCG register */
        PWC_FCG0_REG_Lock();
    }
#endif
#if (LL_GPIO_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_GPIO) != 0UL) {
        /* Unlock GPIO register: PSPCR, PCCR, PINAER, PCRxy, PFSRxy */
        GPIO_REG_Lock();
    }
#endif
#if (LL_MPU_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_MPU) != 0UL) {
        /* Lock all MPU registers */
        MPU_REG_Lock();
    }
#endif
#if (LL_PWC_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_LVD) != 0UL) {
        /* Lock LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
        PWC_REG_Lock(PWC_UNLOCK_CODE2);
    }
#endif
#if (LL_PWC_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_PWC_CLK_RMU) != 0UL) {
        /* Lock PWC, CLK, RMU registers, @ref PWC_REG_Write_Unlock_Code for details */
        PWC_REG_Lock(PWC_UNLOCK_CODE0 | PWC_UNLOCK_CODE1);
    }
#endif
#if (LL_SRAM_ENABLE == DDL_ON)
    if ((u32Peripheral & LL_PERIPH_SRAM) != 0UL) {
        /* Lock SRAM register: WTCR, CKCR */
        SRAM_REG_Lock();
    }
#endif
}

/**
 * @brief  Software sync start timer
 * @param  [in] u32Tmr                  Timer of software sync start
 *         This parameter can be one or any combination of the macros group @ref Timer_SW_Sync_Start_Global_Macros
 * @retval None
 */
void LL_TMR_SWSyncStart(uint32_t u32Tmr)
{
    if ((LL_SW_SYNC_START_TMR_ALL & u32Tmr) != 0UL) {
        WRITE_REG32(CM_PERIC->TMR_SYNENR, (LL_SW_SYNC_START_TMR_ALL & u32Tmr));
    }
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
