/*
  ******************************************************************************
  * @file    HAL_LCD.c
  * @version V1.0.0
  * @date    2020
  * @brief   LCD HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (LCD).
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  *           @ Peripheral Control functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

/*********************************************************************************
* Function    : HAL_LCD_MspInit
* Description : Initialize the LCD MSP.
* Input       : hcan : pointer to a LCD structure that contains
*                      the configuration information for LCD module
* Output      :
* Author      : CWT                         Data : 2020年
**********************************************************************************/
__weak void HAL_LCD_MspInit(LCD_HandleTypeDef *hlcd)
{

    /* NOTE : This function only enable lcd clk and config NVIC
    Because lcd's SEG and COM is different，so the gpio of lcd need user config self.*/

    /* Enable LCD clock */
    System_Module_Enable(EN_LCD);
    /* Enable the LCD  Frame interrupt */
    hlcd->Instance->CR1 |= LCD_CR1_IE;
    NVIC_ClearPendingIRQ(LCD_IRQn);
    NVIC_SetPriority(LCD_IRQn, 5);
    NVIC_EnableIRQ(LCD_IRQn);
}

/*********************************************************************************
* Function    : HAL_LCD_MspDeInit
* Description : DeInitialize the LCD MSP.
* Input       : hcan : pointer to a LCD structure that contains
*                      the configuration information for LCD module
* Output      :
* Author      : CWT                         Data : 2020年
**********************************************************************************/
void HAL_LCD_MspDeInit(LCD_HandleTypeDef *hlcd)
{
    /* Disable LCD clock */
    System_Module_Disable(EN_LCD);
}
/*********************************************************************************
* Function    : HAL_LCD_Init
* Description : Initialize the LCD.
* Input       : hcan : pointer to a LCD structure that contains
*                      the configuration information for LCD module
* Output      :
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_LCD_Init(LCD_HandleTypeDef *hlcd)
{
    /* Check the parameters */
    if(!IS_LCD_PERIPH(hlcd->Instance)) return HAL_ERROR;
    if(!IS_LCD_DUTY(hlcd->Init.Duty)) return HAL_ERROR;
    if(!IS_LCD_BIAS(hlcd->Init.Bias)) return HAL_ERROR;
    if(!IS_LCD_Driving_Waveform(hlcd->Init.Driving_Waveform)) return HAL_ERROR;
    if(!IS_LCD_BiasSrc(hlcd->Init.BiasSrc)) return HAL_ERROR;
    if(!IS_LCD_DisplayMode(hlcd->Init.DisplayMode)) return HAL_ERROR;

    if(!IS_LCD_LCDFrequency(hlcd->Init.LCDFrequency)) return HAL_ERROR;
    if(!IS_LCD_BlinkEN(hlcd->Init.BlinkEN)) return HAL_ERROR;
    if(!IS_LCD_BlinkFrequency(hlcd->Init.BlinkFrequency)) return HAL_ERROR;

    /* Reset the RST_LCD */
    System_Module_Reset(RST_LCD);
    HAL_LCD_MspInit(hlcd);
    hlcd->Instance->CR0|=(LCD_CR0_LCDEN|hlcd->Init.LCDFrequency|hlcd->Init.Bias|hlcd->Init.Duty|hlcd->Init.BiasSrc|hlcd->Init.Driving_Waveform);
    hlcd->Instance->CR1|=(hlcd->Init.BlinkEN|hlcd->Init.BlinkFrequency|hlcd->Init.DisplayMode);
    if(hlcd->Init.Driving_Waveform==LCD_Driving_Waveform_A)
    {
        hlcd->Instance->CR0&=~(LCD_CR0_WSEL);
    }

    if(hlcd->Init.Duty==LCD_DUTY_STATIC)
    {
        if(!IS_LCD_StaticPower(hlcd->Init.StaticPower)) return HAL_ERROR;
        hlcd->Instance->CR0|=hlcd->Init.StaticPower;
    }
    else
    {
        hlcd->Instance->CR0&=~(LCD_CR0_STATIC);//当DUTY选择非静态时，该位必须设置为0
    }
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_LCD_DeInit
* Description : DeInitialize the LCD.
* Input       : hcan : pointer to a LCD structure that contains
*                      the configuration information for LCD module
* Output      :
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_LCD_DeInit(LCD_HandleTypeDef *hlcd)
{
    /* Check the parameters */
    if(!IS_LCD_PERIPH(hlcd->Instance)) return HAL_ERROR;
    /* Reset the CAN peripheral */
    CLEAR_BIT(hlcd->Instance->CR0, LCD_CR0_LCDEN);

    HAL_LCD_MspDeInit(hlcd);
    /* Return function status */
    return HAL_OK;
}
/*********************************************************************************
* Function    : HAL_LCD_InResConfig
* Description : Initialize the LCD When LCD BiasSrc is LCD_BiasSrc_InRes_Seg31_35_Normal or LCD_BiasSrc_InRes_Seg31_35_Cap.
* Input       : hlcd : pointer to a LCD structure that contains
*                      the configuration information for LCD module
*               LCD_InResInitStruct:LCD_InResInitTypeDef
* Output      :
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_LCD_InResConfig(LCD_HandleTypeDef *hlcd,LCD_InResInitTypeDef* LCD_InResInitStruct)
{
    /* Check the parameters */
    if(!IS_LCD_PERIPH(hlcd->Instance)) return HAL_ERROR;
    /* Config when BiasSrc is Inside Resistance Mod  */
    if(hlcd->Init.BiasSrc!=LCD_BiasSrc_ExRes_Seg31_35_Cap)
    {
    /* Check the parameters */
    if(!IS_LCD_BiasRes(LCD_InResInitStruct->BiasRes)) return HAL_ERROR;
    if(!IS_LCD_DriveMod(LCD_InResInitStruct->DriveMod)) return HAL_ERROR;
    if(!IS_LCD_FastCharge(LCD_InResInitStruct->FastCharge)) return HAL_ERROR;
    if(!IS_LCD_Contrast(LCD_InResInitStruct->Contrast)) return HAL_ERROR;
    /* Config LCD Contrast and Bias Resistance and DriveMod */
    hlcd->Instance->CR0|=(LCD_InResInitStruct->Contrast);
    hlcd->Instance->CR1|=(LCD_InResInitStruct->BiasRes|LCD_InResInitStruct->DriveMod);

    /* Config LCD PONTime when DriveMod is Fast Charge and Fast Charge(FCC) is Enable. */
    if(LCD_InResInitStruct->FastCharge==LCD_FastCharge_Enable && LCD_InResInitStruct->DriveMod==LCD_DriveMod_FC)
    {
        if(!IS_LCD_PONTime(LCD_InResInitStruct->PONTime)) return HAL_ERROR;
        hlcd->Instance->CR1|=(LCD_InResInitStruct->PONTime<<18);
    }
    }
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_LCD_SegComConfig
* Description : Config the LCD SEG and COM enable/disable.
* Input       : hlcd : pointer to a LCD structure that contains
*                      the configuration information for LCD module
*               SegCom:LCD_SegComInitTypeDef
* Output      :
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_LCD_SegComConfig(LCD_HandleTypeDef *hlcd,LCD_SegComInitTypeDef *SegCom)
{
    /* Check the parameters */
    if(!IS_LCD_PERIPH(hlcd->Instance)) return HAL_ERROR;
    hlcd->Instance->LCD_POEN0=SegCom->SEG0_31;
    hlcd->Instance->LCD_POEN1=SegCom->Stc_SEG32_39_COM0_8.SEG32_39_COM0_8;
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_LCD_Write
* Description : Write LCD RAMx.
* Input       : hlcd : pointer to a LCD structure that contains
*                      the configuration information for LCD module
*               LCDRAMIndex:LCD RAM index
*               Data:The data you want to write
* Output      :
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_LCD_Write(LCD_HandleTypeDef *hlcd, uint32_t LCDRAMIndex, uint32_t Data)
{
    /* Check the parameters */
    if(!IS_LCD_PERIPH(hlcd->Instance)) return HAL_ERROR;
    if(LCDRAMIndex>15) return HAL_ERROR;
    /* Wrete Data bytes to LCD RAM register */
    hlcd->Instance->LCD_RAM[LCDRAMIndex]=Data;
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_LCD_Clear
* Description : Clear LCD RAMx.
* Input       : hlcd : pointer to a LCD structure that contains
*                      the configuration information for LCD module
* Output      :
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_LCD_Clear(LCD_HandleTypeDef *hlcd)
{
    uint8_t LCDRAMIndex=0;
    /* Check the parameters */
    if(!IS_LCD_PERIPH(hlcd->Instance)) return HAL_ERROR;
    /* Clear the LCD_RAM registers */
    for(LCDRAMIndex = 0; LCDRAMIndex <= 15; LCDRAMIndex++)
    {
        hlcd->Instance->LCD_RAM[LCDRAMIndex] = 0U;
    }
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_LCD_Start_DMA
* Description : Start lcd dma transfer
* Input       : hlcd : pointer to a LCD structure that contains
*                      the configuration information for LCD module
*               pData:The data want to transfer
*               Length:transfer Size
* Output      :
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_LCD_Start_DMA(LCD_HandleTypeDef *hlcd, uint32_t *pData, uint32_t Length)
{

    /* Check the parameters */
    if(!IS_LCD_PERIPH(hlcd->Instance)) return HAL_ERROR;

    hlcd->Instance->CR1 |= LCD_CR1_DMAEN;

    if (HAL_DMA_Start_IT(hlcd->DMA_Handle,(uint32_t)pData,(uint32_t)(&hlcd->Instance->LCD_RAM[0]), Length))
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_LCD_Stop_DMA
* Description : Stop lcd dma transfer
* Input       : hlcd : pointer to a LCD structure that contains
*                      the configuration information for LCD module
*               pData:The data want to transfer
*               Length:transfer Size
* Output      :
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_LCD_Stop_DMA(LCD_HandleTypeDef *hlcd)
{
    HAL_StatusTypeDef status = HAL_OK;
    /* Check the parameters */
    if(!IS_LCD_PERIPH(hlcd->Instance)) return HAL_ERROR;

    hlcd->Instance->CR1 &=~ LCD_CR1_DMAEN;

    status = HAL_DMA_Abort(hlcd->DMA_Handle);

    return status;
}

/*********************************************************************************
* Function    : HAL_LCD_IRQHandler
* Description : HAL_LCD_IRQHandler
* Input       : hlcd : pointer to a LCD structure that contains
*                      the configuration information for LCD module
* Output      :
* Author      : CWT                         Data : 2020年
**********************************************************************************/
void HAL_LCD_IRQHandler(LCD_HandleTypeDef *hlcd)
{
    hlcd->Instance->INTCLR &=~ (LCD_INTCLR_INTFT);
}
