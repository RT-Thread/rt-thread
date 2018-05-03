/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "board_info.h"
#include <rtdef.h>
#include <rtdevice.h>
#include <drivers/mmcsd_core.h>
#include "mmc.h"

//#define FH_MMC_DEBUG
#define MMC_USE_INTERNAL_BUF

#ifdef FH_MMC_DEBUG
#define PRINT_MMC_DBG(fmt, args...)     \
    do                                  \
    {                                   \
        rt_kprintf("FH_MMC_DEBUG: tick-%d, ", rt_tick_get());   \
        rt_kprintf(fmt, ## args);       \
    }                                   \
    while(0)
#else
#define PRINT_MMC_DBG(fmt, args...)  do { } while (0)
#endif

#define PRINT_MMC_REGS(base)                                        \
    do                                                              \
    {                                                               \
        int i_for_marco;                                            \
        rt_uint32_t addr;                                           \
        for(i_for_marco=0; i_for_marco<20; i_for_marco++)           \
        {                                                           \
            addr = base + i_for_marco*4*4;                          \
            rt_kprintf("0x%x: 0x%x, 0x%x, 0x%x, 0x%x\n", addr,      \
                    GET_REG(addr+0x0),                              \
                    GET_REG(addr+0x4),                              \
                    GET_REG(addr+0x8),                              \
                    GET_REG(addr+0xc));                             \
        }                                                           \
    }                                                               \
    while(0)


#define MMC_INTERNAL_DMA_BUF_SIZE (32*1024)
static rt_uint32_t *g_mmc_dma_buf;

static int fh_mmc_write_pio(struct mmc_driver *mmc_drv)
{
    struct fh_mmc_obj *mmc_obj = (struct fh_mmc_obj *)mmc_drv->priv;
    struct rt_mmcsd_cmd *cmd = mmc_drv->cmd;
    struct rt_mmcsd_data *data = RT_NULL;
    rt_uint32_t size;

    if(cmd)
        data = cmd->data;

    if(!data)
    {
        rt_kprintf("ERROR: %s, data is NULL\n", __func__);
        return -RT_EIO;
    }

    size = data->blks * data->blksize;
    PRINT_MMC_DBG("%s, Send %d bytes\n", __func__, size);
    MMC_WriteData(mmc_obj, data->buf, size);
    MMC_ResetFifo(mmc_obj);

    return 0;
}

static int fh_mmc_read_pio(struct mmc_driver *mmc_drv)
{
    struct fh_mmc_obj *mmc_obj = (struct fh_mmc_obj *)mmc_drv->priv;
    struct rt_mmcsd_cmd *cmd = mmc_drv->cmd;
    struct rt_mmcsd_data *data = RT_NULL;
    rt_uint32_t size;
    int ret;

    if(cmd)
        data = cmd->data;

    if(!data)
    {
        rt_kprintf("ERROR: %s, data is NULL\n", __func__);
        return -RT_EIO;
    }

    size = data->blks * data->blksize;
    PRINT_MMC_DBG("%s, read %d bytes\n", __func__, size);
    ret = MMC_ReadData(mmc_obj, data->buf, size);
    if(ret)
    {
        rt_kprintf("ERROR: %s, fifo IO error, ret: %d\n", __func__, ret);
        return -RT_EIO;
    }

    MMC_ResetFifo(mmc_obj);

    return 0;
}


static void fh_mmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    rt_uint32_t clkdiv;
    struct mmc_driver *mmc_drv = host->private_data;
    struct fh_mmc_obj *mmc_obj = (struct fh_mmc_obj *)mmc_drv->priv;

    PRINT_MMC_DBG("%s start\n", __func__);

    //fixme: read from PMU
    //why io_cfg->clock == 0 ?
    if(io_cfg->clock)
    {
        clkdiv = MMC_CLOCK_IN / io_cfg->clock / 2;
        MMC_UpdateClockRegister(mmc_obj, clkdiv);
        PRINT_MMC_DBG("io_cfg->clock: %lu, clock in: %lu, clkdiv: %d\n", io_cfg->clock, MMC_CLOCK_IN, clkdiv);
    }

    if (io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
    {
        MMC_SetCardWidth(mmc_obj, MMC_CARD_WIDTH_4BIT);
        PRINT_MMC_DBG("set to 4-bit mode\n", MMC_CLOCK_IN, clkdiv);
    }
    else
    {
        MMC_SetCardWidth(mmc_obj, MMC_CARD_WIDTH_1BIT);
        PRINT_MMC_DBG("set to 1-bit mode\n", MMC_CLOCK_IN, clkdiv);
    }


    /* maybe switch power to the card */
    switch (io_cfg->power_mode)
    {
        case MMCSD_POWER_OFF:
            break;
        case MMCSD_POWER_UP:
            break;
        case MMCSD_POWER_ON:
            break;
        default:
            rt_kprintf("ERROR: %s, unknown power_mode %d\n", __func__, io_cfg->power_mode);
            break;
    }
    PRINT_MMC_DBG("%s end\n", __func__);
}

static void fh_mmc_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t enable)
{
    struct mmc_driver *mmc_drv = host->private_data;
    struct fh_mmc_obj *mmc_obj = (struct fh_mmc_obj *)mmc_drv->priv;
    rt_uint32_t reg;

    PRINT_MMC_DBG("%s start\n", __func__);

    if (enable)
    {
        MMC_ClearRawInterrupt(mmc_obj, MMC_INT_STATUS_SDIO);
        reg = MMC_GetInterruptMask(mmc_obj);
        reg |= MMC_INT_STATUS_SDIO;
        MMC_SetInterruptMask(mmc_obj, reg);
    }
    else
    {
        reg = MMC_GetInterruptMask(mmc_obj);
        reg &= ~MMC_INT_STATUS_SDIO;
        MMC_SetInterruptMask(mmc_obj, reg);
    }

}

