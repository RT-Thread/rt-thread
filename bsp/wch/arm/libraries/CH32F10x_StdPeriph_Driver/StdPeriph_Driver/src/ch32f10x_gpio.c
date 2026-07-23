/***************COPYRIGHT(C)  2019 WCH. A11 rights reserved*********************
* File Name          : ch32f10x_gpio.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2019/10/15
* Description        : This file provides all the GPIO firmware functions. 
*******************************************************************************/
#include "ch32f10x_gpio.h"
#include "ch32f10x_rcc.h"


/* ------------ RCC registers bit address in the alias region ----------------*/
#define AFIO_OFFSET                  (AFIO_BASE - PERIPH_BASE)

/* --- ECR Register -----*/
/* Alias word address of EVOE bit */
#define ECR_OFFSET                   (AFIO_OFFSET + 0x00)
#define EVOE_BitNumber               ((uint8_t)0x07)
#define ECR_EVOE_BB                  (PERIPH_BB_BASE + (ECR_OFFSET * 32) + (EVOE_BitNumber * 4))


/* ---  PCFR1 Register ---*/ 
/* Alias word address of MII_RMII_SEL bit */ 
#define PCFR1_OFFSET                 (AFIO_OFFSET + 0x04) 
#define MII_RMII_SEL_BitNumber       ((u8)0x17) 
#define PCFR1_MII_RMII_SEL_BB        (PERIPH_BB_BASE + (PCFR1_OFFSET * 32) + (MII_RMII_SEL_BitNumber * 4))

#define ECR_PORTPINCONFIG_MASK      ((uint16_t)0xFF80)
#define LSB_MASK                    ((uint16_t)0xFFFF)
#define DBGAFR_POSITION_MASK        ((uint32_t)0x000F0000)
#define DBGAFR_SWJCFG_MASK          ((uint32_t)0xF0FFFFFF)
#define DBGAFR_LOCATION_MASK        ((uint32_t)0x00200000)
#define DBGAFR_NUMBITS_MASK         ((uint32_t)0x00100000)


/*******************************************************************************
* Function Name  : GPIO_DeInit
* Description    : Deinitializes the GPIOx peripheral registers to their default reset values.
* Input          : GPIOx: where x can be (A..G) to select the GPIO peripheral.
* Return         : None
*******************************************************************************/
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
  if (GPIOx == GPIOA)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, DISABLE);
  }
  else if (GPIOx == GPIOB)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB, DISABLE);
  }
  else if (GPIOx == GPIOC)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, DISABLE);
  }
  else if (GPIOx == GPIOD)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD, DISABLE);
  }    
  else if (GPIOx == GPIOE)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE, DISABLE);
  } 
  else if (GPIOx == GPIOF)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF, DISABLE);
  }
  else
  {
    if (GPIOx == GPIOG)
    {
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG, DISABLE);
    }
  }
}

/*******************************************************************************
* Function Name  : GPIO_AFIODeInit
* Description    : Deinitializes the Alternate Functions (remap, event control
*      and EXTI configuration) registers to their default reset values.
* Input          : None
* Return         : None
*******************************************************************************/
void GPIO_AFIODeInit(void)
{
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO, DISABLE);
}

/*******************************************************************************
* Function Name  : GPIO_Init
* Description    : GPIOx: where x can be (A..G) to select the GPIO peripheral.
* Input          : GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
*      contains the configuration information for the specified GPIO peripheral.
* Return         : None
*******************************************************************************/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;

  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
	
  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  { 
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
  }

  if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CFGLR;
		
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos;
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
			
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        tmpreg |= (currentmode << pos);

        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BCR = (((uint32_t)0x01) << pinpos);
        }
        else
        {
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
            GPIOx->BSHR = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }
    GPIOx->CFGLR = tmpreg;
  }

  if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
    tmpreg = GPIOx->CFGHR;
		
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
			
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        tmpreg |= (currentmode << pos);

        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BCR = (((uint32_t)0x01) << (pinpos + 0x08));
        }

        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSHR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }
    GPIOx->CFGHR = tmpreg;
  }
}

/*******************************************************************************
* Function Name  : GPIO_StructInit
* Description    : Fills each GPIO_InitStruct member with its default
* Input          : GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure 
*      which will be initialized.
* Return         : None
*******************************************************************************/
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN_FLOATING;
}

/*******************************************************************************
* Function Name  : GPIO_ReadInputDataBit
* Description    : GPIOx: where x can be (A..G) to select the GPIO peripheral.
* Input          : GPIO_Pin:  specifies the port bit to read.
*                    This parameter can be GPIO_Pin_x where x can be (0..15).
* Return         : The input port pin value.
*******************************************************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  
  if ((GPIOx->INDR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
	
  return bitstatus;
}

/*******************************************************************************
* Function Name  : GPIO_ReadInputData
* Description    : Reads the specified GPIO input data port.
* Input          : GPIOx: where x can be (A..G) to select the GPIO peripheral.
* Return         : The output port pin value.
*******************************************************************************/
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
  return ((uint16_t)GPIOx->INDR);
}

