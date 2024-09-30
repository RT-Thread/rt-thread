/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-02-01   HPMicro     First version
 * 2023-02-15   HPMicro     Add DMA support
 * 2023-07-14   HPMicro     Manage the DMA buffer alignment in driver
 * 2023-12-14   HPMicro     change state blocking wait to interrupt semaphore wait for DMA
 * 2024-06-10   HPMicro     Add the SPI pin settings
 */
#include <rtthread.h>

#ifdef BSP_USING_SPI
#include <rtdevice.h>
#include "board.h"
#include "drv_spi.h"
#include "hpm_spi_drv.h"
#include "hpm_sysctl_drv.h"
#include "hpm_dma_mgr.h"
#include "hpm_dmamux_drv.h"

#include "hpm_l1c_drv.h"



struct hpm_spi
{
    uint32_t instance;
    char *bus_name;
    SPI_Type *spi_base;
    spi_control_config_t control_config;
    struct rt_spi_bus spi_bus;
    rt_sem_t xfer_sem;
    rt_bool_t enable_dma;
    rt_uint8_t tx_dmamux;
    rt_uint8_t rx_dmamux;
    dma_resource_t tx_dma;
    dma_resource_t rx_dma;
    rt_uint8_t spi_irq;
    rt_sem_t spi_xfer_done_sem;
    rt_sem_t txdma_xfer_done_sem;
    rt_sem_t rxdma_xfer_done_sem;
    void (*spi_pins_init)(SPI_Type *spi_base);
};

static rt_err_t hpm_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg);
static rt_ssize_t hpm_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *msg);

