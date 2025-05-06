/*!
    \file    gd32e50x_gpio.c
    \brief   GPIO driver

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#include "gd32e50x_gpio.h"

#define AFIO_EXTI_SOURCE_MASK              ((uint8_t)0x03U)         /*!< AFIO exti source selection mask*/
#define AFIO_EXTI_SOURCE_FIELDS            ((uint8_t)0x04U)         /*!< select AFIO exti source registers */
#define LSB_16BIT_MASK                     ((uint16_t)0xFFFFU)      /*!< LSB 16-bit mask */
#define PCF_POSITION_MASK                  ((uint32_t)0x000F0000U)  /*!< AFIO_PCF register position mask */
#define PCF_SWJCFG_MASK                    ((uint32_t)0xF8FFFFFFU)  /*!< AFIO_PCF register SWJCFG mask */
#define PCF_LOCATION1_MASK                 ((uint32_t)0x00200000U)  /*!< AFIO_PCF register location1 mask */
#define PCF_LOCATION2_MASK                 ((uint32_t)0x00100000U)  /*!< AFIO_PCF register location2 mask */
#define AFIO_PCF1_FIELDS                   ((uint32_t)0x80000000U)  /*!< select AFIO_PCF1 register */
#define GPIO_OUTPUT_PORT_OFFSET            ((uint32_t)4U)           /*!< GPIO event output port offset*/

/*!
    \brief      reset GPIO port
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G)
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
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G)
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
      \arg        GPIO_OSPEED_MAX: output max speed more than 50MHz
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_init(uint32_t gpio_periph, uint32_t mode, uint32_t speed, uint32_t pin)
{
    uint16_t i;
    uint32_t temp_mode = 0U;
    uint32_t reg = 0U;

    /* GPIO mode configuration */
    temp_mode = (uint32_t)(mode & ((uint32_t)0x0FU));

    /* GPIO speed configuration */
    if(((uint32_t)0x00U) != ((uint32_t)mode & ((uint32_t)0x10U)))
    {
        /* output mode max speed */
        if(GPIO_OSPEED_MAX == (uint32_t)speed)
        {
            temp_mode |= (uint32_t)0x03U;
            /* set the corresponding SPD bit */
            GPIOx_SPD(gpio_periph) |= (uint32_t)pin ;
        }else{
            /* output mode max speed:10MHz,2MHz,50MHz */
            temp_mode |= (uint32_t)speed;
        }
    }

    /* configure the eight low port pins with GPIO_CTL0 */
    for(i = 0U;i < 8U;i++)
    {
        if((1U << i) & pin)
        {
            reg = GPIO_CTL0(gpio_periph);

            /* clear the specified pin mode bits */
            reg &= ~GPIO_MODE_MASK(i);
            /* set the specified pin mode bits */
            reg |= GPIO_MODE_SET(i, temp_mode);

            /* set IPD or IPU */
            if(GPIO_MODE_IPD == mode)
            {
                /* reset the corresponding OCTL bit */
                GPIO_BC(gpio_periph) = (uint32_t)((1U << i) & pin);
            }else{
                /* set the corresponding OCTL bit */
                if(GPIO_MODE_IPU == mode)
                {
                    GPIO_BOP(gpio_periph) = (uint32_t)((1U << i) & pin);
                }
            }
            /* set GPIO_CTL0 register */
            GPIO_CTL0(gpio_periph) = reg;
        }
    }
    /* configure the eight high port pins with GPIO_CTL1 */
    for(i = 8U;i < 16U;i++)
    {
        if((1U << i) & pin)
        {
            reg = GPIO_CTL1(gpio_periph);

            /* clear the specified pin mode bits */
            reg &= ~GPIO_MODE_MASK(i - 8U);
            /* set the specified pin mode bits */
            reg |= GPIO_MODE_SET(i - 8U, temp_mode);

            /* set IPD or IPU */
            if(GPIO_MODE_IPD == mode)
            {
                /* reset the corresponding OCTL bit */
                GPIO_BC(gpio_periph) = (uint32_t)((1U << i) & pin);
            }else{
                /* set the corresponding OCTL bit */
                if(GPIO_MODE_IPU == mode)
                {
                    GPIO_BOP(gpio_periph) = (uint32_t)((1U << i) & pin);
                }
            }
            /* set GPIO_CTL1 register */
            GPIO_CTL1(gpio_periph) = reg;
        }
    }
}

