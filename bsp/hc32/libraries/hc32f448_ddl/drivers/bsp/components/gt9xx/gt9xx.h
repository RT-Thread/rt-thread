/**
 *******************************************************************************
 * @file  gt9XX.h
 * @brief This file contains all the functions prototypes of the touch pad GT9XX
 *        driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-12-31       CDT             First version
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
#ifndef __GT9XX_H__
#define __GT9XX_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/**
 * @addtogroup GT9XX
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup GT9XX_Global_Types GT9XX Global Types
 * @{
 */

/**
 * @brief GT9XX low layer structure definition
 */
typedef struct {
    /* Methods */
    void (*Init)(void);
    void (*Read)(const uint8_t *pu8Reg, uint8_t u8RegLen, uint8_t *pu8Buf, uint32_t u32Len);
    void (*Write)(const uint8_t *pu8Reg, uint8_t u8RegLen, const uint8_t *pu8Buf, uint32_t u32Len);
} stc_gt9xx_ll_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GT9XX_Global_Macros GT9XX Global Macros
 * @{
 */
/**
 * @defgroup GT9XX_Local_Macros GT9XX Local Macros
 * @{
 */
#define GT9XX_COMMAND                       (0x8040U)
#define GT9XX_CONFIG                        (0x8047U)

#define GT9XX_CHECK_SUM                     (0X80FF)

#define GT9XX_PRODUCT_ID                    (0x8140U)
#define GT9XX_TOUCH_STATUS                  (0x814EU)

#define GT9XX_POINT1                        (0x8150U)
#define GT9XX_POINT2                        (0x8158U)
#define GT9XX_POINT3                        (0X8160U)
#define GT9XX_POINT4                        (0X8168U)
#define GT9XX_POINT5                        (0X8170U)
#define GT9XX_POINT6                        (0X8178U)
#define GT9XX_POINT7                        (0X8180U)
#define GT9XX_POINT8                        (0X8188U)
#define GT9XX_POINT9                        (0X8190U)
#define GT9XX_POINT10                       (0X8198U)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup GT9XX_Global_Functions
 * @{
 */
void GT9XX_REG_Read(const stc_gt9xx_ll_t *pstcGt9xxLL, uint16_t u16Reg, uint8_t *pu8RegValue, uint32_t u32Len);
void GT9XX_REG_Write(const stc_gt9xx_ll_t *pstcGt9xxLL, uint16_t u16Reg, const uint8_t *pu8RegValue, uint32_t u32Len);
void GT9XX_SoftReset(const stc_gt9xx_ll_t *pstcGt9xxLL);
uint8_t GT9XX_ReadTouchStatus(const stc_gt9xx_ll_t *pstcGt9xxLL);
void GT9XX_ReadProductID(const stc_gt9xx_ll_t *pstcGt9xxLL, uint8_t *pu8IDValue, uint32_t u32Len);
void GT9XX_GetXY(const stc_gt9xx_ll_t *pstcGt9xxLL, uint16_t u16Point, uint16_t *pu16X, uint16_t *pu16Y);
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

#ifdef __cplusplus
}
#endif

#endif /* __GT9XX_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