/*******************************************************************************
* Function Name  : GPIO_ReadOutputDataBit
* Description    : Reads the specified output data port bit.
* Input          : GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                  GPIO_Pin:  specifies the port bit to read.
*                    This parameter can be GPIO_Pin_x where x can be (0..15).
* Return         : The output port pin value.
*******************************************************************************/
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
 
  if ((GPIOx->OUTDR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
	
  return bitstatus;
}

/*******************************************************************************
* Function Name  : GPIO_ReadOutputData
* Description    : Reads the specified GPIO output data port.
* Input          : GPIOx: where x can be (A..G) to select the GPIO peripheral.        
* Return         : GPIO output port pin value.
*******************************************************************************/
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{ 
  return ((uint16_t)GPIOx->OUTDR);
}

/*******************************************************************************
* Function Name  : GPIO_SetBits
* Description    : Sets the selected data port bits.
* Input          : GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                  GPIO_Pin: specifies the port bits to be written.
*                    This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
* Return         : None
*******************************************************************************/
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  GPIOx->BSHR = GPIO_Pin;
}

/*******************************************************************************
* Function Name  : GPIO_ResetBits
* Description    : Clears the selected data port bits.
* Input          : GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                  GPIO_Pin: specifies the port bits to be written.
*                    This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
* Return         : None
*******************************************************************************/
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  GPIOx->BCR = GPIO_Pin;
}

/*******************************************************************************
* Function Name  : GPIO_WriteBit
* Description    : Sets or clears the selected data port bit.
* Input          : GPIO_Pin: specifies the port bit to be written.
*                    This parameter can be one of GPIO_Pin_x where x can be (0..15).
*                  BitVal: specifies the value to be written to the selected bit.
*                    Bit_SetL: to clear the port pin.
*                    Bit_SetH: to set the port pin.                  
* Return         : None
*******************************************************************************/
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  if (BitVal != Bit_RESET)
  {
    GPIOx->BSHR = GPIO_Pin;
  }
  else
  {
    GPIOx->BCR = GPIO_Pin;
  }
}

/*******************************************************************************
* Function Name  : GPIO_Write
* Description    : Writes data to the specified GPIO data port.
* Input          : GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                  PortVal: specifies the value to be written to the port output data register.
* Return         : None
*******************************************************************************/
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
  GPIOx->OUTDR = PortVal;
}

/*******************************************************************************
* Function Name  : GPIO_PinLockConfig
* Description    : Locks GPIO Pins configuration registers.
* Input          : GPIOx: where x can be (A..G) to select the GPIO peripheral.
*                  GPIO_Pin: specifies the port bit to be written.
*                    This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
* Return         : None
*******************************************************************************/
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp = 0x00010000;
  
  tmp |= GPIO_Pin;
  GPIOx->LCKR = tmp;
  GPIOx->LCKR =  GPIO_Pin;
  GPIOx->LCKR = tmp;
  tmp = GPIOx->LCKR;
  tmp = GPIOx->LCKR;
}

/*******************************************************************************
* Function Name  : GPIO_EventOutputConfig
* Description    : Selects the GPIO pin used as Event output.
* Input          : GPIO_PortSource: selects the GPIO port to be used as source
*      for Event output.
*                    This parameter can be GPIO_PortSourceGPIOx where x can be (A..E).
*                  GPIO_PinSource: specifies the pin for the Event output.
*                    This parameter can be GPIO_PinSourcex where x can be (0..15).
* Return         : None
*******************************************************************************/
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmpreg = 0x00;
  
  tmpreg = AFIO->ECR;
  tmpreg &= ECR_PORTPINCONFIG_MASK;
  tmpreg |= (uint32_t)GPIO_PortSource << 0x04;
  tmpreg |= GPIO_PinSource;
  AFIO->ECR = tmpreg;
}