/*!
    \brief      set GPIO pin bit
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_set(uint32_t gpio_periph,uint32_t pin)
{
    GPIO_BOP(gpio_periph) = (uint32_t)pin;
}

/*!
    \brief      reset GPIO pin bit
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_reset(uint32_t gpio_periph,uint32_t pin)
{
    GPIO_BC(gpio_periph) = (uint32_t)pin;
}

/*!
    \brief      write data to the specified GPIO pin
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[in]  bit_value: SET or RESET
      \arg        RESET: clear the port pin
      \arg        SET: set the port pin
    \param[out] none
    \retval     none
*/
void gpio_bit_write(uint32_t gpio_periph,uint32_t pin,bit_status bit_value)
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
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G)
    \param[in]  data: specify the value to be written to the port output data register
    \param[out] none
    \retval     none
*/
void gpio_port_write(uint32_t gpio_periph,uint16_t data)
{
    GPIO_OCTL(gpio_periph) = (uint32_t)data;
}

/*!
    \brief      get GPIO pin input status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G)
    \param[in]  pin: GPIO pin
                only one parameter can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     input status of gpio pin: SET or RESET
*/
FlagStatus gpio_input_bit_get(uint32_t gpio_periph,uint32_t pin)
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
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G)
    \param[out] none
    \retval     input status of gpio all pins
*/
uint16_t gpio_input_port_get(uint32_t gpio_periph)
{
    return (uint16_t)(GPIO_ISTAT(gpio_periph));
}

/*!
    \brief      get GPIO pin output status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G)
    \param[in]  pin: GPIO pin
                only one parameter can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     output status of gpio pin: SET or RESET
*/
FlagStatus gpio_output_bit_get(uint32_t gpio_periph,uint32_t pin)
{
    if((uint32_t)RESET !=(GPIO_OCTL(gpio_periph)&(pin)))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      get GPIO port output status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G)
    \param[out] none
    \retval     output status of gpio all pins
