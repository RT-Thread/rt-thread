/*!
 * @file        apm32f10x_gpio.c
 *
 * @brief       This file provides all the GPIO firmware functions
 *
 * @version     V1.0.4
 *
 * @date        2022-12-01
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
#include "apm32f10x_gpio.h"
#include "apm32f10x_rcm.h"

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup GPIO_Driver GPIO Driver
  @{
*/

/** @defgroup GPIO_Functions Functions
  @{
*/

/*!
 * @brief     Reset GPIO peripheral registers to their default reset values
 *
 * @param     port: Select the GPIO port.
 *                  This parameter can be one of GPIOx( x can be from A to G).
 *
 * @retval    None
 */
void GPIO_Reset(GPIO_T* port)
{
    RCM_APB2_PERIPH_T APB2Periph;

    if (port == GPIOA)
    {
        APB2Periph = RCM_APB2_PERIPH_GPIOA;
    }
    else if (port == GPIOB)
    {
        APB2Periph = RCM_APB2_PERIPH_GPIOB;
    }
    else if (port == GPIOC)
    {
        APB2Periph = RCM_APB2_PERIPH_GPIOC;
    }
    else if (port == GPIOD)
    {
        APB2Periph = RCM_APB2_PERIPH_GPIOD;
    }
    else if (port == GPIOE)
    {
        APB2Periph = RCM_APB2_PERIPH_GPIOE;
    }
    else if (port == GPIOF)
    {
        APB2Periph = RCM_APB2_PERIPH_GPIOF;
    }
    else if (port == GPIOG)
    {
        APB2Periph = RCM_APB2_PERIPH_GPIOG;
    }

    RCM_EnableAPB2PeriphReset(APB2Periph);
    RCM_DisableAPB2PeriphReset(APB2Periph);
}

/*!
 * @brief     Reset Alternate Functions registers to their default reset values
 *
 * @param     None
 *
 * @retval    None
 */
void GPIO_AFIOReset(void)
{
    RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_AFIO);
    RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_AFIO);
}

/*!
 * @brief     Config the GPIO peripheral according to the specified parameters in the gpioConfig
 *
 * @param     port: Select the GPIO port.
 *                  This parameter can be one of GPIOx( x can be from A to G).
 *
 * @param     gpioConfig: pointer to a GPIO_Config_T structure
 *
 * @retval    None
 */
void GPIO_Config(GPIO_T* port, GPIO_Config_T* gpioConfig)
{
    uint8_t i;
    uint32_t mode;
    uint32_t CR;
    uint32_t temp;
    uint32_t shift;

    mode = gpioConfig->mode & 0x0f;

    if (gpioConfig->mode & 0x80)
    {
        mode |= gpioConfig->speed;
    }

    if (gpioConfig->pin & 0xff)
    {
        CR = port->CFGLOW;

        for (i = 0, shift = 0x01; i < 8; i++, shift <<= 1)
        {
            if (gpioConfig->pin & shift)
            {
                temp = i << 2;
                CR &= (uint32_t)~(0x0f << temp);
                CR |= mode << temp;

                if (gpioConfig->mode == GPIO_MODE_IN_PD)
                {
                    port->BC = shift;
                }
                else if (gpioConfig->mode == GPIO_MODE_IN_PU)
                {
                    port->BSC = shift;
                }
            }
        }

        port->CFGLOW = CR;
    }

    if (gpioConfig->pin & 0xff00)
    {
        CR = port->CFGHIG;

        for (i = 8, shift = 0x100; i < 16; i++, shift <<= 1)
        {
            if (gpioConfig->pin & shift)
            {
                temp = (i - 8) << 2;
                CR &= (uint32_t)~(0x0f << temp);
                CR |= mode << temp;

                if (gpioConfig->mode == GPIO_MODE_IN_PD)
                {
                    port->BC = shift;
                }
                else if (gpioConfig->mode == GPIO_MODE_IN_PU)
                {
                    port->BSC = shift;
                }
            }
        }

        port->CFGHIG = CR;
    }
}