/*******************************************************************************
* Function Name  : GPIO_EventOutputCmd
* Description    : Enables or disables the Event Output.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void GPIO_EventOutputCmd(FunctionalState NewState)
{
  *(__IO uint32_t *) ECR_EVOE_BB = (uint32_t)NewState;
}

/*******************************************************************************
* Function Name  : GPIO_PinRemapConfig
* Description    : Changes the mapping of the specified pin.
* Input          : GPIO_Remap: selects the pin to remap.
*                    GPIO_Remap_SPI1: SPI1 Alternate Function mapping
*                    GPIO_Remap_I2C1: I2C1 Alternate Function mapping
*                    GPIO_Remap_USART1: USART1 Alternate Function mapping
*                    GPIO_Remap_USART2: USART2 Alternate Function mapping
*                    GPIO_PartialRemap_USART3: USART3 Partial Alternate Function mapping
*                    GPIO_FullRemap_USART3: USART3 Full Alternate Function mapping
*                    GPIO_PartialRemap_TIM1: TIM1 Partial Alternate Function mapping
*                    GPIO_FullRemap_TIM1: TIM1 Full Alternate Function mapping
*                    GPIO_PartialRemap1_TIM2: TIM2 Partial1 Alternate Function mapping
*                    GPIO_PartialRemap2_TIM2: TIM2 Partial2 Alternate Function mapping
*                    GPIO_FullRemap_TIM2: TIM2 Full Alternate Function mapping
*                    GPIO_PartialRemap_TIM3: TIM3 Partial Alternate Function mapping
*                    GPIO_FullRemap_TIM3: TIM3 Full Alternate Function mapping
*                    GPIO_Remap_TIM4: TIM4 Alternate Function mapping
*                    GPIO_Remap1_CAN1: CAN1 Alternate Function mapping
*                    GPIO_Remap2_CAN1: CAN1 Alternate Function mapping
*                    GPIO_Remap_PD01: PD01 Alternate Function mapping
*                    GPIO_Remap_ADC1_ETRGINJ: ADC1 External Trigger Injected Conversion remapping
*                    GPIO_Remap_ADC1_ETRGREG: ADC1 External Trigger Regular Conversion remapping
*                    GPIO_Remap_SWJ_NoJTRST: Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST
*                    GPIO_Remap_SWJ_JTAGDisable: JTAG-DP Disabled and SW-DP Enabled
*                    GPIO_Remap_SWJ_Disable: Full SWJ Disabled (JTAG-DP + SW-DP)  
*                    GPIO_Remap_TIM2ITR1_PTP_SOF: Ethernet PTP output or USB OTG SOF (Start of Frame) 
*      connected to TIM2 Internal Trigger 1 for calibration (only for Connectivity line devices).If the
*      is enabled the TIM2 ITR1 is connected to Ethernet PTP output. When Reset TIM2 ITR1 is connected  
*      to USB OTG SOF output.    
*                    GPIO_Remap_TIM1_DMA: TIM1 DMA requests mapping (only for Value line devices)
*                    GPIO_Remap_TIM67_DAC_DMA: TIM6/TIM7 and DAC DMA requests remapping (only for High density Value line devices)
*                    GPIO_Remap_MISC: Miscellaneous Remap (DMA2 Channel5 Position and DAC Trigger remapping, 
*      only for High density Value line devices)     
*                  NewState: ENABLE or DISABLE.             
* Return         : None
*******************************************************************************/
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState)
{
  uint32_t tmp = 0x00, tmp1 = 0x00, tmpreg = 0x00, tmpmask = 0x00;

  if((GPIO_Remap & 0x80000000) == 0x80000000)
  {
    tmpreg = AFIO->PCFR2;
  }
  else
  {
    tmpreg = AFIO->PCFR1;
  }

  tmpmask = (GPIO_Remap & DBGAFR_POSITION_MASK) >> 0x10;
  tmp = GPIO_Remap & LSB_MASK;

  if ((GPIO_Remap & (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK)) == (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK))
  {
    tmpreg &= DBGAFR_SWJCFG_MASK;
    AFIO->PCFR1 &= DBGAFR_SWJCFG_MASK;
  }
  else if ((GPIO_Remap & DBGAFR_NUMBITS_MASK) == DBGAFR_NUMBITS_MASK)
  {
    tmp1 = ((uint32_t)0x03) << tmpmask;
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

  if((GPIO_Remap & 0x80000000) == 0x80000000)
  {
    AFIO->PCFR2 = tmpreg;
  }
  else
  {
    AFIO->PCFR1 = tmpreg;
  }  
}

/*******************************************************************************
* Function Name  : GPIO_EXTILineConfig
* Description    : Selects the GPIO pin used as EXTI Line.
* Input          : GPIO_PortSource: selects the GPIO port to be used as source for EXTI lines.
*                    This parameter can be GPIO_PortSourceGPIOx where x can be (A..G).
*                  GPIO_PinSource: specifies the EXTI line to be configured.
*                    This parameter can be GPIO_PinSourcex where x can be (0..15).
* Return         : None
*******************************************************************************/
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmp = 0x00;

  tmp = ((uint32_t)0x0F) << (0x04 * (GPIO_PinSource & (uint8_t)0x03));
  AFIO->EXTICR[GPIO_PinSource >> 0x02] &= ~tmp;
  AFIO->EXTICR[GPIO_PinSource >> 0x02] |= (((uint32_t)GPIO_PortSource) << (0x04 * (GPIO_PinSource & (uint8_t)0x03)));
}


  




