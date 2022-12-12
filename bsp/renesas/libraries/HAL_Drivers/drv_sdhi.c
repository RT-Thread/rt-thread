/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-03     mazhiyuan    first version
 */

#include <drv_sdhi.h>
struct ra_sdhi sdhi;

#define RTHW_SDIO_LOCK(_sdio) rt_mutex_take(&_sdio->mutex, RT_WAITING_FOREVER)
#define RTHW_SDIO_UNLOCK(_sdio) rt_mutex_release(&_sdio->mutex);

struct rthw_sdio
{
    struct rt_mmcsd_host *host;
    struct ra_sdhi sdhi_des;
    struct rt_event event;
    struct rt_mutex mutex;
};

static struct rt_mmcsd_host *host;

rt_align(SDIO_ALIGN_LEN)
static rt_uint8_t cache_buf[SDIO_BUFF_SIZE];

rt_err_t command_send(sdhi_instance_ctrl_t *p_ctrl, struct rt_mmcsd_cmd *cmd)
{
    uint32_t wait_bit;
    uint32_t timeout = BUSY_TIMEOUT_US;
    volatile sdhi_event_t event;
    struct rt_mmcsd_data *data = cmd->data;
    while (SD_INFO2_CBSY_SDD0MON_IDLE_VAL !=
            (p_ctrl->p_reg->SD_INFO2 & SD_INFO2_CBSY_SDD0MON_IDLE_MASK))
    {
        if (timeout == 0)
        {
            return RT_ETIMEOUT;
        }
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout--;
    }
    p_ctrl->p_reg->SD_INFO1 = 0U;
    p_ctrl->p_reg->SD_INFO2 = 0U;
    p_ctrl->sdhi_event.word = 0U;

    /* Enable response end interrupt. */
    /* Disable access end interrupt and enable response end interrupt. */
    uint32_t mask = p_ctrl->p_reg->SD_INFO1_MASK;
    mask &= (~SDHI_INFO1_RESPONSE_END);
    mask |= SDHI_INFO1_ACCESS_END;
    p_ctrl->p_reg->SD_INFO1_MASK = mask;
    p_ctrl->p_reg->SD_INFO2_MASK = SDHI_INFO2_MASK_CMD_SEND;
    /* Write argument, then command to the SDHI peripheral. */
    p_ctrl->p_reg->SD_ARG = cmd->arg & UINT16_MAX;
    p_ctrl->p_reg->SD_ARG1 = cmd->arg >> 16;

    if ((cmd->flags & CMD_MASK) == CMD_ADTC)
    {
        cmd->cmd_code |= SDHI_CMD_ADTC_EN;
        switch (cmd->flags & RESP_MASK)
        {
        case RESP_R1:
        case RESP_R5:
        case RESP_R6:
        case RESP_R7:
            cmd->cmd_code |= SDHI_CMD_RESP_TYPE_EXT_R1_R5_R6_R7;
            break;
        case RESP_R1B:
            cmd->cmd_code |= SDHI_CMD_RESP_TYPE_EXT_R1B;
            break;
        case RESP_R2:
            cmd->cmd_code |= SDHI_CMD_RESP_TYPE_EXT_R2;
            break;
        case RESP_R3:
        case RESP_R4:
            cmd->cmd_code |= SDHI_CMD_RESP_TYPE_EXT_R3_R4;
            break;
        case RESP_NONE:
            cmd->cmd_code |= SDHI_CMD_RESP_TYPE_EXT_NONE;
            break;
        }
        if (data != RT_NULL)
        {
            if ((data->flags & 7) == DATA_DIR_WRITE)
            {
                cmd->cmd_code &= ~SDHI_CMD_DATA_DIR_READ;
            }
            else if ((data->flags & 7) == DATA_DIR_READ)
            {
                cmd->cmd_code |= SDHI_CMD_DATA_DIR_READ;
            }
        }
    }
    p_ctrl->p_reg->SD_CMD = cmd->cmd_code;

    timeout = 100000;
    while (true)
    {
        /* Check for updates to the event status. */
        event.word = p_ctrl->sdhi_event.word;

        /* Return an error if a hardware error occurred. */
        if (event.bit.event_error)
        {
            cmd->err = -RT_ERROR;
            if ((event.word & HW_SDHI_ERR_CRCE) && (resp_type(cmd) & (RESP_R3 | RESP_R4)))
            {
                if ((cmd->flags & RESP_MASK) == RESP_R2)
                {
                    cmd->resp[0] = (p_ctrl->p_reg->SD_RSP76 << 8) | (p_ctrl->p_reg->SD_RSP54 >> 24);
                    cmd->resp[1] = (p_ctrl->p_reg->SD_RSP54 << 8) | (p_ctrl->p_reg->SD_RSP32 >> 24);
                    cmd->resp[2] = (p_ctrl->p_reg->SD_RSP32 << 8) | (p_ctrl->p_reg->SD_RSP10 >> 24);
                    cmd->resp[3] = (p_ctrl->p_reg->SD_RSP10 << 8);
                }
                else
                {
                    cmd->resp[0] = p_ctrl->p_reg->SD_RSP10;
                }
                cmd->err = RT_EOK;
            }
            if (event.word & HW_SDHI_ERR_RTIMEOUT)
            {
                cmd->err = -RT_ETIMEOUT;
            }
            if (event.word & HW_SDHI_ERR_DTIMEOUT)
            {
                data->err = -RT_ETIMEOUT;
            }
            return -RT_ERROR;
        }
        if (data != RT_NULL)
        {
            wait_bit = SDHI_WAIT_ACCESS_BIT;
        }
        else
        {
            wait_bit = SDHI_WAIT_RESPONSE_BIT;
        }

        /* If the requested bit is set, return success. */
        if (event.word & (1U << wait_bit))
        {
            cmd->err = RT_EOK;
            if ((cmd->flags & RESP_MASK) == RESP_R2)
            {
                cmd->resp[0] = (p_ctrl->p_reg->SD_RSP76 << 8) | (p_ctrl->p_reg->SD_RSP54 >> 24);
                cmd->resp[1] = (p_ctrl->p_reg->SD_RSP54 << 8) | (p_ctrl->p_reg->SD_RSP32 >> 24);
                cmd->resp[2] = (p_ctrl->p_reg->SD_RSP32 << 8) | (p_ctrl->p_reg->SD_RSP10 >> 24);
                cmd->resp[3] = (p_ctrl->p_reg->SD_RSP10 << 8);
            }
            else
            {
                cmd->resp[0] = p_ctrl->p_reg->SD_RSP10;
            }

            return RT_EOK;
        }

        /* Check for timeout. */
        timeout--;
        if (0U == timeout)
        {
            cmd->err = -RT_ETIMEOUT;
            return RT_ERROR;
        }

        /* Wait 1 us for consistent loop timing. */
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
    }
}

