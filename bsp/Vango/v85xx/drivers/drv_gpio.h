/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-12-27     iysheng           first release
 * 2021-09-10     ZhuXW             add V85XX support
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __V85XX_PORT(port)  GPIO##port##_BASE

#define GET_PIN(PORTx,PIN) (__V85XX_PORT(PORTx)==GPIOA_BASE) ? (rt_base_t)(0 + PIN):(rt_base_t)((16 * ( ((rt_base_t)__V85XX_PORT(PORTx) - (rt_base_t)GPIOB_BASE)/(0x0400UL) +1)) + PIN)

#define PIN_NUM(port, no) (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin) ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin) ((uint8_t)((pin) & 0xFu))

#define PIN_V85XXPORT(pin) ((GPIO_TypeDef *)(GPIOB_BASE + (0x400u * PIN_PORT(pin))))
#define PIN_V85XXPIN(pin) ((uint16_t)(1u << PIN_NO(pin)))

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

