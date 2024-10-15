/*
 * Copyright (c) 2022-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-02-23   HPMicro     First version
 * 2022-07-19   HPMicro     Fixed the multi-block read/write issue
 * 2023-07-27   HPMicro     Fixed clock setting issue
 * 2023-08-02   HPMicro     Added speed mode setting
 * 2024-01-03   HPMicro     Added multiple instance support
 * 2024-05-23   HPMicro     Fixed unaligned transfer issue in the SDIO case
 * 2024-05-25   HPMicro     Added HS200 & HS400 support, optimize the cache-management policy for read
 * 2024-05-26   HPMicro     Added UHS-I support, added DDR50 and High Speed DDR mode support
 * 2024-06-19   HPMicro     Added timeout check for SDXC transfer
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

/**
 * Note: Allocate cache-line aligned buffer in the SD/eMMC read/write case may require larger heap size
 *       if the read/write length is a big number (for example: 64KB), the RT-Thread RTOS may
 *       be unable to allocate enough size of buffer if the heap size is small.
 *
 *       Keep this option disabled by default, please enable it if the default setting cannot meet
 *       real requirement of application.
 */
#define HPM_SDXC_ALLOC_CACHELINE_ALIGNED_BUF 0

struct hpm_mmcsd
{
    struct rt_mmcsd_host *host;
    struct rt_mmcsd_req *req;
    struct rt_mmcsd_cmd *cmd;
    struct rt_timer *timer;

    char name[RT_NAME_MAX];
    rt_uint32_t *buf;
    SDXC_Type *sdxc_base;
    int32_t irq_num;
    uint32_t *sdxc_adma2_table;
    bool support_8bit;
    bool support_4bit;
    bool support_1v8;
    bool support_3v3;
    uint8_t power_mode;
    uint8_t bus_width;
    uint8_t timing;
    uint8_t bus_mode;
    uint32_t freq;
    uint16_t vdd;
    const char *vsel_pin_name;
    const char *pwr_pin_name;

};

/**
 * @brief SDIO CMD53 argument
 */
typedef union
{
    uint32_t value;
    struct
    {
        uint32_t count :9;
        uint32_t reg_addr :17;
        uint32_t op_code :1;
        uint32_t block_mode :1;
        uint32_t func_num :3;
        uint32_t rw_flag :1;
    };
} sdio_cmd53_arg_t;

static void hpm_sdmmc_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req);
static void hpm_sdmmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg);
static void hpm_sdmmc_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t en);
static void hpm_sdmmc_host_recovery(SDXC_Type *base);
static hpm_stat_t hpm_sdmmc_transfer(SDXC_Type *base, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer);
static rt_int32_t hpm_sdmmc_execute_tuning(struct rt_mmcsd_host *host, rt_int32_t opcode);
static rt_int32_t hpm_sdmmc_switch_uhs_voltage(struct rt_mmcsd_host *host);

static void hpm_sdmmc_power_on_via_pin(struct hpm_mmcsd *mmcsd);
static void hpm_sdmmc_power_off_via_pin(struct hpm_mmcsd *mmcsd);

static void hpm_sdmmc_switch_to_3v3_via_pin(struct hpm_mmcsd *mmcsd);
static void hpm_sdmmc_switch_to_1v8_via_pin(struct hpm_mmcsd *mmcsd);



static void hpm_sdmmc_pin_init(const char *pin_name, bool is_output);
static void hpm_sdmmc_pin_write(const char *pin_name, rt_uint8_t value);
static void hpm_sdmmc_pin_init(const char *pin_name, bool is_output)
{
    rt_base_t pin = rt_pin_get(pin_name);
    if (pin < 0) {
        return;
    }

    rt_uint8_t mode = (is_output) ? PIN_MODE_OUTPUT : PIN_MODE_INPUT_PULLUP;
    if (is_output)
    {
        rt_pin_mode(pin, mode);
    }
}

static void hpm_sdmmc_pin_write(const char *pin_name, rt_uint8_t value)
{
    rt_base_t pin = rt_pin_get(pin_name);
    if (pin < 0)
    {
        return;
    }

    rt_pin_write(pin, value);
}