rt_err_t transfer_write(sdhi_instance_ctrl_t *const p_ctrl,
                        uint32_t block_count,
                        uint32_t bytes,
                        const uint8_t *p_data)
{
    transfer_info_t *p_info = p_ctrl->p_cfg->p_lower_lvl_transfer->p_cfg->p_info;

    /* When the SD_DMAEN.DMAEN bit is 1, set the SD_INFO2_MASK.BWEM bit to 1 and the SD_INFO2_MASK.BREM bit to 1. */
    p_ctrl->p_reg->SD_INFO2_MASK |= 0x300U;
    p_ctrl->p_reg->SD_DMAEN = 0x2U;

    uint32_t transfer_settings = (uint32_t)TRANSFER_MODE_BLOCK << TRANSFER_SETTINGS_MODE_BITS;
    transfer_settings |= TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_SRC_ADDR_BITS;
    transfer_settings |= TRANSFER_SIZE_4_BYTE << TRANSFER_SETTINGS_SIZE_BITS;

#if SDMMC_CFG_UNALIGNED_ACCESS_ENABLE
    if ((0U != ((uint32_t)p_data & 0x3U)) || (0U != (bytes & 3U)))
    {
        transfer_settings |= TRANSFER_IRQ_EACH << TRANSFER_SETTINGS_IRQ_BITS;
        transfer_settings |= TRANSFER_REPEAT_AREA_SOURCE << TRANSFER_SETTINGS_REPEAT_AREA_BITS;

        /* If the pointer is not 4-byte aligned or the number of bytes is not a multiple of 4, use a temporary buffer.
         * Transfer the first block to the temporary buffer before enabling the transfer.  Subsequent blocks will be
         * transferred from the user buffer to the temporary buffer in an interrupt after each block transfer. */
        rt_memcpy((void *)&p_ctrl->aligned_buff[0], p_data, bytes);
        p_info->p_src = &p_ctrl->aligned_buff[0];

        p_ctrl->transfer_block_current = 1U;
        p_ctrl->transfer_blocks_total = block_count;
        p_ctrl->p_transfer_data = (uint8_t *)&p_data[bytes];
        p_ctrl->transfer_dir = SDHI_TRANSFER_DIR_WRITE;
        p_ctrl->transfer_block_size = bytes;
    }
    else
#endif
    {
        p_info->p_src = p_data;
    }

    p_info->transfer_settings_word = transfer_settings;
    p_info->p_dest = (uint32_t *)(&p_ctrl->p_reg->SD_BUF0);
    p_info->num_blocks = (uint16_t)block_count;

    /* Round up to the nearest multiple of 4 bytes for the transfer. */
    uint32_t words = (bytes + (sizeof(uint32_t) - 1U)) / sizeof(uint32_t);
    p_info->length = (uint16_t)words;
    /* Configure the transfer driver to write to the SD buffer. */
    fsp_err_t err = p_ctrl->p_cfg->p_lower_lvl_transfer->p_api->reconfigure(p_ctrl->p_cfg->p_lower_lvl_transfer->p_ctrl,
                    p_ctrl->p_cfg->p_lower_lvl_transfer->p_cfg->p_info);
    if (FSP_SUCCESS != err)
        return RT_ERROR;
    return RT_EOK;
}