static rt_int32_t fh_mmc_get_card_status(struct rt_mmcsd_host *host)
{
    PRINT_MMC_DBG("%s, start\n", __func__);
    PRINT_MMC_DBG("%s, end\n", __func__);
    return 0;
}

static void fh_mmc_send_command(struct mmc_driver *mmc_drv, struct rt_mmcsd_cmd *cmd)
{
    struct fh_mmc_obj *mmc_obj = (struct fh_mmc_obj *)mmc_drv->priv;
    struct rt_mmcsd_host *host = mmc_drv->host;
    struct rt_mmcsd_req *req = mmc_drv->req;
    //fixme: cmd->data or req->data
    struct rt_mmcsd_data *data = cmd->data;
    int ret;

    rt_uint32_t retries = 0;
    rt_uint32_t cmd_flags = 0;

    PRINT_MMC_DBG("%s, start\n", __func__);

    if (!cmd)
    {
        //fixme: stop dma
        rt_kprintf("ERROR: %s, cmd is NULL\n", __func__);
        return;
    }

    if (data)
    {
        cmd_flags |= MMC_CMD_FLAG_DATA_EXPECTED;
        /* always set data start - also set direction flag for read */
        if (data->flags & DATA_DIR_WRITE)
            cmd_flags |= MMC_CMD_FLAG_WRITE_TO_CARD;

        if (data->flags & DATA_STREAM)
            cmd_flags |= MMC_CMD_FLAG_DATA_STREAM;
    }

    if (cmd == req->stop)
        cmd_flags |= MMC_CMD_FLAG_STOP_TRANSFER;
    else
        cmd_flags |= MMC_CMD_FLAG_WAIT_PREV_DATA;

    switch (resp_type(cmd))
    {
        case RESP_NONE:
            break;
        case RESP_R1:
        case RESP_R5:
        case RESP_R6:
        case RESP_R7:
        case RESP_R1B:
            cmd_flags |= MMC_CMD_FLAG_RESPONSE_EXPECTED;
            cmd_flags |= MMC_CMD_FLAG_CHECK_RESP_CRC;
            break;
        case RESP_R2:
            cmd_flags |= MMC_CMD_FLAG_RESPONSE_EXPECTED;
            cmd_flags |= MMC_CMD_FLAG_CHECK_RESP_CRC;
            cmd_flags |= MMC_CMD_FLAG_LONG_RESPONSE;
            break;
        case RESP_R3:
        case RESP_R4:
            cmd_flags |= MMC_CMD_FLAG_RESPONSE_EXPECTED;
            break;
        default:
            rt_kprintf("ERROR: %s, unknown cmd type %x\n", __func__, resp_type(cmd));
            return;
    }

    if (cmd->cmd_code == GO_IDLE_STATE)
        cmd_flags |= MMC_CMD_FLAG_SEND_INIT;

    /* CMD 11 check switch voltage */
    if (cmd->cmd_code == READ_DAT_UNTIL_STOP)
        cmd_flags |= MMC_CMD_FLAG_SWITCH_VOLTAGE;

    PRINT_MMC_DBG("cmd code: %d, args: 0x%x, resp type: 0x%x, flag: 0x%x\n", cmd->cmd_code, cmd->arg, resp_type(cmd), cmd_flags);
    ret = MMC_SendCommand(mmc_obj, cmd->cmd_code, cmd->arg, cmd_flags);

    if(ret)
    {
        rt_kprintf("ERROR: %s, Send command timeout, cmd: %d, status: 0x%x\n", __func__, cmd->cmd_code, MMC_GetStatus(mmc_obj));
    }

}
static void fh_mmc_perpare_data(struct mmc_driver *mmc_drv)
{
    struct rt_mmcsd_cmd *cmd = mmc_drv->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    struct fh_mmc_obj *mmc_obj = (struct fh_mmc_obj *)mmc_drv->priv;
    rt_uint32_t data_size;
    int i;

    if(!data)
    {
        MMC_SetBlockSize(mmc_obj, 0);
        MMC_SetByteCount(mmc_obj, 0);
        return;
    }

    PRINT_MMC_DBG("%s, start\n", __func__);

    if(MMC_ResetFifo(mmc_obj))
    {
        return;
    }

    data_size = data->blks * data->blksize;

    MMC_SetBlockSize(mmc_obj, data->blksize);

    if(data_size % 4)
    {
        rt_kprintf("ERROR: data_size should be a multiple of 4, but now is %d\n", data_size);
    }
    MMC_SetByteCount(mmc_obj, data_size);

    PRINT_MMC_DBG("%s, set blk size: 0x%x, byte count: 0x%x\n", __func__, data->blksize, data_size);

    if(data_size > MMC_DMA_DESC_BUFF_SIZE * mmc_drv->max_desc)
    {
        rt_kprintf("ERROR: %s, given buffer is too big, size: 0x%x, max: 0x%x\n", __func__, data_size, MMC_DMA_DESC_BUFF_SIZE * mmc_drv->max_desc);
        return;
    }

    if (data_size > MMC_INTERNAL_DMA_BUF_SIZE)
    {
        rt_kprintf("ERROR: please increase MMC_INTERNAL_DMA_BUF_SIZE.\n");
        return;
    }

#ifdef MMC_USE_DMA
#ifdef MMC_USE_INTERNAL_BUF
    if (data->flags & DATA_DIR_WRITE)
    {
        rt_memcpy(g_mmc_dma_buf, data->buf, data_size);
        mmu_clean_invalidated_dcache(g_mmc_dma_buf, data_size);
    }
    else
    {
        mmu_invalidate_dcache(g_mmc_dma_buf, data_size);
    }
    MMC_InitDescriptors(mmc_obj, (rt_uint32_t*)g_mmc_dma_buf, data_size);
    mmu_clean_invalidated_dcache(mmc_obj->descriptors, sizeof(MMC_DMA_Descriptors) * mmc_drv->max_desc);
    MMC_StartDma(mmc_obj);
#else
    MMC_InitDescriptors(mmc_obj, data->buf, data_size);
    mmu_clean_invalidated_dcache(mmc_obj->descriptors, sizeof(MMC_DMA_Descriptors) * mmc_drv->max_desc);
    mmu_clean_invalidated_dcache(data->buf, data_size);
    MMC_StartDma(mmc_obj);
#endif
#endif
    PRINT_MMC_DBG("%s, end\n", __func__);
}

