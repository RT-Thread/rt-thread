/**
  ******************************************************************************
  * @file    tae32f53xx_ll_gpio.c
  * @author  MCD Application Team
  * @brief   GPIO LL module driver.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll.h"


#define DBG_TAG             "GPIO LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup GPIO_LL GPIO LL
  * @brief      GPIO LL module driver
  * @{
  */

#ifdef LL_GPIO_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup GPIO_LL_Exported_Functions GPIO LL Exported Functions
  * @brief    GPIO LL Exported Functions
  * @{
  */

/** @defgroup GPIO_LL_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
  [..]
    This section provides functions allowing to initialize and de-initialize the GPIOs
    to be ready for use.

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the GPIOx peripheral according to the specified parameters in the GPIO_Init.
  * @param  GPIOx: where x can be (A, B, ... depending on device used) to select the GPIO peripheral
  * @param  GPIO_Init: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @return status of the initialization
  */
LL_StatusETypeDef LL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    uint32_t position = 0x00U;
    uint32_t iocurrent;
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Init->Pin));
		

    /* Configure the port pins */
    while (((GPIO_Init->Pin) >> position) != 0x00U) {
        /* Get current io position */
        iocurrent = (GPIO_Init->Pin) & (1UL << position);

        if (iocurrent != 0x00U) {
            /*--------------------- GPIO Mode Configuration ------------------------*/
            switch (GPIO_Init->Mode & 0x03U) {
                /*In case of Alternate function mode selection*/
                case GPIO_MODE_AF:

                    /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
                    MODIFY_REG(GPIOx->PMUXR[position >> 3U], 0x0FU << ((position & 0x07U) * 4U),
                               (GPIO_Init->Alternate & 0x0FU) << ((position & 0x07U) * 4U));

                    /* Configure the IO Output Type */
                    MODIFY_REG(GPIOx->OTYPR, 0x01U << position, (GPIO_Init->OType & 0x01U) << position);

                    /* Configure the IO Speed */
                    MODIFY_REG(GPIOx->OSRR, 0x01U << position, (GPIO_Init->Speed & 0x01U) << position);
                    break;

                /* In case of Input function mode selection */
                case GPIO_MODE_INPUT:
                    /* Configure IO Direction mode (Input) */
                    MODIFY_REG(GPIOx->PMUXR[position >> 3U], 0x0FU << ((position & 0x07U) * 4U),
                               GPIO_AF0_INPUT << ((position & 0x07U) * 4U));

                    /* Interrupt Eanble */
                    MODIFY_REG(GPIOx->ITER, 0x01U << position, ((GPIO_Init->Mode >> 28U) & 0x01U) << position);

                    /* Rising/Falling Edge */
                    MODIFY_REG(GPIOx->RFTSR, 0x01U << position, ((GPIO_Init->Mode >> 20U) & 0x01U) << position);
                    MODIFY_REG(GPIOx->RFTSR, 0x01U << (position + 16U), ((GPIO_Init->Mode >> 21U) & 0x01U) << (position + 16U));

                    /* GPIO Port Interrupt Enable */
                    WRITE_REG(GPIOx->IER, (READ_REG(GPIOx->ITER) == 0x00UL) ? 0x00UL : 0x01UL);

                    /* Clear Pending */
                    WRITE_REG(GPIOx->PR, 0x01U << position);
                    break;

                /* In case of Output function mode selection */
                case GPIO_MODE_OUTPUT:

                    /* Configure the IO Output Type */
                    MODIFY_REG(GPIOx->PMUXR[position >> 3U], 0x0FU << ((position & 0x07U) * 4U),
                               GPIO_AF1_OUTPUT << ((position & 0x07U) * 4U));

                    /* Configure the IO Output Type */
                    MODIFY_REG(GPIOx->OTYPR, 0x01U << position, (GPIO_Init->OType & 0x01U) << position);

                    /* Configure the IO Speed */
                    MODIFY_REG(GPIOx->OSRR, 0x01U << position, (GPIO_Init->Speed & 0x01U) << position);
                    break;
            }


            /* Activate the Pull-up  resistor for the current IO */
            if (GPIO_Init->Pull == GPIO_PULLUP) {
                SET_BIT(GPIOx->PUR, 0x01U << position);
                CLEAR_BIT(GPIOx->PDR, 0x01U << position);
            }

            /* Activate the Pull-dowm  resistor for the current IO */
            if (GPIO_Init->Pull == GPIO_PULLDOWN) {
                CLEAR_BIT(GPIOx->PUR, 0x01U << position);
                SET_BIT(GPIOx->PDR, 0x01U << position);
            }

            /* Unactivate the Pull-up or Pull down resistor for the current IO */
            if (GPIO_Init->Pull == GPIO_NOPULL) {
                CLEAR_BIT(GPIOx->PUR, 0x01U << position);
                CLEAR_BIT(GPIOx->PDR, 0x01U << position);
            }
        }

        position++;
    }

    return LL_OK;
}

