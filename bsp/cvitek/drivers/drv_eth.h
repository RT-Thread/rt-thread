/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/04/25     flyingcys    first version
 */
#ifndef __DRV_ETH_H__
#define __DRV_ETH_H__

#include "mmio.h"
#include "dw_eth_mac.h"
#include "cvi_eth_phy.h"
#include "drv_ioremap.h"

#define DW_MAC_BASE                 DRV_IOREMAP((void *)0x04070000, 0x10000)
#define DW_MAC_IRQ                  31

#endif /* __DRV_ETH_H__ */
