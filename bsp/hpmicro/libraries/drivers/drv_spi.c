/*
 * Copyright (c) 2021 hpm
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include <rtthread.h>

#ifdef BSP_USING_SPI
#include <rtdevice.h>
#include "board.h"
#include "drv_spi.h"
#include "hpm_spi_drv.h"
#include "hpm_sysctl_drv.h"

struct hpm_spi
{
    uint32_t instance;
    char *bus_name;
    SPI_Type *spi_base;
    spi_control_config_t control_config;
    struct rt_spi_bus spi_bus;
    rt_sem_t xfer_sem;
    /* TODO: add DMA support later */
};

static rt_err_t hpm_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg);
static rt_uint32_t hpm_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *msg);

static struct hpm_spi hpm_spis[] =
{
#if defined(BSP_USING_SPI0)
    {
        .bus_name = "spi0",
        .spi_base = HPM_SPI0,
    },
#endif
#if defined(BSP_USING_SPI1)
    {
        .bus_name = "spi1",
        .spi_base = HPM_SPI1,
    },
#endif
#if defined(BSP_USING_SPI2)
    {
        .bus_name = "spi2",
        .spi_base = HPM_SPI2,
    },
#endif
#if defined(BSP_USING_SPI3)
    {
        .bus_name = "spi3",
        .spi_base = HPM_SPI3,
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
        return -RT_EINVAL;
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

static rt_uint32_t hpm_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *msg)
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

    uint32_t remaining_size = msg->length;
    uint32_t transfer_len;
    uint8_t *tx_buf = (uint8_t*) msg->send_buf;
    uint8_t *rx_buf = (uint8_t*) msg->recv_buf;
    while (remaining_size > 0)
    {
        transfer_len = MIN(512, remaining_size);
        if (msg->send_buf != NULL && msg->recv_buf != NULL)
        {
            spi->control_config.common_config.trans_mode = spi_trans_write_read_together;
            spi_stat = spi_transfer(spi->spi_base,
                                    &spi->control_config,
                                    NULL,
                                    NULL,
                                    tx_buf, transfer_len,
                                    rx_buf, transfer_len);
        }
        else if (msg->send_buf != NULL)
        {
            spi->control_config.common_config.trans_mode = spi_trans_write_only;
            spi_stat = spi_transfer(spi->spi_base, &spi->control_config,
                                    NULL,
                                    NULL,
                                    (uint8_t*) tx_buf, transfer_len,
                                    NULL, 0);
        }
        else
        {
            spi->control_config.common_config.trans_mode = spi_trans_read_only;
            spi_stat = spi_transfer(spi->spi_base, &spi->control_config,
                                    NULL,
                                    NULL,
                                    NULL, 0,
                                    rx_buf, transfer_len);
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

    for (uint32_t i = 0; i < sizeof(hpm_spis) / sizeof(hpm_spis[0]); i++)
    {
        hpm_spis[i].spi_bus.parent.user_data = &hpm_spis[i];

        ret = rt_spi_bus_register(&hpm_spis[i].spi_bus, hpm_spis[i].bus_name, &hpm_spi_ops);
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

