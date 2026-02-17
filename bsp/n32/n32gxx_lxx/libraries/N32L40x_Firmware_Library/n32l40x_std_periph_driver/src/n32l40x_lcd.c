/*****************************************************************************
* Copyright (c) 2022, Nations Technologies Inc.
*
* All rights reserved.
* ****************************************************************************
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* - Redistributions of source code must retain the above copyright notice,
* this list of conditions and the disclaimer below.
*
* Nations' name may not be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ****************************************************************************/

/**
 * @file n32l40x_lcd.c
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

#include "n32l40x_lcd.h"

/** @addtogroup N32L40x_StdPeriph_Driver
 * @{
 */

/** @addtogroup LCD
 * @brief LCD driver modules
 * @{
 */

/** @addtogroup LCD_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup LCD_Private_Defines
 * @{
 */


/**
 * @}
 */

/**
 * @brief  Initialize the LCD peripheral according to the specified parameters
 *         in the LCD_InitStruct.
 * @param LCD_InitStructure LCD initialize structure parameters
 * @retval LCD error code
 */
LCD_ErrorTypeDef LCD_Init(LCD_InitType *LCD_InitStructure )
{
    uint32_t tmp, timeout;

    /* Check function parameters */
    assert_param(IS_LCD_BIAS(LCD_InitStructure->Bias));
    assert_param(IS_LCD_BLINKFREQ(LCD_InitStructure->BlinkFreq));
    assert_param(IS_LCD_BLINKMODE(LCD_InitStructure->BlinkMode));
    assert_param(IS_LCD_CONTRASTLEVEL(LCD_InitStructure->Contrast));
    assert_param(IS_LCD_DEADTIME(LCD_InitStructure->DeadTime));
    assert_param(IS_LCD_DIVIDER(LCD_InitStructure->Divider));
    assert_param(IS_LCD_DUTY(LCD_InitStructure->Duty));
    assert_param(IS_LCD_HIGHDRIVE(LCD_InitStructure->HighDrive));
    assert_param(IS_LCD_HIGHDRIVEBUFFER(LCD_InitStructure->HighDriveBuffer));
    assert_param(IS_LCD_MUXSEGMENT(LCD_InitStructure->MuxSegment));
    assert_param(IS_LCD_PRESCALER(LCD_InitStructure->Prescaler));
    assert_param(IS_LCD_PULSEONDURATION(LCD_InitStructure->PulseOnDuration));
    assert_param(IS_LCD_VOLTAGESOURCE(LCD_InitStructure->VoltageSource));

    /*Disable LCD controller*/
    __LCD_DISABLE();

    /*During 1/8 duty mode, 1/4 bias is not supported,use 1/3 bias instead*/
    if (LCD_DUTY_1_8 == LCD_InitStructure->Duty)
    {
        if (LCD_BIAS_1_4 == LCD_InitStructure->Bias)
            LCD_InitStructure->Bias = LCD_BIAS_1_3;
    }

    /* set the bits of LCD_CTRL register with corresonding parameters */
    tmp = 0;
    tmp |= LCD_InitStructure->HighDriveBuffer;
    tmp |= LCD_InitStructure->MuxSegment;
    tmp |= LCD_InitStructure->Bias;
    tmp |= LCD_InitStructure->Duty;
    tmp |= LCD_InitStructure->VoltageSource;
    LCD->CTRL = tmp;

    /*If High driver enable, PulseOnDuration must be LCD_PulseOnDuration_1*/
    if (LCD_InitStructure->HighDrive == LCD_HIGHDRIVE_ENABLE)
    {
        LCD_InitStructure->PulseOnDuration = LCD_PULSEONDURATION_1;
    }

    /* set the bits of LCD_FCTRL register with corresonding parameters */
    tmp = 0;
    tmp |= LCD_InitStructure->Prescaler;
    tmp |= LCD_InitStructure->Divider;
    tmp |= LCD_InitStructure->BlinkMode;
    tmp |= LCD_InitStructure->BlinkFreq;
    tmp |= LCD_InitStructure->Contrast;
    tmp |= LCD_InitStructure->DeadTime;
    tmp |= LCD_InitStructure->HighDrive;
    tmp |= LCD_InitStructure->PulseOnDuration;
    LCD->FCTRL = tmp;

    /*Clear LCD display ram, and set the update request flag*/
    LCD_RamClear();
    __LCD_UPDATE_REQUEST();

    /*Enable LCD controller*/
    __LCD_ENABLE();

    /*Check the LCD ENSTS status*/
    timeout = 0;
    while (RESET == (__LCD_GET_FLAG(LCD_FLAG_ENSTS)))
    {
        if (++timeout >= LCD_TIME_OUT)
            return LCD_ERROR_ENSTS;
    }

    /*Wait VLCD stable*/
    timeout = 0;
    while (RESET == (__LCD_GET_FLAG(LCD_FLAG_RDY)))
    {
        if (++timeout >= LCD_TIME_OUT)
            return LCD_ERROR_RDY;
    }

    return (LCD_WaitForSynchro());
}

