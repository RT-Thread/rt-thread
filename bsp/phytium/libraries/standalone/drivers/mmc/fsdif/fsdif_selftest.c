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
 * FilePath: fsdif_selftest.c
 * Date: 2022-06-02 11:49:44
 * LastEditTime: 2022-06-02 11:49:45
 * Description:  This file is for sdif self-test function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 * 2.0   zhugengyu  2023/9/16    rename as sdif, support SD 3.0 and rework clock timing
 */
/***************************** Include Files *********************************/

#include "fio.h"
#include "fdrivers_port.h"
#include "fassert.h"
#include "ftypes.h"

#include "fsdif_hw.h"
#include "fsdif.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDIF_DEBUG_TAG "FSDIF-TEST"
#define FSDIF_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)

#define FSDIF_DUMPER(base_addr, reg_off, reg_name) \
    FSDIF_DEBUG("\t\t[%s]@0x%x\t=\t0x%x", reg_name, (reg_off), FSDIF_READ_REG((base_addr), (reg_off)))
/************************** Function Prototypes ******************************/

/*****************************************************************************/

/**
 * @name: FSdifDumpRegister
 * @msg: Dump all register value of SDIF instance
 * @return {NONE}
 * @param {uintptr} base_addr, base address of SDIF controller
 */
void FSdifDumpRegister(uintptr base_addr)
{
    FSDIF_DEBUG("Dump register info @0x%x", base_addr);
    FSDIF_DUMPER(base_addr, FSDIF_CNTRL_OFFSET, "cntrl");
    FSDIF_DUMPER(base_addr, FSDIF_PWREN_OFFSET, "pwren");
    FSDIF_DUMPER(base_addr, FSDIF_CLKDIV_OFFSET, "clkdiv");
    FSDIF_DUMPER(base_addr, FSDIF_CLKENA_OFFSET, "clkena");
    FSDIF_DUMPER(base_addr, FSDIF_TMOUT_OFFSET, "tmout");
    FSDIF_DUMPER(base_addr, FSDIF_CTYPE_OFFSET, "ctype");
    FSDIF_DUMPER(base_addr, FSDIF_BLK_SIZ_OFFSET, "blksz");
    FSDIF_DUMPER(base_addr, FSDIF_BYT_CNT_OFFSET, "blkcnt");
    FSDIF_DUMPER(base_addr, FSDIF_INT_MASK_OFFSET, "intmask");
    FSDIF_DUMPER(base_addr, FSDIF_CMD_ARG_OFFSET, "cmdarg");
    FSDIF_DUMPER(base_addr, FSDIF_CMD_OFFSET, "cmd");
    FSDIF_DUMPER(base_addr, FSDIF_RESP0_OFFSET, "resp0");
    FSDIF_DUMPER(base_addr, FSDIF_RESP1_OFFSET, "reps1");
    FSDIF_DUMPER(base_addr, FSDIF_RESP2_OFFSET, "resp2");
    FSDIF_DUMPER(base_addr, FSDIF_RESP3_OFFSET, "resp3");
    FSDIF_DUMPER(base_addr, FSDIF_MASKED_INTS_OFFSET, "maskints");
    FSDIF_DUMPER(base_addr, FSDIF_RAW_INTS_OFFSET, "rawints");
    FSDIF_DUMPER(base_addr, FSDIF_STATUS_OFFSET, "status");
    FSDIF_DUMPER(base_addr, FSDIF_FIFOTH_OFFSET, "fifoth");
    FSDIF_DUMPER(base_addr, FSDIF_CARD_DETECT_OFFSET, "carddet");
    FSDIF_DUMPER(base_addr, FSDIF_CARD_WRTPRT_OFFSET, "wrtprt");
    FSDIF_DUMPER(base_addr, FSDIF_CKSTS_OFFSET, "cksts");
    FSDIF_DUMPER(base_addr, FSDIF_TRAN_CARD_CNT_OFFSET, "trans_cardcnt");
    FSDIF_DUMPER(base_addr, FSDIF_TRAN_FIFO_CNT_OFFSET, "trans_fifocnt");
    FSDIF_DUMPER(base_addr, FSDIF_DEBNCE_OFFSET, "debnce");
    FSDIF_DUMPER(base_addr, FSDIF_UID_OFFSET, "uid");
    FSDIF_DUMPER(base_addr, FSDIF_VID_OFFSET, "vid");
    FSDIF_DUMPER(base_addr, FSDIF_HWCONF_OFFSET, "hwconf");
    FSDIF_DUMPER(base_addr, FSDIF_UHS_REG_OFFSET, "uhsreg");
    FSDIF_DUMPER(base_addr, FSDIF_CARD_RESET_OFFSET, "cardreset");
    FSDIF_DUMPER(base_addr, FSDIF_BUS_MODE_OFFSET, "busmode");
    FSDIF_DUMPER(base_addr, FSDIF_DESC_LIST_ADDRL_OFFSET, "descaddrl");
    FSDIF_DUMPER(base_addr, FSDIF_DESC_LIST_ADDRH_OFFSET, "descaddrh");
    FSDIF_DUMPER(base_addr, FSDIF_DMAC_STATUS_OFFSET, "dmacstatus");
    FSDIF_DUMPER(base_addr, FSDIF_DMAC_INT_EN_OFFSET, "dmacinten");
    FSDIF_DUMPER(base_addr, FSDIF_CUR_DESC_ADDRL_OFFSET, "curdescaddrl");
    FSDIF_DUMPER(base_addr, FSDIF_CUR_DESC_ADDRH_OFFSET, "curdescaddrh");
    FSDIF_DUMPER(base_addr, FSDIF_CUR_BUF_ADDRL_OFFSET, "curbufaddrl");
    FSDIF_DUMPER(base_addr, FSDIF_CUR_BUF_ADDRH_OFFSET, "curbufaddrh");
    FSDIF_DUMPER(base_addr, FSDIF_CARD_THRCTL_OFFSET, "card_thrctl");
    FSDIF_DUMPER(base_addr, FSDIF_CLK_SRC_OFFSET, "clock_src");
    FSDIF_DUMPER(base_addr, FSDIF_EMMC_DDR_REG_OFFSET, "emmcddr");
    FSDIF_DUMPER(base_addr, FSDIF_ENABLE_SHIFT_OFFSET, "enableshift");
}

/**
 * @name: FSdifDumpCmdInfo
 * @msg: Dump command and data info
 * @return {NONE}
 * @param {FSdifCmdData *const} cmd_data, info data of SD command and data
 */
void FSdifDumpCmdInfo(FSdifCmdData *const cmd_data)
{
    FSDIF_DEBUG("cmd struct @%p", cmd_data);
    FSDIF_DEBUG("   opcode: %d", cmd_data->cmdidx);
    FSDIF_DEBUG("   arg: 0x%x", cmd_data->cmdarg);
    FSDIF_DEBUG("   resp@%p: 0x%x 0x%x 0x%x 0x%x",
                cmd_data->response,
                cmd_data->response[0],
                cmd_data->response[1],
                cmd_data->response[2],
                cmd_data->response[3]);
    FSDIF_DEBUG("   flag: 0x%x", cmd_data->flag);
    FSDIF_DEBUG("   data @%p", cmd_data->data_p);

    if (cmd_data->data_p)
    {
        FSDIF_DEBUG("   buf: %p, len: %d", cmd_data->data_p->buf_dma,
                    cmd_data->data_p->datalen);
        FSDIF_DEBUG("   blk sz: %d", cmd_data->data_p->blksz);
        FSDIF_DEBUG("   blk cnt: %d", cmd_data->data_p->blkcnt);
    }
}