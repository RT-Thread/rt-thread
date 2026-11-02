/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_EXTERNAL_IRQ_H__
#define __DRV_EXTERNAL_IRQ_H__

#include <rtdevice.h>
#include <drivers/ofw.h>

struct ra_external_irq;

struct ra_external_irq *ra_external_irq_get(struct rt_ofw_node *np);
int ra_external_irq_acquire(struct ra_external_irq *external_irq,
                            rt_uint8_t port, rt_uint8_t pin, rt_uint8_t mode);
rt_err_t ra_external_irq_enable(struct ra_external_irq *external_irq,
                                rt_uint8_t port, rt_uint8_t pin);
rt_err_t ra_external_irq_disable(struct ra_external_irq *external_irq,
                                 rt_uint8_t port, rt_uint8_t pin);
rt_err_t ra_external_irq_release(struct ra_external_irq *external_irq,
                                 rt_uint8_t port, rt_uint8_t pin);

#endif /* __DRV_EXTERNAL_IRQ_H__ */
