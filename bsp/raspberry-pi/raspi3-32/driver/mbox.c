/*
 * File      : mbox.c
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-08-29     zdzn           first version
 */

/* mailbox message buffer */
#include "mbox.h"
#include "mmu.h"

volatile unsigned int *mbox = (volatile unsigned int *) MBOX_ADDR;
/**
 * Make a mailbox call. Returns 0 on failure, non-zero on success
 */
void init_mbox_mmu_map()
{
    rt_hw_change_mmu_table(MBOX_ADDR, 96, MBOX_ADDR, STRONG_ORDER_MEM);
}

int mbox_call(unsigned char ch, int mmu_enable)
{
    unsigned int r = (((MBOX_ADDR)&~0xF) | (ch&0xF));
    if (mmu_enable)
        r = BUS_ADDRESS(r);
    /* wait until we can write to the mailbox */
    do
    {
        asm volatile("nop");
    } while (*MBOX_STATUS & MBOX_FULL);
    /* write the address of our message to the mailbox with channel identifier */
    *MBOX_WRITE = r;
    /* now wait for the response */
    while (1)
    {
        /* is there a response? */
        do
        {
            asm volatile("nop");
        } 
        while (*MBOX_STATUS & MBOX_EMPTY);
        /* is it a response to our message? */
        if (r == *MBOX_READ)
        {
            /* is it a valid successful response? */
            return mbox[1] == MBOX_RESPONSE;
        }
    }
    return 0;
}
