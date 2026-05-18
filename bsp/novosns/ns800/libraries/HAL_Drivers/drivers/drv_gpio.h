/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-11-06     balanceTWK        first version
 * 2020-09-01     thread-liu        add GPIOZ
 * 2020-09-18     geniusgogo        optimization design pin-index algorithm
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GPIO_TypeDef *port;
    GPIO_PinNum  pin;
} rt_pin_info_t;


#define PIN_NUM(...)        get_pin_num(__VA_ARGS__)
#define PIN_PORT(pin)       get_port_index_by_num(pin)
#define PIN_NO(pin)         get_pin_index_by_num(pin)

const rt_pin_info_t* get_pin_info(int pin_num);
int get_pin_num(GPIO_TypeDef *port, GPIO_PinNum pin);
uint8_t get_port_index(GPIO_TypeDef *port);
uint8_t get_pin_index(uint16_t pin);
uint8_t get_port_index_by_num(int pin_num);
uint8_t get_pin_index_by_num(int pin_num);

int rt_hw_pin_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

