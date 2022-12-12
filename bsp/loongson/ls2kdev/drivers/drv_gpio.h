/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-24     勤为本        first version
 * 2018-05-11     zhuangwei    add gpio interrupt ops
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rthw.h>

struct gpio_irq_def
{
    void  *irq_arg[32];
    void (*irq_cb[32])(void *param);
    rt_uint8_t irq_type[32];
    rt_uint8_t state[32];
};

struct loongson_gpio {
    rt_uint64_t GPIO0_OEN;
    rt_uint64_t GPIO1_OEN;    /* Reserved */
    rt_uint64_t GPIO0_O;
    rt_uint64_t GPIO1_O;      /* Reserved */
    rt_uint64_t GPIO0_I;
    rt_uint64_t GPIO1_I;      /* Reserved */
    rt_uint64_t GPIO0_INTEN;
    rt_uint64_t GPIO1_INTEN;  /* Reserved */
};

int loongson_pin_init(void);

#endif

