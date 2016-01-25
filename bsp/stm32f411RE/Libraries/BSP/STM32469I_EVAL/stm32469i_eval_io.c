/**
  ******************************************************************************
  * @file    stm32469i_eval_io.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file provides a set of functions needed to manage the IO pins
  *          on STM32469I-EVAL evaluation board.
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

/* File Info : -----------------------------------------------------------------
                                   User NOTES
1. How To use this driver:
--------------------------
   - This driver is used to drive the IO module of the STM32469I-EVAL evaluation
     board.
   - The MFXSTM32L152 IO expander device component driver must be included with this
     driver in order to run the IO functionalities commanded by the IO expander
     device mounted on the evaluation board.

2. Driver description:
---------------------
  + Initialization steps:
     o Initialize the IO module using the BSP_IO_Init() function. This
       function includes the MSP layer hardware resources initialization and the
       communication layer configuration to start the IO functionalities use.

  + IO functionalities use
     o The IO pin mode is configured when calling the function BSP_IO_ConfigPin(), you
       must specify the desired IO mode by choosing the "IO_ModeTypedef" parameter
       predefined value.
     o If an IO pin is used in interrupt mode, the function BSP_IO_ITGetStatus() is
       needed to get the interrupt status. To clear the IT pending bits, you should
       call the function BSP_IO_ITClearPin() with specifying the IO pending bit to clear.
     o The IT is handled using the corresponding external interrupt IRQ handler,
       the user IT callback treatment is implemented on the same external interrupt
       callback.
     o To get/set an IO pin combination state you can use the functions
       BSP_IO_ReadPin()/BSP_IO_WritePin() or the function BSP_IO_TogglePin() to toggle the pin
       state.

------------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32469i_eval_io.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I-EVAL
  * @{
  */

/** @defgroup STM32469I-EVAL_IO STM32469I-EVAL IO
  * @{
  */

/** @defgroup STM32469I-EVAL_IO_Private_Types_Definitions STM32469I-EVAL IO Private Types Definitions
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_IO_Private_Defines STM32469I-EVAL IO Private Defines
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_IO_Private_Macros STM32469I-EVAL IO Private Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_IO_Private_Variables STM32469I-EVAL IO Private Variables
  * @{
  */
static IO_DrvTypeDef *IoDrv = NULL;
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_IO_Private_Function_Prototypes STM32469I-EVAL IO Private Function Prototypes
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_IO_Private_Functions STM32469I-EVAL IO Private Functions
  * @{
  */

/**
  * @brief  Initializes and configures the IO functionalities and configures all
  *         necessary hardware resources (GPIOs, clocks..).
  * @note   BSP_IO_Init() is using HAL_Delay() function to ensure that MFXSTM32L152
  *         IO Expander is correctly reset. HAL_Delay() function provides accurate
  *         delay (in milliseconds) based on variable incremented in SysTick ISR.
  *         This implies that if BSP_IO_Init() is called from a peripheral ISR process,
  *         then the SysTick interrupt must have higher priority (numerically lower)
  *         than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  * @retval IO_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_IO_Init(void)
{
  uint8_t ret = IO_ERROR;
  uint8_t mfxstm32l152_id = 0;
  HAL_Delay(1);
  /* Read ID and verify the IO expander is ready */
  mfxstm32l152_id = mfxstm32l152_io_drv.ReadID(IO_I2C_ADDRESS);
  if((mfxstm32l152_id == MFXSTM32L152_ID_1) || (mfxstm32l152_id == MFXSTM32L152_ID_2))
  {
    /* Initialize the IO driver structure */
    IoDrv = &mfxstm32l152_io_drv;
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
  * @brief  DeInit allows Mfx Inititialization to be executed again
  * @note   BSP_IO_Init() has no effect if the IoDrv is already initialized
  *         BSP_IO_DeInit() allows to erase the pointer such to allow init to be effective
  * @retval IO_OK
  */
uint8_t BSP_IO_DeInit(void)
{
  IoDrv = NULL;
  return IO_OK;
}

/**
  * @brief  Gets the selected pins IT status.
  * @param  IoPin: Selected pins to check the status.
  *          This parameter can be any combination of the IO pins.
  * @retval IO_OK if read status OK. Other value if error.
  */
uint32_t BSP_IO_ITGetStatus(uint32_t IoPin)
{
  /* Return the IO Pin IT status */
  return (IoDrv->ITStatus(IO_I2C_ADDRESS, IoPin));
}

/**
  * @brief  Clears all the IO IT pending bits.
  */
void BSP_IO_ITClear(void)
{
  /* Clear all IO IT pending bits */
  IoDrv->ClearIT(IO_I2C_ADDRESS, MFXSTM32L152_GPIO_PINS_ALL);
}

/**
  * @brief  Clear only one or a selection of IO IT pending bits.
  * @param  IO_Pins_To_Clear : MFX IRQ status IO pin to clear (or combination of several IOs)
  */
void BSP_IO_ITClearPin(uint32_t IO_Pins_To_Clear)
{
  /* Clear only the selected list of IO IT pending bits */
  IoDrv->ClearIT(IO_I2C_ADDRESS, IO_Pins_To_Clear);
}

/**
  * @brief  Configures the IO pin(s) according to IO mode structure value.
  * @param  IO_Pin: IO pin(s) to be configured.
  *          This parameter can be one of the following values:
  *            @arg  MFXSTM32L152_GPIO_PIN_x: where x can be from 0 to 23.
  * @param  IO_Mode: IO pin mode to configure
  *          This parameter can be one of the following values:
  *            @arg  IO_MODE_INPUT
  *            @arg  IO_MODE_OUTPUT
  *            @arg  IO_MODE_IT_RISING_EDGE
  *            @arg  IO_MODE_IT_FALLING_EDGE
  *            @arg  IO_MODE_IT_LOW_LEVEL
  *            @arg  IO_MODE_IT_HIGH_LEVEL
  *            @arg  IO_MODE_ANALOG
  *            @arg  IO_MODE_OFF
  *            @arg  IO_MODE_INPUT_PU,
  *            @arg  IO_MODE_INPUT_PD,
  *            @arg  IO_MODE_OUTPUT_OD,
  *            @arg  IO_MODE_OUTPUT_OD_PU,
  *            @arg  IO_MODE_OUTPUT_OD_PD,
  *            @arg  IO_MODE_OUTPUT_PP,
  *            @arg  IO_MODE_OUTPUT_PP_PU,
  *            @arg  IO_MODE_OUTPUT_PP_PD,
  *            @arg  IO_MODE_IT_RISING_EDGE_PU
  *            @arg  IO_MODE_IT_FALLING_EDGE_PU
  *            @arg  IO_MODE_IT_LOW_LEVEL_PU
  *            @arg  IO_MODE_IT_HIGH_LEVEL_PU
  *            @arg  IO_MODE_IT_RISING_EDGE_PD
  *            @arg  IO_MODE_IT_FALLING_EDGE_PD
  *            @arg  IO_MODE_IT_LOW_LEVEL_PD
  *            @arg  IO_MODE_IT_HIGH_LEVEL_PD
  * @retval IO_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_IO_ConfigPin(uint32_t IO_Pin, IO_ModeTypedef IO_Mode)
{
  /* Configure the selected IO pin(s) mode */
  IoDrv->Config(IO_I2C_ADDRESS, IO_Pin, IO_Mode);

  return IO_OK;
}

/**
  * @brief  Sets the selected pins state.
  * @param  IO_Pin: Selected pins to write.
  *          This parameter can be any combination of the IO pins.
  * @param  PinState: New pins state to write
  */
void BSP_IO_WritePin(uint32_t IO_Pin, BSP_IO_PinStateTypeDef PinState)
{
  /* Set the Pin state */
  IoDrv->WritePin(IO_I2C_ADDRESS, IO_Pin, PinState);
}

/**
  * @brief  Gets the selected pins current state.
  * @param  IO_Pin: Selected pins to read.
  *          This parameter can be any combination of the IO pins.
  * @retval The current pins state
  */
uint32_t BSP_IO_ReadPin(uint32_t IO_Pin)
{
 return(IoDrv->ReadPin(IO_I2C_ADDRESS, IO_Pin));
}

/**
  * @brief  Toggles the selected pins state.
  * @param  IO_Pin: Selected pins to toggle.
  *         This parameter can be any combination of the IO pins.
  * @note   This function is only used to toggle one pin in the same time
  */
void BSP_IO_TogglePin(uint32_t IO_Pin)
{
  /* Toggle the current pin state */
  if(IoDrv->ReadPin(IO_I2C_ADDRESS, IO_Pin) != 0) /* Set */
  {
    IoDrv->WritePin(IO_I2C_ADDRESS, IO_Pin, 0); /* Reset */
  }
  else
  {
    IoDrv->WritePin(IO_I2C_ADDRESS, IO_Pin, 1); /* Set */
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
