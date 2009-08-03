/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_gpio.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the GPIO firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ------------ RCC registers bit address in the alias region ----------- */
#define AFIO_OFFSET                 (AFIO_BASE - PERIPH_BASE)

/* --- EVENTCR Register ---*/
/* Alias word address of EVOE bit */
#define EVCR_OFFSET                 (AFIO_OFFSET + 0x00)
#define EVOE_BitNumber              ((u8)0x07)
#define EVCR_EVOE_BB                (PERIPH_BB_BASE + (EVCR_OFFSET * 32) + (EVOE_BitNumber * 4))

#define EVCR_PORTPINCONFIG_MASK     ((u16)0xFF80)
#define LSB_MASK                    ((u16)0xFFFF)
#define DBGAFR_POSITION_MASK        ((u32)0x000F0000)
#define DBGAFR_SWJCFG_MASK          ((u32)0xF0FFFFFF)
#define DBGAFR_LOCATION_MASK        ((u32)0x00200000)
#define DBGAFR_NUMBITS_MASK         ((u32)0x00100000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : GPIO_DeInit
* Description    : Deinitializes the GPIOx peripheral registers to their default
*                  reset values.
* Input          : - GPIOx: where x can be (A..G) to select the GPIO peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  switch (*(u32*)&GPIOx)
  {
    case GPIOA_BASE:
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, DISABLE);
      break;

    case GPIOB_BASE:
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB, DISABLE);
      break;

    case GPIOC_BASE:
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, DISABLE);
      break;

    case GPIOD_BASE:
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD, DISABLE);
      break;
      
    case GPIOE_BASE:
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE, DISABLE);
      break; 

    case GPIOF_BASE:
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF, DISABLE);
      break;

    case GPIOG_BASE:
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG, DISABLE);
      break;                       

    default:
      break;
  }
}

/*******************************************************************************
* Function Name  : GPIO_AFIODeInit
* Description    : Deinitializes the Alternate Functions (remap, event control
*                  and EXTI configuration) registers to their default reset
*                  values.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_AFIODeInit(void)
{
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO, DISABLE);
}

/*******************************************************************************
* Function Name  : GPIO_Init
* Description    : Initializes the GPIOx peripheral according to the specified
*                  parameters in the GPIO_InitStruct.
* Input          : - GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                  - GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
*                    contains the configuration information for the specified GPIO
*                    peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  u32 currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  u32 tmpreg = 0x00, pinmask = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));  
  
/*---------------------------- GPIO Mode Configuration -----------------------*/
  currentmode = ((u32)GPIO_InitStruct->GPIO_Mode) & ((u32)0x0F);

  if ((((u32)GPIO_InitStruct->GPIO_Mode) & ((u32)0x10)) != 0x00)
  { 
    /* Check the parameters */
    assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));
    /* Output mode */
    currentmode |= (u32)GPIO_InitStruct->GPIO_Speed;
  }

/*---------------------------- GPIO CRL Configuration ------------------------*/
  /* Configure the eight low port pins */
  if (((u32)GPIO_InitStruct->GPIO_Pin & ((u32)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CRL;

    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((u32)0x01) << pinpos;
      /* Get the port pins position */
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding low control register bits */
        pinmask = ((u32)0x0F) << pos;
        tmpreg &= ~pinmask;

        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);

        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((u32)0x01) << pinpos);
        }
        else
        {
          /* Set the corresponding ODR bit */
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
            GPIOx->BSRR = (((u32)0x01) << pinpos);
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
      pos = (((u32)0x01) << (pinpos + 0x08));
      /* Get the port pins position */
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding high control register bits */
        pinmask = ((u32)0x0F) << pos;
        tmpreg &= ~pinmask;

        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);

        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((u32)0x01) << (pinpos + 0x08));
        }
        /* Set the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSRR = (((u32)0x01) << (pinpos + 0x08));
        }
      }
    }
    GPIOx->CRH = tmpreg;
  }
}

/*******************************************************************************
* Function Name  : GPIO_StructInit
* Description    : Fills each GPIO_InitStruct member with its default value.
* Input          : - GPIO_InitStruct : pointer to a GPIO_InitTypeDef structure
*                    which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN_FLOATING;
}

/*******************************************************************************
* Function Name  : GPIO_ReadInputDataBit
* Description    : Reads the specified input port pin.
* Input          : - GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                : - GPIO_Pin:  specifies the port bit to read.
*                    This parameter can be GPIO_Pin_x where x can be (0..15).
* Output         : None
* Return         : The input port pin value.
*******************************************************************************/
u8 GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{
  u8 bitstatus = 0x00;
  
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin)); 
  
  if ((GPIOx->IDR & GPIO_Pin) != (u32)Bit_RESET)
  {
    bitstatus = (u8)Bit_SET;
  }
  else
  {
    bitstatus = (u8)Bit_RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : GPIO_ReadInputData
* Description    : Reads the specified GPIO input data port.
* Input          : - GPIOx: where x can be (A..G) to select the GPIO peripheral.
* Output         : None
* Return         : GPIO input data port value.
*******************************************************************************/
u16 GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  return ((u16)GPIOx->IDR);
}

