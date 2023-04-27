/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fgdma_selftest.c
 * Date: 2022-05-20 13:39:27
 * LastEditTime: 2022-05-20 13:39:27
 * Description:  This file is for self test implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/11/5    init commit
 * 1.1   zhugengyu  2022/5/16    modify according to tech manual.
 */
/***************************** Include Files *********************************/
#include <string.h>

#include "fdebug.h"

#include "fgdma_hw.h"
#include "fgdma.h"
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FGDMA_DEBUG_TAG "GDMA-TEST"
#define FGDMA_ERROR(format, ...)   FT_DEBUG_PRINT_E(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGDMA_WARN(format, ...)    FT_DEBUG_PRINT_W(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGDMA_INFO(format, ...)    FT_DEBUG_PRINT_I(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGDMA_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/****************************************************************************/
/**
 * @name: FGdmaDumpRegisterVals
 * @msg: 打印当前的GDMA寄存器值
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 * @param {u32} max_chan, 打印从 0 ~ max_chan 的通道寄存器值
 */
void FGdmaDumpRegisterVals(uintptr base_addr, u32 max_chan)
{
    FGDMA_DEBUG("ctrl[0x%x]: 0x%x", FGDMA_CTL_OFFSET, FGDMA_READREG(base_addr, FGDMA_CTL_OFFSET));
    FGDMA_DEBUG("state[0x%x]: 0x%x", FGDMA_INTR_STATE_OFFSET, FGDMA_READREG(base_addr, FGDMA_INTR_STATE_OFFSET));
    FGDMA_DEBUG("intr[0x%x]: 0x%x", FGDMA_INTR_CTRL_OFFSET, FGDMA_READREG(base_addr, FGDMA_INTR_CTRL_OFFSET));
    FGDMA_DEBUG("lp[0x%x] : 0x%x", FGDMA_LP_OFFSET, FGDMA_READREG(base_addr, FGDMA_LP_OFFSET));
    FGDMA_DEBUG("qos[0x%x] : 0x%x", FGDMA_QOS_CFG_OFFSET, FGDMA_READREG(base_addr, FGDMA_QOS_CFG_OFFSET));

    for (u32 chan = 0; chan <= max_chan; chan++)
    {
        FGDMA_DEBUG("chan-%d", chan);
        FGDMA_DEBUG("   ctrl[0x%x]: 0x%x", FGDMA_CHX_CTL_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_CTL_OFFSET(chan)));
        FGDMA_DEBUG("   mode[0x%x]: 0x%x", FGDMA_CHX_MODE_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_MODE_OFFSET(chan)));
        FGDMA_DEBUG("   intr[0x%x]: 0x%x", FGDMA_CHX_INT_CTRL_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_INT_CTRL_OFFSET(chan)));
        FGDMA_DEBUG("   state[0x%x]: 0x%x", FGDMA_CHX_INT_STATE_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_INT_STATE_OFFSET(chan)));
        FGDMA_DEBUG("   lvi[0x%x]: 0x%x", FGDMA_CHX_LVI_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_LVI_OFFSET(chan)));
        FGDMA_DEBUG("   ts[0x%x]: 0x%x", FGDMA_CHX_TS_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_TS_OFFSET(chan)));
        FGDMA_DEBUG("   src-up[0x%x]: 0x%x", FGDMA_CHX_UPSADDR_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_UPSADDR_OFFSET(chan)));
        FGDMA_DEBUG("   src-low[0x%x]: 0x%x", FGDMA_CHX_LWSADDR_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_LWSADDR_OFFSET(chan)));
        FGDMA_DEBUG("   dst-up[0x%x]: 0x%x", FGDMA_CHX_UPDADDR_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_UPDADDR_OFFSET(chan)));
        FGDMA_DEBUG("   dst-low[0x%x]: 0x%x", FGDMA_CHX_LWDADDR_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_LWDADDR_OFFSET(chan)));
        FGDMA_DEBUG("   xfer[0x%x]: 0x%x", FGDMA_CHX_XFER_CFG_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_XFER_CFG_OFFSET(chan)));
        FGDMA_DEBUG("   lpc[0x%x]: 0x%x", FGDMA_CHX_LCP_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_LCP_OFFSET(chan)));
        FGDMA_DEBUG("   sec[0x%x]: 0x%x", FGDMA_CHX_SECCTL_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_SECCTL_OFFSET(chan)));
        FGDMA_DEBUG("   atst[0x%x]: 0x%x", FGDMA_CHX_SEC_ATST_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_SEC_ATST_OFFSET(chan)));
        FGDMA_DEBUG("   nsid[0x%x]: 0x%x", FGDMA_CHX_NSID_STRMID_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_NSID_STRMID_OFFSET(chan)));
        FGDMA_DEBUG("   aw[0x%x]: 0x%x", FGDMA_CHX_AW_CFG_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_AW_CFG_OFFSET(chan)));
        FGDMA_DEBUG("   ar[0x%x]: 0x%x", FGDMA_CHX_AR_CFG_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_AR_CFG_OFFSET(chan)));
        FGDMA_DEBUG("   resp[0x%x]: 0x%x", FGDMA_CHX_SECRSP_OFFSET(chan), FGDMA_READREG(base_addr, FGDMA_CHX_SECRSP_OFFSET(chan)));
    }

    return;
}