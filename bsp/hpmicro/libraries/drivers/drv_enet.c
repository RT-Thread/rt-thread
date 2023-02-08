/*
 * Copyright (c) 2021 - 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-01-11   hpmicro     First version
 * 2022-07-10   hpmicro     Driver optimization for multiple instances
 */

#include <rtdevice.h>

#ifdef BSP_USING_ETH
#include <rtdbg.h>
#include <netif/ethernetif.h>
#include "board.h"
#include "drv_enet.h"
#include "hpm_soc_feature.h"
#include "hpm_enet_soc_drv.h"
#include "hpm_enet_drv.h"

#define ETH_DEBUG

#ifdef BSP_USING_ETH0

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_DESC_ADDR_ALIGNMENT)
__RW enet_rx_desc_t enet0_dma_rx_desc_tab[ENET0_RX_BUFF_COUNT] ; /* Ethernet0 Rx DMA Descriptor */

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_DESC_ADDR_ALIGNMENT)
__RW enet_tx_desc_t enet0_dma_tx_desc_tab[ENET0_TX_BUFF_COUNT] ; /* Ethernet0 Tx DMA Descriptor */

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_BUFF_ADDR_ALIGNMENT)
__RW uint8_t enet0_rx_buff[ENET0_RX_BUFF_COUNT][ENET0_RX_BUFF_SIZE]; /* Ethernet0 Receive Buffer */

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_BUFF_ADDR_ALIGNMENT)
__RW uint8_t enet0_tx_buff[ENET0_TX_BUFF_COUNT][ENET0_TX_BUFF_SIZE]; /* Ethernet0 Transmit Buffer */

struct eth_device eth0_dev;
static enet_device enet0_dev;
static enet_buff_config_t enet0_rx_buff_cfg = {.buffer = (uint32_t)enet0_rx_buff,
                                               .count  = ENET0_RX_BUFF_COUNT,
                                               .size   = ENET0_RX_BUFF_SIZE
                                              };

static enet_buff_config_t enet0_tx_buff_cfg = {.buffer = (uint32_t)enet0_tx_buff,
                                               .count  = ENET0_TX_BUFF_COUNT,
                                               .size   = ENET0_TX_BUFF_SIZE
                                              };

static enet_ptp_time_t ptp_timestamp0 = {0, 0};
static enet_ptp_config_t ptp_config0 = {.sub_sec_count_res = enet_ptp_count_res_low,
                                        .update_method = enet_ptp_time_fine_update,
                                        .addend = 0xffffffff,
                                       };

static hpm_enet_t enet0 = {.name            = "ETH0",
                           .base            = HPM_ENET0,
                           .irq_num         = IRQn_ENET0,
                           .inf             = BOARD_ENET0_INF,
                           .eth_dev         = &eth0_dev,
                           .enet_dev        = &enet0_dev,
                           .rx_buff_cfg     = &enet0_rx_buff_cfg,
                           .tx_buff_cfg     = &enet0_tx_buff_cfg,
                           .dma_rx_desc_tab = enet0_dma_rx_desc_tab,
                           .dma_tx_desc_tab = enet0_dma_tx_desc_tab,
                           .tx_delay        = BOARD_ENET0_TX_DLY,
                           .rx_delay        = BOARD_ENET0_RX_DLY,
                           .ptp_enable      = true,
                           .ptp_clk_src     = BOARD_ENET0_PTP_CLOCK,
                           .ptp_config      = &ptp_config0,
                           .ptp_timestamp   = &ptp_timestamp0
                          };
#endif

#ifdef BSP_USING_ETH1

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_DESC_ADDR_ALIGNMENT)
__RW enet_rx_desc_t enet1_dma_rx_desc_tab[ENET1_RX_BUFF_COUNT]; /* Ethernet1 Rx DMA Descriptor */

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_DESC_ADDR_ALIGNMENT)
__RW enet_tx_desc_t enet1_dma_tx_desc_tab[ENET1_TX_BUFF_COUNT]; /* Ethernet1 Tx DMA Descriptor */

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_BUFF_ADDR_ALIGNMENT)
__RW uint8_t enet1_rx_buff[ENET1_RX_BUFF_COUNT][ENET1_RX_BUFF_SIZE]; /* Ethernet1 Receive Buffer */

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_BUFF_ADDR_ALIGNMENT)
__RW uint8_t enet1_tx_buff[ENET1_TX_BUFF_COUNT][ENET1_TX_BUFF_SIZE]; /* Ethernet1 Transmit Buffer */

