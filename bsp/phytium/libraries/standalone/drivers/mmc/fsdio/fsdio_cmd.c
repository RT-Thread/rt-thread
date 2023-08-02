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
 * FilePath: fsdio_cmd.c
 * Date: 2022-06-01 14:23:59
 * LastEditTime: 2022-06-01 14:24:00
 * Description:  This file is for SDIO command related function
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

#include "fcache.h"
#include "fswap.h"

#include "fsdio_hw.h"
#include "fsdio.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/
#define FSDIO_EXT_APP_CMD       55U

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDIO_DEBUG_TAG "FSDIO-CMD"
#define FSDIO_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/
extern FError FSdioPIOReadData(FSdio *const instance_p, FSdioData *data_p);

/*****************************************************************************/
FError FSdioSendPrivateCmd(uintptr base_addr, u32 cmd, u32 arg)
{
    u32 reg_val;
    int retries = FSDIO_TIMEOUT;

    do
    {
        reg_val = FSDIO_READ_REG(base_addr, FSDIO_STATUS_OFFSET);
        if (--retries <= 0)
        {
            break;
        }
    }
    while (FSDIO_STATUS_DATA_BUSY & reg_val);

    if (retries <= 0)
    {
        return FSDIO_ERR_BUSY;
    }

    FSDIO_WRITE_REG(base_addr, FSDIO_CMD_ARG_OFFSET, arg);

    FSDIO_DATA_BARRIER(); /* drain writebuffer */

    FSDIO_WRITE_REG(base_addr, FSDIO_CMD_OFFSET, FSDIO_CMD_START | cmd);

    retries = FSDIO_TIMEOUT;
    do
    {
        reg_val = FSDIO_READ_REG(base_addr, FSDIO_CMD_OFFSET);
        if (--retries <= 0)
        {
            break;
        }
    }
    while (FSDIO_CMD_START & reg_val);   /* wait until command send done */

    return (retries <= 0) ? FSDIO_ERR_TIMEOUT : FSDIO_SUCCESS;
}

/**
 * @name: FSdioTransferCmd
 * @msg: pack and transfer command
 * @return {FError} FSDIO_SUCCESS if transfer success
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {FSdioCmdData} *cmd_data_p, contents of transfer command and data
 */
FError FSdioTransferCmd(FSdio *const instance_p, FSdioCmdData *const cmd_data_p)
{
    FASSERT(cmd_data_p);
    FError ret = FSDIO_SUCCESS;
    uintptr base_addr = instance_p->config.base_addr;
    u32 cmd_flag = cmd_data_p->flag;
    u32 raw_cmd = FSDIO_CMD_USE_HOLD_REG; /* USE_HOLD_REG必须为1 */

    /* 命令需要进行卡初始化，如CMD-0 */
    if (FSDIO_CMD_FLAG_NEED_INIT & cmd_flag)
    {
        raw_cmd |= FSDIO_CMD_INIT;
    }

    /* 命令涉及电压切换 */
    if (FSDIO_CMD_FLAG_SWITCH_VOLTAGE & cmd_flag)
    {
        raw_cmd |= FSDIO_CMD_VOLT_SWITCH;
    }

    /* 命令传输过程伴随数据传输 */
    if (FSDIO_CMD_FLAG_EXP_DATA & cmd_flag)
    {
        raw_cmd |= FSDIO_CMD_DAT_EXP;

        if (FSDIO_CMD_FLAG_WRITE_DATA & cmd_flag) /* 写卡 */
        {
            raw_cmd |= FSDIO_CMD_DAT_WRITE;
        }
    }

    /* 命令需要进行CRC校验 */
    if (FSDIO_CMD_FLAG_NEED_RESP_CRC & cmd_flag)
    {
        raw_cmd |= FSDIO_CMD_RESP_CRC;
    }

    /* 命令需要响应回复 */
    if (FSDIO_CMD_FLAG_EXP_RESP & cmd_flag)
    {
        raw_cmd |= FSDIO_CMD_RESP_EXP;

        if (FSDIO_CMD_FLAG_EXP_LONG_RESP & cmd_flag) /* 命令需要136字节长回复 */
        {
            raw_cmd |= FSDIO_CMD_RESP_LONG;
        }
    }

    raw_cmd |= FSDIO_CMD_INDX_SET(cmd_data_p->cmdidx);

    FSDIO_DEBUG("============[%s-%d]@0x%x begin ============",
                (FSDIO_EXT_APP_CMD == instance_p->prev_cmd) ? "ACMD" : "CMD", cmd_data_p->cmdidx,
                base_addr);
    FSDIO_DEBUG("    cmd: 0x%x", raw_cmd);
    FSDIO_DEBUG("    arg: 0x%x", cmd_data_p->cmdarg);

    /* enable related interrupt */
    FSdioSetInterruptMask(instance_p, FSDIO_GENERAL_INTR,
                          FSDIO_INTS_CMD_MASK, TRUE);

    ret = FSdioSendPrivateCmd(base_addr, raw_cmd, cmd_data_p->cmdarg);
    FSDIO_INFO("cmd send done ...");
    return ret;
}

