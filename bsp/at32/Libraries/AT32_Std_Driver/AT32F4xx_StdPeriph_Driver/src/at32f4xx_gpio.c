/**
 **************************************************************************
 * File Name    : at32f4xx_gpio.c
 * Description  : at32f4xx GPIO source file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_gpio.h"
#include "at32f4xx_rcc.h"
#include <math.h>

/** @addtogroup at32f4xx_StdPeriph_Driver
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


/* ---  MAPR Register ---*/
/* Alias word address of MII_RMII_SEL bit */
#define MAP_OFFSET                 (AFIO_OFFSET + 0x04)
#define MII_RMII_SEL_BitNumber      ((u8)0x17)
#define MAPR_MII_RMII_SEL_BB        (PERIPH_BB_BASE + (MAP_OFFSET * 32) + (MII_RMII_SEL_BitNumber * 4))


#define EVCR_PORTPINCONFIG_MASK     ((uint16_t)0xFF80)
#define LSB_MASK                    ((uint16_t)0xFFFF)
#define DBGAFR_POSITION_MASK        ((uint32_t)0x000F0000)
#define DBGAFR_SWJCONF_MASK          ((uint32_t)0xF0FFFFFF)
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
  * @brief  Deinitializes the GPIOx peripheral registers to their default reset values.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @retval None
  */
void GPIO_Reset(GPIO_Type* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  if (GPIOx == GPIOA)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOA, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOA, DISABLE);
  }
  else if (GPIOx == GPIOB)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOB, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOB, DISABLE);
  }
  else if (GPIOx == GPIOC)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOC, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOC, DISABLE);
  }
  else if (GPIOx == GPIOD)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOD, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOD, DISABLE);
  }
#if defined (AT32F403xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)
  else if (GPIOx == GPIOE)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOE, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOE, DISABLE);
  }
#endif
#if !defined (AT32F403Axx) && !defined (AT32F407xx)
  else if (GPIOx == GPIOF)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOF, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOF, DISABLE);
  }
#endif
#ifdef AT32F403xx
  else if (GPIOx == GPIOG)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOG, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_GPIOG, DISABLE);
  }
#endif
}

/**
  * @brief  Deinitializes the Alternate Functions (remap, event control
  *   and EXTI configuration) registers to their default reset values.
  * @param  None
  * @retval None
  */
void GPIO_AFIOReset(void)
{
  RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_AFIO, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_AFIO, DISABLE);
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitType structure that
  *         contains the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_Type* GPIOx, GPIO_InitType* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_MDE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PINS(GPIO_InitStruct->GPIO_Pins));

  /*---------------------------- GPIO Mode Configuration -----------------------*/
  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);

  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  {
    /* Check the parameters */
    assert_param(IS_GPIO_MAXSPEED(GPIO_InitStruct->GPIO_MaxSpeed));
    /* Output mode */
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_MaxSpeed;
  }

  /*---------------------------- GPIO CRL Configuration ------------------------*/
  /* Configure the eight low port pins */
  if (((uint32_t)GPIO_InitStruct->GPIO_Pins & ((uint32_t)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CTRLL;

    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos;
      /* Get the port pins position */
      currentpin = (GPIO_InitStruct->GPIO_Pins) & pos;

      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding low control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);

        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN_PD)
        {
          GPIOx->BRE = (((uint32_t)0x01) << pinpos);
        }
        else
        {
          /* Set the corresponding ODR bit */
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN_PU)
          {
            GPIOx->BSRE = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }

    GPIOx->CTRLL = tmpreg;
  }

  /*---------------------------- GPIO CRH Configuration ------------------------*/
  /* Configure the eight high port pins */
  if (GPIO_InitStruct->GPIO_Pins > 0x00FF)
  {
    tmpreg = GPIOx->CTRLH;

    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
      /* Get the port pins position */
      currentpin = ((GPIO_InitStruct->GPIO_Pins) & pos);

      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding high control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);

        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN_PD)
        {
          GPIOx->BRE = (((uint32_t)0x01) << (pinpos + 0x08));
        }

        /* Set the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN_PU)
        {
          GPIOx->BSRE = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }

    GPIOx->CTRLH = tmpreg;
  }
}

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct : pointer to a GPIO_InitType structure which will
  *         be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitType* GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pins  = GPIO_Pins_All;
  GPIO_InitStruct->GPIO_MaxSpeed = GPIO_MaxSpeed_2MHz;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN_FLOATING;
}

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PINS(GPIO_Pin));

  if ((GPIOx->IPTDT & GPIO_Pin) != (uint32_t)Bit_RESET)
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
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @retval GPIO input data port value.
  */
