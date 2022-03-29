/**
  ******************************************************************************
  * @file    lib_gpio.c
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   GPIO library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_gpio.h"


/**
  * @brief  Initializes GPIO.
  * @param  GPIOx: GPIOB~GPIOF
            InitStruct:GPIO configuration.
                GPIO_Pin: can use the '|' operator
                    GPIO_Pin_0 ~ GPIO_Pin_15 or GPIO_Pin_All
                GPIO_Mode:
                    GPIO_MODE_INPUT
                    GPIO_MODE_OUTPUT_CMOS
                    GPIO_MODE_OUTPUT_OD
                    GPIO_MODE_INOUT_OD
                    GPIO_MODE_INOUT_CMOS
                    GPIO_MODE_FORBIDDEN
  * @retval None
  */
void GPIOBToF_Init(GPIO_Type *GPIOx, GPIO_InitType *InitStruct)
{
  uint32_t tmp_reg1, tmp_reg2;

  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PIN(InitStruct->GPIO_Pin));
  assert_parameters(IS_GPIO_MODE(InitStruct->GPIO_Mode));

  /* Configure ATT */
  if (InitStruct->GPIO_Mode & 0x2U)
  {
    tmp_reg1 = GPIOx->ATT;
    tmp_reg1 &= ~InitStruct->GPIO_Pin;
    if (InitStruct->GPIO_Mode & 0x1U)
    {
      tmp_reg1 |= InitStruct->GPIO_Pin;
    }
    GPIOx->ATT = tmp_reg1;
  }

  /* Configure output/input mode */
  tmp_reg1 = GPIOx->OEN;
  tmp_reg1 &= ~InitStruct->GPIO_Pin;
  tmp_reg2 = GPIOx->IE;
  tmp_reg2 &= ~InitStruct->GPIO_Pin;
  if (InitStruct->GPIO_Mode & 0x8U)
  {
    tmp_reg2 |= InitStruct->GPIO_Pin;
  }
  if (InitStruct->GPIO_Mode & 0x4U)
  {
    tmp_reg1 |= InitStruct->GPIO_Pin;
  }
  GPIOx->OEN = tmp_reg1;
  GPIOx->IE = tmp_reg2;
}

/**
  * @brief  Initializes GPIOA.
  * @param  GPIOx: GPIOA
            InitStruct:GPIO configuration.
                GPIO_Pin: can use the '|' operator
                    GPIO_Pin_0 ~ GPIO_Pin_15 or GPIO_Pin_All
                GPIO_Mode:
                    GPIO_MODE_INPUT
                    GPIO_MODE_OUTPUT_CMOS
                    GPIO_MODE_OUTPUT_OD
                    GPIO_MODE_INOUT_OD
                    GPIO_MODE_INOUT_CMOS
                    GPIO_MODE_FORBIDDEN
  * @retval None
  */
void GPIOA_Init(GPIOA_Type *GPIOx, GPIO_InitType *InitStruct)
{
  uint32_t tmp_reg1, tmp_reg2;

  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PIN(InitStruct->GPIO_Pin));
  assert_parameters(IS_GPIO_MODE(InitStruct->GPIO_Mode));

  /* Configure ATT */
  if (InitStruct->GPIO_Mode & 0x2U)
  {
    tmp_reg1 = GPIOx->ATT;
    tmp_reg1 &= ~InitStruct->GPIO_Pin;
    if (InitStruct->GPIO_Mode & 0x1U)
    {
      tmp_reg1 |= InitStruct->GPIO_Pin;
    }
    GPIOx->ATT = tmp_reg1;
  }

  /* Configure output/input mode */
  tmp_reg1 = GPIOx->OEN;
  tmp_reg1 &= ~InitStruct->GPIO_Pin;
  tmp_reg2 = GPIOx->IE;
  tmp_reg2 &= ~InitStruct->GPIO_Pin;
  if (InitStruct->GPIO_Mode & 0x8U)
  {
    tmp_reg2 |= InitStruct->GPIO_Pin;
  }
  if (InitStruct->GPIO_Mode & 0x4U)
  {
    tmp_reg1 |= InitStruct->GPIO_Pin;
  }
  GPIOx->OEN = tmp_reg1;
  GPIOx->IE = tmp_reg2;
}

/**
  * @brief  Reads input data register bit.
  * @param  GPIOx: GPIOB~GPIOF
            GPIO_Pin:GPIO_Pin_0~GPIO_Pin_15.
  * @retval input pin value.
  */