rt_err_t transfer_read(sdhi_instance_ctrl_t *const p_ctrl,
                       uint32_t block_count,
                       uint32_t bytes,
                       void *p_data)
{
    transfer_info_t *p_info = p_ctrl->p_cfg->p_lower_lvl_transfer->p_cfg->p_info;

    /* When the SD_DMAEN.DMAEN bit is 1, set the SD_INFO2_MASK.BWEM bit to 1 and the SD_INFO2_MASK.BREM bit to 1. */
    p_ctrl->p_reg->SD_INFO2_MASK |= 0X300U;
    p_ctrl->p_reg->SD_DMAEN = 0x2U;

    uint32_t transfer_settings = (uint32_t)TRANSFER_MODE_BLOCK << TRANSFER_SETTINGS_MODE_BITS;
    transfer_settings |= TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_DEST_ADDR_BITS;
    transfer_settings |= TRANSFER_SIZE_4_BYTE << TRANSFER_SETTINGS_SIZE_BITS;

#if SDMMC_CFG_UNALIGNED_ACCESS_ENABLE

    /* If the pointer is not 4-byte aligned or the number of bytes is not a multiple of 4, use a temporary buffer.
     * Data will be transferred from the temporary buffer into the user buffer in an interrupt after each block transfer. */
    if ((0U != ((uint32_t)p_data & 0x3U)) || (0U != (bytes & 3U)))
    {
        transfer_settings |= TRANSFER_IRQ_EACH << TRANSFER_SETTINGS_IRQ_BITS;
        p_info->p_dest = &p_ctrl->aligned_buff[0];

        p_ctrl->transfer_block_current = 0U;
        p_ctrl->transfer_blocks_total = block_count;
        p_ctrl->p_transfer_data = (uint8_t *)p_data;
        p_ctrl->transfer_dir = SDHI_TRANSFER_DIR_READ;
        p_ctrl->transfer_block_size = bytes;
    }
    else
#endif
    {
        transfer_settings |= TRANSFER_REPEAT_AREA_SOURCE << TRANSFER_SETTINGS_REPEAT_AREA_BITS;
        p_info->p_dest = p_data;
    }

    p_info->transfer_settings_word = transfer_settings;
    p_info->p_src = (uint32_t *)(&p_ctrl->p_reg->SD_BUF0);
    p_info->num_blocks = (uint16_t)block_count;

    /* Round up to the nearest multiple of 4 bytes for the transfer. */
    uint32_t words = (bytes + (sizeof(uint32_t) - 1U)) / sizeof(uint32_t);
    p_info->length = (uint16_t)words;

    /* Configure the transfer driver to read from the SD buffer. */
    fsp_err_t err = p_ctrl->p_cfg->p_lower_lvl_transfer->p_api->reconfigure(p_ctrl->p_cfg->p_lower_lvl_transfer->p_ctrl,
                    p_ctrl->p_cfg->p_lower_lvl_transfer->p_cfg->p_info);
    if (err != FSP_SUCCESS)
        return RT_ERROR;

    return RT_EOK;
}

