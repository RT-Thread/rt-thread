/*
 * Copyright (c) 2020, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-16     Dystopia     the first version
 */

#ifndef SERIAL_REG_H
#define SERIAL_REG_H

struct uart_reg
{
    unsigned int uartdata;
    unsigned int uartstatus;
    unsigned int uartctrl;
    unsigned int uartscaler;
};

#endif /* end of include guard: SERIAL_REG_H */