int fh_mmc_wait_card_idle(struct fh_mmc_obj *mmc_obj)
{
    rt_uint32_t tick, timeout;

    tick = rt_tick_get();
    timeout = tick + RT_TICK_PER_SECOND / 2; //500ms

    while(MMC_GetStatus(mmc_obj) & MMC_STATUS_DATA_BUSY)
    {
        tick = rt_tick_get();
        if(tick > timeout)
        {
            return -RT_ETIMEOUT;
        }
    }

    return 0;
}

static int fh_mmc_get_response(struct mmc_driver *mmc_drv, struct rt_mmcsd_cmd *cmd)
{
    int i;
    rt_uint32_t tick, timeout, status;
    struct fh_mmc_obj *mmc_obj = (struct fh_mmc_obj *)mmc_drv->priv;

    cmd->resp[0] = 0;
    cmd->resp[1] = 0;
    cmd->resp[2] = 0;
    cmd->resp[3] = 0;

    tick = rt_tick_get();
    timeout = tick + RT_TICK_PER_SECOND / 2; //500ms

    //fixme: spin_lock_irqsave?
    do
    {
        status = MMC_GetRawInterrupt(mmc_obj);
        tick = rt_tick_get();
        if(tick > timeout)
        {
            PRINT_MMC_DBG("ERROR: %s, get response timeout(cmd is not received by card), RINTSTS: 0x%x, cmd: %d\n", __func__, status, cmd->cmd_code);
            return -RT_ETIMEOUT;
        }
    }
    while(!(status & MMC_INT_STATUS_CMD_DONE));

    MMC_ClearRawInterrupt(mmc_obj, MMC_INT_STATUS_CMD_DONE);

    for (i = 0; i < 4; i++)
    {
        if (resp_type(cmd) == RESP_R2)
        {
            cmd->resp[i] = MMC_GetResponse(mmc_obj, 3 - i);
            //fixme : R2 must delay some time here ,when use UHI card, need check why
            //1ms
            //rt_thread_sleep(RT_TICK_PER_SECOND / 100);
        }
        else
        {
            cmd->resp[i] = MMC_GetResponse(mmc_obj, i);
        }
    }

    PRINT_MMC_DBG("resp: 0x%x, 0x%x, 0x%x, 0x%x\n", cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);

    if (status & MMC_INT_STATUS_RESPONSE_TIMEOUT)
    {
        MMC_ClearRawInterrupt(mmc_obj, MMC_INT_STATUS_RESPONSE_TIMEOUT);
        PRINT_MMC_DBG("ERROR: %s, get response timeout, RINTSTS: 0x%x\n", __func__, status);
        return -RT_ETIMEOUT;
    }

    else if (status & (MMC_INT_STATUS_RESP_CRC_ERROR | MMC_INT_STATUS_RESPONSE_ERROR))
    {
        MMC_ClearRawInterrupt(mmc_obj, MMC_INT_STATUS_RESP_CRC_ERROR | MMC_INT_STATUS_RESPONSE_ERROR);
        rt_kprintf("ERROR: %s, response error or response crc error, RINTSTS: 0x%x\n", __func__, status);
        //return -RT_ERROR;
    }

    return 0;
}

