/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-12-02     Meco Man     the first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtdef.h>

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

#define GET_PIN(PORTx,PIN) (rt_uint64_t)((((rt_uint64_t)GPIO_PIN_##PIN) << 32) | (rt_uint64_t)(rt_ubase_t)GPIO##PORTx)

void rt_pin_mode(rt_uint64_t pin, rt_uint8_t mode);
void rt_pin_write(rt_uint64_t pin, rt_uint8_t value);
rt_int8_t rt_pin_read(rt_uint64_t pin);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */
