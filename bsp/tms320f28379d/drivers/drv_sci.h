/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-02-02     xuzhuoyi     first version
 */

#ifndef __DRV_SCI_H__
#define __DRV_SCI_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include "F2837xD_device.h"
#include "F2837xD_sci.h"

int rt_hw_sci_init(void);

/* c28x uart dirver class */
struct c28x_uart
{
    const char *name;
    struct SCI_REGS *sci_regs;
    struct rt_serial_device serial;
};

#endif  /* __DRV_SCI_H__ */
