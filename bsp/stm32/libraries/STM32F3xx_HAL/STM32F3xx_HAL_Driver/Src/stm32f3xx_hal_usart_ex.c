/**
  ******************************************************************************
  * @file    stm32f3xx_hal_usart_ex.c
  * @author  MCD Application Team
  * @brief   Extended USART HAL module driver.
  *          This file provides firmware functions to manage the following extended
  *          functionalities of the Universal Synchronous Receiver Transmitter Peripheral (USART).
  *           + Peripheral Control functions
  *
  *
  @verbatim
  ==============================================================================
               ##### USART peripheral extended features  #####
  ==============================================================================

    (#) FIFO mode enabling/disabling and RX/TX FIFO threshold programming.

        -@- When USART operates in FIFO mode, FIFO mode must be enabled prior
            starting RX/TX transfers. Also RX/TX FIFO thresholds must be
            configured prior starting RX/TX transfers.

    (#) Slave mode enabling/disabling and NSS pin configuration.

        -@- When USART operates in Slave mode, Slave mode must be enabled prior
            starting RX/TX transfers.

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @defgroup USARTEx USARTEx
  * @brief USART Extended HAL module driver
  * @{
  */

#ifdef HAL_USART_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/** @defgroup USARTEx_Exported_Functions  USARTEx Exported Functions
  * @{
  */

/** @defgroup USARTEx_Exported_Functions_Group1 IO operation functions
  * @brief Extended USART Transmit/Receive functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    This subsection provides a set of FIFO mode related callback functions.

    (#) TX/RX Fifos Callbacks:
        (+) HAL_USARTEx_RxFifoFullCallback()
        (+) HAL_USARTEx_TxFifoEmptyCallback()

@endverbatim
  * @{
  */


/**
  * @}
  */

/** @defgroup USARTEx_Exported_Functions_Group2 Peripheral Control functions
  * @brief    Extended Peripheral Control functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..] This section provides the following functions:
     (+) HAL_USARTEx_EnableSPISlaveMode() API enables the SPI slave mode
     (+) HAL_USARTEx_DisableSPISlaveMode() API disables the SPI slave mode
     (+) HAL_USARTEx_ConfigNSS API configures the Slave Select input pin (NSS)
     (+) HAL_USARTEx_EnableFifoMode() API enables the FIFO mode
     (+) HAL_USARTEx_DisableFifoMode() API disables the FIFO mode
     (+) HAL_USARTEx_SetTxFifoThreshold() API sets the TX FIFO threshold
     (+) HAL_USARTEx_SetRxFifoThreshold() API sets the RX FIFO threshold


@endverbatim
  * @{
  */


/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup USARTEx_Private_Functions
  * @{
  */

/**
  * @}
  */

#endif /* HAL_USART_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
