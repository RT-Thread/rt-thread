/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH          the first version
 */

#ifndef __DRV_ETH_H__
#define __DRV_ETH_H__
#include "rthw.h"
#include "rtthread.h"
#include "ch32v30x_eth.h"


/* MII/MDI interface select */
#define PHY_ADDRESS 0x01
#define USE10BASE_T

#ifndef USE10BASE_T
    #define USE_GIGA_MAC
    #ifndef USE_GIGA_MAC
        #define USE_FAST_MAC
    #endif
#endif

#define ETH_RXBUFNB        6
#define ETH_TXBUFNB        6

typedef struct
{
    u32 length;
    u32 buffer;
    ETH_DMADESCTypeDef *descriptor;
}FrameTypeDef;

#endif
