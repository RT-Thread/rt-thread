/**
 *******************************************************************************
 * @file  gt9xx.c
 * @brief This file provides firmware functions for Touch Pad GT9XX.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-12-31       CDT             First version
   2023-12-15       CDT             Add null pointer check
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
#include "gt9xx.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/**
 * @defgroup GT9XX Touch Pad GT9XX
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
 * @defgroup GT9XX_Global_Functions GT9XX Global Functions
 * @{
 */

/**
 * @brief  Read register on touch pad register.
 * @param  [in]  pstcGt9xxLL            Pointer to a @ref stc_gt9xx_ll_t structure
 * @param  [in]  u16Reg                 Register to be read
 * @param  [out] pu8RegValue            The buffer for reading
 * @param  [in]  u32Len                 The buffer size for bytes
 * @retval None
 */
void GT9XX_REG_Read(const stc_gt9xx_ll_t *pstcGt9xxLL, uint16_t u16Reg, uint8_t *pu8RegValue, uint32_t u32Len)
{
    uint8_t au8RegAddr[2];

    if ((NULL != pstcGt9xxLL) && (NULL != pstcGt9xxLL->Read) && (NULL != pu8RegValue)) {
        au8RegAddr[0] = (uint8_t)((u16Reg & 0xFF00U) >> 8);
        au8RegAddr[1] = (uint8_t)(u16Reg & 0x00FFU);
        (void)pstcGt9xxLL->Read(au8RegAddr, ARRAY_SZ(au8RegAddr), pu8RegValue, u32Len);
    }
}

/**
 * @brief  Write register on touch pad register.
 * @param  [in]  pstcGt9xxLL            Pointer to a @ref stc_gt9xx_ll_t structure
 * @param  [in]  u16Reg                 Register to be write
 * @param  [in]  pu8RegValue            The buffer for writing
 * @param  [in]  u32Len                 The buffer size for bytes
 * @retval None
 */
void GT9XX_REG_Write(const stc_gt9xx_ll_t *pstcGt9xxLL, uint16_t u16Reg, const uint8_t *pu8RegValue, uint32_t u32Len)
{
    uint8_t au8RegAddr[2];

    if ((NULL != pstcGt9xxLL) && (NULL != pstcGt9xxLL->Write) && (NULL != pu8RegValue)) {
        au8RegAddr[0] = (uint8_t)((u16Reg & 0xFF00U) >> 8);
        au8RegAddr[1] = (uint8_t)(u16Reg & 0x00FFU);
        (void)pstcGt9xxLL->Write(au8RegAddr, ARRAY_SZ(au8RegAddr), pu8RegValue, u32Len);
    }
}

/**
 * @brief  Reset GT9XX.
 * @param  [in] pstcGt9xxLL             Pointer to a @ref stc_gt9xx_ll_t structure.
 * @retval None
 */
void GT9XX_SoftReset(const stc_gt9xx_ll_t *pstcGt9xxLL)
{
    uint8_t u8RegValue = 0x02U;

    GT9XX_REG_Write(pstcGt9xxLL, GT9XX_COMMAND, &u8RegValue, 1UL);
}

/**
 * @brief  Read GT9XX touch status.
 * @param  [in] pstcGt9xxLL             Pointer to a @ref stc_gt9xx_ll_t structure.
 * @retval Touch status
 */
uint8_t GT9XX_ReadTouchStatus(const stc_gt9xx_ll_t *pstcGt9xxLL)
{
    uint8_t u8Status = 0U;

    GT9XX_REG_Read(pstcGt9xxLL, GT9XX_TOUCH_STATUS, &u8Status, 1UL);
    return u8Status;
}

/**
 * @brief  Read GT9XX ID.
 * @param  [in] pstcGt9xxLL             Pointer to a @ref stc_gt9xx_ll_t structure.
 * @param  [out] pu8IDValue             The buffer for reading ID
 * @param  [in]  u32Len                 The buffer size for bytes
 * @retval None
 */
void GT9XX_ReadProductID(const stc_gt9xx_ll_t *pstcGt9xxLL, uint8_t *pu8IDValue, uint32_t u32Len)
{
    GT9XX_REG_Read(pstcGt9xxLL, GT9XX_PRODUCT_ID, pu8IDValue, u32Len);
}

/**
 * @brief  Read GT9XX point.
 * @param  [in]  pstcGt9xxLL            Pointer to a @ref stc_gt9xx_ll_t structure.
 * @param  [in]  u16Point               Touch pad point
 * @param  [out] pu16X                  Point x coordinate
 * @param  [out] pu16Y                  Point y coordinate
 * @retval None
 */
void GT9XX_GetXY(const stc_gt9xx_ll_t *pstcGt9xxLL, uint16_t u16Point, uint16_t *pu16X, uint16_t *pu16Y)
{
    uint8_t au8Tmp[4];

    if ((pu16X != NULL) && (pu16Y != NULL)) {
        GT9XX_REG_Read(pstcGt9xxLL, u16Point, au8Tmp, 4UL);
        (*pu16X) = (uint16_t)au8Tmp[0] | ((uint16_t)au8Tmp[1] << 8);
        (*pu16Y) = (uint16_t)au8Tmp[2] | ((uint16_t)au8Tmp[3] << 8);
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

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