uint16_t GPIO_ReadInputData(GPIO_Type* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->IPTDT);
}

/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PINS(GPIO_Pin));

  if ((GPIOx->OPTDT & GPIO_Pin) != (uint32_t)Bit_RESET)
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
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(GPIO_Type* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->OPTDT);
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_SetBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PINS(GPIO_Pin));

  GPIOx->BSRE = GPIO_Pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_ResetBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PINS(GPIO_Pin));

  GPIOx->BRE = GPIO_Pin;
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be one of GPIO_Pin_x where x can be (0..15).
  * @param  BitVal: specifies the value to be written to the selected bit.
  *   This parameter can be one of the BitState enum values:
  *     @arg Bit_RESET: to clear the port pin
  *     @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin, BitState BitVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PINS(GPIO_Pin));
  assert_param(IS_GPIO_BIT_STATE(BitVal));

  if (BitVal != Bit_RESET)
  {
    GPIOx->BSRE = GPIO_Pin;
  }
  else
  {
    GPIOx->BRE = GPIO_Pin;
  }
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(GPIO_Type* GPIOx, uint16_t PortVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->OPTDT = PortVal;
}

/**
  * @brief  Locks GPIO Pins configuration registers.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_PinsLockConfig(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp = 0x00010000;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PINS(GPIO_Pin));

  tmp |= GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LOCK = tmp;
  /* Reset LCKK bit */
  GPIOx->LOCK =  GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LOCK = tmp;
  /* Read LCKK bit*/
  tmp = GPIOx->LOCK;
  /* Read LCKK bit*/
  tmp = GPIOx->LOCK;
}

/**
  * @brief  Selects the GPIO pin used as Event output.
  * @param  GPIO_PortSource: selects the GPIO port to be used as source
  *   for Event output.
  *   This parameter can be GPIO_PortSourceGPIOx where x can be (A..E).
  * @param  GPIO_PinSource: specifies the pin for the Event output.
  *   This parameter can be GPIO_PinSourcex where x can be (0..15).
  * @retval None
  */
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmpreg = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_EVENTOUT_PORT_SOURCE(GPIO_PortSource));
  assert_param(IS_GPIO_PINS_SOURCE(GPIO_PinSource));

  tmpreg = AFIO->EVCTRL;
  /* Clear the PORT[6:4] and PIN[3:0] bits */
  tmpreg &= EVCR_PORTPINCONFIG_MASK;
  tmpreg |= (uint32_t)GPIO_PortSource << 0x04;
  tmpreg |= GPIO_PinSource;
  AFIO->EVCTRL = tmpreg;
}