static void hpm_sdmmc_power_on_via_pin(struct hpm_mmcsd *mmcsd)
{
    hpm_sdmmc_pin_write(mmcsd->pwr_pin_name, 1);
}

static void hpm_sdmmc_power_off_via_pin(struct hpm_mmcsd *mmcsd)
{
    hpm_sdmmc_pin_write(mmcsd->pwr_pin_name, 0);
}

static void hpm_sdmmc_switch_to_3v3_via_pin(struct hpm_mmcsd *mmcsd)
{
    hpm_sdmmc_pin_write(mmcsd->vsel_pin_name, 0);
}

static void hpm_sdmmc_switch_to_1v8_via_pin(struct hpm_mmcsd *mmcsd)
{
    hpm_sdmmc_pin_write(mmcsd->vsel_pin_name, 1);
}


static rt_int32_t hpm_sdmmc_switch_uhs_voltage(struct rt_mmcsd_host *host)
{
    struct hpm_mmcsd *mmcsd = (struct hpm_mmcsd *) host->private_data;
    SDXC_Type *base = mmcsd->sdxc_base;

    /* 1. Stop providing clock to the card */
    sdxc_enable_inverse_clock(mmcsd->sdxc_base, false);
    sdxc_enable_sd_clock(mmcsd->sdxc_base, false);

    /* 2. Wait until DAT[3:0] are 4'b0000 */
    uint32_t data3_0_level;
    uint32_t delay_cnt = 1000000UL;
    do
    {
        data3_0_level = sdxc_get_data3_0_level(mmcsd->sdxc_base);
        --delay_cnt;
    } while ((data3_0_level != 0U) && (delay_cnt > 0U));
    if (delay_cnt < 1)
    {
        return -RT_ETIMEOUT;
    }

    /* 3. Switch to 1.8V */
    hpm_sdmmc_switch_to_1v8_via_pin(mmcsd);
    sdxc_select_voltage(mmcsd->sdxc_base, sdxc_bus_voltage_sd_1v8);

    /* 4. spec:host delay 5ms,  host: give more delay time here */
    rt_thread_mdelay(10);

    /* 5. Provide SD clock the card again */
    sdxc_enable_inverse_clock(mmcsd->sdxc_base, true);
    sdxc_enable_sd_clock(mmcsd->sdxc_base, true);

    /* 6. spec: wait 1ms, host: give more delay time here */
    rt_thread_mdelay(5);

    /* 7. Check DAT[3:0], make sure the value is 4'b0000 */
    delay_cnt = 1000000UL;
    data3_0_level;
    do
    {
        data3_0_level = sdxc_get_data3_0_level(mmcsd->sdxc_base);
        --delay_cnt;
    } while ((data3_0_level == 0U) && (delay_cnt > 0U));
    if (delay_cnt < 1)
    {
        return -RT_ETIMEOUT;
    }

    return RT_EOK;
}




static const struct rt_mmcsd_host_ops hpm_mmcsd_host_ops =
{
    .request = hpm_sdmmc_request,
    .set_iocfg = hpm_sdmmc_set_iocfg,
    .get_card_status = NULL,
    .enable_sdio_irq = NULL,
    .execute_tuning = hpm_sdmmc_execute_tuning,
    .switch_uhs_voltage = hpm_sdmmc_switch_uhs_voltage,

};

