/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30     bernard       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "mbox.h"

void set_led(int state) //set state LED nyala atau mati
{
    if (state==1)                       //LED nyala
    { 
        mbox[0] = 8*4;                  // length of the message
        mbox[1] = MBOX_REQUEST;         // this is a request message
    
        mbox[2] = 0x00038041;   // get serial number command
        mbox[3] = 8;                    // buffer size
        mbox[4] = 0;
        mbox[5] = 130;                    // clear output buffer
        mbox[6] = 1;
        mbox[7] = MBOX_TAG_LAST;
        mbox_call(8, MMU_DISABLE);
    }
    else if (state==0)                  //LED mati
    { 
        mbox[0] = 8*4;                  // length of the message
        mbox[1] = MBOX_REQUEST;         // this is a request message
    
        mbox[2] = 0x00038041;   // get serial number command
        mbox[3] = 8;                    // buffer size
        mbox[4] = 0;
        mbox[5] = 130;                    // clear output buffer
        mbox[6] = 0;
        mbox[7] = MBOX_TAG_LAST;
        mbox_call(8, MMU_DISABLE);
    }
}

int main(int argc, char** argv)
{
    int count = 1;

    rt_kprintf("Hi, this is RT-Thread!!\n");

    while (count++)
    {
        set_led(1);
        rt_thread_mdelay(500);
        set_led(0);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
