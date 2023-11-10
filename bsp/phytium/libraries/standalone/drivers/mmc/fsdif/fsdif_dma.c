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
 * FilePath: fsdif_dma.c
 * Date: 2022-06-01 14:21:41
 * LastEditTime: 2022-06-01 14:21:42
 * Description:  This file is for DMA related function implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 * 2.0   zhugengyu  2023/9/16    rename as sdif, support SD 3.0 and rework clock timing
 */
/***************************** Include Files *********************************/
#include <string.h>

#include "fio.h"
#include "fdrivers_port.h"
#include "fassert.h"
#include "ftypes.h"

#include "fsdif_hw.h"
#include "fsdif.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDIF_DEBUG_TAG "FSDIF-DMA"
#define FSDIF_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/
extern FError FSdifTransferCmd(FSdif *const instance_p, FSdifCmdData *const cmd_data_p);
extern FError FSdifPollWaitBusyCard(FSdif *const instance_p);

/*****************************************************************************/
/**
 * @name: FSdifDumpDMADescriptor
 * @msg: dump DMA descriptor list
 * @return {*}
 * @param {FSdif} *instance_p, instance of controller
 * @param {u32} desc_in_use, max index of descriptor in use
 */
static void FSdifDumpDMADescriptor(FSdif *const instance_p, u32 desc_in_use)
{
    u32 loop;
    volatile FSdifIDmaDesc *cur_desc = NULL;

    if (instance_p->desc_list.first_desc)
    {
        for (loop = 0; loop < desc_in_use; loop++)
        {
            cur_desc = &(instance_p->desc_list.first_desc[loop]);
            FSDIF_DEBUG("descriptor@%p", cur_desc);
            FSDIF_DEBUG("\tattribute: 0x%x", cur_desc->attribute);
            FSDIF_DEBUG("\tnon1: 0x%x", cur_desc->non1);
            FSDIF_DEBUG("\tlen: 0x%x", cur_desc->len);
            FSDIF_DEBUG("\tnon2: 0x%x", cur_desc->non2);
            FSDIF_DEBUG("\taddr_lo: 0x%x", cur_desc->addr_lo);
            FSDIF_DEBUG("\taddr_hi: 0x%x", cur_desc->addr_hi);
            FSDIF_DEBUG("\tdesc_lo: 0x%x", cur_desc->desc_lo);
            FSDIF_DEBUG("\tdesc_hi: 0x%x", cur_desc->desc_hi);
        }
    }
}

/**
 * @name: FSdifSetupDMADescriptor
 * @msg: setup DMA descriptor list before do transcation
 * @return {FError} FSDIF_SUCCESS if setup success
 * @param {FSdif} *instance_p, instance of controller
 * @param {FSdifData} *data_p, data in transcation
 */
