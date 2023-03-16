/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-06-16     guohp1128         first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <board.h>
#include <rtdevice.h>
#include <hal/nrf_gpio.h>
#include <drivers/include/nrfx_gpiote.h>

#define __NRF5X_PORT(port)  NRF_P##port##_BASE

#define GET_PIN(PORTx,PIN) (rt_base_t)((32 * ( ((rt_base_t)__NRF5X_PORT(PORTx) - (rt_base_t)NRF_P0_BASE)/(0x0300UL) )) + PIN)

#define __NRF5X_PIN(index, gpio, gpio_index)                                \
    {                                                                       \
        index, NRF_P##gpio, gpio_index                                      \
    }

#define __NRF5X_PIN_RESERVE                                                 \
    {                                                                       \
        -1, 0, 0                                                            \
    }

/* nrf5x GPIO driver */
struct pin_index
{
    int index;
    NRF_GPIO_Type *gpio;//NRF_P0 or NRF_P1
    rt_base_t pin;
};

rt_err_t rt_hw_pin_init(void);

#endif /* __DRV_GPIO_H__ */

