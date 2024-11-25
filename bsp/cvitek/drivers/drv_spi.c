/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-28     qiujingbao   first version
 * 2024/06/08     flyingcys    fix transmission failure
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_spi.h"

#include "drv_pinmux.h"
#include "drv_ioremap.h"

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "drv.spi"

struct _device_spi
{
    struct rt_spi_bus spi_bus;
    struct dw_spi dws;
    char *device_name;
};

static struct _device_spi _spi_obj[] =
{
#ifdef BSP_USING_SPI0
    {
        .dws.regs = (void *)DW_SPI0_BASE,
        .dws.irq = DW_SPI0_IRQn,
        .dws.index = 0,
        .device_name = "spi0",
    },
#endif /* BSP_USING_SPI0 */
#ifdef BSP_USING_SPI1
    {
        .dws.regs = (void *)DW_SPI1_BASE,
        .dws.irq = DW_SPI1_IRQn,
        .dws.index = 0,
        .device_name = "spi1",
    },
#endif /* BSP_USING_SPI1 */
#ifdef BSP_USING_SPI2
    {
        .dws.regs = (void *)DW_SPI2_BASE,
        .dws.irq = DW_SPI2_IRQn,
        .dws.index = 0,
        .device_name = "spi2",
    },
#endif /* BSP_USING_SPI2 */
#ifdef BSP_USING_SPI3
    {
        .dws.regs = (void *)DW_SPI3_BASE,
        .dws.irq = DW_SPI3_IRQn,
        .dws.index = 0,
        .device_name = "spi3",
    },
#endif /* BSP_USING_SPI3 */
};

static rt_err_t spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    rt_err_t ret = RT_EOK;
    struct _device_spi *spi = (struct _device_spi *)device->bus->parent.user_data;
    struct dw_spi *dws = &spi->dws;

    rt_uint8_t mode;

    LOG_D("spi_configure input");

    /* set cs low when spi idle */
    writel(0, (void *)0x030001d0);

    if (cfg->mode & RT_SPI_SLAVE)
    {
        LOG_E("invalid mode: %d", cfg->mode);
        return -RT_EINVAL;
    }

    spi_reset_chip(dws);
    spi_hw_init(dws);
    spi_enable_chip(dws, 0);

    LOG_D("cfg->max_hz: %d", cfg->max_hz);
    dw_spi_set_clock(dws, SPI_REF_CLK, cfg->max_hz);

    LOG_D("cfg->data_width: %d", cfg->data_width);
    if (dw_spi_set_data_frame_len(dws, (uint32_t)cfg->data_width) < 0)
    {
        LOG_E("dw_spi_set_data_frame_len failed...\n");
        return -RT_ERROR;
    }

    LOG_D("cfg->mode: %08x", cfg->mode);
    switch (cfg->mode & RT_SPI_MODE_3)
    {
        case RT_SPI_MODE_0:
            mode = SPI_FORMAT_CPOL0_CPHA0;
            break;

        case RT_SPI_MODE_1:
            mode = SPI_FORMAT_CPOL0_CPHA1;
            break;

        case RT_SPI_MODE_2:
            mode = SPI_FORMAT_CPOL1_CPHA0;
            break;

        case RT_SPI_MODE_3:
            mode = SPI_FORMAT_CPOL1_CPHA1;
            break;

        default:
            LOG_E("spi configure mode error %x\n", cfg->mode);
            break;
    }

    dw_spi_set_polarity_and_phase(dws, mode);

    dw_spi_set_cs(dws, 1, 0);

    spi_enable_chip(dws, 1);

    return RT_EOK;
}

