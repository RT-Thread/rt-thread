/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-31     shelton      first version
 */

#include <rtthread.h>
#include "at32f421.h"
#include "at32_msp.h"

#ifdef BSP_USING_UART
void at32_msp_usart_init(void *instance)
{
    gpio_init_type gpio_init_struct;
    usart_type *usart_x = (usart_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_UART1
    if(USART1 == usart_x)
    {
        crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_9;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_init_struct.gpio_pins = GPIO_PINS_10;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE9, GPIO_MUX_1);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE10, GPIO_MUX_1);
    }
#endif
#ifdef BSP_USING_UART2
    if(USART2 == usart_x)
    {
        crm_periph_clock_enable(CRM_USART2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_2;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_init_struct.gpio_pins = GPIO_PINS_3;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE2, GPIO_MUX_1);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE3, GPIO_MUX_1);
    }
#endif
    /* add others */
}
#endif /* BSP_USING_SERIAL */

#ifdef BSP_USING_SPI
void at32_msp_spi_init(void *instance)
{
    gpio_init_type gpio_init_struct;
    spi_type *spi_x = (spi_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_SPI1
    if(SPI1 == spi_x)
    {
        crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_4;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_pins = GPIO_PINS_5 | GPIO_PINS_6 | GPIO_PINS_7;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE5, GPIO_MUX_0);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE6, GPIO_MUX_0);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE7, GPIO_MUX_0);
    }
#endif
#ifdef BSP_USING_SPI2
    if(SPI2 == spi_x)
    {
        crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_12;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_pins = GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE13, GPIO_MUX_0);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE14, GPIO_MUX_0);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE15, GPIO_MUX_0);
    }
#endif
    /* add others */
}
#endif /* BSP_USING_SPI */

#ifdef BSP_USING_PWM
void at32_msp_tmr_init(void *instance)
{
    gpio_init_type gpio_init_struct;
    tmr_type *tmr_x = (tmr_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    if(tmr_x == TMR1)
    {
        /* tmr1 clock enable */
        crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);
        /* gpioa clock enable */
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        /* gpioa configuration: tmr1 channel1 and channel4 as alternate function push-pull */
        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_8 | GPIO_PINS_11;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE8, GPIO_MUX_2);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE11, GPIO_MUX_2);
    }
    /* add others */
}
#endif /* BSP_USING_PWM */

#ifdef BSP_USING_ADC
void at32_msp_adc_init(void *instance)
{
    gpio_init_type gpio_init_struct;
    adc_type *adc_x = (adc_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_ADC1
    if(adc_x == ADC1)
    {
        /* adc1 & gpio clock enable */
        crm_periph_clock_enable(CRM_ADC1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        /* configure adc channel as analog input */
        gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1 | GPIO_PINS_4 | GPIO_PINS_5 | GPIO_PINS_6;
        gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
        gpio_init(GPIOA, &gpio_init_struct);
    }
#endif
}
#endif /* BSP_USING_ADC */

#ifdef BSP_USING_HWTIMER
void at32_msp_hwtmr_init(void *instance)
{
    tmr_type *tmr_x = (tmr_type *)instance;

#ifdef BSP_USING_HWTMR3
    if(tmr_x == TMR3)
    {
        /* tmr3 clock enable */
        crm_periph_clock_enable(CRM_TMR3_PERIPH_CLOCK, TRUE);
    }
#endif
}
#endif
