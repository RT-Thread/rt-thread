/**
  ******************************************************************************
  * @file    stmpe1600.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    10-February-2015
  * @brief   This file provides a set of functions needed to manage the STMPE1600
  *          IO Expander devices.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stmpe1600.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */ 
  
/** @defgroup STMPE1600
  * @{
  */   
  
/* Private typedef -----------------------------------------------------------*/

/** @defgroup STMPE1600_Private_Types_Definitions
  * @{
  */ 
  
/* Private define ------------------------------------------------------------*/

/** @defgroup STMPE1600_Private_Defines
  * @{
  */ 
#define STMPE1600_MAX_INSTANCE        2

/* Private macro -------------------------------------------------------------*/

/** @defgroup STMPE1600_Private_Macros
  * @{
  */ 
  
/* Private variables ---------------------------------------------------------*/
static uint16_t tmp = 0;

/** @defgroup STMPE1600_Private_Variables
  * @{
  */ 
/* IO driver structure initialization */  
IO_DrvTypeDef stmpe1600_io_drv = 
{
  stmpe1600_Init,
  stmpe1600_ReadID,
  stmpe1600_Reset,
  stmpe1600_Start,
  stmpe1600_IO_Config,
  stmpe1600_IO_WritePin,
  stmpe1600_IO_ReadPin,
  0,
  0,
  stmpe1600_IO_ITStatus,
  stmpe1600_IO_ClearIT,
};

uint8_t stmpe1600[STMPE1600_MAX_INSTANCE] = {0};
/**
  * @}
  */ 
    
/* Private function prototypes -----------------------------------------------*/

/** @defgroup STMPE1600_Private_Function_Prototypes
  * @{
  */
static uint8_t stmpe1600_GetInstance(uint16_t DeviceAddr);

/* Private functions ---------------------------------------------------------*/

/** @defgroup STMPE1600_Private_Functions
  * @{
  */ 

/**
  * @brief  Initialize the stmpe1600 and configure the needed hardware resources
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void stmpe1600_Init(uint16_t DeviceAddr)
{
  uint8_t instance;
  uint8_t empty;
  
  /* Check if device instance already exists */
  instance = stmpe1600_GetInstance(DeviceAddr);
  
  if(instance == 0xFF)
  {
    /* Look for empty instance */
    empty = stmpe1600_GetInstance(0);
    
    if(empty < STMPE1600_MAX_INSTANCE)
    {
      /* Register the current device instance */
      stmpe1600[empty] = DeviceAddr;
      
      /* Initialize IO BUS layer */
      IOE_Init(); 
      
      /* Generate stmpe1600 Software reset */
      stmpe1600_Reset(DeviceAddr);
    }
  } 
}

/**
  * @brief  Configures the touch Screen Controller (Single point detection)
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None.
  */
void stmpe1600_Start(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  /*Configuration already done during the initialization */ 
}

/**
  * @brief  Reset the stmpe1600 by Software.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void stmpe1600_Reset(uint16_t DeviceAddr)
{
  /* Power Down the stmpe1600 */
  IOE_Write(DeviceAddr, STMPE1600_REG_SYS_CTRL, (uint16_t)0x80);

  /* Wait for a delay to ensure registers erasing */
  IOE_Delay(2); 
  
  /* Power On the Codec after the power off: all registers are reinitialized */
  IOE_Write(DeviceAddr, STMPE1600_REG_SYS_CTRL, (uint16_t)0x00); 
  
  /* Wait for a delay to ensure registers erasing */
  IOE_Delay(2); 
}

/**
  * @brief  Read the stmpe1600 device ID.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval The Device ID (two bytes).
  */
uint16_t stmpe1600_ReadID(uint16_t DeviceAddr)
{
  uint8_t tmpData[2] = {0 , 0};

  /* Initialize IO BUS layer */
  IOE_Init(); 
  
  /* Read the stmpe1600 device ID */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_CHP_ID, tmpData, 2);
  
  /* Return the device ID value */
  return((uint16_t)tmpData[0] | (((uint16_t)tmpData[1]) << 8));
}

