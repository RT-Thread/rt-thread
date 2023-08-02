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
 * FilePath: fsdio_pio.c
 * Date: 2022-06-01 14:21:47
 * LastEditTime: 2022-06-01 14:21:47
 * Description:  This file is for PIO transfer related function implementation
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
#define FSDIO_DEBUG_TAG "FSDIO-PIO"
#define FSDIO_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/
extern FError FSdioTransferCmd(FSdio *const instance_p, FSdioCmdData *const cmd_data_p);
extern FError FSdioPollWaitBusyCard(FSdio *const instance_p);

/*****************************************************************************/
/**
 * @name: FSdioPIOWriteData
 * @msg: Write data to fifo
 * @return {FError} FSDIO_SUCCESS if write success
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {FSdioData} *data_p, contents of transfer data
 */
static FError FSdioPIOWriteData(FSdio *const instance_p, FSdioData *data_p)
{
    FASSERT(data_p);
    FError ret = FSDIO_SUCCESS;
    u32 loop;
    uintptr base_addr = instance_p->config.base_addr;
    const u32 wr_times = data_p->datalen / sizeof(u32); /* u8 --> u32 */
    u32 *wr_buf = (u32 *)data_p->buf;

    /* write fifo data */
    FSDIO_WRITE_REG(base_addr, FSDIO_CMD_OFFSET, FSDIO_CMD_DAT_WRITE);
    for (loop = 0; loop < wr_times; loop++)
    {
        FSDIO_WRITE_REG(base_addr, FSDIO_DATA_OFFSET, wr_buf[loop]);
    }

    return ret;
}

/**
 * @name: FSdioPIOReadData
 * @msg: Read data from fifo
 * @return {FError} FSDIO_SUCCESS if read success
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {FSdioData} *data_p, contents of transfer data
 */
FError FSdioPIOReadData(FSdio *const instance_p, FSdioData *data_p)
{
    FASSERT(data_p);
    FError ret = FSDIO_SUCCESS;
    u32 loop;
    uintptr base_addr = instance_p->config.base_addr;
    const u32 rd_times = data_p->datalen / sizeof(u32); /* u8 --> u32 */
    u32 *rd_buf = (u32 *)data_p->buf;

    /* while in PIO mode, max data transferred is 0x800 */
    if (data_p->datalen > FSDIO_MAX_FIFO_CNT)
    {
        FSDIO_ERROR("Fifo do not support writing more than 0x%x.", FSDIO_MAX_FIFO_CNT);
        return FSDIO_ERR_NOT_SUPPORT;
    }

    /* read data from fifo */
    for (loop = 0; loop < rd_times; loop++)
    {
        rd_buf[loop] = FSDIO_READ_REG(base_addr, FSDIO_DATA_OFFSET);
    }

    return ret;
}

/**
 * @name: FSdioPIOTransfer
 * @msg: Start command and data transfer in PIO mode
 * @return {FError} FSDIO_SUCCESS if transfer success, otherwise failed
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {FSdioCmdData} *cmd_data_p, contents of transfer command and data
 */
FError FSdioPIOTransfer(FSdio *const instance_p, FSdioCmdData *const cmd_data_p)
{
    FASSERT(instance_p);
    FASSERT(cmd_data_p);
    FError ret = FSDIO_SUCCESS;
    const boolean read = cmd_data_p->flag & FSDIO_CMD_FLAG_READ_DATA;
    uintptr base_addr = instance_p->config.base_addr;

    cmd_data_p->success = FALSE; /* reset cmd transfer status */

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIO_ERROR("device is not yet initialized!!!");
        return FSDIO_ERR_NOT_INIT;
    }

    if (FSDIO_PIO_TRANS_MODE != instance_p->config.trans_mode)
    {
        FSDIO_ERROR("device is not configure in PIO transfer mode.");
        return FSDIO_ERR_INVALID_STATE;
    }

    /* for removable media, check if card exists */
    if ((FALSE == instance_p->config.non_removable) &&
        (FALSE == FSdioCheckIfCardExists(base_addr)))
    {
        FSDIO_ERROR("card is not detected !!!");
        return FSDIO_ERR_NO_CARD;
    }

    /* wait previous command finished and card not busy */
    ret = FSdioPollWaitBusyCard(instance_p);
    if (FSDIO_SUCCESS != ret)
    {
        return ret;
    }

    /* reset fifo and not use DMA */
    FSDIO_CLR_BIT(base_addr, FSDIO_CNTRL_OFFSET, FSDIO_CNTRL_USE_INTERNAL_DMAC);
    ret = FSdioResetCtrl(base_addr, FSDIO_CNTRL_FIFO_RESET);
    if (FSDIO_SUCCESS != ret)
    {
        return ret;
    }
    FSDIO_CLR_BIT(base_addr, FSDIO_BUS_MODE_OFFSET, FSDIO_BUS_MODE_DE);

    if (NULL != cmd_data_p->data_p)
    {
        /* while in PIO mode, max data transferred is 0x800 */
        if (cmd_data_p->data_p->datalen > FSDIO_MAX_FIFO_CNT)
        {
            FSDIO_ERROR("Fifo do not support writing more than 0x%x.", FSDIO_MAX_FIFO_CNT);
            return FSDIO_ERR_NOT_SUPPORT;
        }

        /* set transfer data length and block size */
        FSdioSetTransBytes(base_addr, cmd_data_p->data_p->datalen);
        FSdioSetBlockSize(base_addr, cmd_data_p->data_p->blksz);

        if (FALSE == read) /* if need to write, write to fifo before send command */
        {
            /* invalide buffer for data to write */

            FSDIO_DATA_BARRIER();

            ret = FSdioPIOWriteData(instance_p, cmd_data_p->data_p);
        }
    }

    if (FSDIO_SUCCESS == ret) /* send command */
    {
        ret = FSdioTransferCmd(instance_p, cmd_data_p);
    }

    return ret;
}

