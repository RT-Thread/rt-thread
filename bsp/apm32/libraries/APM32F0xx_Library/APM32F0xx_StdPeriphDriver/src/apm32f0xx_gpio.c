/*!
 * @file        apm32f0xx_gpio.c
 *
 * @brief       This file contains all the functions for the GPIO peripheral
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup GPIO_Driver
  @{
*/


/** @defgroup GPIO_Macros Macros
  @{
  */

/**@} end of group GPIO_Macros */

/** @defgroup GPIO_Enumerates Enumerates
  @{
  */

/**@} end of group GPIO_Enumerates */

/** @defgroup GPIO_Structures Structures
  @{
  */

/**@} end of group GPIO_Structures */

/** @defgroup GPIO_Variables Variables
  @{
  */

/**@} end of group GPIO_Variables */

/** @defgroup GPIO_Functions Functions
  @{
  */

/*!
 * @brief       Reset GPIO peripheral registers to their default reset values
 *
 * @param       port:   GPIO peripheral.It can be GPIOA/GPIOB/GPIOC/GPIOD/GPIOE/GPIOF
 *
 * @retval      None
 *
 * @note        GPIOE is available only for APM32F072 and APM32F091
 */
void GPIO_Reset(GPIO_T* port)
{
    if (port == GPIOA)
    {
        RCM_EnableAHBPeriphReset(RCM_AHB_PERIPH_GPIOA);
        RCM_DisableAHBPeriphReset(RCM_AHB_PERIPH_GPIOA);
    }
    else if (port == GPIOB)
    {
        RCM_EnableAHBPeriphReset(RCM_AHB_PERIPH_GPIOB);
        RCM_DisableAHBPeriphReset(RCM_AHB_PERIPH_GPIOB);
    }
    else if (port == GPIOC)
    {
        RCM_EnableAHBPeriphReset(RCM_AHB_PERIPH_GPIOC);
        RCM_DisableAHBPeriphReset(RCM_AHB_PERIPH_GPIOC);
    }
    else if (port == GPIOD)
    {
        RCM_EnableAHBPeriphReset(RCM_AHB_PERIPH_GPIOD);
        RCM_DisableAHBPeriphReset(RCM_AHB_PERIPH_GPIOD);
    }
    else if (port == GPIOE)
    {
        RCM_EnableAHBPeriphReset(RCM_AHB_PERIPH_GPIOE);
        RCM_DisableAHBPeriphReset(RCM_AHB_PERIPH_GPIOE);
    }
    else if (port == GPIOF)
    {
        RCM_EnableAHBPeriphReset(RCM_AHB_PERIPH_GPIOF);
        RCM_DisableAHBPeriphReset(RCM_AHB_PERIPH_GPIOF);
    }
}

/*!
 * @brief       Config the GPIO peripheral according to the specified parameters in the gpioConfig
 *
 * @param       port:   GPIO peripheral.It can be GPIOA/GPIOB/GPIOC/GPIOD/GPIOE/GPIOF
 *
 * @param       gpioConfig:     Pointer to a GPIO_Config_T structure that
 *                              contains the configuration information for the specified GPIO peripheral
 *
 * @retval      None
 *
 * @note        GPIOE is available only for APM32F072 and APM32F091
 */
void GPIO_Config(GPIO_T* port, GPIO_Config_T* gpioConfig)
{
    uint32_t i;
    uint32_t bit;

    for (i = 0; i < 16; i++)
    {
        bit = (uint32_t)1 << i;

        if (!(gpioConfig->pin & bit))
        {
            continue;
        }

        if ((gpioConfig->mode == GPIO_MODE_OUT) || (gpioConfig->mode == GPIO_MODE_AF))
        {
            /* speed */
            port->OSSEL &= ~((0x03) << (i * 2));
            port->OSSEL |= ((uint32_t)(gpioConfig->speed) << (i * 2));

            /* Output mode configuration */
            port->OMODE &= ~(((uint16_t)gpioConfig->outtype) << ((uint16_t)i));
            port->OMODE |= (uint16_t)(((uint16_t)gpioConfig->outtype) << ((uint16_t)i));
        }

        /* input/output mode */
        port->MODE  &= ~(0x03 << (i * 2));
        port->MODE |= (((uint32_t)gpioConfig->mode) << (i * 2));

        /* Pull-up Pull down resistor configuration */
        port->PUPD &= ~(0x03 << ((uint16_t)i * 2));
        port->PUPD |= (((uint32_t)gpioConfig->pupd) << (i * 2));
    }
}

/*!
 * @brief       Fills each GPIO_Config_T member with its default value
 *
 * @param       gpioConfig: Pointer to a GPIO_Config_T structure which will be initialized
 *
 * @retval      None
 */
void GPIO_ConfigStructInit(GPIO_Config_T* gpioConfig)
{
    gpioConfig->pin     = GPIO_PIN_ALL;
    gpioConfig->mode    = GPIO_MODE_IN;
    gpioConfig->outtype = GPIO_OUT_TYPE_PP;
    gpioConfig->speed   = GPIO_SPEED_10MHz;
    gpioConfig->pupd    = GPIO_PUPD_NO;
}

/*!
 * @brief       Locks GPIO Pins configuration registers
 *
 * @param       port:   GPIOA/B peripheral
 *
 * @param       pin:    specifies the port bit to be written
 *
 * @retval      None
 */
