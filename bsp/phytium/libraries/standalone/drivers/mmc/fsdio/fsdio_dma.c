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
 * FilePath: fsdio_dma.c
 * Date: 2022-06-01 14:21:41
 * LastEditTime: 2022-06-01 14:21:42
 * Description:  This file is for DMA related function implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 */
/***************************** Include Files *********************************/
#include <string.h>

#include "fio.h"
#include "fdebug.h"
#include "fassert.h"
#include "ftypes.h"


#include "fsdio_hw.h"
#include "fsdio.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDIO_DEBUG_TAG "FSDIO-DMA"
#define FSDIO_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/
extern FError FSdioTransferCmd(FSdio *const instance_p, FSdioCmdData *const cmd_data_p);
extern FError FSdioPollWaitBusyCard(FSdio *const instance_p);

/*****************************************************************************/
/**
 * @name: FSdioDumpDMADescriptor
 * @msg: dump DMA descriptor list
 * @return {*}
 * @param {FSdio} *instance_p, instance of controller
 * @param {u32} desc_in_use, max index of descriptor in use
 */
static void FSdioDumpDMADescriptor(FSdio *const instance_p, u32 desc_in_use)
{
    u32 loop;
    volatile FSdioIDmaDesc *cur_desc = NULL;

    if (instance_p->desc_list.first_desc)
    {
        for (loop = 0; loop < desc_in_use; loop++)
        {
            cur_desc = &(instance_p->desc_list.first_desc[loop]);
            FSDIO_DEBUG("descriptor@%p", cur_desc);
            FSDIO_DEBUG("\tattribute: 0x%x", cur_desc->attribute);
            FSDIO_DEBUG("\tnon1: 0x%x", cur_desc->non1);
            FSDIO_DEBUG("\tlen: 0x%x", cur_desc->len);
            FSDIO_DEBUG("\tnon2: 0x%x", cur_desc->non2);
            FSDIO_DEBUG("\taddr_lo: 0x%x", cur_desc->addr_lo);
            FSDIO_DEBUG("\taddr_hi: 0x%x", cur_desc->addr_hi);
            FSDIO_DEBUG("\tdesc_lo: 0x%x", cur_desc->desc_lo);
            FSDIO_DEBUG("\tdesc_hi: 0x%x", cur_desc->desc_hi);
        }
    }
}

/**
 * @name: FSdioSetupDMADescriptor
 * @msg: setup DMA descriptor list before do transcation
 * @return {FError} FSDIO_SUCCESS if setup success
 * @param {FSdio} *instance_p, instance of controller
 * @param {FSdioData} *data_p, data in transcation
 */
static FError FSdioSetupDMADescriptor(FSdio *const instance_p, FSdioData *data_p)
{
    FASSERT(data_p);
    FASSERT(instance_p->desc_list.first_desc);
    u32 loop;
    u32 buf_num = data_p->datalen / data_p->blksz +
                  ((data_p->datalen % data_p->blksz) ? 1U : 0U);
    volatile FSdioIDmaDesc *cur_desc = NULL;
    uintptr buff_addr = 0U;
    uintptr desc_addr = 0U;
    boolean is_first = TRUE;
    boolean is_last = FALSE;

    if (buf_num > instance_p->desc_list.desc_num)
    {
        FSDIO_ERROR("Descriptor is too short to transfer %d < %d.",
                    instance_p->desc_list.desc_num, buf_num);
        return FSDIO_ERR_SHORT_BUF;
    }

    memset((void *)instance_p->desc_list.first_desc, 0,
           sizeof(FSdioIDmaDesc) * instance_p->desc_list.desc_num);

    FSDIO_INFO("%d of descriptor is in using.", buf_num);
    for (loop = 0U; loop < buf_num; loop++)
    {
        cur_desc = &(instance_p->desc_list.first_desc[loop]);
        is_first = (0U == loop) ? TRUE : FALSE;
        is_last = ((buf_num - 1U) == loop) ? TRUE : FALSE;

        /* set properity of descriptor entry */
        cur_desc->attribute = FSDIO_IDMAC_DES0_CH | FSDIO_IDMAC_DES0_OWN; /* descriptor list in chain, and set OWN bit  */
        cur_desc->attribute |= (is_first) ? FSDIO_IDMAC_DES0_FD : 0; /* is it the first entry ? */
        cur_desc->attribute |= (is_last) ? (FSDIO_IDMAC_DES0_LD | FSDIO_IDMAC_DES0_ER) : 0; /* is it the last entry ? */

        /* set data length in transfer */
        cur_desc->non1 = 0U;
        cur_desc->len = FSDIO_IDMAC_DES2_BUF1_SIZE(data_p->blksz) | FSDIO_IDMAC_DES2_BUF2_SIZE(0U);

        /* set data buffer for transfer */
        buff_addr = (uintptr)data_p->buf + (uintptr)(loop * data_p->blksz);
        if (buff_addr % data_p->blksz) /* make sure buffer aligned and not cross page boundary */
        {
            FSDIO_ERROR("Data buffer 0x%x do not align.", buff_addr);
            return FSDIO_ERR_DMA_BUF_UNALIGN;
        }

#ifdef __aarch64__
        cur_desc->addr_hi = UPPER_32_BITS(buff_addr);
        cur_desc->addr_lo = LOWER_32_BITS(buff_addr);
#else
        cur_desc->addr_hi = 0U;
        cur_desc->addr_lo = (u32)(buff_addr);
#endif

        /* set address of next descriptor entry, NULL for last entry */
        desc_addr = is_last ? 0U : (uintptr)&instance_p->desc_list.first_desc[loop + 1];
        if (desc_addr % sizeof(FSdioIDmaDesc)) /* make sure dma descriptor aligned and not cross page boundary */
        {
            FSDIO_ERROR("dma descriptor 0x%x do not align.", desc_addr);
            return FSDIO_ERR_DMA_BUF_UNALIGN;
        }

#ifdef __aarch64__
        cur_desc->desc_hi = UPPER_32_BITS(desc_addr);
        cur_desc->desc_lo = LOWER_32_BITS(desc_addr);
#else
        cur_desc->desc_hi = 0U;
        cur_desc->desc_lo = (u32)(desc_addr);
#endif
    }

    /* flush cache of descripor list and transfer buffer */
    FSDIO_DATA_BARRIER();

    FSdioDumpDMADescriptor(instance_p, buf_num);
    return FSDIO_SUCCESS;
}

