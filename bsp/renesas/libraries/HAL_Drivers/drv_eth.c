/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-19     SummerGift   first version
 * 2018-12-25     zylx         fix some bugs
 * 2019-06-10     SummerGift   optimize PHY state detection process
 * 2019-09-03     xiaofan      optimize link change detection process
 */

#include "drv_config.h"
#include "drv_eth.h"
#include <hal_data.h>
#include <netif/ethernetif.h>
#include <lwipopts.h>

/*
* Emac driver uses CubeMX tool to generate emac and phy's configuration,
* the configuration files can be found in CubeMX_Config folder.
*/

/* debug option */
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP
#define MINIMUM_ETHERNET_FRAME_SIZE               (60U)
#define ETH_MAX_PACKET_SIZE 1514
#define ETH_RX_BUF_SIZE ETH_MAX_PACKET_SIZE
#define ETH_TX_BUF_SIZE ETH_MAX_PACKET_SIZE
//#define DRV_DEBUG
#define LOG_TAG             "drv.eth"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

#define MAX_ADDR_LEN 6

#undef PHY_FULL_DUPLEX
#define PHY_LINK         (1 << 0)
#define PHY_100M         (1 << 1)
#define PHY_FULL_DUPLEX  (1 << 2)

struct rt_ra6m3_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;
#ifndef PHY_USING_INTERRUPT_MODE
    rt_timer_t poll_link_timer;
#endif

    /* interface address info, hw address */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];
};

static rt_uint8_t *Rx_Buff, *Tx_Buff;
//static  ETH_HandleTypeDef EthHandle;
static struct rt_ra6m3_eth ra6m3_eth_device;

#if defined(ETH_RX_DUMP) || defined(ETH_TX_DUMP)
#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char *)ptr;
    int i, j;

    for (i = 0; i < buflen; i += 16)
    {
        rt_kprintf("%08X: ", i);

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                rt_kprintf("%02X ", buf[i + j]);
            else
                rt_kprintf("   ");
        rt_kprintf(" ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                rt_kprintf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
        rt_kprintf("\n");
    }
}
#endif

extern void phy_reset(void);
/* EMAC initialization function */
static rt_err_t rt_ra6m3_eth_init(rt_device_t dev)
{
    fsp_err_t res;

    res = R_ETHER_Open(&g_ether0_ctrl, &g_ether0_cfg);
    if (res != FSP_SUCCESS)
        LOG_W("R_ETHER_Open failed!, res = %d", res);
    return RT_EOK;
}

static rt_err_t rt_ra6m3_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("emac open");
    return RT_EOK;
}

static rt_err_t rt_ra6m3_eth_close(rt_device_t dev)
{
    LOG_D("emac close");
    return RT_EOK;
}

static rt_ssize_t rt_ra6m3_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("emac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_ra6m3_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("emac write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_ra6m3_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args)
        {
            SMEMCPY(args, ra6m3_eth_device.dev_addr, 6);
        }
        else
        {
            return -RT_ERROR;
        }
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* ethernet device interface */
/* transmit data*/
rt_err_t rt_ra6m3_eth_tx(rt_device_t dev, struct pbuf *p)
{
    fsp_err_t res;
    struct pbuf *q;
    uint8_t *buffer = Tx_Buff;
    uint32_t framelength = 0;
    uint32_t bufferoffset = 0;
    uint32_t byteslefttocopy = 0;
    uint32_t payloadoffset = 0;
    bufferoffset = 0;

    LOG_D("send frame len : %d", p->tot_len);

    /* copy frame from pbufs to driver buffers */
    for (q = p; q != NULL; q = q->next)
    {
        /* Get bytes in current lwIP buffer */
        byteslefttocopy = q->len;
        payloadoffset = 0;

        /* Check if the length of data to copy is bigger than Tx buffer size*/
        while ((byteslefttocopy + bufferoffset) > ETH_TX_BUF_SIZE)
        {
            /* Copy data to Tx buffer*/
            SMEMCPY((uint8_t *)((uint8_t *)buffer + bufferoffset), (uint8_t *)((uint8_t *)q->payload + payloadoffset), (ETH_TX_BUF_SIZE - bufferoffset));

            byteslefttocopy = byteslefttocopy - (ETH_TX_BUF_SIZE - bufferoffset);
            payloadoffset = payloadoffset + (ETH_TX_BUF_SIZE - bufferoffset);
            framelength = framelength + (ETH_TX_BUF_SIZE - bufferoffset);
            bufferoffset = 0;
        }

        /* Copy the remaining bytes */
        SMEMCPY((uint8_t *)((uint8_t *)buffer + bufferoffset), (uint8_t *)((uint8_t *)q->payload + payloadoffset), byteslefttocopy);
        bufferoffset = bufferoffset + byteslefttocopy;
        framelength = framelength + byteslefttocopy;
    }


#ifdef ETH_TX_DUMP
    dump_hex(buffer, p->tot_len);
#endif
#ifdef ETH_RX_DUMP
    if (p)
    {
        LOG_E("******p buf frame *********");
        for (q = p; q != NULL; q = q->next)
        {
            dump_hex(q->payload, q->len);
        }

    }
#endif
    res = R_ETHER_Write(&g_ether0_ctrl, buffer, p->tot_len);//>MINIMUM_ETHERNET_FRAME_SIZE?p->tot_len:MINIMUM_ETHERNET_FRAME_SIZE);
    if (res != FSP_SUCCESS)
        LOG_W("R_ETHER_Write failed!, res = %d", res);
    return RT_EOK;
}