/**
 * @brief  DeInitialize the LCD peripheral
 * @param  None
 * @retval None
 */
void LCD_DeInit(void)
{
    RCC_EnableRETPeriphReset(RCC_RET_PERIPH_LCD,ENABLE);
    RCC_EnableRETPeriphReset(RCC_RET_PERIPH_LCD,DISABLE);
}

/**
 * @brief  Config the clock source of LCD
 * @param  LCD_ClkSource specifies the clock source of LCD
 *   This parameter can be one of the following values:
 *     @arg LCD_CLK_SRC_LSI:              LCD clock source is LSI
 *     @arg LCD_CLK_SRC_LSE:              LCD clock source is LSE,and LSE is oscillator
 *     @arg LCD_CLK_SRC_LSE_BYPASS:       LCD clock source is LSE,and LSE is extennal clock
 *     @arg LCD_CLK_SRC_HSE_DIV32:        LCD clock source is HSE/32,and HSE is oscillator
 *     @arg LCD_CLK_SRC_HSE_BYPASS_DIV32: LCD clock source is HSE/32,and HSE is extennal clock
 * @retval LCD error code
 * note: LCD clock is the same with RTC
 */
LCD_ErrorTypeDef LCD_ClockConfig(uint32_t LCD_ClkSource)
{
    uint32_t timeout;

    /*Enable PWR  peripheral Clock*/
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR,ENABLE);

    if (LCD_CLK_SRC_LSI == LCD_ClkSource)
    {
        /*enable LSI clock*/
        RCC_EnableLsi(ENABLE);

        /*Wait LSI stable*/
        timeout = 0;
        while (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_LSIRD) == RESET)
        {
            if (++timeout >LCD_TIME_OUT)
                return LCD_ERROR_CLK;
        }
    }
    else if ((LCD_CLK_SRC_LSE==LCD_ClkSource)||(LCD_CLK_SRC_LSE_BYPASS==LCD_ClkSource))
    {
        if (RCC_GetFlagStatus(RCC_LDCTRL_FLAG_LSERD)==RESET)
        {
            RCC_ConfigLse((LCD_ClkSource & (~RCC_LDCTRL_RTCSEL)),0x28);
            timeout = 0;
            while (RCC_GetFlagStatus(RCC_LDCTRL_FLAG_LSERD) == RESET)
            {
                if (++timeout >LCD_TIME_OUT)
                    return LCD_ERROR_CLK;
            }
        }
    }
    else if ((LCD_CLK_SRC_HSE_DIV32==LCD_ClkSource)||(LCD_CLK_SRC_HSE_BYPASS_DIV32==LCD_ClkSource))
    {
        if (RCC_GetFlagStatus(RCC_CTRL_FLAG_HSERDF)==RESET)
        {
            RCC_ConfigHse(LCD_ClkSource & (~RCC_LDCTRL_RTCSEL));
            if (RCC_WaitHseStable()!=SUCCESS)
                return LCD_ERROR_CLK;
        }
    }
    else
        return LCD_ERROR_PARAM;

    // Set bit 8 of PWR_CTRL1.Open PWR DBP.
    PWR_BackupAccessEnable(ENABLE); //PWR->CTRL1 |=  0x100;

    /*set LSI as RTC clock source*/
    RCC_ConfigRtcClk(LCD_ClkSource & RCC_LDCTRL_RTCSEL);

    /*Enable RTC clk*/
    RCC_EnableRtcClk(ENABLE);

    /*Enable LCD clk*/
    RCC_EnableRETPeriphClk(RCC_RET_PERIPH_LCD,ENABLE);

    return LCD_ERROR_OK;
}

/**
 * @brief  Clear LCD ram register.
 * @param None
 * @retval None
 */
void LCD_RamClear(void)
{
    uint32_t counter;

    /*Clear lcd ram*/
    for(counter = LCD_RAM1_COM0; counter <= LCD_RAM2_COM7; counter++)
    {
        LCD->RAM_COM[counter] = 0x0U;
    }
}

/**
 * @brief  Update Display request.
 * @param None
 * @retval LCD error code
 */
