/**
******************************************************************************
* @file  HAL_gpio.c
* @author  IC Applications Department
* @version  V0.8
* @date  2019_08_02
* @brief  This file provides all the GPIO firmware functions.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, HOLOCENE SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2016 HOLOCENE</center></h2>
*/

/* Includes ------------------------------------------------------------------*/
#include "HAL_gpio.h"
#include "HAL_rcc.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @defgroup GPIO
* @brief GPIO driver modules
* @{
*/

/** @defgroup GPIO_Private_TypesDefinitions
* @{
*/

/**
* @}
*/

/** @defgroup GPIO_Private_Defines
* @{
*/

/* ------------ RCC registers bit address in the alias region ----------------*/
#define AFIO_OFFSET                 (AFIO_BASE - PERIPH_BASE)

/* --- EVENTCR Register -----*/

/* Alias word address of EVOE bit */
#define EVCR_OFFSET                 (AFIO_OFFSET + 0x00)
#define EVOE_BitNumber              ((uint8_t)0x07)
#define EVCR_EVOE_BB                (PERIPH_BB_BASE + (EVCR_OFFSET * 32) + (EVOE_BitNumber * 4))
#define EVCR_PORTPINCONFIG_MASK     ((uint16_t)0xFF80)
#define LSB_MASK                    ((uint16_t)0xFFFF)
#define DBGAFR_POSITION_MASK        ((uint32_t)0x000F0000)
#define DBGAFR_SWJCFG_MASK          ((uint32_t)0xF0FFFFFF)
#define DBGAFR_LOCATION_MASK        ((uint32_t)0x00200000)
#define DBGAFR_NUMBITS_MASK         ((uint32_t)0x00100000)

/**
* @}
*/

/** @defgroup GPIO_Private_Macros
* @{
*/

/**
* @}
*/

/** @defgroup GPIO_Private_Variables
* @{
*/

/**
* @}
*/

/** @defgroup GPIO_Private_FunctionPrototypes
* @{
*/

/**
* @}
*/

/** @defgroup GPIO_Private_Functions
* @{
*/

/**
* @brief  Deinitializes the GPIOx peripheral registers to their default
*   reset values.
* @param GPIOx: where x can be (A..G) to select the GPIO peripheral.
* @retval : None
*/
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  switch (*(uint32_t*)&GPIOx)
  {
  case GPIOA_BASE:
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, DISABLE);
    break;
  case GPIOB_BASE:
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, DISABLE);
    break;
  case GPIOC_BASE:
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, DISABLE);
    break;
  case GPIOD_BASE:
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, DISABLE);
    break;
  default:
    break;
  }
}


/**
* @brief  Initializes the GPIOx peripheral according to the specified
*   parameters in the GPIO_InitStruct.
* @param GPIOx: where x can be (A..G) to select the GPIO peripheral.
* @param GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
*   contains the configuration information for the specified GPIO
*   peripheral.
* @retval : None
*/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));

  /*---------------------------- GPIO Mode Configuration -----------------------*/
  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  {
    /* Check the parameters */
    assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));
    /* Output mode */
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
  }
  /*---------------------------- GPIO CRL Configuration ------------------------*/
  /* Configure the eight low port pins */
  if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CRL;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos;
      /* Get the port pins position */
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding low control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << pinpos);
        }
        else
        {
          /* Set the corresponding ODR bit */
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
            GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }
    GPIOx->CRL = tmpreg;
  }
  /*---------------------------- GPIO CRH Configuration ------------------------*/
  /* Configure the eight high port pins */
  if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
    tmpreg = GPIOx->CRH;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
      /* Get the port pins position */
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding high control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
        /* Set the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }
    GPIOx->CRH = tmpreg;
  }
    /*---------------------------- GPIOE_CRH_EXT Configuration ------------------------*/
  if(GPIO_InitStruct->GPIO_Pin>>16)  //说明是GPIOE的16~23位
  {
        GPIO_InitStruct->GPIO_Pin = GPIO_InitStruct->GPIO_Pin>>16;
    tmpreg = GPIOE->CRH_EXT;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos;
      /* Get the port pins position */
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding low control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << pinpos);
        }
        else
        {
          /* Set the corresponding ODR bit */
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
            GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }
    GPIOE->CRH_EXT = tmpreg;
  }
}

/**
* @brief  Fills each GPIO_InitStruct member with its default value.
* @param GPIO_InitStruct : pointer to a GPIO_InitTypeDef structure
*   which will be initialized.
* @retval : None
*/
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN_FLOATING;
}

/**
* @brief  Reads the specified input port pin.
* @param GPIOx: where x can be (A..G) to select the GPIO peripheral.
* @param GPIO_Pin:  specifies the port bit to read.
*   This parameter can be GPIO_Pin_x where x can be (0..15).
* @retval : The input port pin value.
*/
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
* @brief  Reads the specified GPIO input data port.
* @param GPIOx: where x can be (A..G) to select the GPIO peripheral.
* @retval : GPIO input data port value.
*/
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->IDR);
}

/**
* @brief  Reads the specified output data port bit.
* @param GPIOx: where x can be (A..G) to select the GPIO peripheral.
* @param GPIO_Pin:  specifies the port bit to read.
*   This parameter can be GPIO_Pin_x where x can be (0..15).
* @retval : The output port pin value.
*/
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->ODR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
* @brief  Reads the specified GPIO output data port.
* @param GPIOx: where x can be (A..G) to select the GPIO peripheral.
* @retval : GPIO output data port value.
*/
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->ODR);
}

