/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-07     Liu Changjie add WCH CH390 SPI Ethernet driver
 *
 * WCH CH390 SPI Ethernet controller driver.
 */

#include "ch390.h"

#ifdef RT_USING_CH390

#include <netif/ethernetif.h>
#include <lwip/pbuf.h>

#define DBG_TAG "drv.ch390"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define CH390_VENDOR_ID 0x1C00
#define CH390_PID_H_D   0x9151
#define CH390_PID_L_F   0x9150

#define CH390_PKT_MAX            1536
#define CH390_PKT_MIN            64
#define CH390_FCS_SIZE           4
#define CH390_SPI_XFER_SIZE      (CH390_PKT_MAX + 1)
#define CH390_TX_TIMEOUT_MS      100
#define CH390_LINK_POLL_MS       1000
#define CH390_DEFAULT_SPI_MAX_HZ (5 * 1000 * 1000)
#define CH390_DEFAULT_POLL_MS    20
#define CH390_DEFAULT_NETIF_NAME "e0"

#define CH390_NCR    0x00
#define CH390_NSR    0x01
#define CH390_TCR    0x02
#define CH390_RCR    0x05
#define CH390_RSR    0x06
#define CH390_PAR    0x10
#define CH390_MAR    0x16
#define CH390_GPR    0x1F
#define CH390_VIDL   0x28
#define CH390_VIDH   0x29
#define CH390_PIDL   0x2A
#define CH390_PIDH   0x2B
#define CH390_CHIPR  0x2C
#define CH390_TCR2   0x2D
#define CH390_TCSCR  0x31
#define CH390_MPTRCR 0x55
#define CH390_MRCMDX 0x70
#define CH390_MRCMD  0x72
#define CH390_MRRL   0x74
#define CH390_MRRH   0x75
#define CH390_MWCMD  0x78
#define CH390_TXPLL  0x7C
#define CH390_TXPLH  0x7D
#define CH390_ISR    0x7E
#define CH390_IMR    0x7F

#define CH390_NCR_RST      (1U << 0)
#define CH390_NSR_LINKST   (1U << 6)
#define CH390_NSR_WAKEST   (1U << 5)
#define CH390_NSR_TX2END   (1U << 3)
#define CH390_NSR_TX1END   (1U << 2)
#define CH390_TCR_TXREQ    (1U << 0)
#define CH390_RCR_DIS_CRC  (1U << 4)
#define CH390_RCR_ALL      (1U << 3)
#define CH390_RCR_RXEN     (1U << 0)
#define CH390_RSR_FOE      (1U << 0)
#define CH390_RSR_ERR_BITS ((1U << 7) | (1U << 5) | (1U << 4) | \
                            (1U << 3) | (1U << 2) | (1U << 1) | \
                            CH390_RSR_FOE)
#define CH390_GPR_PHY_ON 0x00
#define CH390_ISR_LNKCHG (1U << 5)
#define CH390_ISR_ROO    (1U << 3)
#define CH390_ISR_ROS    (1U << 2)
#define CH390_ISR_PT     (1U << 1)
#define CH390_ISR_PR     (1U << 0)
#define CH390_IMR_PAR    (1U << 7)

#define CH390_PKT_NONE           0x00
#define CH390_PKT_RDY            0x01
#define CH390_PKT_ERR_MASK       0xFE
#define CH390_RX_STATUS_ERR_MASK 0x3F

#define CH390_RX_MEM_END  0x4000
#define CH390_RX_MEM_SIZE 0x3400

#define CH390_SPI_REG_READ  0x00
#define CH390_SPI_REG_WRITE 0x80

struct ch390
{
    struct eth_device parent;
    struct rt_spi_device *spi;
    rt_base_t rst_pin;
    rt_base_t int_pin;
    rt_uint8_t mac[6];
    struct rt_mutex lock;
    rt_uint8_t tx_buf[CH390_SPI_XFER_SIZE];
    rt_uint8_t rx_buf[CH390_SPI_XFER_SIZE];
    rt_thread_t poll_thread;
    rt_uint16_t poll_interval_ms;
    rt_bool_t link_up;
    rt_uint32_t tx_packets;
    rt_uint32_t tx_bytes;
    rt_uint32_t tx_errors;
    rt_uint32_t tx_timeouts;
    rt_uint32_t rx_packets;
    rt_uint32_t rx_bytes;
    rt_uint32_t rx_errors;
    rt_uint32_t rx_dropped;
};