LCD_ErrorTypeDef LCD_UpdateDisplayRequest(void)
{
    uint32_t timeout;

    /*Clear UDD flag*/
    __LCD_CLEAR_FLAG(LCD_FLAG_UDD_CLEAR);

    /* set update display request bit*/
    __LCD_UPDATE_REQUEST();

    /* Wait update complete */
    timeout = 0;
    while (RESET == (__LCD_GET_FLAG(LCD_FLAG_UDD)))
    {
        if (++timeout >= LCD_TIME_OUT)
            return LCD_ERROR_UDD;
    }

    return LCD_ERROR_OK;
}

/**
 * @brief    write to the lcd ram register.
 * @param RAMRegisterIndex RAM register index,
 *                  this parameter can be LCD_RAM_COMx_y where x can be (0..7) and y can be (1..2).
 * @param RAMRegisterMask specifies the LCD RAM Register Data Mask.
 * @param RAMData value written to RAM.
 * @retval LCD error code
 */
LCD_ErrorTypeDef LCD_Write(uint32_t RAMRegisterIndex,uint32_t RAMRegisterMask,uint32_t RAMData)
{
    uint32_t timeout;

    /* Check function parameters */
    assert_param(IS_LCD_RAM_REGISTER_INDEX(RAMRegisterIndex));

    if (RAMRegisterIndex > LCD_RAM2_COM7)
        return LCD_ERROR_PARAM;

    /* Wait VLCD request flag  clear */
    timeout = 0;
    while (__LCD_GET_FLAG(LCD_FLAG_UDR))
    {
        if (++timeout >= LCD_TIME_OUT)
        {
            return LCD_ERROR_UDR;
        }
    }

    /* Write lcd RAMData */
    MODIFY_REG(LCD->RAM_COM[RAMRegisterIndex], ~(RAMRegisterMask), RAMData &(~(RAMRegisterMask)));

    return LCD_ERROR_OK;

}

/**
 * @brief    set some bits of lcd ram register.
 * @param RAMRegisterIndex: RAM register index,
 *        this parameter can be LCD_RAM_COMx_y where x can be (0..7) and y can be (1..2).
 * @param RAMData: value to be set
 * @retval LCD error code
 */
LCD_ErrorTypeDef LCD_SetBit(uint32_t RAMRegisterIndex,uint32_t RAMData)
{
    uint32_t timeout;
    /* Check function parameters */
    assert_param(IS_LCD_RAM_REGISTER_INDEX(RAMRegisterIndex));

    if (RAMRegisterIndex > LCD_RAM2_COM7)
        return LCD_ERROR_PARAM;

    /* Wait VLCD request flag  clear */
    timeout = 0;
    while (__LCD_GET_FLAG(LCD_FLAG_UDR))
    {
        if (++timeout >= LCD_TIME_OUT)
        {
            return LCD_ERROR_UDR;
        }
    }

    /* Write lcd RAMData */
    SET_BIT(LCD->RAM_COM[RAMRegisterIndex], RAMData);
    return LCD_ERROR_OK;
}

/**
 * @brief    clear some bits of lcd ram register.
 * @param RAMRegisterIndex: RAM register index,
 *        this parameter can be LCD_RAM_COMx_y where x can be (0..7) and y can be (1..2).
 * @param RAMData: value to be clear
 * @retval LCD error code
 */
LCD_ErrorTypeDef LCD_ClearBit(uint32_t RAMRegisterIndex,uint32_t RAMData)
{
    uint32_t timeout;
    /* Check function parameters */
    assert_param(IS_LCD_RAM_REGISTER_INDEX(RAMRegisterIndex));

    if (RAMRegisterIndex > LCD_RAM2_COM7)
        return LCD_ERROR_PARAM;

    /* Wait VLCD request flag  clear */
    timeout = 0;
    while (__LCD_GET_FLAG(LCD_FLAG_UDR))
    {
        if (++timeout >= LCD_TIME_OUT)
        {
            return LCD_ERROR_UDR;
        }
    }

    /* Write lcd RAMData */
    CLEAR_BIT(LCD->RAM_COM[RAMRegisterIndex], RAMData);
    return LCD_ERROR_OK;
}


/**
 * @brief  Wait until the LCD FCTRL register is synchronized in the LCDCLK domain.
 *   This function must be called after any write operation to LCD_FCTRL register.
 * @param RAMData: None
 * @retval LCD error code
 */
LCD_ErrorTypeDef LCD_WaitForSynchro(void)
{
    uint32_t timeout;

    /* Loop until FCRSF flag is set */
    timeout = 0;
    while (RESET == (__LCD_GET_FLAG(LCD_FLAG_FCRSF)))
    {
        if (++timeout >= LCD_TIME_OUT)
        {
            return LCD_ERROR_FCRSF;
        }
    }

    return LCD_ERROR_OK;
}

/**
* @}
*/
/**
* @}
*/



