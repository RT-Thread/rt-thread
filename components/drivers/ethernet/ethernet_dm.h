/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#ifndef __ETHERNET_DM_H__
#define __ETHERNET_DM_H__

#include <rtthread.h>

#include <netif/ethernetif.h>

void ethernet_random_addr(struct eth_device *eth, rt_uint8_t *addr);

#endif /* __ETHERNET_DM_H__ */