static struct ch390 ch390_dev;
static const rt_uint8_t ch390_default_mac[6] = { 0x02, 0x12, 0x34, 0x56, 0x78, 0x90 };

static rt_err_t ch390_init(rt_device_t dev);
static rt_err_t ch390_open(rt_device_t dev, rt_uint16_t oflag);
static rt_err_t ch390_close(rt_device_t dev);
static rt_ssize_t ch390_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
static rt_ssize_t ch390_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
static rt_err_t ch390_control(rt_device_t dev, int cmd, void *args);

static struct pbuf *ch390_rx(rt_device_t dev);
static rt_err_t ch390_tx(rt_device_t dev, struct pbuf *p);

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops ch390_ops = {
    ch390_init,
    ch390_open,
    ch390_close,
    ch390_read,
    ch390_write,
    ch390_control
};
#endif

static rt_err_t ch390_lock(struct ch390 *ch390)
{
    return rt_mutex_take(&ch390->lock, RT_WAITING_FOREVER);
}

static void ch390_unlock(struct ch390 *ch390)
{
    rt_mutex_release(&ch390->lock);
}

static rt_uint8_t ch390_reg_read(struct ch390 *ch390, rt_uint8_t reg)
{
    rt_uint8_t tx_buf[2];
    rt_uint8_t rx_buf[2];

    tx_buf[0] = CH390_SPI_REG_READ | reg;
    tx_buf[1] = 0xFF;
    rx_buf[0] = 0x00;
    rx_buf[1] = 0x00;

    if (rt_spi_transfer(ch390->spi, tx_buf, rx_buf, sizeof(tx_buf)) != sizeof(tx_buf))
    {
        LOG_E("read reg 0x%02x failed", reg);
        return 0xFF;
    }

    return rx_buf[1];
}

static rt_err_t ch390_reg_write(struct ch390 *ch390, rt_uint8_t reg, rt_uint8_t value)
{
    rt_uint8_t tx_buf[2];

    tx_buf[0] = CH390_SPI_REG_WRITE | reg;
    tx_buf[1] = value;

    if (rt_spi_transfer(ch390->spi, tx_buf, RT_NULL, sizeof(tx_buf)) != sizeof(tx_buf))
    {
        LOG_E("write reg 0x%02x failed", reg);
        return -RT_EIO;
    }

    return RT_EOK;
}

static rt_err_t ch390_mem_read(struct ch390 *ch390, rt_uint8_t reg, void *buffer, rt_size_t size)
{
    if ((buffer == RT_NULL) || (size > CH390_PKT_MAX))
    {
        return -RT_EINVAL;
    }

    ch390->tx_buf[0] = CH390_SPI_REG_READ | reg;
    rt_memset(&ch390->tx_buf[1], 0xFF, size);

    if (rt_spi_transfer(ch390->spi, ch390->tx_buf, ch390->rx_buf, size + 1) != (size + 1))
    {
        LOG_E("read mem 0x%02x failed", reg);
        return -RT_EIO;
    }

    rt_memcpy(buffer, &ch390->rx_buf[1], size);
    return RT_EOK;
}

static rt_err_t ch390_fifo_read(struct ch390 *ch390, rt_size_t size)
{
    if (size > CH390_PKT_MAX)
    {
        return -RT_EINVAL;
    }

    ch390->tx_buf[0] = CH390_SPI_REG_READ | CH390_MRCMD;
    rt_memset(&ch390->tx_buf[1], 0xFF, size);

    if (rt_spi_transfer(ch390->spi, ch390->tx_buf, ch390->rx_buf, size + 1) != (size + 1))
    {
        LOG_E("read rx fifo failed");
        return -RT_EIO;
    }

    rt_memmove(ch390->rx_buf, &ch390->rx_buf[1], size);
    return RT_EOK;
}

static rt_err_t ch390_fifo_write(struct ch390 *ch390, rt_size_t size)
{
    if (size > (CH390_PKT_MAX - CH390_FCS_SIZE))
    {
        return -RT_EINVAL;
    }

    ch390->tx_buf[0] = CH390_SPI_REG_WRITE | CH390_MWCMD;

    if (rt_spi_transfer(ch390->spi, ch390->tx_buf, RT_NULL, size + 1) != (size + 1))
    {
        LOG_E("write tx fifo failed");
        return -RT_EIO;
    }

    return RT_EOK;
}

