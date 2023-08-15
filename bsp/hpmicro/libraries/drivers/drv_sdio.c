/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-02-23   HPMicro     First version
 * 2022-07-19   HPMicro     Fixed the multi-block read/write issue
 * 2023-07-27   HPMicro     Fixed clock setting issue
 * 2023-08-02   HPMicro     Add speed mode setting
 */
#include <rtthread.h>

#ifdef BSP_USING_SDXC
#include <rthw.h>
#include <rtdevice.h>
#include <rtdbg.h>

#include "board.h"
#include "hpm_sdxc_drv.h"
#include "hpm_l1c_drv.h"


#define CACHE_LINESIZE                  HPM_L1C_CACHELINE_SIZE
#define SDXC_ADMA_TABLE_WORDS           (2U)
#define SDXC_AMDA2_ADDR_ALIGN           (4U)
#define SDXC_DATA_TIMEOUT               (0xFU)

#define SDXC_CACHELINE_ALIGN_DOWN(x)    HPM_L1C_CACHELINE_ALIGN_DOWN(x)
#define SDXC_CACHELINE_ALIGN_UP(x)      HPM_L1C_CACHELINE_ALIGN_UP(x)
#define SDXC_IS_CACHELINE_ALIGNED(n)    ((uint32_t)(n) % (uint32_t)(CACHE_LINESIZE) == 0U)

struct hpm_mmcsd
{
    struct rt_mmcsd_host *host;
    struct rt_mmcsd_req *req;
    struct rt_mmcsd_cmd *cmd;
    struct rt_timer *timer;
    rt_uint32_t *buf;
    SDXC_Type *sdxc_base;
    int32_t irq_num;
    uint32_t *sdxc_adma2_table;

    uint8_t power_mode;
    uint8_t bus_width;
    uint8_t timing;
    uint8_t bus_mode;
    uint32_t freq;

};

static void hpm_sdmmc_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req);
static void hpm_sdmmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg);
static void hpm_sdmmc_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t en);
static void hpm_sdmmc_host_recovery(SDXC_Type *base);
static int hpm_sdmmc_transfer(SDXC_Type *base, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer);


static const struct rt_mmcsd_host_ops hpm_mmcsd_host_ops =
{
    .request = hpm_sdmmc_request,
    .set_iocfg = hpm_sdmmc_set_iocfg,
    .get_card_status = NULL,
    .enable_sdio_irq = NULL, // Do not use the interrupt mode, use DMA instead
};

/* Place the ADMA2 table to non-cacheable region */
ATTR_PLACE_AT_NONCACHEABLE static uint32_t s_sdxc_adma2_table[SDXC_ADMA_TABLE_WORDS];


static int hpm_sdmmc_transfer(SDXC_Type *base, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer)
{
    hpm_stat_t status;
    sdxc_command_t *cmd = xfer->command;
    sdxc_data_t *data = xfer->data;
    status = sdxc_transfer_nonblocking(base, dma_config, xfer);
    if (status != status_success)
    {
        return -RT_ERROR;
    }
    /* Wait until idle */
    volatile uint32_t interrupt_status = sdxc_get_interrupt_status(base);
    while (!IS_HPM_BITMASK_SET(interrupt_status, SDXC_INT_STAT_CMD_COMPLETE_MASK))
    {
        interrupt_status = sdxc_get_interrupt_status(base);
        status = sdxc_parse_interrupt_status(base);
        HPM_BREAK_IF(status != status_success);
    }
    sdxc_clear_interrupt_status(base, SDXC_INT_STAT_CMD_COMPLETE_MASK);
    if (status == status_success)
    {
        status = sdxc_receive_cmd_response(base, cmd);
    }
    if ((status == status_success) && (data != RT_NULL))
    {
        interrupt_status = sdxc_get_interrupt_status(base);
        while (!IS_HPM_BITMASK_SET(interrupt_status, SDXC_INT_STAT_XFER_COMPLETE_MASK | SDXC_STS_ERROR))
        {
            interrupt_status = sdxc_get_interrupt_status(base);
            status = sdxc_parse_interrupt_status(base);
            HPM_BREAK_IF(status != status_success);
        }
    }

    return (status == status_success) ? RT_EOK : -RT_ERROR;
}

/**
 * !@brief SDMMC request implementation based on HPMicro SDXC Host
 */