void GPIO_ConfigPinLock(GPIO_T* port, uint16_t pin)
{
    uint32_t val = 0x00010000;

    val  |= pin;
    /* Set LOCK bit */
    port->LOCK = val ;
    /* Reset LOCK bit */
    port->LOCK = pin;
    /* Set LOCK bit */
    port->LOCK = val;
    /* Read LOCK bit*/
    val = port->LOCK;
    /* Read LOCK bit*/
    val = port->LOCK;
}

/*!
 * @brief       Reads the specified input port pin
 *
 * @param       port:   GPIO peripheral.It can be GPIOA/GPIOB/GPIOC/GPIOD/GPIOE/GPIOF
 *
 * @param       pin:    specifies pin to read
 *
 * @retval      The input port pin value
 *
 * @note        APM32F072 and APM32F091: (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0..10) for GPIOF.
 */
uint8_t GPIO_ReadInputBit(GPIO_T* port, uint16_t pin)
{
    uint8_t ret;

    ret = (port->IDATA & pin) ?  BIT_SET : BIT_RESET;

    return ret;
}

/*!
 * @brief       Reads the specified GPIO input data port
 *
 * @param       port:   GPIO peripheral
 *
 * @retval      GPIO input data port value
 *
 * @note        GPIOE is available only for APM32F072 and APM32F091
 */
uint16_t GPIO_ReadInputPort(GPIO_T* port)
{
    return ((uint16_t)port->IDATA);
}

/*!
 * @brief       Reads the specified output data port bit
 *
 * @param       port:   GPIO peripheral
 *
 * @param       pin:    specifies pin to read
 *
 * @retval      The output port pin value
 *
 * @note        GPIOE is available only for APM32F072 and APM32F091
 */
uint8_t GPIO_ReadOutputBit(GPIO_T* port, uint16_t pin)
{

    uint8_t ret;

    ret = (port->ODATA & pin) ? BIT_SET : BIT_RESET;

    return ret;
}

/*!
 * @brief       Reads the specified GPIO output data port
 *
 * @param       port:   GPIO peripheral
 *
 * @retval      output data port value
 *
 * @note        GPIOE is available only for APM32F072 and APM32F091
 */
uint16_t GPIO_ReadOutputPort(GPIO_T* port)
{
    return ((uint16_t)port->ODATA);
}

/*!
 * @brief       Sets the selected data port bits
 *
 * @param       port:   GPIO peripheral
 *
 * @param       pin:    specifies the port bits to be written
 *
 * @retval      None
 *
 * @note        APM32F072 and APM32F091: (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0..10) for GPIOF.
 */
void GPIO_SetBit(GPIO_T* port, uint16_t pin)
{
    port->BSC = (uint32_t)pin;
}

/*!
 * @brief       Clears the selected data port bits
 *
 * @param       port:   GPIO peripheral
 *
 * @param       pin:    specifies the port bits to be written
 *
 * @retval      None
 *
 * @note        APM32F072 and APM32F091: (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0..10) for GPIOF.
 */
void GPIO_ClearBit(GPIO_T* port, uint16_t pin)
{
    port->BR = (uint32_t)pin;
}

/*!
 * @brief       Sets or clears the selected data port bit
 *
 * @param       port:   GPIO peripheral
 *
 * @param       pin:    specifies the port bits to be written
 *
 * @param       bitVal
 *
 * @retval      None
 *
 * @note        APM32F072 and APM32F091: (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0..10) for GPIOF.
 */
void GPIO_WriteBitValue(GPIO_T* port, uint16_t pin, GPIO_BSRET_T bitVal)
{
    if (bitVal != Bit_RESET)
    {
        port->BSC = pin;
    }
    else
    {
        port->BR = pin ;
    }
}

/*!
 * @brief       Writes data to the specified GPIO data port
 *
 * @param       port:     GPIO peripheral
 *
 * @param       portVal:  Write value to the port output data register
 *
 * @retval      None
 *
 * @note        GPIOE is available only for APM32F072 and APM32F091
 */
void GPIO_WriteOutputPort(GPIO_T* port, uint16_t portValue)
{
    port->ODATA = (uint32_t)portValue;
}

/*!
 * @brief       Changes the mapping of the specified pin
 *
 * @param       port: GPIO peripheral
 *
 * @param       pinSource:  Specifies the pin for the Alternate function.
 *              This parameter can be one of the following values:
 *              @arg GPIOA,GPIOB,GPIOD,GPIOE for 0..15
 *              @arg GPIOC for 0..12
 *              @arg GPIOF for 0, 2..5, 9..10
 *
 * @param       afPin: Selects the pin to used as Alternate function.
 *
 * @retval      None
 *
 * @note        GPIOC, GPIOD, GPIOE and GPIOF  are available only for APM32F072 and APM32F091
 */
void GPIO_ConfigPinAF(GPIO_T* port, GPIO_PIN_SOURCE_T pinSource, GPIO_AF_T afPin)
{
    uint32_t temp  = 0x00;
    uint32_t temp1 = 0x00;

    if (pinSource <= 0x07)
    {
        temp = (uint8_t)afPin << ((uint32_t)pinSource * 4);
        port->ALFL &= ~((uint32_t)0xf << ((uint32_t)pinSource * 4));
        port->ALFL |=  temp;
    }
    else
    {
        temp1 = (uint8_t)afPin << ((uint32_t)(pinSource & 0x07) * 4);
        port->ALFH &= ~((uint32_t)0xf << (((uint32_t)pinSource & 0x07) * 4));
        port->ALFH |=  temp1;
    }
}
/**@} end of group GPIO_Functions */
/**@} end of group GPIO_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