/**
  * @brief  Set the global interrupt Polarity.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @param  Polarity: could be one of these values; 
  *   @arg  STMPE1600_POLARITY_LOW: Interrupt line is active Low/Falling edge      
  *   @arg  STMPE1600_POLARITY_HIGH: Interrupt line is active High/Rising edge               
  * @retval None
  */
void stmpe1600_SetITPolarity(uint16_t DeviceAddr, uint8_t Polarity)
{
  uint8_t tmp = 0;
  
  /* Get the current register value */ 
  tmp = IOE_Read(DeviceAddr, STMPE1600_REG_SYS_CTRL);
  
  /* Mask the polarity bit */
  tmp &= ~(uint16_t)0x01;
    
  /* Set the Interrupt Output line polarity */
  tmp |= (uint8_t)Polarity;
  
  /* Set the new register value */
  IOE_Write(DeviceAddr, STMPE1600_REG_SYS_CTRL, tmp);
}

/**
  * @brief  Enable the Global interrupt.
  * @param  DeviceAddr: Device address on communication Bus.        
  * @retval None
  */
void stmpe1600_EnableGlobalIT(uint16_t DeviceAddr)
{
  uint8_t tmpData[2] = {0 , 0};

  /* Configure NVIC IT for IOE */
  IOE_ITConfig();
  
  /* Get the current register value */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_SYS_CTRL, tmpData, 2);
  
  tmp = ((uint16_t)tmpData[0] | (((uint16_t)tmpData[1]) << 8));
  
  /* Set the global interrupts to be Enabled */    
  tmp |= (uint16_t)STMPE1600_IT_ENABLE;
  
  /* Write Back the Interrupt Control register */
  IOE_WriteMultiple(DeviceAddr, STMPE1600_REG_SYS_CTRL, (uint8_t *)&tmp, 2); 
}

/**
  * @brief  Disable the Global interrupt.
  * @param  DeviceAddr: Device address on communication Bus.        
  * @retval None
  */
void stmpe1600_DisableGlobalIT(uint16_t DeviceAddr)
{ 
  uint8_t tmpData[2] = {0 , 0};

  /* Get the current register value */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_SYS_CTRL, tmpData, 2);
  
  tmp = ((uint16_t)tmpData[0] | (((uint16_t)tmpData[1]) << 8));
  
  /* Set the global interrupts to be Enabled */    
  tmp &= ~(uint16_t)STMPE1600_IT_ENABLE;
  
  /* Write Back the Interrupt Control register */
  IOE_WriteMultiple(DeviceAddr, STMPE1600_REG_SYS_CTRL, (uint8_t *)&tmp, 2); 
}

/**
  * @brief  Initialize the selected pin(s) direction.
  * @param  DeviceAddr: Device address on communication Bus.   
  * @param  IO_Pin: IO pin(s) to be configured. 
  *         This parameter could be any combination of the following values:
  *   @arg  STMPE1600_PIN_x: where x can be from 0 to 15.  
  * @param  Direction: could be STMPE1600_DIRECTION_IN or STMPE1600_DIRECTION_OUT.      
  * @retval None
  */
void stmpe1600_IO_InitPin(uint16_t DeviceAddr, uint32_t IO_Pin, uint8_t Direction)
{
  uint8_t tmpData[2] = {0 , 0};
  
  /* Get the current register value */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_GPDR, tmpData, 2);

  tmp = ((uint16_t)tmpData[0] | (((uint16_t)tmpData[1]) << 8));
  
  /* Set the Pin direction */
  if (Direction != STMPE1600_DIRECTION_IN)
  {
    tmp |= (uint16_t)IO_Pin;
  }  
  else 
  {
    tmp &= ~(uint16_t)IO_Pin;
  }
    
  /* Set the new register value */
  IOE_WriteMultiple(DeviceAddr, STMPE1600_REG_GPDR, (uint8_t *)&tmp, 2);      
}