static void hpm_sdmmc_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(host->private_data != RT_NULL);
    RT_ASSERT(req != RT_NULL);
    RT_ASSERT(req->cmd != RT_NULL);

    sdxc_adma_config_t adma_config = { 0 };
    sdxc_xfer_t xfer = { 0 };
    sdxc_command_t sdxc_cmd = { 0 };
    sdxc_data_t sdxc_data = { 0 };
    uint32_t *aligned_buf = NULL;
    hpm_stat_t err = status_invalid_argument;
    struct hpm_mmcsd *mmcsd = (struct hpm_mmcsd *) host->private_data;
    struct rt_mmcsd_cmd *cmd = req->cmd;
    struct rt_mmcsd_data *data = cmd->data;

    /*　configure command　*/
    sdxc_cmd.cmd_index = cmd->cmd_code;
    sdxc_cmd.cmd_argument = cmd->arg;
    sdxc_cmd.cmd_type = (cmd->cmd_code == STOP_TRANSMISSION) ? sdxc_cmd_type_abort_cmd : sdxc_cmd_type_normal_cmd;

    switch (cmd->flags & RESP_MASK)
    {
    case RESP_NONE:
        sdxc_cmd.resp_type = sdxc_dev_resp_none;
        break;
    case RESP_R1:
        sdxc_cmd.resp_type = sdxc_dev_resp_r1;
        break;
    case RESP_R1B:
        sdxc_cmd.resp_type = sdxc_dev_resp_r1b;
        break;
    case RESP_R2:
        sdxc_cmd.resp_type = sdxc_dev_resp_r2;
        break;
    case RESP_R3:
        sdxc_cmd.resp_type = sdxc_dev_resp_r3;
        break;
    case RESP_R4:
        sdxc_cmd.resp_type = sdxc_dev_resp_r4;
        break;
    case RESP_R6:
        sdxc_cmd.resp_type = sdxc_dev_resp_r6;
        break;
    case RESP_R7:
        sdxc_cmd.resp_type = sdxc_dev_resp_r7;
        break;
    case RESP_R5:
        sdxc_cmd.resp_type = sdxc_dev_resp_r5;
        break;
    default:
        RT_ASSERT(NULL);
        break;
    }
    sdxc_cmd.cmd_flags = 0UL;
    xfer.command = &sdxc_cmd;
    if (data != NULL)
    {
        sdxc_data.enable_auto_cmd12 = false;
        sdxc_data.enable_auto_cmd23 = false;

        sdxc_data.enable_ignore_error = false;
        sdxc_data.data_type = sdxc_xfer_data_normal;
        sdxc_data.block_size = data->blksize;
        sdxc_data.block_cnt = data->blks;

        /* configure adma2 */
        adma_config.dma_type = sdxc_dmasel_adma2;
        adma_config.adma_table = (uint32_t*) core_local_mem_to_sys_address(BOARD_RUNNING_CORE,
                (uint32_t) mmcsd->sdxc_adma2_table);
        adma_config.adma_table_words = SDXC_ADMA_TABLE_WORDS;

        if ((req->data->flags & DATA_DIR_WRITE) != 0U)
        {
            uint32_t write_size = data->blks * data->blksize;
            if (!SDXC_IS_CACHELINE_ALIGNED(data->buf) || !SDXC_IS_CACHELINE_ALIGNED(write_size))
            {
                write_size = SDXC_CACHELINE_ALIGN_UP(write_size);
                aligned_buf = (uint32_t *) rt_malloc_align(write_size, CACHE_LINESIZE);
                rt_memcpy(aligned_buf, data->buf, write_size);
                sdxc_data.tx_data = aligned_buf;
                rt_enter_critical();
                l1c_dc_flush((uint32_t) sdxc_data.tx_data, write_size);
                rt_exit_critical();
            }
            else
            {
                sdxc_data.tx_data = (uint32_t const *) core_local_mem_to_sys_address(BOARD_RUNNING_CORE,
                        (uint32_t) data->buf);
                rt_enter_critical();
                l1c_dc_flush((uint32_t) data->buf, write_size);
                rt_exit_critical();
            }
            sdxc_data.rx_data = NULL;
        }
        else
        {
            uint32_t read_size = data->blks * data->blksize;
            if (!SDXC_IS_CACHELINE_ALIGNED(data->buf) || !SDXC_IS_CACHELINE_ALIGNED(read_size))
            {
                uint32_t aligned_read_size = SDXC_CACHELINE_ALIGN_UP(read_size);
                aligned_buf = (uint32_t *) rt_malloc_align(aligned_read_size, CACHE_LINESIZE);
                sdxc_data.rx_data = aligned_buf;
            }
            else
            {
                sdxc_data.rx_data = (uint32_t*) core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t) data->buf);
            }
            sdxc_data.tx_data = NULL;
        }
        xfer.data = &sdxc_data;
    }
    else
    {
        xfer.data = NULL;
    }

    if ((req->data->blks > 1) && ((cmd->cmd_code == READ_MULTIPLE_BLOCK) || ((cmd->cmd_code == WRITE_MULTIPLE_BLOCK))))
    {
        xfer.data->enable_auto_cmd12 = true;
    }

    err = hpm_sdmmc_transfer(mmcsd->sdxc_base, &adma_config, &xfer);
    LOG_I("cmd=%d, arg=%x\n", cmd->cmd_code, cmd->arg);
    if (err != status_success)
    {
        hpm_sdmmc_host_recovery(mmcsd->sdxc_base);
        LOG_E(" ***hpm_sdmmc_transfer error: %d*** -->\n", err);
        cmd->err = -RT_ERROR;
    }
    else
    {
        LOG_I(" ***hpm_sdmmc_transfer passed: %d*** -->\n", err);
        if (sdxc_cmd.resp_type == sdxc_dev_resp_r2)
        {
            LOG_I("resp:0x%08x 0x%08x 0x%08x 0x%08x\n", sdxc_cmd.response[0],
                    sdxc_cmd.response[1], sdxc_cmd.response[2], sdxc_cmd.response[3]);
        }
        else
        {
            LOG_I("resp:0x%08x\n", sdxc_cmd.response[0]);
        }
    }
    if ((sdxc_data.rx_data != NULL) && (cmd->err == RT_EOK))
    {
        uint32_t read_size = data->blks * data->blksize;
        if (aligned_buf != NULL)
        {
            uint32_t aligned_read_size = SDXC_CACHELINE_ALIGN_UP(read_size);
            rt_enter_critical();
            l1c_dc_invalidate((uint32_t) aligned_buf, aligned_read_size);
            rt_exit_critical();
            rt_memcpy(data->buf, aligned_buf, read_size);
        }
        else
        {
            rt_enter_critical();
            l1c_dc_invalidate((uint32_t) data->buf, read_size);
            rt_exit_critical();
        }
    }

    if (aligned_buf != NULL)
    {
        rt_free_align(aligned_buf);
        aligned_buf = NULL;
    }

    if ((cmd->flags & RESP_MASK) == RESP_R2)
    {
        cmd->resp[3] = sdxc_cmd.response[0];
        cmd->resp[2] = sdxc_cmd.response[1];
        cmd->resp[1] = sdxc_cmd.response[2];
        cmd->resp[0] = sdxc_cmd.response[3];
    }
    else
    {
        cmd->resp[0] = sdxc_cmd.response[0];
    }

    mmcsd_req_complete(host);
}