/**
 * @name: FSdioDMATransferData
 * @msg:
 * @return {*}
 * @param {FSdio} *instance_p
 * @param {FSdioData} *data_p
 */
static FError FSdioDMATransferData(FSdio *const instance_p, FSdioData *data_p)
{
    FASSERT(data_p);
    FError ret = FSDIO_SUCCESS;
    uintptr base_addr = instance_p->config.base_addr;

    /* enable related interrupt */
    FSdioSetInterruptMask(instance_p, FSDIO_GENERAL_INTR, FSDIO_INTS_DATA_MASK, TRUE);
    FSdioSetInterruptMask(instance_p, FSDIO_IDMA_INTR, FSDIO_DMAC_INTS_MASK, TRUE);

    /* fill transfer buffer to DMA descriptor */
    ret = FSdioSetupDMADescriptor(instance_p, data_p);
    if (FSDIO_SUCCESS != ret)
    {
        return ret;
    }

    FSDIO_DATA_BARRIER();

    FSDIO_INFO("Descriptor@%p, trans bytes: %d, block size: %d",
               instance_p->desc_list.first_desc,
               data_p->datalen,
               data_p->blksz);

    /* set transfer info to register */
    FSdioSetDescriptor(base_addr, (uintptr)(instance_p->desc_list.first_desc));
    FSdioSetTransBytes(base_addr, data_p->datalen);
    FSdioSetBlockSize(base_addr, data_p->blksz);

    return ret;
}

/**
 * @name: FSdioDMATransfer
 * @msg: Start command and data transfer in DMA mode
 * @return {FError} FSDIO_SUCCESS if transfer success, otherwise failed
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {FSdioCmdData} *cmd_data_p, contents of transfer command and data
 */
FError FSdioDMATransfer(FSdio *const instance_p, FSdioCmdData *const cmd_data_p)
{
    FASSERT(instance_p);
    FASSERT(cmd_data_p);
    FError ret = FSDIO_SUCCESS;
    uintptr base_addr = instance_p->config.base_addr;

    cmd_data_p->success = FALSE; /* reset cmd transfer status */

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIO_ERROR("Device is not yet initialized!!!");
        return FSDIO_ERR_NOT_INIT;
    }

    if (FSDIO_IDMA_TRANS_MODE != instance_p->config.trans_mode)
    {
        FSDIO_ERROR("Device is not configure in DMA transfer mode.");
        return FSDIO_ERR_INVALID_STATE;
    }

    /* for removable media, check if card exists */
    if ((FALSE == instance_p->config.non_removable) &&
        (FALSE == FSdioCheckIfCardExists(base_addr)))
    {
        FSDIO_ERROR("Card is not detected !!!");
        return FSDIO_ERR_NO_CARD;
    }

    /* wait previous command finished and card not busy */
    ret = FSdioPollWaitBusyCard(instance_p);
    if (FSDIO_SUCCESS != ret)
    {
        return ret;
    }

    FSDIO_WRITE_REG(base_addr, FSDIO_RAW_INTS_OFFSET, 0xffffe);

    /* reset fifo and DMA before transfer */

    ret = FSdioResetCtrl(base_addr, FSDIO_CNTRL_FIFO_RESET | FSDIO_CNTRL_DMA_RESET);
    if (FSDIO_SUCCESS != ret)
    {
        return ret;
    }

    /* enable use of DMA */
    FSDIO_SET_BIT(base_addr, FSDIO_CNTRL_OFFSET, FSDIO_CNTRL_USE_INTERNAL_DMAC);
    FSDIO_SET_BIT(base_addr, FSDIO_BUS_MODE_OFFSET, FSDIO_BUS_MODE_DE);

    if (NULL != cmd_data_p->data_p) /* transfer data */
    {
        ret = FSdioDMATransferData(instance_p,
                                   cmd_data_p->data_p);
    }

    if (FSDIO_SUCCESS == ret) /* transfer command */
    {
        ret = FSdioTransferCmd(instance_p, cmd_data_p);
    }

    return ret;
}

