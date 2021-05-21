/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-11     Carl        the first version
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <board.h>
#include <rtdevice.h>
#include <rtthread.h>
#include "ft_can.h"

    struct ft2004_can
    {
        const char *name;
        FCan_t can_handle;
        struct rt_semaphore recv_semaphore;
        struct rt_can_device device; /* inherit from can device */
    };

    int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif // !
