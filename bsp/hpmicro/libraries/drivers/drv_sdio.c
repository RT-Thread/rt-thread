/*
 * Copyright (c) 2022-2025 HPMicro
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
 * 2025-03-06   HPMicro     Adapt hpm-sdk v1.9.0
 * 2025-03-24   HPMicro     Added ADMA3 support, added interrupt driven mode
 * 2025-04-11   HPMicro     Added the non-cacheable buffer support, avoided dynamic memory allocation at transfer stage
 */
#include <rtthread.h>

#ifdef BSP_USING_SDXC
#include <rtdbg.h>
#include <rtdevice.h>

#include "board.h"
#include "hpm_sdxc_drv.h"
#include "hpm_l1c_drv.h"


#define CACHELINE_SIZE                  HPM_L1C_CACHELINE_SIZE
#define SDXC_ADMA_TABLE_WORDS           SDXC_AMDA3_DESC_MIN_WORDS
#define SDXC_AMDA_ADDR_ALIGNMENT        (4U)
#define SDXC_ADMA_XFER_SIZE_ALIGNMENT   (4U)
#define SDXC_DATA_TIMEOUT               (1000) /* 1000ms */
#define SDMMC_DEFAULT_SECTOR_SIZE       (512U)

#define SDXC_CACHELINE_ALIGN_DOWN(x)    HPM_L1C_CACHELINE_ALIGN_DOWN(x)
#define SDXC_CACHELINE_ALIGN_UP(x)      HPM_L1C_CACHELINE_ALIGN_UP(x)
#define SDXC_IS_CACHELINE_ALIGNED(n)    ((uint32_t)(n) % (uint32_t)(CACHELINE_SIZE) == 0U)

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
    uint32_t *sdxc_adma_table;
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
    bool enable_interrupt_driven;
    bool use_noncacheable_buf;
    uint8_t *data_buf;
    uint32_t data_buf_size;
    uint8_t irq_priority;
    rt_event_t xfer_event;
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
static hpm_stat_t hpm_sdmmc_transfer_polling(struct hpm_mmcsd *mmcsd, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer);
static hpm_stat_t hpm_sdmmc_transfer_interrupt_driven(struct hpm_mmcsd *mmcsd, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer);
static hpm_stat_t hpm_sdmmc_transfer(struct hpm_mmcsd *mmcsd, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer);
static rt_int32_t hpm_sdmmc_execute_tuning(struct rt_mmcsd_host *host, rt_int32_t opcode);
static rt_err_t hpm_sdmmc_signal_voltage_switch(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg);

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

    rt_uint8_t mode = is_output ? PIN_MODE_OUTPUT : PIN_MODE_INPUT_PULLUP;
    rt_pin_mode(pin, mode);
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


static rt_err_t hpm_sdmmc_signal_voltage_switch(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
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

    /* 3. Switch to 1.8V/3.3V */
    if (ios->signal_voltage == MMCSD_SIGNAL_VOLTAGE_330)
    {
        hpm_sdmmc_switch_to_3v3_via_pin(mmcsd);
        sdxc_select_voltage(mmcsd->sdxc_base, sdxc_bus_voltage_sd_3v3);
    }
    else
    {
        hpm_sdmmc_switch_to_1v8_via_pin(mmcsd);
        sdxc_select_voltage(mmcsd->sdxc_base, sdxc_bus_voltage_sd_1v8);
    }

    /* 4. spec:host delay 5ms,  host: give more delay time here */
    rt_thread_mdelay(10);

    /* 5. Provide SD clock the card again */
    sdxc_enable_inverse_clock(mmcsd->sdxc_base, true);
    sdxc_enable_sd_clock(mmcsd->sdxc_base, true);

    /* 6. spec: wait 1ms, host: give more delay time here */
    rt_thread_mdelay(5);

    /* 7. Check DAT[3:0], make sure the value is 4'b0000 */
    delay_cnt = 1000000UL;
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
    .enable_sdio_irq = hpm_sdmmc_enable_sdio_irq,
    .execute_tuning = hpm_sdmmc_execute_tuning,
    .signal_voltage_switch = hpm_sdmmc_signal_voltage_switch,
};

