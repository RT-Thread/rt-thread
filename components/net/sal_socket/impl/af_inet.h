/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-25     ChenYong     First version
 */

#ifndef __AF_INET_H__
#define __AF_INET_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SAL_USING_LWIP

/* Set lwIP network interface device protocol family information  */
int sal_lwip_netdev_set_pf_info(struct netdev *netdev);

#endif /* SAL_USING_LWIP */

#ifdef SAL_USING_AT

/* Set AT network interface device protocol family information */
int sal_at_netdev_set_pf_info(struct netdev *netdev);

#endif /* SAL_USING_AT */

#ifdef __cplusplus
}
#endif

#endif /* __AF_INET_H__ */