struct eth_device eth1_dev;
static enet_device enet1_dev;
static enet_buff_config_t enet1_rx_buff_cfg = {.buffer = (uint32_t)enet1_rx_buff,
                                               .count  = ENET1_RX_BUFF_COUNT,
                                               .size   = ENET1_RX_BUFF_SIZE
                                              };

static enet_buff_config_t enet1_tx_buff_cfg = {.buffer = (uint32_t)enet1_tx_buff,
                                               .count  = ENET1_TX_BUFF_COUNT,
                                               .size   = ENET1_TX_BUFF_SIZE
                                              };

static enet_ptp_time_t ptp_timestamp1 = {0, 0};
static enet_ptp_config_t ptp_config1 = {.sub_sec_count_res = enet_ptp_count_res_low,
                                        .update_method = enet_ptp_time_fine_update,
                                        .addend = 0xffffffff,
                                       };

static hpm_enet_t enet1 = {.name            = "ETH1",
                           .base            = HPM_ENET1,
                           .irq_num         = IRQn_ENET1,
                           .inf             = BOARD_ENET1_INF,
                           .eth_dev         = &eth1_dev,
                           .enet_dev        = &enet1_dev,
                           .rx_buff_cfg     = &enet1_rx_buff_cfg,
                           .tx_buff_cfg     = &enet1_tx_buff_cfg,
                           .dma_rx_desc_tab = enet1_dma_rx_desc_tab,
                           .dma_tx_desc_tab = enet1_dma_tx_desc_tab,
                           .int_refclk      = BOARD_ENET1_INT_REF_CLK,
                           .ptp_enable      = true,
                           .ptp_clk_src     = BOARD_ENET1_PTP_CLOCK,
                           .ptp_config      = &ptp_config1,
                           .ptp_timestamp   = &ptp_timestamp1
                          };

#endif

static hpm_enet_t *s_geths[] = {
#ifdef BSP_USING_ETH0
       &enet0,
#endif

#ifdef BSP_USING_ETH1
       &enet1
#endif
};


static hpm_stat_t hpm_enet_init(enet_device *init)
{
    /* Initialize eth controller */
    enet_controller_init(init->instance, init->media_interface, &init->desc, &init->mac_config, init->mask, init->dis_mask);

    if (init->media_interface == enet_inf_rmii)
    {
        /* Initialize reference clock */
        board_init_enet_rmii_reference_clock(init->instance, init->int_refclk);
        enet_rmii_enable_clock(init->instance, init->int_refclk);
    }

    /* Set RGMII clock delay */
   if (init->media_interface == enet_inf_rgmii)
   {
        enet_rgmii_enable_clock(init->instance);
        enet_rgmii_set_clock_delay(init->instance, init->tx_delay, init->rx_delay);
   }

   if (init->ptp_enable)
   {
       /* initialize Ethernet PTP Module */
       init->ptp_config.ssinc = ENET_ONE_SEC_IN_NANOSEC / clock_get_frequency(init->ptp_clk_src);
       enet_init_ptp(init->instance, &init->ptp_config);

       /* set the initial timestamp */
       enet_set_ptp_timestamp(init->instance, &init->ptp_timestamp);
   }

    /* enable irq */
    intc_m_enable_irq(init->irq_number);
}

static rt_err_t rt_hpm_eth_init(rt_device_t dev)
{
    enet_device *enet_dev = (enet_device *)dev->user_data;

    /* Initialize GPIOs */
    board_init_enet_pins(enet_dev->instance);

    /* Reset an enet PHY */
    board_reset_enet_phy(enet_dev->instance);

    /* Initialize MAC and DMA */
    if (hpm_enet_init(enet_dev) == 0) {
        LOG_D("Ethernet control initialize successfully\n");
    }

    return RT_EOK;
}

static rt_err_t rt_hpm_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_hpm_eth_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rt_hpm_eth_read(rt_device_t dev, rt_off_t pos, void * buffer, rt_size_t size)
{
    return 0;
}

static rt_ssize_t rt_hpm_eth_write(rt_device_t dev, rt_off_t pos, const void * buffer, rt_size_t size)
{
    return 0;
}

static rt_err_t rt_hpm_eth_control(rt_device_t dev, int cmd, void * args)
{
    uint8_t *mac;

    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* read MAC address */
        if (args != NULL)
        {
            mac = (uint8_t *)args;
            mac[0] = MAC_ADDR0;
            mac[1] = MAC_ADDR1;
            mac[2] = MAC_ADDR2;
            mac[3] = MAC_ADDR3;
            mac[4] = MAC_ADDR4;
            mac[5] = MAC_ADDR5;
            SMEMCPY(args, mac, 6);
        }
        else
        {
            return -RT_ERROR;
        }
        break;
    default:
        break;
    }

    return RT_EOK;
}

