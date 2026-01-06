/*
 * Copyright (c) 2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2025-3-31    Jiading     Initial version
 */

#include <rtdevice.h>

#ifdef BSP_USING_TSW
#include <rtdbg.h>
#include "drv_tsw.h"
#include "board.h"

#if defined(BSP_USING_TSW_PHY_RTL8211)
#include "hpm_rtl8211.h"
#endif

ATTR_PLACE_AT_NONCACHEABLE_BSS_WITH_ALIGNMENT(TSW_SOC_DATA_BUS_WIDTH) uint8_t send_buff[TSW_SEND_DESC_COUNT][TSW_SEND_BUFF_LEN];
ATTR_PLACE_AT_NONCACHEABLE_BSS_WITH_ALIGNMENT(TSW_SOC_DATA_BUS_WIDTH) uint8_t recv_buff[TSW_RECV_DESC_COUNT][TSW_RECV_BUFF_LEN];
ATTR_PLACE_AT_NONCACHEABLE_BSS_WITH_ALIGNMENT(TSW_SOC_DATA_BUS_WIDTH) tsw_frame_t frame[TSW_FRAME_BUFF_COUNT];

struct eth_device eth0_dev;
static tsw_device tsw0_dev;

static tsw_buff_config_t tsw_rx_buff_cfg = {.buffer = (uint32_t)recv_buff,
                                            .count  = TSW_RECV_DESC_COUNT,
                                            .size   = TSW_RECV_BUFF_LEN
                                           };

static tsw_buff_config_t tsw_tx_buff_cfg = {.buffer = (uint32_t)send_buff,
                                            .count  = TSW_SEND_DESC_COUNT,
                                            .size   = TSW_SEND_BUFF_LEN
                                           };

static hpm_tsw_t tsw = {.name            = "E0",
                        .base            = BOARD_TSW,
                        .port            = BOARD_TSW_PORT,
                        .irq_num         = IRQn_TSW_0,
                        .inf             = BOARD_TSW_PORT_ITF,
                        .eth_dev         = &eth0_dev,
                        .tsw_dev         = &tsw0_dev,
                        .rx_buff_cfg     = &tsw_rx_buff_cfg,
                        .tx_buff_cfg     = &tsw_tx_buff_cfg,
                        .tx_delay        = BOARD_TSW_PORT3_RGMII_TX_DLY,
                        .rx_delay        = BOARD_TSW_PORT3_RGMII_RX_DLY
                       };

mac_init_t mac_init[] = {
    {MAC0_ADDR0, MAC0_ADDR1, MAC0_ADDR2, MAC0_ADDR3, MAC0_ADDR4, MAC0_ADDR5}
};

static hpm_tsw_t *s_geths[] = {
    &tsw
};

ATTR_WEAK rt_err_t tsw_get_mac_address(TSW_Type *ptr, uint8_t *mac)
{
    /* load MAC address from MACRO definitions */
    SMEMCPY(mac, &mac_init[0], TSW_MAC_COUNT);

    return RT_EOK;
}

static rt_err_t hpm_tsw_init(tsw_device *init)
{
   tsw_dma_config_t config;
   uint8_t *ptx, *prx;
   rtl8211_config_t phy_config;

   /* Set RGMII clock delay */
   if (init->media_interface == tsw_port_phy_itf_rgmii) {
       tsw_set_port_clock_delay(init->instance, init->port, init->tx_delay, init->rx_delay);
   }

   /* Disable all MACs(TX/RX) */
   tsw_ep_disable_all_mac_ctrl(init->instance, tsw_mac_type_emac);

   /* Set MAC Address */
   tsw_ep_set_mac_addr(init->instance, init->port, init->mac, true);

   /* Set MAC Mode: GMII, CLKSEL: REFCLK */
   tsw_ep_set_mac_mode(init->instance, init->port, init->media_interface == tsw_port_phy_itf_rgmii ? tsw_mac_mode_gmii : tsw_mac_mode_mii);

   /* Set port PHY interface */
   tsw_set_port_interface(init->instance, init->port, init->media_interface);

   /* Enable all MACs(TX/RX) */
   tsw_ep_enable_all_mac_ctrl(init->instance, tsw_mac_type_emac);

   /* Clear CAM */
   tsw_clear_cam(init->instance);

   /* Wait for CAM clearing completion */
   rt_thread_mdelay(10);

   /* Enable VLAN-ID 1 at all ports */
   tsw_set_cam_vlan_port(init->instance);

   /* Get the default DMA config */
   tsw_get_default_dma_config(&config);

   /* Initialize DMA for sending */
   tsw_init_send(init->instance, &config);

   ptx = (uint8_t *)(init->tx_buff_cfg->buffer);
   for (uint8_t i = 0; i < init->tx_buff_cfg->count; i++) {
       ptx[i * init->tx_buff_cfg->size] = init->port + 1;
   }

   /* Initialize DMA for receiving */
   config.irq = true;
   tsw_init_recv(init->instance, &config);

   prx = (uint8_t *)(init->rx_buff_cfg->buffer);
   for (uint8_t i = 0; i < init->rx_buff_cfg->count; i++) {
       tsw_commit_recv_desc(init->instance, &prx[i * init->rx_buff_cfg->size], init->rx_buff_cfg->size, i);
   }

   /* Enable TSW IRQ */
   intc_m_enable_irq(init->irq_number);

   return RT_EOK;
}

