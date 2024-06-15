/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-15     yby          the first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include "board.h"

#define _MSP432_STRING(x) #x
#define _MSP432_PIN_NAME(PORTx,PIN) \
        ("P" _MSP432_STRING(PORTx) "." _MSP432_STRING(PIN))
#define GET_PIN(PORTx,PIN) rt_pin_get(_MSP432_PIN_NAME(PORTx,PIN))

/* MSP432 GPIO driver*/
struct pin_index
{
    rt_uint8_t index;
    rt_uint32_t gpioBaseAddress;
    rt_uint32_t pin;
};

int rt_hw_pin_init(void);

#endif  /*__DRV_GPIO_H__*/

/************************** end of file ******************/
