/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-24     Wayne        first version
 */

#ifndef SYNOP_GMAC_PLAT_H
#define SYNOP_GMAC_PLAT_H 1

#include <rtthread.h>
#include "synopGMAC_types.h"
#include "drv_common.h"

#define DEFAULT_DELAY_VARIABLE  10
#define DEFAULT_LOOP_VARIABLE   1000

/* Error Codes */
#define ESYNOPGMACNOERR   0
#define ESYNOPGMACNOMEM   1
#define ESYNOPGMACPHYERR  2
#define ESYNOPGMACBUSY    3

#define TR0(fmt, args...) rt_kprintf("SynopGMAC: " fmt, ##args)

//#define DEBUG
#ifdef DEBUG
    #undef TR
    #define TR(fmt, args...) rt_kprintf("SynopGMAC: " fmt, ##args)
#else
    #define TR(fmt, args...) /* not debugging: nothing */
#endif

u32 synopGMACReadReg(u32 RegBase, u32 RegOffset);
void synopGMACWriteReg(u32 RegBase, u32 RegOffset, u32 RegData);
void synopGMACSetBits(u32 RegBase, u32 RegOffset, u32 BitPos);
void  synopGMACClearBits(u32 RegBase, u32 RegOffset, u32 BitPos);
bool synopGMACCheckBits(u32 RegBase, u32 RegOffset, u32 BitPos);
void plat_delay(u32);

#endif
