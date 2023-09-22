/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-10-11     zmshahaha    move from <rtdef.h>
 */

#ifndef __NET_H__
#define __NET_H__

#include <rtdef.h>

/* net interface device*/
#define RT_DEVICE_CTRL_NETIF_GETMAC     (RT_DEVICE_CTRL_BASE(NetIf) + 1)            /**< get mac address */

#endif /* __NET_H__ */