static rt_err_t rt_hpm_eth_tx(rt_device_t dev, struct pbuf * p)
{
    rt_err_t ret = RT_ERROR;
    uint32_t status;
    enet_device *enet_dev = (enet_device *)dev->user_data;
    uint32_t tx_buff_size = enet_dev->desc.tx_buff_cfg.size;
    struct pbuf *q;
    uint8_t *buffer;
    __IO enet_tx_desc_t *dma_tx_desc;
    uint32_t frame_length = 0;
    uint32_t buffer_offset = 0;
    uint32_t bytes_left_to_copy = 0;
    uint32_t payload_offset = 0;
    enet_tx_desc_t  *tx_desc_list_cur = enet_dev->desc.tx_desc_list_cur;

    dma_tx_desc = tx_desc_list_cur;
    buffer = (uint8_t *)(dma_tx_desc->tdes2_bm.buffer1);
    buffer_offset = 0;

    /* copy frame from pbufs to driver buffers */
    for (q = p; q != NULL; q = q->next)
    {
        /* Get bytes in current lwIP buffer */
        bytes_left_to_copy = q->len;
        payload_offset = 0;

        /* Check if the length of data to copy is bigger than Tx buffer size*/
        while ((bytes_left_to_copy + buffer_offset) > tx_buff_size)
        {
            /* Copy data to Tx buffer*/
            SMEMCPY((uint8_t *)((uint8_t *)buffer + buffer_offset),
                    (uint8_t *)((uint8_t *)q->payload + payload_offset),
                    tx_buff_size - buffer_offset);

            /* Point to next descriptor */
            dma_tx_desc = (enet_tx_desc_t *)(dma_tx_desc->tdes3_bm.next_desc);

            /* Check if the buffer is available */
            if (dma_tx_desc->tdes0_bm.own != 0)
            {
                LOG_E("DMA tx desc buffer is not valid\n");
                return ERR_USE;
            }

            buffer = (uint8_t *)(dma_tx_desc->tdes2_bm.buffer1);

            bytes_left_to_copy = bytes_left_to_copy - (tx_buff_size - buffer_offset);
            payload_offset = payload_offset + (tx_buff_size - buffer_offset);
            frame_length = frame_length + (tx_buff_size - buffer_offset);
            buffer_offset = 0;
        }

        /* Copy the remaining bytes */
        SMEMCPY((uint8_t *)((uint8_t *)buffer + buffer_offset),
                (uint8_t *)((uint8_t *)q->payload + payload_offset),
                bytes_left_to_copy);

        buffer_offset = buffer_offset + bytes_left_to_copy;
        frame_length = frame_length + bytes_left_to_copy;
    }

    /* Prepare transmit descriptors to give to DMA */
    LOG_D("The length of the transmitted frame: %d\n", frame_length);

    frame_length += 4;
    status = enet_prepare_transmission_descriptors(enet_dev->instance, &enet_dev->desc.tx_desc_list_cur, frame_length, enet_dev->desc.tx_buff_cfg.size);
    if (status != ENET_SUCCESS)
    {
        LOG_E("Ethernet controller transmit unsuccessfully: %d\n", status);
    }

    return ERR_OK;
}

static struct pbuf *rt_hpm_eth_rx(rt_device_t dev)
{
    struct pbuf *p = NULL, *q = NULL;
    enet_device *enet_dev = (enet_device *)dev->user_data;
    uint32_t rx_buff_size = enet_dev->desc.rx_buff_cfg.size;
    uint16_t len = 0;
    uint8_t *buffer;
    enet_frame_t frame = {0, 0, 0};
    enet_rx_desc_t *dma_rx_desc;
    uint32_t buffer_offset = 0;
    uint32_t payload_offset = 0;
    uint32_t bytes_left_to_copy = 0;
    uint32_t i = 0;

    /* Get a received frame */
    frame = enet_get_received_frame_interrupt(&enet_dev->desc.rx_desc_list_cur,
                                              &enet_dev->desc.rx_frame_info,
                                              enet_dev->desc.rx_buff_cfg.count);

    /* Obtain the size of the packet and put it into the "len" variable. */
    len = frame.length;
    buffer = (uint8_t *)frame.buffer;