/**
  * @brief  Enables or disables the Event Output.
  * @param  NewState: new state of the Event output.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_EventOutputCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) EVCR_EVOE_BB = (uint32_t)NewState;
}

/**
  * @brief  Changes the mapping of the specified pin.
  * @param  GPIO_Remap: selects the pin to remap.
  *   This parameter can be one of the following values:
  *     @arg GPIO_Remap01_SPI1           : SPI1 Alternate Function mapping01
  *     @arg GPIO_Remap10_SPI1           : SPI1 Alternate Function mapping10
  *     @arg GPIO_Remap_I2C1             : I2C1 Alternate Function mapping
  *     @arg GPIO_Remap_USART1           : USART1 Alternate Function mapping
  *     @arg GPIO_Remap_USART2           : USART2 Alternate Function mapping
  *     @arg GPIO_PartialRemap_USART3    : USART3 Partial Alternate Function mapping
  *     @arg GPIO_FullRemap_USART3       : USART3 Full Alternate Function mapping
  *     @arg GPIO_PartialRemap_TMR1      : TMR1 Partial Alternate Function mapping
  *     @arg GPIO_FullRemap_TMR1         : TMR1 Full Alternate Function mapping
  *     @arg GPIO_PartialRemap1_TMR2     : TMR2 Partial1 Alternate Function mapping
  *     @arg GPIO_PartialRemap2_TMR2     : TMR2 Partial2 Alternate Function mapping
  *     @arg GPIO_FullRemap_TMR2         : TMR2 Full Alternate Function mapping
  *     @arg GPIO_PartialRemap_TMR3      : TMR3 Partial Alternate Function mapping
  *     @arg GPIO_FullRemap_TMR3         : TMR3 Full Alternate Function mapping
  *     @arg GPIO_Remap_TMR4             : TMR4 Alternate Function mapping
  *     @arg GPIO_Remap1_CAN1            : CAN1 Alternate Function mapping
  *     @arg GPIO_Remap2_CAN1            : CAN1 Alternate Function mapping
  *     @arg GPIO_Remap_PD01            : PD01 Alternate Function mapping
  *     @arg GPIO_Remap_TMR5CH4_LSI      : LSI connected to TMR5 Channel4 input capture for calibration
  *     @arg GPIO_Remap_ADC1_EXTRGINJ    : ADC1 External Trigger Injected Conversion remapping
  *     @arg GPIO_Remap_ADC1_EXTRGREG    : ADC1 External Trigger Regular Conversion remapping
  *     @arg GPIO_Remap_ADC2_EXTRGINJ    : ADC2 External Trigger Injected Conversion remapping
  *     @arg GPIO_Remap_ADC2_EXTRGREG    : ADC2 External Trigger Regular Conversion remapping
  *     @arg GPIO_Remap_SWJ_NoJNTRST     : Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST
  *     @arg GPIO_Remap_SWJ_JTAGDisable  : JTAG-DP Disabled and SW-DP Enabled
  *     @arg GPIO_Remap_SWJ_AllDisable   : Full SWJ Disabled (JTAG-DP + SW-DP)
  *     @arg GPIO_Remap_TMR15            : TMR15 Alternate Function mapping
  *     @arg GPIO_Remap_TMR9             : TMR9 Alternate Function mapping
  *     @arg GPIO_Remap_TMR10            : TMR10 Alternate Function mapping
  *     @arg GPIO_Remap_TMR11            : TMR11 Alternate Function mapping
  *     @arg GPIO_Remap_TMR13            : TMR13 Alternate Function mapping
  *     @arg GPIO_Remap_TMR14            : TMR14 Alternate Function mapping
  *     @arg GPIO_Remap_XMC_NADV         : XMC_NADV Alternate Function mapping
  *     @arg GPIO_Remap_SPI4             : SPI4 Alternate Function mapping
  *     @arg GPIO_Remap_I2C3             : I2C3 Alternate Function mapping
  *     @arg GPIO_Remap01_SDIO2          : SDIO2 Alternate Function mapping 01:CK/CMD Remaped None,D0~D3 Remaped to PA4~PA7.
  *     @arg GPIO_Remap10_SDIO2          : SDIO2 Alternate Function mapping 10:CK/CMD Remaped to PA2/PA3,D0~D3 Remaped None.
  *     @arg GPIO_Remap11_SDIO2          : SDIO2 Alternate Function mapping 11:CK/CMD Remaped to PA2/PA3,D0~D3 Remaped to PA4~PA7.
  *     @arg GPIO_Remap_EXT_FLASH        : EXT_FLASH Alternate Function mapping
  
  *     @arg AFIO_MAP3_TMR9_0010         : TMR9 Alternate Function mapping:
  *     @arg AFIO_MAP3_TMR10_0010        : TMR10 Alternate Function mapping:
  *     @arg AFIO_MAP3_TMR11_0010        : TMR11 Alternate Function mapping:
  *     @arg AFIO_MAP4_TMR1_0001         : TMR1 Alternate Function mapping 
  *     @arg AFIO_MAP4_TMR2_0001         : TMR2 Alternate Function mapping 0001
  *     @arg AFIO_MAP4_TMR2_0010         : TMR2 Alternate Function mapping 0010
  *     @arg AFIO_MAP4_TMR2_0011         : TMR2 Alternate Function mapping 0011
  *     @arg AFIO_MAP4_TMR3_0010         : TMR3 Alternate Function mapping 0010
  *     @arg AFIO_MAP4_TMR3_0011         : TMR3 Alternate Function mapping 0011
  *     @arg AFIO_MAP4_TMR5_0001         : TMR5 Alternate Function mapping 0001: CH1/CH2
  *     @arg AFIO_MAP4_TMR5_1000         : TMR5 Alternate Function mapping 1000: CH4 
  *     @arg AFIO_MAP4_TMR5_1001         : TMR5 Alternate Function mapping 1001: CH1/CH2+CH4 
  *     @arg AFIO_MAP5_I2C1_0001         : I2C1 Alternate Function mapping 0001
  *     @arg AFIO_MAP5_I2C1_0011         : I2C1 Alternate Function mapping 0011
  *     @arg AFIO_MAP5_I2C2_0001         : I2C2 Alternate Function mapping 0001
  *     @arg AFIO_MAP5_I2C2_0010         : I2C2 Alternate Function mapping 0010
  *     @arg AFIO_MAP5_I2C2_0011         : I2C2 Alternate Function mapping 0011
  *     @arg AFIO_MAP5_SPI1_0001         : SPI1 Alternate Function mapping 
  *     @arg AFIO_MAP5_SPI2_0001         : SPI2 Alternate Function mapping 
  *     @arg AFIO_MAP6_CAN1_0010         : CAN1 Alternate Function mapping 
  *     @arg AFIO_MAP6_CAN2_0001         : CAN2 Alternate Function mapping 
  *     @arg AFIO_MAP6_SDIO_0100         : SDIO Alternate Function mapping 100 
  *     @arg AFIO_MAP6_SDIO_0101         : SDIO Alternate Function mapping 101 
  *     @arg AFIO_MAP6_SDIO_0110         : SDIO Alternate Function mapping 110 
  *     @arg AFIO_MAP6_SDIO_0111         : SDIO Alternate Function mapping 111 
  *     @arg AFIO_MAP6_USART1_0001       : USART1 Alternate Function mapping 
  *     @arg AFIO_MAP6_USART3_0001       : USART3 Partial Alternate Function mapping 
  *     @arg AFIO_MAP6_UART4_0001        : UART4 Alternate Function mapping 
  *     @arg AFIO_MAP7_SPIF_1000         : EXT_FLASH Alternate Function mapping  
  *     @arg AFIO_MAP7_SPIF_1001         : EXT_FLASH Alternate Function enable  
  *     @arg AFIO_MAP7_ADC1_0001         : ADC1 External Trigger Injected Conversion remapping 
  *     @arg AFIO_MAP7_ADC1_0010         : ADC1 External Trigger Regular Conversion remapping 
  *     @arg AFIO_MAP7_ADC1_0011         : ADC1 External Trigger Regular & Injected Conversion remapping 
  *     @arg AFIO_MAP7_ADC2_0001         : ADC2 External Trigger Injected Conversion remapping 
  *     @arg AFIO_MAP7_ADC2_0010         : ADC2 External Trigger Regular Conversion remapping 
  *     @arg AFIO_MAP7_ADC2_0011         : ADC2 External Trigger Regular & Injected Conversion remapping 
  *     @arg AFIO_MAP7_SWJTAG_0001       : Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST 
  *     @arg AFIO_MAP7_SWJTAG_0010       : JTAG-DP Disabled and SW-DP Enabled 
  *     @arg AFIO_MAP7_SWJTAG_0100       : Full SWJ Disabled (JTAG-DP + SW-DP) 
  *     @arg AFIO_MAP7_PD01_0001         : PD01 Alternate Function mapping 
  * @param  NewState: new state of the port pin remapping.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_PinsRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState)
{
#ifndef AT32F403xx
  if(IS_GREMAP(GPIO_Remap))
  {
    uint32_t reg_ost = 0x00, bit_ost = 0x00, Remap_Addr, Remap_val;
    volatile uint32_t *AFIO_MAPx;

    /* Calculate the remap register value by parameter GPIO_Remap */
    Remap_Addr = GPIO_Remap & 0x7FFFFFFF;
    reg_ost = Remap_Addr >> 7;
    Remap_Addr &= 0x7f;
    bit_ost = Remap_Addr >> 4;
    Remap_Addr &= 0x0f;
    
