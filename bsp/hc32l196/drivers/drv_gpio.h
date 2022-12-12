/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-05     DongBowen    first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtdevice.h>
#include "hc32l196_ddl.h"
#include "hc32l196_gpio.h"

#ifdef RT_USING_PIN

#define __HC_PORT(port)                 GpioPort##port
#define __HC_PORT_ADJUST(port)          ((port) <=  GpioPortD ? (port) : ((port) & 0xff) + 0x100)
#define GET_PIN(PORT, PIN)              (((rt_uint16_t)__HC_PORT_ADJUST(__HC_PORT(PORT)) / 4) + PIN)
#define __GET_PIN(PORT, PIN)            (((rt_uint16_t)__HC_PORT_ADJUST(PORT) / 4) + PIN)

#endif

#endif /* __DRV_GPIO_H__ */
