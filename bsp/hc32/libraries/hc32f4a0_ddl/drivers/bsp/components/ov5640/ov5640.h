/**
 *******************************************************************************
 * @file  ov5640.h
 * @brief This file contains all the functions prototypes of the camera OV5640
 *        driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
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
#ifndef __OV5640_H__
#define __OV5640_H__

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
 * @addtogroup OV5640
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup OV5640_Global_Types OV5640 Global Types
 * @{
 */

/**
 * @brief OV5640 low layer structure definition
 */
typedef struct {
    /* Methods */
    void (*Delay)(uint32_t u32Delay);
    void (*Init)(void);
    void (*Write)(const uint8_t au8Reg[], uint8_t u8RegLen, const uint8_t au8Buf[], uint32_t u32RegLen);
    void (*Read)(const uint8_t au8Reg[], uint8_t u8RegLen, uint8_t au8Buf[], uint32_t u32RegLen);
} stc_ov5640_ll_t;

/**
 * @brief OV5640 low layer structure definition
 */
typedef struct {
    uint16_t u16RegAddr;
    uint8_t  u8RegValue;
} stc_ov5640_reg_value_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup OV5640_Global_Macros OV5640 Global Macros
 * @{
 */

/**
 * @defgroup OV5640_Light_Control OV5640 Light Control
 * @{
 */
#define OV5640_LIGHT_ON             (1U)
#define OV5640_LIGHT_OFF            (0U)
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
 * @addtogroup OV5640_Global_Functions
 * @{
 */
int32_t OV5640_Init(const stc_ov5640_ll_t *pstcOv5640LL,
                    const stc_ov5640_reg_value_t astcOv5640RegTable[], uint32_t u32ArraySize);
int32_t OV5640_RGB565_Mode(const stc_ov5640_ll_t *pstcOv5640LL,
                           const stc_ov5640_reg_value_t astcModeRegTable[], uint32_t u32ArraySize);
uint16_t OV5640_ReadID(const stc_ov5640_ll_t *pstcOv5640LL);
int32_t OV5640_LightControl(const stc_ov5640_ll_t *pstcOv5640LL, uint8_t u8Switch);
int32_t OV5640_SetOutSize(const stc_ov5640_ll_t *pstcOv5640LL, uint16_t u16X, uint16_t u16Y,
                          uint16_t u16Width, uint16_t u16Height);
int32_t OV5640_TestPattern(const stc_ov5640_ll_t *pstcOv5640LL, uint8_t u8Mode);
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

#endif /* __OV5640_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
