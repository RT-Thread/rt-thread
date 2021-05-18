/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-07-27     thread-liu        first version
 */

#include "board.h"
#ifdef BSP_USING_EXTI

//#define DRV_DEBUG
#define LOG_TAG             "drv.exti"
#include <drv_log.h>

/* defined the KEY2 pin: */
#define KEY2_PIN    GET_PIN(A, 13)

void key2_on(void *args)
{
    rt_kprintf("press key2!\n");
}

static int exti_sample(void)
{
    rt_pin_mode(KEY2_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY2_PIN, PIN_IRQ_MODE_FALLING, key2_on, RT_NULL);
    rt_pin_irq_enable(KEY2_PIN, PIN_IRQ_ENABLE);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(exti_sample);

#endif
