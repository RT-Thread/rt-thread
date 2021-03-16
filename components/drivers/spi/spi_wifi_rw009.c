/*
 * COPYRIGHT (C) 2011-2021, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-07-31     aozima       the first version
 * 2014-09-18     aozima       update command & response.
 * 2017-07-28     armink       fix auto reconnect feature
 */

#include <rtthread.h>
#include <drivers/spi.h>

#include <netif/ethernetif.h>
#include <netif/etharp.h>
#include <lwip/icmp.h>
#include "lwipopts.h"

#define WIFI_DEBUG_ON
// #define ETH_RX_DUMP
// #define ETH_TX_DUMP

#ifdef WIFI_DEBUG_ON
#define WIFI_DEBUG         rt_kprintf("[RW009] ");rt_kprintf
//#define SPI_DEBUG         rt_kprintf("[SPI] ");rt_kprintf
#define SPI_DEBUG(...)
#else
#define WIFI_DEBUG(...)
#define SPI_DEBUG(...)
#endif /* #ifdef WIFI_DEBUG_ON */

/********************************* RW009 **************************************/
#include "spi_wifi_rw009.h"

/* tools */
#define node_entry(node, type, member) \
    ((type *)((char *)(node) - (unsigned long)(&((type *)0)->member)))
#define member_offset(type, member) \
    ((unsigned long)(&((type *)0)->member))

#define MAX_SPI_PACKET_SIZE     (member_offset(struct spi_data_packet, buffer) + SPI_MAX_DATA_LEN)
#define MAX_SPI_BUFFER_SIZE     (sizeof(struct spi_response) + MAX_SPI_PACKET_SIZE)
#define MAX_ADDR_LEN 6

struct rw009_wifi
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

    int spi_tx_mb_pool[SPI_TX_POOL_SIZE + 1];
    int eth_rx_mb_pool[SPI_RX_POOL_SIZE + 1];

    int rw009_cmd_mb_pool[3];
    struct rt_mailbox rw009_cmd_mb;
    uint32_t last_cmd;

    ALIGN(4)
    rt_uint8_t spi_tx_mempool[(sizeof(struct spi_data_packet) + 4) * SPI_TX_POOL_SIZE];
    ALIGN(4)
    rt_uint8_t spi_rx_mempool[(sizeof(struct spi_data_packet) + 4) * SPI_RX_POOL_SIZE];

    ALIGN(4)
    uint8_t spi_hw_rx_buffer[MAX_SPI_BUFFER_SIZE];

    /* status for RW009 */
    rw009_ap_info ap_info;  /* AP info for conn. */
    rw009_ap_info *ap_scan; /* AP list for SCAN. */
    uint32_t ap_scan_count;
};
static struct rw009_wifi rw009_wifi_device;
static struct rt_event spi_wifi_data_event;