/**
 * !@brief Set IO Configuration for HPMicro IO and SDXC Host
 */
static void hpm_sdmmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(host->private_data != RT_NULL);
    RT_ASSERT(io_cfg != RT_NULL);

    struct hpm_mmcsd *mmcsd = (struct hpm_mmcsd *) host->private_data;
    uint32_t vdd = io_cfg->vdd;
    if (io_cfg->power_mode != mmcsd->power_mode)
    {
        switch(io_cfg->power_mode)
        {
        case MMCSD_POWER_OFF:
            board_sd_power_switch(mmcsd->sdxc_base, false);
            break;
        case MMCSD_POWER_ON:
            board_sd_power_switch(mmcsd->sdxc_base, true);
            break;
        case MMCSD_POWER_UP:
            board_sd_power_switch(mmcsd->sdxc_base, false);
            rt_thread_mdelay(10);
            board_sd_power_switch(mmcsd->sdxc_base, true);
            break;
        default:
            /* Do nothing */
            break;
        }
        mmcsd->power_mode = io_cfg->power_mode;
    }

    if (mmcsd->bus_width != io_cfg->bus_width)
    {
        switch (io_cfg->bus_width)
        {
        case MMCSD_BUS_WIDTH_4:
            sdxc_set_data_bus_width(mmcsd->sdxc_base, sdxc_bus_width_4bit);
            break;
        case MMCSD_BUS_WIDTH_8:
            sdxc_set_data_bus_width(mmcsd->sdxc_base, sdxc_bus_width_8bit);
            break;
        default:
            sdxc_set_data_bus_width(mmcsd->sdxc_base, sdxc_bus_width_1bit);
            break;
        }
        mmcsd->bus_width = io_cfg->bus_width;
    }

    if (mmcsd->timing != io_cfg->timing)
    {
        switch (io_cfg->timing)
        {
        case MMCSD_TIMING_LEGACY:
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_sd_speed_normal);
            break;
        case MMCSD_TIMING_SD_HS:
        case MMCSD_TIMING_MMC_HS:
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_sd_speed_high);
            break;
        case MMCSD_TIMING_UHS_SDR12:
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_sd_speed_sdr12);
            break;
        case MMCSD_TIMING_UHS_SDR25:
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_sd_speed_sdr25);
            break;
        case MMCSD_TIMING_UHS_SDR50:
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_sd_speed_sdr50);
            break;
        case MMCSD_TIMING_UHS_SDR104:
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_sd_speed_sdr104);
            break;
        case MMCSD_TIMING_UHS_DDR50:
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_sd_speed_ddr50);
            break;
        case MMCSD_TIMING_MMC_DDR52:
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_emmc_speed_high_speed_ddr);
            break;
        case MMCSD_TIMING_MMC_HS200:
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_emmc_speed_hs200);
            break;
        case MMCSD_TIMING_MMC_HS400:
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_emmc_speed_hs400);
            break;
        }
        mmcsd->timing = io_cfg->timing;
    }

    board_init_sd_pins(mmcsd->sdxc_base);
    uint32_t sdxc_clock = io_cfg->clock;
    if (sdxc_clock != 0U)
    {
        if (mmcsd->freq != sdxc_clock)
        {
            /* Ensure request frequency from mmcsd stack level doesn't exceed maximum supported frequency by host */
            uint32_t clock_freq = MIN(mmcsd->host->freq_max, sdxc_clock);
            board_sd_configure_clock(mmcsd->sdxc_base, clock_freq);
            mmcsd->freq = sdxc_clock;
        }
    }
}

