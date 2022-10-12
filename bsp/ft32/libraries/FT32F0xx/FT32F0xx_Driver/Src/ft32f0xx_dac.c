/**
  ******************************************************************************
  * @file               ft32f0xx_dac.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of DAC peripheral
  * @version            V1.0.0
  * @data                   2021-07-01
    ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx_dac.h"

/**
    *
    */
void DAC_Ref_Config(uint32_t    DAC_RefSel)
{
    uint32_t tmpreg = 0;

    assert_param(IS_DAC_REF_SEL(DAC_RefSel));

    tmpreg = DAC->CTRL;
    tmpreg &= ~DAC_CTRL_REF_SEL;
    tmpreg |= DAC_RefSel;

    DAC->CTRL |= tmpreg;
}
/**
    *   @Parame
    */
void DAC_Cmd(FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        DAC->CTRL |= DAC_CTRL_EN;
    }
    else
    {
        DAC->CTRL &= ~DAC_CTRL_EN;
    }
}


/**
  * @brief  Set the specified data holding register value for DAC channel1.
  * @param  DAC_Align: no use.
  * @param  Data: Data to be loaded in the selected data DAC1DATA register. 7BIT
  * @retval None
  */
void DAC_SetChannel1Data(uint32_t DAC_Align, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_DAC_DATA(Data));

  DAC->DATA1 = (uint32_t)Data;
}

void DAC_SetChannel2Data(uint32_t DAC_Align, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_DAC_DATA(Data));

  DAC->DATA2 = (uint32_t)Data;
}



/**
    *   @Parame
    *
    */
uint8_t DAC_Read_Reg(uint8_t DAC_Register)
{
  __IO uint32_t tmp = 0;

  tmp = (uint32_t)DAC_BASE;
  tmp += DAC_Register;

  /* Return the selected register value */
  return (uint8_t)(*(__IO uint32_t *) tmp);
}
