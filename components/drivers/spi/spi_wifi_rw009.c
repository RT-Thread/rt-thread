/*
 * File      : spi_wifi_rw009.c
 * This file is part of RT-Thread RTOS
 * Copyright by Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-07-31     aozima       the first version
 */

#include <rtthread.h>
#include <drivers/spi.h>

#include <netif/ethernetif.h>
#include <netif/etharp.h>
#include <lwip/icmp.h>
#include "lwipopts.h"

#include "spi_wifi_rw009.h"

#define SSID_NAME      "AP_SSID"
#define SSID_PASSWORD  "AP_passwd"

//#define WIFI_DEBUG_ON
// #define ETH_RX_DUMP
// #define ETH_TX_DUMP

#ifdef WIFI_DEBUG_ON
#define WIFI_DEBUG         rt_kprintf("[WIFI] ");rt_kprintf
#else
#define WIFI_DEBUG(...)
#endif /* #ifdef WIFI_DEBUG_ON */

#define MAX_BUFFER_SIZE     (sizeof(struct response) + MAX_DATA_LEN)
#define MAX_ADDR_LEN 6
struct spi_wifi_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;

    struct rt_spi_device *rt_spi_device;

    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];         /* hw address   */
    rt_uint8_t  active;

    struct rt_mempool spi_tx_mp;
    struct rt_mempool spi_rx_mp;

    struct rt_mailbox spi_tx_mb;
    struct rt_mailbox eth_rx_mb;

    int spi_tx_mb_pool[SPI_TX_POOL_SIZE];
    int eth_rx_mb_pool[SPI_TX_POOL_SIZE];

    int spi_wifi_cmd_mb_pool[3];
    struct rt_mailbox spi_wifi_cmd_mb;

    ALIGN(4)
    rt_uint8_t spi_tx_mempool[(sizeof(struct spi_data_packet) + 4) * SPI_TX_POOL_SIZE];
    ALIGN(4)
    rt_uint8_t spi_rx_mempool[(sizeof(struct spi_data_packet) + 4) * SPI_TX_POOL_SIZE];

    ALIGN(4)
    uint8_t spi_hw_rx_buffer[MAX_BUFFER_SIZE];
};
static struct spi_wifi_eth spi_wifi_device;
static struct rt_event spi_wifi_data_event;

static void resp_handler(struct spi_wifi_eth *wifi_device, struct spi_wifi_resp *resp)
{
    struct spi_wifi_resp *resp_return;

    switch (resp->cmd)
    {
    case SPI_WIFI_CMD_INIT:
        WIFI_DEBUG("resp_handler SPI_WIFI_CMD_INIT\n");
        resp_return = (struct spi_wifi_resp *)rt_malloc(sizeof(struct spi_wifi_resp)); //TODO:
        memcpy(resp_return, resp, 10);
        rt_mb_send(&wifi_device->spi_wifi_cmd_mb, (rt_uint32_t)resp_return);
        break;

    case SPI_WIFI_CMD_SCAN:
        WIFI_DEBUG("resp_handler SPI_WIFI_CMD_SCAN\n");
        break;

    case SPI_WIFI_CMD_JOIN:
        WIFI_DEBUG("resp_handler SPI_WIFI_CMD_JOIN\n");
        wifi_device->active = 1;
        eth_device_linkchange(&wifi_device->parent, RT_TRUE);
        break;

    default:
        WIFI_DEBUG("resp_handler %d\n", resp->cmd);
        break;
    }

}

