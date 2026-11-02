/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>
#ifdef BSP_USING_I2C
#include "drv_i2c.h"
#include "hpm_i2c_drv.h"
#include "hpm_dma_mgr.h"
#include "hpm_l1c_drv.h"
#include "board.h"
#include "hpm_dmamux_drv.h"

#ifdef RT_USING_I2C

#define HPM_RTT_DRV_RETRY_TIMEOUT (1000000)

#ifndef HPM_I2C_DRV_DEFAULT_RETRY_COUNT
#define HPM_I2C_DRV_DEFAULT_RETRY_COUNT (5000U)
#endif

struct hpm_i2c
{
    struct rt_i2c_bus_device bus;
    I2C_Type *base;
    clock_name_t clk_name;
    char *bus_name;
    rt_sem_t i2c_xfer_sem;
    rt_sem_t dma_xfer_sem;
    rt_bool_t enable_dma;
    rt_uint8_t dmamux;
    dma_resource_t dma;
    rt_uint8_t i2c_irq;
    rt_uint8_t is_read;
    rt_uint8_t irq_priority;
};

/* Macros to reduce repetitive I2C configuration code */
#define HPM_I2C_CONFIG(idx) \
    { \
        .base = HPM_I2C##idx, \
        .bus_name = "i2c"#idx, \
        .clk_name = clock_i2c##idx, \
        HPM_I2C_DMA_CONFIG_##idx \
        .dmamux = HPM_DMA_SRC_I2C##idx, \
        .i2c_irq = IRQn_I2C##idx, \
        HPM_I2C_IRQ_PRIORITY_##idx \
    }

/* DMA configuration per instance */
#if defined(BSP_I2C0_USING_DMA)
#define HPM_I2C_DMA_CONFIG_0 .enable_dma = RT_TRUE,
#else
#define HPM_I2C_DMA_CONFIG_0 .enable_dma = RT_FALSE,
#endif

#if defined(BSP_I2C1_USING_DMA)
#define HPM_I2C_DMA_CONFIG_1 .enable_dma = RT_TRUE,
#else
#define HPM_I2C_DMA_CONFIG_1
#endif

#if defined(BSP_I2C2_USING_DMA)
#define HPM_I2C_DMA_CONFIG_2 .enable_dma = RT_TRUE,
#else
#define HPM_I2C_DMA_CONFIG_2 .enable_dma = RT_FALSE,
#endif

#if defined(BSP_I2C3_USING_DMA)
#define HPM_I2C_DMA_CONFIG_3 .enable_dma = RT_TRUE,
#else
#define HPM_I2C_DMA_CONFIG_3 .enable_dma = RT_FALSE,
#endif

#if defined(BSP_I2C4_USING_DMA)
#define HPM_I2C_DMA_CONFIG_4 .enable_dma = RT_TRUE,
#else
#define HPM_I2C_DMA_CONFIG_4
#endif

#if defined(BSP_I2C5_USING_DMA)
#define HPM_I2C_DMA_CONFIG_5 .enable_dma = RT_TRUE,
#else
#define HPM_I2C_DMA_CONFIG_5 .enable_dma = RT_FALSE,
#endif

#if defined(BSP_I2C6_USING_DMA)
#define HPM_I2C_DMA_CONFIG_6 .enable_dma = RT_TRUE,
#else
#define HPM_I2C_DMA_CONFIG_6 .enable_dma = RT_FALSE,
#endif

#if defined(BSP_I2C7_USING_DMA)
#define HPM_I2C_DMA_CONFIG_7 .enable_dma = RT_TRUE,
#else
#define HPM_I2C_DMA_CONFIG_7
#endif

/* IRQ priority configuration per instance */
#if defined(BSP_I2C0_IRQ_PRIORITY)
#define HPM_I2C_IRQ_PRIORITY_0 .irq_priority = BSP_I2C0_IRQ_PRIORITY,
#else
#define HPM_I2C_IRQ_PRIORITY_0 .irq_priority = 1,
#endif

#if defined(BSP_I2C1_IRQ_PRIORITY)
#define HPM_I2C_IRQ_PRIORITY_1 .irq_priority = BSP_I2C1_IRQ_PRIORITY,
#else
#define HPM_I2C_IRQ_PRIORITY_1 .irq_priority = 1,
#endif