uint8_t GPIOBToF_ReadInputDataBit(GPIO_Type *GPIOx, uint16_t GPIO_Pin)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PINR(GPIO_Pin));

  if (GPIOx->STS & GPIO_Pin)
    return 1;
  else
    return 0;
}

/**
  * @brief  Reads input data register bit.
  * @param  GPIOx: GPIOA
            GPIO_Pin:GPIO_Pin_0~GPIO_Pin_15.
  * @retval input pin value.
  */
uint8_t GPIOA_ReadInputDataBit(GPIOA_Type *GPIOx, uint16_t GPIO_Pin)
{
  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PINR(GPIO_Pin));

  if (GPIOx->STS & GPIO_Pin)
    return 1;
  else
    return 0;
}

/**
  * @brief  Reads input data register.
  * @param  GPIOx: GPIOB~GPIOF
  * @retval input port value.
  */
uint16_t GPIOBToF_ReadInputData(GPIO_Type* GPIOx)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));

  return GPIOx->STS;
}

/**
  * @brief  Reads input data register.
  * @param  GPIOx: GPIOA
  * @retval input port value.
  */
uint16_t GPIOA_ReadInputData(GPIOA_Type* GPIOx)
{
  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));

  return GPIOx->STS;
}

/**
  * @brief  Reads output data register bit.
  * @param  GPIOx: GPIOB~GPIOF
            GPIO_Pin:GPIO_Pin_0~GPIO_Pin_15
  * @retval output pin value.
  */
uint8_t GPIOBToF_ReadOutputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PINR(GPIO_Pin));

  if (GPIOx->DAT & GPIO_Pin)
    return 1;
  else
    return 0;
}

/**
  * @brief  Reads output data register bit.
  * @param  GPIOx: GPIOA
            GPIO_Pin:GPIO_Pin_0~GPIO_Pin_15
  * @retval output pin value.
  */
uint8_t GPIOA_ReadOutputDataBit(GPIOA_Type* GPIOx, uint16_t GPIO_Pin)
{
  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PINR(GPIO_Pin));

  if (GPIOx->DAT & GPIO_Pin)
    return 1;
  else
    return 0;
}

/**
  * @brief  Reads output data register.
  * @param  GPIOx: GPIOB~GPIOF
  * @retval Output port value.
  */
uint16_t GPIOBToF_ReadOutputData(GPIO_Type* GPIOx)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));

  return GPIOx->DAT;
}

/**
  * @brief  Reads output data register.
  * @param  GPIOx: GPIOA
  * @retval Output port value.
  */
uint16_t GPIOA_ReadOutputData(GPIOA_Type* GPIOx)
{
  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));

  return GPIOx->DAT;
}

/**
  * @brief  Writes output data register bit.
  * @param  DATx: GPIO_A~GPIO_F
            PinNum: 0~15
            val:value write to register bit.
  * @retval None.
  */
void GPIO_WriteBit(GPIO_DATInitType* DATx, uint8_t PinNum, uint8_t val)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_DAT(DATx));
  assert_parameters(IS_GPIO_PINNUM(PinNum));
  assert_parameters(IS_GPIO_BITVAL(val));
  
  DATx->DATBitBand[PinNum] = val;
}
/**
  * @brief  Write output data register bit.
  * @param  GPIOx: GPIOB~GPIOF
            GPIO_Pin: can use the ‘|’ operator
                GPIO_Pin_0~GPIO_Pin_15 or GPIO_Pin_All
            val:value write to register bit.
  * @retval None.
  */
void GPIOBToF_WriteBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin, uint8_t val)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_Pin)); 
  assert_parameters(IS_GPIO_BITVAL(val));
  
  if (val == 1)
  {
    GPIOx->DAT |= GPIO_Pin;
  }
  else
  {
    GPIOx->DAT &= ~GPIO_Pin;
  }
}

/**
  * @brief  Write output data register bit.
  * @param  GPIOx: GPIOA
            GPIO_Pin: can use the ‘|’ operator
                 GPIO_Pin_0~GPIO_Pin_15 or GPIO_Pin_All
            val:value write to register bit.
  * @retval None.
  */
void GPIOA_WriteBit(GPIOA_Type* GPIOx, uint16_t GPIO_Pin, uint8_t val)
{
  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_Pin)); 
  assert_parameters(IS_GPIO_BITVAL(val));
  
  if (val == 1)
  {
    GPIOx->DAT |= GPIO_Pin;
  }
  else
  {
    GPIOx->DAT &= ~GPIO_Pin;
  }
}

