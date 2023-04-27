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
 * FilePath: fsdio_selftest.c
 * Date: 2022-06-02 11:49:44
 * LastEditTime: 2022-06-02 11:49:45
 * Description:  This file is for SDIO self-test function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 */
/***************************** Include Files *********************************/

#include "fio.h"
#include "fdebug.h"
#include "fassert.h"
#include "ftypes.h"

#include "fsdio_hw.h"
#include "fsdio.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDIO_DEBUG_TAG "FSDIO-TEST"
#define FSDIO_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)

#define FSDIO_DUMPER(base_addr, reg_off, reg_name) \
    FSDIO_DEBUG("\t\t[%s]@0x%x\t=\t0x%x", reg_name, (reg_off), FSDIO_READ_REG((base_addr), (reg_off)))
/************************** Function Prototypes ******************************/

/*****************************************************************************/

/**
 * @name: FSdioDumpRegister
 * @msg: Dump all register value of SDIO instance
 * @return {NONE}
 * @param {uintptr} base_addr, base address of SDIO controller
 */
void FSdioDumpRegister(uintptr base_addr)
{
    FSDIO_DEBUG("Dump register info @0x%x", base_addr);
    FSDIO_DUMPER(base_addr, FSDIO_CNTRL_OFFSET, "cntrl");
    FSDIO_DUMPER(base_addr, FSDIO_PWREN_OFFSET, "pwren");
    FSDIO_DUMPER(base_addr, FSDIO_CLKDIV_OFFSET, "clkdiv");
    FSDIO_DUMPER(base_addr, FSDIO_CLKENA_OFFSET, "clkena");
    FSDIO_DUMPER(base_addr, FSDIO_TMOUT_OFFSET, "tmout");
    FSDIO_DUMPER(base_addr, FSDIO_CTYPE_OFFSET, "ctype");
    FSDIO_DUMPER(base_addr, FSDIO_BLK_SIZ_OFFSET, "blksz");
    FSDIO_DUMPER(base_addr, FSDIO_BYT_CNT_OFFSET, "blkcnt");
    FSDIO_DUMPER(base_addr, FSDIO_INT_MASK_OFFSET, "intmask");
    FSDIO_DUMPER(base_addr, FSDIO_CMD_ARG_OFFSET, "cmdarg");
    FSDIO_DUMPER(base_addr, FSDIO_CMD_OFFSET, "cmd");
    FSDIO_DUMPER(base_addr, FSDIO_RESP0_OFFSET, "resp0");
    FSDIO_DUMPER(base_addr, FSDIO_RESP1_OFFSET, "reps1");
    FSDIO_DUMPER(base_addr, FSDIO_RESP2_OFFSET, "resp2");
    FSDIO_DUMPER(base_addr, FSDIO_RESP3_OFFSET, "resp3");
    FSDIO_DUMPER(base_addr, FSDIO_MASKED_INTS_OFFSET, "maskints");
    FSDIO_DUMPER(base_addr, FSDIO_RAW_INTS_OFFSET, "rawints");
    FSDIO_DUMPER(base_addr, FSDIO_STATUS_OFFSET, "status");
    FSDIO_DUMPER(base_addr, FSDIO_FIFOTH_OFFSET, "fifoth");
    FSDIO_DUMPER(base_addr, FSDIO_CARD_DETECT_OFFSET, "carddet");
    FSDIO_DUMPER(base_addr, FSDIO_CARD_WRTPRT_OFFSET, "wrtprt");
    FSDIO_DUMPER(base_addr, FSDIO_GPIO_OFFSET, "gpio");
    FSDIO_DUMPER(base_addr, FSDIO_TRAN_CARD_CNT_OFFSET, "trans_cardcnt");
    FSDIO_DUMPER(base_addr, FSDIO_TRAN_FIFO_CNT_OFFSET, "trans_fifocnt");
    FSDIO_DUMPER(base_addr, FSDIO_DEBNCE_OFFSET, "debnce");
    FSDIO_DUMPER(base_addr, FSDIO_UID_OFFSET, "uid");
    FSDIO_DUMPER(base_addr, FSDIO_VID_OFFSET, "vid");
    FSDIO_DUMPER(base_addr, FSDIO_HWCONF_OFFSET, "hwconf");
    FSDIO_DUMPER(base_addr, FSDIO_UHS_REG_OFFSET, "uhsreg");
    FSDIO_DUMPER(base_addr, FSDIO_CARD_RESET_OFFSET, "cardreset");
    FSDIO_DUMPER(base_addr, FSDIO_BUS_MODE_OFFSET, "busmode");
    FSDIO_DUMPER(base_addr, FSDIO_DESC_LIST_ADDRL_OFFSET, "descaddrl");
    FSDIO_DUMPER(base_addr, FSDIO_DESC_LIST_ADDRH_OFFSET, "descaddrh");
    FSDIO_DUMPER(base_addr, FSDIO_DMAC_STATUS_OFFSET, "dmacstatus");
    FSDIO_DUMPER(base_addr, FSDIO_DMAC_INT_EN_OFFSET, "dmacinten");
    FSDIO_DUMPER(base_addr, FSDIO_CUR_DESC_ADDRL_OFFSET, "curdescaddrl");
    FSDIO_DUMPER(base_addr, FSDIO_CUR_DESC_ADDRH_OFFSET, "curdescaddrh");
    FSDIO_DUMPER(base_addr, FSDIO_CUR_BUF_ADDRL_OFFSET, "curbufaddrl");
    FSDIO_DUMPER(base_addr, FSDIO_CUR_BUF_ADDRH_OFFSET, "curbufaddrh");
    FSDIO_DUMPER(base_addr, FSDIO_CARD_THRCTL_OFFSET, "card_thrctl");
    FSDIO_DUMPER(base_addr, FSDIO_UHS_REG_EXT_OFFSET, "uhsregext");
    FSDIO_DUMPER(base_addr, FSDIO_EMMC_DDR_REG_OFFSET, "emmcddr");
    FSDIO_DUMPER(base_addr, FSDIO_ENABLE_SHIFT_OFFSET, "enableshift");
}

/**
 * @name: FSdioDumpCmdInfo
 * @msg: Dump command and data info
 * @return {NONE}
 * @param {FSdioCmdData *const} cmd_data, info data of SD command and data
 */
void FSdioDumpCmdInfo(FSdioCmdData *const cmd_data)
{
    FSDIO_DEBUG("cmd struct @%p", cmd_data);
    FSDIO_DEBUG("   opcode: %d", cmd_data->cmdidx);
    FSDIO_DEBUG("   arg: 0x%x", cmd_data->cmdarg);
    FSDIO_DEBUG("   resp@%p: 0x%x 0x%x 0x%x 0x%x",
                cmd_data->response,
                cmd_data->response[0],
                cmd_data->response[1],
                cmd_data->response[2],
                cmd_data->response[3]);
    FSDIO_DEBUG("   flag: 0x%x", cmd_data->flag);
    FSDIO_DEBUG("   data @%p", cmd_data->data_p);

    if (cmd_data->data_p)
    {
        FSDIO_DEBUG("   buf: %p, len: %d", cmd_data->data_p->buf,
                    cmd_data->data_p->datalen);
        FSDIO_DEBUG("   blk sz: %d", cmd_data->data_p->blksz);
        FSDIO_DEBUG("   blk cnt: %d", cmd_data->data_p->blkcnt);
    }
}