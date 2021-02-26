/*
 * Copyright (c) 2020-2021, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include "ab32vg1_hal.h"

void hal_uart_mspinit(struct uart_handle *huart)
{
    struct gpio_init gpio_init;

    if (huart->instance == UART0_BASE) {
        gpio_init.pin       = GPIO_PIN_7;
        gpio_init.pull      = GPIO_PULLUP;
        gpio_init.dir       = GPIO_DIR_INPUT;
        gpio_init.de        = GPIO_DIGITAL;
        gpio_init.alternate = GPIO_AF_MAP_Gx(UT0TXMAP_AF, GPIO_AF_G1) | UT0RXMAP_TX;
        gpio_init.af_con    = GPIO_AFEN | GPIO_AFCON0 | UT0TXMAP_AF;
        hal_gpio_init(GPIOA_BASE, &gpio_init);
    } else if (huart->instance == UART1_BASE) {
        gpio_init.pin       = GPIO_PIN_4;
        gpio_init.dir       = GPIO_DIR_OUTPUT;
        gpio_init.de        = GPIO_DIGITAL;
        gpio_init.alternate = GPIO_AF_MAP_Gx(UT1TXMAP_AF, GPIO_AF_G2);
        gpio_init.af_con    = GPIO_AFEN | GPIO_AFCON0 | UT1TXMAP_AF;
        hal_gpio_init(GPIOA_BASE, &gpio_init);

        gpio_init.pin       = GPIO_PIN_3;
        gpio_init.pull      = GPIO_PULLUP;
        gpio_init.dir       = GPIO_DIR_INPUT;
        gpio_init.de        = GPIO_DIGITAL;
        gpio_init.alternate = GPIO_AF_MAP_Gx(UT1RXMAP_AF, GPIO_AF_G2);
        gpio_init.af_con    = GPIO_AFEN | GPIO_AFCON0 | UT1RXMAP_AF;
        hal_gpio_init(GPIOA_BASE, &gpio_init);
        /* Interrupt */
    }
}

#ifdef HAL_DAC_MODULE_ENABLED
void hal_dac_mspinit(struct dac_handle *hdac)
{
}
#endif

#ifdef HAL_SD_MODULE_ENABLED
void hal_sd_mspinit(sd_handle_t hsd)
{
    struct gpio_init gpio_init;

    gpio_init.pin       = GPIO_PIN_0 | GPIO_PIN_2;
    gpio_init.pull      = GPIO_PULLUP;
    gpio_init.dir       = GPIO_DIR_INPUT;
    gpio_init.de        = GPIO_DIGITAL;
    gpio_init.alternate = GPIO_AF_MAP_Gx(SD0MAP_AF, GPIO_AF_G2);
    gpio_init.af_con    = GPIO_AFEN | GPIO_AFCON0 | SD0MAP_AF;
    hal_gpio_init(GPIOB_BASE, &gpio_init);

    gpio_init.pin       = GPIO_PIN_1;
    gpio_init.dir       = GPIO_DIR_OUTPUT;
    gpio_init.alternate = GPIO_AF_MAP_Gx(SD0MAP_AF, GPIO_AF_G2);
    gpio_init.af_con    = GPIO_AFEN | GPIO_AFCON0 | SD0MAP_AF;
    hal_gpio_init(GPIOB_BASE, &gpio_init);
}
#endif

void hal_pwm_mspinit(void)
{
    struct gpio_init gpio_init = {0};

    gpio_init.dir       = GPIO_DIR_OUTPUT;
    gpio_init.de        = GPIO_DIGITAL;

#ifdef BSP_USING_T3_PWM0
    gpio_init.pin       = GPIO_PIN_0;
    gpio_init.alternate = GPIO_AF_MAP_Gx(TMR3MAP_AF, GPIO_AF_G1);
    gpio_init.af_con    = GPIO_AFEN | GPIO_AFCON2;
    hal_gpio_init(GPIOB_BASE, &gpio_init);
#endif

#ifdef BSP_USING_T4_PWM1
    gpio_init.pin       = GPIO_PIN_6;
    gpio_init.alternate = GPIO_AF_MAP_Gx(TMR4MAP_AF, GPIO_AF_G1);
    gpio_init.af_con    = GPIO_AFEN | GPIO_AFCON2;
    hal_gpio_init(GPIOA_BASE, &gpio_init);
#endif

#ifdef BSP_USING_T5_PWM0
    gpio_init.pin       = GPIO_PIN_1;
    gpio_init.alternate = GPIO_AF_MAP_Gx(TMR5MAP_AF, GPIO_AF_G1);
    gpio_init.af_con    = GPIO_AFEN | GPIO_AFCON2;
    hal_gpio_init(GPIOE_BASE, &gpio_init);
#endif

#ifdef BSP_USING_LPWM0_G1
    gpio_init.pin       = GPIO_PIN_4;
    gpio_init.alternate = GPIO_AF_MAP_Gx(LPWM0MAP_AF, GPIO_AF_G1);
    gpio_init.af_con    = GPIO_AFEN | GPIO_AFCON1;
    hal_gpio_init(GPIOE_BASE, &gpio_init);
#endif

#ifdef BSP_USING_LPWM1_G3
    gpio_init.pin       = GPIO_PIN_1;
    gpio_init.alternate = GPIO_AF_MAP_Gx(LPWM1MAP_AF, GPIO_AF_G3);
    gpio_init.af_con    = GPIO_AFEN | GPIO_AFCON1;
    hal_gpio_init(GPIOA_BASE, &gpio_init);
#endif

#ifdef BSP_USING_LPWM2_G2
    gpio_init.pin       = GPIO_PIN_0;
    gpio_init.alternate = GPIO_AF_MAP_Gx(LPWM2MAP_AF, GPIO_AF_G2);
    gpio_init.af_con    = GPIO_AFEN | GPIO_AFCON1;
    hal_gpio_init(GPIOE_BASE, &gpio_init);
#endif

#ifdef BSP_USING_LPWM2_G3
    gpio_init.pin       = GPIO_PIN_2;
    gpio_init.alternate = GPIO_AF_MAP_Gx(LPWM2MAP_AF, GPIO_AF_G3);
    gpio_init.af_con    = GPIO_AFEN | GPIO_AFCON1;
    hal_gpio_init(GPIOA_BASE, &gpio_init);
#endif
}
