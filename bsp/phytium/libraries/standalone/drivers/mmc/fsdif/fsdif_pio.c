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
 * FilePath: fsdif_pio.c
 * Date: 2022-06-01 14:21:47
 * LastEditTime: 2022-06-01 14:21:47
 * Description:  This file is for PIO transfer related function implementation
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
#define FSDIF_DEBUG_TAG "FSDIF-PIO"
#define FSDIF_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/
extern FError FSdifTransferCmd(FSdif *const instance_p, FSdifCmdData *const cmd_data_p);
extern FError FSdifPollWaitBusyCard(FSdif *const instance_p);

/*****************************************************************************/
/**
 * @name: FSdifPIOWriteData
 * @msg: Write data to fifo
 * @return {FError} FSDIF_SUCCESS if write success
 * @param {FSdif} *instance_p, SDIF controller instance
 * @param {FSdifData} *data_p, contents of transfer data
 */
static FError FSdifPIOWriteData(FSdif *const instance_p, FSdifData *data_p)
{
    FASSERT(data_p);
    FError ret = FSDIF_SUCCESS;
    u32 loop;
    uintptr base_addr = instance_p->config.base_addr;
    const u32 wr_times = data_p->datalen / sizeof(u32); /* u8 --> u32 */
    u32 *wr_buf = (u32 *)data_p->buf;

    /* write fifo data */
    FSDIF_WRITE_REG(base_addr, FSDIF_CMD_OFFSET, FSDIF_CMD_DAT_WRITE);
    for (loop = 0; loop < wr_times; loop++)
    {
        FSDIF_WRITE_REG(base_addr, FSDIF_DATA_OFFSET, wr_buf[loop]);
    }

    return ret;
}

/**
 * @name: FSdifPIOReadData
 * @msg: Read data from fifo
 * @return {FError} FSDIF_SUCCESS if read success
 * @param {FSdif} *instance_p, SDIF controller instance
 * @param {FSdifData} *data_p, contents of transfer data
 */
FError FSdifPIOReadData(FSdif *const instance_p, FSdifData *data_p)
{
    FASSERT(data_p);
    FError ret = FSDIF_SUCCESS;
    u32 loop;
    uintptr base_addr = instance_p->config.base_addr;
    const u32 rd_times = data_p->datalen / sizeof(u32); /* u8 --> u32 */
    u32 *rd_buf = (u32 *)data_p->buf;

    /* while in PIO mode, max data transferred is 0x800 */
    if (data_p->datalen > FSDIF_MAX_FIFO_CNT)
    {
        FSDIF_ERROR("Fifo do not support writing more than 0x%x.", FSDIF_MAX_FIFO_CNT);
        return FSDIF_ERR_NOT_SUPPORT;
    }

    /* read data from fifo */
    for (loop = 0; loop < rd_times; loop++)
    {
        rd_buf[loop] = FSDIF_READ_REG(base_addr, FSDIF_DATA_OFFSET);
    }

    return ret;
}

/**
 * @name: FSdifPIOTransfer
 * @msg: Start command and data transfer in PIO mode
 * @return {FError} FSDIF_SUCCESS if transfer success, otherwise failed
 * @param {FSdif} *instance_p, SDIF controller instance
 * @param {FSdifCmdData} *cmd_data_p, contents of transfer command and data
 */