static int fh_mmc_start_transfer(struct mmc_driver *mmc_drv)
{
    struct fh_mmc_obj *mmc_obj = (struct fh_mmc_obj *)mmc_drv->priv;
    struct rt_mmcsd_host *host = mmc_drv->host;
    struct rt_mmcsd_req *req = mmc_drv->req;
    struct rt_mmcsd_cmd *cmd = mmc_drv->cmd;
    struct rt_mmcsd_data *data = RT_NULL;
    int ret;
    rt_uint32_t interrupt, status, reg;

    if(cmd)
        data = cmd->data;

    if(!data)
    {
        return 0;
    }

    PRINT_MMC_DBG("%s, start\n", __func__);

    //fixme: spin_lock_irqsave(&host->lock, flags);
    //open data interrupts
    reg = MMC_GetInterruptMask(mmc_obj);
    reg |= MMC_INT_STATUS_DATA;
    MMC_SetInterruptMask(mmc_obj, reg);

    //fixme: spin_unlock_irqrestore(&host->lock, flags);
    ret = rt_completion_wait(&mmc_drv->transfer_completion, RT_TICK_PER_SECOND * 5);

    reg = MMC_GetInterruptMask(mmc_obj);
    reg &= ~MMC_INT_STATUS_DATA;
    MMC_SetInterruptMask(mmc_obj, reg);

    if(ret)
    {
        //fixme: error handle
        cmd->err = ret;
        interrupt = MMC_GetRawInterrupt(mmc_obj);
        status = MMC_GetStatus(mmc_obj);
        rt_kprintf("ERROR: %s, transfer timeout, ret: %d, RINTSTS: 0x%x, STATUS: 0x%x\n", __func__, ret, interrupt, status);
        //PRINT_MMC_REGS(mmc_obj->base);
        return -RT_ETIMEOUT;
    }

    data->bytes_xfered = data->blks * data->blksize;

#ifdef MMC_USE_INTERNAL_BUF
    if (!(data->flags & DATA_DIR_WRITE))
    {
        rt_memcpy(data->buf, g_mmc_dma_buf, data->bytes_xfered);
        mmu_invalidate_dcache(g_mmc_dma_buf, data->bytes_xfered);
    }
#endif

    return 0;
}