void hpm_sdmmc_isr(struct hpm_mmcsd *mmcsd)
{
    SDXC_Type *base = mmcsd->sdxc_base;
    uint32_t int_stat = sdxc_get_interrupt_status(base);
    uint32_t int_signal_en = sdxc_get_interrupt_signal(base);
    if (((int_stat & SDXC_INT_STAT_CARD_INTERRUPT_MASK) != 0) &&
        ((int_signal_en & SDXC_INT_STAT_CARD_INTERRUPT_MASK) != 0))
    {
        hpm_sdmmc_enable_sdio_irq(mmcsd->host, 0);
        rt_sem_release(mmcsd->host->sdio_irq_sem);
    }
    if (mmcsd->enable_interrupt_driven)
    {
        const uint32_t xfer_done_or_err_int_mask = SDXC_INT_STAT_CMD_COMPLETE_MASK  \
                                                 | SDXC_INT_STAT_XFER_COMPLETE_MASK \
                                                 | SDXC_INT_STAT_ERR_INTERRUPT_MASK;
        if (((int_signal_en & xfer_done_or_err_int_mask) != 0U) && ((int_stat & xfer_done_or_err_int_mask) != 0U)) {
            uint32_t event_flags = int_stat & xfer_done_or_err_int_mask;
            rt_event_send(mmcsd->xfer_event, event_flags);
            sdxc_clear_interrupt_status(base, event_flags);
        }
    }
}

#if defined(BSP_USING_SDXC0)
void sdxc0_isr(void);
/* Place the ADMA table to non-cacheable region */
ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(8) static uint32_t s_sdxc0_adma_table[SDXC_ADMA_TABLE_WORDS];

#if defined(BSP_SDXC0_USE_NONCACHEABLE_BUFFER)
#if defined(BSP_SDXC0_NONCACHEABLE_BUF_IN_FAST_RAM)
ATTR_PLACE_AT_FAST_RAM_WITH_ALIGNMENT(8)
#else
ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(8)
#endif
static uint8_t s_sdxc0_noncacheable_buf[BSP_SDXC0_NONCACHEABLE_BUFFER_SIZE_IN_SECTOR * SDMMC_DEFAULT_SECTOR_SIZE];
#endif

/* SDXC0 */
static struct hpm_mmcsd s_hpm_sdxc0 =
{
    .name = "sd0",
    .sdxc_base = HPM_SDXC0,
    .sdxc_adma_table = s_sdxc0_adma_table,
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
#if defined(BSP_SDXC0_ENABLE_INTERRUPT_DRIVEN)
    .enable_interrupt_driven = true,
#endif
#if defined(BSP_SDXC0_REQUIRE_CACHELINE_ALIGNED_BUF)
    .require_cacheline_aligned_buf = true,
#endif
#if defined(BSP_SDXC0_IRQ_PRIORITY)
    .irq_priority = BSP_SDXC0_IRQ_PRIORITY,
#else
    .irq_priority = 1,
#endif
#if defined (BSP_SDXC0_USE_NONCACHEABLE_BUFFER)
    .use_noncacheable_buf = true,
    .data_buf = s_sdxc0_noncacheable_buf,
    .data_buf_size = sizeof(s_sdxc0_noncacheable_buf),
#endif
#if defined(BSP_SDXC0_USE_CACHEABLE_BUFFER)
    .data_buf_size = BSP_SDXC0_CACHEABLE_BUFFER_SIZE_IN_SECTOR * SDMMC_DEFAULT_SECTOR_SIZE,
#endif
};
SDK_DECLARE_EXT_ISR_M(IRQn_SDXC0, sdxc0_isr);
void sdxc0_isr(void)
{
    hpm_sdmmc_isr(&s_hpm_sdxc0);
}
#endif

#if defined(BSP_USING_SDXC1)
void sdxc1_isr(void);
/* Place the ADMA table to non-cacheable region */
ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(8) static uint32_t s_sdxc1_adma_table[SDXC_ADMA_TABLE_WORDS];
#if defined(BSP_SDXC1_NONCACHEABLE_BUFFER_SIZE_IN_SECTOR)