/* receive data*/
struct pbuf *rt_ra6m3_eth_rx(rt_device_t dev)
{
    struct pbuf *p = NULL;
    struct pbuf *q = NULL;
    uint32_t len = 0;
    uint8_t *buffer = Rx_Buff;
    fsp_err_t res;

    res = R_ETHER_Read(&g_ether0_ctrl, buffer, &len);
    if (res != FSP_SUCCESS)
        LOG_D("R_ETHER_Read failed!, res = %d", res);

    uint32_t bufferoffset = 0;
    uint32_t payloadoffset = 0;
    uint32_t byteslefttocopy = 0;

    LOG_D("receive frame len : %d", len);

    if (len > 0)
    {
        /* We allocate a pbuf chain of pbufs from the Lwip buffer pool */
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    }

#ifdef ETH_RX_DUMP
    if (p)
    {
        dump_hex(buffer, p->tot_len);
    }
#endif

    if (p != NULL)
    {
        bufferoffset = 0;
        for (q = p; q != NULL; q = q->next)
        {
            byteslefttocopy = q->len;
            payloadoffset = 0;

            /* Check if the length of bytes to copy in current pbuf is bigger than Rx buffer size*/
            while ((byteslefttocopy + bufferoffset) > ETH_RX_BUF_SIZE)
            {
                /* Copy data to pbuf */
                SMEMCPY((uint8_t *)((uint8_t *)q->payload + payloadoffset), (uint8_t *)((uint8_t *)buffer + bufferoffset), (ETH_RX_BUF_SIZE - bufferoffset));

                byteslefttocopy = byteslefttocopy - (ETH_RX_BUF_SIZE - bufferoffset);
                payloadoffset = payloadoffset + (ETH_RX_BUF_SIZE - bufferoffset);
                bufferoffset = 0;
            }
            /* Copy remaining data in pbuf */
            SMEMCPY((uint8_t *)((uint8_t *)q->payload + payloadoffset), (uint8_t *)((uint8_t *)buffer + bufferoffset), byteslefttocopy);
            bufferoffset = bufferoffset + byteslefttocopy;
        }
    }

#ifdef ETH_RX_DUMP
    if (p)
    {
        LOG_E("******p buf frame *********");
        for (q = p; q != NULL; q = q->next)
        {
            dump_hex(q->payload, q->len);
        }

    }
#endif


    return p;
}

