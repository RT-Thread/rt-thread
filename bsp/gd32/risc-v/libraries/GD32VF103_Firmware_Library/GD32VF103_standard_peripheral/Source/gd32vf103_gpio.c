/*!
    \file    gd32vf103_gpio.c
    \brief   GPIO driver

    \version 2019-06-05, V1.0.0, firmware for GD32VF103
    \version 2020-08-04, V1.1.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32vf103_gpio.h"

#define AFIO_EXTI_SOURCE_MASK              ((uint8_t)0x03U)         /*!< AFIO exti source selection mask*/
#define AFIO_EXTI_SOURCE_FIELDS            ((uint8_t)0x04U)         /*!< select AFIO exti source registers */
#define LSB_16BIT_MASK                     ((uint16_t)0xFFFFU)      /*!< LSB 16-bit mask */
#define PCF_POSITION_MASK                  ((uint32_t)0x000F0000U)  /*!< AFIO_PCF register position mask */
#define PCF_SWJCFG_MASK                    ((uint32_t)0xF0FFFFFFU)  /*!< AFIO_PCF register SWJCFG mask */
#define PCF_LOCATION1_MASK                 ((uint32_t)0x00200000U)  /*!< AFIO_PCF register location1 mask */
#define PCF_LOCATION2_MASK                 ((uint32_t)0x00100000U)  /*!< AFIO_PCF register location2 mask */
#define AFIO_PCF1_FIELDS                   ((uint32_t)0x80000000U)  /*!< select AFIO_PCF1 register */
#define GPIO_OUTPUT_PORT_OFFSET            ((uint32_t)4U)           /*!< GPIO event output port offset*/

/*!
    \brief      reset GPIO port
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E)
    \param[out] none
    \retval     none
*/
void gpio_deinit(uint32_t gpio_periph)
{
    switch (gpio_periph) {
    case GPIOA:
        /* reset GPIOA */
        rcu_periph_reset_enable(RCU_GPIOARST);
        rcu_periph_reset_disable(RCU_GPIOARST);
        break;
    case GPIOB:
        /* reset GPIOB */
        rcu_periph_reset_enable(RCU_GPIOBRST);
        rcu_periph_reset_disable(RCU_GPIOBRST);
        break;
    case GPIOC:
        /* reset GPIOC */
        rcu_periph_reset_enable(RCU_GPIOCRST);
        rcu_periph_reset_disable(RCU_GPIOCRST);
        break;
    case GPIOD:
        /* reset GPIOD */
        rcu_periph_reset_enable(RCU_GPIODRST);
        rcu_periph_reset_disable(RCU_GPIODRST);
        break;
    case GPIOE:
        /* reset GPIOE */
        rcu_periph_reset_enable(RCU_GPIOERST);
        rcu_periph_reset_disable(RCU_GPIOERST);
        break;
    default:
        break;
    }
}

