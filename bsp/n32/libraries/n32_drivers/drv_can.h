/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#include <rtdevice.h>
#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

struct n32_baud_rate_tab
{
    uint32_t baud_rate;
    uint16_t PRESCALE;
    uint8_t  RSJW;
    uint8_t  TBS1;
    uint8_t  TBS2;
    uint8_t  Reserved;
};

#define N32_CAN_BAUD_DEF(rate, rsjw, tbs1, tbs2, prescale) \
{                                                          \
    .baud_rate = rate,                                     \
    .RSJW = rsjw,                                          \
    .TBS1 = tbs1,                                          \
    .TBS2 = tbs2,                                          \
    .PRESCALE = prescale                                   \
}

/* n32 can device */
struct n32_can
{
    char *name;
    CAN_Module *CANx;
    CAN_InitType can_init;
    CAN_FilterInitType FilterConfig;
    struct rt_can_device device;     /* inherit from can device */
};

int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_CAN_H__ */