static void resp_handler(struct rw009_wifi *wifi_device, struct rw009_resp *resp)
{
    struct rw009_resp *resp_return = RT_NULL;

    switch (resp->cmd)
    {
    case RW009_CMD_INIT:
        WIFI_DEBUG("resp_handler RW009_CMD_INIT\n");
        resp_return = (struct rw009_resp *)rt_malloc(member_offset(struct rw009_resp, resp) + sizeof(rw009_resp_init)); //TODO:
        if(resp_return == RT_NULL) break;
        memcpy(resp_return, resp, member_offset(struct rw009_resp, resp) + sizeof(rw009_resp_init));

        WIFI_DEBUG("sn:%-*.*s\n", sizeof(resp->resp.init.sn), sizeof(resp->resp.init.sn), resp->resp.init.sn);
        WIFI_DEBUG("version:%-*.*s\n", sizeof(resp->resp.init.version), sizeof(resp->resp.init.version), resp->resp.init.version);

        rt_memcpy(wifi_device->dev_addr, resp->resp.init.mac, 6);
        break;

    case RW009_CMD_SCAN:
        if( resp->len == sizeof(rw009_ap_info) )
        {
            rw009_ap_info *ap_scan = rt_realloc(wifi_device->ap_scan, sizeof(rw009_ap_info) * (wifi_device->ap_scan_count + 1) );
            if(ap_scan != RT_NULL)
            {
                memcpy( &ap_scan[wifi_device->ap_scan_count], &resp->resp.ap_info, sizeof(rw009_ap_info) );

                //dump
                if(1)
                {
#ifdef WIFI_DEBUG_ON
                    rw009_ap_info *ap_info = &resp->resp.ap_info;
                    WIFI_DEBUG("SCAN SSID:%-32.32s\n", ap_info->ssid);
                    WIFI_DEBUG("SCAN BSSID:%02X-%02X-%02X-%02X-%02X-%02X\n",
                               ap_info->bssid[0],
                               ap_info->bssid[1],
                               ap_info->bssid[2],
                               ap_info->bssid[3],
                               ap_info->bssid[4],
                               ap_info->bssid[5]);
                    WIFI_DEBUG("SCAN rssi:%ddBm\n", ap_info->rssi);
                    WIFI_DEBUG("SCAN rate:%dMbps\n", ap_info->max_data_rate/1000);
                    WIFI_DEBUG("SCAN channel:%d\n", ap_info->channel);
                    WIFI_DEBUG("SCAN security:%08X\n\n", ap_info->security);
#endif /* WIFI_DEBUG_ON */
                }

                wifi_device->ap_scan_count++;
                wifi_device->ap_scan = ap_scan;
            }

            return; /* wait for next ap */
        }
        break;
    case RW009_CMD_JOIN:
    case RW009_CMD_EASY_JOIN:
        WIFI_DEBUG("resp_handler RW009_CMD_EASY_JOIN\n");
        resp_return = (struct rw009_resp *)rt_malloc(member_offset(struct rw009_resp, resp) + sizeof(rw009_resp_join)); //TODO:
        if(resp_return == RT_NULL) break;
        memcpy(resp_return, resp, member_offset(struct rw009_resp, resp) + sizeof(rw009_resp_join));

        if( resp->result == 0 )
        {
            memcpy(&wifi_device->ap_info, &resp_return->resp.ap_info, sizeof(rw009_resp_join));
            wifi_device->active = 1;
            eth_device_linkchange(&wifi_device->parent, RT_TRUE);
        }
        else
        {
            wifi_device->active = 1;
            eth_device_linkchange(&wifi_device->parent, RT_FALSE);
            WIFI_DEBUG("RW009_CMD_EASY_JOIN result: %d\n", resp->result );
        }

        //dupm
        if(1)
        {
#ifdef WIFI_DEBUG_ON
            rw009_ap_info *ap_info = &resp->resp.ap_info;
            WIFI_DEBUG("JOIN SSID:%-32.32s\n", ap_info->ssid);
            WIFI_DEBUG("JOIN BSSID:%02X-%02X-%02X-%02X-%02X-%02X\n",
                       ap_info->bssid[0],
                       ap_info->bssid[1],
                       ap_info->bssid[2],
                       ap_info->bssid[3],
                       ap_info->bssid[4],
                       ap_info->bssid[5]);
            WIFI_DEBUG("JOIN rssi:%ddBm\n", ap_info->rssi);
            WIFI_DEBUG("JOIN rate:%dMbps\n", ap_info->max_data_rate/1000);
            WIFI_DEBUG("JOIN channel:%d\n", ap_info->channel);
            WIFI_DEBUG("JOIN security:%08X\n\n", ap_info->security);
#endif /* WIFI_DEBUG_ON */
        }
        break;

    case RW009_CMD_RSSI:
        // TODO: client RSSI.
    {
        rw009_ap_info *ap_info = &resp->resp.ap_info;
        wifi_device->ap_info.rssi = ap_info->rssi;
        WIFI_DEBUG("current RSSI: %d\n", wifi_device->ap_info.rssi);
    }
    break;

    case RW009_CMD_SOFTAP:
    {
        if( resp->result == 0 )
        {
            ;
            wifi_device->active = 1;
            eth_device_linkchange(&wifi_device->parent, RT_TRUE);
        }
        else
        {
            WIFI_DEBUG("RW009_CMD_EASY_JOIN result: %d\n", resp->result );
        }

    }
    break;

    default:
        WIFI_DEBUG("resp_handler %d\n", resp->cmd);
        break;
    }


    if(resp->cmd == wifi_device->last_cmd)
    {
        rt_mb_send(&wifi_device->rw009_cmd_mb, (rt_uint32_t)resp_return);
        return;
    }
    else
    {
        rt_free(resp_return);
    }
}