/*!
    \brief      reset alternate function I/O(AFIO)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_afio_deinit(void)
{
    rcu_periph_reset_enable(RCU_AFRST);
    rcu_periph_reset_disable(RCU_AFRST);
}

/*!
    \brief      GPIO parameter initialization
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E)
    \param[in]  mode: gpio pin mode
                only one parameter can be selected which is shown as below:
      \arg        GPIO_MODE_AIN: analog input mode
      \arg        GPIO_MODE_IN_FLOATING: floating input mode
      \arg        GPIO_MODE_IPD: pull-down input mode
      \arg        GPIO_MODE_IPU: pull-up input mode
      \arg        GPIO_MODE_OUT_OD: GPIO output with open-drain
      \arg        GPIO_MODE_OUT_PP: GPIO output with push-pull
      \arg        GPIO_MODE_AF_OD: AFIO output with open-drain
      \arg        GPIO_MODE_AF_PP: AFIO output with push-pull
    \param[in]  speed: gpio output max speed value
                only one parameter can be selected which is shown as below:
      \arg        GPIO_OSPEED_10MHZ: output max speed 10MHz
      \arg        GPIO_OSPEED_2MHZ: output max speed 2MHz
      \arg        GPIO_OSPEED_50MHZ: output max speed 50MHz
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL

    \param[out] none
    \retval     none
*/
void gpio_init(uint32_t gpio_periph, uint32_t mode, uint32_t speed,
        uint32_t pin)
{
    uint16_t i;
    uint32_t temp_mode = 0U;
    uint32_t reg = 0U;

    /* GPIO mode configuration */
    temp_mode = (uint32_t) (mode & ((uint32_t) 0x0FU));

    /* GPIO speed configuration */
    if (((uint32_t) 0x00U) != ((uint32_t) mode & ((uint32_t) 0x10U))) {
        /* output mode max speed:10MHz,2MHz,50MHz */
        temp_mode |= (uint32_t) speed;
    }

    /* configure the eight low port pins with GPIO_CTL0 */
    for (i = 0U; i < 8U; i++) {
        if ((1U << i) & pin) {
            reg = GPIO_CTL0(gpio_periph);

            /* clear the specified pin mode bits */
            reg &= ~GPIO_MODE_MASK(i);
            /* set the specified pin mode bits */
            reg |= GPIO_MODE_SET(i, temp_mode);

            /* set IPD or IPU */
            if (GPIO_MODE_IPD == mode) {
                /* reset the corresponding OCTL bit */
                GPIO_BC(gpio_periph) = (uint32_t) ((1U << i) & pin);
            } else {
                /* set the corresponding OCTL bit */
                if (GPIO_MODE_IPU == mode) {
                    GPIO_BOP(gpio_periph) = (uint32_t) ((1U << i) & pin);
                }
            }
            /* set GPIO_CTL0 register */
            GPIO_CTL0(gpio_periph) = reg;
        }
    }
    /* configure the eight high port pins with GPIO_CTL1 */
    for (i = 8U; i < 16U; i++) {
        if ((1U << i) & pin) {
            reg = GPIO_CTL1(gpio_periph);

            /* clear the specified pin mode bits */
            reg &= ~GPIO_MODE_MASK(i - 8U);
            /* set the specified pin mode bits */
            reg |= GPIO_MODE_SET(i - 8U, temp_mode);

            /* set IPD or IPU */
            if (GPIO_MODE_IPD == mode) {
                /* reset the corresponding OCTL bit */
                GPIO_BC(gpio_periph) = (uint32_t) ((1U << i) & pin);
            } else {
                /* set the corresponding OCTL bit */
                if (GPIO_MODE_IPU == mode) {
                    GPIO_BOP(gpio_periph) = (uint32_t) ((1U << i) & pin);
                }
            }
            /* set GPIO_CTL1 register */
            GPIO_CTL1(gpio_periph) = reg;
        }
    }
}

/*!
    \brief      set GPIO pin
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_set(uint32_t gpio_periph, uint32_t pin)
{
    GPIO_BOP(gpio_periph) = (uint32_t) pin;
}

/*!
    \brief      reset GPIO pin
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_reset(uint32_t gpio_periph, uint32_t pin)
{
    GPIO_BC(gpio_periph) = (uint32_t) pin;
}

/*!
    \brief      write data to the specified GPIO pin
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[in]  bit_value: SET or RESET
                only one parameter can be selected which is shown as below:
      \arg        RESET: clear the port pin
      \arg        SET: set the port pin
    \param[out] none
    \retval     none
*/
void gpio_bit_write(uint32_t gpio_periph, uint32_t pin, bit_status bit_value)
{
    if (RESET != bit_value) {
        GPIO_BOP(gpio_periph) = (uint32_t) pin;
    } else {
        GPIO_BC(gpio_periph) = (uint32_t) pin;
    }
}

/*!
    \brief      write data to the specified GPIO port
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E)
    \param[in]  data: specify the value to be written to the port output data register
    \param[out] none
    \retval     none
*/
void gpio_port_write(uint32_t gpio_periph, uint16_t data)
{
    GPIO_OCTL(gpio_periph) = (uint32_t) data;
}

/*!
    \brief      get GPIO pin input status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E)
    \param[in]  pin: GPIO pin
                only one parameter can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     input status of gpio pin: SET or RESET
*/
FlagStatus gpio_input_bit_get(uint32_t gpio_periph, uint32_t pin)
{
    if ((uint32_t) RESET != (GPIO_ISTAT(gpio_periph) & (pin))) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      get GPIO port input status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E)
    \param[out] none
    \retval     input status of gpio all pins
*/
uint16_t gpio_input_port_get(uint32_t gpio_periph)
{
    return (uint16_t) (GPIO_ISTAT(gpio_periph));
}

/*!
    \brief      get GPIO pin output status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E)
    \param[in]  pin: GPIO pin
                only one parameter can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     output status of gpio pin: SET or RESET
*/
FlagStatus gpio_output_bit_get(uint32_t gpio_periph, uint32_t pin)
{
    if ((uint32_t) RESET != (GPIO_OCTL(gpio_periph) & (pin))) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      get GPIO port output status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E)
    \param[out] none
    \retval     output status of gpio all pins