static rt_err_t spi_wifi_transfer(struct spi_wifi_eth *dev)
{
    struct pbuf *p = RT_NULL;
    struct cmd_request cmd;
    struct response resp;

    rt_err_t result;
    const struct spi_data_packet *data_packet = RT_NULL;

    struct spi_wifi_eth *wifi_device = (struct spi_wifi_eth *)dev;
    struct rt_spi_device *rt_spi_device = wifi_device->rt_spi_device;

    spi_wifi_int_cmd(0);
    while (spi_wifi_is_busy());
    WIFI_DEBUG("sequence start!\n");

    memset(&cmd, 0, sizeof(struct cmd_request));
    cmd.magic1 = CMD_MAGIC1;
    cmd.magic2 = CMD_MAGIC2;

    cmd.flag |= CMD_FLAG_MRDY;

    result = rt_mb_recv(&wifi_device->spi_tx_mb,
                        (rt_uint32_t *)&data_packet,
                        0);
    if ((result == RT_EOK) && (data_packet != RT_NULL) && (data_packet->data_len > 0))
    {
        cmd.M2S_len = data_packet->data_len + member_offset(struct spi_data_packet, buffer);
        //WIFI_DEBUG("cmd.M2S_len = %d\n", cmd.M2S_len);
    }

    rt_spi_send(rt_spi_device, &cmd, sizeof(cmd));
    while (spi_wifi_is_busy());

    {
        struct rt_spi_message message;
        uint32_t max_data_len = 0;

        /* setup message */
        message.send_buf = RT_NULL;
        message.recv_buf = &resp;
        message.length = sizeof(resp);
        message.cs_take = 1;
        message.cs_release = 0;

        rt_spi_take_bus(rt_spi_device);

        /* transfer message */
        rt_spi_device->bus->ops->xfer(rt_spi_device, &message);

        if ((resp.magic1 != RESP_MAGIC1) || (resp.magic2 != RESP_MAGIC2))
        {
            WIFI_DEBUG("bad resp magic, abort!\n");
            goto _bad_resp_magic;
        }

        if (resp.flag & RESP_FLAG_SRDY)
        {
            WIFI_DEBUG("RESP_FLAG_SRDY\n");
            max_data_len = cmd.M2S_len;
        }

        if (resp.S2M_len)
        {
            WIFI_DEBUG("resp.S2M_len: %d\n", resp.S2M_len);
            if (resp.S2M_len > sizeof(struct spi_data_packet))
            {
                WIFI_DEBUG("resp.S2M_len > sizeof(struct spi_data_packet), drop!\n");
                resp.S2M_len = 0;//drop
            }

            if (resp.S2M_len > max_data_len)
                max_data_len = resp.S2M_len;
        }

        if (max_data_len == 0)
        {
            WIFI_DEBUG("no rx or tx data!\n");
        }

        //WIFI_DEBUG("max_data_len = %d\n", max_data_len);

_bad_resp_magic:
        /* setup message */
        message.send_buf = data_packet;//&tx_buffer;
        message.recv_buf = wifi_device->spi_hw_rx_buffer;//&rx_buffer;
        message.length = max_data_len;
        message.cs_take = 0;
        message.cs_release = 1;

        /* transfer message */
        rt_spi_device->bus->ops->xfer(rt_spi_device, &message);

        rt_spi_release_bus(rt_spi_device);

        if (cmd.M2S_len && (resp.flag & RESP_FLAG_SRDY))
        {
            rt_mp_free((void *)data_packet);
        }

        if ((resp.S2M_len) && (resp.S2M_len <= MAX_DATA_LEN))
        {
            data_packet = (struct spi_data_packet *)wifi_device->spi_hw_rx_buffer;
            if (data_packet->data_type == data_type_eth_data)
            {

                if (wifi_device->active)
                {
                    p = pbuf_alloc(PBUF_LINK, data_packet->data_len, PBUF_RAM);
                    pbuf_take(p, (rt_uint8_t *)data_packet->buffer, data_packet->data_len);

                    rt_mb_send(&wifi_device->eth_rx_mb, (rt_uint32_t)p);
                    eth_device_ready((struct eth_device *)dev);
                }
                else
                {
                    WIFI_DEBUG("!active, RX drop.\n");
                }
            }
            else if (data_packet->data_type == data_type_resp)
            {
                WIFI_DEBUG("data_type_resp\n");
                resp_handler(dev, (struct spi_wifi_resp *)data_packet->buffer);
            }
            else
            {
                WIFI_DEBUG("data_type: %d, %dbyte\n",
                           data_packet->data_type,
                           data_packet->data_len);
            }
        }
    }
    spi_wifi_int_cmd(1);

    WIFI_DEBUG("sequence finish!\n\n");

    if ((cmd.M2S_len == 0) && (resp.S2M_len == 0))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

#if defined(ETH_RX_DUMP) ||  defined(ETH_TX_DUMP)
static void packet_dump(const char *msg, const struct pbuf *p)
{
    rt_uint32_t i;
    rt_uint8_t *ptr = p->payload;

    rt_kprintf("%s %d byte\n", msg, p->tot_len);

    for (i = 0; i < p->tot_len; i++)
    {
        if ((i % 8) == 0)
        {
            rt_kprintf("  ");
        }
        if ((i % 16) == 0)
        {
            rt_kprintf("\r\n");
        }
        rt_kprintf("%02x ", *ptr);
        ptr++;
    }
    rt_kprintf("\n\n");
}
#endif /* dump */

/* initialize the interface */
static rt_err_t spi_wifi_eth_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t spi_wifi_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t spi_wifi_eth_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t spi_wifi_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t spi_wifi_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}


