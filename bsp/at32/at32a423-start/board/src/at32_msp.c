/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-12     shelton      first version
 */

#include <rtthread.h>
#include "at32a423.h"
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

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE9, GPIO_MUX_7);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE10, GPIO_MUX_7);
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

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE2, GPIO_MUX_7);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE3, GPIO_MUX_7);
    }
#endif
#ifdef BSP_USING_UART3
    if(USART3 == usart_x)
    {
        crm_periph_clock_enable(CRM_USART3_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_10;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_init_struct.gpio_pins = GPIO_PINS_11;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE10, GPIO_MUX_7);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE11, GPIO_MUX_7);
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

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE5, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE6, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE7, GPIO_MUX_5);
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

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE13, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE14, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE15, GPIO_MUX_5);
    }
#endif
    /* add others */
}
#endif /* BSP_USING_SPI */
#ifdef BSP_USING_HARD_I2C
void at32_msp_i2c_init(void *instance)
{
    gpio_init_type gpio_init_struct;
    i2c_type *i2c_x = (i2c_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_HARD_I2C1
    if(I2C1 == i2c_x)
    {
        crm_periph_clock_enable(CRM_I2C1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_6 | GPIO_PINS_7;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE6, GPIO_MUX_4);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE7, GPIO_MUX_4);
    }
#endif
#ifdef BSP_USING_HARD_I2C2
    if(I2C2 == i2c_x)
    {
        crm_periph_clock_enable(CRM_I2C2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_10 | GPIO_PINS_11;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE10, GPIO_MUX_4);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE11, GPIO_MUX_4);
    }
#endif
#ifdef BSP_USING_HARD_I2C3
    if(I2C3 == i2c_x)
    {
        crm_periph_clock_enable(CRM_I2C3_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_8;
        gpio_init(GPIOA, &gpio_init_struct);
        gpio_init_struct.gpio_pins = GPIO_PINS_9;
        gpio_init(GPIOC, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE8, GPIO_MUX_4);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE9, GPIO_MUX_4);
    }
#endif
    /* add others */
}
#endif /* BSP_USING_HARD_I2C */

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

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE8, GPIO_MUX_1);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE11, GPIO_MUX_1);
    }

    if(tmr_x == TMR2)
    {
        /* tmr2 clock enable */
        crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);
        /* gpioa clock enable */
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        /* gpioa configuration: tmr1 channel1 and channel2 as alternate function push-pull */
        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE0, GPIO_MUX_1);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE1, GPIO_MUX_1);
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
        crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

        /* configure adc channel as analog input */
        gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1 | GPIO_PINS_2 | GPIO_PINS_3 | GPIO_PINS_4 | GPIO_PINS_5;
        gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
        gpio_init(GPIOC, &gpio_init_struct);
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

#ifdef BSP_USING_CAN
void at32_msp_can_init(void *instance)
{
    gpio_init_type gpio_init_struct;
    can_type *can_x = (can_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_CAN1
    if(can_x == CAN1)
    {
        crm_periph_clock_enable(CRM_CAN1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_8 | GPIO_PINS_9;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE8, GPIO_MUX_9);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE9, GPIO_MUX_9);
    }
#endif
#ifdef BSP_USING_CAN2
    if(can_x == CAN2)
    {
        crm_periph_clock_enable(CRM_CAN2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_5 | GPIO_PINS_6;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE5, GPIO_MUX_9);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE6, GPIO_MUX_9);
    }
#endif
}
#endif /* BSP_USING_CAN */

#ifdef BSP_USING_USBOTG
void at32_msp_usb_init(void *instance)
{
    /* defalut usb clock from hext */
    usb_clk48_s clk_s = USB_CLK_HEXT;

    crm_periph_clock_enable(CRM_OTGFS1_PERIPH_CLOCK, TRUE);

    if(clk_s == USB_CLK_HICK)
    {
        crm_usb_clock_source_select(CRM_USB_CLOCK_SOURCE_HICK);

        /* enable the acc calibration ready interrupt */
        crm_periph_clock_enable(CRM_ACC_PERIPH_CLOCK, TRUE);

        /* update the c1\c2\c3 value */
        acc_write_c1(7980);
        acc_write_c2(8000);
        acc_write_c3(8020);

        /* open acc calibration */
        acc_calibration_mode_enable(ACC_CAL_HICKTRIM, TRUE);
    }
    else
    {
        switch(system_core_clock)
        {
            /* 48MHz */
            case 48000000:
                crm_usb_clock_div_set(CRM_USB_DIV_2);
                break;
            /* 72MHz */
            case 72000000:
                crm_usb_clock_div_set(CRM_USB_DIV_3);
                break;
            /* 96MHz */
            case 96000000:
                crm_usb_clock_div_set(CRM_USB_DIV_4);
                break;
            /* 120MHz */
            case 120000000:
                crm_usb_clock_div_set(CRM_USB_DIV_5);
                break;
            /* 144MHz */
            case 144000000:
                crm_usb_clock_div_set(CRM_USB_DIV_6);
                break;
            default:
                break;
        }
    }
}
#endif /* BSP_USING_USBOTG */

#ifdef BSP_USING_DAC
void at32_msp_dac_init(void *instance)
{
    gpio_init_type gpio_init_struct;
    dac_type *dac_x = (dac_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_DAC1
    if(dac_x == DAC)
    {
        /* dac & gpio clock enable */
        crm_periph_clock_enable(CRM_DAC_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        /* configure adc channel as analog output */
        gpio_init_struct.gpio_pins = GPIO_PINS_4 | GPIO_PINS_5;
        gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init(GPIOA, &gpio_init_struct);
    }
#endif
}
#endif /* BSP_USING_DAC */
