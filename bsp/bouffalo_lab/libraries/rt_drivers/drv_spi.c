/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author          Notes
 * 2023-05-01       flyingcys       first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_spi.h"

#ifdef BSP_USING_SPI

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "drv.spi"

#define DMA_MAX_BUFSIZE             4095

#if defined(BSP_USING_BL808)
#define NOCACHE_BUFSTART            0x22026000
#define NOCACHE_BUFSIZE             (40 * 1024)
#elif defined (BSP_USING_BL61X)
#define NOCACHE_BUFSTART            0x22FC6000
#define NOCACHE_BUFSIZE             (104 * 1024)
#endif

struct bl_device_spi
{
    struct rt_spi_bus spi_bus;
    struct bflb_device_s *spi;

#if defined(BSP_SPI_TX_USING_DMA)
    struct bflb_device_s *dma_tx;
    rt_uint32_t dma_dst_req;
    rt_sem_t sem_tx;
#endif

#if defined(BSP_SPI_RX_USING_DMA)
    struct bflb_device_s *dma_rx;
    rt_uint32_t dma_src_req;
    rt_sem_t sem_rx;
#endif
};

#if defined(BSP_SPI_TX_USING_DMA) && defined(BSP_SPI_TX_DMA_NOCACHE_BUFSIZE)
static ATTR_NOCACHE_NOINIT_RAM_SECTION rt_uint8_t dma_tx_buf[BSP_SPI_TX_DMA_NOCACHE_BUFSIZE];
#endif

#if defined(BSP_SPI_RX_USING_DMA) && defined(BSP_SPI_RX_DMA_NOCACHE_BUFSIZE)
static ATTR_NOCACHE_NOINIT_RAM_SECTION rt_uint8_t dma_rx_buf[BSP_SPI_RX_DMA_NOCACHE_BUFSIZE];
#endif

#if defined(BSP_SPI_TX_USING_DMA)
static void spi_bl_spi_dma_tx_isr(void *arg)
{
    struct bl_device_spi *bl_spi = (struct bl_device_spi *)arg;
    LOG_D("spi dma tx done ");

    rt_sem_release(bl_spi->sem_tx);
}
#endif

#if defined(BSP_SPI_RX_USING_DMA)
void spi_dma_rx_isr(void *arg)
{
    struct bl_device_spi *bl_spi = (struct bl_device_spi *)arg;
    LOG_D("spi dma rx done");

    rt_sem_release(bl_spi->sem_rx);
}
#endif

static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *cfg)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    struct bflb_spi_config_s spi_cfg = {
        .freq = 1 * 1000 * 1000,
        .role = SPI_ROLE_MASTER,
        .mode = SPI_MODE3,
        .data_width = SPI_DATA_WIDTH_8BIT,
        .bit_order = SPI_BIT_MSB,
        .byte_order = SPI_BYTE_LSB,
        .tx_fifo_threshold = 0,
        .rx_fifo_threshold = 0,
    };

    switch (cfg->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:             /* RT_SPI_CPOL:0 , RT_SPI_CPHA:0 */
        spi_cfg.mode = SPI_MODE0;
        break;
    case RT_SPI_MODE_1:             /* RT_SPI_CPOL:0 , RT_SPI_CPHA:1 */
        spi_cfg.mode = SPI_MODE1;
        break;
    case RT_SPI_MODE_2:             /* RT_SPI_CPOL:1 , RT_SPI_CPHA:0 */
        spi_cfg.mode = SPI_MODE2;
        break;
    case RT_SPI_MODE_3:             /* RT_SPI_CPOL:1 , RT_SPI_CPHA:1 */
        spi_cfg.mode = SPI_MODE3;
        break;
    default:
        LOG_E("spi_configure mode error %x\n", cfg->mode);
        return -RT_EINVAL;
    }

    switch (cfg->data_width)
    {
    case 8:
        spi_cfg.data_width = SPI_DATA_WIDTH_8BIT;
        break;
    case 16:
        spi_cfg.data_width = SPI_DATA_WIDTH_16BIT;
        break;
    case 24:
        spi_cfg.data_width = SPI_DATA_WIDTH_24BIT;
        break;
    case 32:
        spi_cfg.data_width = SPI_DATA_WIDTH_32BIT;
        break;
    default:
        LOG_E("spi_configure data_width error %x\n", cfg->data_width);
        return RT_ERROR;
    }

    spi_cfg.freq = cfg->max_hz;

    if (cfg->mode & RT_SPI_MSB)
        spi_cfg.bit_order = SPI_BIT_MSB;
    else
        spi_cfg.bit_order = SPI_BIT_LSB;

    if (cfg->mode & RT_SPI_SLAVE)
        spi_cfg.role = SPI_ROLE_SLAVE;
    else
        spi_cfg.role = SPI_ROLE_MASTER;

    struct bl_device_spi *bl_spi;
    bl_spi = (struct bl_device_spi *)device->bus->parent.user_data;

    bflb_spi_init(bl_spi->spi, &spi_cfg);