#ifdef AT32F415xx
    if(reg_ost != AFIO_MAP8)
      Remap_val = Remap_Addr << (bit_ost * 4);
    else
      Remap_val = Remap_Addr << (bit_ost/2 * 4);
#else
    Remap_val = Remap_Addr << (bit_ost * 4);
#endif
    
    switch(reg_ost)
    {
      case AFIO_MAP3:
        AFIO_MAPx = &(AFIO->MAP3);
        break;

      case AFIO_MAP4:
        AFIO_MAPx = &(AFIO->MAP4);
        break;

      case AFIO_MAP5:
        AFIO_MAPx = &(AFIO->MAP5);
        break;

      case AFIO_MAP6:
        AFIO_MAPx = &(AFIO->MAP6);
        break;

      case AFIO_MAP7:
        AFIO_MAPx = &(AFIO->MAP7);
        break;
      
#ifndef AT32F413xx
      case AFIO_MAP8:
        AFIO_MAPx = &(AFIO->MAP8);
        break;
#endif
      
      default:
        break;
    }

    if(bit_ost == BITS0)
    {
#ifdef AT32F415xx
      if(reg_ost == AFIO_MAP8)
      {
        *AFIO_MAPx &= 0xFFFFFFFC;
      }else
      {
        *AFIO_MAPx &= OFFSET_MASK0;
      }
#else
      *AFIO_MAPx &= OFFSET_MASK0;
#endif
    }
    else if(bit_ost == BITS1)
    {
      #ifdef AT32F415xx
      if(reg_ost == AFIO_MAP8)
      {
        *AFIO_MAPx &= 0xFFFFFFF3;
      }else
      {
        *AFIO_MAPx &= OFFSET_MASK1;
      }
      #elif defined (AT32F403Axx) || defined (AT32F407xx)
      if(reg_ost == AFIO_MAP4)
      {
        if(Remap_Addr > 4)
        {
          *AFIO_MAPx &= 0xFFFFFF3F;
        }else
        {
          *AFIO_MAPx &= 0xFFFFFFCF;
        }
      }else
      {
        *AFIO_MAPx &= OFFSET_MASK1;
      }
      #else
      *AFIO_MAPx &= OFFSET_MASK1;
      #endif
    }
    else if(bit_ost == BITS2)
    {
#ifdef AT32F415xx
      if(reg_ost == AFIO_MAP8)
      {
        *AFIO_MAPx &= 0xFFFFFFCF;
      }else
      {
        *AFIO_MAPx &= OFFSET_MASK2;
      }
#else
      *AFIO_MAPx &= OFFSET_MASK2;
#endif
    }
    else if(bit_ost == BITS3)
    {
#ifdef AT32F415xx
      if(reg_ost == AFIO_MAP8)
      {
        *AFIO_MAPx &= 0xFFFFFF3F;
      }else
      {
        *AFIO_MAPx &= OFFSET_MASK3;
      }
#else
      *AFIO_MAPx &= OFFSET_MASK3;
#endif
    }
    else if(bit_ost == BITS4)
    {
      *AFIO_MAPx &= OFFSET_MASK4;
    }
    else if(bit_ost == BITS5)
    {
      *AFIO_MAPx &= OFFSET_MASK5;
    }
    else if(bit_ost == BITS6)
    {
      *AFIO_MAPx &= OFFSET_MASK6;
    }
    else if(bit_ost == BITS7)
    {
      *AFIO_MAPx &= OFFSET_MASK7;
    }

    if(NewState == ENABLE)
    {
      *AFIO_MAPx |= Remap_val;
    }

  }
  else
