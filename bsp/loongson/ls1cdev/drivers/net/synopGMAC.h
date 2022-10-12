/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-24     chinesebear  first version
 */

#ifndef __SYNOPGMAC__H
#define __SYNOPGMAC__H

#include "synopGMAC_network_interface.h"
#include "synopGMAC_Host.h"
#include "synopGMAC_Dev.h"
#include "synopGMAC_plat.h"
#include "mii.h"
#include "synopGMAC_types.h"

int rt_hw_eth_init(void);

#endif  /*__SYNOPGMAC__H*/
