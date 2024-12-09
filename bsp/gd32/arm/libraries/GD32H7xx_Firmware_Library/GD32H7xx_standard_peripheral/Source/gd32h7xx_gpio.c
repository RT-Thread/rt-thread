/*!
    \file    gd32h7xx_gpio.c
    \brief   GPIO driver

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

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

#include "gd32h7xx_gpio.h"

/*!
    \brief      reset GPIO port
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[out] none
    \retval     none
*/
void gpio_deinit(uint32_t gpio_periph)
{
    switch(gpio_periph)
    {
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
    case GPIOF:
        /* reset GPIOF */
        rcu_periph_reset_enable(RCU_GPIOFRST);
        rcu_periph_reset_disable(RCU_GPIOFRST);
        break;
    case GPIOG:
        /* reset GPIOG */
        rcu_periph_reset_enable(RCU_GPIOGRST);
        rcu_periph_reset_disable(RCU_GPIOGRST);
        break;
    case GPIOH:
        /* reset GPIOH */
        rcu_periph_reset_enable(RCU_GPIOHRST);
        rcu_periph_reset_disable(RCU_GPIOHRST);
        break;
    case GPIOJ:
        /* reset GPIOJ */
        rcu_periph_reset_enable(RCU_GPIOJRST);
        rcu_periph_reset_disable(RCU_GPIOJRST);
        break;
    case GPIOK:
        /* reset GPIOK */
        rcu_periph_reset_enable(RCU_GPIOKRST);
        rcu_periph_reset_disable(RCU_GPIOKRST);
        break;
    default:
        break;
    }
}

/*!
    \brief      set GPIO mode
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[in]  mode: gpio pin mode
                only one parameter can be selected which is shown as below:
      \arg        GPIO_MODE_INPUT: input mode
      \arg        GPIO_MODE_OUTPUT: output mode
      \arg        GPIO_MODE_AF: alternate function mode
      \arg        GPIO_MODE_ANALOG: analog mode
    \param[in]  pull_up_down: gpio pin with pull-up or pull-down resistor
                only one parameter can be selected which is shown as below:
      \arg        GPIO_PUPD_NONE: floating mode, no pull-up and pull-down resistors
      \arg        GPIO_PUPD_PULLUP: with pull-up resistor
      \arg        GPIO_PUPD_PULLDOWN:with pull-down resistor
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_mode_set(uint32_t gpio_periph, uint32_t mode, uint32_t pull_up_down, uint32_t pin)
{
    uint16_t i;
    uint32_t ctl, pupd;

    ctl = GPIO_CTL(gpio_periph);
    pupd = GPIO_PUD(gpio_periph);

    for(i = 0U;i < 16U;i++)
    {
        if((1U << i) & pin)
        {
            /* clear the specified pin mode bits */
            ctl &= ~GPIO_MODE_MASK(i);
            /* set the specified pin mode bits */
            ctl |= GPIO_MODE_SET(i, mode);

            /* clear the specified pin pupd bits */
            pupd &= ~GPIO_PUPD_MASK(i);
            /* set the specified pin pupd bits */
            pupd |= GPIO_PUPD_SET(i, pull_up_down);
        }
    }

    GPIO_CTL(gpio_periph) = ctl;
    GPIO_PUD(gpio_periph) = pupd;
}

/*!
    \brief      set GPIO output type and speed
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[in]  otype: gpio pin output mode
                only one parameter can be selected which is shown as below:
      \arg        GPIO_OTYPE_PP: push pull mode
      \arg        GPIO_OTYPE_OD: open drain mode
    \param[in]  speed: gpio pin output max speed
                only one parameter can be selected which is shown as below:
      \arg        GPIO_OSPEED_12MHZ: output max speed 12MHz
      \arg        GPIO_OSPEED_60MHZ: output max speed 60MHz
      \arg        GPIO_OSPEED_85MHZ: output max speed 85MHz
      \arg        GPIO_OSPEED_100_220MHZ: output max speed 100/220MHz
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_output_options_set(uint32_t gpio_periph, uint8_t otype, uint32_t speed, uint32_t pin)
{
    uint16_t i;
    uint32_t ospeed;

    if(GPIO_OTYPE_OD == otype)
    {
        GPIO_OMODE(gpio_periph) |= (uint32_t)pin;
    }else{
        GPIO_OMODE(gpio_periph) &= (uint32_t)(~pin);
    }

    /* get the specified pin output speed bits value */
    ospeed = GPIO_OSPD(gpio_periph);

    for(i = 0U;i < 16U;i++)
    {
        if((1U << i) & pin)
        {
            /* clear the specified pin output speed bits */
            ospeed &= ~GPIO_OSPEED_MASK(i);
            /* set the specified pin output speed bits */
            ospeed |= GPIO_OSPEED_SET(i,speed);
        }
    }
    GPIO_OSPD(gpio_periph) = ospeed;
}

