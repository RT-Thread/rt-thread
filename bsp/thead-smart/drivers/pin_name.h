/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      header file for the pin_name
 */

#ifndef _PINNAMES_H
#define _PINNAMES_H


#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
    PA0 = 0,
    PA1,
    PA2,
    PA3,
    PA4,
    PA5,
    PA6,
    PA7,
    PAD_UART0_SIN,
    PAD_UART0_SOUT
}
pin_name_e;

typedef enum
{
    PORTA = 0,
    PORTB = 1,
    PORTC = 2,
    PORTD = 3,
    PORTE = 4,
    PORTF = 5,
    PORTG = 6,
    PORTH = 7
} port_name_e;

typedef enum
{
    NONE = 0
} pin_func_e;

#ifdef __cplusplus
}
#endif

#endif
