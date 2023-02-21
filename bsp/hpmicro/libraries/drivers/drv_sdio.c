/*
 * Copyright (c) 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-02-23   hpmicro     First version
 * 2022-07-19   hpmicro     Fixed the multi-block read/write issue
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

#define SDXC_CACHELINE_ALIGN_DOWN(x)    ((uint32_t)(x) & ~((uint32_t)(CACHE_LINESIZE) - 1UL))
#define SDXC_CACHELINE_ALIGN_UP(x)      SDXC_CACHELINE_ALIGN_DOWN((uint32_t)(x) + (uint32_t)(CACHE_LINESIZE) - 1U)
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
};

static void hpm_sdmmc_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req);
static void hpm_sdmmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg);
static void hpm_sdmmc_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t en);
static void hpm_sdmmc_host_recovery(SDXC_Type *base);

static const struct rt_mmcsd_host_ops hpm_mmcsd_host_ops =
{
    .request = hpm_sdmmc_request,
    .set_iocfg = hpm_sdmmc_set_iocfg,
    .get_card_status = NULL,
    .enable_sdio_irq = NULL, // Do not use the interrupt mode, use DMA instead
};

/* Place the ADMA2 table to non-cacheable region */
ATTR_PLACE_AT_NONCACHEABLE static uint32_t s_sdxc_adma2_table[SDXC_ADMA_TABLE_WORDS];

/**
 * !@brief SDMMC request implementation based on HPMicro SDXC Host
 */
static void hpm_sdmmc_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct hpm_mmcsd *mmcsd;
    struct rt_mmcsd_cmd *cmd;
    struct rt_mmcsd_data *data;
    sdxc_adma_config_t adma_config = { 0 };
    sdxc_xfer_t xfer = { 0 };
    sdxc_command_t sdxc_cmd = { 0 };
    sdxc_data_t sdxc_data = { 0 };
    uint32_t *aligned_buf = NULL;
    hpm_stat_t err = status_invalid_argument;

    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(host->private_data != RT_NULL);
    RT_ASSERT(req != RT_NULL);
    RT_ASSERT(req->cmd != RT_NULL);

    mmcsd = (struct hpm_mmcsd *) host->private_data;

    cmd = req->cmd;

    data = cmd->data;

    /*　configure command　*/
    sdxc_cmd.cmd_index = cmd->cmd_code;
    sdxc_cmd.cmd_argument = cmd->arg;
    if (cmd->cmd_code == STOP_TRANSMISSION)
    {
        sdxc_cmd.cmd_type = sdxc_cmd_type_abort_cmd;
    }
    else
    {
        sdxc_cmd.cmd_type = sdxc_cmd_type_normal_cmd;
    }

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
                memcpy(aligned_buf, data->buf, write_size);
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

    err = sdxc_transfer_blocking(mmcsd->sdxc_base, &adma_config, &xfer);
    LOG_I("cmd=%d, arg=%x\n", cmd->cmd_code, cmd->arg);
    if (err != status_success)
    {
        hpm_sdmmc_host_recovery(mmcsd->sdxc_base);
        LOG_E(" ***sdxc_transfer_blocking error: %d*** -->\n", err);
        cmd->err = -RT_ERROR;
    }
    else
    {
        LOG_I(" ***sdxc_transfer_blocking passed: %d*** -->\n", err);
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
            memcpy(data->buf, aligned_buf, read_size);
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
    struct hpm_mmcsd *mmcsd;
    uint32_t sdxc_clk;
    uint32_t vdd;
    RT_ASSERT(host != RT_NULL);RT_ASSERT(host->private_data != RT_NULL);RT_ASSERT(io_cfg != RT_NULL);

    mmcsd = (struct hpm_mmcsd *) host->private_data;

    vdd = io_cfg->vdd;

    static bool has_init = false;

    init_sdxc_pins(mmcsd->sdxc_base, false);

    uint32_t sdxc_clock = io_cfg->clock;

    if (sdxc_clock != 0U)
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
        board_sd_configure_clock(mmcsd->sdxc_base, sdxc_clk);
    }
    rt_thread_mdelay(5);
}

static void hpm_sdmmc_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t en)
{
    RT_ASSERT(host != RT_NULL);RT_ASSERT(host->private_data != RT_NULL);

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