static rt_err_t rw009_cmd(struct rw009_wifi *wifi_device, uint32_t cmd, void *args)
{
    rt_err_t result = RT_EOK;
    rt_int32_t timeout = RW009_CMD_TIMEOUT;

    struct spi_data_packet *data_packet;
    struct rw009_cmd *wifi_cmd = RT_NULL;
    struct rw009_resp *resp = RT_NULL;

    wifi_device->last_cmd = cmd;

    data_packet = (struct spi_data_packet *)rt_mp_alloc(&wifi_device->spi_tx_mp, RT_WAITING_FOREVER);
    wifi_cmd = (struct rw009_cmd *)data_packet->buffer;

    wifi_cmd->cmd = cmd;
    wifi_cmd->len = 0;

    if( cmd == RW009_CMD_INIT )
    {
        wifi_cmd->len = sizeof(rw009_cmd_init);
    }
    else if( cmd == RW009_CMD_SCAN )
    {
        wifi_cmd->len = 0;
        timeout += RT_TICK_PER_SECOND*10;

        if(wifi_device->ap_scan)
        {
            rt_free(wifi_device->ap_scan);
            wifi_device->ap_scan = RT_NULL;
            wifi_device->ap_scan_count = 0;
        }
    }
    else if( cmd == RW009_CMD_JOIN )
    {
        wifi_cmd->len = sizeof(rw009_cmd_join);
    }
    else if( cmd == RW009_CMD_EASY_JOIN )
    {
        wifi_cmd->len = sizeof(rw009_cmd_easy_join);
        timeout += RT_TICK_PER_SECOND*5;
    }
    else if( cmd == RW009_CMD_RSSI )
    {
        wifi_cmd->len = sizeof(rw009_cmd_rssi);
    }
    else if( cmd == RW009_CMD_SOFTAP )
    {
        wifi_cmd->len = sizeof(rw009_cmd_softap);
    }
    else
    {
        WIFI_DEBUG("unkown RW009 CMD %d\n", cmd);
        result = -RT_ENOSYS;
        rt_mp_free(data_packet);
        data_packet = RT_NULL;
    }

    if(data_packet == RT_NULL)
    {
        goto _exit;
    }

    if(wifi_cmd->len)
        memcpy(&wifi_cmd->params, args, wifi_cmd->len);

    data_packet->data_type = data_type_cmd;
    data_packet->data_len = member_offset(struct rw009_cmd, params) + wifi_cmd->len;

    rt_mb_send(&wifi_device->spi_tx_mb, (rt_uint32_t)data_packet);
    rt_event_send(&spi_wifi_data_event, 1);

    result = rt_mb_recv(&wifi_device->rw009_cmd_mb,
                        (rt_uint32_t *)&resp,
                        timeout);

    if ( result != RT_EOK )
    {
        WIFI_DEBUG("CMD %d error, resultL %d\n", cmd, result );
    }

    if(resp != RT_NULL)
        result = resp->result;

_exit:
    wifi_device->last_cmd = 0;
    if(resp) rt_free(resp);
    return result;
}

