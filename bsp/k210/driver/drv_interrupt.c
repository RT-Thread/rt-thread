/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-19     ZYH          first version
 */

#include <plic.h>

void plic_irq_handle(plic_irq_t irq)
{
    plic_instance_t (*plic_instance)[IRQN_MAX] = plic_get_instance();
    if (plic_instance[0][irq].callback)
    {
        plic_instance[0][irq].callback(
            plic_instance[0][irq].ctx);
    }
    else if (plic_instance[1][irq].callback)
    {
        plic_instance[1][irq].callback(
            plic_instance[1][irq].ctx);
    }
}

