/**************************************************************************//**
 * @file     lcd.c
 * @version  V3.00
 * @brief    Liquid-Crystal Display(LCD) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup LCD_Driver LCD Driver
  @{
*/


/// @cond HIDDEN_SYMBOLS

/** @addtogroup LCD_EXPORTED_VARIABLES LCD Exported Variables
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/* Global file scope (static) variables                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
static uint32_t g_LCDFrameRate;

/**@}*/ /* end of group LCD_EXPORTED_VARIABLES */

/// @endcond /* HIDDEN_SYMBOLS */


/** @addtogroup LCD_EXPORTED_FUNCTIONS LCD Exported Functions
  @{
*/

/**
  * @brief      LCD Initialization routine
  *
  * @param[in]  pLCDCfg Specify the LCD property. It includes:
  *                     u32SrcFreq: Clock source frequency of LCD controller.
  *                     u32ComDuty: LCD COM duty ratio selection. Valid values are:
  *                                 - \ref LCD_COM_DUTY_1_1
  *                                 - \ref LCD_COM_DUTY_1_2
  *                                 - \ref LCD_COM_DUTY_1_3
  *                                 - \ref LCD_COM_DUTY_1_4
  *                                 - \ref LCD_COM_DUTY_1_5
  *                                 - \ref LCD_COM_DUTY_1_6
  *                                 - \ref LCD_COM_DUTY_1_7
  *                                 - \ref LCD_COM_DUTY_1_8
  *                     u32BiasLevel: LCD Bias level selection. Valid values are:
  *                                     - \ref LCD_BIAS_LV_1_2
  *                                     - \ref LCD_BIAS_LV_1_3
  *                                     - \ref LCD_BIAS_LV_1_4
  *                     u32Framerate: Specify the target LCD operating frame rate (Hz).
  *                     u32WaveformType: Specify the LCD waveform type. Valid values are:
  *                                         - \ref LCD_WAVEFORM_TYPE_A_NORMAL
  *                                         - \ref LCD_WAVEFORM_TYPE_B_NORMAL
  *                                         - \ref LCD_WAVEFORM_TYPE_A_INVERSE
  *                                         - \ref LCD_WAVEFORM_TYPE_B_INVERSE
  *                     u32IntSrc: Interrupt source selection. Valid values are:
  *                                 - \ref LCD_DISABLE_ALL_INT
  *                                 - \ref LCD_FRAME_COUNTING_END_INT
  *                                 - \ref LCD_FRAME_END_INT
  *                                 - \ref LCD_CPTOUT_INT
  *                                 - \ref LCD_ENABLE_ALL_INT
  *                     u32DrivingMode: LCD operation driving mode selection. Valid values are:
  *                                 - \ref LCD_LOW_DRIVING_AND_BUF_OFF
  *                                 - \ref LCD_HIGH_DRIVING_AND_BUF_OFF
  *                                 - \ref LCD_HIGH_DRIVING_AND_BUF_OFF_AND_PWR_SAVING
  *                                 - \ref LCD_HIGH_DRIVING_AND_BUF_OFF_AND_PWR_SAVING
  *                                 - \ref LCD_LOW_DRIVING_AND_BUF_ON_AND_PWR_SAVING
  *                     u32VSrc: Voltage source selection. Valid values are:
  *                                 - \ref LCD_VOLTAGE_SOURCE_VLCD
  *                                 - \ref LCD_VOLTAGE_SOURCE_AVDD
  *                                 - \ref LCD_VOLTAGE_SOURCE_CP
  *
  * @return     The real LCD operating frame rate. Or 0 means LCD_Open failed.
  *
  * @details    This function will configure the LCD properties for driving the LCD display well.
  *             After that, user can perform \ref LCD_ENABLE_DISPLAY() to enable LCD controller for LCD display.
  */