#if defined(BSP_SPI_TX_USING_DMA)
    bl_spi->sem_tx = rt_sem_create("dam_tx", 0, RT_IPC_FLAG_PRIO);
    if (bl_spi->sem_tx == RT_NULL)
    {
        LOG_E("rt_sem_create dma_tx error");
        return -RT_ENOMEM;
    }

    rt_uint8_t tx_data_width = DMA_DATA_WIDTH_8BIT;
    if (spi_cfg.data_width == SPI_DATA_WIDTH_8BIT)
        tx_data_width = DMA_DATA_WIDTH_8BIT;
    else if (spi_cfg.data_width == SPI_DATA_WIDTH_16BIT)
        tx_data_width = DMA_DATA_WIDTH_16BIT;
    else if (spi_cfg.data_width == SPI_DATA_WIDTH_32BIT)
        tx_data_width = DMA_DATA_WIDTH_32BIT;
    else
    {
        LOG_E("spi dma not support 24bit...");
        return -RT_EINVAL;
    }

    struct bflb_dma_channel_config_s tx_config = {
        .direction = DMA_MEMORY_TO_PERIPH,
        .src_req = DMA_REQUEST_NONE,
        .dst_req = bl_spi->dma_dst_req,
        .src_addr_inc = DMA_ADDR_INCREMENT_ENABLE,
        .dst_addr_inc = DMA_ADDR_INCREMENT_DISABLE,
        .src_burst_count = DMA_BURST_INCR1,
        .dst_burst_count = DMA_BURST_INCR1,
        .src_width = tx_data_width,
        .dst_width = tx_data_width,
    };

    bflb_spi_link_txdma(bl_spi->spi, true);
    bflb_dma_channel_init(bl_spi->dma_tx, &tx_config);
    bflb_dma_channel_irq_attach(bl_spi->dma_tx, spi_bl_spi_dma_tx_isr, (void *)bl_spi);
#endif

#if defined(BSP_SPI_RX_USING_DMA)
    bl_spi->sem_rx = rt_sem_create("dam_rx", 0, RT_IPC_FLAG_PRIO);
    if (bl_spi->sem_rx == RT_NULL)
    {
        LOG_E("rt_sem_create dma_rx error");
        return -RT_ENOMEM;
    }

    rt_uint8_t rx_data_width = DMA_DATA_WIDTH_8BIT;
    if (spi_cfg.data_width == SPI_DATA_WIDTH_8BIT)
        rx_data_width = DMA_DATA_WIDTH_8BIT;
    else if (spi_cfg.data_width == SPI_DATA_WIDTH_16BIT)
        rx_data_width = DMA_DATA_WIDTH_16BIT;
    else if (spi_cfg.data_width == SPI_DATA_WIDTH_32BIT)
        rx_data_width = DMA_DATA_WIDTH_32BIT;
    else
    {
        LOG_E("spi dma not support 24bit...");
        return -RT_EINVAL;
    }

    struct bflb_dma_channel_config_s rx_config = {
        .direction = DMA_PERIPH_TO_MEMORY,
        .src_req = bl_spi->dma_src_req,
        .dst_req = DMA_REQUEST_NONE,
        .src_addr_inc = DMA_ADDR_INCREMENT_DISABLE,
        .dst_addr_inc = DMA_ADDR_INCREMENT_ENABLE,
        .src_burst_count = DMA_BURST_INCR1,
        .dst_burst_count = DMA_BURST_INCR1,
        .src_width = rx_data_width,
        .dst_width = rx_data_width,
    };

    bflb_spi_link_rxdma(bl_spi->spi, true);
    bflb_dma_channel_init(bl_spi->dma_rx, &rx_config);
    bflb_dma_channel_irq_attach(bl_spi->dma_rx, spi_dma_rx_isr, (void *)bl_spi);
