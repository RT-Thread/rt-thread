/*!
 * @file        apm32f4xx_gpio.c
 *
 * @brief       This file provides all the GPIO firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f4xx_gpio.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup GPIO_Driver
  * @brief GPIO driver modules
  @{
*/

/** @defgroup GPIO_Functions
  @{
*/

/*!
 * @brief  Reset the GPIOx peripheral registers to their default reset values.
 *
 * @param  port: Select the GPIO port.
 *               This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral
 *               for APM32F405xx/407xx and APM32F415xx/417xx devices
 * @retval None
 *
 * @note   By reset, The GPIO pins are configured in input floating mode (except the JTAG pins).
 */
void GPIO_Reset(GPIO_T *port)
{
    RCM_AHB1_PERIPH_T AHB1Periph;

    if (port == GPIOA)
    {
        AHB1Periph = RCM_AHB1_PERIPH_GPIOA;
    }
    else if (port == GPIOB)
    {
        AHB1Periph = RCM_AHB1_PERIPH_GPIOB;
    }
    else if (port == GPIOC)
    {
        AHB1Periph = RCM_AHB1_PERIPH_GPIOC;
    }
    else if (port == GPIOD)
    {
        AHB1Periph = RCM_AHB1_PERIPH_GPIOD;
    }
    else if (port == GPIOE)
    {
        AHB1Periph = RCM_AHB1_PERIPH_GPIOE;
    }
    else if (port == GPIOF)
    {
        AHB1Periph = RCM_AHB1_PERIPH_GPIOF;
    }
    else if (port == GPIOG)
    {
        AHB1Periph = RCM_AHB1_PERIPH_GPIOG;
    }
    else if (port == GPIOH)
    {
        AHB1Periph = RCM_AHB1_PERIPH_GPIOH;
    }
    else if (port == GPIOI)
    {
        AHB1Periph = RCM_AHB1_PERIPH_GPIOI;
    }
    else if (port == GPIOJ)
    {
        AHB1Periph = RCM_AHB1_PERIPH_GPIOJ;
    }
    else if (port == GPIOK)
    {
        AHB1Periph = RCM_AHB1_PERIPH_GPIOK;
    }

    RCM_EnableAHB1PeriphReset(AHB1Periph);
    RCM_DisableAHB1PeriphReset(AHB1Periph);
}

/*!
 * @brief        Config the GPIO peripheral according to the specified parameters in the gpioConfig
 *
 * @param        port: Select the GPIO port.
 *                     This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral
 *                     for APM32F405xx/407xx and APM32F415xx/417xx devices
 *
 * @param       gpioConfig: pointer to a GPIO_Config_T structure
 *
 * @retval      None
 */
void GPIO_Config(GPIO_T *port, GPIO_Config_T *gpioConfig)
{
    uint32_t i = 0x00;
    uint32_t pos = 0x00;
    uint32_t temp = 0x00;

    for (i = 0; i < 16; i++)
    {
        pos = ((uint32_t)0x01) << i;
        temp = (gpioConfig->pin) & pos;

        if (temp == pos)
        {
            port->MODE  &= ~(0x03 << (i * 2));
            port->MODE |= (((uint32_t)gpioConfig->mode) << (i * 2));

            if ((gpioConfig->mode == GPIO_MODE_OUT) || (gpioConfig->mode == GPIO_MODE_AF))
            {
                port->OSSEL &= ~(0x03 << (i * 2));
                port->OSSEL |= ((uint32_t)(gpioConfig->speed) << (i * 2));

                port->OMODE  &= ~(0x01 << ((uint16_t)i)) ;
                port->OMODE |= (uint16_t)(((uint16_t)gpioConfig->otype) << ((uint16_t)i));
            }

            port->PUPD &= ~(0x03 << ((uint16_t)i * 2));
            port->PUPD |= (((uint32_t)gpioConfig->pupd) << (i * 2));
        }
    }
}

/*!
 * @brief       Fills every gpioConfig member with its default value.
 *
 * @param       gpioConfig : pointer to a GPIO_Config_T structure which will be initialized.
 *
 * @retval      None
 */
