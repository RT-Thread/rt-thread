/**
 *******************************************************************************
 * @file  nt35510.h
 * @brief This file contains all the functions prototypes of the LCD NT35510
 *        driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-05-31       CDT             Optimize function arguments
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
#ifndef __NT35510_H__
#define __NT35510_H__

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
 * @addtogroup NT35510
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup NT35510_Global_Types NT35510 Global Types
 * @{
 */

/**
 * @brief LCD Device Controller Structure Definition
 */
typedef struct {
    volatile uint16_t u16REG;
    volatile uint16_t u16RAM;
} stc_lcd_controller_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup NT35510_Global_Macros NT35510 Global Macros
 * @{
 */

/**
 * @defgroup LCD_Scan_Direction LCD Scan Direction
 * @{
 */
#define LCD_SCAN_DIR_L2R_U2D            (0U)    /* From left to right && from up to down */
#define LCD_SCAN_DIR_L2R_D2U            (1U)    /* From left to right && from down to up */
#define LCD_SCAN_DIR_R2L_U2D            (2U)    /* From right to left && from up to down */
#define LCD_SCAN_DIR_R2L_D2U            (3U)    /* From right to left && from down to up */
#define LCD_SCAN_DIR_U2D_L2R            (4U)    /* From up to down && from left to right */
#define LCD_SCAN_DIR_U2D_R2L            (5U)    /* From up to down && from right to left */
#define LCD_SCAN_DIR_D2U_L2R            (6U)    /* From down to up && from left to right */
#define LCD_SCAN_DIR_D2U_R2L            (7U)    /* From down to up && from right to left */
/**
 * @}
 */

/**
 * @defgroup LCD_Display_Direction LCD Display Direction
 * @{
 */
#define LCD_DISPLAY_VERTICAL            (0x0000U)
#define LCD_DISPLAY_HORIZONTAL          (0x0001U)
/**
 * @}
 */

/**
 * @defgroup LCD_Color LCD Color
 * @{
 */
#define LCD_COLOR_WHITE                 (0xFFFFU)
#define LCD_COLOR_BLACK                 (0x0000U)
#define LCD_COLOR_BLUE                  (0x001FU)
#define LCD_COLOR_BRED                  (0xF81FU)
#define LCD_COLOR_GRED                  (0xFFE0U)
#define LCD_COLOR_GBLUE                 (0x07FFU)
#define LCD_COLOR_RED                   (0xF800U)
#define LCD_COLOR_MAGENTA               (0xF81FU)
#define LCD_COLOR_GREEN                 (0x07E0U)
#define LCD_COLOR_CYAN                  (0x7FFFU)
#define LCD_COLOR_YELLOW                (0xFFE0U)
#define LCD_COLOR_BROWN                 (0xBC40U)
#define LCD_COLOR_BRRED                 (0xFC07U)
#define LCD_COLOR_GRAY                  (0x8430U)

#define LCD_COLOR_DARKBLUE              (0x01CFU)
#define LCD_COLOR_LIGHTBLUE             (0x7D7CU)
#define LCD_COLOR_GRAYBLUE              (0x5458U)

#define LCD_COLOR_LIGHTGREEN            (0x841FU)
#define LCD_COLOR_LIGHTGRAY             (0xEF5BU)
#define LCD_COLOR_LGRAY                 (0xC618U)
#define LCD_COLOR_LGRAYBLUE             (0xA651U)
#define LCD_COLOR_LBBLUE                (0x2B12U)
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
 * @addtogroup NT35510_Global_Functions
 * @{
 */
void NT35510_Init(stc_lcd_controller_t *pstcLCD);
void NT35510_WriteData(stc_lcd_controller_t *pstcLCD, uint16_t u16Data);
void NT35510_WriteReg(stc_lcd_controller_t *pstcLCD, uint16_t u16Reg);
uint16_t NT35510_ReadData(stc_lcd_controller_t *pstcLCD);
void NT35510_WriteRegData(stc_lcd_controller_t *pstcLCD, uint16_t u16Reg, uint16_t u16Data);
uint16_t NT35510_ReadRegData(stc_lcd_controller_t *pstcLCD, uint16_t u16Reg);
uint16_t NT35510_ReadID(stc_lcd_controller_t *pstcLCD);
void NT35510_DisplayOn(stc_lcd_controller_t *pstcLCD);
void NT35510_DisplayOff(stc_lcd_controller_t *pstcLCD);
uint16_t NT35510_GetPixelWidth(void);
uint16_t NT35510_GetPixelHeight(void);
void NT35510_SetScanDir(stc_lcd_controller_t *pstcLCD, uint16_t u16Dir);
void NT35510_SetDisplayDir(stc_lcd_controller_t *pstcLCD, uint16_t u16Dir);
void NT35510_PrepareWriteRAM(stc_lcd_controller_t *pstcLCD);
void NT35510_SetBackLight(stc_lcd_controller_t *pstcLCD, uint8_t u8PWM);
void NT35510_SetCursor(stc_lcd_controller_t *pstcLCD, uint16_t u16Xpos, uint16_t u16Ypos);
void NT35510_WritePixel(stc_lcd_controller_t *pstcLCD, uint16_t u16Xpos, uint16_t u16Ypos, uint16_t u16RGBCode);
void NT35510_DrawLine(stc_lcd_controller_t *pstcLCD, uint16_t u16X1, uint16_t u16Y1,
                      uint16_t u16X2, uint16_t u16Y2, uint16_t u16RGBCode);
void NT35510_DrawCircle(stc_lcd_controller_t *pstcLCD, uint16_t u16Xpos, uint16_t u16Ypos,
                        uint16_t u16Radius, uint16_t u16RGBCode);
void NT35510_FillTriangle(stc_lcd_controller_t *pstcLCD, uint16_t u16X1, uint16_t u16Y1,
                          uint16_t u16X2, uint16_t u16Y2, uint16_t u16X3, uint16_t u16Y3, uint16_t u16RGBCode);
void NT35510_DrawRectangle(stc_lcd_controller_t *pstcLCD, uint16_t u16X1, uint16_t u16Y1,
                           uint16_t u16X2, uint16_t u16Y2, uint16_t u16RGBCode);
void NT35510_Clear(stc_lcd_controller_t *pstcLCD, uint16_t u16RGBCode);
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

#endif /* __NT35510_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