void ra_sdhi_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct rthw_sdio *sdio = host->private_data;
    struct rt_mmcsd_data *data;
    static rt_uint8_t *buffer;

    RTHW_SDIO_LOCK(sdio);

    if (req->cmd != RT_NULL)
    {
        data = req->cmd->data;
        if (data != RT_NULL)
        {
            rt_uint32_t size = data->blks * data->blksize;

            RT_ASSERT(size <= SDIO_BUFF_SIZE);

            buffer = (rt_uint8_t *)data->buf;
            if ((rt_uint32_t)data->buf & (SDIO_ALIGN_LEN - 1))
            {
                buffer = cache_buf;
                if (data->flags & DATA_DIR_WRITE)
                {
                    rt_memcpy(cache_buf, data->buf, size);
                }
            }
            if (data->flags & DATA_DIR_WRITE)
            {
                transfer_write(sdio->sdhi_des.instance->p_ctrl, data->blks, data->blksize, buffer);
            }
            else if (data->flags & DATA_DIR_READ)
            {
                transfer_read(sdio->sdhi_des.instance->p_ctrl, data->blks, data->blksize, buffer);
            }
            /* Set the sector count. */
            if (data->blks > 1U)
            {
                ((sdhi_instance_ctrl_t *)sdio->sdhi_des.instance->p_ctrl)->p_reg->SD_STOP = 0x100U;
                ((sdhi_instance_ctrl_t *)sdio->sdhi_des.instance->p_ctrl)->p_reg->SD_SECCNT = data->blks;
            }
            else
            {
                ((sdhi_instance_ctrl_t *)sdio->sdhi_des.instance->p_ctrl)->p_reg->SD_STOP = 0U;
            }
            ((sdhi_instance_ctrl_t *)sdio->sdhi_des.instance->p_ctrl)->p_reg->SD_SIZE = data->blksize;
        }
        rt_enter_critical();
        command_send(sdio->sdhi_des.instance->p_ctrl, req->cmd);
        rt_exit_critical();
        if ((data != RT_NULL) && (data->flags & DATA_DIR_READ) && ((rt_uint32_t)data->buf & (SDIO_ALIGN_LEN - 1)))
        {
            rt_memcpy(data->buf, cache_buf, data->blksize * data->blks);
        }
    }

    if (req->stop != RT_NULL)
    {
        rt_enter_critical();
        command_send(sdio->sdhi_des.instance->p_ctrl, req->stop);
        rt_exit_critical();
    }
    RTHW_SDIO_UNLOCK(sdio);
    mmcsd_req_complete(sdio->host);
}

static rt_err_t clock_rate_set(sdhi_instance_ctrl_t *p_ctrl, uint32_t max_rate)
{
    uint32_t setting = 0xFFU;

    /* Get the runtime frequency of the source of the SD clock */
    uint32_t frequency = R_FSP_SystemClockHzGet(BSP_FEATURE_SDHI_CLOCK);

    /* Iterate over all possible divisors, starting with the smallest, until the resulting clock rate is less than
     * or equal to the requested maximum rate. */
    for (uint32_t divisor_shift = BSP_FEATURE_SDHI_MIN_CLOCK_DIVISION_SHIFT;
            divisor_shift <= 9U;
            divisor_shift++)
    {
        if ((frequency >> divisor_shift) <= max_rate)
        {
            /* If the calculated frequency is less than or equal to the maximum supported by the device,
             * select this frequency. The register setting is the divisor value divided by 4, or 0xFF for no divider. */
            setting = divisor_shift ? ((1U << divisor_shift) >> 2U) : UINT8_MAX;

            /* Set the clock setting. */

            /* The clock register is accessible 8 SD clock counts after the last command completes.  Each register access
             * requires at least one PCLK count, so check the register up to 8 times the maximum PCLK divisor value (512). */
            uint32_t timeout = 8U * 512U;

            while (timeout > 0U)
            {
                /* Do not write to clock control register until this bit is set. */
                if (p_ctrl->p_reg->SD_INFO2_b.SD_CLK_CTRLEN)
                {
                    /* Set the calculated divider and enable clock output to start the 74 clocks required before
                     * initialization. Do not change the automatic clock control setting. */
                    uint32_t clkctrlen = p_ctrl->p_reg->SD_CLK_CTRL & (1U << 9);
                    p_ctrl->p_reg->SD_CLK_CTRL = setting | clkctrlen | (1U << 8);
                    p_ctrl->device.clock_rate = frequency >> divisor_shift;

                    return RT_EOK;
                }

                timeout--;
            }

            /* Valid setting already found, stop looking. */
            break;
        }
    }

    return RT_ERROR;
}