static void fh_mmc_complete_request(struct mmc_driver *mmc_drv)
{
    struct fh_mmc_obj *mmc_obj = (struct fh_mmc_obj *)mmc_drv->priv;
#ifdef MMC_USE_DMA
    MMC_StopDma(mmc_obj);
#endif
    mmc_drv->cmd = RT_NULL;
    mmc_drv->req = RT_NULL;
    mmc_drv->data = RT_NULL;

    rt_memset(mmc_obj->descriptors, 0, 4096);

    MMC_SetBlockSize(mmc_obj, 0);
    MMC_SetByteCount(mmc_obj, 0);

    mmcsd_req_complete(mmc_drv->host);
}

static void fh_mmc_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    int ret;
    struct mmc_driver *mmc_drv = host->private_data;
    struct rt_mmcsd_cmd *cmd = req->cmd;
    struct fh_mmc_obj *mmc_obj = (struct fh_mmc_obj *)mmc_drv->priv;

    PRINT_MMC_DBG("%s start\n", __func__);

    mmc_drv->req = req;
    mmc_drv->cmd = cmd;

    rt_completion_init(&mmc_drv->transfer_completion);

    ret = fh_mmc_wait_card_idle(mmc_obj);

    if (ret)
    {
        rt_kprintf("ERROR: %s, data transfer timeout, status: 0x%x\n", __func__, MMC_GetStatus(mmc_obj));
        return;
    }

    fh_mmc_perpare_data(mmc_drv);
    fh_mmc_send_command(mmc_drv, cmd);
    ret = fh_mmc_get_response(mmc_drv, cmd);
    if(ret)
    {
        cmd->err = ret;
        rt_kprintf("%s,get response returns %d, cmd: %d\n", __func__, ret, cmd->cmd_code);
        goto out;
    }
    fh_mmc_start_transfer(mmc_drv);

    if(req->stop)
    {
        /* send stop command */
        PRINT_MMC_DBG("%s send stop\n", __func__);
        fh_mmc_send_command(mmc_drv, req->stop);
    }

out:
    fh_mmc_complete_request(mmc_drv);
    PRINT_MMC_DBG("%s end\n", __func__);
}

static const struct rt_mmcsd_host_ops fh_mmc_ops =
{
    .request            = fh_mmc_request,
    .set_iocfg          = fh_mmc_set_iocfg,
    .enable_sdio_irq    = fh_mmc_enable_sdio_irq,
    .get_card_status    = fh_mmc_get_card_status,
};

static void fh_mmc_interrupt(int irq, void *param)
{
    struct mmc_driver *mmc_drv = (struct mmc_driver *)param;
    struct fh_mmc_obj *mmc_obj = (struct fh_mmc_obj *)mmc_drv->priv;
    struct rt_mmcsd_req *req = mmc_drv->req;
    struct rt_mmcsd_cmd *cmd = mmc_drv->cmd;
    struct rt_mmcsd_data *data;
    rt_uint32_t status;

    if (cmd && cmd->data)
    {
        data = cmd->data;
    }

    status = MMC_GetUnmaskedInterrupt(mmc_obj);
    PRINT_MMC_DBG("unmasked interrupts: 0x%x\n", status);

    if(status & MMC_INT_STATUS_CARD_DETECT)
    {
        rt_uint32_t card_status = MMC_GetCardStatus(mmc_obj);

        if (card_status == CARD_UNPLUGED)
        {
            rt_kprintf("card disconnected\n");
        }
        else
        {
            rt_kprintf("card connected\n");
        }
        mmcsd_change(mmc_drv->host);
    }

    if (status & MMC_INT_STATUS_SDIO)
    {
        //fixme: handle sdio
        //mmc_signal_sdio_irq ?
    }

    if(status & MMC_INIT_STATUS_DATA_ERROR)
    {
        rt_kprintf("ERROR: %s, data error, status: 0x%x\n", __func__, status);
    }

    if (status & MMC_INT_STATUS_TRANSFER_OVER)
    {
        //MMC_ResetFifo(mmc_obj);
        //rt_completion_done(&mmc_drv->transfer_completion);
    }

    if (status & MMC_INT_STATUS_TX_REQUEST)
    {
        fh_mmc_write_pio(mmc_drv);
    }

    if (status & MMC_INT_STATUS_RX_REQUEST)
    {
        fh_mmc_read_pio(mmc_drv);
    }

    MMC_ClearRawInterrupt(mmc_obj, MMC_INT_STATUS_ALL);
    rt_completion_done(&mmc_drv->transfer_completion);
}