static void FSdioFlipByteOrder(u32 *response, fsize_t size)
{
    /*
        swap response and convert byte order
        resp[0] = bswap32(resp[3])
        resp[1] = bswap32(resp[2])
        resp[2] = bswap32(resp[1])
        resp[3] = bswap32(resp[0])
    */
    FASSERT(size % (2 * sizeof(u32)) == 0);
    const fsize_t n_words = size / sizeof(uint32_t);
    for (int i = 0; i < (int)n_words / 2; ++i)
    {
        u32 left = __builtin_bswap32(response[i]);
        u32 right = __builtin_bswap32(response[n_words - i - 1]);
        response[i] = right;
        response[n_words - i - 1] = left;
    }
}

/**
 * @name: FSdioGetCmdResponse
 * @msg: Get cmd response and received data after wait poll status or interrupt signal
 * @return {FError} FSDIO_SUCCESS if get success
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {FSdioCmdData} *cmd_data_p, contents of transfer command and data
 */
FError FSdioGetCmdResponse(FSdio *const instance_p, FSdioCmdData *const cmd_data_p)
{
    FASSERT(instance_p);
    FASSERT(cmd_data_p);
    FError ret = FSDIO_SUCCESS;
    const boolean read = cmd_data_p->flag & FSDIO_CMD_FLAG_READ_DATA;
    uintptr base_addr = instance_p->config.base_addr;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIO_ERROR("Device is not yet initialized!!!");
        return FSDIO_ERR_NOT_INIT;
    }

    if ((NULL != cmd_data_p->data_p) && (read))
    {
        if (FSDIO_PIO_TRANS_MODE == instance_p->config.trans_mode)
        {
            ret = FSdioPIOReadData(instance_p, cmd_data_p->data_p);
        }
    }

    /* check response of cmd */
    if (FSDIO_CMD_FLAG_EXP_RESP & cmd_data_p->flag)
    {
        if (FSDIO_CMD_FLAG_EXP_LONG_RESP & cmd_data_p->flag)
        {
            cmd_data_p->response[0] = FSDIO_READ_REG(base_addr, FSDIO_RESP0_OFFSET);
            cmd_data_p->response[1] = FSDIO_READ_REG(base_addr, FSDIO_RESP1_OFFSET);
            cmd_data_p->response[2] = FSDIO_READ_REG(base_addr, FSDIO_RESP2_OFFSET);
            cmd_data_p->response[3] = FSDIO_READ_REG(base_addr, FSDIO_RESP3_OFFSET);

            /* according to SD spec. 136 bits R2 is send-back in reverse order and big-end,
               some SD protocol will do this reverse and ntol itself, other do not,
               filp_resp_byte_order is to compilant with those not */
            if (instance_p->config.filp_resp_byte_order)
            {
                FSdioFlipByteOrder(cmd_data_p->response, sizeof(u32) * 4);
            }

            FSDIO_DEBUG("    resp: 0x%x-0x%x-0x%x-0x%x",
                        cmd_data_p->response[0], cmd_data_p->response[1],
                        cmd_data_p->response[2], cmd_data_p->response[3]);
        }
        else
        {
            cmd_data_p->response[0] = FSDIO_READ_REG(base_addr, FSDIO_RESP0_OFFSET);
            cmd_data_p->response[1] = 0U;
            cmd_data_p->response[2] = 0U;
            cmd_data_p->response[3] = 0U;
            FSDIO_DEBUG("    resp: 0x%x", cmd_data_p->response[0]);
        }
    }

    cmd_data_p->success = TRUE; /* cmd / data transfer finished successful */
    FSDIO_DEBUG("============[%s-%d]@0x%x end  ============",
                (FSDIO_EXT_APP_CMD == instance_p->prev_cmd) ? "ACMD" : "CMD",
                cmd_data_p->cmdidx, base_addr);

    /* disable related interrupt */
    FSdioSetInterruptMask(instance_p, FSDIO_GENERAL_INTR, FSDIO_INTS_CMD_MASK | FSDIO_INTS_DATA_MASK, FALSE);
    FSdioSetInterruptMask(instance_p, FSDIO_IDMA_INTR, FSDIO_DMAC_INTS_MASK, FALSE);

    instance_p->prev_cmd = cmd_data_p->cmdidx; /* record previous command */

    return ret;
}