/*******************************************************************************
* Function Name  : GPIO_ReadOutputDataBit
* Description    : Reads the specified output data port bit.
* Input          : - GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                : - GPIO_Pin:  specifies the port bit to read.
*                    This parameter can be GPIO_Pin_x where x can be (0..15).
* Output         : None
* Return         : The output port pin value.
*******************************************************************************/
u8 GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{
  u8 bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin)); 
  
  if ((GPIOx->ODR & GPIO_Pin) != (u32)Bit_RESET)
  {
    bitstatus = (u8)Bit_SET;
  }
  else
  {
    bitstatus = (u8)Bit_RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : GPIO_ReadOutputData
* Description    : Reads the specified GPIO output data port.
* Input          : - GPIOx: where x can be (A..G) to select the GPIO peripheral.
* Output         : None
* Return         : GPIO output data port value.
*******************************************************************************/
u16 GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    
  return ((u16)GPIOx->ODR);
}

/*******************************************************************************
* Function Name  : GPIO_SetBits
* Description    : Sets the selected data port bits.
* Input          : - GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                  - GPIO_Pin: specifies the port bits to be written.
*                    This parameter can be any combination of GPIO_Pin_x where 
*                    x can be (0..15).
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_SetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->BSRR = GPIO_Pin;
}

/*******************************************************************************
* Function Name  : GPIO_ResetBits
* Description    : Clears the selected data port bits.
* Input          : - GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                  - GPIO_Pin: specifies the port bits to be written.
*                    This parameter can be any combination of GPIO_Pin_x where 
*                    x can be (0..15).
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->BRR = GPIO_Pin;
}

/*******************************************************************************
* Function Name  : GPIO_WriteBit
* Description    : Sets or clears the selected data port bit.
* Input          : - GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                  - GPIO_Pin: specifies the port bit to be written.
*                    This parameter can be one of GPIO_Pin_x where x can be (0..15).
*                  - BitVal: specifies the value to be written to the selected bit.
*                    This parameter can be one of the BitAction enum values:
*                       - Bit_RESET: to clear the port pin
*                       - Bit_SET: to set the port pin
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, BitAction BitVal)
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

/*******************************************************************************
* Function Name  : GPIO_Write
* Description    : Writes data to the specified GPIO data port.
* Input          : - GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                  - PortVal: specifies the value to be written to the port output
*                    data register.
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Write(GPIO_TypeDef* GPIOx, u16 PortVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  GPIOx->ODR = PortVal;
}

/*******************************************************************************
* Function Name  : GPIO_PinLockConfig
* Description    : Locks GPIO Pins configuration registers.
* Input          : - GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                  - GPIO_Pin: specifies the port bit to be written.
*                    This parameter can be any combination of GPIO_Pin_x where 
*                    x can be (0..15).
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{
  u32 tmp = 0x00010000;
  
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

/*******************************************************************************
* Function Name  : GPIO_EventOutputConfig
* Description    : Selects the GPIO pin used as Event output.
* Input          : - GPIO_PortSource: selects the GPIO port to be used as source
*                    for Event output.
*                    This parameter can be GPIO_PortSourceGPIOx where x can be
*                    (A..E).
*                  - GPIO_PinSource: specifies the pin for the Event output.
*                    This parameter can be GPIO_PinSourcex where x can be (0..15).
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_EventOutputConfig(u8 GPIO_PortSource, u8 GPIO_PinSource)
{
  u32 tmpreg = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_EVENTOUT_PORT_SOURCE(GPIO_PortSource));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
    
  tmpreg = AFIO->EVCR;
  /* Clear the PORT[6:4] and PIN[3:0] bits */
  tmpreg &= EVCR_PORTPINCONFIG_MASK;
  tmpreg |= (u32)GPIO_PortSource << 0x04;
  tmpreg |= GPIO_PinSource;

  AFIO->EVCR = tmpreg;
}

