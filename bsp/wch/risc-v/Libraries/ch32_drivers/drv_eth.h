/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-25       IceBear003   the first version
 */

#ifndef __DRV_ETH_H__
#define __DRV_ETH_H__

#include <rtthread.h>
#include <rtdevice.h>

#define ETH_RX_BUF_COUNT 7
#define ETH_TX_BUF_COUNT 2

int rt_hw_eth_init(void);

#endif