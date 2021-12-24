/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-08-20     BruceOu           the first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GPIOA_BASE            (GPIO_BASE + 0x00000800UL)
#define GPIOB_BASE            (GPIO_BASE + 0x00000C00UL)
#define GPIOC_BASE            (GPIO_BASE + 0x00001000UL)
#define GPIOD_BASE            (GPIO_BASE + 0x00001400UL)
#define GPIOE_BASE            (GPIO_BASE + 0x00001800UL)
#define GPIOF_BASE            (GPIO_BASE + 0x00001C00UL)
#define GPIOG_BASE            (GPIO_BASE + 0x00002000UL)

#define __GD32_PORT(port)  GPIO##port##_BASE

#define GD32_PIN(index, port, pin) {index, RCU_GPIO##port,      \
                                    GPIO##port, GPIO_PIN_##pin, \
                                    EXTI_SOURCE_GPIO##port,     \
                                    EXTI_SOURCE_PIN##pin}
#define GD32_PIN_DEFAULT            {-1, (rcu_periph_enum)0, 0, 0, 0, 0}

#define GET_PIN(PORTx, PIN) (rt_base_t)((16 * ( ((rt_base_t)__GD32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)

struct pin_index
{
    rt_int16_t index;
    rcu_periph_enum clk;
    rt_uint32_t gpio_periph;
    rt_uint32_t pin;
    rt_uint8_t port_src;
    rt_uint8_t pin_src;
};

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