/**
  * @brief  Writes output data register.
  * @param  GPIOx: GPIOB~GPIOF
            val:value write to register.
  * @retval None.
  */
void GPIOBToF_Write(GPIO_Type* GPIOx, uint16_t val)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));

  GPIOx->DAT = val;
}

/**
  * @brief  Writes output data register.
  * @param  GPIOx: GPIOA
            val:value write to register.
  * @retval None.
  */
void GPIOA_Write(GPIOA_Type* GPIOx, uint16_t val)
{
  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));

  GPIOx->DAT = val;
}

/**
  * @brief  Enables or disables GPIO AF functiuon.
  * @param  GPIOx:GPIOB GPIOE
            GPIO_AFx:
                GPIOB_AF_PLLHDIV
                GPIOB_AF_PLLLOUT
                GPIOB_AF_OSC
                GPIOE_AF_CMP1O
            NewState:
                ENABLE
                DISABLE
  * @retval None.
  */
void GPIOBToF_AFConfig(GPIO_Type* GPIOx, uint32_t GPIO_AFx, uint8_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_GPIOAF_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_GPIOAF(GPIO_AFx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (GPIOx == GPIOB)
  {
    if (NewState == ENABLE)
    {
      GPIOAF->IOB_SEL |= GPIO_AFx;
    }
    else
    {
      GPIOAF->IOB_SEL &= ~GPIO_AFx;
    }
  }
  if (GPIOx == GPIOE)
  {
    if (NewState == ENABLE)
    {
      GPIOAF->IOE_SEL |= GPIO_AFx;
    }
    else
    {
      GPIOAF->IOE_SEL &= ~GPIO_AFx;
    }
  }
}

/**
  * @brief  Enables or disables GPIOA AF function.
  * @param  PMUIO_AFx:can use the '|' operator
                PMUIO7_AF_PLLDIV
                PMUIO6_AF_CMP2O
                PMUIO3_AF_PLLDIV
            NewState:
                ENABLE
                DISABLE
  * @retval None.
  */
void GPIOA_AFConfig(uint32_t PMUIO_AFx, uint8_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_PMUIOAF(PMUIO_AFx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState == ENABLE)
  {
    GPIOA->SEL |= PMUIO_AFx;
  }
  else
  {
    GPIOA->SEL &= ~PMUIO_AFx;
  }
}

/**
  * @brief  Enables or disables GPIO pin remap function.
  * @param  GPIO_Remap:
                GPIO_REMAP_I2C
            NewState:
               ENABLE
               DISABLE
  * @retval None.
  */
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, uint8_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_REMAP(GPIO_Remap));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState == ENABLE)
  {
    GPIOAF->IO_MISC |= GPIO_Remap;
  }
  else
  {
    GPIOAF->IO_MISC &= ~GPIO_Remap;
  }
}

/**
  * @brief  Configures GPIO PLLDIV function.
  * @param  Divider:
                GPIO_PLLDIV_1
                GPIO_PLLDIV_2
                GPIO_PLLDIV_4
                GPIO_PLLDIV_8
                GPIO_PLLDIV_16
  * @retval None.
  */
void GPIO_PLLDIVConfig(uint32_t Divider)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_GPIO_PLLDIV(Divider));

  tmp = GPIOAF->IO_MISC;
  tmp &= ~GPIOAF_IO_MISC_PLLHDIV;
  tmp |= Divider;
  GPIOAF->IO_MISC = tmp;
}

/**
  * @brief  Enables or disables GPIOA de-glitch circuit.
  * @param  GPIO_Pin: can use the '|' operator
                 GPIO_Pin_0~GPIO_Pin_15 or GPIO_Pin_All
            NewState:
               ENABLE
               DISABLE
  * @retval None.
  */
void GPIOA_DeGlitchCmd(uint16_t GPIO_Pin, uint8_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_PIN(GPIO_Pin));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));  

  /*IOA wake-up signal will go through de-glitch circuit.*/
  if (NewState == ENABLE)
  {
    GPIOA->IOANODEG &= ~GPIO_Pin;
  }
  /*IOA wake-up signal will not go through de-glitch circuit.*/
  else
  {
    GPIOA->IOANODEG |= GPIO_Pin;
  }
}

/*********************************** END OF FILE ******************************/