void ra_sdhi_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    struct rthw_sdio *sdio = host->private_data;
    RTHW_SDIO_LOCK(sdio);
    if (io_cfg->bus_width == MMCSD_BUS_WIDTH_1)
    {
        ((sdhi_instance_ctrl_t *)sdio->sdhi_des.instance->p_ctrl)->p_reg->SD_OPTION_b.WIDTH = 1;
    }
    else if (io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
    {
        ((sdhi_instance_ctrl_t *)sdio->sdhi_des.instance->p_ctrl)->p_reg->SD_OPTION_b.WIDTH = 0;
        ((sdhi_instance_ctrl_t *)sdio->sdhi_des.instance->p_ctrl)->p_reg->SD_OPTION_b.WIDTH8 = 0;
    }
    else if (io_cfg->bus_width == MMCSD_BUS_WIDTH_8)
    {
        ((sdhi_instance_ctrl_t *)sdio->sdhi_des.instance->p_ctrl)->p_reg->SD_OPTION_b.WIDTH = 0;
        ((sdhi_instance_ctrl_t *)sdio->sdhi_des.instance->p_ctrl)->p_reg->SD_OPTION_b.WIDTH8 = 1;
    }
    clock_rate_set(sdio->sdhi_des.instance->p_ctrl, io_cfg->clock);
    RTHW_SDIO_UNLOCK(sdio);
}

rt_int32_t ra_sdhi_get_card_status(struct rt_mmcsd_host *host)
{
    sdmmc_status_t status;
    struct rthw_sdio *sdio = host->private_data;
    sdio->sdhi_des.instance->p_api->statusGet(sdio->sdhi_des.instance->p_ctrl, &status);
    return status.card_inserted;
}

void ra_sdhi_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t en)
{
    struct rthw_sdio *sdio = host->private_data;
    sdio->sdhi_des.instance->p_api->ioIntEnable(sdio->sdhi_des.instance->p_ctrl, en);
}

struct rt_mmcsd_host_ops ra_sdhi_ops =
{
    .request = ra_sdhi_request,
    .set_iocfg = ra_sdhi_set_iocfg,
    .get_card_status = ra_sdhi_get_card_status,
    .enable_sdio_irq = ra_sdhi_enable_sdio_irq
};

void sdhi_callback(sdmmc_callback_args_t *p_args)
{
}

struct rt_mmcsd_host *sdio_host_create(struct ra_sdhi *sdhi_des)
{
    struct rt_mmcsd_host *host;
    struct rthw_sdio *sdio = RT_NULL;

    if (sdhi_des == RT_NULL)
        return RT_NULL;

    sdio = rt_malloc(sizeof(struct rthw_sdio));
    if (sdio == RT_NULL)
        return RT_NULL;
    rt_memset(sdio, 0, sizeof(struct rthw_sdio));

    host = mmcsd_alloc_host();
    if (host == RT_NULL)
    {
        rt_free(sdio);
        return RT_NULL;
    }

    rt_memcpy(&sdio->sdhi_des, sdhi_des, sizeof(struct ra_sdhi));

    rt_event_init(&sdio->event, "sdio", RT_IPC_FLAG_FIFO);
    rt_mutex_init(&sdio->mutex, "sdio", RT_IPC_FLAG_FIFO);

    /* set host defautl attributes */
    host->ops = &ra_sdhi_ops;
    host->freq_min = 400 * 1000;
    host->freq_max = SDIO_MAX_FREQ;
    host->valid_ocr = 0X00FFFF80; /* The voltage range supported is 1.65v-3.6v */
#ifndef SDHI_USING_1_BIT
    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_SDIO_IRQ;
#else
    host->flags = MMCSD_MUTBLKWRITE | MMCSD_SUP_SDIO_IRQ;
#endif
    host->max_seg_size = SDIO_BUFF_SIZE;
    host->max_dma_segs = 1;
    host->max_blk_size = 512;
    host->max_blk_count = 512;

    /* link up host and sdio */
    sdio->host = host;
    host->private_data = sdio;

    ra_sdhi_enable_sdio_irq(host, 1);

    /* ready to change */
    mmcsd_change(host);

    return host;
}

int rt_hw_sdhi_init(void)
{
    sdhi.instance = &g_sdmmc0;
    sdhi.instance->p_api->open(sdhi.instance->p_ctrl, sdhi.instance->p_cfg);
    host = sdio_host_create(&sdhi);
    if (host == RT_NULL)
    {
        return -1;
    }
    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_sdhi_init);