#if defined(BSP_SDXC1_USE_NONCACHEABLE_BUFFER)
ATTR_PLACE_AT_FAST_RAM_WITH_ALIGNMENT(8)
#else
ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(8)
#endif
static uint8_t s_sdxc1_noncacheable_buf[BSP_SDXC1_NONCACHEABLE_BUFFER_SIZE_IN_SECTOR * SDMMC_DEFAULT_SECTOR_SIZE];
#endif
static struct hpm_mmcsd s_hpm_sdxc1 =
{
    .name = "sd1",
    .sdxc_base = HPM_SDXC1,
    .sdxc_adma_table = s_sdxc1_adma_table,
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
#if defined(BSP_SDXC1_ENABLE_INTERRUPT_DRIVEN)
    .enable_interrupt_driven = true,
#endif
#if defined(BSP_SDXC1_REQUIRE_CACHELINE_ALIGNED_BUF)
    .require_cacheline_aligned_buf = true,
#endif
#if defined(BSP_SDXC1_IRQ_PRIORITY)
    .irq_priority = BSP_SDXC1_IRQ_PRIORITY,
#else
    .irq_priority = 1,
#endif
#if defined (BSP_SDXC1_USE_NONCACHEABLE_BUFFER)
    .use_noncacheable_buf = true,
    .data_buf = s_sdxc1_noncacheable_buf,
    .data_buf_size = sizeof(s_sdxc1_noncacheable_buf),
#endif
#if defined(BSP_SDXC1_USE_CACHEABLE_BUFFER)
    .data_buf_size = BSP_SDXC1_CACHEABLE_BUFFER_SIZE_IN_SECTOR * SDMMC_DEFAULT_SECTOR_SIZE,
#endif
};
SDK_DECLARE_EXT_ISR_M(IRQn_SDXC1, sdxc1_isr);
void sdxc1_isr(void)
{
    hpm_sdmmc_isr(&s_hpm_sdxc1);
}
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
    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(host->private_data != RT_NULL);

    struct hpm_mmcsd *mmcsd = (struct hpm_mmcsd *) host->private_data;
    SDXC_Type *base = mmcsd->sdxc_base;
    RT_ASSERT(base != RT_NULL);

    /* Prepare the Auto tuning environment */
    sdxc_stop_clock_during_phase_code_change(base, true);
    sdxc_set_post_change_delay(base, 3U);
    sdxc_select_cardclk_delay_source(base, false);
    sdxc_enable_power(base, true);
    hpm_stat_t err = sdxc_perform_auto_tuning(base, opcode);

    return (err != status_success)  ? -RT_EPERM : RT_EOK;
}