*/
uint16_t gpio_output_port_get(uint32_t gpio_periph)
{
    return ((uint16_t) GPIO_OCTL(gpio_periph));
}

/*!
    \brief      configure GPIO pin remap
    \param[in]  gpio_remap: select the pin to remap
                only one parameter can be selected which are shown as below:
      \arg        GPIO_SPI0_REMAP: SPI0 remapping
      \arg        GPIO_I2C0_REMAP: I2C0 remapping
      \arg        GPIO_USART0_REMAP: USART0 remapping
      \arg        GPIO_USART1_REMAP: USART1 remapping
      \arg        GPIO_USART2_PARTIAL_REMAP: USART2 partial remapping
      \arg        GPIO_USART2_FULL_REMAP: USART2 full remapping
      \arg        GPIO_TIMER0_PARTIAL_REMAP: TIMER0 partial remapping
      \arg        GPIO_TIMER0_FULL_REMAP: TIMER0 full remapping
      \arg        GPIO_TIMER1_PARTIAL_REMAP0: TIMER1 partial remapping
      \arg        GPIO_TIMER1_PARTIAL_REMAP1: TIMER1 partial remapping
      \arg        GPIO_TIMER1_FULL_REMAP: TIMER1 full remapping
      \arg        GPIO_TIMER2_PARTIAL_REMAP: TIMER2 partial remapping
      \arg        GPIO_TIMER2_FULL_REMAP: TIMER2 full remapping
      \arg        GPIO_TIMER3_REMAP: TIMER3 remapping
      \arg        GPIO_CAN0_PARTIAL_REMAP: CAN0 partial remapping
      \arg        GPIO_CAN0_FULL_REMAP: CAN0 full remapping
      \arg        GPIO_PD01_REMAP: PD01 remapping
      \arg        GPIO_TIMER4CH3_IREMAP: TIMER4 channel3 internal remapping
      \arg        GPIO_CAN1_REMAP: CAN1 remapping
      \arg        GPIO_SWJ_NONJTRST_REMAP: JTAG-DP,but without NJTRST
      \arg        GPIO_SWJ_DISABLE_REMAP: JTAG-DP disabled
      \arg        GPIO_SPI2_REMAP: SPI2 remapping
      \arg        GPIO_TIMER1ITI1_REMAP: TIMER1 internal trigger 1 remapping
      \arg        GPIO_EXMC_NADV_REMAP: EXMC_NADV connect/disconnect
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void gpio_pin_remap_config(uint32_t remap, ControlStatus newvalue)
{
    uint32_t remap1 = 0U, remap2 = 0U, temp_reg = 0U, temp_mask = 0U;

    if (AFIO_PCF1_FIELDS == (remap & AFIO_PCF1_FIELDS)) {
        /* get AFIO_PCF1 regiter value */
        temp_reg = AFIO_PCF1;
    } else {
        /* get AFIO_PCF0 regiter value */
        temp_reg = AFIO_PCF0;
    }

    temp_mask = (remap & PCF_POSITION_MASK) >> 0x10U;
    remap1 = remap & LSB_16BIT_MASK;

    /* judge pin remap type */
    if ((PCF_LOCATION1_MASK | PCF_LOCATION2_MASK)
            == (remap & (PCF_LOCATION1_MASK | PCF_LOCATION2_MASK))) {
        temp_reg &= PCF_SWJCFG_MASK;
        AFIO_PCF0 &= PCF_SWJCFG_MASK;
    } else if (PCF_LOCATION2_MASK == (remap & PCF_LOCATION2_MASK)) {
        remap2 = ((uint32_t) 0x03U) << temp_mask;
        temp_reg &= ~remap2;
        temp_reg |= ~PCF_SWJCFG_MASK;
    }  else {
        temp_reg &= ~(remap1 << ((remap >> 0x15U) * 0x10U));
        temp_reg |= ~PCF_SWJCFG_MASK;
    }

    /* set pin remap value */
    if (DISABLE != newvalue) {
        temp_reg |= (remap1 << ((remap >> 0x15U) * 0x10U));
    }

    if (AFIO_PCF1_FIELDS == (remap & AFIO_PCF1_FIELDS)) {
        /* set AFIO_PCF1 regiter value */
        AFIO_PCF1 = temp_reg;
    } else {
        /* set AFIO_PCF0 regiter value */
        AFIO_PCF0 = temp_reg;
    }
}