static rt_err_t spi_wifi_eth_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    struct spi_wifi_eth *wifi_device = (struct spi_wifi_eth *)dev;
    struct spi_data_packet *data_packet;
    struct spi_wifi_cmd *wifi_cmd;
    struct spi_wifi_resp *resp;

    switch (cmd)
    {
    case NIOCTL_GADDR:
        memcpy(args, wifi_device->dev_addr, 6);
        break;

    case SPI_WIFI_CMD_INIT:
        /* get mac address */
        if (args)
        {
            rt_err_t result;

            data_packet = (struct spi_data_packet *)rt_mp_alloc(&wifi_device->spi_tx_mp, RT_WAITING_FOREVER);
            // TODO: check result.

            wifi_cmd = (struct spi_wifi_cmd *)data_packet->buffer;
            wifi_cmd->cmd = SPI_WIFI_CMD_INIT;

            data_packet->data_type = data_type_cmd;
            data_packet->data_len = member_offset(struct spi_wifi_cmd, buffer) + 0;

            rt_mb_send(&wifi_device->spi_tx_mb, (rt_uint32_t)data_packet);
            rt_event_send(&spi_wifi_data_event, 1);

            result = rt_mb_recv(&wifi_device->spi_wifi_cmd_mb,
                                (rt_uint32_t *)&resp,
                                RT_WAITING_FOREVER);

            if ((result == RT_EOK) && (resp != RT_NULL))
            {
                WIFI_DEBUG("resp cmd: %d\n", resp->cmd);

                rt_memcpy(args, resp->buffer, 6);
            }
        }
        else return -RT_ERROR;
        break;


    case SPI_WIFI_CMD_SCAN:

    case SPI_WIFI_CMD_JOIN:
        if (args)
        {
            struct cmd_join *cmd_join;

            data_packet = (struct spi_data_packet *)rt_mp_alloc(&wifi_device->spi_tx_mp, RT_WAITING_FOREVER);

            wifi_cmd = (struct spi_wifi_cmd *)data_packet->buffer;
            wifi_cmd->cmd = SPI_WIFI_CMD_JOIN;
            cmd_join = (struct cmd_join *)wifi_cmd->buffer;

#define WPA_SECURITY    0x00200000
#define WPA2_SECURITY   0x00400000

#define TKIP_ENABLED    0x0002
#define AES_ENABLED     0x0004


            strncpy(cmd_join->ssid, SSID_NAME, SSID_NAME_LENGTH_MAX);
            strncpy(cmd_join->passwd, SSID_PASSWORD, PASSWORD_LENGTH_MAX);
            cmd_join->security = WPA2_SECURITY | TKIP_ENABLED | AES_ENABLED;
            // cmd_join->security = WPA_SECURITY | TKIP_ENABLED;
            data_packet->data_type = data_type_cmd;
            data_packet->data_len = sizeof(struct cmd_join) + member_offset(struct spi_wifi_cmd, buffer);

            rt_mb_send(&wifi_device->spi_tx_mb, (rt_uint32_t)data_packet);
            rt_event_send(&spi_wifi_data_event, 1);
        }
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* transmit packet. */
rt_err_t spi_wifi_eth_tx(rt_device_t dev, struct pbuf *p)
{
    rt_err_t result = RT_EOK;
    struct spi_data_packet *data_packet;
    struct spi_wifi_eth *wifi_device = (struct spi_wifi_eth *)dev;

    if (!wifi_device->active)
    {
        WIFI_DEBUG("!active, TX drop!\n");
        return RT_EOK;
    }

    /* get free tx buffer */
    data_packet = (struct spi_data_packet *)rt_mp_alloc(&wifi_device->spi_tx_mp, RT_WAITING_FOREVER);
    if (data_packet != RT_NULL)
    {
        data_packet->data_type = data_type_eth_data;
        data_packet->data_len = p->tot_len;

        pbuf_copy_partial(p, data_packet->buffer, data_packet->data_len, 0);

        rt_mb_send(&wifi_device->spi_tx_mb, (rt_uint32_t)data_packet);
        eth_device_ready((struct eth_device *)dev);
    }
    else
        return -RT_ERROR;

#ifdef ETH_TX_DUMP
    packet_dump("TX dump", p);
#endif /* ETH_TX_DUMP */

    /* Return SUCCESS */
    return result;
}

/* reception packet. */
struct pbuf *spi_wifi_eth_rx(rt_device_t dev)
{
    struct pbuf *p = RT_NULL;
    struct spi_wifi_eth *wifi_device = (struct spi_wifi_eth *)dev;

    if (rt_mb_recv(&wifi_device->eth_rx_mb, (rt_uint32_t *)&p, 0) != RT_EOK)
    {
        return RT_NULL;
    }



    return p;
}

static void spi_wifi_data_thread_entry(void *parameter)
{
    rt_uint32_t e;
    rt_err_t result;

    while (1)
    {
        /* receive first event */
        if (rt_event_recv(&spi_wifi_data_event,
                          1,
                          RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER,
                          &e) != RT_EOK)
        {
            continue;
        }

        result = spi_wifi_transfer(&spi_wifi_device);

        if (result == RT_EOK)
        {
            rt_event_send(&spi_wifi_data_event, 1);
        }
    }
}

rt_err_t rt_hw_wifi_init(const char *spi_device_name)
{
    memset(&spi_wifi_device, 0, sizeof(struct spi_wifi_eth));

    spi_wifi_device.rt_spi_device = (struct rt_spi_device *)rt_device_find(spi_device_name);

    if (spi_wifi_device.rt_spi_device == RT_NULL)
    {
        WIFI_DEBUG("spi device %s not found!\r\n", spi_device_name);
        return -RT_ENOSYS;
    }

    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0 and Mode 3 */
        cfg.max_hz = 1000000; /* 50M */
        rt_spi_configure(spi_wifi_device.rt_spi_device, &cfg);
    }

    spi_wifi_device.parent.parent.init       = spi_wifi_eth_init;
    spi_wifi_device.parent.parent.open       = spi_wifi_eth_open;
    spi_wifi_device.parent.parent.close      = spi_wifi_eth_close;
    spi_wifi_device.parent.parent.read       = spi_wifi_eth_read;
    spi_wifi_device.parent.parent.write      = spi_wifi_eth_write;
    spi_wifi_device.parent.parent.control    = spi_wifi_eth_control;
    spi_wifi_device.parent.parent.user_data  = RT_NULL;

    spi_wifi_device.parent.eth_rx     = spi_wifi_eth_rx;
    spi_wifi_device.parent.eth_tx     = spi_wifi_eth_tx;

    rt_mp_init(&spi_wifi_device.spi_tx_mp,
               "spi_tx",
               &spi_wifi_device.spi_tx_mempool[0],
               sizeof(spi_wifi_device.spi_tx_mempool),
               sizeof(struct spi_data_packet));

    rt_mp_init(&spi_wifi_device.spi_rx_mp,
               "spi_rx",
               &spi_wifi_device.spi_rx_mempool[0],
               sizeof(spi_wifi_device.spi_rx_mempool),
               sizeof(struct spi_data_packet));

    rt_mb_init(&spi_wifi_device.spi_tx_mb,
               "spi_tx",
               &spi_wifi_device.spi_tx_mb_pool[0],
               SPI_TX_POOL_SIZE,
               RT_IPC_FLAG_PRIO);

    rt_mb_init(&spi_wifi_device.eth_rx_mb,
               "eth_rx",
               &spi_wifi_device.eth_rx_mb_pool[0],
               SPI_TX_POOL_SIZE,
               RT_IPC_FLAG_PRIO);

    rt_mb_init(&spi_wifi_device.spi_wifi_cmd_mb,
               "wifi_cmd",
               &spi_wifi_device.spi_wifi_cmd_mb_pool[0],
               sizeof(spi_wifi_device.spi_wifi_cmd_mb_pool) / 4,
               RT_IPC_FLAG_PRIO);
    rt_event_init(&spi_wifi_data_event, "wifi", RT_IPC_FLAG_FIFO);

    spi_wifi_hw_init();

    {
        rt_thread_t tid;


        tid = rt_thread_create("wifi",
                               spi_wifi_data_thread_entry,
                               RT_NULL,
                               2048,
                               RT_THREAD_PRIORITY_MAX - 2,
                               20);

        if (tid != RT_NULL)
            rt_thread_startup(tid);
    }

    /* init: get mac address */
    {
        WIFI_DEBUG("wifi_control SPI_WIFI_CMD_INIT\n");
        spi_wifi_eth_control((rt_device_t)&spi_wifi_device,
                             SPI_WIFI_CMD_INIT,
                             (void *)&spi_wifi_device.dev_addr[0]);

    }
    /* register eth device */
    eth_device_init(&(spi_wifi_device.parent), "w0");
    eth_device_linkchange(&spi_wifi_device.parent, RT_FALSE);

    {
        WIFI_DEBUG("wifi_control SPI_WIFI_CMD_JOIN\n");
        spi_wifi_eth_control((rt_device_t)&spi_wifi_device,
                             SPI_WIFI_CMD_JOIN,
                             (void *)&spi_wifi_device.dev_addr[0]);

        WIFI_DEBUG("wifi_control exit\n");
    }

    return RT_EOK;
}

void spi_wifi_isr(int vector)
{
	/* enter interrupt */
	rt_interrupt_enter();

    WIFI_DEBUG("spi_wifi_isr\n");
    rt_event_send(&spi_wifi_data_event, 1);

	/* leave interrupt */
	rt_interrupt_leave();
}
