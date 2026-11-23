/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_PIN_MCXC162_H__
#define __DRV_PIN_MCXC162_H__

#include <rtdevice.h>

#define GET_PINS(port, pin) ((port) * 32 + (pin))

int rt_hw_pin_init(void);

#endif /* __DRV_PIN_MCXC162_H__ */