void GPIO_ConfigStructInit(GPIO_Config_T *gpioConfig)
{
    gpioConfig->pin  = GPIO_PIN_ALL;
    gpioConfig->mode = GPIO_MODE_IN;
    gpioConfig->speed = GPIO_SPEED_2MHz;
    gpioConfig->otype = GPIO_OTYPE_PP;
    gpioConfig->pupd = GPIO_PUPD_NOPULL;
}

/*!
 * @brief        Lock GPIO Pins config registers.
 *
 * @param        port: Select the GPIO port.
 *                     This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral
 *                     for APM32F405xx/407xx and APM32F415xx/417xx devices
 *
 * @param        pin: specifies the pin bit to be locked.
 *                    This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 *
 * @retval       None
 *
 * @note         Locked registers are GPIOx_MODER, GPIOx_OMODER, GPIOx_OOSSELR,
 *               GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH,until the next reset the
 *               configuration of the locked GPIO pins can no longer be config.
 *
 */
void GPIO_ConfigPinLock(GPIO_T *port, uint16_t pin)
{
    __IOM uint32_t temp = 0x00010000;

    temp |= pin;

    port->LOCK = temp;

    port->LOCK = pin;

    port->LOCK = temp;

    temp = port->LOCK;
}

/*!
 * @brief        Reads the specified input port pin.
 *
 * @param        port :Select the GPIO port.
 *                     This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral
 *                     for APM32F405xx/407xx and APM32F415xx/417xx devices
 *
 * @param        pin: specifies the port bit to read.
 *                    This parameter can be GPIO_Pin_x where x can be (0..15).
 *
 * @retval The input port pin value.
 */
uint8_t GPIO_ReadInputBit(GPIO_T *port, uint16_t pin)
{
    uint8_t readBit = 0x00;

    readBit = (port->IDATA & pin) ?  BIT_SET : BIT_RESET;

    return readBit;
}

/*!
 * @brief        Reads the specified GPIO input data port.
 *
 * @param        port :Select the GPIO port.
 *                     This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral
 *                     for APM32F405xx/407xx and APM32F415xx/417xx devices
 *
 * @retval      GPIO input data port value.
 */
uint16_t GPIO_ReadInputPort(GPIO_T *port)
{
    return ((uint16_t)port->IDATA);
}

/*!
 * @brief        Reads the specified output data port bit.
 *
 * @param        port :Select the GPIO port.
 *                     This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral
 *                     for APM32F405xx/407xx and APM32F415xx/417xx devices
 *
 * @param        pin: specifies the port bit to read.
 *                    This parameter can be one of GPIO_Pin_x where x can be (0..15).
 *
 * @retval       The output port pin value.
 */
uint8_t GPIO_ReadOutputBit(GPIO_T *port, uint16_t pin)
{
    uint8_t readBit = 0x00;

    readBit = (port->ODATA & pin) ? BIT_SET : BIT_RESET;

    return readBit;
}

/*!
 * @brief        Reads the specified GPIO output data port
 *
 * @param        port: Select the GPIO port.
 *                     This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral
 *                     for APM32F405xx/407xx and APM32F415xx/417xx devices
 *
 * @retval       output data port value
 */
uint16_t GPIO_ReadOutputPort(GPIO_T *port)
{
    return ((uint16_t)port->ODATA);
}

/*!
 * @brief        Sets the selected data port bits
 *
 * @param        port: Select the GPIO port.
 *                     This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral
 *                     for APM32F405xx/407xx and APM32F415xx/417xx devices
 *
 * @param        pin : specifies pin to be written.
 *                  This parameter can be any combination of GPIO_PIN_x( x can be from 0 to 15).
 *
 * @retval       None
 */
void GPIO_SetBit(GPIO_T *port, uint16_t pin)
{
    port->BSCL = pin;
}