/*!
    \brief      set GPIO pin bit
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_set(uint32_t gpio_periph, uint32_t pin)
{
    GPIO_BOP(gpio_periph) = (uint32_t)pin;
}

/*!
    \brief      reset GPIO pin bit
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,F)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_reset(uint32_t gpio_periph, uint32_t pin)
{
    GPIO_BC(gpio_periph) = (uint32_t)pin;
}

/*!
    \brief      write data to the specified GPIO pin
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
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
    if(RESET != bit_value)
    {
        GPIO_BOP(gpio_periph) = (uint32_t)pin;
    }else{
        GPIO_BC(gpio_periph) = (uint32_t)pin;
    }
}

/*!
    \brief      write data to the specified GPIO port
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[in]  data: specify the value to be written to the port output control register
    \param[out] none
    \retval     none
*/
void gpio_port_write(uint32_t gpio_periph, uint16_t data)
{
    GPIO_OCTL(gpio_periph) = (uint32_t)data;
}

/*!
    \brief      set GPIO input filter
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[in]  speriod: gpio pin input sample period
                only one parameter can be selected which is shown as below:
      \arg        GPIO_ISPERIOD(x): x = 0 ~ 255
    \param[in]  iftype: gpio pin input filtering type
                only one parameter can be selected which is shown as below:
      \arg        GPIO_IFTYPE_SYNC: input filter type synchronization
      \arg        GPIO_IFTYPE_3_SAMPLE: input filter type filter 3 samples
      \arg        GPIO_IFTYPE_6_SAMPLE: input filter type filter 6 samples
      \arg        GPIO_IFTYPE_ASYNC: input filter type asynchronous
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_input_filter_set(uint32_t gpio_periph, uint8_t speriod, uint32_t iftype, uint32_t pin)
{
    uint16_t i;
    uint32_t isperiod;
    uint32_t iftp;

    isperiod = GPIO_IFL(gpio_periph);
    if(pin & 0x000000FFU)
    {
        isperiod &= ~GPIO_IFL_FLPRD0;
        isperiod |= (uint32_t)speriod;
    }
    if(pin & 0x0000FF00U)
    {
        isperiod &= ~GPIO_IFL_FLPRD1;
        isperiod |= ((uint32_t)speriod << 8U);
    }
    GPIO_IFL(gpio_periph) = isperiod;

    /* get the specified pin output speed bits value */
    iftp = GPIO_IFTP(gpio_periph);
    for(i = 0U;i < 16U;i++)
    {
        if((1U << i) & pin)
        {
            /* clear the specified pin output speed bits */
            iftp &= ~GPIO_IFTYPE_MASK(i);
            /* set the specified pin output speed bits */
            iftp |= GPIO_IFTYPE_SET(i,iftype);
        }
    }
    GPIO_IFTP(gpio_periph) = iftp;
}

/*!
    \brief      get GPIO pin input status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus gpio_input_bit_get(uint32_t gpio_periph, uint32_t pin)
{
    if((uint32_t)RESET != (GPIO_ISTAT(gpio_periph)&(pin)))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      get GPIO port input status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[out] none
    \retval     state of GPIO all pins
*/
uint16_t gpio_input_port_get(uint32_t gpio_periph)
{
    return ((uint16_t)GPIO_ISTAT(gpio_periph));
}

/*!
    \brief      get GPIO pin output status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus gpio_output_bit_get(uint32_t gpio_periph, uint32_t pin)
{
    if((uint32_t)RESET != (GPIO_OCTL(gpio_periph)&(pin)))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      get GPIO port output status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[out] none
    \retval     state of GPIO all pins
*/
uint16_t gpio_output_port_get(uint32_t gpio_periph)
{
    return ((uint16_t)GPIO_OCTL(gpio_periph));
}