#if defined(BSP_I2C2_IRQ_PRIORITY)
#define HPM_I2C_IRQ_PRIORITY_2 .irq_priority = BSP_I2C2_IRQ_PRIORITY,
#else
#define HPM_I2C_IRQ_PRIORITY_2 .irq_priority = 1,
#endif

#if defined(BSP_I2C3_IRQ_PRIORITY)
#define HPM_I2C_IRQ_PRIORITY_3 .irq_priority = BSP_I2C3_IRQ_PRIORITY,
#else
#define HPM_I2C_IRQ_PRIORITY_3 .irq_priority = 1,
#endif

#if defined(BSP_I2C4_IRQ_PRIORITY)
#define HPM_I2C_IRQ_PRIORITY_4 .irq_priority = BSP_I2C4_IRQ_PRIORITY,
#else
#define HPM_I2C_IRQ_PRIORITY_4 .irq_priority = 1,
#endif

#if defined(BSP_I2C5_IRQ_PRIORITY)
#define HPM_I2C_IRQ_PRIORITY_5 .irq_priority = BSP_I2C5_IRQ_PRIORITY,
#else
#define HPM_I2C_IRQ_PRIORITY_5 .irq_priority = 1,
#endif

#if defined(BSP_I2C6_IRQ_PRIORITY)
#define HPM_I2C_IRQ_PRIORITY_6 .irq_priority = BSP_I2C6_IRQ_PRIORITY,
#else
#define HPM_I2C_IRQ_PRIORITY_6 .irq_priority = 1,
#endif

#if defined(BSP_I2C7_IRQ_PRIORITY)
#define HPM_I2C_IRQ_PRIORITY_7 .irq_priority = BSP_I2C7_IRQ_PRIORITY,
#else
#define HPM_I2C_IRQ_PRIORITY_7 .irq_priority = 1,
#endif

