/**
  ******************************************************************************
  * @file    lib_gpio.c 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   GPIO library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_gpio.h"


/**
  * @brief  GPIO initialization.
  * @param  GPIOx: GPIOB~GPIOF
            InitStruct:GPIO configuration.
                GPIO_Pin: can use the ¡®|¡¯ operator
                    GPIO_Pin_0 ~ GPIO_Pin_15 or GPIO_Pin_All
                GPIO_Mode:
                    GPIO_Mode_INPUT
                    GPIO_Mode_OUTPUT_CMOS
                    GPIO_Mode_OUTPUT_OD
                    GPIO_Mode_INOUT_OD
                    GPIO_Mode_INOUT_CMOS
                    GPIO_Mode_FORBIDDEN
  * @retval None
  */
void GPIOBToF_Init(GPIO_TypeDef *GPIOx, GPIO_InitType *InitStruct)
{
  uint32_t tmp_reg1, tmp_reg2;
  
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PIN(InitStruct->GPIO_Pin));
  assert_parameters(IS_GPIO_MODE(InitStruct->GPIO_Mode));
  
  if (GPIOF == GPIOx)
    InitStruct->GPIO_Pin &= ~(GPIO_Pin_2);
  
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
  * @brief  GPIOA initialization.
  * @param  GPIOx: GPIOA
            InitStruct:GPIO configuration.
                GPIO_Pin: can use the ¡®|¡¯ operator
                    GPIO_Pin_0 ~ GPIO_Pin_15 or GPIO_Pin_All
                GPIO_Mode:
                    GPIO_Mode_INPUT
                    GPIO_Mode_OUTPUT_CMOS
                    GPIO_Mode_OUTPUT_OD
                    GPIO_Mode_INOUT_OD
                    GPIO_Mode_FORBIDDEN
  * @retval None
  */
void GPIOA_Init(GPIOA_TypeDef *GPIOx, GPIO_InitType *InitStruct)
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
  * @brief  Read input data register bit.
  * @param  GPIOx: GPIOB~GPIOF
            GPIO_Pin:GPIO_Pin_0~GPIO_Pin_15.
  * @retval input pin value.
  */
uint8_t GPIOBToF_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PINR(GPIO_Pin));

  tmp = GPIOx->STS;

  tmp &= GPIO_Pin;
  if (tmp)
    return 1;
  else
    return 0;
}

/**
  * @brief  Read input data register bit.
  * @param  GPIOx: GPIOA
            GPIO_Pin:GPIO_Pin_0~GPIO_Pin_15.
  * @retval input pin value.
  */
uint8_t GPIOA_ReadInputDataBit(GPIOA_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PINR(GPIO_Pin));

  tmp = GPIOx->STS;

  tmp &= GPIO_Pin;
  if (tmp)
    return 1;
  else
    return 0;
}

/**
  * @brief  Read input data register.
  * @param  GPIOx: GPIOB~GPIOF
  * @retval input port value.
  */
uint16_t GPIOBToF_ReadInputData(GPIO_TypeDef* GPIOx)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));
  
  return GPIOx->STS;
}

/**
  * @brief  Read input data register.
  * @param  GPIOx: GPIOA
  * @retval input port value.
  */
uint16_t GPIOA_ReadInputData(GPIOA_TypeDef* GPIOx)
{
  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));
  
  return GPIOx->STS;
}

/**
  * @brief  Read output data register bit.
  * @param  GPIOx: GPIOB~GPIOF
            GPIO_Pin:GPIO_Pin_0~GPIO_Pin_15
  * @retval output pin value.
  */
uint8_t GPIOBToF_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PINR(GPIO_Pin));  

  tmp = GPIOx->DAT;
  tmp &= GPIO_Pin;
  if (tmp)
    return 1;
  else
    return 0;
}

/**
  * @brief  Read output data register bit.
  * @param  GPIOx: GPIOA
            GPIO_Pin:GPIO_Pin_0~GPIO_Pin_15
  * @retval output pin value.
  */
uint8_t GPIOA_ReadOutputDataBit(GPIOA_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PINR(GPIO_Pin));
  
  tmp = GPIOx->DAT;
  tmp &= GPIO_Pin;
  if (tmp)
    return 1;
  else
    return 0;
}

/**
  * @brief  Read output data register.
  * @param  GPIOx: GPIOB~GPIOF
  * @retval Output port value.
  */
uint16_t GPIOBToF_ReadOutputData(GPIO_TypeDef* GPIOx)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));  
  
  return GPIOx->DAT;
}

/**
  * @brief  Read output data register.
  * @param  GPIOx: GPIOA
  * @retval Output port value.
  */
uint16_t GPIOA_ReadOutputData(GPIOA_TypeDef* GPIOx)
{
  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));
  
  return GPIOx->DAT;
}

/**
  * @brief  Set output data register bit.
  * @param  GPIOx: GPIOB~GPIOF
            GPIO_Pin: can use the ¡®|¡¯ operator
                GPIO_Pin_0 ~ GPIO_Pin_15 or GPIO_Pin_All
  * @retval None.
  */
void GPIOBToF_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_Pin));   
  
  GPIOx->DAT |= GPIO_Pin;
}

/**
  * @brief  Set output data register bit.
  * @param  GPIOx: GPIOA
            GPIO_Pin: can use the ¡®|¡¯ operator
                GPIO_Pin_0~GPIO_Pin_15 or GPIO_Pin_All
  * @retval None.
  */
void GPIOA_SetBits(GPIOA_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->DAT |= GPIO_Pin;
}

/**
  * @brief  Reset output data register bit.
  * @param  GPIOx: GPIOB~GPIOF
            GPIO_Pin: can use the ¡®|¡¯ operator
                GPIO_Pin_0~GPIO_Pin_15 or GPIO_Pin_All
  * @retval None.
  */