static rt_err_t rt_hpm_tsw_init(rt_device_t dev)
{
    uint8_t mac[TSW_MAC_COUNT];

    tsw_device *tsw_dev = (tsw_device *)dev->user_data;

    /* Initialize GPIOs */
    board_init_tsw_pins(tsw_dev->instance);

    /* Reset an TSW PHY */
    board_reset_tsw_phy(tsw_dev->instance, tsw_dev->port);

    /* Get MAC address */
    tsw_get_mac_address(tsw_dev->instance, mac);

    /* Set mac0 address */
    memcpy(tsw_dev->mac, mac, TSW_MAC_COUNT);

    /* Initialize MAC and DMA */
    if (hpm_tsw_init(tsw_dev) == 0) {
        LOG_D("Ethernet control initialize successfully\n");
        return RT_EOK;
    } else {
        LOG_D("Ethernet control initialize unsuccessfully\n");
        return -RT_ERROR;
    }
}

static rt_err_t rt_hpm_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_hpm_tsw_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rt_hpm_tsw_read(rt_device_t dev, rt_off_t pos, void * buffer, rt_size_t size)
{
    return 0;
}

static rt_ssize_t rt_hpm_tsw_write(rt_device_t dev, rt_off_t pos, const void * buffer, rt_size_t size)
{
    return 0;
}

static rt_err_t rt_hpm_tsw_control(rt_device_t dev, int cmd, void * args)
{
    uint8_t *mac = (uint8_t *)args;
    tsw_device *tsw_dev = (tsw_device *)dev->user_data;

    switch (cmd) {
    case NIOCTL_GADDR:
        if (args != NULL) {
            tsw_get_mac_address(tsw_dev->instance, (uint8_t *)mac);
            SMEMCPY(args, mac, TSW_MAC_COUNT);
        } else {
            return -RT_ERROR;
        }
        break;
    default:
        break;
    }

    return RT_EOK;
}

static rt_err_t rt_hpm_tsw_tx(rt_device_t dev, struct pbuf * p)
{
    struct pbuf *q;
    static uint32_t i = 0;
    uint32_t id;
    uint32_t length = TSW_SOC_SWITCH_HEADER_LEN;
    tsw_device *tsw_dev = (tsw_device *)dev->user_data;
    uint8_t *ptx = ((uint8_t *)tsw_dev->tx_buff_cfg->buffer);

    id = i++ % TSW_SOC_DMA_MAX_DESC_COUNT;

    for (q = p; q != NULL; q = q->next) {
        SMEMCPY(&ptx[id * tsw_dev->tx_buff_cfg->size + TSW_SOC_SWITCH_HEADER_LEN], q->payload, q->len);
        length += q->len;
    }

    tsw_send_frame(tsw_dev->instance, &ptx[id * tsw_dev->tx_buff_cfg->size], length, id);

    return ERR_OK;
}

static struct pbuf *rt_hpm_tsw_rx(rt_device_t dev)
{
    struct pbuf *p = NULL, *q;
    static uint8_t idx = 0;
    tsw_device *tsw_dev = (tsw_device *)dev->user_data;
    uint8_t *prx = (uint8_t *)tsw_dev->rx_buff_cfg->buffer;