/*!
    \brief      set GPIO alternate function
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[in]  alt_func_num: GPIO pin af function, please refer to specific device datasheet
                only one parameter can be selected which is shown as below:
      \arg        GPIO_AF_0: SYSTEM, TIMER40, TIMER41, TIMER42, TIMER43, TIMER44
      \arg        GPIO_AF_1: TIMER0, TIMER1, TIMER15, TIMER16, EXMC, SAI1, SAI2
      \arg        GPIO_AF_2: TIMER2, TIMER3, TIMER4, TIMER7, TIMER14, TLI, CAN2, SAI0, EXMC
      \arg        GPIO_AF_3: TIMER7, TIMER9, EDOUT, EXMC, TLI, HPDF, OSPIM
      \arg        GPIO_AF_4: TIMER14, TIMER30, TIMER31, I2C0, I2C1, I2C2, I2C3, USART0, HPDF, OSPIM, TLI
      \arg        GPIO_AF_5: SPI0, SPI1, SPI2, SPI3, SPI4, SPI5, CAN2
      \arg        GPIO_AF_6: UART3, SPI2, I2C3, HPDF, SAI0, ETH1, EDOUT, OSPIM
      \arg        GPIO_AF_7: USART0, USART1, USART2, USART5, UART6, TIMER40, TIMER41, TIMER42, TIMER43,
                             SPI1, SPI2, SPI5, SDIO0, USBHS1
      \arg        GPIO_AF_8: UART3, UART4, UART7, SPI5, SDIO0, RSPDIF, TIMER44, USBHS1, SAI1, SAI2
      \arg        GPIO_AF_9: SDIO1, TRGSEL, CAN0, CAN1, TLI, OPSIM, EXMC, RSPDIF, SAI2
      \arg        GPIO_AF_10: SAI1, SAI2, OTG0, SDIO1, CMP, USBHS0, OPSIM, EXMC
      \arg        GPIO_AF_11: ETH0, MDIO, CMP, UART6, EXMC, HPDF, I2C3, TLI, SDIO1, OPSIM
      \arg        GPIO_AF_12: TIMER0, MDIOS, SDIO0, EXMC, OPSIM, CMP, TLI, USBHS1
      \arg        GPIO_AF_13: TRGSEL, DCI, COMP0, CMP, TIMER22
      \arg        GPIO_AF_14: TLI, UART4, TIMER23
      \arg        GPIO_AF_15: EVENTOUT
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_af_set(uint32_t gpio_periph, uint32_t alt_func_num, uint32_t pin)
{
    uint16_t i;
    uint32_t afrl, afrh;

    afrl = GPIO_AFSEL0(gpio_periph);
    afrh = GPIO_AFSEL1(gpio_periph);

    for(i = 0U;i < 8U;i++)
    {
        if((1U << i) & pin)
        {
            /* clear the specified pin alternate function bits */
            afrl &= ~GPIO_AFR_MASK(i);
            afrl |= GPIO_AFR_SET(i,alt_func_num);
        }
    }

    for(i = 8U;i < 16U;i++)
    {
        if((1U << i) & pin)
        {
            /* clear the specified pin alternate function bits */
            afrh &= ~GPIO_AFR_MASK(i - 8U);
            afrh |= GPIO_AFR_SET(i - 8U,alt_func_num);
        }
    }

    GPIO_AFSEL0(gpio_periph) = afrl;
    GPIO_AFSEL1(gpio_periph) = afrh;
}

/*!
    \brief      lock GPIO pin bit
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
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

    /* lock key writing sequence: write 1->write 0->write 1->read 0->read 1 */
    GPIO_LOCK(gpio_periph) = (uint32_t)lock;
    GPIO_LOCK(gpio_periph) = (uint32_t)pin;
    GPIO_LOCK(gpio_periph) = (uint32_t)lock;
    lock = GPIO_LOCK(gpio_periph);
    lock = GPIO_LOCK(gpio_periph);
}

/*!
    \brief      toggle GPIO pin status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_toggle(uint32_t gpio_periph, uint32_t pin)
{
    GPIO_TG(gpio_periph) = (uint32_t)pin;
}

/*!
    \brief      toggle GPIO port status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,J,K)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,H,J,K)
    \param[out] none
    \retval     none
*/
void gpio_port_toggle(uint32_t gpio_periph)
{
    GPIO_TG(gpio_periph) = 0x0000FFFFU;
}