#endif

    return RT_EOK;
}

#if defined(BSP_SPI_TX_USING_DMA)
static rt_err_t _bl_spi_dma_tx(struct bl_device_spi *bl_spi, rt_uint8_t *src, rt_size_t length)
{
    rt_err_t result;
    struct bflb_dma_channel_lli_pool_s tx_llipool[1];
    struct bflb_dma_channel_lli_transfer_s tx_transfers[1];

    tx_transfers[0].src_addr = (rt_uint32_t)src;
    tx_transfers[0].dst_addr = (rt_uint32_t)DMA_ADDR_SPI0_TDR;
    tx_transfers[0].nbytes = length;

    LOG_D("dma tx start...");
    rt_kprintf("tx length:%d\n", length);
    bflb_dma_channel_lli_reload(bl_spi->dma_tx, tx_llipool, 1, tx_transfers, 1);
    bflb_dma_channel_start(bl_spi->dma_tx);

    result = rt_sem_take(bl_spi->sem_tx, BSP_SPI_TX_DMA_TIMEOUT);
    if (result != RT_EOK)
        LOG_E("sem take dma tx error:%d", result);

    return result;
}

static rt_err_t _spi_dma_xfer_tx(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_err_t result = RT_EOK;
    rt_uint8_t *src = (rt_uint8_t *)message->send_buf;
    rt_size_t length = message->length;
    struct bl_device_spi *bl_spi = (struct bl_device_spi *)device->bus->parent.user_data;

#if defined(NOCACHE_BUFSTART) && defined(NOCACHE_BUFSIZE)
    if ((message->send_buf < NOCACHE_BUFSTART) || (message->send_buf > (NOCACHE_BUFSTART + NOCACHE_BUFSIZE)))
    {
        if (length <= BSP_SPI_TX_DMA_NOCACHE_BUFSIZE)
        {
            memcpy(dma_tx_buf, src, length);
            result = _bl_spi_dma_tx(bl_spi, dma_tx_buf, length);
        }
        else
        {
            while(length > 0)
            {
                if (length >= BSP_SPI_TX_DMA_NOCACHE_BUFSIZE)
                {
                    memcpy(dma_tx_buf, src, BSP_SPI_TX_DMA_NOCACHE_BUFSIZE);
                    result = _bl_spi_dma_tx(bl_spi, dma_tx_buf, BSP_SPI_TX_DMA_NOCACHE_BUFSIZE);
                    if (result != RT_EOK)
                        break;

                    length -= BSP_SPI_TX_DMA_NOCACHE_BUFSIZE;
                    src += BSP_SPI_TX_DMA_NOCACHE_BUFSIZE;
                }
                else
                {
                    memcpy(dma_tx_buf, src, length);
                    result = _bl_spi_dma_tx(bl_spi, dma_tx_buf, length);
                    length = 0;
                }
            }
        }
    }
    else
#endif
    {
        if (length <= DMA_MAX_BUFSIZE)
        {
            result = _bl_spi_dma_tx(bl_spi, src, length);
        }
        else
        {
            while(length > 0)
            {
                if (length >= DMA_MAX_BUFSIZE)
                {
                    result = _bl_spi_dma_tx(bl_spi, src, DMA_MAX_BUFSIZE);
                    if (result != RT_EOK)
                        break;

                    length -= DMA_MAX_BUFSIZE;
                    src += DMA_MAX_BUFSIZE;
                }
                else
                {
                    result = _bl_spi_dma_tx(bl_spi, src, length);
                    length = 0;
                }
            }
        }
    }

    LOG_D("dma tx finish...");

    return result;
}
#endif