    LOG_D("The current received frame length : %d\n", len);

    if (len > 0)
    {
        /* allocate a pbuf chain of pbufs from the Lwip buffer pool */
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    }

    if (p != NULL)
    {
        dma_rx_desc = frame.rx_desc;
        buffer_offset = 0;
        for (q = p; q != NULL; q = q->next)
        {
            bytes_left_to_copy = q->len;
            payload_offset = 0;

            /* Check if the length of bytes to copy in current pbuf is bigger than Rx buffer size*/
            while ((bytes_left_to_copy + buffer_offset) > rx_buff_size)
            {
                /* Copy data to pbuf */
                SMEMCPY((uint8_t *)((uint8_t *)q->payload + payload_offset), (uint8_t *)((uint8_t *)buffer + buffer_offset), (rx_buff_size - buffer_offset));

                /* Point to next descriptor */
                dma_rx_desc = (enet_rx_desc_t *)(dma_rx_desc->rdes3_bm.next_desc);
                buffer = (uint8_t *)(dma_rx_desc->rdes2_bm.buffer1);

                bytes_left_to_copy = bytes_left_to_copy - (rx_buff_size - buffer_offset);
                payload_offset = payload_offset + (rx_buff_size - buffer_offset);
                buffer_offset = 0;
            }
            /* Copy remaining data in pbuf */
            SMEMCPY((uint8_t *)((uint8_t *)q->payload + payload_offset), (uint8_t *)((uint8_t *)buffer + buffer_offset), bytes_left_to_copy);
            buffer_offset = buffer_offset + bytes_left_to_copy;
        }
    }
    else
    {
        return NULL;
    }

    /* Release descriptors to DMA */
    /* Point to first descriptor */
    dma_rx_desc = frame.rx_desc;

    /* Set Own bit in Rx descriptors: gives the buffers back to DMA */
    for (i = 0; i < enet_dev->desc.rx_frame_info.seg_count; i++)
    {
        dma_rx_desc->rdes0_bm.own = 1;
        dma_rx_desc = (enet_rx_desc_t*)(dma_rx_desc->rdes3_bm.next_desc);
    }

    /* Clear Segment_Count */
    enet_dev->desc.rx_frame_info.seg_count = 0;

    return p;
}

static void eth_rx_callback(struct eth_device* dev)
{
    rt_err_t result;
    result = eth_device_ready(dev);
    if (result != RT_EOK)
    {
        LOG_I("Receive callback error = %d\n", result);
    }
}

void isr_enet(hpm_enet_t *obj)
{
    uint32_t status;

    status = obj->base->DMA_STATUS;

    if (ENET_DMA_STATUS_GLPII_GET(status)) {
        obj->base->DMA_STATUS |= ENET_DMA_STATUS_GLPII_SET(ENET_DMA_STATUS_GLPII_GET(status));
    }

    if (ENET_DMA_STATUS_RI_GET(status)) {
        obj->base->DMA_STATUS |= ENET_DMA_STATUS_RI_SET(ENET_DMA_STATUS_RI_GET(status));
        eth_rx_callback(obj->eth_dev);
    }
}

