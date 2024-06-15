/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_nt35510.h
 * @brief This file contains all the functions prototypes of the LCD nt35510
 *        driver library for the board EV_HC32F4A0_LQFP176.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-01-15       CDT             Update function arguments
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
#ifndef __EV_HC32F4A0_LQFP176_NT35510_H__
#define __EV_HC32F4A0_LQFP176_NT35510_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "nt35510.h"
#include "hc32_ll_gpio.h"
#include "hc32_ll_smc.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176_NT35510
 * @{
 */
#if ((DDL_ON == BSP_NT35510_ENABLE) && (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_NT35510_Global_Macros EV_HC32F4A0_LQFP176 NT35510 Global Macros
 * @{
 */

/**
 * @defgroup LCD_Map_SMC_Chip LCD Map SMC Chip
 * @{
 */
#define BSP_NT35510_CHIP                (EXMC_SMC_CHIP3)
/**
 * @}
 */

/**
 * @defgroup LCD_SMC_Address_Space LCD SMC Address Space
 * @{
 */
#define BSP_NT35510_MATCH_ADDR          (0x60UL)
#define BSP_NT35510_MASK_ADDR           (EXMC_SMC_ADDR_MASK_16MB)
/**
 * @}
 */

/**
 * @defgroup LCD_Interface_Pin LCD Interface Pin
 * @{
 */
#define BSP_NT35510_CS_PORT             (GPIO_PORT_G)   /* PG10 - EXMC_CE2 */
#define BSP_NT35510_CS_PIN              (GPIO_PIN_12)

#define BSP_NT35510_WE_PORT             (GPIO_PORT_C)   /* PC00 - EXMC_WE */
#define BSP_NT35510_WE_PIN              (GPIO_PIN_00)

#define BSP_NT35510_OE_PORT             (GPIO_PORT_F)   /* PF11 - EXMC_OE */
#define BSP_NT35510_OE_PIN              (GPIO_PIN_11)

#define BSP_NT35510_RS_PORT             (GPIO_PORT_G)   /* PG02 - EXMC_ADD12 for LCD_RS */
#define BSP_NT35510_RS_PIN              (GPIO_PIN_02)

#define BSP_NT35510_DATA0_PORT          (GPIO_PORT_D)   /* PD14 - EXMC_DATA0 */
#define BSP_NT35510_DATA0_PIN           (GPIO_PIN_14)
#define BSP_NT35510_DATA1_PORT          (GPIO_PORT_D)   /* PD15 - EXMC_DATA1 */
#define BSP_NT35510_DATA1_PIN           (GPIO_PIN_15)
#define BSP_NT35510_DATA2_PORT          (GPIO_PORT_D)   /* PD00 - EXMC_DATA2 */
#define BSP_NT35510_DATA2_PIN           (GPIO_PIN_00)
#define BSP_NT35510_DATA3_PORT          (GPIO_PORT_D)   /* PD01 - EXMC_DATA3 */
#define BSP_NT35510_DATA3_PIN           (GPIO_PIN_01)
#define BSP_NT35510_DATA4_PORT          (GPIO_PORT_E)   /* PE07 - EXMC_DATA4 */
#define BSP_NT35510_DATA4_PIN           (GPIO_PIN_07)
#define BSP_NT35510_DATA5_PORT          (GPIO_PORT_E)   /* PE08 - EXMC_DATA5 */
#define BSP_NT35510_DATA5_PIN           (GPIO_PIN_08)
#define BSP_NT35510_DATA6_PORT          (GPIO_PORT_E)   /* PE09 - EXMC_DATA6 */
#define BSP_NT35510_DATA6_PIN           (GPIO_PIN_09)
#define BSP_NT35510_DATA7_PORT          (GPIO_PORT_E)   /* PE10 - EXMC_DATA7 */
#define BSP_NT35510_DATA7_PIN           (GPIO_PIN_10)
#define BSP_NT35510_DATA8_PORT          (GPIO_PORT_E)   /* PE11 - EXMC_DATA8 */
#define BSP_NT35510_DATA8_PIN           (GPIO_PIN_11)
#define BSP_NT35510_DATA9_PORT          (GPIO_PORT_E)   /* PE12 - EXMC_DATA9 */
#define BSP_NT35510_DATA9_PIN           (GPIO_PIN_12)
#define BSP_NT35510_DATA10_PORT         (GPIO_PORT_E)   /* PE13 - EXMC_DATA10 */
#define BSP_NT35510_DATA10_PIN          (GPIO_PIN_13)
#define BSP_NT35510_DATA11_PORT         (GPIO_PORT_E)   /* PE14 - EXMC_DATA11 */
#define BSP_NT35510_DATA11_PIN          (GPIO_PIN_14)
#define BSP_NT35510_DATA12_PORT         (GPIO_PORT_E)   /* PE15 - EXMC_DATA12 */
#define BSP_NT35510_DATA12_PIN          (GPIO_PIN_15)
#define BSP_NT35510_DATA13_PORT         (GPIO_PORT_D)   /* PD08 - EXMC_DATA13 */
#define BSP_NT35510_DATA13_PIN          (GPIO_PIN_08)
#define BSP_NT35510_DATA14_PORT         (GPIO_PORT_D)   /* PD09 - EXMC_DATA14 */
#define BSP_NT35510_DATA14_PIN          (GPIO_PIN_09)
#define BSP_NT35510_DATA15_PORT         (GPIO_PORT_D)   /* PD10 - EXMC_DATA15 */
#define BSP_NT35510_DATA15_PIN          (GPIO_PIN_10)
/**
 * @}
 */

/* Use EXMC CS3, A12 as the RS signal */
#define BSP_NT35510_BASE                (0x60000000UL | ((1UL << 13U) - 2UL))

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
 * @addtogroup EV_HC32F4A0_LQFP176_NT35510_Global_Functions
 * @{
 */
void BSP_NT35510_Init(void);
uint32_t BSP_NT35510_ReadID(void);
void BSP_NT35510_DisplayOn(void);
void BSP_NT35510_DisplayOff(void);
uint16_t BSP_NT35510_GetPixelWidth(void);
uint16_t BSP_NT35510_GetPixelHeight(void);
void BSP_NT35510_WriteData(uint16_t u16Data);
void BSP_NT35510_WriteReg(uint16_t u16Reg);
uint16_t BSP_NT35510_ReadData(void);
void BSP_NT35510_WriteRegData(uint16_t u16Reg, uint16_t u16Data);
uint16_t BSP_NT35510_ReadRegData(uint16_t u16Reg);
void BSP_NT35510_SetScanDir(uint16_t u16Dir);
void BSP_NT35510_SetDisplayDir(uint16_t u16Dir);
void BSP_NT35510_PrepareWriteRAM(void);
void BSP_NT35510_SetBackLight(uint8_t u8PWM);
void BSP_NT35510_SetCursor(uint16_t u16Xpos, uint16_t u16Ypos);
void BSP_NT35510_WritePixel(uint16_t u16Xpos, uint16_t u16Ypos, uint16_t u16RGBCode);
void BSP_NT35510_DrawLine(uint16_t u16X1, uint16_t u16Y1,
                          uint16_t u16X2, uint16_t u16Y2, uint16_t u16RGBCode);
void BSP_NT35510_DrawCircle(uint16_t u16Xpos, uint16_t u16Ypos, uint16_t u16Radius, uint16_t u16RGBCode);
void BSP_NT35510_FillTriangle(uint16_t u16X1, uint16_t u16Y1, uint16_t u16X2, uint16_t u16Y2,
                              uint16_t u16X3, uint16_t u16Y3, uint16_t u16RGBCode);
void BSP_NT35510_DrawRectangle(uint16_t u16X1, uint16_t u16Y1,
                               uint16_t u16X2, uint16_t u16Y2, uint16_t u16RGBCode);
void BSP_NT35510_Clear(uint16_t u16RGBCode);
/**
 * @}
 */

#endif /* BSP_NT35510_ENABLE && BSP_EV_HC32F4A0_LQFP176 */

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

#endif /* __EV_HC32F4A0_LQFP176_NT35510_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