static rt_err_t ch390_reg_write_array(struct ch390 *ch390, rt_uint8_t reg,
                                      const rt_uint8_t *data, rt_size_t size)
{
    rt_size_t i;

    for (i = 0; i < size; i++)
    {
        rt_err_t ret = ch390_reg_write(ch390, reg + i, data[i]);
        if (ret != RT_EOK)
        {
            return ret;
        }
    }

    return RT_EOK;
}

static rt_err_t ch390_reset(struct ch390 *ch390)
{
    rt_uint8_t ncr;
    int retry;

    if (ch390->rst_pin != PIN_NONE)
    {
        rt_pin_mode(ch390->rst_pin, PIN_MODE_OUTPUT);
        rt_pin_write(ch390->rst_pin, PIN_LOW);
        rt_thread_mdelay(20);
        rt_pin_write(ch390->rst_pin, PIN_HIGH);
        rt_thread_mdelay(50);
    }

    ch390_reg_write(ch390, CH390_NCR, CH390_NCR_RST);

    for (retry = 0; retry < 20; retry++)
    {
        rt_thread_mdelay(5);
        ncr = ch390_reg_read(ch390, CH390_NCR);
        if ((ncr & CH390_NCR_RST) == 0)
        {
            LOG_I("reset done, NCR=0x%02x", ncr);
            return RT_EOK;
        }
    }

    LOG_W("reset timeout, NCR=0x%02x", ch390_reg_read(ch390, CH390_NCR));
    return -RT_ETIMEOUT;
}

static rt_err_t ch390_read_id_or_known_register(struct ch390 *ch390)
{
    rt_uint8_t vidl;
    rt_uint8_t vidh;
    rt_uint8_t pidl;
    rt_uint8_t pidh;
    rt_uint8_t chipr;
    rt_uint16_t vid;
    rt_uint16_t pid;

    vidl = ch390_reg_read(ch390, CH390_VIDL);
    vidh = ch390_reg_read(ch390, CH390_VIDH);
    pidl = ch390_reg_read(ch390, CH390_PIDL);
    pidh = ch390_reg_read(ch390, CH390_PIDH);
    chipr = ch390_reg_read(ch390, CH390_CHIPR);

    vid = ((rt_uint16_t)vidh << 8) | vidl;
    pid = ((rt_uint16_t)pidh << 8) | pidl;

    LOG_I("id VID:PID=0x%04x:0x%04x CHIPR=0x%02x", vid, pid, chipr);

    if ((vid == 0x0000) || (vid == 0xFFFF) || (pid == 0x0000) || (pid == 0xFFFF))
    {
        LOG_E("invalid id readback, check CH390 wiring and SPI mode");
        return -RT_EIO;
    }

    if (vid != CH390_VENDOR_ID)
    {
        LOG_W("unexpected VID 0x%04x, expected 0x%04x", vid, CH390_VENDOR_ID);
    }

    if ((pid != CH390_PID_H_D) && (pid != CH390_PID_L_F))
    {
        LOG_W("unexpected PID 0x%04x, expected 0x%04x or 0x%04x",
              pid, CH390_PID_H_D, CH390_PID_L_F);
    }

    return RT_EOK;
}