static FError FSdifSetupDMADescriptor(FSdif *const instance_p, FSdifData *data_p)
{
    FASSERT(data_p && data_p->buf);
    FASSERT(instance_p->desc_list.first_desc);
    FSdifIDmaDescList *desc_list = &instance_p->desc_list;
    volatile FSdifIDmaDesc *cur_desc = NULL;
    u32 desc_num = 1U;
    /* num of blocks can be transferred by one descriptor */
    u32 desc_blocks = instance_p->desc_list.desc_trans_sz / data_p->blksz;
    u32 remain_blocks = data_p->blkcnt; /* blocks still need to transfer */
    u32 trans_blocks; /* blocks that will be transferred this round */
    uintptr next_desc_addr = 0U;
    uintptr buff_addr = data_p->buf_dma;
    boolean is_first = TRUE;
    boolean is_last = FALSE;
    u32 loop = 0;

    if (data_p->datalen > instance_p->desc_list.desc_trans_sz)
    {
        desc_num = ((data_p->datalen / instance_p->desc_list.desc_trans_sz) +
                    (data_p->datalen % instance_p->desc_list.desc_trans_sz));
    }

    if (desc_num > desc_list->desc_num)
    {
        FSDIF_ERROR("Transfer descriptor are not enough %d < %d !!!",
                    desc_list->desc_num, desc_num);
        return FSDIF_ERR_SHORT_BUF;
    }

    FSDIF_DEBUG("DMA transfer 0x%x use %d desc, total %d",
                data_p->buf_dma, desc_num, desc_list->desc_num);

    /* setup DMA descriptor list, so that we just need to update buffer address
       in each transaction */
    memset((void *)desc_list->first_desc, 0, sizeof(FSdifIDmaDesc) * desc_list->desc_num);

    for (loop = 0; loop < desc_num; loop++)
    {
        trans_blocks = (remain_blocks <= desc_blocks) ? remain_blocks : desc_blocks;
        cur_desc = &(desc_list->first_desc[loop]); /* virtual addr of current descriptor */
        next_desc_addr = desc_list->first_desc_dma + (loop + 1) * sizeof(FSdifIDmaDesc); /* physical addr of next descriptor */

        is_first = (0U == loop) ? TRUE : FALSE;
        is_last = ((desc_num - 1U) == loop) ? TRUE : FALSE;

        /* set properity of descriptor entry */
        cur_desc->attribute = FSDIF_IDMAC_DES0_CH | FSDIF_IDMAC_DES0_OWN; /* descriptor list in chain, and set OWN bit  */
        cur_desc->attribute |= (is_first) ? FSDIF_IDMAC_DES0_FD : 0; /* is it the first entry ? */
        cur_desc->attribute |= (is_last) ? (FSDIF_IDMAC_DES0_LD | FSDIF_IDMAC_DES0_ER) : 0; /* is it the last entry ? */

        /* set data length in transfer */
        cur_desc->non1 = 0U;
        cur_desc->len = (u32)(trans_blocks * data_p->blksz);

        /* set data buffer for transfer */
        if (buff_addr % data_p->blksz) /* make sure buffer aligned and not cross page boundary */
        {
            FSDIF_ERROR("Data buffer 0x%x do not align to %d.", buff_addr, data_p->blksz);
            return FSDIF_ERR_DMA_BUF_UNALIGN;
        }

#ifdef __aarch64__
        cur_desc->addr_hi = UPPER_32_BITS(buff_addr);
        cur_desc->addr_lo = LOWER_32_BITS(buff_addr);
#else
        cur_desc->addr_hi = 0U;
        cur_desc->addr_lo = (u32)(buff_addr);
#endif

        /* set address of next descriptor entry, NULL for last entry */
        next_desc_addr = is_last ? 0U : next_desc_addr;
        if (next_desc_addr % sizeof(FSdifIDmaDesc)) /* make sure dma descriptor aligned and not cross page boundary */
        {
            FSDIF_ERROR("DMA descriptor 0x%x do not align.", next_desc_addr);
            return FSDIF_ERR_DMA_BUF_UNALIGN;
        }

#ifdef __aarch64__
        cur_desc->desc_hi = UPPER_32_BITS(next_desc_addr);
        cur_desc->desc_lo = LOWER_32_BITS(next_desc_addr);
#else
        cur_desc->desc_hi = 0U;
        cur_desc->desc_lo = (u32)(next_desc_addr);
#endif

        buff_addr += cur_desc->len;
        remain_blocks -= trans_blocks;
    }

    /* flush cache of descripor list and transfer buffer */
    FSDIF_DATA_BARRIER();

    FSdifDumpDMADescriptor(instance_p, desc_num);
    return FSDIF_SUCCESS;
}

/**
 * @name: FSdifDMATransferData
 * @msg: Start DMA tranfers for data
 * @return {FError} FSDIF_SUCCESS if transfer issued success, otherwise failed
 * @param {FSdif} *instance_p, instance of controller
 * @param {FSdifData} *data_p, data instance
 */