/**
  * @brief  Configure the IO pin(s) according to IO mode structure value.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @param  IO_Pin: The output pin to be set or reset. This parameter can be one 
  *         of the following values:   
  *   @arg  STMPE1600_PIN_x: where x can be from 0 to 7.
  * @param  IO_Mode: The IO pin mode to configure, could be one of the following values:
  *   @arg  IO_MODE_INPUT
  *   @arg  IO_MODE_OUTPUT
  *   @arg  IO_MODE_IT_RISING_EDGE
  *   @arg  IO_MODE_IT_FALLING_EDGE         
  * @retval 0 if no error, IO_Mode if error
  */
uint8_t stmpe1600_IO_Config(uint16_t DeviceAddr, uint32_t IO_Pin, IO_ModeTypedef IO_Mode)
{
  uint8_t error_code = 0;
    uint8_t buffer[2] = {0,0};  
    
  /* Configure IO pin according to selected IO mode */
  switch(IO_Mode)
  {
  case IO_MODE_INPUT: /* Input mode */
    stmpe1600_IO_DisablePinIT(DeviceAddr, IO_Pin);
    stmpe1600_IO_InitPin(DeviceAddr, IO_Pin, STMPE1600_DIRECTION_IN);
    break;
    
  case IO_MODE_OUTPUT: /* Output mode */
    stmpe1600_IO_DisablePinIT(DeviceAddr, IO_Pin);
    stmpe1600_IO_InitPin(DeviceAddr, IO_Pin, STMPE1600_DIRECTION_OUT);
    break;
  
  case IO_MODE_IT_RISING_EDGE: /* Interrupt rising edge mode */
    stmpe1600_SetITPolarity(DeviceAddr, STMPE1600_POLARITY_HIGH);
    stmpe1600_IO_EnablePinIT(DeviceAddr, IO_Pin);
    stmpe1600_IO_InitPin(DeviceAddr, IO_Pin, STMPE1600_DIRECTION_IN); 
    /* Clear all IO IT pending bits if any */
    stmpe1600_IO_ClearIT(DeviceAddr, IO_Pin);
    
    /* Read GMPR to enable interrupt */
    IOE_ReadMultiple(DeviceAddr , STMPE1600_REG_GPMR, buffer, 2);
    break; 
    
  case IO_MODE_IT_FALLING_EDGE: /* Interrupt falling edge mode */
    stmpe1600_SetITPolarity(DeviceAddr, STMPE1600_POLARITY_LOW);
    stmpe1600_IO_EnablePinIT(DeviceAddr, IO_Pin);
    stmpe1600_IO_InitPin(DeviceAddr, IO_Pin, STMPE1600_DIRECTION_IN); 
    
    /* Clear all IO IT pending bits if any */
    stmpe1600_IO_ClearIT(DeviceAddr, IO_Pin);
    
    /* Read GMPR to enable interrupt */
    IOE_ReadMultiple(DeviceAddr , STMPE1600_REG_GPMR, buffer, 2);    
    break;

  default:
    error_code = (uint8_t) IO_Mode;
	break;
  } 
  return error_code;
}

/**
  * @brief  Enable polarity inversion of the selected IO pin(s).
  * @param  DeviceAddr: Device address on communication Bus.    
  * @param  IO_Pin: IO pin(s) to be configured.  
  *         This parameter could be any combination of the following values:
  *   @arg  STMPE1600_PIN_x: where x can be from 0 to 15. 
  * @retval None
  */ 