    if (frame[idx].length > TSW_SOC_SWITCH_HEADER_LEN) {
        /* Allocate a pbuf chain of pbufs from the lwIP buffer pool */
        p = pbuf_alloc(PBUF_RAW, frame[idx].length - TSW_SOC_SWITCH_HEADER_LEN, PBUF_POOL);
        if (p != NULL) {
            for (q = p; q != NULL; q = q->next) {
                /* pass the buffer to pbuf */
                frame[idx].buffer = &prx[frame[idx].id * tsw_dev->rx_buff_cfg->size];
                SMEMCPY(q->payload, &frame[idx].buffer[TSW_SOC_SWITCH_HEADER_LEN], q->len);
                frame[idx].length = 0;
                idx++;
                idx %= TSW_FRAME_BUFF_COUNT;
            }
        }
    }

    return p;
}

static void eth_rx_callback(struct eth_device* dev)
{
    rt_err_t result;
    result = eth_device_ready(dev);
    if (result != RT_EOK) {
        LOG_I("Receive callback error = %d\n", result);
    }
}

void isr_tsw(hpm_tsw_t *obj)
{
   static int idx = 0;
   uint8_t *prx = (uint8_t *)obj->tsw_dev->rx_buff_cfg->buffer;

   tsw_recv_frame(obj->base, &frame[idx]);
   tsw_commit_recv_desc(obj->base, &prx[idx * obj->tsw_dev->rx_buff_cfg->size], TSW_RECV_BUFF_LEN, idx);
   idx++;
   idx %= TSW_FRAME_BUFF_COUNT;
   eth_rx_callback(obj->eth_dev);
}

SDK_DECLARE_EXT_ISR_M(IRQn_TSW_0, isr_tsw_port_cpu)
void isr_tsw_port_cpu(void)
{
    isr_tsw(&tsw);
}

int rt_hw_tsw_init(void)
{
    rt_err_t err = RT_ERROR;

    for (uint32_t i = 0; i < ARRAY_SIZE(s_geths); i++) {
        /* Set TX & RX buffer config */
        s_geths[i]->tsw_dev->tx_buff_cfg = s_geths[i]->tx_buff_cfg;
        s_geths[i]->tsw_dev->rx_buff_cfg = s_geths[i]->rx_buff_cfg;

        /* Set media interface */
        s_geths[i]->tsw_dev->media_interface = s_geths[i]->inf;

        /* Set instance */
        s_geths[i]->tsw_dev->instance = s_geths[i]->base;

        /* Set Port */
        s_geths[i]->tsw_dev->port = s_geths[i]->port;

        /* Set TX/RX delay */
        s_geths[i]->tsw_dev->tx_delay = s_geths[i]->tx_delay;
        s_geths[i]->tsw_dev->rx_delay = s_geths[i]->rx_delay;

        /* Set IRQ number */
        s_geths[i]->tsw_dev->irq_number = s_geths[i]->irq_num;

        /* Set the parent parameters */
        s_geths[i]->eth_dev->parent.init      = rt_hpm_tsw_init;
        s_geths[i]->eth_dev->parent.close     = rt_hpm_tsw_close;
        s_geths[i]->eth_dev->parent.read      = rt_hpm_tsw_read;
        s_geths[i]->eth_dev->parent.write     = rt_hpm_tsw_write;
        s_geths[i]->eth_dev->parent.control   = rt_hpm_tsw_control;

        s_geths[i]->eth_dev->parent.user_data = s_geths[i]->tsw_dev;

        s_geths[i]->eth_dev->eth_rx = rt_hpm_tsw_rx;
        s_geths[i]->eth_dev->eth_tx = rt_hpm_tsw_tx;

        err = eth_device_init(s_geths[i]->eth_dev, s_geths[i]->name);

        if (RT_EOK == err) {
            LOG_D("Ethernet device %d initialize successfully!\n", i);
        } else {
            LOG_D("Ethernet device %d initialize unsuccessfully!\n");
            return err;
        }
    }

    return err;
}
INIT_DEVICE_EXPORT(rt_hw_tsw_init);
#endif /* BSP_USING_TSW */