void GPIOBToF_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_Pin)); 
  
  GPIOx->DAT &= ~GPIO_Pin;
}

/**
  * @brief  Reset output data register bit.
  * @param  GPIOx: GPIOA 
            GPIO_Pin: can use the ¡®|¡¯ operator
                GPIO_Pin_0~GPIO_Pin_15 or GPIO_Pin_All
  * @retval None.
  */
void GPIOA_ResetBits(GPIOA_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->DAT &= ~GPIO_Pin;
}

/**
  * @brief  Write output data register bit.
  * @param  GPIOx: GPIOB~GPIOF
            GPIO_Pin: can use the ¡®|¡¯ operator
                GPIO_Pin_0~GPIO_Pin_15 or GPIO_Pin_All
            val:value write to register bit.
  * @retval None.
  */
void GPIOBToF_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t val)
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
            GPIO_Pin: can use the ¡®|¡¯ operator
                 GPIO_Pin_0~GPIO_Pin_15 or GPIO_Pin_All
            val:value write to register bit.
  * @retval None.
  */
void GPIOA_WriteBit(GPIOA_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t val)
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
  * @brief  Write output data register.
  * @param  GPIOx: GPIOB~GPIOF
            val:value write to register.
  * @retval None.
  */
void GPIOBToF_Write(GPIO_TypeDef* GPIOx, uint16_t val)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_ALL_INSTANCE(GPIOx)); 

  GPIOx->DAT = val;
}

/**
  * @brief  Write output data register.
  * @param  GPIOx: GPIOA
            val:value write to register.
  * @retval None.
  */
void GPIOA_Write(GPIOA_TypeDef* GPIOx, uint16_t val)
{
  /* Check parameters */
  assert_parameters(IS_PMUIO_ALL_INSTANCE(GPIOx));  

  GPIOx->DAT = val;
}

/**
  * @brief  GPIO AF configure.
  * @param  GPIOx:GPIOB GPIOE
            GPIO_AFx:
                GPIOB_AF_PLLHDIV
                GPIOB_AF_OSC  
                GPIOB_AF_PLLLOUT
                GPIOE_AF_CMP1O
            NewState:
                ENABLE
                DISABLE
  * @retval None.
  */
void GPIOBToF_AFConfig(GPIO_TypeDef* GPIOx, uint32_t GPIO_AFx, uint8_t NewState)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_GPIOAF_ALL_INSTANCE(GPIOx));
  assert_parameters(IS_GPIO_GPIOAF(GPIO_AFx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
    
  if (GPIOx == GPIOB)
  {
    tmp = GPIOAF->SELB;
    if (NewState != DISABLE)
    {
      tmp |= GPIO_AFx;
    }
    else
    {
      tmp &= ~GPIO_AFx;
    }
    GPIOAF->SELB = tmp;
  }
  if (GPIOx == GPIOE)
  {
    tmp = GPIOAF->SELE;
    if (NewState != DISABLE)
    {
      tmp |= GPIO_AFx;
    }
    else
    {
     tmp &= ~GPIO_AFx;
    }
    GPIOAF->SELE = tmp;
  }
}

/**
  * @brief  GPIO AF configure.
  * @param  PMUIO_AFx:
                PMUIO7_AF_PLLDIV
                PMUIO_AF_CMP2O
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
  
  if (NewState != DISABLE)
  {
    GPIOA->SEL |= PMUIO_AFx;
  }
  else
  {
    GPIOA->SEL &= ~PMUIO_AFx;
  }
}

/**
  * @brief  GPIO pin remap.
  * @param  GPIO_Remap:
                GPIO_REMAP_I2C
            NewState:
               ENABLE
               DISABLE
  * @retval None.
  */
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, uint8_t NewState)
{
  uint32_t tmp;
   
  /* Check parameters */
  assert_parameters(IS_GPIO_REMAP(GPIO_Remap));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  tmp = GPIOAF->_MISC;
  tmp &= ~GPIO_Remap;
  if (NewState == ENABLE)
    tmp |= GPIO_Remap;
  GPIOAF->_MISC = tmp;
}

/**
  * @brief  GPIO PLLDIV configure.
  * @param  Divider:
                GPIO_PLLDIV_1
                GPIO_PLLDIV_2
                GPIO_PLLDIV_4
                GPIO_PLLDIV_8
                GPIO_PLLDIV_16
  * @retval None.
  */
void GPIO_PLLDIV_Config(uint32_t Divider)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_GPIO_PLLDIV(Divider));
    
  tmp = GPIOAF->_MISC;
  tmp &= ~IO_MISC_PLLHDIV;
  tmp |= Divider;
  GPIOAF->_MISC = tmp;
}

/**
  * @brief  GPIOA de-glitch circuit control.
  * @param  GPIO_Pin: can use the ¡®|¡¯ operator
                 GPIO_Pin_0~GPIO_Pin_15 or GPIO_Pin_All
            NewState:
               ENABLE 
               DISABLE                  
  * @retval None.
  */
void GPIOA_NoDeg_Cmd( uint16_t GPIO_Pin, uint8_t NewState)
{
  uint16_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_GPIO_PIN(GPIO_Pin)); 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
    
  tmp = GPIOA->IOANODEG;
  /*IOA wake-up signal will not go through de-glitch circuit.*/
  if (NewState != DISABLE)
  {
    tmp |= GPIO_Pin;
  }
  /*IOA wake-up signal will go through de-glitch circuit.*/
  else
  {
    tmp &= ~GPIO_Pin;
  }
  GPIOA->IOANODEG = tmp;
}

/*********************************** END OF FILE ******************************/