void stmpe1600_IO_PolarityInv_Enable(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  uint8_t tmpData[2] = {0 , 0};
  
  /* Get the current register value */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_GPPIR, tmpData, 2);
  
  tmp = ((uint16_t)tmpData[0] | (((uint16_t)tmpData[1]) << 8));  

  /* Enable pin polarity inversion */
  tmp |= (uint16_t)IO_Pin;
    
  /* Set the new register value */  
  IOE_WriteMultiple(DeviceAddr, STMPE1600_REG_GPPIR, (uint8_t *)&tmp, 2);
}

/**
  * @brief  Disable polarity inversion of the selected IO pins.
  * @param  DeviceAddr: Device address on communication Bus.    
  * @param  IO_Pin: IO pin(s) to be configured. 
  *         This parameter could be any combination of the following values:
  *   @arg  STMPE1600_PIN_x: where x can be from 0 to 15.
  * @retval None
  */ 
void stmpe1600_IO_PolarityInv_Disable(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  uint8_t tmpData[2] = {0 , 0};
  
  /* Get the current register value */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_GPPIR, tmpData, 2);
  
  tmp = ((uint16_t)tmpData[0] | (((uint16_t)tmpData[1]) << 8));  

  /* Disable pin polarity inversion */
   tmp &= ~ (uint16_t)IO_Pin;
    
  /* Set the new register value */  
  IOE_WriteMultiple(DeviceAddr, STMPE1600_REG_GPPIR, (uint8_t *)&tmp, 2);  
}

/**
  * @brief  Set the value of the selected IO pins.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @param  IO_Pin: IO pin(s) to be set.
  *         This parameter could be any combination of the following values:
  *   @arg  STMPE1600_PIN_x: where x can be from 0 to 15.
  * @param  PinState: The value to be set. 
  * @retval None
  */
void stmpe1600_IO_WritePin(uint16_t DeviceAddr, uint32_t IO_Pin, uint8_t PinState)
{
  uint8_t tmpData[2] = {0 , 0};
  
  /* Get the current register value */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_GPMR, tmpData, 2);
  
  tmp = ((uint16_t)tmpData[0] | (((uint16_t)tmpData[1]) << 8));  
  
  /* Set the pin state */
  if(PinState != 0)
  {
    tmp |= (uint16_t)IO_Pin;
  }  
  else 
  {
    tmp &= ~(uint16_t)IO_Pin;
  }
    
  /* Set the new register value */  
  IOE_WriteMultiple(DeviceAddr, STMPE1600_REG_GPSR, (uint8_t *)&tmp, 2);
}

/**
  * @brief  Read the state of the selected IO pin(s).
  * @param  DeviceAddr: Device address on communication Bus. 
  * @param  IO_Pin: IO pin(s) to be read.  
  *         This parameter could be any combination of the following values:
  *   @arg  STMPE1600_PIN_x: where x can be from 0 to 15.
  * @retval State of the selected IO pin(s).
  */
uint32_t stmpe1600_IO_ReadPin(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  uint8_t tmpData[2] = {0 , 0};
  
  /* Get the register value */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_GPMR, tmpData, 2);
  
  tmp = ((uint16_t)tmpData[0] | (((uint16_t)tmpData[1]) << 8));
  
  /* Return the pin(s) state */
  return(tmp & IO_Pin);  
}

/**
  * @brief  Enable the interrupt mode for the selected IO pin(s).
  * @param  DeviceAddr: Device address on communication Bus.     
  * @param  IO_Pin: IO pin(s) to be configured.  
  *         This parameter could be any combination of the following values:
  *   @arg  STMPE1600_PIN_x: where x can be from 0 to 15. 
  * @retval None
  */
void stmpe1600_IO_EnablePinIT(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  uint8_t tmpData[2] = {0 , 0};
    
  /* Enable global interrupt */
  stmpe1600_EnableGlobalIT(DeviceAddr);

  /* Get the current register value */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_IEGPIOR, tmpData, 2);
  
  tmp = ((uint16_t)tmpData[0] | (((uint16_t)tmpData[1]) << 8));  
  
  /* Put pin in IT mode */
  tmp |= (uint16_t)IO_Pin;
    
  /* Write the new register value */
  IOE_WriteMultiple(DeviceAddr, STMPE1600_REG_IEGPIOR, (uint8_t *)&tmp, 2);
}

