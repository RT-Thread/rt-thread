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
 * FilePath: fddma_selftest.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:24:47
 * Description:  This file is for ddma self test
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/5/13    init commit
 */

/***************************** Include Files *********************************/
#include <string.h>

#include "fkernel.h"
#include "fparameters.h"
#include "fassert.h"
#include "fdebug.h"

#include "fddma_hw.h"
#include "fddma.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FDDMA_DEBUG_TAG "DDMA-TEST"
#define FDDMA_ERROR(format, ...)   FT_DEBUG_PRINT_E(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_WARN(format, ...)   FT_DEBUG_PRINT_W(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_INFO(format, ...)    FT_DEBUG_PRINT_I(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)

#define FDDMA_DUMPER(base_addr, reg_off, reg_name) \
    FDDMA_DEBUG("\t\t[%s]@0x%x\t=\t0x%x", reg_name, (reg_off), FDdmaReadReg((base_addr), (reg_off)))
/************************** Function Prototypes ******************************/

/****************************************************************************/


void FDdmaDumpRegisters(uintptr base_addr)
{
    FDDMA_DEBUG("ddma@0x%x", base_addr);
    FDDMA_DUMPER(base_addr, FDDMA_CTL_OFFSET, "ctl");
    FDDMA_DUMPER(base_addr, FDDMA_CHAN_0_3_CFG_OFFSET, "chan_0_3");
    FDDMA_DUMPER(base_addr, FDDMA_STA_OFFSET, "sta");
    FDDMA_DUMPER(base_addr, FDDMA_MASK_INTR_OFFSET, "mask_intr");
    FDDMA_DUMPER(base_addr, FDDMA_UP_AXI_AW_CFG_OFFSET, "up_axi_aw");
    FDDMA_DUMPER(base_addr, FDDMA_UP_AXI_AR_CFG_OFFSET, "up_axi_ar");
    FDDMA_DUMPER(base_addr, FDDMA_DOWN_AXI_AW_CFG_OFFSET, "dw_axi_aw");
    FDDMA_DUMPER(base_addr, FDDMA_DOWN_AXI_AR_CFG_OFFSET, "dw_axi_ar");
    FDDMA_DUMPER(base_addr, FDDMA_CHAN_BIND_OFFSET, "chan_bind");
    FDDMA_DUMPER(base_addr, FDDMA_GCAP_OFFSET, "gcap");
    FDDMA_DUMPER(base_addr, FDDMA_CHAN_4_7_CFG_OFFSET, "chan_4_7");
}

void FDdmaDumpChanRegisters(uintptr base_addr, FDdmaChanIndex chan)
{
    FDDMA_DEBUG("\tchan-%d", chan);
    FDDMA_DUMPER(base_addr, FDDMA_CHAN_DDR_UP_ADDR_OFFSET(chan), "ddr_up");
    FDDMA_DUMPER(base_addr, FDDMA_CHAN_DDR_LOW_ADDR_OFFSET(chan), "ddr_low");
    FDDMA_DUMPER(base_addr, FDDMA_CHAN_DEV_ADDR_OFFSET(chan), "dev");
    FDDMA_DUMPER(base_addr, FDDMA_CHAN_TS_OFFSET(chan), "ts");
    FDDMA_DUMPER(base_addr, FDDMA_CHAN_CRT_UP_ADDR_OFFSET(chan), "crt_up");
    FDDMA_DUMPER(base_addr, FDDMA_CHAN_CRT_LOW_ADDR_OFFSET(chan), "crt_low");
    FDDMA_DUMPER(base_addr, FDDMA_CHAN_CTL_OFFSET(chan), "ctl");
    FDDMA_DUMPER(base_addr, FDDMA_CHAN_STS_OFFSET(chan), "sts");
    FDDMA_DUMPER(base_addr, FDDMA_CHAN_TIMEOUT_CNT_OFFSET(chan), "cnt");
}