static hpm_stat_t hpm_sdmmc_transfer_polling(struct hpm_mmcsd *mmcsd, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer)
{
    hpm_stat_t status;
    SDXC_Type *base = mmcsd->sdxc_base;
    sdxc_command_t *cmd = xfer->command;
    sdxc_data_t *data = xfer->data;
    volatile uint32_t interrupt_status;
    volatile rt_tick_t start_tick;
    rt_tick_t current_tick;
    bool need_chk_xfer_stat = false;
    sdxc_clear_interrupt_status(base, ~0UL);
    if (data == NULL)
    {
        (void)sdxc_send_command(base, cmd);
        /* Wait until idle */
        start_tick = rt_tick_get();
        do
        {
            interrupt_status = sdxc_get_interrupt_status(base);
            status = sdxc_parse_interrupt_status(base);
            HPM_BREAK_IF(status != status_success);
            current_tick = rt_tick_get();
            if ((current_tick - start_tick) > RT_TICK_PER_SECOND) {
                status = status_timeout;
                break;
            }
        } while (!IS_HPM_BITMASK_SET(interrupt_status, SDXC_INT_STAT_CMD_COMPLETE_MASK));

        if ((status == status_success) && (cmd->resp_type == sdxc_dev_resp_r1b))
        {
            need_chk_xfer_stat = true;
        }
    }
    else
    {
        status = sdxc_transfer_nonblocking(base, dma_config, xfer);
        if (status != status_success)
        {
            return status;
        }
        if (dma_config->dma_type == sdxc_dmasel_adma2)
        {
            /* Wait until idle */
            interrupt_status = sdxc_get_interrupt_status(base);
            start_tick = rt_tick_get();
            while (!IS_HPM_BITMASK_SET(interrupt_status, SDXC_INT_STAT_CMD_COMPLETE_MASK))
            {
                interrupt_status = sdxc_get_interrupt_status(base);
                status = sdxc_parse_interrupt_status(base);
                HPM_BREAK_IF(status != status_success);
                current_tick = rt_tick_get();
                if ((current_tick - start_tick) > RT_TICK_PER_SECOND)
                {
                    status = status_timeout;
                    break;
                }
            }
        }

        if (status == status_success)
        {
            need_chk_xfer_stat = true;
        }
    }

    if (need_chk_xfer_stat)
    {
        interrupt_status = sdxc_get_interrupt_status(base);
        start_tick = rt_tick_get();
        while (!IS_HPM_BITMASK_SET(interrupt_status, SDXC_INT_STAT_XFER_COMPLETE_MASK | SDXC_STS_ERROR))
        {
            interrupt_status = sdxc_get_interrupt_status(base);
            status = sdxc_parse_interrupt_status(base);
            HPM_BREAK_IF(status != status_success);
            current_tick = rt_tick_get();
            if ((current_tick - start_tick) > RT_TICK_PER_SECOND)
            {
                status = status_timeout;
                break;
            }
        }
    }
    if (status == status_success)
    {
        status = sdxc_receive_cmd_response(base, cmd);
    }

    return status;
}

static hpm_stat_t hpm_sdmmc_transfer_interrupt_driven(struct hpm_mmcsd *mmcsd, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer)
{
    hpm_stat_t status;
    SDXC_Type *base = mmcsd->sdxc_base;
    sdxc_command_t *cmd = xfer->command;
    sdxc_data_t *data = xfer->data;
    bool need_chk_xfer_stat = false;
    sdxc_clear_interrupt_status(base, ~0UL);
    if (data == NULL)
    {
        (void)sdxc_send_command(base, cmd);
        /* Wait until idle */
        const uint32_t wait_event_flags = SDXC_INT_STAT_CMD_COMPLETE_MASK \
                                        | SDXC_INT_STAT_ERR_INTERRUPT_MASK;
        rt_err_t err = rt_event_recv(mmcsd->xfer_event, wait_event_flags, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_TICK_PER_SECOND, NULL);
        if (err == RT_EOK)
        {
            status = sdxc_parse_interrupt_status(base);
        }
        else
        {
            status = status_timeout;
        }

        if ((status == status_success) && (cmd->resp_type == sdxc_dev_resp_r1b))
        {
            need_chk_xfer_stat = true;
        }
    }
    else
    {
        status = sdxc_transfer_nonblocking(base, dma_config, xfer);
        if (status != status_success)
        {
            return status;
        }
        if (dma_config->dma_type == sdxc_dmasel_adma2)
        {
            const uint32_t wait_event_flags = SDXC_INT_STAT_CMD_COMPLETE_MASK | SDXC_INT_STAT_ERR_INTERRUPT_MASK;
            rt_err_t err = rt_event_recv(mmcsd->xfer_event, wait_event_flags, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_TICK_PER_SECOND, NULL);
            if (err == RT_EOK)
            {
                status = sdxc_parse_interrupt_status(base);
            }
            else
            {
                status = status_timeout;
            }
        }

        if (status == status_success)
        {
            need_chk_xfer_stat = true;
        }
    }
    if (need_chk_xfer_stat)
    {
        const uint32_t wait_event_flags = SDXC_INT_STAT_XFER_COMPLETE_MASK | SDXC_INT_STAT_ERR_INTERRUPT_MASK;
        rt_err_t err = rt_event_recv(mmcsd->xfer_event, wait_event_flags, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_TICK_PER_SECOND, NULL);
        if (err == RT_EOK)
        {
            status = sdxc_parse_interrupt_status(base);
        }
    }
    if (status == status_success)
    {
        status = sdxc_receive_cmd_response(base, cmd);
    }

    return status;
}