static rt_err_t ch390_set_mac(struct ch390 *ch390, const rt_uint8_t mac[6])
{
    rt_err_t ret;

    ret = ch390_reg_write_array(ch390, CH390_PAR, mac, 6);
    if (ret != RT_EOK)
    {
        return ret;
    }

    LOG_I("mac %02x:%02x:%02x:%02x:%02x:%02x",
          mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return RT_EOK;
}

static rt_err_t ch390_wait_tx_idle(struct ch390 *ch390, rt_uint32_t timeout_ms)
{
    rt_uint32_t retry;

    for (retry = 0; retry < timeout_ms; retry++)
    {
        if ((ch390_reg_read(ch390, CH390_TCR) & CH390_TCR_TXREQ) == 0)
        {
            return RT_EOK;
        }
        rt_thread_mdelay(1);
    }

    return -RT_ETIMEOUT;
}

static rt_err_t ch390_reset_rx_ptr(struct ch390 *ch390)
{
    rt_uint8_t rcr;
    rt_err_t ret;

    rcr = ch390_reg_read(ch390, CH390_RCR);

    ret = ch390_reg_write(ch390, CH390_RCR, rcr & (rt_uint8_t)~CH390_RCR_RXEN);
    if (ret != RT_EOK)
    {
        return ret;
    }

    ret = ch390_reg_write(ch390, CH390_MPTRCR, 0x01);
    if (ret != RT_EOK)
    {
        return ret;
    }

    ret = ch390_reg_write(ch390, CH390_MRRH, 0x0C);
    if (ret != RT_EOK)
    {
        return ret;
    }

    rt_thread_mdelay(1);
    return ch390_reg_write(ch390, CH390_RCR, rcr | CH390_RCR_RXEN);
}

static rt_err_t ch390_drop_packet(struct ch390 *ch390, rt_uint16_t len)
{
    rt_uint16_t ptr;
    rt_err_t ret;

    ptr = ch390_reg_read(ch390, CH390_MRRL);
    ptr |= (rt_uint16_t)ch390_reg_read(ch390, CH390_MRRH) << 8;
    ptr += len;
    if (ptr >= CH390_RX_MEM_END)
    {
        ptr -= CH390_RX_MEM_SIZE;
    }

    ret = ch390_reg_write(ch390, CH390_MRRL, ptr & 0xFF);
    if (ret != RT_EOK)
    {
        return ret;
    }

    return ch390_reg_write(ch390, CH390_MRRH, ptr >> 8);
}

static int ch390_read_rx_ready(struct ch390 *ch390)
{
    rt_uint8_t ready;
    rt_uint8_t rsr;
    rt_err_t ret;

    (void)ch390_reg_read(ch390, CH390_MRCMDX);
    ready = ch390_reg_read(ch390, CH390_MRCMDX);

    if ((ready & CH390_PKT_ERR_MASK) != 0)
    {
        LOG_W("rx ready error 0x%02x, reset rx pointer", ready);
        ret = ch390_reset_rx_ptr(ch390);
        return (ret == RT_EOK) ? -RT_EIO : ret;
    }

    if ((ready & CH390_PKT_RDY) == 0)
    {
        rsr = ch390_reg_read(ch390, CH390_RSR);
        if ((rsr & CH390_RSR_FOE) != 0)
        {
            ret = ch390_reset_rx_ptr(ch390);
            if (ret != RT_EOK)
            {
                return ret;
            }
        }

        return CH390_PKT_NONE;
    }

    return CH390_PKT_RDY;
}

static rt_bool_t ch390_read_link_status(struct ch390 *ch390)
{
    return (ch390_reg_read(ch390, CH390_NSR) & CH390_NSR_LINKST) ? RT_TRUE : RT_FALSE;
}

static void ch390_copy_rx_to_pbuf(struct ch390 *ch390, struct pbuf *p, rt_uint16_t len)
{
    struct pbuf *q;
    rt_uint8_t *src = ch390->rx_buf;
    rt_uint16_t copied = 0;

    for (q = p; (q != RT_NULL) && (copied < len); q = q->next)
    {
        rt_memcpy(q->payload, src, q->len);
        src += q->len;
        copied += q->len;
    }
}

static void ch390_poll_thread_entry(void *parameter)
{
    struct ch390 *ch390 = (struct ch390 *)parameter;
    rt_tick_t last_link_tick = 0;

    while (1)
    {
        int ready = CH390_PKT_NONE;
        rt_bool_t notify_rx = RT_FALSE;
        rt_bool_t notify_link = RT_FALSE;
        rt_bool_t link_up = RT_FALSE;
        rt_tick_t now = rt_tick_get();

        if (ch390_lock(ch390) == RT_EOK)
        {
            ready = ch390_read_rx_ready(ch390);
            if (ready == CH390_PKT_RDY)
            {
                notify_rx = RT_TRUE;
            }
            else if (ready < 0)
            {
                ch390->rx_errors++;
            }

            if ((now - last_link_tick) >= rt_tick_from_millisecond(CH390_LINK_POLL_MS))
            {
                link_up = ch390_read_link_status(ch390);
                if (link_up != ch390->link_up)
                {
                    ch390->link_up = link_up;
                    notify_link = RT_TRUE;
                }
                last_link_tick = now;
            }

            ch390_unlock(ch390);
        }

        if (notify_link)
        {
            LOG_I("link %s", link_up ? "up" : "down");
            eth_device_linkchange(&ch390->parent, link_up);
        }

        if (notify_rx)
        {
            eth_device_ready(&ch390->parent);
        }

        rt_thread_mdelay(ch390->poll_interval_ms);
    }
}

static rt_err_t ch390_basic_init(struct ch390 *ch390)
{
    static const rt_uint8_t multicast_hash[8] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };
    rt_err_t ret;

    LOG_I("CH390 init start");

    ret = ch390_reset(ch390);
    if (ret != RT_EOK)
    {
        return ret;
    }

    ret = ch390_read_id_or_known_register(ch390);
    if (ret != RT_EOK)
    {
        return ret;
    }

    ret = ch390_reg_write(ch390, CH390_GPR, CH390_GPR_PHY_ON);
    if (ret != RT_EOK)
    {
        return ret;
    }
    rt_thread_mdelay(1);

    ch390_reg_write(ch390, CH390_NSR, CH390_NSR_WAKEST | CH390_NSR_TX2END | CH390_NSR_TX1END);
    ch390_reg_write(ch390, CH390_ISR, 0xFF);
    ch390_reg_write(ch390, CH390_TCR2, 0x80);
    ch390_reg_write(ch390, CH390_TCSCR, 0x1F);

    ret = ch390_reg_write_array(ch390, CH390_MAR, multicast_hash, sizeof(multicast_hash));
    if (ret != RT_EOK)
    {
        return ret;
    }

    ret = ch390_set_mac(ch390, ch390->mac);
    if (ret != RT_EOK)
    {
        return ret;
    }

    ret = ch390_reg_write(ch390, CH390_IMR, CH390_IMR_PAR);
    if (ret != RT_EOK)
    {
        return ret;
    }

    ret = ch390_reg_write(ch390, CH390_RCR, CH390_RCR_RXEN | CH390_RCR_DIS_CRC | CH390_RCR_ALL);
    if (ret != RT_EOK)
    {
        return ret;
    }

    LOG_I("CH390 basic init done");
    return RT_EOK;
}

