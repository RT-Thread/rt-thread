/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/04/24     Juice      The first version
 */

#include <rthw.h>

#include <board.h>

typedef void (*irq_handler_t)(void);
extern const irq_handler_t isrTable[];

uintptr_t handle_trap(uintptr_t mcause, uintptr_t epc, uintptr_t *sp)
{
    uint32_t intNum;
    if (mcause & 0x80000000) /* For external interrupt. */
    {
    }
    else
    {
        intNum = mcause & 0x1FUL;
        /* Now call the real irq handler for intNum */
        if (intNum <= 24)
        {
            if (isrTable[intNum])isrTable[intNum]();
        }
    }
}