static FError FSdifDMATransferData(FSdif *const instance_p, FSdifData *data_p)
{
    FASSERT(data_p);
    FError ret = FSDIF_SUCCESS;
    uintptr base_addr = instance_p->config.base_addr;

    /* enable related interrupt */
    FSdifSetInterruptMask(instance_p, FSDIF_GENERAL_INTR, FSDIF_INTS_DATA_MASK, TRUE);
    FSdifSetInterruptMask(instance_p, FSDIF_IDMA_INTR, FSDIF_DMAC_INTS_MASK, TRUE);

    /* fill transfer buffer to DMA descriptor */
    ret = FSdifSetupDMADescriptor(instance_p, data_p);
    if (FSDIF_SUCCESS != ret)
    {
        return ret;
    }

    FSDIF_INFO("Descriptor@%p, trans bytes: %d, block size: %d",
               instance_p->desc_list.first_desc,
               data_p->datalen,
               data_p->blksz);

    /* set transfer info to register */
    FSdifSetDescriptor(base_addr, instance_p->desc_list.first_desc_dma);
    FSdifSetTransBytes(base_addr, data_p->datalen);
    FSdifSetBlockSize(base_addr, data_p->blksz);

    return ret;
}

/**
 * @name: FSdifDMATransfer
 * @msg: Start command and data transfer in DMA mode
 * @return {FError} FSDIF_SUCCESS if transfer success, otherwise failed
 * @param {FSdif} *instance_p, SDIF controller instance
 * @param {FSdifCmdData} *cmd_data_p, contents of transfer command and data
 */
FError FSdifDMATransfer(FSdif *const instance_p, FSdifCmdData *const cmd_data_p)
{
    FASSERT(instance_p);
    FASSERT(cmd_data_p);
    FError ret = FSDIF_SUCCESS;
    uintptr base_addr = instance_p->config.base_addr;

    cmd_data_p->success = FALSE; /* reset cmd transfer status */
    instance_p->cur_cmd = cmd_data_p;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIF_ERROR("Device is not yet initialized!!!");
        return FSDIF_ERR_NOT_INIT;
    }

    if (FSDIF_IDMA_TRANS_MODE != instance_p->config.trans_mode)
    {
        FSDIF_ERROR("Device is not configure in DMA transfer mode.");
        return FSDIF_ERR_INVALID_STATE;
    }

    /* for removable media, check if card exists */
    if ((FALSE == instance_p->config.non_removable) &&
        (FALSE == FSdifCheckIfCardExists(base_addr)))
    {
        FSDIF_ERROR("Card is not detected !!!");
        return FSDIF_ERR_NO_CARD;
    }

    /* wait previous command finished and card not busy */
    ret = FSdifPollWaitBusyCard(instance_p);
    if (FSDIF_SUCCESS != ret)
    {
        return ret;
    }

    FSDIF_WRITE_REG(base_addr, FSDIF_RAW_INTS_OFFSET, 0xffffe);

    /* reset fifo and DMA before transfer */

    ret = FSdifResetCtrl(base_addr, FSDIF_CNTRL_FIFO_RESET | FSDIF_CNTRL_DMA_RESET);
    if (FSDIF_SUCCESS != ret)
    {
        return ret;
    }

    /* enable use of DMA */
    FSDIF_SET_BIT(base_addr, FSDIF_CNTRL_OFFSET, FSDIF_CNTRL_USE_INTERNAL_DMAC);
    FSDIF_SET_BIT(base_addr, FSDIF_BUS_MODE_OFFSET, FSDIF_BUS_MODE_DE);

    if (NULL != cmd_data_p->data_p) /* transfer data */
    {
        ret = FSdifDMATransferData(instance_p,
                                   cmd_data_p->data_p);
    }

    if (FSDIF_SUCCESS == ret) /* transfer command */
    {
        ret = FSdifTransferCmd(instance_p, cmd_data_p);
    }

    return ret;
}