/*!
 * @brief     Fills each gpioConfig member with its default value.
 *
 * @param     gpioConfig : pointer to a GPIO_Config_T structure which will be initialized.
 *
 * @retval    None
 */
void GPIO_ConfigStructInit(GPIO_Config_T* gpioConfig)
{
    gpioConfig->pin  = GPIO_PIN_ALL;
    gpioConfig->speed = GPIO_SPEED_2MHz;
    gpioConfig->mode = GPIO_MODE_IN_FLOATING;
}

/*!
 * @brief     Reads the specified input port pin
 *
 * @param     port: Select the GPIO port.
 *                  This parameter can be one of GPIOx( x can be from A to G).
 *
 * @param     pin : specifies pin to read.
 *                  This parameter can be one of GPIO_PIN_x( x can be from 0 to 15).
 *
 * @retval    The input port pin value
 */
uint8_t GPIO_ReadInputBit(GPIO_T* port, uint16_t pin)
{
    uint8_t ret;

    ret = (port->IDATA & pin) ?  BIT_SET : BIT_RESET;

    return ret;
}

/*!
 * @brief     Reads the specified GPIO input data port
 *
 * @param     port: Select the GPIO port.
 *                  This parameter can be one of GPIOx( x can be from A to G).
 *
 * @retval    GPIO input data port value
 */
uint16_t GPIO_ReadInputPort(GPIO_T* port)
{
    return ((uint16_t)port->IDATA);
}

/*!
 * @brief     Reads the specified output data port bit
 *
 * @param     port: Select the GPIO port.
 *                  This parameter can be one of GPIOx( x can be from A to G).
 *
 * @param     pin : specifies pin to read.
 *                  This parameter can be one of GPIO_PIN_x( x can be from 0 to 15).
 *
 * @retval    The output port pin value
 */
uint8_t GPIO_ReadOutputBit(GPIO_T* port, uint16_t pin)
{

    uint8_t ret;

    ret = (port->ODATA & pin) ? BIT_SET : BIT_RESET;

    return ret;
}

/*!
 * @brief     Reads the specified GPIO output data port
 *
 * @param     port: Select the GPIO port.
 *                  This parameter can be one of GPIOx( x can be from A to G).
 *
 * @retval    output data port value
 */
uint16_t GPIO_ReadOutputPort(GPIO_T* port)
{
    return ((uint16_t)port->ODATA);
}

/*!
 * @brief     Sets the selected data port bits
 *
 * @param     port: Select the GPIO port.
 *                  This parameter can be one of GPIOx( x can be from A to G).
 *
 * @param     pin : specifies pin to be written.
 *                  This parameter can be any combination of GPIO_PIN_x( x can be from 0 to 15).
 *
 * @retval    None
 */
void GPIO_SetBit(GPIO_T* port, uint16_t pin)
{
    port->BSC = (uint32_t)pin;
}

/*!
 * @brief     Clears the selected data port bits
 *
 * @param     port: Select the GPIO port.
 *                  This parameter can be one of GPIOx( x can be from A to G).
 *
 * @param     pin : specifies pin to be cleared.
 *                  This parameter can be any combination of GPIO_PIN_x( x can be from 0 to 15).
 *
 * @retval    None
 */
void GPIO_ResetBit(GPIO_T* port, uint16_t pin)
{
    port->BC = (uint32_t)pin;
}

/*!
 * @brief     Writes data to the specified GPIO data port bit
 *
 * @param     port: Select the GPIO port.
 *                  This parameter can be one of GPIOx( x can be from A to G).
 *
 * @param     pin : Select specifies pin.
 *                  This parameter can be one of GPIO_PIN_x( x can be from 0 to 15).
 *
 *
 * @param     bitVal : specifies the value to be written to the port output data register
 *                     This parameter can be one of the following values:
 *                       @arg BIT_RESET: Reset the port pin
 *                       @arg BIT_SET  : Set the port pin
 *
 * @retval    None
 */