static hpm_stat_t hpm_sdmmc_transfer(struct hpm_mmcsd *mmcsd, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer)
{
    if (mmcsd->enable_interrupt_driven)
    {
        return hpm_sdmmc_transfer_interrupt_driven(mmcsd, dma_config, xfer);
    }
    else
    {
        return hpm_sdmmc_transfer_polling(mmcsd, dma_config, xfer);
    }
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
    bool need_copy_back = false;
    hpm_stat_t err = status_invalid_argument;
    struct hpm_mmcsd *mmcsd = (struct hpm_mmcsd *) host->private_data;
    struct rt_mmcsd_cmd *cmd = req->cmd;
    struct rt_mmcsd_data *data = cmd->data;

    /* configure command */
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
        sdxc_data.block_size = data->blksize;
        sdxc_data.block_cnt = data->blks;

        /* configure adma3 */
        adma_config.dma_type = sdxc_dmasel_adma3;
        adma_config.adma_table = (uint32_t*) core_local_mem_to_sys_address(BOARD_RUNNING_CORE,
                                                                           (uint32_t) mmcsd->sdxc_adma_table);
        adma_config.adma_table_words = SDXC_ADMA_TABLE_WORDS;
        size_t xfer_buf_addr = (uint32_t)data->buf;
        uint32_t xfer_len = data->blks * data->blksize;
        bool need_cache_maintenance = true;
        if ((req->data->flags & DATA_DIR_WRITE) != 0U)
        {
            uint32_t write_size = xfer_len;
            size_t aligned_start;
            uint32_t aligned_size;
            if ((xfer_buf_addr % CACHELINE_SIZE != 0) || (write_size % CACHELINE_SIZE != 0))
            {
                uint32_t write_size = xfer_len;
                aligned_size = SDXC_CACHELINE_ALIGN_UP(write_size);
                rt_memcpy(mmcsd->data_buf, data->buf, xfer_len);
                rt_memset(&mmcsd->data_buf[write_size], 0, aligned_size - write_size);
                sdxc_data.tx_data = (uint32_t const *)core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t)mmcsd->data_buf);
                aligned_start = (uint32_t)sdxc_data.tx_data;
                need_cache_maintenance = !mmcsd->use_noncacheable_buf;
            }
            else
            {
                sdxc_data.tx_data = (uint32_t const *)core_local_mem_to_sys_address(BOARD_RUNNING_CORE, xfer_buf_addr);
                aligned_start = (uint32_t)sdxc_data.tx_data;
                aligned_size = write_size;
            }
            if (need_cache_maintenance)
            {
                l1c_dc_flush(aligned_start, aligned_size);
            }

            sdxc_data.rx_data = NULL;
        }
        else
        {
            uint32_t read_size = xfer_len;
            uint32_t aligned_read_size;
            if ((xfer_buf_addr % CACHELINE_SIZE != 0) || (read_size % CACHELINE_SIZE != 0))
            {
                aligned_read_size = SDXC_CACHELINE_ALIGN_UP(read_size);
                sdxc_data.rx_data = (uint32_t *)core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t)mmcsd->data_buf);
                need_copy_back = true;
                need_cache_maintenance = !mmcsd->use_noncacheable_buf;
            }
            else
            {
                aligned_read_size = read_size;
                sdxc_data.rx_data = (uint32_t *)core_local_mem_to_sys_address(BOARD_RUNNING_CORE, xfer_buf_addr);
            }
            /* Invalidate cache-line for the new allocated buffer */
            if (need_cache_maintenance)
            {
                l1c_dc_invalidate((uint32_t)sdxc_data.rx_data, aligned_read_size);
            }
            sdxc_data.tx_data = RT_NULL;
        }
        xfer.data = &sdxc_data;

        /* Align the write/read size since the ADMA engine in the SDXC cannot transfer unaligned size of data */
        if ((cmd->cmd_code == SD_IO_RW_EXTENDED) && (xfer_len % SDXC_ADMA_XFER_SIZE_ALIGNMENT != 0))
        {
            sdio_cmd53_arg_t cmd53_arg;
            cmd53_arg.value = sdxc_cmd.cmd_argument;
            cmd53_arg.count = HPM_ALIGN_UP(xfer_len, SDXC_ADMA_XFER_SIZE_ALIGNMENT);
            sdxc_cmd.cmd_argument = cmd53_arg.value;
            sdxc_data.block_size = HPM_ALIGN_UP(xfer_len, SDXC_ADMA_XFER_SIZE_ALIGNMENT);
        }
    }

    if ((req->data->blks > 1) && ((cmd->cmd_code == READ_MULTIPLE_BLOCK) || ((cmd->cmd_code == WRITE_MULTIPLE_BLOCK))))
    {
        xfer.data->enable_auto_cmd12 = true;
    }

    err = hpm_sdmmc_transfer(mmcsd, &adma_config, &xfer);
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
                                                        sdxc_cmd.response[1],
                                                        sdxc_cmd.response[2],
                                                        sdxc_cmd.response[3]);
        }
        else
        {
            LOG_I("resp:0x%08x\n", sdxc_cmd.response[0]);
        }
    }
    if ((sdxc_data.rx_data != NULL) && (cmd->err == RT_EOK))
    {
        uint32_t read_size = data->blks * data->blksize;
        if (need_copy_back)
        {
            rt_memcpy(data->buf, mmcsd->data_buf, read_size);
        }
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
    RT_ASSERT(mmcsd->sdxc_base != RT_NULL);
    SDXC_Type *base = mmcsd->sdxc_base;
    if (en != 0)
    {
        sdxc_enable_interrupt_signal(base, SDXC_INT_STAT_CARD_INTERRUPT_MASK, true);
        sdxc_enable_interrupt_status(base, SDXC_INT_STAT_CARD_INTERRUPT_MASK, true);
    }
    else
    {
        sdxc_enable_interrupt_status(base, SDXC_INT_STAT_CARD_INTERRUPT_MASK, false);
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

    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_sdxcs); i++)
    {
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

        if (!mmcsd->use_noncacheable_buf)
        {
            mmcsd->data_buf = rt_malloc_align(mmcsd->data_buf_size, CACHELINE_SIZE);
        }
        RT_ASSERT(mmcsd->data_buf != RT_NULL);
        host->max_seg_size = mmcsd->data_buf_size;
        host->max_dma_segs = 1;
        host->max_blk_size = 512;
        host->max_blk_count = mmcsd->data_buf_size / SDMMC_DEFAULT_SECTOR_SIZE;


        mmcsd->host = host;

        /* Perform necessary initialization */
        board_sd_configure_clock(mmcsd->sdxc_base, 375000, true);

        sdxc_config_t sdxc_config = { 0 };
        sdxc_config.data_timeout = SDXC_DATA_TIMEOUT;
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

        if (mmcsd->enable_interrupt_driven)
        {
            char event_name[RT_NAME_MAX];
            snprintf(event_name, sizeof(event_name), "%s%s", mmcsd->name, "_evt");
            mmcsd->xfer_event = rt_event_create(event_name, RT_IPC_FLAG_FIFO);
            RT_ASSERT(mmcsd->xfer_event != RT_NULL);
            const uint32_t irq_mask = SDXC_INT_STAT_CMD_COMPLETE_MASK \
                                    | SDXC_INT_STAT_XFER_COMPLETE_MASK \
                                    | SDXC_INT_STAT_ERR_INTERRUPT_MASK;
            sdxc_enable_interrupt_signal(mmcsd->sdxc_base, irq_mask, true);
        }
        intc_m_enable_irq_with_priority(mmcsd->irq_num, mmcsd->irq_priority);

        mmcsd_change(host);
    }

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
