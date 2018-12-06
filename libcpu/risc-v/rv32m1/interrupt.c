/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/01     Bernard      The first version
 */

#include <rthw.h>

#include <board.h>
#include <RV32M1_ri5cy.h>

typedef void (*irq_handler_t)(void);
extern const irq_handler_t isrTable[];

void SystemIrqHandler(uint32_t mcause)
{
    uint32_t intNum;

    if (mcause & 0x80000000) /* For external interrupt. */
    {
        intNum = mcause & 0x1FUL;

        /* Clear pending flag in EVENT unit .*/
        EVENT_UNIT->INTPTPENDCLEAR = (1U << intNum);

        /* Now call the real irq handler for intNum */
        isrTable[intNum]();
    }
}
