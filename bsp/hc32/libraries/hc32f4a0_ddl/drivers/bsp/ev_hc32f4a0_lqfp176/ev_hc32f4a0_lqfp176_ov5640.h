/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_ov5640.h
 * @brief This file contains all the functions prototypes of the camera ov5640
 *        driver library for the board EV_HC32F4A0_LQFP176.
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
#ifndef __EV_HC32F4A0_LQFP176_OV5640_H__
#define __EV_HC32F4A0_LQFP176_OV5640_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ev_hc32f4a0_lqfp176.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176_OV5640
 * @{
 */

#if ((DDL_ON == BSP_OV5640_ENABLE) && (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_OV5640_Global_Macros EV_HC32F4A0_LQFP176 OV5640 Global Macros
 * @{
 */

/**
 * @defgroup DVP_Interface_Pin DVP Interface Pin
 * @{
 */
#define BSP_OV5640_DVP_PIXCLK_PORT      (GPIO_PORT_F)   /* PF09 - DVP_PIXCLK */
#define BSP_OV5640_DVP_PIXCLK_PIN       (GPIO_PIN_09)

#define BSP_OV5640_DVP_HSYNC_PORT       (GPIO_PORT_H)   /* PH08 - DVP_HSYNC */
#define BSP_OV5640_DVP_HSYNC_PIN        (GPIO_PIN_08)   /* Line sync */

#define BSP_OV5640_DVP_VSYNC_PORT       (GPIO_PORT_I)   /* PI05 - DVP_VSYNC */
#define BSP_OV5640_DVP_VSYNC_PIN        (GPIO_PIN_05)   /* Frame sync */

#define BSP_OV5640_DVP_DATA0_PORT       (GPIO_PORT_H)   /* PH09 - DVP_DATA0 */
#define BSP_OV5640_DVP_DATA0_PIN        (GPIO_PIN_09)
#define BSP_OV5640_DVP_DATA1_PORT       (GPIO_PORT_H)   /* PH10 - DVP_DATA1 */
#define BSP_OV5640_DVP_DATA1_PIN        (GPIO_PIN_10)
#define BSP_OV5640_DVP_DATA2_PORT       (GPIO_PORT_H)   /* PH11 - DVP_DATA2 */
#define BSP_OV5640_DVP_DATA2_PIN        (GPIO_PIN_11)
#define BSP_OV5640_DVP_DATA3_PORT       (GPIO_PORT_H)   /* PH12 - DVP_DATA3 */
#define BSP_OV5640_DVP_DATA3_PIN        (GPIO_PIN_12)
#define BSP_OV5640_DVP_DATA4_PORT       (GPIO_PORT_H)   /* PH14 - DVP_DATA4 */
#define BSP_OV5640_DVP_DATA4_PIN        (GPIO_PIN_14)
#define BSP_OV5640_DVP_DATA5_PORT       (GPIO_PORT_I)   /* PI04 - DVP_DATA5 */
#define BSP_OV5640_DVP_DATA5_PIN        (GPIO_PIN_04)
#define BSP_OV5640_DVP_DATA6_PORT       (GPIO_PORT_I)   /* PI06 - DVP_DATA6 */
#define BSP_OV5640_DVP_DATA6_PIN        (GPIO_PIN_06)
#define BSP_OV5640_DVP_DATA7_PORT       (GPIO_PORT_I)   /* PI07 - DVP_DATA7 */
#define BSP_OV5640_DVP_DATA7_PIN        (GPIO_PIN_07)
/**
 * @}
 */

/**
 * @defgroup OV5640_I2C_Interface OV5640 I2C Interface
 * @{
 */
/* OV5640 I2C device address */
#define BSP_OV5640_I2C_ADDR             (0x3CU)

/* I2C unit  */
#define BSP_OV5640_I2C_UNIT             (CM_I2C1)
#define BSP_OV5640_I2C_FCG              (FCG1_PERIPH_I2C1)

/* SDA and SCL pin define  */
#define BSP_OV5640_I2C_SCL_PORT         (GPIO_PORT_D)
#define BSP_OV5640_I2C_SCL_PIN          (GPIO_PIN_03)
#define BSP_OV5640_I2C_SCL_FUNC         (GPIO_FUNC_49)

#define BSP_OV5640_I2C_SDA_PORT         (GPIO_PORT_F)
#define BSP_OV5640_I2C_SDA_PIN          (GPIO_PIN_10)
#define BSP_OV5640_I2C_SDA_FUNC         (GPIO_FUNC_48)
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
 * @addtogroup EV_HC32F4A0_LQFP176_OV5640_Global_Functions
 * @{
 */
void BSP_OV5640_Init(void);
void BSP_OV5640_RGB565_Mode(void);
uint16_t BSP_OV5640_ReadID(void);
void BSP_OV5640_LightControl(uint8_t u8Switch);
void BSP_OV5640_SetOutSize(uint16_t u16X, uint16_t u16Y, uint16_t u16Width, uint16_t u16Height);
void BSP_OV5640_TestPattern(uint8_t u8Mode);
/**
 * @}
 */

#endif /* BSP_OV5640_ENABLE && BSP_EV_HC32F4A0_LQFP176 */

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

#endif /* __EV_HC32F4A0_LQFP176_OV5640_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
