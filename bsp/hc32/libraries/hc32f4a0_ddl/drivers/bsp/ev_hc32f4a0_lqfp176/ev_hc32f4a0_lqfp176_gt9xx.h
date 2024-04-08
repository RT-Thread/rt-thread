/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_gt9xx.h
 * @brief This file contains all the functions prototypes of the touch pad gt9xx
 *        driver library for the board EV_HC32F4A0_LQFP176.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-01-15       CDT             First version
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
#ifndef __EV_HC32F4A0_LQFP176_GT9XX_H__
#define __EV_HC32F4A0_LQFP176_GT9XX_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "gt9xx.h"
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
 * @addtogroup EV_HC32F4A0_LQFP176_GT9XX
 * @{
 */
#if ((BSP_GT9XX_ENABLE == DDL_ON) && (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_GT9XX_Global_Macros EV_HC32F4A0_LQFP176 GT9XX Global Macros
 * @{
 */

/**
 * @defgroup GT9XX_I2C_Interface GT9XX I2C Interface
 * @{
 */
/* GT9XX I2C device address: 0x5D or 0x14 */
#define BSP_GT9XX_I2C_ADDR             (0x14U)

/* I2C unit  */
#define BSP_GT9XX_I2C_UNIT             (CM_I2C1)
#define BSP_GT9XX_I2C_FCG              (FCG1_PERIPH_I2C1)

/* SDA and SCL pin define  */
#define BSP_GT9XX_I2C_SCL_PORT         (GPIO_PORT_D)
#define BSP_GT9XX_I2C_SCL_PIN          (GPIO_PIN_03)
#define BSP_GT9XX_I2C_SCL_FUNC         (GPIO_FUNC_49)

#define BSP_GT9XX_I2C_SDA_PORT         (GPIO_PORT_F)
#define BSP_GT9XX_I2C_SDA_PIN          (GPIO_PIN_10)
#define BSP_GT9XX_I2C_SDA_FUNC         (GPIO_FUNC_48)
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
 * @addtogroup EV_HC32F4A0_LQFP176_GT9XX_Global_Functions
 * @{
 */
void BSP_GT9XX_Init(void);
void BSP_GT9XX_SoftReset(void);
uint8_t BSP_GT9XX_ReadTouchStatus(void);
void BSP_GT9XX_ReadProductID(uint8_t *pu8IDValue, uint32_t u32Len);
void BSP_GT9XX_GetXY(uint16_t u16Point, uint16_t *pu16X, uint16_t *pu16Y);
void BSP_GT9XX_REG_Read(uint16_t u16Reg, uint8_t *pu8RegValue, uint32_t u32Len);
void BSP_GT9XX_REG_Write(uint16_t u16Reg, const uint8_t *pu8RegValue, uint32_t u32Len);
/**
 * @}
 */

#endif /* BSP_GT9XX_ENABLE && BSP_EV_HC32F4A0_LQFP176 */

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