/**
  * @brief  Disable the interrupt mode for the selected IO pin(s).
  * @param  DeviceAddr: Device address on communication Bus.    
  * @param  IO_Pin: IO pin(s) to be configured.  
  *         This parameter could be any combination of the following values:
  *   @arg  STMPE1600_PIN_x: where x can be from 0 to 15. 
  * @retval None
  */
void stmpe1600_IO_DisablePinIT(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  uint8_t tmpData[2] = {0 , 0};
  
  /* Get the current register value */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_IEGPIOR, tmpData, 2);
  
  tmp = ((uint16_t)tmpData[0] | (((uint16_t)tmpData[1]) << 8));  
  
  /* Disable the IT pin mode */
  tmp &= ~(uint16_t)IO_Pin;
    
  /* Set the new register value */
  IOE_WriteMultiple(DeviceAddr, STMPE1600_REG_IEGPIOR, (uint8_t *)&tmp, 2); 
}

/**
  * @brief  Read the IT status of the selected IO pin(s)
  *         (clears all the pending bits if any). 
  * @param  DeviceAddr: Device address on communication Bus.  
  * @param  IO_Pin: IO pin(s) to be checked.  
  *         This parameter could be any combination of the following values:
  *   @arg  STMPE1600_PIN_x: where x can be from 0 to 15.           
  * @retval IT Status of the selected IO pin(s).
  */
uint32_t stmpe1600_IO_ITStatus(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  uint8_t tmpData[2] = {0 , 0};
  
  /* Get the register value */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_ISGPIOR, tmpData, 2);
  
  tmp = ((uint16_t)tmpData[0] | (((uint16_t)tmpData[1]) << 8));
  
  /* Return the pin IT status */
  return((tmp & IO_Pin) == IO_Pin);  
}

/**
  * @brief  Detect an IT pending bit from the selected IO pin(s).
  *         (clears all the pending bits if any).
  * @param  DeviceAddr: Device address on communication Bus.  
  * @param  IO_Pin: IO pin(s) to be checked.  
  *         This parameter could be any combination of the following values:
  *   @arg  STMPE1600_PIN_x: where x can be from 0 to 15.           
  * @retval IT pending bit detection status.
  */
uint8_t stmpe1600_IO_ReadIT(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  uint8_t tmpData[2] = {0 , 0};
  
  /* Get the register value */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_ISGPIOR, tmpData, 2);
  
  tmp = ((uint16_t)tmpData[0] | (((uint16_t)tmpData[1]) << 8));
  
  /* Return if there is an IT pending bit or not */
  return(tmp & IO_Pin);
}

/**
  * @brief  Clear all the IT pending bits if any. 
  * @param  DeviceAddr: Device address on communication Bus.            
  * @retval None
  */
void stmpe1600_IO_ClearIT(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  uint8_t tmpData[2] = {0 , 0};
    
  /* Get the register value to clear all pending bits */
  IOE_ReadMultiple(DeviceAddr, STMPE1600_REG_ISGPIOR, tmpData, 2);
}

/**
  * @brief  Check if the device instance of the selected address is already registered
  *         and return its index 
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval Index of the device instance if registered, 0xFF if not.
  */
static uint8_t stmpe1600_GetInstance(uint16_t DeviceAddr)
{
  uint8_t idx = 0;
  
  /* Check all the registered instances */
  for(idx = 0; idx < STMPE1600_MAX_INSTANCE ; idx ++)
  {
    /* Return index if there is address match */
    if(stmpe1600[idx] == DeviceAddr)
    {
      return idx; 
    }
  }
  
  return 0xFF;
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

/**
  * @}
  */      
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
