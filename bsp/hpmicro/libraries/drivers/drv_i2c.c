/*
 * Copyright (c) 2022-2024 HPMicro
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
#include "hpm_dmamux_drv.h"
#include "hpm_l1c_drv.h"
#include "board.h"


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
    rt_sem_t xfer_sem;
    rt_bool_t enable_dma;
    rt_uint8_t dmamux;
    dma_resource_t dma;
    rt_uint8_t i2c_irq;
    rt_uint8_t is_read;
};

static struct hpm_i2c hpm_i2cs[] =
{
#if defined(BSP_USING_I2C0)
    {
        .base = HPM_I2C0,
        .bus_name = "i2c0",
        .clk_name = clock_i2c0,
#if defined(BSP_I2C0_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .dmamux = HPM_DMA_SRC_I2C0,
        .i2c_irq = IRQn_I2C0,
    },
#endif
#if defined(BSP_USING_I2C1)
    {
        .base = HPM_I2C1,
        .bus_name = "i2c1",
        .clk_name = clock_i2c1,
#if defined(BSP_I2C1_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .dmamux = HPM_DMA_SRC_I2C1,
        .i2c_irq = IRQn_I2C1,
    },
#endif
#if defined(BSP_USING_I2C2)
    {
        .base = HPM_I2C2,
        .bus_name = "i2c2",
        .clk_name = clock_i2c2,
#if defined(BSP_I2C2_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .dmamux = HPM_DMA_SRC_I2C2,
        .i2c_irq = IRQn_I2C2,
    },
#endif
#if defined(BSP_USING_I2C3)
    {
        .base = HPM_I2C3,
        .bus_name = "i2c3",
        .clk_name = clock_i2c3,
#if defined(BSP_I2C3_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .dmamux = HPM_DMA_SRC_I2C3,
        .i2c_irq = IRQn_I2C3,
    },
#endif
};
static hpm_stat_t i2c_transfer(I2C_Type *ptr, const uint16_t device_address,
                                    uint8_t *buf, const uint32_t size,  uint16_t flags);
static rt_ssize_t hpm_i2c_master_transfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num);
static hpm_stat_t i2c_tx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, I2C_Type *i2c_ptr, uint32_t src, uint32_t size);
static hpm_stat_t i2c_rx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, I2C_Type *i2c_ptr, uint32_t dst, uint32_t size);

struct rt_i2c_bus_device_ops hpm_i2c_ops =
{
    hpm_i2c_master_transfer,
    RT_NULL,
    RT_NULL
};

static inline void handle_i2c_isr(I2C_Type *ptr)
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
                rt_sem_release(hpm_i2cs[i].xfer_sem);
            }
        }
        i2c_disable_irq(ptr, I2C_EVENT_TRANSACTION_COMPLETE);
        i2c_clear_status(ptr, I2C_EVENT_TRANSACTION_COMPLETE);
    }
    rt_hw_interrupt_enable(level);
}

#if defined(BSP_USING_I2C0)
void i2c0_isr(void)
{
    handle_i2c_isr(HPM_I2C0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_I2C0, i2c0_isr);
#endif

#if defined(BSP_USING_I2C1)
void i2c1_isr(void)
{
    handle_i2c_isr(HPM_I2C1);
}
SDK_DECLARE_EXT_ISR_M(IRQn_I2C1, i2c1_isr);
#endif

#if defined(BSP_USING_I2C2)
void i2c2_isr(void)
{
    handle_i2c_isr(HPM_I2C2);
}
SDK_DECLARE_EXT_ISR_M(IRQn_I2C2, i2c2_isr);
#endif

#if defined(BSP_USING_I2C3)
void i2c3_isr(void)
{
    handle_i2c_isr(HPM_I2C3);
}
SDK_DECLARE_EXT_ISR_M(IRQn_I2C3, i2c3_isr);
#endif

static hpm_stat_t i2c_tx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, I2C_Type *i2c_ptr, uint32_t src, uint32_t size)
{
    dma_handshake_config_t config;

    dma_default_handshake_config(dma_ptr, &config);
    config.ch_index = ch_num;
    config.dst = (uint32_t)&i2c_ptr->DATA;
    config.dst_fixed = true;
    config.src = src;
    config.src_fixed = false;
    config.data_width = DMA_TRANSFER_WIDTH_BYTE;
    config.size_in_byte = size;

    return dma_setup_handshake(dma_ptr, &config, true);
}

static hpm_stat_t i2c_rx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, I2C_Type *i2c_ptr, uint32_t dst, uint32_t size)
{
    dma_handshake_config_t config;

    dma_default_handshake_config(dma_ptr, &config);
    config.ch_index = ch_num;
    config.dst = dst;
    config.dst_fixed = false;
    config.src = (uint32_t)&i2c_ptr->DATA;
    config.src_fixed = true;
    config.data_width = DMA_TRANSFER_WIDTH_BYTE;
    config.size_in_byte = size;

    return dma_setup_handshake(dma_ptr, &config, true);
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
        if (i2c->is_read == true)
        {
            rt_sem_release(i2c->xfer_sem);
        }
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
                }
                else
                {
                    aligned_buf = (uint8_t*)HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)raw_alloc_buf);
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
                        /* sequential transfer now is not support dma */
                        if ((msg->flags & RT_I2C_NO_START) || (msg->flags & RT_I2C_NO_STOP) ||
                            (msg->flags & RT_I2C_NO_READ_ACK) || (msg->flags & RT_I2C_NO_READ_ACK) ) {
                            i2c_stat = status_invalid_argument;
                            break;
                        }
                        i2c_info->is_read = true;
                        i2c_enable_irq(i2c_info->base, I2C_EVENT_TRANSACTION_COMPLETE);
                        dmamux_config(HPM_DMAMUX, i2c_info->dma.channel, i2c_info->dmamux, true);
                        i2c_stat = i2c_rx_trigger_dma(i2c_info->dma.base, i2c_info->dma.channel, i2c_info->base,
                                            core_local_mem_to_sys_address(0, (uint32_t) dummy_buf), transfer_len);
                        if (i2c_stat != status_success)
                        {
                            break;
                        }
                        i2c_stat = i2c_master_start_dma_read(i2c_info->base, msg->addr, msg->len);
                        if (i2c_stat != status_success)
                        {
                            break;
                        }
                        rt_sem_take(i2c_info->xfer_sem, RT_WAITING_FOREVER);
                    }
                    else
                    {
                        i2c_master_transfer(i2c_info->base, msg->addr, dummy_buf, transfer_len, msg->flags);
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
                        /* sequential transfer now is not support dma */
                        if ((msg->flags & RT_I2C_NO_START) || (msg->flags & RT_I2C_NO_STOP) ||
                            (msg->flags & RT_I2C_NO_READ_ACK) || (msg->flags & RT_I2C_NO_READ_ACK) ) {
                            i2c_stat = status_invalid_argument;
                            break;
                        }
                        i2c_info->is_read = false;
                        i2c_enable_irq(i2c_info->base, I2C_EVENT_TRANSACTION_COMPLETE);
                        dmamux_config(HPM_DMAMUX, i2c_info->dma.channel, i2c_info->dmamux, true);
                        i2c_stat = i2c_tx_trigger_dma(i2c_info->dma.base, i2c_info->dma.channel, i2c_info->base,
                                            core_local_mem_to_sys_address(0, (uint32_t) dummy_buf), transfer_len);
                        if (i2c_stat != status_success)
                        {
                            break;
                        }
                        i2c_stat = i2c_master_start_dma_write(i2c_info->base, msg->addr, msg->len);
                        if (i2c_stat != status_success)
                        {
                            break;
                        }
                        rt_sem_take(i2c_info->xfer_sem, RT_WAITING_FOREVER);
                    }
                    else
                    {
                        i2c_master_transfer(i2c_info->base, msg->addr, dummy_buf, transfer_len, msg->flags);
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
    }

    if (i2c_stat != status_success)
    {
        return ret;
    }

    ret = i;
    return ret;
}