#endif
  {
    /* Check the parameters */
    assert_param(IS_GPIO_REMAP(GPIO_Remap));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    switch(GPIO_Remap)
    {
    case GPIO_Remap_I2C1:
    case GPIO_Remap_USART1:
    case GPIO_Remap_PD01:
    case GPIO_Remap_TMR5CH4_LSI:
    case GPIO_Remap_ADC1_EXTRGINJ:
    case GPIO_Remap_ADC1_EXTRGREG:
#if defined (AT32F403xx) || defined (AT32F403Axx) || defined (AT32F407xx)
    case GPIO_Remap_USART2:
    case GPIO_Remap_TMR4:
#endif
#ifndef AT32F415xx
    case GPIO_Remap_ADC2_EXTRGINJ:
    case GPIO_Remap_ADC2_EXTRGREG:
#endif
      AFIO->MAP &= ~GPIO_Remap;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap;
      }

      break;

    case GPIO_Remap01_SPI1:
      AFIO->MAP &= 0x7FFFFFFE;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap01_SPI1;
      }

      break;
      
#ifdef AT32F403xx
    case GPIO_Remap10_SPI1:
      AFIO->MAP &= 0x7FFFFFFE;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap10_SPI1;
      }

      break;
#endif
      
    case GPIO_PartialRemap_USART3:
      AFIO->MAP &= 0xFFFFFFCF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_PartialRemap_USART3;
      }

      break;
      