static struct hpm_spi hpm_spis[] =
{
#if defined(BSP_USING_SPI0)
    {
        .bus_name = "spi0",
        .spi_base = HPM_SPI0,
#if defined(BSP_SPI0_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI0_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI0_RX,
        .spi_irq   = IRQn_SPI0,
#if !defined BSP_SPI0_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI1)
    {
        .bus_name = "spi1",
        .spi_base = HPM_SPI1,
#if defined(BSP_SPI1_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI1_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI1_RX,
        .spi_irq   = IRQn_SPI1,
#if !defined BSP_SPI1_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI2)
    {
        .bus_name = "spi2",
        .spi_base = HPM_SPI2,
#if defined(BSP_SPI2_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI2_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI2_RX,
        .spi_irq   = IRQn_SPI2,
#if !defined BSP_SPI2_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI3)
    {
        .bus_name = "spi3",
        .spi_base = HPM_SPI3,
#if defined(BSP_SPI3_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI3_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI3_RX,
        .spi_irq   = IRQn_SPI3,
#if !defined BSP_SPI3_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI4)
    {
        .bus_name = "spi4",
        .spi_base = HPM_SPI4,
#if defined(BSP_SPI4_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI4_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI4_RX,
        .spi_irq   = IRQn_SPI4,
#if !defined BSP_SPI4_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI5)
    {
        .bus_name = "spi5",
        .spi_base = HPM_SPI5,
#if defined(BSP_SPI5_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI5_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI5_RX,
        .spi_irq   = IRQn_SPI5,
#if !defined BSP_SPI5_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI6)
    {
        .bus_name = "spi6",
        .spi_base = HPM_SPI6,
#if defined(BSP_SPI6_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI6_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI6_RX,
        .spi_irq   = IRQn_SPI6,
#if !defined BSP_SPI6_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
#if defined(BSP_USING_SPI7)
    {
        .bus_name = "spi7",
        .spi_base = HPM_SPI7,
#if defined(BSP_SPI7_USING_DMA)
        .enable_dma = RT_TRUE,
#endif
        .tx_dmamux = HPM_DMA_SRC_SPI7_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI7_RX,
        .spi_irq   = IRQn_SPI7,
#if !defined BSP_SPI7_USING_HARD_CS
        .spi_pins_init = init_spi_pins_with_gpio_as_cs,
#else
        .spi_pins_init = init_spi_pins,
#endif
    },
#endif
};

static struct rt_spi_ops hpm_spi_ops =
{
    .configure = hpm_spi_configure,
    .xfer = hpm_spi_xfer,
};

static inline void handle_spi_isr(SPI_Type *ptr)
{
    volatile uint32_t irq_status;
    RT_ASSERT(ptr != RT_NULL);
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    irq_status = spi_get_interrupt_status(ptr);
    if (irq_status & spi_end_int)
    {
        for (uint32_t i = 0; i < sizeof(hpm_spis) / sizeof(hpm_spis[0]); i++)
        {
            if (hpm_spis[i].spi_base == ptr)
            {
                rt_sem_release(hpm_spis[i].spi_xfer_done_sem);
            }
        }
        spi_disable_interrupt(ptr, spi_end_int);
        spi_clear_interrupt_status(ptr, spi_end_int);
    }
    rt_hw_interrupt_enable(level);
}

#if defined(BSP_USING_SPI0)
void spi0_isr(void)
{
    handle_spi_isr(HPM_SPI0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_SPI0, spi0_isr);
#endif

#if defined(BSP_USING_SPI1)
void spi1_isr(void)
{
    handle_spi_isr(HPM_SPI1);
}
SDK_DECLARE_EXT_ISR_M(IRQn_SPI1, spi1_isr);
#endif

#if defined(BSP_USING_SPI2)
void spi2_isr(void)
{
    handle_spi_isr(HPM_SPI2);
}
SDK_DECLARE_EXT_ISR_M(IRQn_SPI2, spi2_isr);
#endif

#if defined(BSP_USING_SPI3)
void spi3_isr(void)
{
    handle_spi_isr(HPM_SPI3);
}
SDK_DECLARE_EXT_ISR_M(IRQn_SPI3, spi3_isr);
#endif

void spi_dma_channel_tc_callback(DMA_Type *ptr, uint32_t channel, void *user_data)
{
    struct hpm_spi *spi = (struct hpm_spi *)user_data;
    RT_ASSERT(spi != RT_NULL);
    RT_ASSERT(ptr != RT_NULL);
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    if ((spi->tx_dma.base == ptr) && spi->tx_dma.channel == channel)
    {
        dma_mgr_disable_chn_irq(&spi->tx_dma, DMA_MGR_INTERRUPT_MASK_TC);
        rt_sem_release(spi->txdma_xfer_done_sem);
    }
    if ((spi->rx_dma.base == ptr) && spi->rx_dma.channel == channel)
    {
        dma_mgr_disable_chn_irq(&spi->rx_dma, DMA_MGR_INTERRUPT_MASK_TC);
        rt_sem_release(spi->rxdma_xfer_done_sem);
    }
    rt_hw_interrupt_enable(level);
}

static rt_err_t hpm_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    spi_timing_config_t timing_config = { 0 };
    spi_format_config_t format_config = { 0 };

    struct hpm_spi *spi = RT_NULL;

    spi = (struct hpm_spi *) (device->bus->parent.user_data);
    RT_ASSERT(spi != RT_NULL);

    if (cfg->data_width != 8 && cfg->data_width != 16 && cfg->data_width != 32)
    {
        return -RT_EINVAL;
    }

    spi_master_get_default_timing_config(&timing_config);
    spi_master_get_default_format_config(&format_config);

    spi->spi_pins_init(spi->spi_base);

    timing_config.master_config.clk_src_freq_in_hz = board_init_spi_clock(spi->spi_base);

    format_config.common_config.data_len_in_bits = cfg->data_width;
    format_config.common_config.cpha = cfg->mode & RT_SPI_CPHA ? 1 : 0;
    format_config.common_config.cpol = cfg->mode & RT_SPI_CPOL ? 1 : 0;
    format_config.common_config.lsb = cfg->mode & RT_SPI_MSB ? false : true;
    format_config.common_config.mosi_bidir = cfg->mode & RT_SPI_3WIRE ? true : false;
    spi_format_init(spi->spi_base, &format_config);

    if (cfg->max_hz > timing_config.master_config.clk_src_freq_in_hz)
    {
        cfg->max_hz = timing_config.master_config.clk_src_freq_in_hz;
    }
    timing_config.master_config.sclk_freq_in_hz = cfg->max_hz;

    spi_master_timing_init(spi->spi_base, &timing_config);

    spi_master_get_default_control_config(&spi->control_config);
    spi->control_config.master_config.addr_enable = false;
    spi->control_config.master_config.cmd_enable = false;
    spi->control_config.master_config.token_enable = false;
    spi->control_config.common_config.trans_mode = spi_trans_write_read_together;

    return RT_EOK;
}



static hpm_stat_t hpm_spi_xfer_polling(struct rt_spi_device *device, struct rt_spi_message *msg)
{
    struct hpm_spi *spi = (struct hpm_spi *) (device->bus->parent.user_data);
    hpm_stat_t spi_stat = status_success;

    uint32_t remaining_size = msg->length;
    uint32_t transfer_len;
    uint8_t *tx_buf = (uint8_t*) msg->send_buf;
    uint8_t *rx_buf = (uint8_t*) msg->recv_buf;
    while (remaining_size > 0)
    {
        transfer_len = MIN(SPI_SOC_TRANSFER_COUNT_MAX, remaining_size);
        spi->control_config.common_config.tx_dma_enable = false;
        spi->control_config.common_config.rx_dma_enable = false;
        if (msg->send_buf != NULL && msg->recv_buf != NULL)
        {
            spi->control_config.common_config.trans_mode = spi_trans_write_read_together;
            spi_stat = spi_transfer(spi->spi_base, &spi->control_config,
            NULL,
            NULL, tx_buf, transfer_len, rx_buf, transfer_len);
        }
        else if (msg->send_buf != NULL)
        {
            spi->control_config.common_config.trans_mode = spi_trans_write_only;
            spi_stat = spi_transfer(spi->spi_base, &spi->control_config,
            NULL,
            NULL, (uint8_t*) tx_buf, transfer_len,
            NULL, 0);
        }
        else
        {
            spi->control_config.common_config.trans_mode = spi_trans_read_only;
            spi_stat = spi_transfer(spi->spi_base, &spi->control_config,
            NULL,
            NULL,
            NULL, 0, rx_buf, transfer_len);
        }

        if (spi_stat != status_success)
        {
            break;
        }

        if (tx_buf != NULL)
        {
            tx_buf += transfer_len;
        }
        if (rx_buf != NULL)
        {
            rx_buf += transfer_len;
        }
        remaining_size -= transfer_len;
    }

    return spi_stat;
}

hpm_stat_t spi_tx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, SPI_Type *spi_ptr, uint32_t src, uint8_t data_width, uint32_t size)
{
    dma_handshake_config_t config;
    config.ch_index = ch_num;
    config.dst = (uint32_t)&spi_ptr->DATA;
    config.dst_fixed = true;
    config.src = src;
    config.src_fixed = false;
    config.data_width = data_width;
    config.size_in_byte = size;

    return dma_setup_handshake(dma_ptr, &config, true);
}

hpm_stat_t spi_rx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, SPI_Type *spi_ptr, uint32_t dst, uint8_t data_width, uint32_t size)
{
    dma_handshake_config_t config;
    config.ch_index = ch_num;
    config.dst = dst;
    config.dst_fixed = false;
    config.src = (uint32_t)&spi_ptr->DATA;
    config.src_fixed = true;
    config.data_width = data_width;
    config.size_in_byte = size;

    return dma_setup_handshake(dma_ptr, &config, true);
}

static rt_uint32_t hpm_spi_xfer_dma(struct rt_spi_device *device, struct rt_spi_message *msg)
{
    struct hpm_spi *spi = (struct hpm_spi *) (device->bus->parent.user_data);
    hpm_stat_t spi_stat = status_success;
    uint32_t remaining_size = msg->length;
    uint32_t transfer_len;
    uint8_t *raw_alloc_tx_buf = RT_NULL;
    uint8_t *raw_alloc_rx_buf = RT_NULL;
    uint8_t *aligned_tx_buf = RT_NULL;
    uint8_t *aligned_rx_buf = RT_NULL;
    uint32_t aligned_len = 0;
    if (msg->length <= 0)
    {
        return status_invalid_argument;
    }
    aligned_len = (msg->length + HPM_L1C_CACHELINE_SIZE - 1U) & ~(HPM_L1C_CACHELINE_SIZE - 1U);
    if (msg->send_buf != RT_NULL)
    {
        if (l1c_dc_is_enabled())
        {
            /* The allocated pointer is always RT_ALIGN_SIZE aligned */
                raw_alloc_tx_buf = (uint8_t*)rt_malloc(aligned_len + HPM_L1C_CACHELINE_SIZE - RT_ALIGN_SIZE);
                RT_ASSERT(raw_alloc_tx_buf != RT_NULL);
                aligned_tx_buf = (uint8_t*)HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)raw_alloc_tx_buf);
                rt_memcpy(aligned_tx_buf, msg->send_buf, msg->length);
                l1c_dc_flush((uint32_t) aligned_tx_buf, aligned_len);

        }
        else
        {
            aligned_tx_buf = (uint8_t*) msg->send_buf;
        }
    }
    if (msg->recv_buf != RT_NULL)
    {
        if (l1c_dc_is_enabled())
        {
            /* The allocated pointer is always RT_ALIGN_SIZE aligned */
            raw_alloc_rx_buf = (uint8_t*)rt_malloc(aligned_len + HPM_L1C_CACHELINE_SIZE - RT_ALIGN_SIZE);
            RT_ASSERT(raw_alloc_rx_buf != RT_NULL);
            aligned_rx_buf = (uint8_t*)HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)raw_alloc_rx_buf);
        }
        else
        {
            aligned_rx_buf = msg->recv_buf;
        }
    }

    uint8_t *tx_buf = aligned_tx_buf;
    uint8_t *rx_buf = aligned_rx_buf;

    uint32_t core_id = read_csr(CSR_MHARTID);
    spi->spi_base->CTRL &= ~(SPI_CTRL_TXDMAEN_MASK | SPI_CTRL_RXDMAEN_MASK);
    spi->control_config.common_config.tx_dma_enable = false;
    spi->control_config.common_config.rx_dma_enable = false;
    spi_disable_interrupt(spi->spi_base, spi_end_int);
    while (remaining_size > 0)
    {
        transfer_len = MIN(SPI_SOC_TRANSFER_COUNT_MAX, remaining_size);
        if (msg->send_buf != NULL && msg->recv_buf != NULL)
        {
            spi_enable_interrupt(spi->spi_base, spi_end_int);
            spi->control_config.common_config.tx_dma_enable = true;
            spi->control_config.common_config.rx_dma_enable = true;
            spi->control_config.common_config.trans_mode = spi_trans_write_read_together;
            spi_stat = spi_setup_dma_transfer(spi->spi_base, &spi->control_config, NULL, NULL, transfer_len,
                transfer_len);
            if (spi_stat != status_success)
            {
                break;
            }
            dmamux_config(HPM_DMAMUX, spi->tx_dma.channel, spi->tx_dmamux, true);
            spi_stat = spi_tx_trigger_dma(spi->tx_dma.base, spi->tx_dma.channel, spi->spi_base,
                    core_local_mem_to_sys_address(core_id, (uint32_t) tx_buf),
                    DMA_TRANSFER_WIDTH_BYTE, transfer_len);

            /* setup spi rx trigger dma transfer*/
            dmamux_config(HPM_DMAMUX, spi->rx_dma.channel, spi->rx_dmamux, true);
            spi_stat = spi_rx_trigger_dma(spi->rx_dma.base, spi->rx_dma.channel, spi->spi_base,
                    core_local_mem_to_sys_address(core_id, (uint32_t) rx_buf),
                    DMA_TRANSFER_WIDTH_BYTE, transfer_len);
            if (spi_stat != status_success)
            {
                break;
            }
            dma_mgr_enable_chn_irq(&spi->tx_dma, DMA_MGR_INTERRUPT_MASK_TC);
            dma_mgr_enable_chn_irq(&spi->rx_dma, DMA_MGR_INTERRUPT_MASK_TC);
            rt_sem_take(spi->spi_xfer_done_sem, RT_WAITING_FOREVER);
            rt_sem_take(spi->txdma_xfer_done_sem, RT_WAITING_FOREVER);
            rt_sem_take(spi->rxdma_xfer_done_sem, RT_WAITING_FOREVER);
        }
        else if (msg->send_buf != NULL)
        {
            spi_enable_interrupt(spi->spi_base, spi_end_int);
            spi->control_config.common_config.tx_dma_enable = true;
            spi->control_config.common_config.trans_mode = spi_trans_write_only;
            spi_stat = spi_setup_dma_transfer(spi->spi_base, &spi->control_config, NULL, NULL, transfer_len, 0);
            if (spi_stat != status_success)
            {
                break;
            }
            dmamux_config(HPM_DMAMUX, spi->tx_dma.channel, spi->tx_dmamux, true);
            spi_stat = spi_tx_trigger_dma(spi->tx_dma.base, spi->tx_dma.channel, spi->spi_base,
                    core_local_mem_to_sys_address(core_id, (uint32_t) tx_buf),
                    DMA_TRANSFER_WIDTH_BYTE, transfer_len);
            if (spi_stat != status_success)
            {
                break;
            }
            dma_mgr_enable_chn_irq(&spi->tx_dma, DMA_MGR_INTERRUPT_MASK_TC);
            rt_sem_take(spi->spi_xfer_done_sem, RT_WAITING_FOREVER);
            rt_sem_take(spi->txdma_xfer_done_sem, RT_WAITING_FOREVER);
        }
        else
        {
            spi->control_config.common_config.rx_dma_enable = true;
            spi->control_config.common_config.trans_mode = spi_trans_read_only;
            spi_stat = spi_setup_dma_transfer(spi->spi_base, &spi->control_config, NULL, NULL, 0, transfer_len);
            if (spi_stat != status_success)
            {
                break;
            }
            /* setup spi rx trigger dma transfer*/
            dmamux_config(HPM_DMAMUX, spi->rx_dma.channel, spi->rx_dmamux, true);
            spi_stat = spi_rx_trigger_dma(spi->rx_dma.base, spi->rx_dma.channel, spi->spi_base,
                    core_local_mem_to_sys_address(core_id, (uint32_t) rx_buf),
                    DMA_TRANSFER_WIDTH_BYTE, transfer_len);
            if (spi_stat != status_success)
            {
                break;
            }
            spi_enable_interrupt(spi->spi_base, spi_end_int);
            dma_mgr_enable_chn_irq(&spi->rx_dma, DMA_MGR_INTERRUPT_MASK_TC);
            rt_sem_take(spi->spi_xfer_done_sem, RT_WAITING_FOREVER);
            rt_sem_take(spi->rxdma_xfer_done_sem, RT_WAITING_FOREVER);
        }
        if (tx_buf != NULL)
        {
            tx_buf += transfer_len;
        }
        if (rx_buf != NULL)
        {
            rx_buf += transfer_len;
        }
        remaining_size -= transfer_len;
        spi->spi_base->CTRL &= ~(SPI_CTRL_TXDMAEN_MASK | SPI_CTRL_RXDMAEN_MASK);
    }

    if (l1c_dc_is_enabled() && (msg->length > 0))
    {
        /* cache invalidate for receive buff */
        if (aligned_tx_buf != RT_NULL)
        {
            rt_free(raw_alloc_tx_buf);
            raw_alloc_tx_buf = RT_NULL;
            aligned_tx_buf = RT_NULL;
        }

        if (aligned_rx_buf != RT_NULL)
        {
            l1c_dc_invalidate((uint32_t) aligned_rx_buf, aligned_len);
            rt_memcpy(msg->recv_buf, aligned_rx_buf, msg->length);
            rt_free(raw_alloc_rx_buf);
            raw_alloc_rx_buf = RT_NULL;
            aligned_rx_buf = RT_NULL;
        }
    }

    return spi_stat;
}


static rt_ssize_t hpm_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *msg)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(msg != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);

    cs_ctrl_callback_t cs_pin_control = (cs_ctrl_callback_t) device->parent.user_data;

    struct hpm_spi *spi = (struct hpm_spi *) (device->bus->parent.user_data);

    hpm_stat_t spi_stat = status_success;

    if ((cs_pin_control != NULL) && msg->cs_take)
    {
        cs_pin_control(SPI_CS_TAKE);
    }

    if (spi->enable_dma)
    {
        spi_stat = hpm_spi_xfer_dma(device,  msg);
    }
    else
    {
        spi_stat = hpm_spi_xfer_polling(device,  msg);
    }

    if (spi_stat != status_success)
    {
        msg->length = 0;
    }

    if ((cs_pin_control != NULL) && msg->cs_release)
    {
        cs_pin_control(SPI_CS_RELEASE);
    }

    return msg->length;
}


rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, cs_ctrl_callback_t callback)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *) rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void*)callback);
    RT_ASSERT(result == RT_EOK);

    return result;
}


int rt_hw_spi_init(void)
{

    rt_err_t ret = RT_EOK;
    hpm_stat_t stat;

    for (uint32_t i = 0; i < sizeof(hpm_spis) / sizeof(hpm_spis[0]); i++)
    {
        struct hpm_spi *spi = &hpm_spis[i];

        spi->spi_bus.parent.user_data = spi;
        if (spi->enable_dma)
        {
            stat = dma_mgr_request_resource(&spi->tx_dma);
            dma_mgr_install_chn_tc_callback(&spi->tx_dma, spi_dma_channel_tc_callback, (void *)&hpm_spis[i]);
            if (stat != status_success)
            {
                return -RT_ERROR;
            }

            stat = dma_mgr_request_resource(&spi->rx_dma);
            dma_mgr_install_chn_tc_callback(&spi->rx_dma, spi_dma_channel_tc_callback, (void *)&hpm_spis[i]);
            if (stat != status_success)
            {
                return -RT_ERROR;
            }
            intc_m_enable_irq_with_priority(hpm_spis[i].spi_irq, 2);
            dma_mgr_enable_dma_irq_with_priority(&spi->tx_dma, 1);
            dma_mgr_enable_dma_irq_with_priority(&spi->rx_dma, 1);
        }

        ret = rt_spi_bus_register(&spi->spi_bus, spi->bus_name, &hpm_spi_ops);
        if (ret != RT_EOK)
        {
            break;
        }

        char sem_name[RT_NAME_MAX];
        rt_sprintf(sem_name, "%s_s", hpm_spis[i].bus_name);
        hpm_spis[i].xfer_sem = rt_sem_create(sem_name, 0, RT_IPC_FLAG_PRIO);
        if (hpm_spis[i].xfer_sem == RT_NULL)
        {
            ret = RT_ENOMEM;
            break;
        }

        rt_sprintf(sem_name, "%s_ds", hpm_spis[i].bus_name);
        hpm_spis[i].spi_xfer_done_sem = rt_sem_create(sem_name, 0, RT_IPC_FLAG_PRIO);
        if (hpm_spis[i].spi_xfer_done_sem == RT_NULL)
        {
            ret = RT_ENOMEM;
            break;
        }

        rt_sprintf(sem_name, "%s_rds", hpm_spis[i].bus_name);
        hpm_spis[i].rxdma_xfer_done_sem = rt_sem_create(sem_name, 0, RT_IPC_FLAG_PRIO);
        if (hpm_spis[i].rxdma_xfer_done_sem == RT_NULL)
        {
            ret = RT_ENOMEM;
            break;
        }

        rt_sprintf(sem_name, "%s_tds", hpm_spis[i].bus_name);
        hpm_spis[i].txdma_xfer_done_sem = rt_sem_create(sem_name, 0, RT_IPC_FLAG_PRIO);
        if (hpm_spis[i].txdma_xfer_done_sem == RT_NULL)
        {
            ret = RT_ENOMEM;
            break;
        }
    }

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /*BSP_USING_SPI*/