static void phy_linkchange()
{
    static uint32_t phy_speed = 0;
    uint32_t phy_speed_new = 0;
    fsp_err_t res;

    uint32_t p_local_pause;
    uint32_t p_partner_pause;

    res = R_ETHER_LinkProcess(&g_ether0_ctrl);
    if (res != FSP_SUCCESS)
        LOG_D("R_ETHER_LinkProcess failed!, res = %d", res);

    res = R_ETHER_PHY_LinkStatusGet(&g_ether_phy0_ctrl);
    if (res != FSP_SUCCESS)
        LOG_D("R_ETHER_PHY_LinkStatusGet failed!, res = %d", res);

    if(res == FSP_ERR_ETHER_PHY_ERROR_LINK)
    {
        LOG_D("link down");
        eth_device_linkchange(&ra6m3_eth_device.parent, RT_FALSE);
        return;
    }

    res = R_ETHER_PHY_LinkPartnerAbilityGet(&g_ether_phy0_ctrl,
                                        &phy_speed_new,
                                        &p_local_pause,
                                        &p_partner_pause);
    if (res != FSP_SUCCESS)
    LOG_D("R_ETHER_PHY_LinkPartnerAbilityGet failed!, res = %d", res);

    if(res == FSP_ERR_ETHER_PHY_ERROR_LINK)
    {
        LOG_I("link down");
        eth_device_linkchange(&ra6m3_eth_device.parent, RT_FALSE);
        return;
    }

    if (phy_speed != phy_speed_new)
    {
        phy_speed = phy_speed_new;
        if (phy_speed != ETHER_PHY_LINK_SPEED_NO_LINK)
        {
            LOG_D("link up");
            if (phy_speed == ETHER_PHY_LINK_SPEED_100H || phy_speed == ETHER_PHY_LINK_SPEED_100F)
            {
                LOG_D("100Mbps");
            }
            else
            {
                LOG_D("10Mbps");
            }

            if (phy_speed == ETHER_PHY_LINK_SPEED_100F || phy_speed == ETHER_PHY_LINK_SPEED_10F)
            {
                LOG_D("full-duplex");
            }
            else
            {
                LOG_D("half-duplex");
            }

            /* send link up. */
            LOG_I("link up");
            eth_device_linkchange(&ra6m3_eth_device.parent, RT_TRUE);
        }
        else
        {
            LOG_D("link down");
            eth_device_linkchange(&ra6m3_eth_device.parent, RT_FALSE);
        }
    }
}

void user_ether0_callback(ether_callback_args_t * p_args)
{
    rt_err_t result;
        result = eth_device_ready(&(ra6m3_eth_device.parent));
        if (result != RT_EOK)
            rt_kprintf("RX err =%d\n", result);
}

/* Register the EMAC device */
static int rt_hw_ra6m3_eth_init(void)
{
    rt_err_t state = RT_EOK;

    /* Prepare receive and send buffers */
    Rx_Buff = (rt_uint8_t *)rt_calloc(1, ETH_MAX_PACKET_SIZE);
    if (Rx_Buff == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }

    Tx_Buff = (rt_uint8_t *)rt_calloc(1, ETH_MAX_PACKET_SIZE);
    if (Tx_Buff == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }

    /* OUI 00-80-E1 STMICROELECTRONICS. */
    ra6m3_eth_device.dev_addr[0] = 0x00;
    ra6m3_eth_device.dev_addr[1] = 0x80;
    ra6m3_eth_device.dev_addr[2] = 0xE1;
    /* generate MAC addr from 96bit unique ID (only for test). */
    ra6m3_eth_device.dev_addr[3] = (10 + 4);
    ra6m3_eth_device.dev_addr[4] = (10 + 2);
    ra6m3_eth_device.dev_addr[5] = (10 + 0);

    ra6m3_eth_device.parent.parent.init       = rt_ra6m3_eth_init;
    ra6m3_eth_device.parent.parent.open       = rt_ra6m3_eth_open;
    ra6m3_eth_device.parent.parent.close      = rt_ra6m3_eth_close;
    ra6m3_eth_device.parent.parent.read       = rt_ra6m3_eth_read;
    ra6m3_eth_device.parent.parent.write      = rt_ra6m3_eth_write;
    ra6m3_eth_device.parent.parent.control    = rt_ra6m3_eth_control;
    ra6m3_eth_device.parent.parent.user_data  = RT_NULL;

    ra6m3_eth_device.parent.eth_rx     = rt_ra6m3_eth_rx;
    ra6m3_eth_device.parent.eth_tx     = rt_ra6m3_eth_tx;

    /* register eth device */
    state = eth_device_init(&(ra6m3_eth_device.parent), "e0");
    if (RT_EOK == state)
    {
        LOG_D("emac device init success");
    }
    else
    {
        LOG_E("emac device init faild: %d", state);
        state = -RT_ERROR;
        goto __exit;
    }

    ra6m3_eth_device.poll_link_timer = rt_timer_create("phylnk", (void (*)(void*))phy_linkchange,
                                        NULL, RT_TICK_PER_SECOND, RT_TIMER_FLAG_PERIODIC);
    if (!ra6m3_eth_device.poll_link_timer || rt_timer_start(ra6m3_eth_device.poll_link_timer) != RT_EOK)
    {
        LOG_E("Start link change detection timer failed");
    }
__exit:
    if (state != RT_EOK)
    {
        if (Rx_Buff)
        {
            rt_free(Rx_Buff);
        }

        if (Tx_Buff)
        {
            rt_free(Tx_Buff);
        }

    }

    return state;
}
INIT_DEVICE_EXPORT(rt_hw_ra6m3_eth_init);
