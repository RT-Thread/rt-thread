/*!
    \file    gd32f20x_gpio.c
    \brief   GPIO driver

    \version 2015-07-15, V1.0.0, firmware for GD32F20x
    \version 2017-06-05, V2.0.0, firmware for GD32F20x
    \version 2018-10-31, V2.1.0, firmware for GD32F20x
    \version 2020-09-30, V2.2.0, firmware for GD32F20x
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

#include "gd32f20x_gpio.h"

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
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,I)
    \param[out] none
    \retval     none
*/
void gpio_deinit(uint32_t gpio_periph)
{
    switch(gpio_periph){
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
    case GPIOI:
        /* reset GPIOI */
        rcu_periph_reset_enable(RCU_GPIOIRST);
        rcu_periph_reset_disable(RCU_GPIOIRST);
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
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,I)
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
void gpio_init(uint32_t gpio_periph, uint32_t mode, uint32_t speed, uint32_t pin)
{
    uint16_t i;
    uint32_t temp_mode = 0U;
    uint32_t reg = 0U;

    /* GPIO mode configuration */
    temp_mode = (uint32_t)(mode & ((uint32_t)0x0FU));

    /* GPIO speed configuration */
    if(((uint32_t)0x00U) != ((uint32_t)mode & ((uint32_t)0x10U))){
        /* output mode max speed:10MHz,2MHz,50MHz */
        temp_mode |= (uint32_t)speed;
    }

    /* configure the eight low port pins with GPIO_CTL0 */
    for(i = 0U;i < 8U;i++){
        if((1U << i) & pin){
            reg = GPIO_CTL0(gpio_periph);

            /* clear the specified pin mode bits */
            reg &= ~GPIO_MODE_MASK(i);
            /* set the specified pin mode bits */
            reg |= GPIO_MODE_SET(i, temp_mode);

            /* set IPD or IPU */
            if(GPIO_MODE_IPD == mode){
                /* reset the corresponding OCTL bit */
                GPIO_BC(gpio_periph) = (uint32_t)((1U << i) & pin);
            }else{
                /* set the corresponding OCTL bit */
                if(GPIO_MODE_IPU == mode){
                    GPIO_BOP(gpio_periph) = (uint32_t)((1U << i) & pin);
                }
            }
            /* set GPIO_CTL0 register */
            GPIO_CTL0(gpio_periph) = reg;
        }
    }
    /* configure the eight high port pins with GPIO_CTL1 */
    for(i = 8U;i < 16U;i++){
        if((1U << i) & pin){
            reg = GPIO_CTL1(gpio_periph);

            /* clear the specified pin mode bits */
            reg &= ~GPIO_MODE_MASK(i - 8U);
            /* set the specified pin mode bits */
            reg |= GPIO_MODE_SET(i - 8U, temp_mode);

            /* set IPD or IPU */
            if(GPIO_MODE_IPD == mode){
                /* reset the corresponding OCTL bit */
                GPIO_BC(gpio_periph) = (uint32_t)((1U << i) & pin);
            }else{
                /* set the corresponding OCTL bit */
                if(GPIO_MODE_IPU == mode){
                    GPIO_BOP(gpio_periph) = (uint32_t)((1U << i) & pin);
                }
            }
            /* set GPIO_CTL1 register */
            GPIO_CTL1(gpio_periph) = reg;
        }
    }
}

/*!
    \brief      set GPIO pin
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,I)
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
    \brief      reset GPIO pin
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,I)
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
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,I)
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
    if(RESET != bit_value){
        GPIO_BOP(gpio_periph) = (uint32_t)pin;
    }else{
        GPIO_BC(gpio_periph) = (uint32_t)pin;
    }
}

/*!
    \brief      write data to the specified GPIO port
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,I)
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
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,I)
    \param[in]  pin: GPIO pin
                only one parameter can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     input status of gpio pin: SET or RESET
*/
FlagStatus gpio_input_bit_get(uint32_t gpio_periph,uint32_t pin)
{
    if((uint32_t)RESET != (GPIO_ISTAT(gpio_periph)&(pin))){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      get GPIO port input status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,I)
    \param[out] none
    \retval     input status of gpio all pins
*/
uint16_t gpio_input_port_get(uint32_t gpio_periph)
{
    return (uint16_t)(GPIO_ISTAT(gpio_periph));
}

/*!
    \brief      get GPIO pin output status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,I)
    \param[in]  pin: GPIO pin
                only one parameter can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     output status of gpio pin: SET or RESET
*/
FlagStatus gpio_output_bit_get(uint32_t gpio_periph,uint32_t pin)
{
    if((uint32_t)RESET !=(GPIO_OCTL(gpio_periph)&(pin))){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      get GPIO port output status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,I)
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
      \arg        GPIO_ADC0_ETRGINS_REMAP: ADC0 external trigger inserted conversion remapping
      \arg        GPIO_ADC0_ETRGREG_REMAP: ADC0 external trigger regular conversion remapping
      \arg        GPIO_ADC1_ETRGINS_REMAP: ADC1 external trigger inserted conversion remapping
      \arg        GPIO_ADC1_ETRGREG_REMAP: ADC1 external trigger regular conversion remapping
      \arg        GPIO_ENET_REMAP: ENET remapping
      \arg        GPIO_CAN1_REMAP: CAN1 remapping
      \arg        GPIO_SWJ_NONJTRST_REMAP: full SWJ(JTAG-DP + SW-DP),but without NJTRST
      \arg        GPIO_SWJ_SWDPENABLE_REMAP: JTAG-DP disabled and SW-DP enabled
      \arg        GPIO_SWJ_DISABLE_REMAP: JTAG-DP disabled and SW-DP disabled
      \arg        GPIO_SPI2_REMAP: SPI2 remapping
      \arg        GPIO_TIMER1ITI1_REMAP: TIMER1 internal trigger 1 remapping
      \arg        GPIO_PTP_PPS_REMAP: ethernet PTP PPS remapping
      \arg        GPIO_TIMER8_REMAP: TIMER8 remapping
      \arg        GPIO_TIMER9_REMAP: TIMER9 remapping
      \arg        GPIO_TIMER10_REMAP: TIMER10 remapping
      \arg        GPIO_TIMER12_REMAP: TIMER12 remapping
      \arg        GPIO_TIMER13_REMAP: TIMER13 remapping
      \arg        GPIO_EXMC_NADV_REMAP: EXMC_NADV connect/disconnect
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void gpio_pin_remap_config(uint32_t gpio_remap, ControlStatus newvalue)
{
    uint32_t remap1 = 0U, remap2 = 0U, temp_reg = 0U, temp_mask = 0U;

    if(AFIO_PCF1_FIELDS == (gpio_remap & AFIO_PCF1_FIELDS)){
        /* get AFIO_PCF1 regiter value */
        temp_reg = AFIO_PCF1;
    }else{
        /* get AFIO_PCF0 regiter value */
        temp_reg = AFIO_PCF0;
    }

    temp_mask = (gpio_remap & PCF_POSITION_MASK) >> 0x10U;
    remap1 = gpio_remap & LSB_16BIT_MASK;

    /* judge pin remap type */
    if((PCF_LOCATION1_MASK | PCF_LOCATION2_MASK) == (gpio_remap & (PCF_LOCATION1_MASK | PCF_LOCATION2_MASK))){
        temp_reg &= PCF_SWJCFG_MASK;
        AFIO_PCF0 &= PCF_SWJCFG_MASK;
    }else if(PCF_LOCATION2_MASK == (gpio_remap & PCF_LOCATION2_MASK)){
        remap2 = ((uint32_t)0x03U) << temp_mask;
        temp_reg &= ~remap2;
        temp_reg |= ~PCF_SWJCFG_MASK;
    }else{
        temp_reg &= ~(remap1 << ((gpio_remap >> 0x15U)*0x10U));
        temp_reg |= ~PCF_SWJCFG_MASK;
    }

    /* set pin remap value */
    if(DISABLE != newvalue){
        temp_reg |= (remap1 << ((gpio_remap >> 0x15U)*0x10U));
    }

    if(AFIO_PCF1_FIELDS == (gpio_remap & AFIO_PCF1_FIELDS)){
        /* set AFIO_PCF1 regiter value */
        AFIO_PCF1 = temp_reg;
    }else{
        /* set AFIO_PCF0 regiter value */
        AFIO_PCF0 = temp_reg;
    }
}

/*!
    \brief      configure GPIO pin remap1
    \param[in]  remap_reg:
      \arg        GPIO_PCF2: AFIO port configuration register 2
      \arg        GPIO_PCF3: AFIO port configuration register 3
      \arg        GPIO_PCF4: AFIO port configuration register 4
      \arg        GPIO_PCF5: AFIO port configuration register 5
    \param[in]  remap: select the pin to remap
      \arg        GPIO_PCF2_DCI_VSYNC_PG9_REMAP: DCI VSYNC remapped to PG9
      \arg        GPIO_PCF2_DCI_VSYNC_PI5_REMAP: DCI VSYNC remapped to PI5
      \arg        GPIO_PCF2_DCI_D0_PC6_REMAP: DCI D0 remapped to PC6
      \arg        GPIO_PCF2_DCI_D0_PH9_REMAP: DCI D0 remapped to PH9
      \arg        GPIO_PCF2_DCI_D1_PC7_REMAP: DCI D1 remapped to PC7
      \arg        GPIO_PCF2_DCI_D1_PH10_REMAP: DCI D1 remapped to PH10
      \arg        GPIO_PCF2_DCI_D2_PE0_REMAP: DCI D2 remapped to PE0
      \arg        GPIO_PCF2_DCI_D2_PG10_REMAP: DCI D2 remapped to PG10
      \arg        GPIO_PCF2_DCI_D2_PH11_REMAP: DCI D2 remapped to PH11
      \arg        GPIO_PCF2_DCI_D3_PE1_REMAP: DCI D3 remapped to PE1
      \arg        GPIO_PCF2_DCI_D3_PG11_REMAP: DCI D3 remapped to PG11
      \arg        GPIO_PCF2_DCI_D3_PH12_REMAP: DCI D3 remapped to PH12
      \arg        GPIO_PCF2_DCI_D4_PE4_REMAP: DCI D4 remapped to PE4
      \arg        GPIO_PCF2_DCI_D4_PH14_REMAP: DCI D4 remapped to PH14
      \arg        GPIO_PCF2_DCI_D5_PD3_REMAP: DCI D5 remapped to PD3
      \arg        GPIO_PCF2_DCI_D5_PI4_REMAP: DCI D5 remapped to PI4
      \arg        GPIO_PCF2_DCI_D6_PE5_REMAP: DCI D6 remapped to PE5
      \arg        GPIO_PCF2_DCI_D6_PI6_REMAP: DCI D6 remapped to PI6
      \arg        GPIO_PCF2_DCI_D7_PE6_REMAP: DCI D7 remapped to PE6
      \arg        GPIO_PCF2_DCI_D7_PI7_REMAP: DCI D7 remapped to PI7
      \arg        GPIO_PCF2_DCI_D8_PH6_REMAP: DCI D8 remapped to PH6
      \arg        GPIO_PCF2_DCI_D8_PI1_REMAP: DCI D8 remapped to PI1
      \arg        GPIO_PCF2_DCI_D9_PH7_REMAP: DCI D9 remapped to PH7
      \arg        GPIO_PCF2_DCI_D9_PI2_REMAP: DCI D9 remapped to PI2
      \arg        GPIO_PCF2_DCI_D10_PD6_REMAP: DCI D10 remapped to PD6
      \arg        GPIO_PCF2_DCI_D10_PI3_REMAP: DCI D10 remapped to PI3
      \arg        GPIO_PCF2_DCI_D11_PF10_REMAP: DCI D11 remapped to PF10
      \arg        GPIO_PCF2_DCI_D11_PH15_REMAP: DCI D11 remapped to PH15
      \arg        GPIO_PCF2_DCI_D12_PG6_REMAP: DCI D12 remapped to PG6
      \arg        GPIO_PCF2_DCI_D13_PG15_REMAP: DCI D12 remapped to PG15
      \arg        GPIO_PCF2_DCI_D13_PI0_REMAP: DCI D13 remapped to PI0
      \arg        GPIO_PCF2_DCI_HSYNC_PH8_REMAP: DCI HSYNC to PH8
      \arg        GPIO_PCF2_PH01_REMAP: PH0/PH1 remapping
      \arg        GPIO_PCF3_TLI_B5_PA3_REMAP: TLI B5 remapped to PA3
      \arg        GPIO_PCF3_TLI_VSYNC_PA4_REMAP: TLI VSYNC remapped to PA4
      \arg        GPIO_PCF3_TLI_G2_PA6_REMAP: TLI G2 remapped to PA6
      \arg        GPIO_PCF3_TLI_R6_PA8_REMAP: TLI R6 remapped to PA8
      \arg        GPIO_PCF3_TLI_R4_PA11_REMAP: TLI R4 remapped to PA11
      \arg        GPIO_PCF3_TLI_R5_PA12_REMAP: TLI R5 remapped to PA12
      \arg        GPIO_PCF3_TLI_R3_PB0_REMAP: TLI R3 remapped to PB0
      \arg        GPIO_PCF3_TLI_R6_PB1_REMAP: TLI R6 remapped to PB1
      \arg        GPIO_PCF3_TLI_B6_PB8_REMAP: TLI B6 remapped to PB8
      \arg        GPIO_PCF3_TLI_B7_PB9_REMAP: TLI B7 remapped to PB9
      \arg        GPIO_PCF3_TLI_G4_PB10_REMAP: TLI G4 remapped to PB10
      \arg        GPIO_PCF3_TLI_G5_PB11_REMAP: TLI G5 remapped to PB11
      \arg        GPIO_PCF3_TLI_HSYNC_PC6_REMAP: TLI HSYNC remapped to PC6
      \arg        GPIO_PCF3_TLI_G6_PC7_REMAP: TLI G6 remapped to PC7
      \arg        GPIO_PCF3_TLI_R2_PC10_REMAP: TLI R2 remapped to PC10
      \arg        GPIO_PCF3_TLI_G7_PD3_REMAP: TLI G7 remapped to PD3
      \arg        GPIO_PCF3_TLI_B2_PD6_REMAP: TLI B2 remapped to PD6
      \arg        GPIO_PCF3_TLI_B3_PD10_REMAP: TLI B3 remapped to PD10
      \arg        GPIO_PCF3_TLI_B0_PE4_REMAP: TLI B0 remapped to PE4
      \arg        GPIO_PCF3_TLI_G0_PE5_REMAP: TLI G0 remapped to PE5
      \arg        GPIO_PCF3_TLI_G1_PE6_REMAP: TLI G1 remapped to PE6
      \arg        GPIO_PCF3_TLI_G3_PE11_REMAP: TLI G3 remapped to PE11
      \arg        GPIO_PCF3_TLI_B4_PE12_REMAP: TLI B4 remapped to PE12
      \arg        GPIO_PCF3_TLI_DE_PE13_REMAP: TLI DE remapped to PE13
      \arg        GPIO_PCF3_TLI_CLK_PE14_REMAP: TLI CLK remapped to PE14
      \arg        GPIO_PCF3_TLI_R7_PE15_REMAP: TLI R7 remapped to PE15
      \arg        GPIO_PCF3_TLI_DE_PF10_REMAP: TLI DE remapped to PF10
      \arg        GPIO_PCF3_TLI_R7_PG6_REMAP: TLI R7 remapped to PG6
      \arg        GPIO_PCF3_TLI_CLK_PG7_REMAP: TLI CLK remapped to PG7
      \arg        GPIO_PCF3_TLI_G3_PG10_REMAP: TLI G3 remapped to PG10
      \arg        GPIO_PCF3_TLI_B2_PG10_REMAP: TLI B2 remapped to PG10
      \arg        GPIO_PCF3_TLI_B3_PG11_REMAP: TLI B3 remapped to PG11
      \arg        GPIO_PCF4_TLI_B4_PG12_REMAP: B4 remapped to PG12
      \arg        GPIO_PCF4_TLI_B1_PG12_REMAP: B1 remapped to PG12
      \arg        GPIO_PCF4_TLI_R0_PH2_REMAP2: R0 remapped to PH2
      \arg        GPIO_PCF4_TLI_R1_PH3_REMAP: TLI R1 remapped to PH3
      \arg        GPIO_PCF4_TLI_R2_PH8_REMAP: TLI R2 remapped to PH8
      \arg        GPIO_PCF4_TLI_R3_PH9_REMAP: TLI R3 remapped to PH9
      \arg        GPIO_PCF4_TLI_R4_PH10_REMAP: TLI R4 remapped to PH10
      \arg        GPIO_PCF4_TLI_R5_PH11_REMAP: TLI R5 remapped to PH11
      \arg        GPIO_PCF4_TLI_R6_PH12_REMAP: TLI R6 remapped to PH12
      \arg        GPIO_PCF4_TLI_G2_PH13_REMAP: TLI G2 remapped to PH13
      \arg        GPIO_PCF4_TLI_G3_PH14_REMAP: TLI G3 remapped to PH14
      \arg        GPIO_PCF4_TLI_G4_PH15_REMAP: TLI G4 remapped to PH15
      \arg        GPIO_PCF4_TLI_G5_PI0_REMAP: TLI G5 remapped to PI0
      \arg        GPIO_PCF4_TLI_G6_PI1_REMAP: TLI G6 remapped to PI1
      \arg        GPIO_PCF4_TLI_G7_PI2_REMAP: TLI G7 remapped to PI2
      \arg        GPIO_PCF4_TLI_B4_PI4_REMAP: TLI B4 remapped to PI4
      \arg        GPIO_PCF4_TLI_B5_PI5_REMAP: TLI B5 remapped to PI5
      \arg        GPIO_PCF4_TLI_B6_PI6_REMAP: TLI B6 remapped to PI6
      \arg        GPIO_PCF4_TLI_B7_PI7_REMAP: TLI B7 remapped to PI7
      \arg        GPIO_PCF4_TLI_VSYNC_PI9_REMAP: TLI VSYNC remapped to PI9
      \arg        GPIO_PCF4_TLI_HSYNC_PI10_REMAP: TLI HSYNC remapped to PI10
      \arg        GPIO_PCF4_TLI_R0_PH4_REMAP: TLI R0 remapped to PH4
      \arg        GPIO_PCF4_TLI_R1_PI3_REMAP: TLI R1 remapped to PI3
      \arg        GPIO_PCF4_SPI1_SCK_PD3_REMAP: SPI1 SCK remapped to PD3
      \arg        GPIO_PCF4_SPI2_MOSI_PD6_REMAP: SPI2 MOSI remapped to PD6
      \arg        GPIO_PCF5_I2C2_REMAP0: I2C2 remapping 0
      \arg        GPIO_PCF5_I2C2_REMAP1: I2C2 remapping 1
      \arg        GPIO_PCF5_TIMER1_CH0_REMAP: TIMER1 CH0 remapped to PA5
      \arg        GPIO_PCF5_TIMER4_REMAP: TIMER4 CH0 remapping
      \arg        GPIO_PCF5_TIMER7_CHON_REMAP0: TIMER7 CHON remapping 0
      \arg        GPIO_PCF5_TIMER7_CHON_REMAP1: TIMER7 CHON remapping 1
      \arg        GPIO_PCF5_TIMER7_CH_REMAP: TIMER7 CH remapping
      \arg        GPIO_PCF5_I2C1_REMAP0: I2C1 remapping 0
      \arg        GPIO_PCF5_I2C1_REMAP1: I2C1 remapping 1
      \arg        GPIO_PCF5_SPI1_NSCK_REMAP0: SPI1 NSS/SCK remapping 0
      \arg        GPIO_PCF5_SPI1_NSCK_REMAP1: SPI1 NSS/SCK remapping 1
      \arg        GPIO_PCF5_SPI1_IO_REMAP0: SPI1 MISO/MOSI remapping 0
      \arg        GPIO_PCF5_SPI1_IO_REMAP1: SPI1 MISO/MOSI remapping 1
      \arg        GPIO_PCF5_UART3_REMAP: UART3 remapping
      \arg        GPIO_PCF5_TIMER11_REMAP: TIMER11 remapping
      \arg        GPIO_PCF5_CAN0_ADD_REMAP: CAN0 addition remapping
      \arg        GPIO_PCF5_ENET_TXD3_REMAP: ETH_TXD3 remapped to PE2
      \arg        GPIO_PCF5_PPS_HI_REMAP: ETH_PPS_OUT remapped to PG8
      \arg        GPIO_PCF5_ENET_TXD01_REMAP: ETH_TX_EN/ETH_TXD0/ETH_TXD1 remapping
      \arg        GPIO_PCF5_ENET_CRSCOL_REMAP: ETH_MII_CRS/ETH_MII_COL remapping
      \arg        GPIO_PCF5_ENET_RX_HI_REMAP: ETH_RXD2/ETH_RXD3/ETH_RX_ER remapping
      \arg        GPIO_PCF5_UART6_REMAP: UART6 remapping
      \arg        GPIO_PCF5_USART5_CK_PG7_REMAP: USART5 CK remapped to PG7
      \arg        GPIO_PCF5_USART5_RTS_PG12_REMAP: USART5 RTS remapped to PG12
      \arg        GPIO_PCF5_USART5_CTS_PG13_REMAP: USART5 CTS remapped to PG13
      \arg        GPIO_PCF5_USART5_TX_PG14_REMAP: USART5 TX remapped to PG14
      \arg        GPIO_PCF5_USART5_RX_PG9_REMAP: USART5 RX remapped to PG9
      \arg        GPIO_PCF5_EXMC_SDNWE_PC0_REMAP: EXMC SDNWE remapped to PC0
      \arg        GPIO_PCF5_EXMC_SDCKE0_PC3_REMAP: EXMC SDCKE0 remapped to PC3
      \arg        GPIO_PCF5_EXMC_SDCKE1_PB5_REMAP: EXMC SDCKE1 remapped to PB5
      \arg        GPIO_PCF5_EXMC_SDNE0_PC2_REMAP: EXMC SDNE0 remapped to PC2
      \arg        GPIO_PCF5_EXMC_SDNE1_PB6_REMAP: EXMC SDNE1 remapped to PB6
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void gpio_pin_remap1_config(uint8_t remap_reg, uint32_t remap, ControlStatus newvalue)
{
    uint32_t reg = 0U;

    if(DISABLE != newvalue){
        /* AFIO port configuration register selection */
        if(GPIO_PCF2 == remap_reg){
            reg = AFIO_PCF2;
            reg |= remap;
            AFIO_PCF2 = reg;
        }else if(GPIO_PCF3 == remap_reg){
            reg = AFIO_PCF3;
            reg |= remap;
            AFIO_PCF3 = reg;
        }else if(GPIO_PCF4 == remap_reg){
            reg = AFIO_PCF4;
            reg |= remap;
            AFIO_PCF4 = reg;
        }else if(GPIO_PCF5 == remap_reg){
            reg = AFIO_PCF5;
            reg |= remap;
            AFIO_PCF5 = reg;
        }else{
            /* illegal parameters */
        }
    }else{
        if(GPIO_PCF2 == remap_reg){
            reg = AFIO_PCF2;
            reg &= ~remap;
            AFIO_PCF2 = reg;
        }else if(GPIO_PCF3 == remap_reg){
            reg = AFIO_PCF3;
            reg &= ~remap;
            AFIO_PCF3 = reg;
        }else if(GPIO_PCF4 == remap_reg){
            reg = AFIO_PCF4;
            reg &= ~remap;
            AFIO_PCF4 = reg;
        }else if(GPIO_PCF5 == remap_reg){
            reg = AFIO_PCF5;
            reg &= ~remap;
            AFIO_PCF5 = reg;
        }else{
            /* illegal parameters */
        }
    }
}

/*!
    \brief      select GPIO pin exti sources
    \param[in]  output_port: gpio event output port
      \arg        GPIO_PORT_SOURCE_GPIOA: output port source A
      \arg        GPIO_PORT_SOURCE_GPIOB: output port source B
      \arg        GPIO_PORT_SOURCE_GPIOC: output port source C
      \arg        GPIO_PORT_SOURCE_GPIOD: output port source D
      \arg        GPIO_PORT_SOURCE_GPIOE: output port source E
      \arg        GPIO_PORT_SOURCE_GPIOF: output port source F
      \arg        GPIO_PORT_SOURCE_GPIOG: output port source G
      \arg        GPIO_PORT_SOURCE_GPIOH: output port source H
      \arg        GPIO_PORT_SOURCE_GPIOI: output port source I
    \param[in]  output_pin: GPIO_PIN_SOURCE_x(x=0..15)
    \param[out] none
    \retval     none
*/
void gpio_exti_source_select(uint8_t output_port, uint8_t output_pin)
{
    uint32_t source = 0U;
    source = ((uint32_t)0x0FU) << (AFIO_EXTI_SOURCE_FIELDS * (output_pin & AFIO_EXTI_SOURCE_MASK));

    /* select EXTI sources */
    if(GPIO_PIN_SOURCE_4 > output_pin){
        /* select EXTI0/EXTI1/EXTI2/EXTI3 */
        AFIO_EXTISS0 &= ~source;
        AFIO_EXTISS0 |= (((uint32_t)output_port) << (AFIO_EXTI_SOURCE_FIELDS * (output_pin & AFIO_EXTI_SOURCE_MASK)));
    }else if(GPIO_PIN_SOURCE_8 > output_pin){
        /* select EXTI4/EXTI5/EXTI6/EXTI7 */
        AFIO_EXTISS1 &= ~source;
        AFIO_EXTISS1 |= (((uint32_t)output_port) << (AFIO_EXTI_SOURCE_FIELDS * (output_pin & AFIO_EXTI_SOURCE_MASK)));
    }else if(GPIO_PIN_SOURCE_12 > output_pin){
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
    \brief      lock GPIO pin
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,H,I)
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