#ifdef AT32F415xx
    case GPIO_PartialRemap2_USART3:
      AFIO->MAP &= 0xFFFFFFCF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_PartialRemap2_USART3;
      }

      break;
      
    case GPIO_PartialRemap2_TMR1:
      AFIO->MAP &= 0xFFFFFF3F;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_PartialRemap2_TMR1;
      }

      break;
#endif

#if defined (AT32F403xx) || defined (AT32F403Axx) || defined (AT32F407xx)
    case GPIO_FullRemap_USART3:
      AFIO->MAP &= 0xFFFFFFCF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_FullRemap_USART3;
      }

      break;
#endif

    case GPIO_PartialRemap_TMR1:
      AFIO->MAP &= 0xFFFFFF3F;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_PartialRemap_TMR1;
      }

      break;

#if defined (AT32F403xx) || defined (AT32F403Axx) || defined (AT32F407xx)
    case GPIO_FullRemap_TMR1:
      AFIO->MAP &= 0xFFFFFF3F;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_FullRemap_TMR1;
      }

      break;
#endif

    case GPIO_PartialRemap1_TMR2:
      AFIO->MAP &= 0xFFFFFCFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_PartialRemap1_TMR2;
      }

      break;

    case GPIO_PartialRemap2_TMR2:
      AFIO->MAP &= 0xFFFFFCFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_PartialRemap2_TMR2;
      }

      break;

    case GPIO_FullRemap_TMR2:
      AFIO->MAP &= 0xFFFFFCFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_FullRemap_TMR2;
      }

      break;

    case GPIO_PartialRemap_TMR3:
      AFIO->MAP &= 0xFFFFF3FF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_PartialRemap_TMR3;
      }

      break;

    case GPIO_FullRemap_TMR3:
      AFIO->MAP &= 0xFFFFF3FF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_FullRemap_TMR3;
      }

      break;

    case GPIO_Remap1_CAN1:
      AFIO->MAP &= 0xFFFF9FFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap1_CAN1;
      }

      break;

#if defined (AT32F403xx) || defined (AT32F403Axx) || defined (AT32F407xx)
    case GPIO_Remap2_CAN1:
      AFIO->MAP &= 0xFFFF9FFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap2_CAN1;
      }

      break;
#endif

    case GPIO_Remap_SWJ_NoJNTRST:
      AFIO->MAP &= 0xF8FFFFFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap_SWJ_NoJNTRST;
      }

      break;

    case GPIO_Remap_SWJ_JTAGDisable:
      AFIO->MAP &= 0xF8FFFFFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap_SWJ_JTAGDisable;
      }

      break;

    case GPIO_Remap_SWJ_AllDisable:
      AFIO->MAP &= 0xF8FFFFFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap_SWJ_AllDisable;
      }

      break;
      
#if defined (AT32F403Axx) || defined (AT32F407xx)
    case GPIO_Remap_PTP_PPS:
      AFIO->MAP &= ~GPIO_Remap_PTP_PPS;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap_PTP_PPS;
      }

      break;
      
    case GPIO_Remap_TMR2ITR1:
      AFIO->MAP &= ~GPIO_Remap_TMR2ITR1;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap_TMR2ITR1;
      }

      break;
      
    case GPIO_Remap_SPI3:
      AFIO->MAP &= ~GPIO_Remap_SPI3;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap_SPI3;
      }

      break;
      
    case GPIO_Remap_MII_RMII:
      AFIO->MAP &= ~GPIO_Remap_MII_RMII;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap_MII_RMII;
      }

      break;
      
    case GPIO_Remap_CAN2:
      AFIO->MAP &= ~GPIO_Remap_CAN2;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap_CAN2;
      }

      break;
      
    case GPIO_Remap_ETH:
      AFIO->MAP &= ~GPIO_Remap_ETH;

      if(NewState == ENABLE)
      {
        AFIO->MAP |= GPIO_Remap_ETH;
      }

      break;
#endif
      