void GPIO_WriteBitValue(GPIO_T* port, uint16_t pin, uint8_t bitVal)
{
    if (bitVal != BIT_RESET)
    {
        port->BSC = pin;
    }
    else
    {
        port->BC = pin ;
    }
}

/*!
 * @brief     Writes data to the specified GPIO data port
 *
 * @param     port: Select the GPIO port.
 *                  This parameter can be one of GPIOx( x can be from A to G).
 *
 * @param     portValue : specifies the value to be written to the port output data register.
 *
 * @retval    None
 */
void GPIO_WriteOutputPort(GPIO_T* port, uint16_t portValue)
{
    port->ODATA = (uint32_t)portValue;
}

/*!
 * @brief     Locks GPIO Pins configuration registers
 *
 * @param     port: Select the GPIO port.
 *                  This parameter can be one of GPIOx( x can be from A to G).
 *
 * @param     pin : Select specifies pin.
 *                  This parameter can be any combination of GPIO_PIN_x( x can be from 0 to 15).
 *
 * @retval    None
 */
void GPIO_ConfigPinLock(GPIO_T* port, uint16_t pin)
{
    uint32_t val = 0x00010000;

    val  |= pin;
    /* Set LCKK bit */
    port->LOCK = val ;
    /* Reset LCKK bit */
    port->LOCK =  pin;
    /* Set LCKK bit */
    port->LOCK = val;
    /* Read LCKK bit*/
    val = port->LOCK;
    /* Read LCKK bit*/
    val = port->LOCK;
}

/*!
 * @brief     Selects the GPIO pin used as Event output
 *
 * @param     portSource : selects the GPIO port to be used as source for Event output.
 *                         This parameter can be one of GPIO_PORT_SOURCE_x( x can be from A to E).
 *
 * @param     pinSource   specifies the pin for the Event output
 *                  This parameter can be GPIO_PIN_SOURCE_x( x can be from 0 to 15).
 *
 * @retval    None
 */
void GPIO_ConfigEventOutput(GPIO_PORT_SOURCE_T portSource, GPIO_PIN_SOURCE_T pinSource)
{
    AFIO->EVCTRL_B.PORTSEL =  portSource;
    AFIO->EVCTRL_B.PINSEL = pinSource;
}

/*!
 * @brief     Enables the Event Output
 *
 * @param     None
 *
 * @retval    None
 */
void GPIO_EnableEventOutput(void)
{
    AFIO->EVCTRL_B.EVOEN = BIT_SET;
}

/*!
 * @brief     Disable the Event Output
 *
 * @param     None
 *
 * @retval    None
 */
void GPIO_DisableEventOutput(void)
{
    AFIO->EVCTRL_B.EVOEN = BIT_RESET;
}