int fh_mmc_probe(void *priv_data)
{
    struct mmc_driver *mmc_drv;
    struct rt_mmcsd_host *host;
    struct fh_mmc_obj *mmc_obj = (struct fh_mmc_obj *)priv_data;

    PRINT_MMC_DBG("%s start\n", __func__);

    mmc_drv = (struct mmc_driver*)rt_malloc(sizeof(struct mmc_driver));
    rt_memset(mmc_drv, 0, sizeof(struct mmc_driver));
    mmc_drv->priv = mmc_obj;

    host = mmcsd_alloc_host();
    if (!host)
    {
        rt_kprintf("ERROR: %s, failed to malloc host\n", __func__);
        return -RT_ENOMEM;
    }

    mmc_obj->descriptors = (MMC_DMA_Descriptors*)rt_malloc(4096+64);
    mmc_obj->descriptors = (MMC_DMA_Descriptors*)(((UINT32)(mmc_obj->descriptors)+31)&(~31)); //cache-line aligned...

    g_mmc_dma_buf = rt_malloc(MMC_INTERNAL_DMA_BUF_SIZE+64);
    g_mmc_dma_buf = (rt_uint32_t*)(((rt_uint32_t)g_mmc_dma_buf+31) & (~31));

    if(!mmc_obj->descriptors)
    {
        rt_kprintf("ERROR: %s, failed to malloc dma descriptors\n", __func__);
        return -RT_ENOMEM;
    }

    rt_memset(mmc_obj->descriptors, 0, 4096);
    mmc_drv->max_desc = 4096 / (sizeof(MMC_DMA_Descriptors));

    host->ops = &fh_mmc_ops;
    host->freq_min = MMC_FEQ_MIN;
    host->freq_max = MMC_FEQ_MAX;
    host->valid_ocr = VDD_32_33 | VDD_33_34;

    host->flags = MMCSD_MUTBLKWRITE | \
                MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ;
    host->max_seg_size = MMC_DMA_DESC_BUFF_SIZE;
    host->max_dma_segs = mmc_drv->max_desc;
    host->max_blk_size = 512;
    //fixme: max_blk_count?
    host->max_blk_count = 2048;
    host->private_data = mmc_drv;

    mmc_drv->host = host;
    gpio_request(mmc_obj->power_pin_gpio);
    gpio_direction_output(mmc_obj->power_pin_gpio, 0);

    MMC_Init(mmc_obj);

    if(mmc_obj->id == 0){
        rt_hw_interrupt_install(mmc_obj->irq, fh_mmc_interrupt, (void *)mmc_drv, "mmc_isr_0");
    }
    else if(mmc_obj->id == 1){
        rt_hw_interrupt_install(mmc_obj->irq, fh_mmc_interrupt, (void *)mmc_drv, "mmc_isr_1");
    }

    rt_hw_interrupt_umask(mmc_obj->irq);
    mmcsd_change(host);

    MMC_SetInterruptMask(mmc_obj, MMC_INT_STATUS_CARD_DETECT);

    PRINT_MMC_DBG("%s end\n", __func__);

    return 0;
}

int fh_mmc_exit(void *priv_data)
{
    return 0;
}

struct fh_board_ops mmc_driver_ops =
{
        .probe = fh_mmc_probe,
        .exit = fh_mmc_exit,
};

void rt_hw_mmc_init(void)
{
    PRINT_MMC_DBG("%s start\n", __func__);
    fh_board_driver_register("mmc", &mmc_driver_ops);
    PRINT_MMC_DBG("%s end\n", __func__);
}
