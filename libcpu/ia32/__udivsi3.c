/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-10-09     Bernard      the first version for i386
 */

#include <stdint.h>

uint32_t __udivsi3(uint32_t num, uint32_t den)
{
    uint32_t quot = 0, qbit = 1;

    if (den == 0)
    {
        asm volatile ("int $0");
        return 0;   /* If trap returns... */
    }

    /* Left-justify denominator and count shift */
    while ((int32_t) den >= 0)
    {
        den <<= 1;
        qbit <<= 1;
    }

    while (qbit)
    {
        if (den <= num)
        {
            num -= den;
            quot += qbit;
        }
        den >>= 1;
        qbit >>= 1;
    }

    return quot;
}
