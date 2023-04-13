/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-28     shelton      first version
 */

#ifndef __DRV_USBD_H__
#define __DRV_USBD_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

#if defined(BSP_USING_USBD)
#include "usbd_core.h"

struct at32_usbd {
    char *name;
    usbd_core_type *p_usbd_core;
    IRQn_Type irqn;
};
#endif
#endif /* __DRV_USBD_H__ */

/******************* end of file *******************/