/*!
 * @brief     Changes the mapping of the specified pin
 *
 * @param     remap : selects the pin to remap
 *                    This parameter can be one of the following values:
 *                    @arg GPIO_NO_REMAP_SPI1         : No SPI1 Alternate Function mapping
 *                    @arg GPIO_REMAP_SPI1            : SPI1 Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_I2C1         : No I2C1 Alternate Function mapping
 *                    @arg GPIO_REMAP_I2C1            : I2C1 Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_USART1       : No USART1 Alternate Function mapping
 *                    @arg GPIO_REMAP_USART1          : USART1 Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_USART2       : No USART2 Alternate Function mapping
 *                    @arg GPIO_REMAP_USART2          : USART2 Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_USART3       : No USART3 Partial Alternate Function mapping
 *                    @arg GPIO_PARTIAL_REMAP_USART3  : USART3 Partial Alternate Function mapping
 *                    @arg GPIO_FULL_REMAP_USART3     : USART3 Full Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_TMR1         : No TIM1 Partial Alternate Function mapping
 *                    @arg GPIO_PARTIAL_REMAP_TMR1    : TIM1 Partial Alternate Function mapping
 *                    @arg GPIO_FULL_REMAP_TMR1       : TIM1 Full Alternate Function mapping
 *                    @arg GPIO_NO_REMAP1_TMR2        : No TIM2 Partial1 Alternate Function mapping
 *                    @arg GPIO_PARTIAL_REMAP1_TMR2   : TIM2 Partial1 Alternate Function mapping
 *                    @arg GPIO_PARTIAL_REMAP2_TMR2   : TIM2 Partial2 Alternate Function mapping
 *                    @arg GPIO_FULL_REMAP_TMR2       : TIM2 Full Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_TMR3         : No TIM3 Partial Alternate Function mapping
 *                    @arg GPIO_PARTIAL_REMAP_TMR3    : TIM3 Partial Alternate Function mapping
 *                    @arg GPIO_FULL_REMAP_TMR3       : TIM3 Full Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_TMR4         : No TIM4 Alternate Function mapping
 *                    @arg GPIO_REMAP_TMR4            : TIM4 Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_CAN1         : No CAN1 Alternate Function mapping
 *                    @arg GPIO_REMAP1_CAN1           : CAN1 Alternate Function mapping
 *                    @arg GPIO_REMAP2_CAN1           : CAN1 Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_PD01         : No PD01 Alternate Function mapping
 *                    @arg GPIO_REMAP_PD01            : PD01 Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_TMR5CH4_LSI  : No LSI connected to TIM5 Channel4 input capture for calibration
 *                    @arg GPIO_REMAP_TMR5CH4_LSI     : LSI connected to TIM5 Channel4 input capture for calibration
 *                  Only For APM32F10X_CL devices(APM32F107xx and APM32F105xx):
 *                    @arg GPIO_NO_REMAP_ETH_MAC      : No Ethernet MAC Alternate remapping
 *                    @arg GPIO_REMAP_ETH_MAC         : Ethernet MAC Alternate remapping
 *                    @arg GPIO_NO_REMAP_CAN2         : No CAN2 Alternate Function mapping
 *                    @arg GPIO_REMAP_CAN2            : CAN2 Alternate Function mapping
 *                    @arg GPIO_REMAP_MACEISEL_MII    : Ethernet MAC External Interface Select MII Interface
 *                    @arg GPIO_REMAP_MACEISEL_RMII   : Ethernet MAC External Interface Select RMII Interface
 *                    @arg GPIO_NO_REMAP_SPI3         : No SPI3 Alternate Function mapping
 *                    @arg GPIO_REMAP_SPI3            : SPI3 Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_SWJ          : Full SWJ Enabled (JTAG-DP + SW-DP)
 *                    @arg GPIO_REMAP_SWJ_NOJTRST     : Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST
 *                    @arg GPIO_REMAP_SWJ_JTAGDISABLE : JTAG-DP Disabled and SW-DP Enabled
 *                    @arg GPIO_REMAP_SWJ_DISABLE     : Full SWJ Disabled (JTAG-DP + SW-DP)
 *                    @arg GPIO_NO_REMAP_TMR2ITR1     : No TMR2 ITR1 Alternate Function mapping
 *                    @arg GPIO_REMAP_TMR2ITR1        : TMR2 ITR1 Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_PTP_PPS      : No Ethernet MAC PTP_PPS Alternate Function mapping
 *                    @arg GPIO_REMAP_PTP_PPS         : Ethernet MAC PTP_PPS Alternate Function mapping
 *                  For Other APM32F10X_HD/MD/LD devices:
 *                    @arg GPIO_NO_REMAP_ADC1_ETRGINJ : No ADC1 External Trigger Injected Conversion remapping
 *                    @arg GPIO_REMAP_ADC1_ETRGINJ    : ADC1 External Trigger Injected Conversion remapping
 *                    @arg GPIO_NO_REMAP_ADC1_ETRGREG : No ADC1 External Trigger Regular Conversion remapping
 *                    @arg GPIO_REMAP_ADC1_ETRGREG    : ADC1 External Trigger Regular Conversion remapping
 *                    @arg GPIO_NO_REMAP_ADC2_ETRGINJ : No ADC2 External Trigger Injected Conversion remapping
 *                    @arg GPIO_REMAP_ADC2_ETRGINJ    : ADC2 External Trigger Injected Conversion remapping
 *                    @arg GPIO_NO_REMAP_ADC2_ETRGREG : No ADC2 External Trigger Regular Conversion remapping
 *                    @arg GPIO_REMAP_ADC2_ETRGREG    : ADC2 External Trigger Regular Conversion remapping
 *                    @arg GPIO_NO_REMAP_CAN2         : No CAN2 Alternate Function mapping
 *                    @arg GPIO_REMAP_CAN2            : CAN2 Alternate Function mapping
 *                    @arg GPIO_NO_REMAP_SWJ          : Full SWJ Enabled (JTAG-DP + SW-DP)
 *                    @arg GPIO_REMAP_SWJ_NOJTRST     : Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST
 *                    @arg GPIO_REMAP_SWJ_JTAGDISABLE : JTAG-DP Disabled and SW-DP Enabled
 *                    @arg GPIO_REMAP_SWJ_DISABLE     : Full SWJ Disabled (JTAG-DP + SW-DP)
 *
 * @retval    When you use GPIO_REMAP_CAN2, you must put this function last of all other ConfigPinRemap Function.
 */