static rt_err_t ch390_init(rt_device_t dev)
{
    RT_UNUSED(dev);
    return RT_EOK;
}

static rt_err_t ch390_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_UNUSED(dev);
    RT_UNUSED(oflag);
    return RT_EOK;
}

static rt_err_t ch390_close(rt_device_t dev)
{
    RT_UNUSED(dev);
    return RT_EOK;
}

static rt_ssize_t ch390_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    RT_UNUSED(dev);
    RT_UNUSED(pos);
    RT_UNUSED(buffer);
    RT_UNUSED(size);
    return 0;
}

static rt_ssize_t ch390_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    RT_UNUSED(dev);
    RT_UNUSED(pos);
    RT_UNUSED(buffer);
    return size;
}

static rt_err_t ch390_control(rt_device_t dev, int cmd, void *args)
{
    struct eth_device *eth = (struct eth_device *)dev;
    struct ch390 *ch390 = rt_container_of(eth, struct ch390, parent);

    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (args == RT_NULL)
        {
            return -RT_ERROR;
        }
        rt_memcpy(args, ch390->mac, sizeof(ch390->mac));
        return RT_EOK;

    default:
        break;
    }

    return RT_EOK;
}

static struct pbuf *ch390_rx(rt_device_t dev)
{
    struct eth_device *eth = (struct eth_device *)dev;
    struct ch390 *ch390 = rt_container_of(eth, struct ch390, parent);
    struct pbuf *p = RT_NULL;
    rt_uint8_t header[4];
    rt_uint16_t rx_len;
    rt_uint16_t frame_len;
    int ready;
    rt_err_t ret;

    ch390_lock(ch390);

    ready = ch390_read_rx_ready(ch390);
    if (ready < 0)
    {
        ch390->rx_errors++;
        goto out;
    }
    if (ready == CH390_PKT_NONE)
    {
        goto out;
    }

    ret = ch390_mem_read(ch390, CH390_MRCMD, header, sizeof(header));
    if (ret != RT_EOK)
    {
        ch390->rx_errors++;
        goto out;
    }