#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
/* Macro for ISR handler declaration and implementation */
#define HPM_I2C_ISR_HANDLER(idx) \
    SDK_DECLARE_EXT_ISR_M(IRQn_I2C##idx, i2c##idx##_isr); \
    void i2c##idx##_isr(void) \
    { \
        handle_i2c_isr(HPM_I2C##idx); \
    }
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

static struct hpm_i2c hpm_i2cs[] =
{
#if defined(BSP_USING_I2C0)
    HPM_I2C_CONFIG(0),
#endif
#if defined(BSP_USING_I2C1)
    HPM_I2C_CONFIG(1),
#endif
#if defined(BSP_USING_I2C2)
    HPM_I2C_CONFIG(2),
#endif
#if defined(BSP_USING_I2C3)
    HPM_I2C_CONFIG(3),
#endif
#if defined(BSP_USING_I2C4)
    HPM_I2C_CONFIG(4),
#endif
#if defined(BSP_USING_I2C5)
    HPM_I2C_CONFIG(5),
#endif
#if defined(BSP_USING_I2C6)
    HPM_I2C_CONFIG(6),
#endif
#if defined(BSP_USING_I2C7)
    HPM_I2C_CONFIG(7),
#endif
};

static rt_ssize_t hpm_i2c_master_transfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num);
static rt_err_t hpm_i2c_bus_control(struct rt_i2c_bus_device *bus, int cmd, void *args);
static hpm_stat_t i2c_tx_trigger_dma(const dma_resource_t *resource, I2C_Type *i2c_ptr, uint32_t src, uint32_t size);
static hpm_stat_t i2c_rx_trigger_dma(const dma_resource_t *resource, I2C_Type *i2c_ptr, uint32_t dst, uint32_t size);
static hpm_stat_t hpm_i2c_master_start_dma_transfer(I2C_Type *i2c_ptr, const uint16_t device_address, uint32_t size, uint16_t flags);
static void hpm_i2c_clear_xfer_sems(struct hpm_i2c *i2c);
static void hpm_i2c_prepare_dma_xfer(struct hpm_i2c *i2c);

struct rt_i2c_bus_device_ops hpm_i2c_ops =
{
    hpm_i2c_master_transfer,
    RT_NULL,
    hpm_i2c_bus_control
};

#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
static inline void handle_i2c_isr(I2C_Type *ptr)
#else
static inline void handle_i2c_isr(int vector, I2C_Type *ptr)
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
{
    volatile uint32_t irq_status;
    RT_ASSERT(ptr != RT_NULL);
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    irq_status = i2c_get_status(ptr);
    if (irq_status & I2C_EVENT_TRANSACTION_COMPLETE)
    {
        for (uint32_t i = 0; i < sizeof(hpm_i2cs) / sizeof(hpm_i2cs[0]); i++)
        {
            if (hpm_i2cs[i].base == ptr)
            {
                rt_sem_release(hpm_i2cs[i].i2c_xfer_sem);
            }
        }
        i2c_disable_irq(ptr, I2C_EVENT_TRANSACTION_COMPLETE);
        i2c_clear_status(ptr, I2C_EVENT_TRANSACTION_COMPLETE);
    }
    rt_hw_interrupt_enable(level);
}

#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
#if defined(BSP_USING_I2C0)
HPM_I2C_ISR_HANDLER(0)
#endif

#if defined(BSP_USING_I2C1)
HPM_I2C_ISR_HANDLER(1)
#endif

#if defined(BSP_USING_I2C2)
HPM_I2C_ISR_HANDLER(2)
#endif

#if defined(BSP_USING_I2C3)
HPM_I2C_ISR_HANDLER(3)
#endif

#if defined(BSP_USING_I2C4)
HPM_I2C_ISR_HANDLER(4)
#endif

#if defined(BSP_USING_I2C5)
HPM_I2C_ISR_HANDLER(5)
#endif

#if defined(BSP_USING_I2C6)
HPM_I2C_ISR_HANDLER(6)
#endif

#if defined(BSP_USING_I2C7)
HPM_I2C_ISR_HANDLER(7)
#endif
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

static hpm_stat_t i2c_tx_trigger_dma(const dma_resource_t *resource, I2C_Type *i2c_ptr, uint32_t src, uint32_t size)
{
    hpm_stat_t stat = status_success;

    HPM_CHECK_RET(dma_mgr_set_chn_src_work_mode(resource, DMA_MGR_HANDSHAKE_MODE_NORMAL));
    HPM_CHECK_RET(dma_mgr_set_chn_dst_work_mode(resource, DMA_MGR_HANDSHAKE_MODE_HANDSHAKE));
    HPM_CHECK_RET(dma_mgr_set_chn_src_addr_ctrl(resource, DMA_MGR_ADDRESS_CONTROL_INCREMENT));
    HPM_CHECK_RET(dma_mgr_set_chn_dst_addr_ctrl(resource, DMA_MGR_ADDRESS_CONTROL_FIXED));
    HPM_CHECK_RET(dma_mgr_set_chn_src_width(resource, DMA_MGR_TRANSFER_WIDTH_BYTE));
    HPM_CHECK_RET(dma_mgr_set_chn_dst_width(resource, DMA_MGR_TRANSFER_WIDTH_BYTE));
    HPM_CHECK_RET(dma_mgr_set_chn_src_addr(resource, src));
    HPM_CHECK_RET(dma_mgr_set_chn_dst_addr(resource, (uint32_t)&i2c_ptr->DATA));
    HPM_CHECK_RET(dma_mgr_set_chn_transize(resource, size));
    HPM_CHECK_RET(dma_mgr_enable_channel(resource));

    return stat;
}

static hpm_stat_t i2c_rx_trigger_dma(const dma_resource_t *resource, I2C_Type *i2c_ptr, uint32_t dst, uint32_t size)
{
    hpm_stat_t stat = status_success;

    HPM_CHECK_RET(dma_mgr_set_chn_src_work_mode(resource, DMA_MGR_HANDSHAKE_MODE_HANDSHAKE));
    HPM_CHECK_RET(dma_mgr_set_chn_dst_work_mode(resource, DMA_MGR_HANDSHAKE_MODE_NORMAL));
    HPM_CHECK_RET(dma_mgr_set_chn_src_addr_ctrl(resource, DMA_MGR_ADDRESS_CONTROL_FIXED));
    HPM_CHECK_RET(dma_mgr_set_chn_dst_addr_ctrl(resource, DMA_MGR_ADDRESS_CONTROL_INCREMENT));
    HPM_CHECK_RET(dma_mgr_set_chn_src_width(resource, DMA_MGR_TRANSFER_WIDTH_BYTE));
    HPM_CHECK_RET(dma_mgr_set_chn_dst_width(resource, DMA_MGR_TRANSFER_WIDTH_BYTE));
    HPM_CHECK_RET(dma_mgr_set_chn_src_addr(resource, (uint32_t)&i2c_ptr->DATA));
    HPM_CHECK_RET(dma_mgr_set_chn_dst_addr(resource, dst));
    HPM_CHECK_RET(dma_mgr_set_chn_transize(resource, size));
    HPM_CHECK_RET(dma_mgr_enable_channel(resource));

    return stat;
}

static void hpm_i2c_clear_sem(rt_sem_t sem)
{
    while (rt_sem_take(sem, 0) == RT_EOK)
    {
    }
}

static void hpm_i2c_clear_xfer_sems(struct hpm_i2c *i2c)
{
    hpm_i2c_clear_sem(i2c->i2c_xfer_sem);
    hpm_i2c_clear_sem(i2c->dma_xfer_sem);
}

static void hpm_i2c_prepare_dma_xfer(struct hpm_i2c *i2c)
{
    dma_mgr_disable_chn_irq(&i2c->dma, DMA_MGR_INTERRUPT_MASK_TC);
    i2c_disable_irq(i2c->base, I2C_EVENT_TRANSACTION_COMPLETE);
    hpm_i2c_clear_xfer_sems(i2c);
    dma_clear_transfer_status(i2c->dma.base, i2c->dma.channel);
    i2c_clear_status(i2c->base, I2C_STATUS_CMPL_MASK | I2C_STATUS_ADDRHIT_MASK);
}

static hpm_stat_t hpm_i2c_master_start_dma_transfer(I2C_Type *i2c_ptr,
                                                    const uint16_t device_address,
                                                    uint32_t size,
                                                    uint16_t flags)
{
    uint32_t retry = 0;
    uint32_t ctrl = 0;

    if (((size == 0) || (size > I2C_SOC_TRANSFER_COUNT_MAX))) {
        return status_invalid_argument;
    }

    if (flags & I2C_ADDR_10BIT) {
        i2c_enable_10bit_address_mode(i2c_ptr, true);
    } else {
        i2c_enable_10bit_address_mode(i2c_ptr, false);
    }

    i2c_clear_status(i2c_ptr, I2C_STATUS_CMPL_MASK | I2C_STATUS_ADDRHIT_MASK);
    i2c_clear_fifo(i2c_ptr);
    i2c_ptr->ADDR = I2C_ADDR_ADDR_SET(device_address);

    if (flags & I2C_RD) {
        ctrl |= I2C_CTRL_DIR_SET(I2C_DIR_MASTER_READ);
    } else {
        ctrl |= I2C_CTRL_DIR_SET(I2C_DIR_MASTER_WRITE);
    }

    if (flags & I2C_NO_START) {
        ctrl |= I2C_CTRL_PHASE_START_SET(false);
    } else {
        ctrl |= I2C_CTRL_PHASE_START_SET(true);
    }

    if (flags & I2C_NO_STOP) {
        ctrl |= I2C_CTRL_PHASE_STOP_SET(false);
    } else {
        ctrl |= I2C_CTRL_PHASE_STOP_SET(true);
    }

    i2c_ptr->CTRL = ctrl | I2C_CTRL_PHASE_ADDR_SET(true)
                    | I2C_CTRL_PHASE_DATA_SET(true)
#ifdef I2C_CTRL_DATACNT_HIGH_MASK
                    | I2C_CTRL_DATACNT_HIGH_SET(I2C_DATACNT_MAP(size) >> 8U)
#endif
                    | I2C_CTRL_DATACNT_SET(I2C_DATACNT_MAP(size));

    i2c_ptr->SETUP |= I2C_SETUP_DMAEN_MASK;
    i2c_ptr->CMD = I2C_CMD_ISSUE_DATA_TRANSMISSION;

    while (i2c_is_addrhit(i2c_ptr) == false) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            return status_i2c_no_addr_hit;
        }
        retry++;
    }
    i2c_clear_status(i2c_ptr, I2C_STATUS_ADDRHIT_MASK);

    return status_success;
}