uint32_t LCD_Open(S_LCD_CFG_T *pLCDCfg)
{
    uint32_t u32ComNum, u32FreqLCD, u32FreqDiv;

    /* Display LCD display first */
    LCD_DISABLE_DISPLAY();

    /* Turn all segments off */
    LCD_SetAllPixels(0);

    /* Set com and bias */
    LCD->PCTL = (pLCDCfg->u32ComDuty | pLCDCfg->u32BiasLevel);

    /* Set waveform type */
    LCD_WAVEFORM_TYPE(pLCDCfg->u32WaveformType);

    /* Configure interrupt source */
    LCD->INTEN = pLCDCfg->u32IntSrc;

    /* Set driving mode */
    LCD_DRIVING_MODE(pLCDCfg->u32DrivingMode);

    /* Select voltage source */
    LCD_VOLTAGE_SOURCE(pLCDCfg->u32VSrc);

    /*
        An example for specify frame rate.
            If LCD source clock is 32768Hz, COM duty 4.
            In type-A:
                One frame rate 32Hz, frame end event rate 32Hz.
                    32 = (1/4) * F_LCD * (1/2)
                    F_LCD = 32 * 4 * 2 = 256 = (32768 / F_Div)
                    F_Div = (32768 / F_LCD) = 128
            In type-B:
                Each even/odd frame rate 32Hz, frame end event rate 16Hz.
                    32 = (1/4) * F_LCD
                    F_LCD = 32 * 4 = (32768 / F_Div)
                    F_Div = (32768 / F_LCD) = 256
    */
    u32ComNum = ((pLCDCfg->u32ComDuty & LCD_PCTL_DUTY_Msk) >> LCD_PCTL_DUTY_Pos) + 1;
    if((pLCDCfg->u32WaveformType & LCD_PCTL_TYPE_Msk) == LCD_PCTL_TYPE_Msk)
    {
        /* In type-B */

        /* Calculate LCD operation frequency */
        u32FreqLCD = (pLCDCfg->u32Framerate * u32ComNum);

        /* Calculate possible freq. divider */
        u32FreqDiv = (pLCDCfg->u32SrcFreq  / u32FreqLCD);

        if(u32FreqDiv > 1024)
        {
            /* Invalid frame rate */
            g_LCDFrameRate = 0ul;
        }
        else
        {
            /* Set freq. divider */
            LCD_SET_FREQDIV(u32FreqDiv);

            /* Calculate target frame rate */
            g_LCDFrameRate = pLCDCfg->u32SrcFreq / (u32ComNum * u32FreqDiv);
        }
    }
    else
    {
        /* In type-A */

        /* Calculate LCD operation frequency */
        u32FreqLCD = (pLCDCfg->u32Framerate * u32ComNum) * 2;

        /* Calculate possible freq. divider */
        u32FreqDiv = (pLCDCfg->u32SrcFreq  / u32FreqLCD);

        if(u32FreqDiv > 1024)
        {
            /* Invalid frame rate */
            g_LCDFrameRate = 0ul;
        }
        else
        {
            /* Set freq. divider */
            LCD_SET_FREQDIV(u32FreqDiv);

            /* Calculate target frame rate */
            g_LCDFrameRate = (pLCDCfg->u32SrcFreq  / (u32ComNum * u32FreqDiv)) / 2;
        }
    }

    return g_LCDFrameRate;
}

/**
  * @brief      Disable LCD Display
  *
  * @param[in]  None
  *
  * @return     None
  *
  * @details    This function is used to disable LCD display.
  */
void LCD_Close(void)
{
    LCD_DISABLE_DISPLAY();
}

/**
  * @brief      Enables a Segment Display
  *
  * @param[in]  u32Com      Specify COM number. Valid values are from 0~7.
  * @param[in]  u32Seg      Specify Segment number. Valid values are from 0~43.
  * @param[in]  u32OnFlag   0 : Segment not display
  *                         1 : Segment display
  *
  * @return     None
  *
  * @details    This function is used to enable specified segment display on the LCD.
  */
