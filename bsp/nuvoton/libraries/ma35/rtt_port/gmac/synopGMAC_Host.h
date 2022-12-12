/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-24     chinesebear  first version
 */

#ifndef SYNOP_GMAC_HOST_H
#define SYNOP_GMAC_HOST_H 1

#include "synopGMAC_plat.h"
#include "synopGMAC_Dev.h"
#include "mii.h"
#include "synopGMAC_network_interface.h"

typedef struct
{
    uint32_t u32TxDescSize;
    uint32_t u32RxDescSize;

    DmaDesc *psRXDescs;
    PKT_FRAME_T *psRXFrames;
    DmaDesc *psTXDescs;
    PKT_FRAME_T *psTXFrames;
} GMAC_MEMMGR_T;

typedef struct
{
    /*Device Dependent Data structur*/
    synopGMACdevice *m_gmacdev;
    GMAC_MEMMGR_T  *m_gmacmemmgr;
    struct mii_if_info m_mii;
} synopGMACNetworkAdapter;

#endif
