/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-02-16     Tuber             first version
 */

#ifndef __DRV_ETH_H__
#define __DRV_ETH_H__
#include <rtthread.h>

#define ETH_BUF_SIZE 1536

int rt_hw_eth_init(void);

#endif