#if defined(BSP_SPI_RX_USING_DMA)
static rt_err_t _bl_spi_dma_rx(struct bl_device_spi *bl_spi, rt_uint8_t *dst, rt_size_t length)
{
    rt_err_t result;
    struct bflb_dma_channel_lli_pool_s rx_llipool[1];
    struct bflb_dma_channel_lli_transfer_s rx_transfers[1];

    rx_transfers[0].src_addr = (rt_uint32_t)DMA_ADDR_SPI0_RDR;
    rx_transfers[0].dst_addr = (rt_uint32_t)dst;
    rx_transfers[0].nbytes = length;

    bflb_dma_channel_lli_reload(bl_spi->dma_rx, rx_llipool, 1, rx_transfers, 1);
    bflb_dma_channel_start(bl_spi->dma_rx);

    result = rt_sem_take(bl_spi->sem_rx, BSP_SPI_RX_DMA_TIMEOUT);
    if (result != RT_EOK)
        LOG_E("sem take dma rx error:%d", result);

    return result;
}

static rt_err_t _spi_dma_xfer_rx(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_err_t result = RT_EOK;
    rt_uint8_t *dst = (rt_uint8_t *)message->recv_buf;
    rt_size_t length = message->length;
    struct bl_device_spi *bl_spi = (struct bl_device_spi *)device->bus->parent.user_data;

#if defined(NOCACHE_BUFSTART) && defined(NOCACHE_BUFSIZE)
    if ((message->recv_buf < NOCACHE_BUFSTART) || (message->recv_buf > (NOCACHE_BUFSTART + NOCACHE_BUFSIZE)))
    {
        if (length <= BSP_SPI_RX_DMA_NOCACHE_BUFSIZE)
        {
            result = _bl_spi_dma_rx(bl_spi, dst, length);
            if (result == RT_EOK)
                memcpy(dst, dma_rx_buf, length);
        }
        else
        {
            while(length > 0)
            {
                if (length >= BSP_SPI_RX_DMA_NOCACHE_BUFSIZE)
                {
                    result = _bl_spi_dma_rx(bl_spi, dma_tx_buf, BSP_SPI_RX_DMA_NOCACHE_BUFSIZE);
                    if (result != RT_EOK)
                        break;
                    memcpy(dst, dma_rx_buf, BSP_SPI_RX_DMA_NOCACHE_BUFSIZE);
                    length -= BSP_SPI_RX_DMA_NOCACHE_BUFSIZE;
                    dst += BSP_SPI_RX_DMA_NOCACHE_BUFSIZE;
                }
                else
                {
                    result = _bl_spi_dma_rx(bl_spi, dma_rx_buf, length);
                    if (result != RT_EOK)
                        break;
                    memcpy(dst, dma_rx_buf, length);
                    length = 0;
                }
            }
        }
    }
    else
#endif
    {
        if (length <= DMA_MAX_BUFSIZE)
        {
            result = _bl_spi_dma_rx(bl_spi, dst, length);
            if (result == RT_EOK)
                memcpy(dst, dma_rx_buf, length);
        }
        else
        {
            while(length > 0)
            {
                if (length >= DMA_MAX_BUFSIZE)
                {
                    result = _bl_spi_dma_rx(bl_spi, dst, DMA_MAX_BUFSIZE);
                    if (result != RT_EOK)
                        break;

                    memcpy(dst, dma_rx_buf, DMA_MAX_BUFSIZE);
                    length -= DMA_MAX_BUFSIZE;
                    dst += DMA_MAX_BUFSIZE;
                }
                else
                {
                    result = _bl_spi_dma_rx(bl_spi, dst, length);
                    if (result != RT_EOK)
                        break;
                    memcpy(dst, dma_rx_buf, length);
                    length = 0;
                }
            }
        }
    }

    LOG_D("dma rx finish...");

    return result;
}
#endif