static rt_err_t dw_spi_transfer_one(struct dw_spi *dws, const void *tx_buf, void *rx_buf, uint32_t len, enum transfer_type  tran_type)
{
    uint8_t imask = 0;
    uint16_t txlevel = 0;

    dws->tx = NULL;
    dws->tx_end = NULL;
    dws->rx = NULL;
    dws->rx_end = NULL;

    if (tx_buf != NULL) {
        dws->tx = tx_buf;
        dws->tx_end = dws->tx + len;
    }

    if (rx_buf != NULL) {
        dws->rx = rx_buf;
        dws->rx_end = dws->rx + len;
    }

    dws->rx_len = len / dws->n_bytes;
    dws->tx_len = len / dws->n_bytes;

    spi_enable_chip(dws, 0);

    /* For poll mode just disable all interrupts */
    spi_mask_intr(dws, 0xff);

    /* set tran mode */
    set_tran_mode(dws);

    /* cs0 */
    dw_spi_set_cs(dws, true, 0);

    /* enable spi */
    spi_enable_chip(dws, 1);

    rt_hw_us_delay(10);

    if (tran_type == POLL_TRAN)
    {
        if (poll_transfer(dws) < 0)
            return -RT_ERROR;
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_ssize_t spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    struct _device_spi *spi = (struct _device_spi *)device->bus->parent.user_data;
    struct dw_spi *dws = &spi->dws;
    int32_t ret = 0;

    if (message->send_buf && message->recv_buf)
    {
        ret = dw_spi_transfer_one(dws, message->send_buf, message->recv_buf, message->length, POLL_TRAN);

    }
    else if (message->send_buf)
    {
        ret = dw_spi_transfer_one(dws, message->send_buf, RT_NULL, message->length, POLL_TRAN);

    }
    else if (message->recv_buf)
    {
        ret = dw_spi_transfer_one(dws, RT_NULL, message->recv_buf, message->length, POLL_TRAN);

    }

    return message->length;
}

static const struct rt_spi_ops _spi_ops =
{
    .configure = spi_configure,
    .xfer = spi_xfer,
};

#if defined(BOARD_TYPE_MILKV_DUO) || defined(BOARD_TYPE_MILKV_DUO_SPINOR) || defined(BOARD_TYPE_MILKV_DUO256M) || defined(BOARD_TYPE_MILKV_DUO256M_SPINOR)
// For Duo / Duo 256m, only SPI2 are exported on board.
#ifdef BSP_USING_SPI0
static const char *pinname_whitelist_spi0_sck[] = {
    NULL,
};
static const char *pinname_whitelist_spi0_sdo[] = {
    NULL,
};
static const char *pinname_whitelist_spi0_sdi[] = {
    NULL,
};
static const char *pinname_whitelist_spi0_cs[] = {
    NULL,
};
#endif

#ifdef BSP_USING_SPI1
static const char *pinname_whitelist_spi1_sck[] = {
    NULL,
};
static const char *pinname_whitelist_spi1_sdo[] = {
    NULL,
};
static const char *pinname_whitelist_spi1_sdi[] = {
    NULL,
};
static const char *pinname_whitelist_spi1_cs[] = {
    NULL,
};
#endif

#ifdef BSP_USING_SPI2
static const char *pinname_whitelist_spi2_sck[] = {
    "SD1_CLK",
    NULL,
};
static const char *pinname_whitelist_spi2_sdo[] = {
    "SD1_CMD",
    NULL,
};
static const char *pinname_whitelist_spi2_sdi[] = {
    "SD1_D0",
    NULL,
};
static const char *pinname_whitelist_spi2_cs[] = {
    "SD1_D3",
    NULL,
};
#endif

#ifdef BSP_USING_SPI3
static const char *pinname_whitelist_spi3_sck[] = {
    NULL,
};
static const char *pinname_whitelist_spi3_sdo[] = {
    NULL,
};
static const char *pinname_whitelist_spi3_sdi[] = {
    NULL,
};
static const char *pinname_whitelist_spi3_cs[] = {
    NULL,
};
#endif

#else
    #error "Unsupported board type!"
#endif

static void rt_hw_spi_pinmux_config()
{
#ifdef BSP_USING_SPI0
    pinmux_config(BSP_SPI0_SCK_PINNAME, SPI0_SCK, pinname_whitelist_spi0_sck);
    pinmux_config(BSP_SPI0_SDO_PINNAME, SPI0_SDO, pinname_whitelist_spi0_sdo);
    pinmux_config(BSP_SPI0_SDI_PINNAME, SPI0_SDI, pinname_whitelist_spi0_sdi);
    pinmux_config(BSP_SPI0_CS_PINNAME, SPI0_CS_X, pinname_whitelist_spi0_cs);
#endif /* BSP_USING_SPI0 */

#ifdef BSP_USING_SPI1
    pinmux_config(BSP_SPI1_SCK_PINNAME, SPI1_SCK, pinname_whitelist_spi1_sck);
    pinmux_config(BSP_SPI1_SDO_PINNAME, SPI1_SDO, pinname_whitelist_spi1_sdo);
    pinmux_config(BSP_SPI1_SDI_PINNAME, SPI1_SDI, pinname_whitelist_spi1_sdi);
    pinmux_config(BSP_SPI1_CS_PINNAME, SPI1_CS_X, pinname_whitelist_spi1_cs);
#endif /* BSP_USING_SPI1 */

#ifdef BSP_USING_SPI2
    pinmux_config(BSP_SPI2_SCK_PINNAME, SPI2_SCK, pinname_whitelist_spi2_sck);
    pinmux_config(BSP_SPI2_SDO_PINNAME, SPI2_SDO, pinname_whitelist_spi2_sdo);
    pinmux_config(BSP_SPI2_SDI_PINNAME, SPI2_SDI, pinname_whitelist_spi2_sdi);
    pinmux_config(BSP_SPI2_CS_PINNAME, SPI2_CS_X, pinname_whitelist_spi2_cs);
#endif /* BSP_USING_SPI2 */

#ifdef BSP_USING_SPI3
    pinmux_config(BSP_SPI3_SCK_PINNAME, SPI3_SCK, pinname_whitelist_spi3_sck);
    pinmux_config(BSP_SPI3_SDO_PINNAME, SPI3_SDO, pinname_whitelist_spi3_sdo);
    pinmux_config(BSP_SPI3_SDI_PINNAME, SPI3_SDI, pinname_whitelist_spi3_sdi);
    pinmux_config(BSP_SPI3_CS_PINNAME, SPI3_CS_X, pinname_whitelist_spi3_cs);
#endif /* BSP_USING_SPI3 */
}

int rt_hw_spi_init(void)
{
    rt_err_t ret = RT_EOK;
    struct dw_spi *dws;

    rt_hw_spi_pinmux_config();

    for (rt_size_t i = 0; i < sizeof(_spi_obj) / sizeof(struct _device_spi); i++)
    {
        _spi_obj[i].base_addr = (rt_ubase_t)DRV_IOREMAP((void *)_spi_obj[i].base_addr, 0x1000);

        _spi_obj[i].spi_bus.parent.user_data = (void *)&_spi_obj[i];
        ret = rt_spi_bus_register(&_spi_obj[i].spi_bus, _spi_obj[i].device_name, &_spi_ops);
    }

    RT_ASSERT(ret == RT_EOK);

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);