static rt_err_t spi_wifi_transfer(struct rw009_wifi *dev)
{
    struct pbuf *p = RT_NULL;
    struct spi_cmd_request cmd;
    struct spi_response resp;

    rt_err_t result;
    const struct spi_data_packet *data_packet = RT_NULL;

    struct rw009_wifi *wifi_device = (struct rw009_wifi *)dev;
    struct rt_spi_device *rt_spi_device = wifi_device->rt_spi_device;

    spi_wifi_int_cmd(0);
    while (spi_wifi_is_busy());
    SPI_DEBUG("sequence start!\n");

    memset(&cmd, 0, sizeof(struct spi_cmd_request));
    cmd.magic1 = CMD_MAGIC1;
    cmd.magic2 = CMD_MAGIC2;

    cmd.flag |= CMD_FLAG_MRDY;

    result = rt_mb_recv(&wifi_device->spi_tx_mb,
                        (rt_uint32_t *)&data_packet,
                        0);
    if ((result == RT_EOK) && (data_packet != RT_NULL) && (data_packet->data_len > 0))
    {
        cmd.M2S_len = data_packet->data_len + member_offset(struct spi_data_packet, buffer);
        //SPI_DEBUG("cmd.M2S_len = %d\n", cmd.M2S_len);
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
            SPI_DEBUG("bad resp magic, abort!\n");
            goto _bad_resp_magic;
        }

        if (resp.flag & RESP_FLAG_SRDY)
        {
            SPI_DEBUG("RESP_FLAG_SRDY\n");
            max_data_len = cmd.M2S_len;
        }

        if (resp.S2M_len)
        {
            SPI_DEBUG("resp.S2M_len: %d\n", resp.S2M_len);
            if (resp.S2M_len > MAX_SPI_PACKET_SIZE)
            {
                SPI_DEBUG("resp.S2M_len %d > %d(MAX_SPI_PACKET_SIZE), drop!\n", resp.S2M_len, MAX_SPI_PACKET_SIZE);
                resp.S2M_len = 0;//drop
            }

            if (resp.S2M_len > max_data_len)
                max_data_len = resp.S2M_len;
        }

        if (max_data_len == 0)
        {
            SPI_DEBUG("no rx or tx data!\n");
        }

        //SPI_DEBUG("max_data_len = %d\n", max_data_len);

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

        if ((resp.S2M_len) && (resp.S2M_len <= MAX_SPI_PACKET_SIZE))
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
                    SPI_DEBUG("!active, RX drop.\n");
                }
            }
            else if (data_packet->data_type == data_type_resp)
            {
                SPI_DEBUG("data_type_resp\n");
                resp_handler(dev, (struct rw009_resp *)data_packet->buffer);
            }
            else
            {
                SPI_DEBUG("data_type: %d, %dbyte\n",
                          data_packet->data_type,
                          data_packet->data_len);
            }
        }
    }
    spi_wifi_int_cmd(1);

    SPI_DEBUG("sequence finish!\n\n");

    if ((cmd.M2S_len == 0) && (resp.S2M_len == 0))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

#if defined(ETH_RX_DUMP) ||  defined(ETH_TX_DUMP)
static void packet_dump(const char *msg, const struct pbuf *p)
{
    const struct pbuf* q;
    rt_uint32_t i,j;
    rt_uint8_t *ptr = p->payload;

    rt_kprintf("%s %d byte\n", msg, p->tot_len);

    i=0;
    for(q=p; q != RT_NULL; q= q->next)
    {
        ptr = q->payload;

        for(j=0; j<q->len; j++)
        {
            if( (i%8) == 0 )
            {
                rt_kprintf("  ");
            }
            if( (i%16) == 0 )
            {
                rt_kprintf("\r\n");
            }
            rt_kprintf("%02x ",*ptr);

            i++;
            ptr++;
        }
    }
    rt_kprintf("\n\n");
}
#endif /* dump */

/********************************* RT-Thread Ethernet interface begin **************************************/
static rt_err_t rw009_wifi_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rw009_wifi_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rw009_wifi_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rw009_wifi_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t rw009_wifi_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rw009_wifi_control(rt_device_t dev, int cmd, void *args)
{
    struct rw009_wifi *wifi_device = (struct rw009_wifi *)dev;
    rt_err_t result = RT_EOK;

    if (cmd == NIOCTL_GADDR)
    {
        memcpy(args, wifi_device->dev_addr, 6);
    }
    else
    {
        result = rw009_cmd(wifi_device, cmd, args);
    }

    return result;
}

