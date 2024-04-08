/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_nt35510.c
 * @brief This file provides firmware functions of the LCD nt35510 driver
 *        library for the board EV_HC32F4A0_LQFP176.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-01-15       CDT             Optimize function arguments
   2023-09-30       CDT             Modify SMC timing parameter: EXCLK 60MHz -> 30MHz
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
#include <string.h>
#include "nt35510.h"
#include "hc32_ll_smc.h"
#include "ev_hc32f4a0_lqfp176.h"
#include "ev_hc32f4a0_lqfp176_nt35510.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/**
 * @defgroup EV_HC32F4A0_LQFP176_NT35510 EV_HC32F4A0_LQFP176 NT35510
 * @{
 */

#if ((BSP_NT35510_ENABLE == DDL_ON) && (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_NT35510_Local_Macros EV_HC32F4A0_LQFP176 NT35510 Local Macros
 * @{
 */

/**
 * @defgroup SMC_Max_Timeout SMC Max Timeout
 * @{
 */
#define SMC_MAX_TIMEOUT                 (0x100000UL)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_NT35510_Local_Variables EV_HC32F4A0_LQFP176 NT35510 Local Variables
 * @{
 */
static stc_lcd_controller_t *LCD = ((stc_lcd_controller_t *)BSP_NT35510_BASE);
/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup EV_HC32F4A0_LQFP176_NT35510_Local_Functions EV_HC32F4A0_LQFP176 NT35510 Local Functions
 * @{
 */

/**
 * @brief  Initializes LCD gpio.
 */
static void LCD_Port_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;

    /* LCD_CS */
    (void)GPIO_Init(BSP_NT35510_CS_PORT, BSP_NT35510_CS_PIN, &stcGpioInit);

    /* LCD_WE */
    (void)GPIO_Init(BSP_NT35510_WE_PORT, BSP_NT35510_WE_PIN, &stcGpioInit);

    /* LCD_OE */
    (void)GPIO_Init(BSP_NT35510_OE_PORT, BSP_NT35510_OE_PIN, &stcGpioInit);

    /* SMC_DATA[0:15] */
    (void)GPIO_Init(BSP_NT35510_DATA0_PORT,  BSP_NT35510_DATA0_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA1_PORT,  BSP_NT35510_DATA1_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA2_PORT,  BSP_NT35510_DATA2_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA3_PORT,  BSP_NT35510_DATA3_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA4_PORT,  BSP_NT35510_DATA4_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA5_PORT,  BSP_NT35510_DATA5_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA6_PORT,  BSP_NT35510_DATA6_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA7_PORT,  BSP_NT35510_DATA7_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA8_PORT,  BSP_NT35510_DATA8_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA9_PORT,  BSP_NT35510_DATA9_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA10_PORT, BSP_NT35510_DATA10_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA11_PORT, BSP_NT35510_DATA11_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA12_PORT, BSP_NT35510_DATA12_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA13_PORT, BSP_NT35510_DATA13_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA14_PORT, BSP_NT35510_DATA14_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_NT35510_DATA15_PORT, BSP_NT35510_DATA15_PIN, &stcGpioInit);

    (void)GPIO_Init(BSP_NT35510_RS_PORT, BSP_NT35510_RS_PIN, &stcGpioInit);

    /* LCD_DATA[0:15] */
    GPIO_SetFunc(BSP_NT35510_DATA0_PORT,  BSP_NT35510_DATA0_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA1_PORT,  BSP_NT35510_DATA1_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA2_PORT,  BSP_NT35510_DATA2_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA3_PORT,  BSP_NT35510_DATA3_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA4_PORT,  BSP_NT35510_DATA4_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA5_PORT,  BSP_NT35510_DATA5_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA6_PORT,  BSP_NT35510_DATA6_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA7_PORT,  BSP_NT35510_DATA7_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA8_PORT,  BSP_NT35510_DATA8_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA9_PORT,  BSP_NT35510_DATA9_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA10_PORT, BSP_NT35510_DATA10_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA11_PORT, BSP_NT35510_DATA11_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA12_PORT, BSP_NT35510_DATA12_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA13_PORT, BSP_NT35510_DATA13_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA14_PORT, BSP_NT35510_DATA14_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_DATA15_PORT, BSP_NT35510_DATA15_PIN, GPIO_FUNC_12);

    GPIO_SetFunc(BSP_NT35510_CS_PORT, BSP_NT35510_CS_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_RS_PORT, BSP_NT35510_RS_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_WE_PORT, BSP_NT35510_WE_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_NT35510_OE_PORT, BSP_NT35510_OE_PIN, GPIO_FUNC_12);
}

/**
 * @brief  Initializes LCD low level.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR:                  Initialize unsuccessfully.
 */
static int32_t LCD_SMC_Init(void)
{
    __IO uint32_t u32To = 0UL;
    int32_t i32Ret = LL_OK;
    stc_exmc_smc_init_t stcSmcInit;
    stc_exmc_smc_chip_config_t stcChipConfig;
    stc_exmc_smc_timing_config_t stcTimingConfig;
    en_flag_status_t enChipStatus = RESET;
    en_flag_status_t enTimingStatus = RESET;

    LCD_Port_Init();

    /* Enable SMC clock */
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_SMC, ENABLE);

    /* Enable SMC. */
    EXMC_SMC_Cmd(ENABLE);

    EXMC_SMC_ExitLowPower();

    while (EXMC_SMC_READY != EXMC_SMC_GetStatus()) {
        if (u32To > SMC_MAX_TIMEOUT) {
            i32Ret = LL_ERR;
            break;
        }
        u32To++;
    }

    if (LL_OK == i32Ret) {
        /* Configure SMC width && CS &chip & timing. */
        (void)EXMC_SMC_StructInit(&stcSmcInit);
        stcSmcInit.stcChipConfig.u32AddrMatch = BSP_NT35510_MATCH_ADDR;
        stcSmcInit.stcChipConfig.u32AddrMask  = BSP_NT35510_MASK_ADDR;
        stcSmcInit.stcChipConfig.u32MemoryWidth  = EXMC_SMC_MEMORY_WIDTH_16BIT;
        stcSmcInit.stcChipConfig.u32BAA  = EXMC_SMC_BAA_PORT_DISABLE;
        stcSmcInit.stcChipConfig.u32ADV  = EXMC_SMC_ADV_PORT_DISABLE;
        stcSmcInit.stcChipConfig.u32BLS  = EXMC_SMC_BLS_SYNC_CS;
        stcSmcInit.stcChipConfig.u32ReadBurstLen  = EXMC_SMC_READ_BURST_4BEAT;
        stcSmcInit.stcChipConfig.u32WriteBurstLen  = EXMC_SMC_WRITE_BURST_4BEAT;
        stcSmcInit.stcChipConfig.u32ReadMode  = EXMC_SMC_READ_SYNC;
        stcSmcInit.stcChipConfig.u32WriteMode  = EXMC_SMC_WRITE_SYNC;

        /* EXCLK bus frequency@30MHz: 3.3V */
        stcSmcInit.stcTimingConfig.u8RC = 12U;      /* tRCFM: min=400ns, tRDHFM: min=250ns, tRDLFM: min=150ns */
        stcSmcInit.stcTimingConfig.u8WC = 2U;       /* tWC: min=33ns, tWRH: min=15ns, tWRL: min=15ns */
        stcSmcInit.stcTimingConfig.u8CEOE = 7U;
        stcSmcInit.stcTimingConfig.u8WP = 1U;       /* tWRL: min=15ns */
        stcSmcInit.stcTimingConfig.u8PC = 4U;
        stcSmcInit.stcTimingConfig.u8TR = 1U;
        (void)EXMC_SMC_Init(BSP_NT35510_CHIP, &stcSmcInit);

        /* Set command: updateregs */
        EXMC_SMC_SetCommand(BSP_NT35510_CHIP, EXMC_SMC_CMD_UPDATEREGS, 0UL, 0UL);

        /* Check timing status */
        u32To = 0UL;
        while ((enChipStatus != SET) || (enTimingStatus != SET)) {
            (void)EXMC_SMC_GetTimingConfig(BSP_NT35510_CHIP, &stcTimingConfig);
            if (0 == memcmp(&stcTimingConfig, &stcSmcInit.stcTimingConfig, sizeof(stcTimingConfig))) {
                enTimingStatus = SET;
            }

            (void)EXMC_SMC_GetChipConfig(BSP_NT35510_CHIP, &stcChipConfig);
            if (0 == memcmp(&stcChipConfig, &stcSmcInit.stcChipConfig, sizeof(stcChipConfig))) {
                enChipStatus = SET;
            }

            if (u32To > SMC_MAX_TIMEOUT) {
                i32Ret = LL_ERR;
                break;
            }
            u32To++;
        }
    }

    return i32Ret;
}

/**
 * @}
 */

/**
 * @defgroup EV_HC32F4A0_LQFP176_NT35510_Global_Functions EV_HC32F4A0_LQFP176 NT35510 Global Functions
 * @{
 */

/**
 * @brief  LCD device initialize.
 * @param  None
 * @retval None
 */
void BSP_NT35510_Init(void)
{
    (void)LCD_SMC_Init();

    NT35510_Init(LCD);
}

/**
 * @brief  Read LCD ID.
 * @param  None
 * @retval ID.
 */
uint32_t BSP_NT35510_ReadID(void)
{
    return NT35510_ReadID(LCD);
}

/**
 * @brief  Enables the Display.
 * @param  None
 * @retval None
 */
void BSP_NT35510_DisplayOn(void)
{
    NT35510_DisplayOn(LCD);
}

/**
 * @brief  Disables the Display.
 * @param  None
 * @retval None
 */
void BSP_NT35510_DisplayOff(void)
{
    NT35510_DisplayOff(LCD);
}

/**
 * @brief  Get LCD PIXEL WIDTH.
 * @param  None
 * @retval LCD PIXEL WIDTH.
 */
uint16_t BSP_NT35510_GetPixelWidth(void)
{
    return NT35510_GetPixelWidth();
}

/**
 * @brief  Get LCD PIXEL HEIGHT.
 * @param  None
 * @retval LCD PIXEL HEIGHT.
 */
uint16_t BSP_NT35510_GetPixelHeight(void)
{
    return NT35510_GetPixelHeight();
}

/**
 * @brief  Write data on LCD data register.
 * @param  [in] u16Data:                Data to be written
 * @retval None
 */
void BSP_NT35510_WriteData(uint16_t u16Data)
{
    NT35510_WriteData(LCD, u16Data);
}

/**
 * @brief  Write register on LCD register.
 * @param  [in] u16Reg:                 Address of the selected register.
 * @retval None
 */
void BSP_NT35510_WriteReg(uint16_t u16Reg)
{
    NT35510_WriteReg(LCD, u16Reg);
}

/**
 * @brief  Read data from LCD data register.
 * @param  None
 * @retval Read data.
 */
uint16_t BSP_NT35510_ReadData(void)
{
    return NT35510_ReadData(LCD);
}

/**
 * @brief  Write to the selected LCD register.
 * @param  [in] u16Reg:                 Address of the selected register.
 * @param  [in] u16Data:                Data to be written
 * @retval None
 */
void BSP_NT35510_WriteRegData(uint16_t u16Reg, uint16_t u16Data)
{
    NT35510_WriteRegData(LCD, u16Reg, u16Data);
}

/**
 * @brief  Read the selected LCD register.
 * @param  [in] u16Reg:                 Address of the selected register.
 * @retval Register value
 */
uint16_t BSP_NT35510_ReadRegData(uint16_t u16Reg)
{
    return NT35510_ReadRegData(LCD, u16Reg);
}

/**
 * @brief  Set scan direction.
 * @param  [in] u16Dir:                 Scan direction
 *         This parameter can be one of the following values:
 *           @arg LCD_SCAN_DIR_L2R_U2D: From left to right && from up to down
 *           @arg LCD_SCAN_DIR_L2R_D2U: From left to right && from down to up
 *           @arg LCD_SCAN_DIR_R2L_U2D: From right to left && from up to down
 *           @arg LCD_SCAN_DIR_R2L_D2U: From right to left && from down to up
 *           @arg LCD_SCAN_DIR_U2D_L2R: From up to down && from left to right
 *           @arg LCD_SCAN_DIR_U2D_R2L: From up to down && from right to left
 *           @arg LCD_SCAN_DIR_D2U_L2R: From down to up && from left to right
 *           @arg LCD_SCAN_DIR_D2U_R2L: From down to up && from right to left
 * @retval None
 */
void BSP_NT35510_SetScanDir(uint16_t u16Dir)
{
    NT35510_SetScanDir(LCD, u16Dir);
}

/**
 * @brief  Set screen direction.
 * @param  [in] u16Dir:                 Screen direction
 *         This parameter can be one of the following values:
 *           @arg LCD_DISPLAY_VERTICAL:     LCD vertical display
 *           @arg LCD_DISPLAY_HORIZONTAL:   LCD horizontal display
 * @retval None
 */
void BSP_NT35510_SetDisplayDir(uint16_t u16Dir)
{
    NT35510_SetDisplayDir(LCD, u16Dir);
}

/**
 * @brief  Prepare to write LCD RAM.
 * @param  None
 */
void BSP_NT35510_PrepareWriteRAM(void)
{
    NT35510_PrepareWriteRAM(LCD);
}

/**
 * @brief  Set screen backlight.
 * @param  [in] u8PWM:                  PWM level
           This parameter can be a value between Min_Data = 0 and Max_Data = 100
 * @retval None
 */
void BSP_NT35510_SetBackLight(uint8_t u8PWM)
{
    NT35510_SetBackLight(LCD, u8PWM);
}

/**
 * @brief  Set Cursor position.
 * @param  u16Xpos:                     Specifies the X position.
 * @param  u16Ypos:                     Specifies the Y position.
 * @retval None
 */
void BSP_NT35510_SetCursor(uint16_t u16Xpos, uint16_t u16Ypos)
{
    NT35510_SetCursor(LCD, u16Xpos, u16Ypos);
}

/**
 * @brief  Write pixel.
 * @param  u16Xpos:                     Specifies the X position.
 * @param  u16Ypos:                     Specifies the Y position.
 * @param  [in] u16RGBCode:             The RGB pixel color in RGB565 format
 * @retval None
 */
void BSP_NT35510_WritePixel(uint16_t u16Xpos, uint16_t u16Ypos, uint16_t u16RGBCode)
{
    NT35510_WritePixel(LCD, u16Xpos, u16Ypos, u16RGBCode);
}

/**
 * @brief  Write line.
 * @param  u16X1:                       Specifies the X position 1.
 * @param  u16X2:                       Specifies the X position 2.
 * @param  u16Y1:                       Specifies the Y position 1.
 * @param  u16Y2:                       Specifies the Y position 2.
 * @param  [in] u16RGBCode:             The RGB pixel color in RGB565 format
 * @retval None
 */
void BSP_NT35510_DrawLine(uint16_t u16X1, uint16_t u16Y1,
                          uint16_t u16X2, uint16_t u16Y2, uint16_t u16RGBCode)
{
    NT35510_DrawLine(LCD, u16X1, u16Y1, u16X2, u16Y2, u16RGBCode);
}

/**
 * @brief  Draws a circle.
 * @param  [in] u16Xpos:                X position
 * @param  [in] u16Ypos:                Y position
 * @param  [in] u16Radius:              Circle radius
 * @param  [in] u16RGBCode:             The RGB pixel color in RGB565 format
 * @retval None
 */
void BSP_NT35510_DrawCircle(uint16_t u16Xpos, uint16_t u16Ypos, uint16_t u16Radius, uint16_t u16RGBCode)
{
    NT35510_DrawCircle(LCD, u16Xpos, u16Ypos, u16Radius, u16RGBCode);
}

/**
 * @brief  Fills a triangle (between 3 points).
 * @param  [in] u16X1:                  Point 1 X position
 * @param  [in] u16Y1:                  Point 1 Y position
 * @param  [in] u16X2:                  Point 2 X position
 * @param  [in] u16Y2:                  Point 2 Y position
 * @param  [in] u16X3:                  Point 3 X position
 * @param  [in] u16Y3:                  Point 3 Y position
 * @param  [in] u16RGBCode:             The RGB pixel color in RGB565 format
 * @retval None
 */
void BSP_NT35510_FillTriangle(uint16_t u16X1, uint16_t u16Y1, uint16_t u16X2, uint16_t u16Y2, uint16_t u16X3,
                              uint16_t u16Y3, uint16_t u16RGBCode)
{
    NT35510_FillTriangle(LCD, u16X1, u16Y1, u16X2, u16Y2, u16X3, u16Y3, u16RGBCode);
}

/**
 * @brief  Draw rectangle.
 * @param  [in] u16X1:                  Point 1 X position
 * @param  [in] u16Y1:                  Point 1 Y position
 * @param  [in] u16X2:                  Point 2 X position
 * @param  [in] u16Y2:                  Point 2 Y position
 * @param  [in] u16RGBCode:             The RGB pixel color in RGB565 format
 * @retval None
 */
void BSP_NT35510_DrawRectangle(uint16_t u16X1, uint16_t u16Y1,
                               uint16_t u16X2, uint16_t u16Y2, uint16_t u16RGBCode)
{
    NT35510_DrawRectangle(LCD, u16X1, u16Y1, u16X2, u16Y2, u16RGBCode);
}

/**
 * @brief  Clear screen.
 * @param  [in] u16RGBCode:             The RGB pixel color in RGB565 format
 * @retval None
 */
void BSP_NT35510_Clear(uint16_t u16RGBCode)
{
    NT35510_Clear(LCD, u16RGBCode);
}

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

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