int rt_hw_i2c_init(void)
{
    rt_err_t ret = RT_EOK;
    hpm_stat_t stat;
    i2c_config_t config;
    rt_uint32_t freq;
    char sem_name[RT_NAME_MAX];

    for (uint32_t i = 0; i < sizeof(hpm_i2cs) / sizeof(hpm_i2cs[0]); i++) {
        init_i2c_pins(hpm_i2cs[i].base);
        clock_add_to_group(hpm_i2cs[i].clk_name, 0);
        clock_set_source_divider(hpm_i2cs[i].clk_name, clk_src_osc24m, 1U);

        config.i2c_mode = i2c_mode_normal;
        config.is_10bit_addressing = false;
        freq = clock_get_frequency(hpm_i2cs[i].clk_name);
        stat = i2c_init_master(hpm_i2cs[i].base, freq, &config);
        if (stat != status_success) {
            LOG_E("rt i2c device %s init failed", hpm_i2cs[i].bus_name);
        }

        hpm_i2cs[i].bus.ops = &hpm_i2c_ops;
        if (hpm_i2cs[i].enable_dma)
        {
            stat = dma_mgr_request_resource(&hpm_i2cs[i].dma);
            if (stat != status_success)
            {
                return -RT_ERROR;
            }
            dma_mgr_install_chn_tc_callback(&hpm_i2cs[i].dma, i2c_dma_channel_tc_callback, (void *)&hpm_i2cs[i]);
            dma_mgr_enable_dma_irq_with_priority(&hpm_i2cs[i].dma, 1);
            intc_m_enable_irq_with_priority(hpm_i2cs[i].i2c_irq, 2);
            i2c_disable_irq(hpm_i2cs[i].base, I2C_EVENT_TRANSACTION_COMPLETE);
            rt_sprintf(sem_name, "%s_s", hpm_i2cs[i].bus_name);
            hpm_i2cs[i].xfer_sem = rt_sem_create(sem_name, 0, RT_IPC_FLAG_PRIO);
            if (hpm_i2cs[i].xfer_sem == RT_NULL)
            {
                ret = RT_ENOMEM;
                break;
            }
        }
        ret = rt_i2c_bus_device_register(&hpm_i2cs[i].bus, hpm_i2cs[i].bus_name);
        if (ret != RT_EOK) {
            LOG_E("rt i2c device %s register failed, status=%d\n", hpm_i2cs[i].bus_name, ret);
        }
    }

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */

#endif /*BSP_USING_I2C*/

