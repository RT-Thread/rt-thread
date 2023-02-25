/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-28     shelton      first version
 */

#ifndef __DRV_USBFS_H__
#define __DRV_USBFS_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "usb_core.h"

struct at32_usbfs {
    char *name;
    otg_core_type *p_otg_core;
    otg_id_type id;
    IRQn_Type irqn;
};

#endif /* __DRV_USBFS_H__ */

/******************* end of file *******************/