/**
  * @brief  De-initializes the GPIOx peripheral registers to their default reset values.
  * @param  GPIOx: where x can be (A, B, ... depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be any combination of @ref GPIO_pins_define
  * @return status of the de-initialization
  */
LL_StatusETypeDef LL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
    uint32_t position = 0x00U;
    uint32_t iocurrent;
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    /* Configure the port pins */
    while ((GPIO_Pin >> position) != 0x00U) {
        /* Get current io position */
        iocurrent = GPIO_Pin & (0x1U << position);

        if (iocurrent != 0x00U) {
            /*------------------------- GPIO Mode Configuration --------------------*/
            /* Configure the default Alternate Function in current IO */
            MODIFY_REG(GPIOx->PMUXR[position >> 3U], (0x0FU << ((uint32_t)(position & 0x07U) * 4U)),
                       (GPIO_AF15_ANALOG << ((uint32_t)(position & 0x07U) * 4U)));

            /* Configure the default value for IO Speed */
            CLEAR_BIT(GPIOx->OSRR, 0x01U << position);

            /* Configure the default value IO Output Type */
            CLEAR_BIT(GPIOx->OTYPR, 0x01U << position);

            /* Deactivate the Pull-up and Pull-down resistor for the current IO */
            CLEAR_BIT(GPIOx->PDR, 0x01U << position);
            CLEAR_BIT(GPIOx->PUR, 0x01U << position);

            /* Disable Interrupt Mask */
            CLEAR_BIT(GPIOx->ITER, 0x01U << position);

            /* Clear Rising Falling edge configuration */
            CLEAR_BIT(GPIOx->RFTSR, 0x01U << position);
            CLEAR_BIT(GPIOx->RFTSR, 0x01U << (position + 16U));

            /* Disable Interrupt */
            WRITE_REG(GPIOx->IER, (READ_REG(GPIOx->ITER) == 0) ? 0x00 : 0x01);

            /* Clear Pending */
            WRITE_REG(GPIOx->PR, 0x01U << position);

            /* Defalut value of data */
            CLEAR_BIT(GPIOx->DR, 0x01U << position);
        }

        position++;
    }

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup GPIO_LL_Exported_Functions_Group2 GPIO Peripheral Control functions
  * @brief    GPIO Peripheral Control functions
@verbatim
  ===============================================================================
                       ##### Peripheral Control functions #####
  ===============================================================================
  [..]
    This section provides functions allowing to:
    (+) GPIO configure functions

@endverbatim
  * @{
  */

/**
  * @brief  Config the alternate function on runtime.
  * @param  GPIOx where x can be (A, B, ...) to select the GPIO peripheral for TXF53xx
  * @param  GPIO_Pin specifies the port bit to read.
  *         This parameter can be GPIO_PIN_x where x can be (0..15).
  * @param  Alternate Peripheral to be connected to the selected pins.
  *                   This parameter can be a value of @ref GPIO_Alternate_function_selection
  * @return None
  */
void LL_GPIO_AF_Config(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_AFETypeDef Alternate)
{
    uint32_t position = 0x00U;
    uint32_t iocurrent;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    /* Configure the port pins */
    while (((GPIO_Pin) >> position) != 0x00U) {
        /* Get current io position */
        iocurrent = (GPIO_Pin) & (1UL << position);

        if (iocurrent != 0x00U) {
            /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
            MODIFY_REG(GPIOx->PMUXR[position >> 3U], 0x0FU << ((position & 0x07U) * 4U),
                       (Alternate) << ((position & 0x07U) * 4U));
        }

        /* Next pin */
        position++;
    }
}

/**
  * @}
  */


/** @defgroup GPIO_LL_Exported_Functions_Group3 GPIO IO operation functions
 *  @brief   GPIO Read and Write
 *
@verbatim
 ===============================================================================
                       ##### IO operation functions #####
 ===============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the GPIOs:
    (+) Read the GPIOx Pins
    (+) Write the GPIOx Pins
    (+) Toggle the GPIOx Pins
    (+) Write the GPIOx Port
    (+) Read the GPIOx Port

@endverbatim
  * @{
  */

/**
  * @brief  Read the specified input port pin
  * @param  GPIOx where x can be (A, B, ...) to select the GPIO peripheral for TXF53xx
  * @param  GPIO_Pin specifies the port bit to read.
  *         This parameter can be GPIO_PIN_x where x can be (0..15).
  * @return The input port pin value.
  */
GPIO_PinStateETypeDef LL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIO_PinStateETypeDef bitstatus;
    /* Check the parameters */
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    if ((GPIOx->DR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET) {
        bitstatus = GPIO_PIN_SET;
    } else {
        bitstatus = GPIO_PIN_RESET;
    }

    return bitstatus;
}

/**
  * @brief  Set or clear the selected data port bit.
  * @param  GPIOx: where x can be (A, B, ...) to select the GPIO peripheral.
  * @param  bit_field: specifies the port bit to read.
  *          This parameter can be GPIO_Pin_x where x can be (0..15).
  * @param  PinState specifies the value to be written to the selected bit.
  *         This parameter can be one of the GPIO_PinState enum values:
  *            @arg GPIO_PIN_RESET: to clear the port pin
  *            @arg GPIO_PIN_SET: to set the port pin
  * @return None
  */
void LL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinStateETypeDef PinState)
{
    /* Check the parameters */
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    if (PinState != GPIO_PIN_RESET) {
        GPIOx->BSRR = GPIO_Pin;
    } else {
        GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
    }
}

/**
  * @brief  Toggle the specified GPIO pin.
  * @param  GPIOx where x can be (A, B, ...) to select the GPIO peripheral.
  * @param  GPIO_Pin specifies the pin to be toggled.
  * @return None
  */
void LL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->DR ^= (GPIO_Pin & GPIO_PIN_All);
}

/**
  * @brief  Write data to the specified GPIO port.
  * @param  GPIOx where x can be (A, B, ...) to select the GPIO peripheral.
  * @param  Data data to write.
  * @return None
  */
void LL_GPIO_WriteData(GPIO_TypeDef *GPIOx, uint16_t Data)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));

    WRITE_REG(GPIOx->DR, Data);
}


/**
  * @brief  Read data from the specified GPIO port.
  * @param  GPIOx where x can be (A, B, ...) to select the GPIO peripheral.
  * @return GPIO port data
  */
uint16_t LL_GPIO_ReadData(GPIO_TypeDef *GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));

    return READ_REG(GPIOx->DR) & 0xFFFFUL;
}

/**
  * @}
  */


/** @defgroup GPIO_LL_Exported_Functions_Interrupt GPIO Initerrupt management
  *  @brief    GPIO Initerrupt management
  *
@verbatim
  ==============================================================================
                        ##### IRQ handler management #####
  ==============================================================================
  [..]
    This section provides GPIO IRQ handler function.

@endverbatim
  * @{
  */

/**
  * @brief  This function handles GPIO interrupts requests.
  * @param  GPIOx GPIO Port
  * @return None
  */
void LL_GPIO_IRQHandler(GPIO_TypeDef *GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));

    for (uint8_t position = 0x00U; position < GPIO_NUMBER; position++) {
        if ((__LL_GPIO_IT_CHECK_SOURCE(GPIOx, 0x01U << position) != RESET) &&
            (__LL_GPIO_GET_IT(GPIOx, 0x01U << position)) != RESET) {

            __LL_GPIO_CLEAR_IT(GPIOx, 0x01U << position);

            /*Handle something*/
            LL_GPIO_ExtTrigCallback(GPIOx, 0x01U << position);
        }
    }
}

/**
  * @brief  GPIO External Trigger detection callback.
  * @param  GPIOx GPIO Port
  * @param  GPIO_Pin witch trigger the interruption.
  * @return None
  */
__WEAK void LL_GPIO_ExtTrigCallback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(GPIOx);
    LL_UNUSED(GPIO_Pin);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_GPIO_ExtTrigCallback could be implemented in the user file
     */
}
/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


#endif /* LL_GPIO_MODULE_ENABLE */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