/*******************************************************************************
* Function Name  : GPIO_EventOutputCmd
* Description    : Enables or disables the Event Output.
* Input          : - NewState: new state of the Event output.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_EventOutputCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(vu32 *) EVCR_EVOE_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : GPIO_PinRemapConfig
* Description    : Changes the mapping of the specified pin.
* Input          : - GPIO_Remap: selects the pin to remap.
*                    This parameter can be one of the following values:
*                       - GPIO_Remap_SPI1
*                       - GPIO_Remap_I2C1
*                       - GPIO_Remap_USART1
*                       - GPIO_Remap_USART2
*                       - GPIO_PartialRemap_USART3
*                       - GPIO_FullRemap_USART3
*                       - GPIO_PartialRemap_TIM1
*                       - GPIO_FullRemap_TIM1
*                       - GPIO_PartialRemap1_TIM2
*                       - GPIO_PartialRemap2_TIM2
*                       - GPIO_FullRemap_TIM2
*                       - GPIO_PartialRemap_TIM3
*                       - GPIO_FullRemap_TIM3
*                       - GPIO_Remap_TIM4
*                       - GPIO_Remap1_CAN
*                       - GPIO_Remap2_CAN
*                       - GPIO_Remap_PD01
*                       - GPIO_Remap_TIM5CH4_LSI
*                       - GPIO_Remap_ADC1_ETRGINJ
*                       - GPIO_Remap_ADC1_ETRGREG
*                       - GPIO_Remap_ADC2_ETRGINJ
*                       - GPIO_Remap_ADC2_ETRGREG
*                       - GPIO_Remap_SWJ_NoJTRST
*                       - GPIO_Remap_SWJ_JTAGDisable
*                       - GPIO_Remap_SWJ_Disable
*                  - NewState: new state of the port pin remapping.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_PinRemapConfig(u32 GPIO_Remap, FunctionalState NewState)
{
  u32 tmp = 0x00, tmp1 = 0x00, tmpreg = 0x00, tmpmask = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_REMAP(GPIO_Remap));
  assert_param(IS_FUNCTIONAL_STATE(NewState));  
  
  tmpreg = AFIO->MAPR;

  tmpmask = (GPIO_Remap & DBGAFR_POSITION_MASK) >> 0x10;
  tmp = GPIO_Remap & LSB_MASK;

  if ((GPIO_Remap & (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK)) == (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK))
  {
    tmpreg &= DBGAFR_SWJCFG_MASK;
    AFIO->MAPR &= DBGAFR_SWJCFG_MASK;
  }
  else if ((GPIO_Remap & DBGAFR_NUMBITS_MASK) == DBGAFR_NUMBITS_MASK)
  {
    tmp1 = ((u32)0x03) << tmpmask;
    tmpreg &= ~tmp1;
    tmpreg |= ~DBGAFR_SWJCFG_MASK;
  }
  else
  {
    tmpreg &= ~(tmp << ((GPIO_Remap >> 0x15)*0x10));
    tmpreg |= ~DBGAFR_SWJCFG_MASK;
  }

  if (NewState != DISABLE)
  {
    tmpreg |= (tmp << ((GPIO_Remap >> 0x15)*0x10));
  }

  AFIO->MAPR = tmpreg;
}

/*******************************************************************************
* Function Name  : GPIO_EXTILineConfig
* Description    : Selects the GPIO pin used as EXTI Line.
* Input          : - GPIO_PortSource: selects the GPIO port to be used as
*                    source for EXTI lines.
*                    This parameter can be GPIO_PortSourceGPIOx where x can be
*                    (A..G).
*                  - GPIO_PinSource: specifies the EXTI line to be configured.
*                   This parameter can be GPIO_PinSourcex where x can be (0..15).
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_EXTILineConfig(u8 GPIO_PortSource, u8 GPIO_PinSource)
{
  u32 tmp = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_EXTI_PORT_SOURCE(GPIO_PortSource));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  
  tmp = ((u32)0x0F) << (0x04 * (GPIO_PinSource & (u8)0x03));

  AFIO->EXTICR[GPIO_PinSource >> 0x02] &= ~tmp;
  AFIO->EXTICR[GPIO_PinSource >> 0x02] |= (((u32)GPIO_PortSource) << (0x04 * (GPIO_PinSource & (u8)0x03)));
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