/**
 * @name: FSdioPollWaitDMAEnd
 * @msg: Wait DMA transfer finished by poll
 * @return {FError} FSDIO_SUCCESS if wait success, otherwise wait failed
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {FSdioCmdData} *cmd_data_p, contents of transfer command and data
 * @param {FSdioRelaxHandler} relax, handler of relax when wait busy
 */
FError FSdioPollWaitDMAEnd(FSdio *const instance_p, FSdioCmdData *const cmd_data_p)
{
    FASSERT(instance_p);
    FASSERT(cmd_data_p);
    FError ret = FSDIO_SUCCESS;
    u32 reg_val;
    int delay;
    const boolean read = cmd_data_p->flag & FSDIO_CMD_FLAG_READ_DATA;
    uintptr base_addr = instance_p->config.base_addr;
    const u32 wait_bits = (NULL == cmd_data_p->data_p) ? FSDIO_INT_CMD_BIT : (FSDIO_INT_CMD_BIT | FSDIO_INT_DTO_BIT);

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIO_ERROR("Device is not yet initialized!!!");
        return FSDIO_ERR_NOT_INIT;
    }

    if (FSDIO_IDMA_TRANS_MODE != instance_p->config.trans_mode)
    {
        FSDIO_ERROR("Device is not configure in DMA transfer mode.");
        return FSDIO_ERR_INVALID_STATE;
    }

    /* wait command done or data timeout */
    delay = FSDIO_TIMEOUT;
    do
    {
        reg_val = FSdioGetRawStatus(base_addr);

        if (delay % 1000 == 0)
        {
            FSDIO_DEBUG("reg_val = 0x%x", reg_val);
        }

        if (instance_p->relax_handler)
        {
            instance_p->relax_handler();
        }
    }
    while (((wait_bits & reg_val) != wait_bits) && (--delay > 0));

    /* clear status to ack data done */
    FSdioClearRawStatus(base_addr);

    if (((wait_bits & reg_val) != wait_bits) && (delay <= 0))
    {
        FSDIO_ERROR("Wait cmd done timeout, raw ints: 0x%x.", reg_val);
        return FSDIO_ERR_CMD_TIMEOUT;
    }

    if (NULL != cmd_data_p->data_p) /* wait data transfer done or timeout */
    {
        /* invalidate cache of transfer buffer */
        if (read)
        {
            FSDIO_DATA_BARRIER();
        }
    }

    if (FSDIO_SUCCESS == ret)
    {
        ret = FSdioGetCmdResponse(instance_p, cmd_data_p);
    }

    return ret;
}

/**
 * @name: FSdioSetIDMAList
 * @msg: Setup DMA descriptor for SDIO controller instance
 * @return {FError} FSDIO_SUCCESS if setup done, otherwise failed
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {volatile FSdioIDmaDesc} *desc, first item in DMA descriptor lists
 * @param {u32} desc_num, number of items in DMA descriptor lists
 */
FError FSdioSetIDMAList(FSdio *const instance_p, volatile FSdioIDmaDesc *desc, u32 desc_num)
{
    FASSERT(instance_p);
    FError ret = FSDIO_SUCCESS;
    uintptr base_addr = instance_p->config.base_addr;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIO_ERROR("Device is not yet initialized!!!");
        return FSDIO_ERR_NOT_INIT;
    }

    if (FSDIO_IDMA_TRANS_MODE != instance_p->config.trans_mode)
    {
        FSDIO_ERROR("Device is not configure in DMA transfer mode.");
        return FSDIO_ERR_INVALID_STATE;
    }

    instance_p->desc_list.first_desc = desc;
    instance_p->desc_list.desc_num = desc_num;
    return ret;
}