/*!
    \brief      select GPIO pin exti sources
    \param[in]  gpio_outputport: gpio event output port
                only one parameter can be selected which are shown as below:
      \arg        GPIO_PORT_SOURCE_GPIOA: output port source A
      \arg        GPIO_PORT_SOURCE_GPIOB: output port source B
      \arg        GPIO_PORT_SOURCE_GPIOC: output port source C
      \arg        GPIO_PORT_SOURCE_GPIOD: output port source D
      \arg        GPIO_PORT_SOURCE_GPIOE: output port source E
    \param[in]  gpio_outputpin: GPIO_PIN_SOURCE_x(x=0..15)
    \param[out] none
    \retval     none
*/
void gpio_exti_source_select(uint8_t output_port, uint8_t output_pin)
{
    uint32_t source = 0U;
    source = ((uint32_t) 0x0FU)
            << (AFIO_EXTI_SOURCE_FIELDS * (output_pin & AFIO_EXTI_SOURCE_MASK));

    /* select EXTI sources */
    if (GPIO_PIN_SOURCE_4 > output_pin) {
        /* select EXTI0/EXTI1/EXTI2/EXTI3 */
        AFIO_EXTISS0 &= ~source;
        AFIO_EXTISS0 |= (((uint32_t) output_port)
                << (AFIO_EXTI_SOURCE_FIELDS
                        * (output_pin & AFIO_EXTI_SOURCE_MASK)));
    } else if (GPIO_PIN_SOURCE_8 > output_pin) {
        /* select EXTI4/EXTI5/EXTI6/EXTI7 */
        AFIO_EXTISS1 &= ~source;
        AFIO_EXTISS1 |= (((uint32_t) output_port)
                << (AFIO_EXTI_SOURCE_FIELDS
                        * (output_pin & AFIO_EXTI_SOURCE_MASK)));
    } else if (GPIO_PIN_SOURCE_12 > output_pin) {
        /* select EXTI8/EXTI9/EXTI10/EXTI11 */
        AFIO_EXTISS2 &= ~source;
        AFIO_EXTISS2 |= (((uint32_t) output_port)
                << (AFIO_EXTI_SOURCE_FIELDS
                        * (output_pin & AFIO_EXTI_SOURCE_MASK)));
    } else {
        /* select EXTI12/EXTI13/EXTI14/EXTI15 */
        AFIO_EXTISS3 &= ~source;
        AFIO_EXTISS3 |= (((uint32_t) output_port)
                << (AFIO_EXTI_SOURCE_FIELDS
                        * (output_pin & AFIO_EXTI_SOURCE_MASK)));
    }
}

/*!
    \brief      configure GPIO pin event output
    \param[in]  output_port: gpio event output port
                only one parameter can be selected which are shown as below:
      \arg        GPIO_EVENT_PORT_GPIOA: event output port A
      \arg        GPIO_EVENT_PORT_GPIOB: event output port B
      \arg        GPIO_EVENT_PORT_GPIOC: event output port C
      \arg        GPIO_EVENT_PORT_GPIOD: event output port D
      \arg        GPIO_EVENT_PORT_GPIOE: event output port E
    \param[in]  output_pin:
                only one parameter can be selected which are shown as below:
      \arg        GPIO_EVENT_PIN_x(x=0..15)
    \param[out] none
    \retval     none
*/
void gpio_event_output_config(uint8_t output_port, uint8_t output_pin)
{
    uint32_t reg = 0U;
    reg = AFIO_EC;

    /* clear AFIO_EC_PORT and AFIO_EC_PIN bits */
    reg &= (uint32_t) (~(AFIO_EC_PORT | AFIO_EC_PIN));

    reg |= (uint32_t) ((uint32_t) output_port << GPIO_OUTPUT_PORT_OFFSET);
    reg |= (uint32_t) output_pin;

    AFIO_EC = reg;
}

/*!
    \brief      enable GPIO pin event output
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_event_output_enable(void)
{
    AFIO_EC |= AFIO_EC_EOE;
}

/*!
    \brief      disable GPIO pin event output
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_event_output_disable(void)
{
    AFIO_EC &= (uint32_t) (~AFIO_EC_EOE);
}

/*!
    \brief      lock GPIO pin
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_pin_lock(uint32_t gpio_periph, uint32_t pin)
{
    uint32_t lock = 0x00010000U;
    lock |= pin;

    /* lock key writing sequence: write 1 -> write 0 -> write 1 -> read 0 -> read 1 */
    GPIO_LOCK(gpio_periph) = (uint32_t) lock;
    GPIO_LOCK(gpio_periph) = (uint32_t) pin;
    GPIO_LOCK(gpio_periph) = (uint32_t) lock;
    lock = GPIO_LOCK(gpio_periph);
    lock = GPIO_LOCK(gpio_periph);
}
