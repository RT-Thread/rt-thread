/**
  ******************************************************************************
  * @file    stm32f429i_discovery_io.c
  * @author  MCD Application Team
  * @version V2.1.2
  * @date    02-March-2015
  * @brief   This file provides a set of functions needed to manage the STMPE811
  *          IO Expander device mounted on STM32F429I-Discovery Kit.
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
#include "stm32f429i_discovery_io.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32F429I_DISCOVERY
  * @{
  */ 
  
/** @defgroup STM32F429I_DISCOVERY_IO
  * @{
  */ 

/** @defgroup STM32F429I_DISCOVERY_IO_Private_Types_Definitions
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_IO_Private_Defines
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_IO_Private_Macros
  * @{
  */ 
/**
  * @}
  */


/** @defgroup STM32F429I_DISCOVERY_IO_Private_Variables
  * @{
  */
static IO_DrvTypeDef *IoDrv;

/**
  * @}
  */


/** @defgroup STM32F429I_DISCOVERY_IO_Private_Function_Prototypes
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F429I_DISCOVERY_IO_Private_Functions
  * @{
  */

/**
  * @brief  Initializes and configures the IO functionalities and configures all
  *         necessary hardware resources (GPIOs, clocks..).
  * @note   BSP_IO_Init() is using HAL_Delay() function to ensure that stmpe811
  *         IO Expander is correctly reset. HAL_Delay() function provides accurate
  *         delay (in milliseconds) based on variable incremented in SysTick ISR. 
  *         This implies that if BSP_IO_Init() is called from a peripheral ISR process,
  *         then the SysTick interrupt must have higher priority (numerically lower)
  *         than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  * @param  None
  * @retval IO_OK if all initializations done correctly. Other value if error.
  */
uint8_t BSP_IO_Init(void)
{
  uint8_t ret = IO_ERROR;
  
  /* Read ID and verify the IO expander is ready */
  if(stmpe811_io_drv.ReadID(IO_I2C_ADDRESS) == STMPE811_ID)
  {
    /* Initialize the IO driver structure */
    IoDrv = &stmpe811_io_drv;
    ret = IO_OK;
  }

  if(ret == IO_OK)
  {
    IoDrv->Init(IO_I2C_ADDRESS);
    IoDrv->Start(IO_I2C_ADDRESS, IO_PIN_ALL);
  }
  return ret;
}

/**
  * @brief  Gets the selected pins IT status.
  * @param  IoPin: The selected pins to check the status. 
  *         This parameter could be any combination of the IO pins.   
  * @retval Status of IO Pin checked.
  */  
uint8_t BSP_IO_ITGetStatus(uint16_t IoPin)
{
  /* Return the IO Pin IT status */
  return (IoDrv->ITStatus(IO_I2C_ADDRESS, IoPin));
}

/**
  * @brief  Clears all the IO IT pending bits
  * @param  None
  * @retval None
  */  
void BSP_IO_ITClear(void)
{
  /* Clear all IO IT pending bits */
  IoDrv->ClearIT(IO_I2C_ADDRESS, IO_PIN_ALL);
}

/**
  * @brief  Configures the IO pin(s) according to IO mode structure value.
  * @param  IoPin: IO pin(s) to be configured. 
  *         This parameter could be any combination of the following values:
  *   @arg  STMPE811_PIN_x: where x can be from 0 to 7.
  * @param  IoMode: The IO pin mode to configure, could be one of the following values:
  *   @arg  IO_MODE_INPUT
  *   @arg  IO_MODE_OUTPUT
  *   @arg  IO_MODE_IT_RISING_EDGE
  *   @arg  IO_MODE_IT_FALLING_EDGE
  *   @arg  IO_MODE_IT_LOW_LEVEL
  *   @arg  IO_MODE_IT_HIGH_LEVEL 
  * @retval None  
  */ 
void BSP_IO_ConfigPin(uint16_t IoPin, IO_ModeTypedef IoMode)
{
  /* Configure the selected IO pin(s) mode */
  IoDrv->Config(IO_I2C_ADDRESS, IoPin, IoMode);    
}

/**
  * @brief  Sets the selected pins state.
  * @param  IoPin: The selected pins to write. 
  *         This parameter could be any combination of the IO pins. 
  * @param  PinState: the new pins state to write  
  * @retval None
  */
void BSP_IO_WritePin(uint16_t IoPin, uint8_t PinState)
{
  /* Set the Pin state */
  IoDrv->WritePin(IO_I2C_ADDRESS, IoPin, PinState);
}

/**
  * @brief  Gets the selected pins current state.
  * @param  IoPin: The selected pins to read. 
  *         This parameter could be any combination of the IO pins.  
  * @retval The current pins state 
  */
uint16_t BSP_IO_ReadPin(uint16_t IoPin)
{
  return(IoDrv->ReadPin(IO_I2C_ADDRESS, IoPin));
}

/**
  * @brief  Toggles the selected pins state.
  * @param  IoPin: The selected pins to toggle. 
  *         This parameter could be any combination of the IO pins.   
  * @retval None
  */
void BSP_IO_TogglePin(uint16_t IoPin)
{
  /* Toggle the current pin state */
  if(IoDrv->ReadPin(IO_I2C_ADDRESS, IoPin) == 1 /* Set */)
  {
    IoDrv->WritePin(IO_I2C_ADDRESS, IoPin, 0 /* Reset */);
  }
  else
  {
    IoDrv->WritePin(IO_I2C_ADDRESS, IoPin, 1 /* Set */);
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

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
