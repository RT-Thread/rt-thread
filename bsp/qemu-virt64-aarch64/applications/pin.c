/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2022-6-30      GuEe-GUI       first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_PIN

void qemu_gpio3_key_poweroff(void *args)
{
    rt_kprintf("\nYou power off the machine.\n");

    rt_hw_cpu_shutdown();
}

static int pin_init()
{
    rt_pin_attach_irq(3, PIN_IRQ_MODE_FALLING, qemu_gpio3_key_poweroff, RT_NULL);
    rt_pin_irq_enable(3, RT_TRUE);

    return 0;
}
INIT_ENV_EXPORT(pin_init);

#endif /* RT_USING_PIN */