/*!
 * @brief     Clears the selected data port bits
 *
 * @param        port: Select the GPIO port.
 *                     This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral
 *                     for APM32F405xx/407xx and APM32F415xx/417xx devices
 *
 * @param     pin : specifies pin to be cleared.
 *                  This parameter can be any combination of GPIO_PIN_x( x can be from 0 to 15).
 *
 * @retval    None
 */
void GPIO_ResetBit(GPIO_T *port, uint16_t pin)
{
    port->BSCH = pin;
}

/*!
 * @brief        Writes data to the specified GPIO data port bit
 *
 * @param        port: Select the GPIO port.
 *                     This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral
 *                     for APM32F405xx/407xx and APM32F415xx/417xx devices
 *
 * @param        pin : Select specifies pin.
 *                  This parameter can be one of GPIO_PIN_x( x can be from 0 to 15).
 *
 * @param       bitVal : specifies the value to be written to the port output data register
 *                       This parameter can be one of the following values:
 *                       @arg BIT_RESET : Reset the port pin
 *                       @arg BIT_SET   : Set the port pin
 *
 * @retval       None
 */
void GPIO_WriteBitValue(GPIO_T *port, uint16_t pin, uint8_t bitVal)
{
    if (bitVal != BIT_RESET)
    {
        port->BSCL = pin;
    }
    else
    {
        port->BSCH = pin ;
    }
}

/*!
 * @brief        Writes data to the specified GPIO data port
 *
 * @param        port: Select the GPIO port.
 *                     This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral
 *                     for APM32F405xx/407xx and APM32F415xx/417xx devices
 *
 * @param        portValue : specifies the value to be written to the port output data register.
 *
 * @retval       None
 */
void GPIO_WriteOutputPort(GPIO_T *port, uint16_t portValue)
{
    port->ODATA = (uint16_t)portValue;
}

/*!
 * @brief       Toggles the specified GPIO pins.
 *
 * @param       port: Select the GPIO port.
 *                    This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral.
 *
 * @param       pin: Specifies the pins to be toggled.
 *
 * @retval      None
 */
void GPIO_ToggleBit(GPIO_T *port, uint16_t pin)
{
    port->ODATA ^= pin;
}