static void hpm_sdmmc_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t en)
{
    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(host->private_data != RT_NULL);

    struct hpm_mmcsd *mmcsd = (struct hpm_mmcsd *) host->private_data;
    if (en != 0)
    {
        intc_m_enable_irq_with_priority(mmcsd->irq_num, 1);
    }
    else
    {
        intc_m_disable_irq(mmcsd->irq_num);
    }
}

static void hpm_sdmmc_host_recovery(SDXC_Type *base)
{
    uint32_t pstate = sdxc_get_present_status(base);
    bool need_reset_cmd_line = false;
    bool need_reset_data_line = false;

    if ((pstate & SDXC_PSTATE_CMD_INHIBIT_MASK) != 0U)
    {
        /* Reset command line */
        need_reset_cmd_line = true;
    }

    if ((pstate & SDXC_PSTATE_DAT_INHIBIT_MASK) != 0U)
    {
        /* Reset data line */
        need_reset_data_line = true;
    }

    uint32_t int_stat = sdxc_get_interrupt_status(base);

    if ((int_stat & 0xF0000UL) != 0U)
    {
        need_reset_cmd_line = true;
    }
    if ((int_stat & 0x700000) != 0U)
    {
        need_reset_data_line = true;
    }

    if (need_reset_cmd_line)
    {
        sdxc_reset(base, sdxc_reset_cmd_line, 0xFFFFUL);
    }
    if (need_reset_data_line)
    {
        sdxc_reset(base, sdxc_reset_data_line, 0xFFFFUL);
    }

    if (need_reset_cmd_line || need_reset_data_line)
    {
        sdxc_clear_interrupt_status(base, ~0UL);
    }

    rt_thread_mdelay(10);
    LOG_E("%s\n", __func__);
}

int rt_hw_sdio_init(void)
{
    rt_err_t err = RT_EOK;

    struct rt_mmcsd_host *host = NULL;
    struct hpm_mmcsd *mmcsd = NULL;
    do
    {
        host = mmcsd_alloc_host();
        if (host == NULL)
        {
            err = -RT_ERROR;
            break;
        }
        mmcsd = rt_malloc(sizeof(struct hpm_mmcsd));
        if (mmcsd == NULL)
        {
            LOG_E("allocate hpm_mmcsd failed\n");
            err = -RT_ERROR;
            break;
        }

        rt_memset(mmcsd, 0, sizeof(struct hpm_mmcsd));
        mmcsd->sdxc_base = BOARD_APP_SDCARD_SDXC_BASE;
        mmcsd->sdxc_adma2_table = s_sdxc_adma2_table;

        host->ops = &hpm_mmcsd_host_ops;
        host->freq_min = 375000;
        host->freq_max = 50000000;
        host->valid_ocr = VDD_30_31 | VDD_31_32 | VDD_32_33 | VDD_33_34;
        host->flags = MMCSD_MUTBLKWRITE | MMCSD_BUSWIDTH_4 | MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ;

        host->max_seg_size = 65535;
        host->max_dma_segs = 2;
        host->max_blk_size = 512;
        host->max_blk_count = 4096;

        mmcsd->host = host;

        /* Perform necessary initialization */
        board_sd_configure_clock(mmcsd->sdxc_base, 375000);

        sdxc_config_t sdxc_config = { 0 };
        sdxc_config.data_timeout = SDXC_DATA_TIMEOUT;
        sdxc_init(mmcsd->sdxc_base, &sdxc_config);

        host->private_data = mmcsd;

        mmcsd_change(host);

    } while (false);

    if (err != RT_EOK)
    {
        if (host != NULL)
        {
            mmcsd_free_host(host);
            host = NULL;
        }
    }

    return err;
}

INIT_DEVICE_EXPORT(rt_hw_sdio_init);
#endif