    rx_len = ((rt_uint16_t)header[3] << 8) | header[2];
    if ((header[1] & CH390_RX_STATUS_ERR_MASK) ||
        (rx_len < CH390_PKT_MIN) || (rx_len > CH390_PKT_MAX))
    {
        ch390->rx_errors++;
        LOG_W("drop rx packet status=0x%02x len=%u", header[1], (unsigned int)rx_len);
        if ((rx_len >= CH390_PKT_MIN) && (rx_len <= CH390_PKT_MAX))
        {
            ch390_drop_packet(ch390, rx_len);
        }
        else
        {
            ch390_reset_rx_ptr(ch390);
        }
        goto out;
    }

    frame_len = rx_len - CH390_FCS_SIZE;
    p = pbuf_alloc(PBUF_LINK, frame_len, PBUF_POOL);
    if (p == RT_NULL)
    {
        ch390->rx_dropped++;
        ch390_drop_packet(ch390, rx_len);
        goto out;
    }

    ret = ch390_fifo_read(ch390, rx_len);
    if (ret != RT_EOK)
    {
        ch390->rx_errors++;
        pbuf_free(p);
        p = RT_NULL;
        goto out;
    }

    ch390_copy_rx_to_pbuf(ch390, p, frame_len);
    ch390->rx_packets++;
    ch390->rx_bytes += frame_len;

out:
    ch390_unlock(ch390);
    return p;
}

static rt_err_t ch390_tx(rt_device_t dev, struct pbuf *p)
{
    struct eth_device *eth = (struct eth_device *)dev;
    struct ch390 *ch390 = rt_container_of(eth, struct ch390, parent);
    rt_uint16_t len;
    rt_err_t ret = RT_EOK;

    if (p == RT_NULL)
    {
        return -RT_EINVAL;
    }

    len = p->tot_len;
    if ((len == 0) || (len > (CH390_PKT_MAX - CH390_FCS_SIZE)))
    {
        ch390->tx_errors++;
        return -RT_EINVAL;
    }

    ch390_lock(ch390);

    if (pbuf_copy_partial(p, &ch390->tx_buf[1], len, 0) != len)
    {
        ch390->tx_errors++;
        ret = -RT_EIO;
        goto out;
    }

    ret = ch390_wait_tx_idle(ch390, CH390_TX_TIMEOUT_MS);
    if (ret != RT_EOK)
    {
        ch390->tx_errors++;
        ch390->tx_timeouts++;
        goto out;
    }

    ret = ch390_fifo_write(ch390, len);
    if (ret != RT_EOK)
    {
        ch390->tx_errors++;
        goto out;
    }

    ret = ch390_reg_write(ch390, CH390_TXPLL, len & 0xFF);
    if (ret != RT_EOK)
    {
        ch390->tx_errors++;
        goto out;
    }

    ret = ch390_reg_write(ch390, CH390_TXPLH, len >> 8);
    if (ret != RT_EOK)
    {
        ch390->tx_errors++;
        goto out;
    }

    ret = ch390_reg_write(ch390, CH390_TCR, CH390_TCR_TXREQ);
    if (ret != RT_EOK)
    {
        ch390->tx_errors++;
        goto out;
    }

    ret = ch390_wait_tx_idle(ch390, CH390_TX_TIMEOUT_MS);
    if (ret != RT_EOK)
    {
        ch390->tx_errors++;
        ch390->tx_timeouts++;
        goto out;
    }

    ch390_reg_write(ch390, CH390_ISR, CH390_ISR_PT);
    ch390->tx_packets++;
    ch390->tx_bytes += len;

out:
    ch390_unlock(ch390);
    return ret;
}

void ch390_isr(void)
{
    if (ch390_dev.parent.netif != RT_NULL)
    {
        eth_device_ready(&ch390_dev.parent);
    }
}

