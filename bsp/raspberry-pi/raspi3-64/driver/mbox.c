/*
 * File      : mbox.c
 * Copyright (c) 2006-2021, RT-Thread Development Team
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
//volatile unsigned int  __attribute__((aligned(16))) mbox[36];
volatile unsigned int *mbox = (volatile unsigned int *) MBOX_ADDR;
#define BUS_ADDRESS(phys)   (((phys) & ~0xC0000000)  |  0xC0000000)

/**
 * Make a mailbox call. Returns 0 on failure, non-zero on success
 */
int mbox_call(unsigned char ch, int mmu_enable)
{
    unsigned int r = (((MBOX_ADDR)&~0xF) | (ch&0xF));
    if(mmu_enable)
        r = BUS_ADDRESS(r);
    /* wait until we can write to the mailbox */
    do
    {
        asm volatile("nop");
    } while (*MBOX_STATUS & MBOX_FULL);
    /* write the address of our message to the mailbox with channel identifier */
    *MBOX_WRITE = r;
    /* now wait for the response */
   // rt_kprintf("mailbox request %x\n",r);
    while(1)
    {
        /* is there a response? */
        do
        {
            asm volatile("nop");
        } while (*MBOX_STATUS & MBOX_EMPTY);
        /* is it a response to our message? */
        if (r == *MBOX_READ){
            /* is it a valid successful response? */
        //  rt_kprintf("mbox: %x, %x, %x, %x, %x, %x, %x, %x\n", mbox[0], mbox[1], mbox[2], mbox[3], mbox[4], mbox[5], mbox[6], mbox[7]);
            return mbox[1] == MBOX_RESPONSE;
        }
    }
    return 0;
}

int bcm283x_mbox_hardware_get_model(void)
{
    mbox[0] = 8*4;                          // length of the message
    mbox[1] = MBOX_REQUEST;                 // this is a request message

    mbox[2] = MBOX_TAG_HARDWARE_GET_MODEL;
    mbox[3] = 4;                            // buffer size
    mbox[4] = 0;                            // len

    mbox[5] = 0;
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    return mbox[5];
}

int bcm283x_mbox_hardware_get_revison(void)
{
    mbox[0] = 8*4;                          // length of the message
    mbox[1] = MBOX_REQUEST;                 // this is a request message

    mbox[2] = MBOX_TAG_HARDWARE_GET_REV;
    mbox[3] = 4;                            // buffer size
    mbox[4] = 0;                            // len

    mbox[5] = 0;
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    return mbox[5];
}

int bcm283x_mbox_hardware_get_mac_address(uint8_t * mac)
{
    mbox[0] = 8*4;                                 // length of the message
    mbox[1] = MBOX_REQUEST;                        // this is a request message

    mbox[2] = MBOX_TAG_HARDWARE_GET_MAC_ADDRESS;
    mbox[3] = 6;                                   // buffer size
    mbox[4] = 0;                                   // len

    mbox[5] = 0;
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    char * mac_str = (char *)&mbox[5];
    mac[0] = mac_str[0];
    mac[1] = mac_str[1];
    mac[2] = mac_str[2];
    mac[3] = mac_str[3];
    mac[4] = mac_str[4];
    mac[5] = mac_str[5];
    return 0;
}


int bcm283x_mbox_hardware_get_serial(rt_uint64_t* sn)
{
    mbox[0] = 8*4;                              // length of the message
    mbox[1] = MBOX_REQUEST;                     // this is a request message

    mbox[2] = MBOX_TAG_HARDWARE_GET_SERIAL;
    mbox[3] = 8;                                // buffer size
    mbox[4] = 0;                                // len

    mbox[5] = 0;
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    sn = (rt_uint64_t *)&mbox[5];

    return 0;
}

int bcm283x_mbox_hardware_get_arm_memory(rt_uint32_t * base, rt_uint32_t * size)
{
    mbox[0] = 8*4;                                  // length of the message
    mbox[1] = MBOX_REQUEST;                         // this is a request message

    mbox[2] = MBOX_TAG_HARDWARE_GET_ARM_MEMORY;
    mbox[3] = 8;                                    // buffer size
    mbox[4] = 0;                                    // len

    mbox[5] = 0;
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    *base = mbox[5];
    *size = mbox[6];

    return 0;

}

int bcm283x_mbox_hardware_get_vc_memory(rt_uint32_t * base, rt_uint32_t * size)
{
    mbox[0] = 8*4;                               // length of the message
    mbox[1] = MBOX_REQUEST;                      // this is a request message

    mbox[2] = MBOX_TAG_HARDWARE_GET_VC_MEMORY;
    mbox[3] = 8;                                 // buffer size
    mbox[4] = 0;                                 // len

    mbox[5] = 0;
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    *base = mbox[5];
    *size = mbox[6];

    return 0;
}

int bcm283x_mbox_clock_get_turbo(void)
{
    mbox[0] = 8*4;                      // length of the message
    mbox[1] = MBOX_REQUEST;             // this is a request message

    mbox[2] = MBOX_TAG_CLOCK_GET_TURBO;
    mbox[3] = 8;                        // buffer size
    mbox[4] = 4;                        // len

    mbox[5] = 0;                        // id
    mbox[6] = 0;                        // val

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    if(mbox[5] != 0)
    {
        return -1;
    }

    return mbox[6];
}