#if defined(BSP_USING_SDXC0)
/* Place the ADMA2 table to non-cacheable region */
ATTR_PLACE_AT_NONCACHEABLE static uint32_t s_sdxc0_adma2_table[SDXC_ADMA_TABLE_WORDS];
/* SDXC0 */
static struct hpm_mmcsd s_hpm_sdxc0 =
{
    .name = "sd0",
    .sdxc_base = HPM_SDXC0,
    .sdxc_adma2_table = s_sdxc0_adma2_table,
    .irq_num = IRQn_SDXC0,
#if defined(BSP_SDXC0_BUS_WIDTH_8BIT)
    .support_8bit = true,
    .support_4bit = true,
#elif defined(BSP_SDXC0_BUS_WIDTH_4BIT)
    .support_4bit = true,
#elif defined(BSP_SDXC0_BUS_WIDTH_1BIT)
#else
    .support_4bit = true,
#endif

#if defined(BSP_SDXC0_VOLTAGE_3V3)
    .support_3v3 = true,
#endif
#if defined(BSP_SDXC0_VOLTAGE_1V8)
    .support_1v8 = true,
#endif
#if defined(BSP_SDXC0_VOLTAGE_DUAL)
    .support_3v3 = true,
    .support_1v8 = true,
#endif

#if defined(BSP_SDXC0_VSEL_PIN)
    .vsel_pin_name = BSP_SDXC0_VSEL_PIN,
#endif
#if defined(BSP_SDXC0_PWR_PIN)
    .pwr_pin_name = BSP_SDXC0_PWR_PIN,
#endif
};
#endif

#if defined(BSP_USING_SDXC1)
/* Place the ADMA2 table to non-cacheable region */
ATTR_PLACE_AT_NONCACHEABLE static uint32_t s_sdxc1_adma2_table[SDXC_ADMA_TABLE_WORDS];
static struct hpm_mmcsd s_hpm_sdxc1 =
{
    .name = "sd1",
    .sdxc_base = HPM_SDXC1,
    .sdxc_adma2_table = s_sdxc1_adma2_table,
    .irq_num = IRQn_SDXC1,
#if defined(BSP_SDXC1_BUS_WIDTH_8BIT)
    .support_8bit = true,
    .support_4bit = true,
#elif defined(BSP_SDXC1_BUS_WIDTH_4BIT)
    .support_4bit = true,
#elif defined(BSP_SDXC1_BUS_WIDTH_1BIT)
#else
    .support_4bit = true,
#endif

#if defined(BSP_SDXC1_VOLTAGE_3V3)
    .support_3v3 = true,
#endif
#if defined(BSP_SDXC1_VOLTAGE_1V8)
    .support_1v8 = true,
#endif
#if defined(BSP_SDXC1_VOLTAGE_DUAL)
    .support_3v3 = true,
    .support_1v8 = true,
#endif
#if defined(BSP_SDXC1_VSEL_PIN)
    .vsel_pin_name = BSP_SDXC1_VSEL_PIN,
#endif
#if defined(BSP_SDXC1_PWR_PIN)
    .pwr_pin_name = BSP_SDXC1_PWR_PIN,
#endif
};
#endif

static struct hpm_mmcsd *hpm_sdxcs[] =
{
#if defined(BSP_USING_SDXC0)
    &s_hpm_sdxc0,
#endif
#if defined(BSP_USING_SDXC1)
    &s_hpm_sdxc1,
#endif
};

static rt_int32_t hpm_sdmmc_execute_tuning(struct rt_mmcsd_host *host, rt_int32_t opcode)
{
    RT_ASSERT(host != RT_NULL); RT_ASSERT(host->private_data != RT_NULL);

    struct hpm_mmcsd *mmcsd = (struct hpm_mmcsd *) host->private_data;
    SDXC_Type *base = mmcsd->sdxc_base;

    /* Prepare the Auto tuning environment */
    sdxc_stop_clock_during_phase_code_change(base, true);
    sdxc_set_post_change_delay(base, 3U);
    sdxc_select_cardclk_delay_source(base, false);
    sdxc_enable_power(base, true);
    hpm_stat_t err = sdxc_perform_auto_tuning(base, opcode);

    return (err != status_success)  ? -RT_EPERM : RT_EOK;
}