FError FSdifPIOTransfer(FSdif *const instance_p, FSdifCmdData *const cmd_data_p)
{
    FASSERT(instance_p);
    FASSERT(cmd_data_p);
    FError ret = FSDIF_SUCCESS;
    const boolean read = cmd_data_p->flag & FSDIF_CMD_FLAG_READ_DATA;
    uintptr base_addr = instance_p->config.base_addr;

    cmd_data_p->success = FALSE; /* reset cmd transfer status */

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIF_ERROR("device is not yet initialized!!!");
        return FSDIF_ERR_NOT_INIT;
    }

    if (FSDIF_PIO_TRANS_MODE != instance_p->config.trans_mode)
    {
        FSDIF_ERROR("device is not configure in PIO transfer mode.");
        return FSDIF_ERR_INVALID_STATE;
    }

    /* for removable media, check if card exists */
    if ((FALSE == instance_p->config.non_removable) &&
        (FALSE == FSdifCheckIfCardExists(base_addr)))
    {
        FSDIF_ERROR("card is not detected !!!");
        return FSDIF_ERR_NO_CARD;
    }

    /* wait previous command finished and card not busy */
    ret = FSdifPollWaitBusyCard(instance_p);
    if (FSDIF_SUCCESS != ret)
    {
        return ret;
    }

    /* reset fifo and not use DMA */
    FSDIF_CLR_BIT(base_addr, FSDIF_CNTRL_OFFSET, FSDIF_CNTRL_USE_INTERNAL_DMAC);
    ret = FSdifResetCtrl(base_addr, FSDIF_CNTRL_FIFO_RESET);
    if (FSDIF_SUCCESS != ret)
    {
        return ret;
    }
    FSDIF_CLR_BIT(base_addr, FSDIF_BUS_MODE_OFFSET, FSDIF_BUS_MODE_DE);

    if (NULL != cmd_data_p->data_p)
    {
        /* while in PIO mode, max data transferred is 0x800 */
        if (cmd_data_p->data_p->datalen > FSDIF_MAX_FIFO_CNT)
        {
            FSDIF_ERROR("Fifo do not support writing more than 0x%x.", FSDIF_MAX_FIFO_CNT);
            return FSDIF_ERR_NOT_SUPPORT;
        }

        /* set transfer data length and block size */
        FSdifSetTransBytes(base_addr, cmd_data_p->data_p->datalen);
        FSdifSetBlockSize(base_addr, cmd_data_p->data_p->blksz);

        if (FALSE == read) /* if need to write, write to fifo before send command */
        {
            /* invalide buffer for data to write */

            FSDIF_DATA_BARRIER();

            ret = FSdifPIOWriteData(instance_p, cmd_data_p->data_p);
        }
    }

    if (FSDIF_SUCCESS == ret) /* send command */
    {
        ret = FSdifTransferCmd(instance_p, cmd_data_p);
    }

    return ret;
}

/**
 * @name: FSdifPollWaitPIOEnd
 * @msg: Wait PIO transfer finished by poll
 * @return {FError} FSDIF_SUCCESS if wait success, otherwise wait failed
 * @param {FSdif} *instance_p, SDIF controller instance
 * @param {FSdifCmdData} *cmd_data_p, contents of transfer command and data
 * @param {FSdifRelaxHandler} relax, handler of relax when wait busy
 */
FError FSdifPollWaitPIOEnd(FSdif *const instance_p, FSdifCmdData *const cmd_data_p)
{
    FASSERT(instance_p);
    FASSERT(cmd_data_p);
    FError ret = FSDIF_SUCCESS;
    u32 reg_val;
    int delay;
    const boolean read = cmd_data_p->flag & FSDIF_CMD_FLAG_READ_DATA;
    uintptr base_addr = instance_p->config.base_addr;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIF_ERROR("device is not yet initialized!!!");
        return FSDIF_ERR_NOT_INIT;
    }

    if (FSDIF_PIO_TRANS_MODE != instance_p->config.trans_mode)
    {
        FSDIF_ERROR("device is not configure in PIO transfer mode.");
        return FSDIF_ERR_INVALID_STATE;
    }

    FSDIF_INFO("wait for PIO cmd to finish ...");
    delay = FSDIF_TIMEOUT;
    do
    {
        reg_val = FSdifGetRawStatus(base_addr);
        if (instance_p->relax_handler)
        {
            instance_p->relax_handler();
        }
    }
    while (!(FSDIF_INT_CMD_BIT & reg_val) && (--delay > 0));

    if (!(FSDIF_INT_CMD_BIT & reg_val) && (delay <= 0))
    {
        FSDIF_ERROR("wait cmd done timeout, raw ints: 0x%x", reg_val);
        return FSDIF_ERR_CMD_TIMEOUT;
    }

    /* if need to read data, read fifo after send command */
    if ((NULL != cmd_data_p->data_p) && (read))
    {
        FSDIF_INFO("wait for PIO data to read ...");
        delay = FSDIF_TIMEOUT;
        do
        {
            reg_val = FSdifGetRawStatus(base_addr);
            if (instance_p->relax_handler)
            {
                instance_p->relax_handler();
            }
        }
        while (!(FSDIF_INT_DTO_BIT & reg_val) && (--delay > 0));

        /* clear status to ack */
        FSdifClearRawStatus(base_addr);
        FSDIF_INFO("card cnt: 0x%x, fifo cnt: 0x%x",
                   FSDIF_READ_REG(base_addr, FSDIF_TRAN_CARD_CNT_OFFSET),
                   FSDIF_READ_REG(base_addr, FSDIF_TRAN_FIFO_CNT_OFFSET));

        if (!(FSDIF_INT_DTO_BIT & reg_val) && (delay <= 0))
        {
            FSDIF_ERROR("wait PIO transfer timeout, raw ints: 0x%x.", reg_val);
            return FSDIF_ERR_TRANS_TIMEOUT;
        }
    }

    /* clear status to ack cmd done */
    FSdifClearRawStatus(base_addr);

    if (FSDIF_SUCCESS == ret)
    {
        ret = FSdifGetCmdResponse(instance_p, cmd_data_p);
    }

    return ret;
}