/**
* @brief  Sets the selected data port bits.
* @param GPIOx: where x can be (A..G) to select the GPIO peripheral.
* @param GPIO_Pin: specifies the port bits to be written.
*   This parameter can be any combination of GPIO_Pin_x where
*   x can be (0..15).
* @retval : None
*/
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  if(GPIO_Pin>GPIO_Pin_15)GPIOE->BSRR_EXT=GPIO_Pin>>16;
    else
  GPIOx->BSRR = GPIO_Pin;

}

/**
* @brief  Clears the selected data port bits.
* @param GPIOx: where x can be (A..G) to select the GPIO peripheral.
* @param GPIO_Pin: specifies the port bits to be written.
*   This parameter can be any combination of GPIO_Pin_x where
*   x can be (0..15).
* @retval : None
*/
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  GPIOx->BRR = GPIO_Pin;
}

/**
* @brief  Sets or clears the selected data port bit.
* @param GPIOx: where x can be (A..G) to select the GPIO peripheral.
* @param GPIO_Pin: specifies the port bit to be written.
*   This parameter can be one of GPIO_Pin_x where x can be (0..15).
* @param BitVal: specifies the value to be written to the selected bit.
*   This parameter can be one of the BitAction enum values:
* @arg Bit_RESET: to clear the port pin
* @arg Bit_SET: to set the port pin
* @retval : None
*/
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal));

  if (BitVal != Bit_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BRR = GPIO_Pin;
  }
}

/**
* @brief  Writes data to the specified GPIO data port.
* @param GPIOx: where x can be (A..G) to select the GPIO peripheral.
* @param PortVal: specifies the value to be written to the port output
*   data register.
* @retval : None
*/
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->ODR = PortVal;
}

/**
* @brief  Locks GPIO Pins configuration registers.
* @param GPIOx: where x can be (A..G) to select the GPIO peripheral.
* @param GPIO_Pin: specifies the port bit to be written.
*   This parameter can be any combination of GPIO_Pin_x where
*   x can be (0..15).
* @retval : None
*/
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp = 0x00010000;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  tmp |= GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Reset LCKK bit */
  GPIOx->LCKR =  GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;
}


/**
* @brief  Writes data to the specified GPIO data port.
* @param  GPIOx: where x can be (A, B, C, D ) to select the GPIO peripheral.
* @param  GPIO_PinSource: specifies the pin for the Alternate function.
*          This parameter can be GPIO_PinSourcex where x can be (0..15) for GPIOA, GPIOB, GPIOD
*          and (0..12) for GPIOC .
* @param  GPIO_AF: selects the pin to used as Alternate function.
*          This parameter can be one of the following value:
*            @arg GPIO_AF_0: SPI1, MC0, TIM17_BKIN, SWDIO,SWCLK,
UART1
*            @arg GPIO_AF_1: UART1, TIM3_CH1, TIM3_CH2, TIM3_CH3,
TIM3_CH4, I2C1
*            @arg GPIO_AF_2: TIM2_CH1_ETR, TIM2_CH2, TIM2_CH3,
TIM2_CH3, TIM2_CH4, TIM1_BKIN,
TIM1_CH1N, TIM1_CH1, TIM1_CH2,
TIM1_CH3, TIM1_CH4, TIM1_ETR,
TIM1_CH2N, TIM1_CH3N, TIM2_CH2,
TIM1 6_BKIN, TIM16_CH1N, TIM17_CH1N,
TIM1 6_CH1, TIM17_CH1
*            @arg GPIO_AF_4: TIM14_CH1, I2C1
* @note   The pin should already been configured in Alternate Function mode(AF)
*         using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
* @note   Refer to the Alternate function mapping table in the device datasheet
*         for the detailed mapping of the system and peripherals'alternate
*         function I/O pins.
* @retval None
*/
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t GPIO_AF)
{
  uint32_t temp;
    unsigned char i;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  assert_param(IS_GPIO_AF(GPIO_AF));

    if(GPIO_Pin>>16)  //说明是GPIOE的16~23位
    {
        temp = GPIO_Pin>>16;
        for(i=0;i<8;i++)
        {
            if(temp&0x01)
            {
                GPIOE->AFRH_EXT &= ~((uint32_t)0xF << ((uint32_t)(i<<2)));     //AF配置占半字节，要x4,即<<2
                GPIOE->AFRH_EXT |= ((uint32_t)GPIO_AF << ((uint32_t)(i<<2)));
            }
            temp = temp>>1;
        }
    }
    if(GPIO_Pin&0XFF00)  //说明是GPIOE的8~15位
        {
            temp = GPIO_Pin>>8;
            for(i=0;i<8;i++)
            {
                if(temp&0x01)
                {
                    GPIOx->AFRH &= ~((uint32_t)0xF << ((uint32_t)(i<<2)));     //AF配置占半字节，要x4,即<<2
                    GPIOx->AFRH |= ((uint32_t)GPIO_AF << ((uint32_t)(i<<2)));
                }
                temp = temp>>1;
            }
        }
    if(GPIO_Pin&0XFF)  //说明是GPIOE的0~7位
        {
            for(i=0;i<8;i++)
            {
                if(temp&0x01)
                {
                    GPIOx->AFRL &= ~((uint32_t)0xF << ((uint32_t)(i<<2)));     //AF配置占半字节，要x4,即<<2
                    GPIOx->AFRL |= ((uint32_t)GPIO_AF << ((uint32_t)(i<<2)));
                }
                temp = temp>>1;
            }
        }
}

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2016 HOLOCENE ----------------------*/