static i2c_mode_t hpm_i2c_mode_from_hz(rt_uint32_t hz)
{
    if (hz <= 100000U)
    {
        return i2c_mode_normal;
    }
    if (hz <= 400000U)
    {
        return i2c_mode_fast;
    }

    return i2c_mode_fast_plus;
}

static rt_err_t hpm_i2c_bus_control(struct rt_i2c_bus_device *bus, int cmd, void *args)
{
    struct hpm_i2c *i2c_info = (struct hpm_i2c *)bus;
    i2c_config_t config;
    hpm_stat_t stat;
    rt_uint32_t freq;
    rt_uint32_t hz;

    RT_ASSERT(bus != RT_NULL);

    switch (cmd)
    {
    case RT_I2C_DEV_CTRL_CLK:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
        hz = *(rt_uint32_t *)args;
        if (hz == 0U)
        {
            return -RT_EINVAL;
        }
        config.i2c_mode = hpm_i2c_mode_from_hz(hz);
        config.is_10bit_addressing = false;
        freq = clock_get_frequency(i2c_info->clk_name);
        stat = i2c_init_master(i2c_info->base, freq, &config);
        if (i2c_info->enable_dma)
        {
            i2c_disable_irq(i2c_info->base, I2C_EVENT_TRANSACTION_COMPLETE);
        }
        return stat == status_success ? RT_EOK : -RT_ERROR;
    default:
        return -RT_EINVAL;
    }
}

