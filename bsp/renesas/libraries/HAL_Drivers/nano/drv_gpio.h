/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-08-20     kurisaw           first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtdef.h>
#include <hal_data.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PIN_LOW                 0x00
#define PIN_HIGH                0x01

#define PIN_MODE_OUTPUT         0x00
#define PIN_MODE_INPUT          0x01
#define PIN_MODE_INPUT_PULLUP   0x02
#define PIN_MODE_INPUT_PULLDOWN 0x03
#define PIN_MODE_OUTPUT_OD      0x04

#ifdef SOC_SERIES_R9A07G0
#define RA_MIN_PIN_VALUE    BSP_IO_PORT_00_PIN_0
#define RA_MAX_PIN_VALUE    BSP_IO_PORT_24_PIN_7
#else
#define RA_MIN_PIN_VALUE    BSP_IO_PORT_00_PIN_00
#define RA_MAX_PIN_VALUE    BSP_IO_PORT_11_PIN_15
#endif

void rt_pin_mode(rt_uint64_t pin, rt_uint8_t mode);
void rt_pin_write(rt_uint64_t pin, rt_uint8_t value);
rt_int8_t rt_pin_read(rt_uint64_t pin);
#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