/**
 * @name: FSdioPollWaitPIOEnd
 * @msg: Wait PIO transfer finished by poll
 * @return {FError} FSDIO_SUCCESS if wait success, otherwise wait failed
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {FSdioCmdData} *cmd_data_p, contents of transfer command and data
 * @param {FSdioRelaxHandler} relax, handler of relax when wait busy
 */
FError FSdioPollWaitPIOEnd(FSdio *const instance_p, FSdioCmdData *const cmd_data_p)
{
    FASSERT(instance_p);
    FASSERT(cmd_data_p);
    FError ret = FSDIO_SUCCESS;
    u32 reg_val;
    int delay;
    const boolean read = cmd_data_p->flag & FSDIO_CMD_FLAG_READ_DATA;
    uintptr base_addr = instance_p->config.base_addr;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIO_ERROR("device is not yet initialized!!!");
        return FSDIO_ERR_NOT_INIT;
    }

    if (FSDIO_PIO_TRANS_MODE != instance_p->config.trans_mode)
    {
        FSDIO_ERROR("device is not configure in PIO transfer mode.");
        return FSDIO_ERR_INVALID_STATE;
    }

    FSDIO_INFO("wait for PIO cmd to finish ...");
    delay = FSDIO_TIMEOUT;
    do
    {
        reg_val = FSdioGetRawStatus(base_addr);
        if (instance_p->relax_handler)
        {
            instance_p->relax_handler();
        }
    }
    while (!(FSDIO_INT_CMD_BIT & reg_val) && (--delay > 0));

    if (!(FSDIO_INT_CMD_BIT & reg_val) && (delay <= 0))
    {
        FSDIO_ERROR("wait cmd done timeout, raw ints: 0x%x", reg_val);
        return FSDIO_ERR_CMD_TIMEOUT;
    }

    /* if need to read data, read fifo after send command */
    if ((NULL != cmd_data_p->data_p) && (read))
    {
        FSDIO_INFO("wait for PIO data to read ...");
        delay = FSDIO_TIMEOUT;
        do
        {
            reg_val = FSdioGetRawStatus(base_addr);
            if (instance_p->relax_handler)
            {
                instance_p->relax_handler();
            }
        }
        while (!(FSDIO_INT_DTO_BIT & reg_val) && (--delay > 0));

        /* clear status to ack */
        FSdioClearRawStatus(base_addr);
        FSDIO_INFO("card cnt: 0x%x, fifo cnt: 0x%x",
                   FSDIO_READ_REG(base_addr, FSDIO_TRAN_CARD_CNT_OFFSET),
                   FSDIO_READ_REG(base_addr, FSDIO_TRAN_FIFO_CNT_OFFSET));

        if (!(FSDIO_INT_DTO_BIT & reg_val) && (delay <= 0))
        {
            FSDIO_ERROR("wait PIO transfer timeout, raw ints: 0x%x.", reg_val);
            return FSDIO_ERR_TRANS_TIMEOUT;
        }
    }

    /* clear status to ack cmd done */
    FSdioClearRawStatus(base_addr);

    if (FSDIO_SUCCESS == ret)
    {
        ret = FSdioGetCmdResponse(instance_p, cmd_data_p);
    }

    return ret;
}