int bcm283x_mbox_clock_set_turbo(int level)
{
    mbox[0] = 8*4;                      // length of the message
    mbox[1] = MBOX_REQUEST;             // this is a request message

    mbox[2] = MBOX_TAG_CLOCK_SET_TURBO;
    mbox[3] = 8;                        // buffer size
    mbox[4] = 8;                        // len

    mbox[5] = 0;                        // id
    mbox[6] = level ? 1 : 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    if(mbox[5] != 0)
    {
        return -1;
    }

    return mbox[6];
}

int bcm283x_mbox_clock_get_state(int id)
{
    mbox[0] = 8*4;                       // length of the message
    mbox[1] = MBOX_REQUEST;              // this is a request message

    mbox[2] = MBOX_TAG_CLOCK_GET_STATE;
    mbox[3] = 8;                         // buffer size
    mbox[4] = 4;                         // len

    mbox[5] = id;                        // id
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    if(mbox[5] != id)
    {
        return -1;
    }

    return (mbox[6] & 0x3);
}

int bcm283x_mbox_clock_set_state(int id, int state)
{
    mbox[0] = 8*4;                      // length of the message
    mbox[1] = MBOX_REQUEST;             // this is a request message

    mbox[2] = MBOX_TAG_CLOCK_SET_STATE;
    mbox[3] = 8;                        // buffer size
    mbox[4] = 8;                        // len

    mbox[5] = id;                       // id
    mbox[6] = state & 0x3;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    if(mbox[5] != id)
    {
        return -1;
    }

    return (mbox[6] & 0x3);
}

int bcm283x_mbox_clock_get_rate(int id)
{
    mbox[0] = 8*4;                      // length of the message
    mbox[1] = MBOX_REQUEST;             // this is a request message

    mbox[2] = MBOX_TAG_CLOCK_GET_RATE;
    mbox[3] = 8;                        // buffer size
    mbox[4] = 4;                        // len

    mbox[5] = id;                       // id
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    if(mbox[5] != id)
    {
        return -1;
    }

    return mbox[6];
}

int bcm283x_mbox_clock_set_rate(int id, int rate)
{
    mbox[0] = 8*4;                      // length of the message
    mbox[1] = MBOX_REQUEST;             // this is a request message

    mbox[2] = MBOX_TAG_CLOCK_SET_RATE;
    mbox[3] = 8;                        // buffer size
    mbox[4] = 8;                        // len

    mbox[5] = id;                       // id
    mbox[6] = rate;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    if(mbox[5] != id)
    {
        return -1;
    }

    return mbox[6];
}

int bcm283x_mbox_clock_get_max_rate(int id)
{
    mbox[0] = 8*4;                          // length of the message
    mbox[1] = MBOX_REQUEST;                 // this is a request message

    mbox[2] = MBOX_TAG_CLOCK_GET_MAX_RATE;
    mbox[3] = 8;                            // buffer size
    mbox[4] = 4;                            // len

    mbox[5] = id;                           // id
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    if(mbox[5] != id)
    {
        return -1;
    }

    return mbox[6];
}

int bcm283x_mbox_clock_get_min_rate(int id)
{
    mbox[0] = 8*4;                          // length of the message
    mbox[1] = MBOX_REQUEST;                 // this is a request message

    mbox[2] = MBOX_TAG_CLOCK_GET_MIN_RATE;
    mbox[3] = 8;                            // buffer size
    mbox[4] = 4;                            // len

    mbox[5] = id;                           // id
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    if(mbox[5] != id)
    {
        return -1;
    }

    return mbox[6];
}

int bcm283x_mbox_power_get_state(int id)
{
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message

    mbox[2] = MBOX_TAG_POWER_GET_STATE;
    mbox[3] = 8;                    // buffer size
    mbox[4] = 4;                    // len

    mbox[5] = id;                   // id
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    if(mbox[5] != id)
    {
        return -1;
    }

    return (mbox[6] & 0x3);
}

int bcm283x_mbox_power_set_state(int id, int state)
{
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message

    mbox[2] = MBOX_TAG_POWER_SET_STATE;
    mbox[3] = 8;                    // buffer size
    mbox[4] = 8;                    // len

    mbox[5] = id;                    // id
    mbox[6] = state & 0x3;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    if(mbox[5] != id)
    {
        return -1;
    }

    return (mbox[6] & 0x3);
}

int bcm283x_mbox_temp_get(void)
{
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message

    mbox[2] = MBOX_TAG_TEMP_GET;
    mbox[3] = 8;                    // buffer size
    mbox[4] = 4;                    // len

    mbox[5] = 0;                    //id
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    if(mbox[5] != 0)
    {
        return -1;
    }

    return mbox[6];
}

int bcm283x_mbox_temp_get_max(void)
{
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message

    mbox[2] = MBOX_TAG_TEMP_GET_MAX;
    mbox[3] = 8;                    // buffer size
    mbox[4] = 4;                    // len

    mbox[5] = 0;                    // id
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);

    if(mbox[5] != 0)
    {
        return -1;
    }

    return mbox[6];
}