/* transmit packet. */
rt_err_t rw009_wifi_tx(rt_device_t dev, struct pbuf *p)
{
    rt_err_t result = RT_EOK;
    struct spi_data_packet *data_packet;
    struct rw009_wifi *wifi_device = (struct rw009_wifi *)dev;

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
        rt_event_send(&spi_wifi_data_event, 1);
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
struct pbuf *rw009_wifi_rx(rt_device_t dev)
{
    struct pbuf *p = RT_NULL;
    struct rw009_wifi *wifi_device = (struct rw009_wifi *)dev;

    if (rt_mb_recv(&wifi_device->eth_rx_mb, (rt_uint32_t *)&p, 0) != RT_EOK)
    {
        return RT_NULL;
    }

#ifdef ETH_RX_DUMP
    if(p)
        packet_dump("RX dump", p);
#endif /* ETH_RX_DUMP */

    return p;
}
/********************************* RT-Thread Ethernet interface end **************************************/

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

        result = spi_wifi_transfer(&rw009_wifi_device);

        if (result == RT_EOK)
        {
            rt_event_send(&spi_wifi_data_event, 1);
        }
    }
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rw009_ops =
{
    rw009_wifi_init,
    rw009_wifi_open,
    rw009_wifi_close,
    rw009_wifi_read,
    rw009_wifi_write,
    rw009_wifi_control
};
#endif

rt_err_t rt_hw_wifi_init(const char *spi_device_name, wifi_mode_t mode)
{
    /* align and struct size check. */
    RT_ASSERT( (SPI_MAX_DATA_LEN & 0x03) == 0);
    RT_ASSERT( sizeof(struct rw009_resp) <= SPI_MAX_DATA_LEN);

    memset(&rw009_wifi_device, 0, sizeof(struct rw009_wifi));

    rw009_wifi_device.rt_spi_device = (struct rt_spi_device *)rt_device_find(spi_device_name);

    if (rw009_wifi_device.rt_spi_device == RT_NULL)
    {
        SPI_DEBUG("spi device %s not found!\r\n", spi_device_name);
        return -RT_ENOSYS;
    }

    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0. */
        cfg.max_hz = 15 * 1000000; /* 10M */
        rt_spi_configure(rw009_wifi_device.rt_spi_device, &cfg);
    }

#ifdef RT_USING_DEVICE_OPS
    rw009_wifi_device.parent.parent.ops        = &rw009_ops;
#else
    rw009_wifi_device.parent.parent.init       = rw009_wifi_init;
    rw009_wifi_device.parent.parent.open       = rw009_wifi_open;
    rw009_wifi_device.parent.parent.close      = rw009_wifi_close;
    rw009_wifi_device.parent.parent.read       = rw009_wifi_read;
    rw009_wifi_device.parent.parent.write      = rw009_wifi_write;
    rw009_wifi_device.parent.parent.control    = rw009_wifi_control;
#endif
    rw009_wifi_device.parent.parent.user_data  = RT_NULL;

    rw009_wifi_device.parent.eth_rx     = rw009_wifi_rx;
    rw009_wifi_device.parent.eth_tx     = rw009_wifi_tx;

    rt_mp_init(&rw009_wifi_device.spi_tx_mp,
               "spi_tx",
               &rw009_wifi_device.spi_tx_mempool[0],
               sizeof(rw009_wifi_device.spi_tx_mempool),
               sizeof(struct spi_data_packet));

    rt_mp_init(&rw009_wifi_device.spi_rx_mp,
               "spi_rx",
               &rw009_wifi_device.spi_rx_mempool[0],
               sizeof(rw009_wifi_device.spi_rx_mempool),
               sizeof(struct spi_data_packet));

    rt_mb_init(&rw009_wifi_device.spi_tx_mb,
               "spi_tx",
               &rw009_wifi_device.spi_tx_mb_pool[0],
               SPI_TX_POOL_SIZE,
               RT_IPC_FLAG_PRIO);

    rt_mb_init(&rw009_wifi_device.eth_rx_mb,
               "eth_rx",
               &rw009_wifi_device.eth_rx_mb_pool[0],
               SPI_TX_POOL_SIZE,
               RT_IPC_FLAG_PRIO);

    rt_mb_init(&rw009_wifi_device.rw009_cmd_mb,
               "wifi_cmd",
               &rw009_wifi_device.rw009_cmd_mb_pool[0],
               sizeof(rw009_wifi_device.rw009_cmd_mb_pool) / 4,
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
        rw009_cmd_init init;
        init.mode = mode;
        WIFI_DEBUG("wifi_control RW009_CMD_INIT\n");
        rw009_wifi_control((rt_device_t)&rw009_wifi_device,
                           RW009_CMD_INIT,
                           (void *)&init); // 0: firmware, 1: STA, 2:AP

    }

    /* register eth device */
    eth_device_init(&(rw009_wifi_device.parent), "w0");
    eth_device_linkchange(&rw009_wifi_device.parent, RT_FALSE);

    return RT_EOK;
}