static hpm_stat_t hpm_sdmmc_transfer(SDXC_Type *base, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer)
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
    volatile rt_base_t start_tick = rt_tick_get();
    while (!IS_HPM_BITMASK_SET(interrupt_status, SDXC_INT_STAT_CMD_COMPLETE_MASK))
    {
        interrupt_status = sdxc_get_interrupt_status(base);
        status = sdxc_parse_interrupt_status(base);
        HPM_BREAK_IF(status != status_success);
        rt_base_t current_tick = rt_tick_get();
        if ((current_tick - start_tick) > RT_TICK_PER_SECOND)
        {
            return -RT_ETIMEOUT;
        }
    }
    sdxc_clear_interrupt_status(base, SDXC_INT_STAT_CMD_COMPLETE_MASK);
    if (status == status_success)
    {
        status = sdxc_receive_cmd_response(base, cmd);
    }
    if ((status == status_success) && (data != RT_NULL))
    {
        interrupt_status = sdxc_get_interrupt_status(base);
        start_tick = rt_tick_get();
        while (!IS_HPM_BITMASK_SET(interrupt_status, SDXC_INT_STAT_XFER_COMPLETE_MASK | SDXC_STS_ERROR))
        {
            interrupt_status = sdxc_get_interrupt_status(base);
            status = sdxc_parse_interrupt_status(base);
            HPM_BREAK_IF(status != status_success);
            rt_base_t current_tick = rt_tick_get();
            if ((current_tick - start_tick) > RT_TICK_PER_SECOND)
            {
                return -RT_ETIMEOUT;
            }
        }
    }

    return status;
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
    uint32_t *raw_alloc_buf = RT_NULL;
    uint32_t *aligned_buf = RT_NULL;
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
    xfer.data = NULL;
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
        size_t xfer_buf_addr = (uint32_t)data->buf;
        uint32_t xfer_len = data->blks * data->blksize;
        if ((req->data->flags & DATA_DIR_WRITE) != 0U)
        {
            uint32_t write_size = xfer_len;
            size_t aligned_start;
            uint32_t aligned_size;
#if defined(HPM_SDXC_ALLOC_CACHELINE_ALIGNED_BUF) && (HPM_SDXC_ALLOC_CACHELINE_ALIGNED_BUF == 1)
            if (!SDXC_IS_CACHELINE_ALIGNED(xfer_buf_addr) || !SDXC_IS_CACHELINE_ALIGNED(write_size))
#else
            if ((xfer_buf_addr % 4 != 0) && (write_size % 4 != 0))
#endif
            {
                write_size = SDXC_CACHELINE_ALIGN_UP(xfer_len);
                raw_alloc_buf = (uint32_t *) rt_malloc(write_size + CACHE_LINESIZE - RT_ALIGN_SIZE);
                RT_ASSERT(raw_alloc_buf != RT_NULL);
                aligned_buf = (uint32_t *) SDXC_CACHELINE_ALIGN_UP(raw_alloc_buf);
                RT_ASSERT(aligned_buf != RT_NULL);
                memcpy(aligned_buf, data->buf, xfer_len);
                memset(aligned_buf + write_size, 0, write_size - xfer_len);
                sdxc_data.tx_data = (uint32_t const *) core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t) aligned_buf);

                aligned_start = (uint32_t)sdxc_data.tx_data;
                aligned_size = write_size;
            }
            else
            {
                sdxc_data.tx_data = (uint32_t const *) core_local_mem_to_sys_address(BOARD_RUNNING_CORE, xfer_buf_addr);

                aligned_start = SDXC_CACHELINE_ALIGN_DOWN(sdxc_data.tx_data);
                size_t aligned_end = SDXC_CACHELINE_ALIGN_UP((uint32_t)sdxc_data.tx_data + write_size);
                aligned_size = aligned_end - aligned_start;
            }
            rt_base_t level = rt_hw_interrupt_disable();
            l1c_dc_flush(aligned_start, aligned_size);
            rt_hw_interrupt_enable(level);
            sdxc_data.rx_data = NULL;
        }
        else
        {
            uint32_t read_size = xfer_len;
#if defined(HPM_SDXC_ALLOC_CACHELINE_ALIGNED_BUF) && (HPM_SDXC_ALLOC_CACHELINE_ALIGNED_BUF == 1)
            if (!SDXC_IS_CACHELINE_ALIGNED(xfer_buf_addr) || !SDXC_IS_CACHELINE_ALIGNED(read_size))
#else
            if ((xfer_buf_addr % 4 != 0) || (read_size % 4 != 0))
#endif
            {
                uint32_t aligned_read_size = SDXC_CACHELINE_ALIGN_UP(read_size);
                raw_alloc_buf = (uint32_t *) rt_malloc(aligned_read_size + CACHE_LINESIZE - RT_ALIGN_SIZE);
                RT_ASSERT(raw_alloc_buf != RT_NULL);
                aligned_buf = (uint32_t *) SDXC_CACHELINE_ALIGN_UP(raw_alloc_buf);
                sdxc_data.rx_data =  (uint32_t*) core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t) aligned_buf);
            }
            else
            {
                sdxc_data.rx_data = (uint32_t*) core_local_mem_to_sys_address(BOARD_RUNNING_CORE, xfer_buf_addr);
                size_t aligned_start = SDXC_CACHELINE_ALIGN_DOWN(sdxc_data.rx_data);
                size_t aligned_end = SDXC_CACHELINE_ALIGN_UP((uint32_t)sdxc_data.rx_data + read_size);
                uint32_t aligned_size = aligned_end - aligned_start;
                rt_base_t level = rt_hw_interrupt_disable();
                l1c_dc_flush(aligned_start, aligned_size);
                rt_hw_interrupt_enable(level);
            }
            sdxc_data.tx_data = RT_NULL;
        }
        xfer.data = &sdxc_data;

        /* Align the write/read size since the ADMA2 engine in the SDXC cannot transfer unaligned size of data */
        if ((cmd->cmd_code == SD_IO_RW_EXTENDED) && (xfer_len % 4 != 0))
        {
            sdio_cmd53_arg_t cmd53_arg;
            cmd53_arg.value = sdxc_cmd.cmd_argument;
            cmd53_arg.count = HPM_ALIGN_UP(xfer_len, 4);
            sdxc_cmd.cmd_argument = cmd53_arg.value;
            sdxc_data.block_size = HPM_ALIGN_UP(xfer_len, 4);
        }
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
        if (err != status_sdxc_cmd_timeout_error) /* Ignore command timeout error by default */
        {
            LOG_E(" ***hpm_sdmmc_transfer error: %d, cmd:%d, arg:0x%x*** -->\n", err, cmd->cmd_code, cmd->arg);
        }
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
        if (aligned_buf != RT_NULL)
        {
            uint32_t aligned_read_size = SDXC_CACHELINE_ALIGN_UP(read_size);
            rt_base_t level = rt_hw_interrupt_disable();
            l1c_dc_invalidate((uint32_t) aligned_buf, aligned_read_size);
            rt_hw_interrupt_enable(level);
            memcpy(data->buf, aligned_buf, read_size);
        }
        else
        {
            size_t aligned_start = SDXC_CACHELINE_ALIGN_DOWN(sdxc_data.rx_data);
            size_t aligned_end = SDXC_CACHELINE_ALIGN_UP((uint32_t)sdxc_data.rx_data + read_size);
            uint32_t aligned_size = aligned_end - aligned_start;
            rt_base_t level = rt_hw_interrupt_disable();
            l1c_dc_invalidate(aligned_start, aligned_size);
            rt_hw_interrupt_enable(level);
        }
    }

    if (raw_alloc_buf != RT_NULL)
    {
        rt_free(raw_alloc_buf);
        raw_alloc_buf = RT_NULL;
        aligned_buf = RT_NULL;
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

static void hpm_sdmmc_set_cardclk_delay_chain(struct hpm_mmcsd *mmcsd)
{
    SDXC_Type *base = mmcsd->sdxc_base;
    bool need_inverse = sdxc_is_inverse_clock_enabled(base);
    sdxc_enable_inverse_clock(base, false);
    sdxc_enable_sd_clock(base, false);
    uint32_t num_delaycells = sdxc_get_default_cardclk_delay_chain(base, mmcsd->freq);
    sdxc_set_cardclk_delay_chain(base, num_delaycells);
    sdxc_enable_inverse_clock(base, need_inverse);
    sdxc_enable_sd_clock(base, true);
}

ATTR_WEAK void init_sdxc_ds_pin(SDXC_Type *base)
{
    LOG_W("Ignore this warning if the DS pin is not supported\n");
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

    /* Power control */
    uint32_t vdd = io_cfg->vdd;
    if (io_cfg->power_mode != mmcsd->power_mode)
    {
        switch(io_cfg->power_mode)
        {
        case MMCSD_POWER_OFF:
            hpm_sdmmc_power_off_via_pin(mmcsd);
            break;
        case MMCSD_POWER_ON:
            hpm_sdmmc_power_on_via_pin(mmcsd);
            break;
        case MMCSD_POWER_UP:
            hpm_sdmmc_power_off_via_pin(mmcsd);
            rt_thread_mdelay(10);
            hpm_sdmmc_power_on_via_pin(mmcsd);
            /* After power up, wait 1ms, then wait 74 card clock */
            rt_thread_mdelay(1);
            sdxc_wait_card_active(mmcsd->sdxc_base);
            break;
        default:
            /* Do nothing */
            break;
        }
        mmcsd->power_mode = io_cfg->power_mode;
    }

    /* Voltage switch */
    if (mmcsd->vdd != vdd)
    {
        if (vdd == 7)
        {
            /* Switch to 1.8V */
            hpm_sdmmc_switch_to_1v8_via_pin(mmcsd);
        }
        else
        {
            /* Switch to 3V */
            hpm_sdmmc_switch_to_3v3_via_pin(mmcsd);
        }
        mmcsd->vdd = vdd;
    }

    /* Set bus width */
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

    /* Set timing mode */

    bool need_config_ds = false;
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
            /* Must switch to 1.8V signaling for UHS_DDR50 */
            sdxc_select_voltage(mmcsd->sdxc_base, sdxc_bus_voltage_sd_1v8);
            break;
        case MMCSD_TIMING_MMC_DDR52:
            sdxc_enable_emmc_support(mmcsd->sdxc_base, true);
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_emmc_speed_high_speed_ddr);
            break;
        case MMCSD_TIMING_MMC_HS200:
            sdxc_enable_emmc_support(mmcsd->sdxc_base, true);
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_emmc_speed_hs200);
            break;
        case MMCSD_TIMING_MMC_HS400:
        case MMCSD_TIMING_MMC_HS400_ENH_DS:
            sdxc_enable_emmc_support(mmcsd->sdxc_base, true);
            sdxc_set_speed_mode(mmcsd->sdxc_base, sdxc_emmc_speed_hs400);
            if (io_cfg->timing == MMCSD_TIMING_MMC_HS400_ENH_DS)
            {
                sdxc_enable_enhanced_strobe(mmcsd->sdxc_base, true);
                uint32_t num_delaycells = sdxc_get_default_strobe_delay(mmcsd->sdxc_base);
                sdxc_set_data_strobe_delay(mmcsd->sdxc_base, num_delaycells);
            }
            need_config_ds = true;
            break;
        }
        mmcsd->timing = io_cfg->timing;
    }

    /* Initialize SDXC Pins */
    bool open_drain = io_cfg->bus_mode == MMCSD_BUSMODE_OPENDRAIN;
    bool is_1v8 = (io_cfg->vdd == 7) || (mmcsd->host->valid_ocr == VDD_165_195);
    uint32_t width = (io_cfg->bus_width == MMCSD_BUS_WIDTH_8) ? 8 : ((io_cfg->bus_width == MMCSD_BUS_WIDTH_4) ? 4 : 1);
    init_sdxc_cmd_pin(mmcsd->sdxc_base, open_drain, is_1v8);
    init_sdxc_clk_data_pins(mmcsd->sdxc_base, width, is_1v8);
    rt_thread_mdelay(1);
    if (need_config_ds)
    {
        init_sdxc_ds_pin(mmcsd->sdxc_base);
        rt_thread_mdelay(1);
    }
    /* Initialize SDXC clock */
    uint32_t sdxc_clock = io_cfg->clock;
    if (sdxc_clock != 0U)
    {
        if (mmcsd->freq != sdxc_clock)
        {
            bool need_reverse = true;
            bool need_card_delay_clk = false;
            if ((mmcsd->timing == MMCSD_TIMING_UHS_DDR50) ||
                (mmcsd->timing == MMCSD_TIMING_MMC_DDR52) ||
                (mmcsd->timing == MMCSD_TIMING_MMC_HS400) ||
                (mmcsd->timing == MMCSD_TIMING_MMC_HS400_ENH_DS))
            {
                need_reverse = false;
                need_card_delay_clk = true;
            }

            /* Ensure request frequency from mmcsd stack level doesn't exceed maximum supported frequency by host */
            uint32_t clock_freq = MIN(mmcsd->host->freq_max, sdxc_clock);
            clock_freq = board_sd_configure_clock(mmcsd->sdxc_base, clock_freq, need_reverse);
            LOG_I("mmcsd clock: %dHz\n", clock_freq);
            mmcsd->freq = sdxc_clock;

            if (need_card_delay_clk)
            {
                hpm_sdmmc_set_cardclk_delay_chain(mmcsd);
            }
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
}

int rt_hw_sdio_init(void)
{
    rt_err_t err = RT_EOK;

    struct rt_mmcsd_host *host = NULL;
    struct hpm_mmcsd *mmcsd = NULL;

    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_sdxcs); i++) {
        host = mmcsd_alloc_host();
        if (host == NULL)
        {
            err = -RT_ERROR;
            break;
        }
        mmcsd = hpm_sdxcs[i];
        host->ops = &hpm_mmcsd_host_ops;
        host->freq_min = 375000;
        host->freq_max = 50000000;
        host->valid_ocr = 0;

        /* Determine supported Voltage range */
        if (mmcsd->support_3v3)
        {
            host->valid_ocr |= VDD_30_31 | VDD_31_32 | VDD_32_33 | VDD_33_34;
        }
        if (mmcsd->support_1v8)
        {
            host->valid_ocr |= VDD_165_195;
        }

        /* Determine Host supported features */
        host->flags = MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ;
        if (mmcsd->support_4bit)
        {
            host->flags |=  MMCSD_BUSWIDTH_4;
        }
        if (mmcsd->support_8bit) {
            host->flags |=  MMCSD_BUSWIDTH_8;
        }

        if (mmcsd->support_1v8)
        {
            host->freq_max = 166000000;
            host->flags |= MMCSD_SUP_HS200_1V8;

            host->flags |= MMCSD_SUP_SDR50 | MMCSD_SUP_SDR104;
            if (sdxc_is_ddr50_supported(mmcsd->sdxc_base))
            {
                host->flags |= MMCSD_SUP_DDR50;
            }

            if (mmcsd->support_8bit)
            {
                host->flags |= MMCSD_SUP_HS400_1V8 | MMCSD_SUP_ENH_DS;
            }
        }

        /* For eMMC device, add High Speed DDR mode support as long as it is supported by the host controller */
        if (sdxc_is_ddr50_supported(mmcsd->sdxc_base))
        {
            host->flags |= MMCSD_SUP_HIGHSPEED_DDR;
        }

        rt_strncpy(host->name, mmcsd->name, RT_NAME_MAX);

        host->max_seg_size = 0x80000;
        host->max_dma_segs = 1;
        host->max_blk_size = 512;
        host->max_blk_count = 1024;

        mmcsd->host = host;

        /* Perform necessary initialization */
        board_sd_configure_clock(mmcsd->sdxc_base, 375000, true);

        sdxc_config_t sdxc_config = { 0 };
        sdxc_config.data_timeout = 1000;
        sdxc_init(mmcsd->sdxc_base, &sdxc_config);

        host->private_data = mmcsd;

        /* Initialize PWR pin and VSEL pin */
        if (mmcsd->pwr_pin_name != RT_NULL)
        {
            hpm_sdmmc_pin_init(mmcsd->pwr_pin_name, true);
            rt_thread_mdelay(1);

            if (host->valid_ocr == VDD_165_195)
            {
                hpm_sdmmc_switch_to_1v8_via_pin(mmcsd);
            }
            else
            {
                hpm_sdmmc_switch_to_3v3_via_pin(mmcsd);
            }
        }
        if (mmcsd->vsel_pin_name != RT_NULL)
        {
            hpm_sdmmc_pin_init(mmcsd->vsel_pin_name, true);
            rt_thread_mdelay(1);
        }

        mmcsd_change(host);
    };

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