#ifdef BSP_USING_ETH0
void isr_enet0(void)
{
    isr_enet(&enet0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_ENET0, isr_enet0)
#endif

#ifdef BSP_USING_ETH1
void isr_enet1(void)
{
    isr_enet(&enet1);
}
SDK_DECLARE_EXT_ISR_M(IRQn_ENET1, isr_enet1)
#endif

int rt_hw_eth_init(void)
{
    rt_err_t err = RT_ERROR;

    for (uint32_t i = 0; i < ARRAY_SIZE(s_geths); i++)
    {
        /* Clear memory */
        memset((uint8_t *)s_geths[i]->dma_rx_desc_tab, 0x00, sizeof(enet_rx_desc_t) * s_geths[i]->rx_buff_cfg->count);
        memset((uint8_t *)s_geths[i]->dma_tx_desc_tab, 0x00, sizeof(enet_tx_desc_t) * s_geths[i]->tx_buff_cfg->count);

        memset((uint8_t *)s_geths[i]->rx_buff_cfg->buffer, 0x00, sizeof(s_geths[i]->rx_buff_cfg->size));
        memset((uint8_t *)s_geths[i]->tx_buff_cfg->buffer, 0x00, sizeof(s_geths[i]->tx_buff_cfg->size));

        /* Set list heads */
        s_geths[i]->enet_dev->desc.tx_desc_list_head = (enet_tx_desc_t *)core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t)s_geths[i]->dma_tx_desc_tab);
        s_geths[i]->enet_dev->desc.rx_desc_list_head = (enet_rx_desc_t *)core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t)s_geths[i]->dma_rx_desc_tab);

        s_geths[i]->enet_dev->desc.tx_buff_cfg.buffer = core_local_mem_to_sys_address(BOARD_RUNNING_CORE, s_geths[i]->tx_buff_cfg->buffer);
        s_geths[i]->enet_dev->desc.tx_buff_cfg.count = s_geths[i]->tx_buff_cfg->count;
        s_geths[i]->enet_dev->desc.tx_buff_cfg.size = s_geths[i]->tx_buff_cfg->size;

        s_geths[i]->enet_dev->desc.rx_buff_cfg.buffer = core_local_mem_to_sys_address(BOARD_RUNNING_CORE, s_geths[i]->rx_buff_cfg->buffer);
        s_geths[i]->enet_dev->desc.rx_buff_cfg.count = s_geths[i]->rx_buff_cfg->count;
        s_geths[i]->enet_dev->desc.rx_buff_cfg.size = s_geths[i]->rx_buff_cfg->size;

        /* Set mac0 address */
        s_geths[i]->enet_dev->mac_config.mac_addr_high[0] = MAC_ADDR5 << 8 | MAC_ADDR4;
        s_geths[i]->enet_dev->mac_config.mac_addr_low[0] = MAC_ADDR3 << 24 | MAC_ADDR2 << 16 | MAC_ADDR1 << 8 | MAC_ADDR0;
        s_geths[i]->enet_dev->mac_config.valid_max_count = 1;

        /* Set instance */
        s_geths[i]->enet_dev->instance = s_geths[i]->base;

        /* Set media interface */
        s_geths[i]->enet_dev->media_interface = s_geths[i]->inf;

        /* Set refclk  */
        s_geths[i]->enet_dev->int_refclk = s_geths[i]->int_refclk;

        /* Set TX delay */
        s_geths[i]->enet_dev->tx_delay = s_geths[i]->tx_delay;

        /* Set RX delay */
        s_geths[i]->enet_dev->rx_delay = s_geths[i]->rx_delay;

        /* Set PTP function */
        s_geths[i]->enet_dev->ptp_enable    = s_geths[i]->ptp_enable;
        s_geths[i]->enet_dev->ptp_clk_src   = s_geths[i]->ptp_clk_src;
        s_geths[i]->enet_dev->ptp_config    = *s_geths[i]->ptp_config;
        s_geths[i]->enet_dev->ptp_timestamp = *s_geths[i]->ptp_timestamp;

        /* Set the interrupt enable mask */
        s_geths[i]->enet_dev->mask = ENET_DMA_INTR_EN_NIE_SET(1)   /* Enable normal interrupt summary */
                                   | ENET_DMA_INTR_EN_RIE_SET(1);  /* Enable receive interrupt */

        /* Set the interrupt disable mask */
        s_geths[i]->enet_dev->dis_mask = ENET_INTR_MASK_RGSMIIIM_SET(1);

        /* Set the irq number */
        s_geths[i]->enet_dev->irq_number = s_geths[i]->irq_num;

        /* Set the parent parameters */

        s_geths[i]->eth_dev->parent.init      = rt_hpm_eth_init;
        s_geths[i]->eth_dev->parent.open      = rt_hpm_eth_open;
        s_geths[i]->eth_dev->parent.close     = rt_hpm_eth_close;
        s_geths[i]->eth_dev->parent.read      = rt_hpm_eth_read;
        s_geths[i]->eth_dev->parent.write     = rt_hpm_eth_write;
        s_geths[i]->eth_dev->parent.control   = rt_hpm_eth_control;

        s_geths[i]->eth_dev->parent.user_data = s_geths[i]->enet_dev;

        s_geths[i]->eth_dev->eth_rx = rt_hpm_eth_rx;
        s_geths[i]->eth_dev->eth_tx = rt_hpm_eth_tx;

        err = eth_device_init(s_geths[i]->eth_dev, s_geths[i]->name);

        if (RT_EOK == err)
        {
            LOG_D("Ethernet device initialize successfully!\n");
        }
        else
        {
            LOG_D("Ethernet device initialize unsuccessfully!\n");
            return err;
        }
    }

    return err;

}
INIT_DEVICE_EXPORT(rt_hw_eth_init);
#endif /* BSP_USING_ETH */