/**
 * @name: FSdifPollWaitDMAEnd
 * @msg: Wait DMA transfer finished by poll
 * @return {FError} FSDIF_SUCCESS if wait success, otherwise wait failed
 * @param {FSdif} *instance_p, SDIF controller instance
 * @param {FSdifCmdData} *cmd_data_p, contents of transfer command and data
 * @param {FSdifRelaxHandler} relax, handler of relax when wait busy
 */
FError FSdifPollWaitDMAEnd(FSdif *const instance_p, FSdifCmdData *const cmd_data_p)
{
    FASSERT(instance_p);
    FASSERT(cmd_data_p);
    FError ret = FSDIF_SUCCESS;
    u32 reg_val;
    int delay;
    const boolean read = cmd_data_p->flag & FSDIF_CMD_FLAG_READ_DATA;
    uintptr base_addr = instance_p->config.base_addr;
    const u32 wait_bits = (NULL == cmd_data_p->data_p) ? FSDIF_INT_CMD_BIT : (FSDIF_INT_CMD_BIT | FSDIF_INT_DTO_BIT);

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIF_ERROR("Device is not yet initialized!!!");
        return FSDIF_ERR_NOT_INIT;
    }

    if (FSDIF_IDMA_TRANS_MODE != instance_p->config.trans_mode)
    {
        FSDIF_ERROR("Device is not configure in DMA transfer mode.");
        return FSDIF_ERR_INVALID_STATE;
    }

    /* wait command done or data timeout */
    delay = FSDIF_TIMEOUT;
    do
    {
        reg_val = FSdifGetRawStatus(base_addr);

        if (delay % 1000 == 0)
        {
            FSDIF_DEBUG("reg_val = 0x%x", reg_val);
        }

        if (instance_p->relax_handler)
        {
            instance_p->relax_handler();
        }
    }
    while (((wait_bits & reg_val) != wait_bits) && (--delay > 0));

    /* clear status to ack data done */
    FSdifClearRawStatus(base_addr);

    if (((wait_bits & reg_val) != wait_bits) && (delay <= 0))
    {
        FSDIF_ERROR("Wait cmd done timeout, raw ints: 0x%x.", reg_val);
        return FSDIF_ERR_CMD_TIMEOUT;
    }

    if (NULL != cmd_data_p->data_p) /* wait data transfer done or timeout */
    {
        /* invalidate cache of transfer buffer */
        if (read)
        {
            FSDIF_DATA_BARRIER();
        }
    }

    if (FSDIF_SUCCESS == ret)
    {
        ret = FSdifGetCmdResponse(instance_p, cmd_data_p);
    }

    return ret;
}

/**
 * @name: FSdifSetIDMAList
 * @msg: Setup DMA descriptor for SDIF controller instance
 * @return {FError} FSDIF_SUCCESS if setup done, otherwise failed
 * @param {FSdif} *instance_p, SDIF controller instance
 * @param {volatile FSdifIDmaDesc} *desc, first item in DMA descriptor lists
 * @param {u32} desc_num, number of items in DMA descriptor lists
 */
FError FSdifSetIDMAList(FSdif *const instance_p, volatile FSdifIDmaDesc *desc, uintptr desc_dma, u32 desc_num)
{
    FASSERT(instance_p);
    FError ret = FSDIF_SUCCESS;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIF_ERROR("Device is not yet initialized!!!");
        return FSDIF_ERR_NOT_INIT;
    }

    if (FSDIF_IDMA_TRANS_MODE != instance_p->config.trans_mode)
    {
        FSDIF_ERROR("Device is not configure in DMA transfer mode.");
        return FSDIF_ERR_INVALID_STATE;
    }

    instance_p->desc_list.first_desc = desc; /* virtual address of first descriptors */
    instance_p->desc_list.first_desc_dma = desc_dma; /* physical address equals with virtual address */
    instance_p->desc_list.desc_num = desc_num; /* num of descriptors in the array */
    instance_p->desc_list.desc_trans_sz = FSDIF_IDMAC_MAX_BUF_SIZE; /* each descriptor can transfer at most 0x1000 bytes data */
    return ret;
}