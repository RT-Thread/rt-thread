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
 * FilePath: fspim_selftest.c
 * Date: 2022-07-21 13:21:43
 * LastEditTime: 2022-07-21 13:21:44
 * Description:  This file is for providing spim self test func.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/3   init commit
 * 1.1   zhugengyu  2022/4/15   support test mode
 */
/***************************** Include Files *********************************/
#include "fio.h"
#include "fdebug.h"
#include "fassert.h"
#include "ftypes.h"

#include "fspim_hw.h"
#include "fspim.h"
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSPIM_DEBUG_TAG "SPIM-TEST"
#define FSPIM_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_WARN(format, ...)   FT_DEBUG_PRINT_W(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_INFO(format, ...)    FT_DEBUG_PRINT_I(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)

#define FSPIM_DUMPER(base_addr, reg_off, reg_name) \
    FSPIM_DEBUG("\t\t[%s]@0x%x\t=\t0x%x", reg_name, (reg_off), FSPIM_READ_REG32((base_addr), (reg_off)))
/************************** Function Prototypes ******************************/

/*****************************************************************************/

void FSpimDumpRegister(uintptr base_addr)
{
    FSPIM_DEBUG("Dump register info @0x%x", base_addr);
    FSPIM_DUMPER(base_addr, FSPIM_CTRL_R0_OFFSET, "ctrl_r0");
    FSPIM_DUMPER(base_addr, FSPIM_CTRL_R1_OFFSET, "ctrl_r1");
    FSPIM_DUMPER(base_addr, FSPIM_SSIENR_OFFSET, "ssienr");
    FSPIM_DUMPER(base_addr, FSPIM_MWCR_OFFSET, "mwcr");
    FSPIM_DUMPER(base_addr, FSPIM_SER_OFFSET, "ser");
    FSPIM_DUMPER(base_addr, FSPIM_BAUD_R_OFFSET, "baud");
    FSPIM_DUMPER(base_addr, FSPIM_TXFTL_R_OFFSET, "txftl");
    FSPIM_DUMPER(base_addr, FSPIM_RXFTL_R_OFFSET, "rxftl");
    FSPIM_DUMPER(base_addr, FSPIM_TXFLR_OFFSET, "txflr");
    FSPIM_DUMPER(base_addr, FSPIM_RXFLR_OFFSET, "rxflr");
    FSPIM_DUMPER(base_addr, FSPIM_SR_OFFSET, "sr");
    FSPIM_DUMPER(base_addr, FSPIM_IMR_OFFSET, "imr");
    FSPIM_DUMPER(base_addr, FSPIM_ISR_OFFSET, "isr");
    FSPIM_DUMPER(base_addr, FSPIM_RIS_R_OFFSET, "ris_r");
    FSPIM_DUMPER(base_addr, FSPIM_DMA_CR_OFFSET, "cr");
    FSPIM_DUMPER(base_addr, FSPIM_DMA_TDLR_OFFSET, "tdlr");
    FSPIM_DUMPER(base_addr, FSPIM_DMA_RDLR_OFFSET, "rdlr");
    FSPIM_DUMPER(base_addr, FSPIM_IDR_OFFSET, "idr");
    FSPIM_DUMPER(base_addr, FSPIM_RX_SAMPLE_DLY_OFFSET, "rx_sample");
    FSPIM_DUMPER(base_addr, FSPIM_CS_OFFSET, "cs");
}