#if defined (AT32F403xx)
    case GPIO_Remap_TMR15:
    case GPIO_Remap_TMR10:
    case GPIO_Remap_TMR11:
    case GPIO_Remap_TMR13:
    case GPIO_Remap_TMR14:
      AFIO->MAP2 &= ~(GPIO_Remap & 0x003FFFFF);

      if(NewState == ENABLE)
      {
        AFIO->MAP2 |= (GPIO_Remap & 0x003FFFFF);
      }

      break;
#endif
      
#if defined (AT32F403xx) || defined (AT32F403Axx) || defined (AT32F407xx)
    case GPIO_Remap_TMR9:
    case GPIO_Remap_XMC_NADV:
    case GPIO_Remap_SPI4:
    case GPIO_Remap_I2C3:
    case GPIO_Remap_EXT_FLASH:
      AFIO->MAP2 &= ~(GPIO_Remap & 0x003FFFFF);

      if(NewState == ENABLE)
      {
        AFIO->MAP2 |= (GPIO_Remap & 0x003FFFFF);
      }

      break;

    case GPIO_Remap01_SDIO2:
      AFIO->MAP2 &= 0xFFE7FFFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP2 |= (GPIO_Remap01_SDIO2 & 0x003FFFFF);
      }

      break;

    case GPIO_Remap10_SDIO2:
      AFIO->MAP2 &= 0xFFE7FFFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP2 |= (GPIO_Remap10_SDIO2 & 0x003FFFFF);
      }

      break;

    case GPIO_Remap11_SDIO2:
      AFIO->MAP2 &= 0xFFE7FFFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP2 |= (GPIO_Remap11_SDIO2 & 0x003FFFFF);
      }

      break;
#elif defined (AT32F413xx)
    case GPIO_Remap_EXT_FLASH:
      AFIO->MAP2 &= ~(GPIO_Remap & 0x003FFFFF);

      if(NewState == ENABLE)
      {
        AFIO->MAP2 |= (GPIO_Remap & 0x003FFFFF);
      }

      break;
#elif defined (AT32F415xx)
    case GPIO_Remap01_COMP:
      AFIO->MAP2 &= 0xF3FFFFFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP2 |= (GPIO_Remap01_COMP & 0xBFFFFFFF);
      }

      break;
      
    case GPIO_Remap10_COMP:
      AFIO->MAP2 &= 0xF3FFFFFF;

      if(NewState == ENABLE)
      {
        AFIO->MAP2 |= (GPIO_Remap10_COMP & 0xBFFFFFFF);
      }

      break;
#endif
      
    default:
      break;
    }
  }
}

/**
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  GPIO_PortSource: selects the GPIO port to be used as source for EXTI lines.
  *   This parameter can be GPIO_PortSourceGPIOx where x can be (A..G).
  * @param  GPIO_PinSource: specifies the EXTI line to be configured.
  *   This parameter can be GPIO_PinSourcex where x can be (0..15).
  * @retval None
  */
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmp = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_EXTI_PORT_SOURCE(GPIO_PortSource));
  assert_param(IS_GPIO_PINS_SOURCE(GPIO_PinSource));

  tmp = ((uint32_t)0x0F) << (0x04 * (GPIO_PinSource & (uint8_t)0x03));
  AFIO->EXTIC[GPIO_PinSource >> 0x02] &= ~tmp;
  AFIO->EXTIC[GPIO_PinSource >> 0x02] |= (((uint32_t)GPIO_PortSource) << (0x04 * (GPIO_PinSource & (uint8_t)0x03)));
}

/**
  * @brief  Selects the Ethernet media interface.
  * @note   This function applies only to AT32 Connectivity line devices.  
  * @param  GPIO_ETH_MediaInterface: specifies the Media Interface mode.
  *   This parameter can be one of the following values:
  *     @arg GPIO_ETH_MediaInterface_MII: MII mode
  *     @arg GPIO_ETH_MediaInterface_RMII: RMII mode    
  * @retval None
  */
void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface) 
{ 
  assert_param(IS_GPIO_ETH_MEDIA_INTERFACE(GPIO_ETH_MediaInterface)); 
  /* Configure MII_RMII selection bit */ 
  *(__IO uint32_t *) MAPR_MII_RMII_SEL_BB = GPIO_ETH_MediaInterface; 
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