void i2c_dma_channel_tc_callback(DMA_Type *ptr, uint32_t channel, void *user_data)
{
    struct hpm_i2c *i2c = (struct hpm_i2c *)user_data;
    RT_ASSERT(i2c != RT_NULL);
    RT_ASSERT(ptr != RT_NULL);
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    if ((i2c->dma.base == ptr) && i2c->dma.channel == channel)
    {
        dma_mgr_disable_chn_irq(&i2c->dma, DMA_MGR_INTERRUPT_MASK_TC);
        rt_sem_release(i2c->dma_xfer_sem);
    }
    rt_hw_interrupt_enable(level);
}

static rt_ssize_t hpm_i2c_master_transfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(msgs != RT_NULL);

    struct rt_i2c_msg *msg;
    struct hpm_i2c *i2c_info = (struct hpm_i2c *)bus;

    hpm_stat_t i2c_stat = status_success;
    rt_size_t ret = 0;
    rt_uint32_t i;
    rt_uint8_t *raw_alloc_buf = RT_NULL;
    rt_uint8_t *aligned_buf = RT_NULL;
    rt_uint8_t *dummy_buf = RT_NULL;
    rt_uint32_t aligned_len = 0;
    rt_uint32_t remaining_size = 0;
    rt_uint32_t transfer_len;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        aligned_buf = (uint8_t*) msg->buf;
        remaining_size = msg->len;
        if ((msg->len > 0) && (i2c_info->enable_dma))
        {
            aligned_len = (msg->len + HPM_L1C_CACHELINE_SIZE - 1U) & ~(HPM_L1C_CACHELINE_SIZE - 1U);
            if (l1c_dc_is_enabled())
            {
                if (msg->flags & RT_I2C_RD)
                {
                    /* The allocated pointer is always RT_ALIGN_SIZE aligned */
                    raw_alloc_buf = (uint8_t*)rt_malloc(aligned_len + HPM_L1C_CACHELINE_SIZE - RT_ALIGN_SIZE);
                    RT_ASSERT(raw_alloc_buf != RT_NULL);
                    aligned_buf = (uint8_t*)HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)raw_alloc_buf);
                }
                else
                {
                    /* The allocated pointer is always RT_ALIGN_SIZE aligned */
                    raw_alloc_buf = (uint8_t*)rt_malloc(aligned_len + HPM_L1C_CACHELINE_SIZE - RT_ALIGN_SIZE);
                    RT_ASSERT(raw_alloc_buf != RT_NULL);
                    aligned_buf = (uint8_t*)HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)raw_alloc_buf);
                    rt_memcpy(aligned_buf, msg->buf, msg->len);
                    l1c_dc_flush((uint32_t)aligned_buf, aligned_len);
                }
            }
        }
        else
        {
            aligned_buf = (uint8_t*) msg->buf;
        }

        if (msg->flags & RT_I2C_ADDR_10BIT)
        {
            i2c_enable_10bit_address_mode(i2c_info->base, true);
        }
        else
        {
            i2c_enable_10bit_address_mode(i2c_info->base, false);
        }
        dummy_buf = aligned_buf;
        if (msg->flags & RT_I2C_RD)
        {
            /* maybe probe i2c device */
            if (msg->len == 0)
            {
                i2c_stat = i2c_master_read(i2c_info->base, msg->addr, dummy_buf, remaining_size);
            }
            else
            {
                while (remaining_size)
                {
                    transfer_len = MIN(I2C_SOC_TRANSFER_COUNT_MAX, remaining_size);
                    if ((i2c_info->enable_dma))
                    {
                        if (msg->flags & RT_I2C_NO_READ_ACK) {
                            i2c_stat = status_invalid_argument;
                            break;
                        }
                        i2c_info->is_read = true;
                        hpm_i2c_prepare_dma_xfer(i2c_info);
                        i2c_stat = i2c_rx_trigger_dma(&i2c_info->dma, i2c_info->base,
                                            core_local_mem_to_sys_address(0, (uint32_t) dummy_buf), transfer_len);
                        if (i2c_stat != status_success)
                        {
                            break;
                        }
                        dma_mgr_enable_chn_irq(&i2c_info->dma, DMA_MGR_INTERRUPT_MASK_TC);
                        i2c_enable_irq(i2c_info->base, I2C_EVENT_TRANSACTION_COMPLETE);
                        i2c_stat = hpm_i2c_master_start_dma_transfer(i2c_info->base, msg->addr, transfer_len, msg->flags);
                        if (i2c_stat != status_success)
                        {
                            break;
                        }
                        rt_sem_take(i2c_info->dma_xfer_sem, RT_WAITING_FOREVER);
                        rt_sem_take(i2c_info->i2c_xfer_sem, RT_WAITING_FOREVER);
                    }
                    else
                    {
                        i2c_stat = i2c_master_transfer(i2c_info->base, msg->addr, dummy_buf, transfer_len, msg->flags);
                        if (i2c_stat != status_success)
                        {
                            break;
                        }
                    }
                    dummy_buf += transfer_len;
                    remaining_size -= transfer_len;
                }
                if (raw_alloc_buf != RT_NULL)
                {
                    l1c_dc_invalidate((uint32_t) aligned_buf, aligned_len);
                    rt_memcpy(msg->buf, aligned_buf, msg->len);
                    rt_free(raw_alloc_buf);
                    raw_alloc_buf = RT_NULL;
                    aligned_buf = RT_NULL;
                }
            }
        }
        else
        {
            /* maybe probe i2c device */
            if (msg->len == 0)
            {
                i2c_stat = i2c_master_write(i2c_info->base, msg->addr, dummy_buf, remaining_size);
            }
            else
            {
                while (remaining_size)
                {
                    transfer_len = MIN(I2C_SOC_TRANSFER_COUNT_MAX, remaining_size);
                    if (i2c_info->enable_dma)
                    {
                        if (msg->flags & RT_I2C_NO_READ_ACK) {
                            i2c_stat = status_invalid_argument;
                            break;
                        }
                        i2c_info->is_read = false;
                        hpm_i2c_prepare_dma_xfer(i2c_info);
                        i2c_stat = i2c_tx_trigger_dma(&i2c_info->dma, i2c_info->base,
                                            core_local_mem_to_sys_address(0, (uint32_t) dummy_buf), transfer_len);
                        if (i2c_stat != status_success)
                        {
                            break;
                        }
                        dma_mgr_enable_chn_irq(&i2c_info->dma, DMA_MGR_INTERRUPT_MASK_TC);
                        i2c_enable_irq(i2c_info->base, I2C_EVENT_TRANSACTION_COMPLETE);
                        i2c_stat = hpm_i2c_master_start_dma_transfer(i2c_info->base, msg->addr, transfer_len, msg->flags);
                        if (i2c_stat != status_success)
                        {
                            break;
                        }
                        rt_sem_take(i2c_info->dma_xfer_sem, RT_WAITING_FOREVER);
                        rt_sem_take(i2c_info->i2c_xfer_sem, RT_WAITING_FOREVER);
                    }
                    else
                    {
                        i2c_stat = i2c_master_transfer(i2c_info->base, msg->addr, dummy_buf, transfer_len, msg->flags);
                        if (i2c_stat != status_success)
                        {
                            break;
                        }
                    }
                    dummy_buf += transfer_len;
                    remaining_size -= transfer_len;
                }
                if (raw_alloc_buf != RT_NULL)
                {
                    rt_free(raw_alloc_buf);
                    raw_alloc_buf = RT_NULL;
                    aligned_buf = RT_NULL;
                }
            }
        }
        if (i2c_stat != status_success)
        {
            break;
        }
        ret++;
    }

    return ret;
}