void spi_wifi_isr(int vector)
{
    /* enter interrupt */
    rt_interrupt_enter();

    SPI_DEBUG("spi_wifi_isr\n");
    rt_event_send(&spi_wifi_data_event, 1);

    /* leave interrupt */
    rt_interrupt_leave();
}

/********************************* RW009 tools **************************************/
rt_err_t rw009_join(const char * SSID, const char * passwd)
{
    rt_err_t result;
    rt_device_t wifi_device;
    rw009_cmd_easy_join easy_join;

    wifi_device = rt_device_find("w0");
    if(wifi_device == RT_NULL)
        return -RT_ENOSYS;

    strncpy( easy_join.ssid, SSID, sizeof(easy_join.ssid) );
    strncpy( easy_join.passwd, passwd, sizeof(easy_join.passwd) );

    result = rt_device_control(wifi_device,
                               RW009_CMD_EASY_JOIN,
                               (void *)&easy_join);

    return result;
}

rt_err_t rw009_softap(const char * SSID, const char * passwd,uint32_t security,uint32_t channel)
{
    rt_err_t result;
    rt_device_t wifi_device;
    rw009_cmd_softap softap;

    wifi_device = rt_device_find("w0");
    if(wifi_device == RT_NULL)
        return -RT_ENOSYS;

    strncpy( softap.ssid, SSID, sizeof(softap.ssid) );
    strncpy( softap.passwd, passwd, sizeof(softap.passwd) );

    softap.security = security;
    softap.channel = channel;
    result = rt_device_control(wifi_device,
                               RW009_CMD_SOFTAP,
                               (void *)&softap);

    return result;
}

int32_t rw009_rssi(void)
{
    rt_err_t result;
    struct rw009_wifi * wifi_device;

    wifi_device = (struct rw009_wifi *)rt_device_find("w0");

    if(wifi_device == RT_NULL)
        return 0;

    if(wifi_device->active == 0)
        return 0;

    // SCAN
    result = rt_device_control((rt_device_t)wifi_device,
                               RW009_CMD_RSSI,
                               RT_NULL);

    if(result == RT_EOK)
    {
        return wifi_device->ap_info.rssi;
    }

    return 0;
}

#ifdef RT_USING_FINSH
#include <finsh.h>

static rt_err_t rw009_scan(void)
{
    rt_err_t result;
    struct rw009_wifi * wifi_device;

    wifi_device = (struct rw009_wifi *)rt_device_find("w0");

    rt_kprintf("\nCMD RW009_CMD_SCAN \n");
    result = rt_device_control((rt_device_t)wifi_device,
                               RW009_CMD_SCAN,
                               RT_NULL);

    rt_kprintf("CMD RW009_CMD_SCAN result:%d\n", result);

    if(result == RT_EOK)
    {
        uint32_t i;
        rw009_ap_info *ap_info;

        for(i=0; i<wifi_device->ap_scan_count; i++)
        {
            ap_info = &wifi_device->ap_scan[i];
            rt_kprintf("AP #%02d SSID: %-32.32s\n", i, ap_info->ssid );
        }
    }

    return result;
}
FINSH_FUNCTION_EXPORT(rw009_scan, SACN and list AP.);
FINSH_FUNCTION_EXPORT(rw009_join, RW009 join to AP.);
FINSH_FUNCTION_EXPORT(rw009_rssi, get RW009 current AP rssi.);

#endif // RT_USING_FINSH
