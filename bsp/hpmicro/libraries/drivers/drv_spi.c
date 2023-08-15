/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-02-01   HPMicro     First version
 * 2023-02-15   HPMicro     Add DMA support
 * 2023-07-14   HPMicro     Manage the DMA buffer alignment in driver
 */
#include <rtthread.h>

#ifdef BSP_USING_SPI
#include <rtdevice.h>
#include "board.h"
#include "drv_spi.h"
#include "hpm_spi_drv.h"
#include "hpm_sysctl_drv.h"
#include "hpm_dma_manager.h"
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
    hpm_dma_resource_t tx_dma;
    hpm_dma_resource_t rx_dma;
};

static rt_err_t hpm_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg);
static rt_ssize_t hpm_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *msg);

static struct hpm_spi hpm_spis[] =
{
#if defined(BSP_USING_SPI0)
    {
        .bus_name = "spi0",
        .spi_base = HPM_SPI0,
        .enable_dma = RT_TRUE,
        .tx_dmamux = HPM_DMA_SRC_SPI0_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI0_RX,
    },
#endif
#if defined(BSP_USING_SPI1)
    {
        .bus_name = "spi1",
        .spi_base = HPM_SPI1,
        .enable_dma = RT_TRUE,
        .tx_dmamux = HPM_DMA_SRC_SPI1_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI1_RX,
    },
#endif
#if defined(BSP_USING_SPI2)
    {
        .bus_name = "spi2",
        .spi_base = HPM_SPI2,
        .enable_dma = RT_TRUE,
        .tx_dmamux = HPM_DMA_SRC_SPI2_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI2_RX,
    },
#endif
#if defined(BSP_USING_SPI3)
    {
        .bus_name = "spi3",
        .spi_base = HPM_SPI3,
        .enable_dma = RT_TRUE,
        .tx_dmamux = HPM_DMA_SRC_SPI3_TX,
        .rx_dmamux = HPM_DMA_SRC_SPI3_RX,
    },
#endif
};

static struct rt_spi_ops hpm_spi_ops =
{
    .configure = hpm_spi_configure,
    .xfer = hpm_spi_xfer,
};

static rt_err_t hpm_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    spi_timing_config_t timing_config = { 0 };
    spi_format_config_t format_config = { 0 };

    struct hpm_spi *spi = RT_NULL;

    spi = (struct hpm_spi *) (device->bus->parent.user_data);
    RT_ASSERT(spi != RT_NULL);

    if (cfg->data_width != 8 && cfg->data_width != 16 && cfg->data_width != 32)
    {
        return RT_EINVAL;
    }

    spi_master_get_default_timing_config(&timing_config);
    spi_master_get_default_format_config(&format_config);

    init_spi_pins(spi->spi_base);

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
        transfer_len = MIN(512, remaining_size);
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


static hpm_stat_t hpm_spi_wait_idle(SPI_Type *ptr)
{
    hpm_stat_t status = status_success;
    rt_tick_t start_tick = rt_tick_get();
    while(ptr->STATUS & SPI_STATUS_SPIACTIVE_MASK)
    {
        if ((rt_tick_get() - start_tick) > RT_TICK_PER_SECOND)
        {
            status = status_timeout;
            break;
        }
    }
    return status;
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
    if (msg->length > 0)
    {
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
    }
    uint8_t *tx_buf = aligned_tx_buf;
    uint8_t *rx_buf = aligned_rx_buf;

    uint32_t core_id = read_csr(CSR_MHARTID);
    spi->spi_base->CTRL &= ~(SPI_CTRL_TXDMAEN_MASK | SPI_CTRL_RXDMAEN_MASK);
    while (remaining_size > 0)
    {
        transfer_len = MIN(512, remaining_size);
        spi->control_config.common_config.tx_dma_enable = false;
        spi->control_config.common_config.rx_dma_enable = false;
        if (msg->send_buf != NULL && msg->recv_buf != NULL)
        {
            spi->control_config.common_config.trans_mode = spi_trans_write_read_together;
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
        }
        else if (msg->send_buf != NULL)
        {
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
        }
        spi_stat = hpm_spi_wait_idle(spi->spi_base);
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
            stat = dma_manager_request_resource(&spi->tx_dma);
            if (stat != status_success)
            {
                return -RT_ERROR;
            }

            stat = dma_manager_request_resource(&spi->rx_dma);
            if (stat != status_success)
            {
                return -RT_ERROR;
            }
        }

        ret = rt_spi_bus_register(&spi->spi_bus, spi->bus_name, &hpm_spi_ops);
        if (ret != RT_EOK)
        {
            break;
        }

        char sem_name[RT_NAME_MAX];
        rt_sprintf(sem_name, "%s_s", hpm_spis[i].bus_name);
        hpm_spis[i].xfer_sem = rt_sem_create(sem_name, 0, RT_IPC_FLAG_PRIO);
    }

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /*BSP_USING_SPI*/