void GPIO_ConfigPinRemap(GPIO_REMAP_T remap)
{
    uint32_t val, mask, bitOffset, regOffset;
    uint32_t regVal;

    val = remap & 0x0f;
    mask = (remap >> 4) & 0x0f;
    bitOffset = (remap >> 8) & 0xff;
    regOffset = (remap >> 16) & 0x0f;

    if (regOffset)
    {
        regVal = AFIO->REMAP2;
    }
    else
    {
        regVal = AFIO->REMAP1;
    }

    if (remap >> 8 == 0x18)
    {
        regVal &= 0xF0FFFFFF;
        AFIO->REMAP1 &= 0xF0FFFFFF;
    }
    else
    {
        regVal |= 0x0F000000;
    }

    mask <<= bitOffset;
    regVal &= (uint32_t)~mask;
    val <<= bitOffset;
    regVal |= val;

    if (regOffset)
    {
        AFIO->REMAP2 = regVal;
    }
    else
    {
        AFIO->REMAP1 = regVal;
    }
}

/*!
 * @brief     Selects the GPIO pin used as EINT Line
 *
 * @param     portSource : selects the GPIO port to be used as source for EINT line.
 *                         This parameter can be one of GPIO_PORT_SOURCE_x( x can be from A to G).
 *
 * @param     pinSource : Specifies the EINT line to be configured.
 *                        This parameter can be GPIO_PIN_SOURCE_x( x can be from 0 to 15).
 *
 * @retval    None
 */
void GPIO_ConfigEINTLine(GPIO_PORT_SOURCE_T portSource, GPIO_PIN_SOURCE_T pinSource)
{
    uint32_t shift;

    if (pinSource <= GPIO_PIN_SOURCE_3)
    {
        shift = pinSource << 2;
        AFIO->EINTSEL1 &= (uint32_t)~(0x0f << shift);
        AFIO->EINTSEL1 |=  portSource << shift;
    }

    else if (pinSource <= GPIO_PIN_SOURCE_7)
    {
        shift = (pinSource - GPIO_PIN_SOURCE_4) << 2;
        AFIO->EINTSEL2 &= (uint32_t)~(0x0f << shift);
        AFIO->EINTSEL2 |=  portSource << shift;
    }

    else if (pinSource <= GPIO_PIN_SOURCE_11)
    {
        shift = (pinSource - GPIO_PIN_SOURCE_8) << 2;
        AFIO->EINTSEL3 &= (uint32_t)~(0x0f << shift);
        AFIO->EINTSEL3 |=  portSource << shift;
    }

    else if (pinSource <= GPIO_PIN_SOURCE_15)
    {
        shift = (pinSource - GPIO_PIN_SOURCE_12) << 2;
        AFIO->EINTSEL4 &= (uint32_t)~(0x0f << shift);
        AFIO->EINTSEL4 |=  portSource << shift;
    }
}

/**@} end of group GPIO_Functions*/
/**@} end of group GPIO_Driver*/
/**@} end of group APM32F10x_StdPeriphDriver*/