void LCD_SetPixel(uint32_t u32Com, uint32_t u32Seg, uint32_t u32OnFlag)
{
    uint32_t seg_num = (u32Seg / 4);
    uint32_t seg_shift = (8 * (u32Seg - (4 * seg_num)));

    if(seg_num < 11)
    {
        if(u32OnFlag)
        {
            LCD->DATA[seg_num] |= ((uint32_t)(1 << u32Com) << seg_shift);
        }
        else
        {
            LCD->DATA[seg_num] &= (~((uint32_t)(1 << u32Com) << seg_shift));
        }
    }
}

/**
  * @brief      Enable/Disable all LCD segments
  *
  * @param[in]  u32OnOff    0 : Disable all segments display
  *                         1 : Enable all segments display
  *
  * @return     None
  *
  * @details    This function is used to enable/disable all LCD segments display.
  */
void LCD_SetAllPixels(uint32_t u32OnOff)
{
    uint32_t i, u32Value;

    if(u32OnOff == 1ul)
    {
        u32Value = 0xFFFFFFFFul;
    }
    else
    {
        u32Value = 0x00000000ul;
    }

    for(i = 0; i < 11; i++)
        LCD->DATA[i] = u32Value;
}

/**
  * @brief      Enable LCD Blinking
  *
  * @param[in]  u32ms       Blinking period time(unit: ms)
  *
  * @return     Real blinking period time(ms)
  *
  * @details    This function is used to enable blink display with specified period.
  */
uint32_t LCD_EnableBlink(uint32_t u32ms)
{
    uint32_t u32OneCountPeriod, u32TargetCounts;

    if((LCD->PCTL & LCD_PCTL_TYPE_Msk) == LCD_PCTL_TYPE_Msk)
    {
        /* In type-B */
        u32OneCountPeriod = (1000 * 2) / g_LCDFrameRate; // ms
    }
    else
    {
        /* In type-A */
        u32OneCountPeriod = 1000 / g_LCDFrameRate; // ms
    }

    u32TargetCounts = (u32ms / u32OneCountPeriod);
    if(u32TargetCounts == 0)
        u32TargetCounts = 1;
    if(u32TargetCounts > 1024)
        u32TargetCounts = 1024;

    LCD_SET_FRAME_COUNTING_VALUE(u32TargetCounts);

    /* Enable blink display */
    LCD_BLINKING_ON();

    return (u32OneCountPeriod * u32TargetCounts);
}

/**
  * @brief      Disable LCD Blinking
  *
  * @param[in]  None
  *
  * @return     None
  *
  * @details    This function is used to disable LCD blink display.
  */
void LCD_DisableBlink(void)
{
    /* Disable blink display */
    LCD_BLINKING_OFF();
}

/**
  * @brief      Enable LCD Interrupt
  *
  * @param[in]  IntSrc      Interrupt Source. It could be a combination of
  *                             \ref LCD_FRAME_COUNTING_END_INT, \ref LCD_FRAME_END_INT and \ref LCD_CPTOUT_INT.
  *
  * @return     None
  *
  * @details    This function is used to enable the specific LCD interrupt.
  */
void LCD_EnableInt(uint32_t u32IntSrc)
{
    LCD->INTEN |= (u32IntSrc);
}

/**
  * @brief      Disable LCD Interrupt
  *
  * @param[in]  IntSrc      Interrupt Source. It could be a combination of
  *                             \ref LCD_FRAME_COUNTING_END_INT, \ref LCD_FRAME_END_INT and \ref LCD_CPTOUT_INT.
  *
  * @return     None
  *
  * @details    This function is used to disable the specific LCD interrupt.
  */
void LCD_DisableInt(uint32_t u32IntSrc)
{
    LCD->INTEN &= ~(u32IntSrc);
}


/**@}*/ /* end of group LCD_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group LCD_Driver */

/**@}*/ /* end of group Standard_Driver */