*/
uint16_t gpio_output_port_get(uint32_t gpio_periph)
{
    return ((uint16_t)GPIO_OCTL(gpio_periph));
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
      \arg        GPIO_CAN0_PARTIAL_REMAP: CAN0 partial remapping(not support on GD32EPRT devices)
      \arg        GPIO_CAN0_FULL_REMAP: CAN0 full remapping(not support on GD32EPRT devices)
      \arg        GPIO_PD01_REMAP: PD01 remapping
      \arg        GPIO_TIMER4CH3_IREMAP: TIMER4 channel3 internal remapping
      \arg        GPIO_ADC0_ETRGRT_REMAP: ADC0 external trigger routine conversion remapping(only for GD32E50X_HD devices)
      \arg        GPIO_ADC1_ETRGRT_REMAP: ADC1 external trigger routine conversion remapping(only for GD32E50X_HD devices)
      \arg        GPIO_ENET_REMAP: ENET remapping(only for GD32E50X_CL and GD32E508 devices)
      \arg        GPIO_CAN1_REMAP: CAN1 remapping(not support on GD32EPRT devices)
      \arg        GPIO_SWJ_NONJTRST_REMAP: full SWJ(JTAG-DP + SW-DP),but without NJTRST
      \arg        GPIO_SWJ_SWDPENABLE_REMAP: JTAG-DP disabled and SW-DP enabled
      \arg        GPIO_SWJ_DISABLE_REMAP: JTAG-DP disabled and SW-DP disabled
      \arg        GPIO_SPI2_REMAP: SPI2 remapping
      \arg        GPIO_TIMER1ITR1_REMAP: TIMER1 internal trigger 1 remapping(only for GD32E50X_CL and GD32E508 devices)
      \arg        GPIO_PTP_PPS_REMAP: ethernet PTP PPS remapping(only for GD32E50X_CL and GD32E508 devices)
      \arg        GPIO_TIMER8_REMAP: TIMER8 remapping(not support on GD32EPRT devices)
      \arg        GPIO_TIMER9_REMAP: TIMER9 remapping(not support on GD32EPRT devices)
      \arg        GPIO_TIMER10_REMAP: TIMER10 remapping(not support on GD32EPRT devices)
      \arg        GPIO_TIMER12_REMAP: TIMER12 remapping(not support on GD32EPRT devices)
      \arg        GPIO_TIMER13_REMAP: TIMER13 remapping(not support on GD32EPRT devices)
      \arg        GPIO_EXMC_NADV_REMAP: EXMC_NADV connect/disconnect
      \arg        GPIO_CTC_REMAP0: CTC remapping(PD15)
      \arg        GPIO_CTC_REMAP1: CTC remapping(PF0)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void gpio_pin_remap_config(uint32_t remap, ControlStatus newvalue)
{
    uint32_t remap1 = 0U, remap2 = 0U, temp_reg = 0U, temp_mask = 0U;

    if(((uint32_t)0x80000000U) == (remap & 0x80000000U))
    {
        /* get AFIO_PCF1 regiter value */
        temp_reg = AFIO_PCF1;
    }else{
        /* get AFIO_PCF0 regiter value */
        temp_reg = AFIO_PCF0;
    }

    temp_mask = (remap & PCF_POSITION_MASK) >> 0x10U;
    remap1 = remap & LSB_16BIT_MASK;

    /* judge pin remap type */
    if((PCF_LOCATION1_MASK | PCF_LOCATION2_MASK) == (remap & (PCF_LOCATION1_MASK | PCF_LOCATION2_MASK)))
    {
        temp_reg &= PCF_SWJCFG_MASK;
        AFIO_PCF0 &= PCF_SWJCFG_MASK;
    }else if(PCF_LOCATION2_MASK == (remap & PCF_LOCATION2_MASK))
    {
        remap2 = ((uint32_t)0x03U) << temp_mask;
        temp_reg &= ~remap2;
        temp_reg |= ~PCF_SWJCFG_MASK;
    }else{
        temp_reg &= ~(remap1 << ((remap >> 0x15U)*0x10U));
        temp_reg |= ~PCF_SWJCFG_MASK;
    }

    /* set pin remap value */
    if(DISABLE != newvalue)
    {
        temp_reg |= (remap1 << ((remap >> 0x15U)*0x10U));
    }

    if(AFIO_PCF1_FIELDS == (remap & AFIO_PCF1_FIELDS))
    {
        /* set AFIO_PCF1 regiter value */
        AFIO_PCF1 = temp_reg;
    }else{
        /* set AFIO_PCF0 regiter value */
        AFIO_PCF0 = temp_reg;
    }
}

/*!
    \brief      configure AFIO port alternate function
    \param[in]  afio_function: select the port AFIO function(SHRTIMER not support on GD32EPRT devices)
                only one parameter can be selected which are shown as below:
      \arg        AFIO_PA2_CMP1_CFG: configure PA2 alternate function to CMP1
      \arg        AFIO_PA3_USBHS_CFG: configure PA3 alternate function to USBHS
      \arg        AFIO_PA5_USBHS_CFG: configure PA5 alternate function to USBHS
      \arg        AFIO_PA8_I2C2_CFG: configure PA8 alternate function to I2C2
      \arg        AFIO_PA8_SHRTIMER_CFG: configure PA8 alternate function to SHRTIMER
      \arg        AFIO_PA9_CAN2_CFG: configure PA9 alternate function to CAN2(not support on GD32EPRT devices)
      \arg        AFIO_PA9_I2C2_CFG: configure PA9 alternate function to I2C2
      \arg        AFIO_PA9_SHRTIMER_CFG: configure PA9 alternate function to SHRTIMER
      \arg        AFIO_PA10_CAN2_CFG: configure PA10 alternate function to CAN2(not support on GD32EPRT devices)
      \arg        AFIO_PA10_CMP5_CFG: configure PA10 alternate function to CMP5
      \arg        AFIO_PA10_SHRTIMER_CFG: configure PA10 alternate function to SHRTIMER
      \arg        AFIO_PA11_USART5_CFG: configure PA11 alternate function to USART5
      \arg        AFIO_PA11_SHRTIMER_CFG: configure PA11 alternate function to SHRTIMER
      \arg        AFIO_PA12_CMP1_CFG: configure PA12 alternate function to CMP1
      \arg        AFIO_PA12_USART5_CFG: configure PA12 alternate function to USART5
      \arg        AFIO_PA12_SHRTIMER_CFG: configure PA12 alternate function to SHRTIMER
      \arg        AFIO_PA15_SHRTIMER_CFG: configure PA15 alternate function to SHRTIMER
      \arg        AFIO_PB0_USBHS_CFG: configure PB0 alternate function to USBHS
      \arg        AFIO_PB1_CMP3_CFG: configure PB1 alternate function to CMP3
      \arg        AFIO_PB1_USBHS_CFG: configure PB1 alternate function to USBHS
      \arg        AFIO_PB1_SHRTIMER_CFG: configure PB1 alternate function to SHRTIMER
      \arg        AFIO_PB2_USBHS_CFG: configure PB2 alternate function to USBHS
      \arg        AFIO_PB2_SHRTIMER_CFG: configure PB2 alternate function to SHRTIMER
      \arg        AFIO_PB3_SHRTIMER_CFG: configure PB3 alternate function to SHRTIMER
      \arg        AFIO_PB4_I2S2_CFG: configure PB4 alternate function to I2S2
      \arg        AFIO_PB4_I2C2_CFG: configure PB4 alternate function to I2C2
      \arg        AFIO_PB4_SHRTIMER_CFG: configure PB4 alternate function to SHRTIMER
      \arg        AFIO_PB5_I2C2_CFG: configure PB5 alternate function to I2C2
      \arg        AFIO_PB5_USBHS_CFG: configure PB5 alternate function to USBHS
      \arg        AFIO_PB5_SHRTIMER_CFG: configure PB5 alternate function to SHRTIMER
      \arg        AFIO_PB6_SHRTIMER_CFG: configure PB6 alternate function to SHRTIMER
      \arg        AFIO_PB7_SHRTIMER_CFG: configure PB7 alternate function to SHRTIMER
      \arg        AFIO_PB8_I2C2_CFG: configure PB8 alternate function to I2C2
      \arg        AFIO_PB8_SHRTIMER_CFG: configure PB8 alternate function to SHRTIMER
      \arg        AFIO_PB9_CMP1_CFG: configure PB9 alternate function to CMP1
      \arg        AFIO_PB9_SHRTIMER_CFG: configure PB9 alternate function to SHRTIMER
      \arg        AFIO_PB10_CAN2_CFG: configure PB10 alternate function to CAN2(not support on GD32EPRT devices)
      \arg        AFIO_PB10_USBHS_CFG: configure PB10 alternate function to USBHS
      \arg        AFIO_PB10_SHRTIMER_CFG: configure PB10 alternate function to SHRTIMER
      \arg        AFIO_PB11_CAN2_CFG: configure PB11 alternate function to CAN2(not support on GD32EPRT devices)
      \arg        AFIO_PB11_USBHS_CFG: configure PB11 alternate function to USBHS
      \arg        AFIO_PB11_SHRTIMER_CFG: configure PB11 alternate function to SHRTIMER
      \arg        AFIO_PB12_USBHS_CFG: configure PB12 alternate function to USBHS
      \arg        AFIO_PB12_SHRTIMER_CFG: configure PB12 alternate function to SHRTIMER
      \arg        AFIO_PB13_USBHS_CFG: configure PB13 alternate function to USBHS
      \arg        AFIO_PB13_SHRTIMER_CFG: configure PB13 alternate function to SHRTIMER
      \arg        AFIO_PB14_I2S1_CFG: configure PB14 alternate function to I2S1
      \arg        AFIO_PB14_SHRTIMER_CFG: configure PB14 alternate function to SHRTIMER
      \arg        AFIO_PB15_SHRTIMER_CFG: configure PB15 alternate function to SHRTIMER
      \arg        AFIO_PC0_USBHS_CFG: configure PC0 alternate function to USBHS
      \arg        AFIO_PC2_I2S1_CFG: configure PC2 alternate function to I2S1
      \arg        AFIO_PC2_USBHS_CFG: configure PC2 alternate function to USBHS
      \arg        AFIO_PC3_USBHS_CFG: configure PC3 alternate function to USBHS
      \arg        AFIO_PC6_CMP5_CFG: configure PC6 alternate function to CMP5
      \arg        AFIO_PC6_USART5_CFG: configure PC6 alternate function to USART5
      \arg        AFIO_PC6_SHRTIMER_CFG: configure PC6 alternate function to SHRTIMER
      \arg        AFIO_PC7_USART5_CFG: configure PC7 alternate function to USART5
      \arg        AFIO_PC7_SHRTIMER_CFG: configure PC7 alternate function to SHRTIMER
      \arg        AFIO_PC8_USART5_CFG: configure PC8 alternate function to USART5
      \arg        AFIO_PC8_SHRTIMER_CFG: configure PC8 alternate function to SHRTIMER
      \arg        AFIO_PC9_I2C2_CFG: configure PC9 alternate function to I2C2
      \arg        AFIO_PC9_SHRTIMER_CFG: configure PC9 alternate function to SHRTIMER
      \arg        AFIO_PC10_I2C2_CFG: configure PC10 alternate function to I2C2
      \arg        AFIO_PC11_I2S2_CFG: configure PC11 alternate function to I2S2
      \arg        AFIO_PC11_SHRTIMER_CFG: configure PC11 alternate function to SHRTIMER
      \arg        AFIO_PC12_SHRTIMER_CFG: configure PC12 alternate function to SHRTIMER
      \arg        AFIO_PD4_SHRTIMER_CFG: configure PD4 alternate function to SHRTIMER
      \arg        AFIO_PD5_SHRTIMER_CFG: configure PD5 alternate function to SHRTIMER
      \arg        AFIO_PE0_CAN2_CFG: configure PE0 alternate function to CAN2(not support on GD32EPRT devices)
      \arg        AFIO_PE0_SHRTIMER_CFG: configure PE0 alternate function to SHRTIMER
      \arg        AFIO_PE1_CAN2_CFG: configure PE1 alternate function to CAN2(not support on GD32EPRT devices)
      \arg        AFIO_PE1_SHRTIMER_CFG: configure PE1 alternate function to SHRTIMER
      \arg        AFIO_PE8_CMP1_CFG: configure PE8 alternate function to CMP1
      \arg        AFIO_PE9_CMP3_CFG: configure PE9 alternate function to CMP3
      \arg        AFIO_PE10_CMP5_CFG: configure PE10 alternate function to CMP5
      \arg        AFIO_PE11_CMP5_CFG: configure PE11 alternate function to CMP5
      \arg        AFIO_PE12_CMP3_CFG: configure PE12 alternate function to CMP3
      \arg        AFIO_PE13_CMP1_CFG: configure PE13 alternate function to CMP1
      \arg        AFIO_PG6_SHRTIMER_CFG: configure PG6 alternate function to SHRTIMER
      \arg        AFIO_PG7_USART5_CFG: configure PG7 alternate function to USART5
      \arg        AFIO_PG7_SHRTIMER_CFG: configure PG7 alternate function to SHRTIMER
      \arg        AFIO_PG9_USART5_CFG: configure PG9 alternate function to USART5
      \arg        AFIO_PG10_SHRTIMER_CFG: configure PG10 alternate function to SHRTIMER
      \arg        AFIO_PG11_SHRTIMER_CFG: configure PG11 alternate function to SHRTIMER
      \arg        AFIO_PG12_SHRTIMER_CFG: configure PG12 alternate function to SHRTIMER
      \arg        AFIO_PG13_SHRTIMER_CFG: configure PG13 alternate function to SHRTIMER
      \arg        AFIO_PG14_USART5_CFG: configure PG14 alternate function to USART5
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void gpio_afio_port_config(uint32_t afio_function, ControlStatus newvalue)
{
    uint32_t remap1 = 0U, remap2 = 0U, temp_reg = 0U, temp_mask = 0U;

    /* get AFIO_PCFx(x=A,B,C,D,E,G) regiter value */
    temp_reg = REG32(AFIO+0x0000003CU+((afio_function>>24)<<2));

    temp_mask = (afio_function & PCF_POSITION_MASK) >> 0x10U;
    remap1 = afio_function & LSB_16BIT_MASK;

    /* judge port function select type */
    if(afio_function & PCF_LOCATION2_MASK)
    {
        remap2 = ((uint32_t)0x03U) << temp_mask;
        remap2 = (remap2 << (((afio_function & PCF_LOCATION1_MASK) >> 0x15U)*0x10U));
        temp_reg &= ~remap2;
    }else{
        temp_reg &= ~(remap1 << (((afio_function & PCF_LOCATION1_MASK) >> 0x15U)*0x10U));
    }

    /* set pin remap value */
    if(DISABLE != newvalue)
    {
        temp_reg |= (remap1 << (((afio_function & PCF_LOCATION1_MASK) >> 0x15U)*0x10U));
    }

    /* set AFIO_PCFx(x=A,B,C,D,E,G) regiter value */
    REG32(AFIO+0x0000003CU+((afio_function>>24)<<2)) = temp_reg;
}