rt_err_t ch390_attach(const struct ch390_config *config)
{
    struct rt_spi_configuration cfg;
    const rt_uint8_t *mac;
    const char *netif_name;
    rt_err_t ret;

    if ((config == RT_NULL) || (config->spi_device_name == RT_NULL))
    {
        return -RT_EINVAL;
    }

    if (ch390_dev.spi != RT_NULL)
    {
        LOG_E("only one CH390 device is supported");
        return -RT_EBUSY;
    }

    mac = (config->mac != RT_NULL) ? config->mac : ch390_default_mac;
    netif_name = (config->netif_name != RT_NULL) ? config->netif_name : CH390_DEFAULT_NETIF_NAME;

    rt_memset(&ch390_dev, 0, sizeof(ch390_dev));

    ch390_dev.rst_pin = config->rst_pin;
    ch390_dev.int_pin = config->int_pin;
    ch390_dev.poll_interval_ms = config->poll_interval_ms ? config->poll_interval_ms : CH390_DEFAULT_POLL_MS;
    rt_memcpy(ch390_dev.mac, mac, sizeof(ch390_dev.mac));

    ret = rt_mutex_init(&ch390_dev.lock, "ch390", RT_IPC_FLAG_PRIO);
    if (ret != RT_EOK)
    {
        LOG_E("lock init failed: %d", ret);
        return ret;
    }

    ch390_dev.spi = (struct rt_spi_device *)rt_device_find(config->spi_device_name);
    if (ch390_dev.spi == RT_NULL)
    {
        LOG_E("spi device %s not found", config->spi_device_name);
        ret = -RT_ENOSYS;
        goto err_reset_context;
    }

    cfg.data_width = 8;
    cfg.mode = RT_SPI_MODE_3 | RT_SPI_MSB;
    cfg.max_hz = config->spi_max_hz ? config->spi_max_hz : CH390_DEFAULT_SPI_MAX_HZ;

    ret = rt_spi_configure(ch390_dev.spi, &cfg);
    if (ret != RT_EOK)
    {
        LOG_E("spi configure failed: %d", ret);
        goto err_reset_context;
    }

    if (ch390_dev.int_pin != PIN_NONE)
    {
        rt_pin_mode(ch390_dev.int_pin, PIN_MODE_INPUT_PULLUP);
    }

    ch390_lock(&ch390_dev);
    ret = ch390_basic_init(&ch390_dev);
    ch390_unlock(&ch390_dev);
    if (ret != RT_EOK)
    {
        LOG_E("basic init failed: %d", ret);
        goto err_reset_context;
    }

    ch390_dev.parent.parent.type = RT_Device_Class_NetIf;
#ifdef RT_USING_DEVICE_OPS
    ch390_dev.parent.parent.ops = &ch390_ops;
#else
    ch390_dev.parent.parent.init = ch390_init;
    ch390_dev.parent.parent.open = ch390_open;
    ch390_dev.parent.parent.close = ch390_close;
    ch390_dev.parent.parent.read = ch390_read;
    ch390_dev.parent.parent.write = ch390_write;
    ch390_dev.parent.parent.control = ch390_control;
#endif
    ch390_dev.parent.eth_rx = ch390_rx;
    ch390_dev.parent.eth_tx = ch390_tx;

    ret = eth_device_init(&ch390_dev.parent, netif_name);
    if (ret != RT_EOK)
    {
        LOG_E("eth_device_init failed: %d", ret);
        goto err_reset_context;
    }

    ch390_lock(&ch390_dev);
    ch390_dev.link_up = ch390_read_link_status(&ch390_dev);
    ch390_unlock(&ch390_dev);
    LOG_I("link %s", ch390_dev.link_up ? "up" : "down");
    eth_device_linkchange(&ch390_dev.parent, ch390_dev.link_up);

    ch390_dev.poll_thread = rt_thread_create("ch390rx",
                                             ch390_poll_thread_entry,
                                             &ch390_dev,
                                             1536,
                                             RT_THREAD_PRIORITY_MAX - 2,
                                             20);
    if (ch390_dev.poll_thread == RT_NULL)
    {
        LOG_E("poll thread create failed");
        ret = -RT_ENOMEM;
        goto err_deinit_eth;
    }
    rt_thread_startup(ch390_dev.poll_thread);

    LOG_I("CH390 registered as %s", netif_name);
    return RT_EOK;

err_deinit_eth:
    eth_device_deinit(&ch390_dev.parent);
err_reset_context:
    rt_mutex_detach(&ch390_dev.lock);
    rt_memset(&ch390_dev, 0, sizeof(ch390_dev));
    return ret;
}

#endif /* RT_USING_CH390 */