static rt_ssize_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);

    rt_err_t result;
    rt_uint32_t cs_pin = (rt_uint32_t)device->parent.user_data;
    struct bflb_device_s* gpio = bflb_device_get_by_name("gpio");

    struct bl_device_spi *bl_spi;
    bl_spi = (struct bl_device_spi *)device->bus->parent.user_data;

    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            bflb_gpio_set(gpio, cs_pin);
        else
            bflb_gpio_reset(gpio, cs_pin);
    }

    if (message->send_buf && message->recv_buf)
    {
        rt_memset(message->recv_buf, 0x0, message->length);

        bflb_spi_poll_exchange(bl_spi->spi, (void *)message->send_buf, (void *)message->recv_buf, message->length);
        message->length += strlen(message->recv_buf);
    }
    else if (message->send_buf)
    {
#if defined(BSP_SPI_TX_USING_DMA)
        result = _spi_dma_xfer_tx(device, message);
        if(result != RT_EOK)
            message->length = -1;
#else
        bflb_spi_poll_exchange(bl_spi->spi, (void *)message->send_buf, NULL, message->length);
#endif
    }
    else if (message->recv_buf)
    {
        rt_memset(message->recv_buf, 0x0, message->length);

#if defined(BSP_SPI_RX_USING_DMA)
        result = _spi_dma_xfer_rx(device, message);
        if(result != RT_EOK)
            message->length = -1;
#else
        bflb_spi_poll_exchange(bl_spi->spi, NULL, (void *)message->recv_buf, message->length);
#endif
    }
    else
    {
        LOG_E("both send_buf and recv_buf is null!");
        message->length = -1;
    }

    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            bflb_gpio_reset(gpio, cs_pin);
        else
            bflb_gpio_set(gpio, cs_pin);
    }

    return message->length;
}

/* spi bus callback function  */
static const struct rt_spi_ops bl_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t ret;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));

    RT_ASSERT(spi_device != RT_NULL);
    /* initialize the cs pin */
    ret = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);
    if (ret != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d", device_name, bus_name, ret);
        ret = RT_ERROR;
    }

    RT_ASSERT(ret == RT_EOK);
    return ret;
}

int rt_hw_spi_init(void)
{
    rt_err_t ret = RT_ERROR;

    static struct bl_device_spi dev_spi;

    struct bflb_device_s *gpio;
    gpio = bflb_device_get_by_name("gpio");
#ifndef BL808_CORE_D0
    bflb_gpio_init(gpio, SPI_SCK_PIN, GPIO_FUNC_SPI0 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);
    bflb_gpio_init(gpio, SPI_MISO_PIN, GPIO_FUNC_SPI0 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);
    bflb_gpio_init(gpio, SPI_MOSI_PIN, GPIO_FUNC_SPI0 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);

    dev_spi.spi = bflb_device_get_by_name("spi0");

#ifdef BSP_SPI_TX_USING_DMA
    dev_spi.dma_dst_req = DMA_REQUEST_SPI0_TX;
    dev_spi.dma_tx = bflb_device_get_by_name(BSP_SPI_TX_DMA_CHANNEL);
#endif

#ifdef BSP_SPI_RX_USING_DMA
    dev_spi.dma_src_req = DMA_REQUEST_SPI0_RX;
    dev_spi.dma_rx = bflb_device_get_by_name(BSP_SPI_RX_DMA_CHANNEL);
#endif

#endif /* BL808_CORE_D0 */

    dev_spi.spi_bus.parent.user_data = (void *)&dev_spi;

    ret = rt_spi_bus_register(&dev_spi.spi_bus, "spi0", &bl_spi_ops);
    RT_ASSERT(ret == RT_EOK);

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* BSP_USING_SPI */