#if (defined(GD32E50X_CL) || defined(GD32E508) || defined(GD32EPRT))
/*!
    \brief      select ethernet MII or RMII PHY
    \param[in]  enet_sel: ethernet MII or RMII PHY selection
      \arg        GPIO_ENET_PHY_MII: configure ethernet MAC for connection with an MII PHY
      \arg        GPIO_ENET_PHY_RMII: configure ethernet MAC for connection with an RMII PHY
    \param[out] none
    \retval     none
*/
void gpio_ethernet_phy_select(uint32_t enet_sel)
{
    /* clear AFIO_PCF0_ENET_PHY_SEL bit */
    AFIO_PCF0 &= (uint32_t)(~AFIO_PCF0_ENET_PHY_SEL);

    /* select MII or RMII PHY */
    AFIO_PCF0 |= (uint32_t)enet_sel;
}
#endif /* GD32E50X_CL||GD32E508||GD32EPRT */

/*!
    \brief      select GPIO pin exti sources
    \param[in]  output_port: gpio event output port
                only one parameter can be selected which are shown as below:
      \arg        GPIO_PORT_SOURCE_GPIOA: output port source A
      \arg        GPIO_PORT_SOURCE_GPIOB: output port source B
      \arg        GPIO_PORT_SOURCE_GPIOC: output port source C
      \arg        GPIO_PORT_SOURCE_GPIOD: output port source D
      \arg        GPIO_PORT_SOURCE_GPIOE: output port source E
      \arg        GPIO_PORT_SOURCE_GPIOF: output port source F
      \arg        GPIO_PORT_SOURCE_GPIOG: output port source G
    \param[in]  output_pin: GPIO output pin source
                only one parameter can be selected which are shown as below:
      \arg        GPIO_PIN_SOURCE_x(x=0..15)
    \param[out] none
    \retval     none
*/
void gpio_exti_source_select(uint8_t output_port, uint8_t output_pin)
{
    uint32_t source = 0U;
    source = ((uint32_t)0x0FU) << (AFIO_EXTI_SOURCE_FIELDS * (output_pin & AFIO_EXTI_SOURCE_MASK));

    /* select EXTI sources */
    if(GPIO_PIN_SOURCE_4 > output_pin)
    {
        /* select EXTI0/EXTI1/EXTI2/EXTI3 */
        AFIO_EXTISS0 &= ~source;
        AFIO_EXTISS0 |= (((uint32_t)output_port) << (AFIO_EXTI_SOURCE_FIELDS * (output_pin & AFIO_EXTI_SOURCE_MASK)));
    }else if(GPIO_PIN_SOURCE_8 > output_pin)
    {
        /* select EXTI4/EXTI5/EXTI6/EXTI7 */
        AFIO_EXTISS1 &= ~source;
        AFIO_EXTISS1 |= (((uint32_t)output_port) << (AFIO_EXTI_SOURCE_FIELDS * (output_pin & AFIO_EXTI_SOURCE_MASK)));
    }else if(GPIO_PIN_SOURCE_12 > output_pin)
    {
        /* select EXTI8/EXTI9/EXTI10/EXTI11 */
        AFIO_EXTISS2 &= ~source;
        AFIO_EXTISS2 |= (((uint32_t)output_port) << (AFIO_EXTI_SOURCE_FIELDS * (output_pin & AFIO_EXTI_SOURCE_MASK)));
    }else{
        /* select EXTI12/EXTI13/EXTI14/EXTI15 */
        AFIO_EXTISS3 &= ~source;
        AFIO_EXTISS3 |= (((uint32_t)output_port) << (AFIO_EXTI_SOURCE_FIELDS * (output_pin & AFIO_EXTI_SOURCE_MASK)));
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
    \param[in]  output_pin: GPIO event output pin
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
    reg &= (uint32_t)(~(AFIO_EC_PORT|AFIO_EC_PIN));

    reg |= (uint32_t)((uint32_t)output_port << GPIO_OUTPUT_PORT_OFFSET);
    reg |= (uint32_t)output_pin;

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
    AFIO_EC &= (uint32_t)(~AFIO_EC_EOE);
}

/*!
    \brief      lock GPIO pin bit
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_pin_lock(uint32_t gpio_periph,uint32_t pin)
{
    uint32_t lock = 0x00010000U;
    lock |= pin;

    /* lock key writing sequence: write 1 -> write 0 -> write 1 -> read 0 -> read 1 */
    GPIO_LOCK(gpio_periph) = (uint32_t)lock;
    GPIO_LOCK(gpio_periph) = (uint32_t)pin;
    GPIO_LOCK(gpio_periph) = (uint32_t)lock;
    lock = GPIO_LOCK(gpio_periph);
    lock = GPIO_LOCK(gpio_periph);
}

/*!
    \brief      configure the I/O compensation cell
    \param[in]  compensation: specifies the I/O compensation cell mode
                only one parameter can be selected which are shown as below:
      \arg        GPIO_COMPENSATION_ENABLE: I/O compensation cell is enabled
      \arg        GPIO_COMPENSATION_DISABLE: I/O compensation cell is disabled
    \param[out] none
    \retval     none
*/
void gpio_compensation_config(uint32_t compensation)
{
    uint32_t reg;
    reg = AFIO_CPSCTL;

    /* reset the AFIO_CPSCTL_CPS_EN bit and set according to gpio_compensation */
    reg &= ~AFIO_CPSCTL_CPS_EN;
    AFIO_CPSCTL = (reg | compensation);
}

/*!
    \brief      check the I/O compensation cell is ready or not
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
  */
FlagStatus gpio_compensation_flag_get(void)
{
    if(((uint32_t)RESET) != (AFIO_CPSCTL & AFIO_CPSCTL_CPS_RDY))
    {
        return SET;
    }else{
        return RESET;
    }
}