/*!
 * @brief        Changes the mapping of the specified pin.
 *
 * @param        port: Select the GPIO port.
 *                     This parameter can be one of GPIOx(x=A..K) to select the GPIO peripheral.
 *
 * @param        gpioPinSource: specifies the pin for the Alternate function.
 *                              This parameter can be GPIO_PinSourcex where x can be (0..15).
 *
 * @param        gpioAf: selects the pin to used as Alternate function.
 *                       This parameter can be one of the following values:
 *                       @arg GPIO_AF_RTC_50Hz: Connect RTC_50Hz pin to AF0 (default after reset)
 *                       @arg GPIO_AF_MCO: Connect MCO pin (MCO1 and MCO2) to AF0 (default after reset)
 *                       @arg GPIO_AF_TAMPER: Connect TAMPER pins (TAMPER_1 and TAMPER_2) to AF0 (default after reset)
 *                       @arg GPIO_AF_SWJ: Connect SWJ pins (SWD and JTAG)to AF0 (default after reset)
 *                       @arg GPIO_AF_TRACE: Connect TRACE pins to AF0 (default after reset)
 *                       @arg GPIO_AF_TMR1: Connect TMR1 pins to AF1
 *                       @arg GPIO_AF_TMR2: Connect TMR2 pins to AF1
 *                       @arg GPIO_AF_TMR3: Connect TMR3 pins to AF2
 *                       @arg GPIO_AF_TMR4: Connect TMR4 pins to AF2
 *                       @arg GPIO_AF_TMR5: Connect TMR5 pins to AF2
 *                       @arg GPIO_AF_TMR8: Connect TMR8 pins to AF3
 *                       @arg GPIO_AF_TMR9: Connect TMR9 pins to AF3
 *                       @arg GPIO_AF_TMR10: Connect TMR10 pins to AF3
 *                       @arg GPIO_AF_TMR11: Connect TMR11 pins to AF3
 *                       @arg GPIO_AF_I2C1: Connect I2C1 pins to AF4
 *                       @arg GPIO_AF_I2C2: Connect I2C2 pins to AF4
 *                       @arg GPIO_AF_I2C3: Connect I2C3 pins to AF4
 *                       @arg GPIO_AF_SPI1: Connect SPI1 pins to AF5
 *                       @arg GPIO_AF_SPI2: Connect SPI2/I2S2 pins to AF5
 *                       @arg GPIO_AF_SPI4: Connect SPI4 pins to AF5
 *                       @arg GPIO_AF_SPI5: Connect SPI5 pins to AF5
 *                       @arg GPIO_AF_SPI6: Connect SPI6 pins to AF5
 *                       @arg GPIO_AF_SAI1: Connect SAI1 pins to AF6
 *                       @arg GPIO_AF_SPI3: Connect SPI3/I2S3 pins to AF6
 *                       @arg GPIO_AF_I2S3ext: Connect I2S3ext pins to AF7
 *                       @arg GPIO_AF_USART1: Connect USART1 pins to AF7
 *                       @arg GPIO_AF_USART2: Connect USART2 pins to AF7
 *                       @arg GPIO_AF_USART3: Connect USART3 pins to AF7
 *                       @arg GPIO_AF_UART4: Connect UART4 pins to AF8
 *                       @arg GPIO_AF_UART5: Connect UART5 pins to AF8
 *                       @arg GPIO_AF_USART6: Connect USART6 pins to AF8
 *                       @arg GPIO_AF_UART7: Connect UART7 pins to AF8
 *                       @arg GPIO_AF_UART8: Connect UART8 pins to AF8
 *                       @arg GPIO_AF_CAN1: Connect CAN1 pins to AF9
 *                       @arg GPIO_AF_CAN2: Connect CAN2 pins to AF9
 *                       @arg GPIO_AF_TMR12: Connect TMR12 pins to AF9
 *                       @arg GPIO_AF_TMR13: Connect TMR13 pins to AF9
 *                       @arg GPIO_AF_TMR14: Connect TMR14 pins to AF9
 *                       @arg GPIO_AF_OTG_FS: Connect OTG_FS pins to AF10
 *                       @arg GPIO_AF_OTG_HS: Connect OTG_HS pins to AF10
 *                       @arg GPIO_AF_ETH: Connect ETHERNET pins to AF11
 *                       @arg GPIO_AF_FSMC: Connect FSMC pins to AF12
 *                       @arg GPIO_AF_OTG_HS_FS: Connect OTG HS (configured in FS) pins to AF12
 *                       @arg GPIO_AF_SDIO: Connect SDIO pins to AF12
 *                       @arg GPIO_AF_DCMI: Connect DCMI pins to AF13
 *                       @arg GPIO_AF_EVENTOUT: Connect EVENTOUT pins to AF15
 *
 * @retval    None
 */
void GPIO_ConfigPinAF(GPIO_T *port, GPIO_PIN_SOURCE_T gpioPinSource, GPIO_AF_T gpioAf)
{
    uint32_t val = 0x00;
    uint32_t val_2 = 0x00;

    if (gpioPinSource >> 0x03 == 0)
    {
        val = (uint32_t)(gpioAf) << (((uint32_t)gpioPinSource & (uint32_t)0x07) * 4);
        port->ALFL &= ~((uint32_t)0xF << (((uint32_t)gpioPinSource & (uint32_t)0x07) * 4)) ;
        val_2 = port->ALFL | val;
        port->ALFL = val_2;
    }
    else
    {
        val = (uint32_t)(gpioAf) << (((uint32_t)gpioPinSource & (uint32_t)0x07) * 4);
        port->ALFH &= ~((uint32_t)0xF << (((uint32_t)gpioPinSource & (uint32_t)0x07) * 4)) ;
        val_2 = port->ALFH | val;
        port->ALFH = val_2;
    }
}

/**@} end of group GPIO_Functions */
/**@} end of group GPIO_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