int rt_hw_i2c_init(void)
{
    rt_err_t ret = RT_EOK;
    hpm_stat_t stat;
    i2c_config_t config;
    dma_mgr_chn_conf_t dma_config;
    rt_uint32_t freq;
    char sem_name[RT_NAME_MAX];

    for (uint32_t i = 0; i < sizeof(hpm_i2cs) / sizeof(hpm_i2cs[0]); i++) {
        if (init_i2c_pins(hpm_i2cs[i].base) != status_success) {
            LOG_E("Failed to initialize I2C%u pins. Please check board configuration", i);
            ret = -RT_ERROR;
            continue;
        }
        clock_add_to_group(hpm_i2cs[i].clk_name, BOARD_RUNNING_CORE & 0x1);
        clock_set_source_divider(hpm_i2cs[i].clk_name, clk_src_osc24m, 1U);

        config.i2c_mode = i2c_mode_normal;
        config.is_10bit_addressing = false;
        freq = clock_get_frequency(hpm_i2cs[i].clk_name);
        stat = i2c_init_master(hpm_i2cs[i].base, freq, &config);
        if (stat != status_success) {
            LOG_E("rt i2c device %s init failed", hpm_i2cs[i].bus_name);
            ret = -RT_ERROR;
        }

        hpm_i2cs[i].bus.ops = &hpm_i2c_ops;
        if (hpm_i2cs[i].enable_dma)
        {
            stat = dma_mgr_request_resource(&hpm_i2cs[i].dma);
            if (stat != status_success)
            {
                return -RT_ERROR;
            }
            dma_mgr_get_default_chn_config(&dma_config);
            dma_config.en_dmamux = true;
            dma_config.dmamux_src = hpm_i2cs[i].dmamux;
            dma_config.src_width = DMA_MGR_TRANSFER_WIDTH_BYTE;
            dma_config.dst_width = DMA_MGR_TRANSFER_WIDTH_BYTE;
            stat = dma_mgr_setup_channel(&hpm_i2cs[i].dma, &dma_config);
            if (stat != status_success)
            {
                return -RT_ERROR;
            }
            dma_mgr_install_chn_tc_callback(&hpm_i2cs[i].dma, i2c_dma_channel_tc_callback, (void *)&hpm_i2cs[i]);
            dma_mgr_enable_dma_irq_with_priority(&hpm_i2cs[i].dma, 1);
            intc_m_enable_irq_with_priority(hpm_i2cs[i].i2c_irq, hpm_i2cs[i].irq_priority);
            i2c_disable_irq(hpm_i2cs[i].base, I2C_EVENT_TRANSACTION_COMPLETE);
            rt_sprintf(sem_name, "%s_i", hpm_i2cs[i].bus_name);
            hpm_i2cs[i].i2c_xfer_sem = rt_sem_create(sem_name, 0, RT_IPC_FLAG_PRIO);
            if (hpm_i2cs[i].i2c_xfer_sem == RT_NULL)
            {
                ret = -RT_ENOMEM;
                break;
            }
            rt_sprintf(sem_name, "%s_d", hpm_i2cs[i].bus_name);
            hpm_i2cs[i].dma_xfer_sem = rt_sem_create(sem_name, 0, RT_IPC_FLAG_PRIO);
            if (hpm_i2cs[i].dma_xfer_sem == RT_NULL)
            {
                rt_sem_delete(hpm_i2cs[i].i2c_xfer_sem);
                hpm_i2cs[i].i2c_xfer_sem = RT_NULL;
                ret = -RT_ENOMEM;
                break;
            }
        }
        ret = rt_i2c_bus_device_register(&hpm_i2cs[i].bus, hpm_i2cs[i].bus_name);
        if (ret != RT_EOK) {
            LOG_E("rt i2c device %s register failed, status=%d\n", hpm_i2cs[i].bus_name, ret);
        }
#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
        /* Register I2C device to irq table */
        rt_hw_interrupt_install(hpm_i2cs[i].i2c_irq, (rt_isr_handler_t)handle_i2c_isr, hpm_i2cs[i].base, hpm_i2cs[i].bus_name);
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
    }

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */

#endif /*BSP_USING_I2C*/
