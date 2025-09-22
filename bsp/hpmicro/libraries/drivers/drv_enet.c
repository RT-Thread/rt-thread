/*
 * Copyright (c) 2021-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-01-11   HPMicro     First version
 * 2022-07-10   HPMicro     Driver optimization for multiple instances
 * 2024-04-15   HPMicro     Fixed an issue that received data is probabilistically overwritten
 */

#include <rtdevice.h>

#ifdef BSP_USING_ETH
#include <rtdbg.h>
#include "drv_enet.h"
#include "hpm_otp_drv.h"

#ifdef BSP_USING_ETH0

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_DESC_ADDR_ALIGNMENT)
__RW enet_rx_desc_t enet0_dma_rx_desc_tab[ENET0_RX_BUFF_COUNT]; /* Ethernet0 Rx DMA Descriptor */

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_DESC_ADDR_ALIGNMENT)
__RW enet_tx_desc_t enet0_dma_tx_desc_tab[ENET0_TX_BUFF_COUNT]; /* Ethernet0 Tx DMA Descriptor */

ATTR_PLACE_AT_WITH_ALIGNMENT(".fast_ram", ENET_SOC_BUFF_ADDR_ALIGNMENT)
__RW uint8_t enet0_rx_buff[ENET0_RX_BUFF_COUNT][ENET0_RX_BUFF_SIZE]; /* Ethernet0 Receive Buffer */

ATTR_PLACE_AT_WITH_ALIGNMENT(".fast_ram", ENET_SOC_BUFF_ADDR_ALIGNMENT)
__RW uint8_t enet0_tx_buff[ENET0_TX_BUFF_COUNT][ENET0_TX_BUFF_SIZE]; /* Ethernet0 Transmit Buffer */

LWIP_MEMPOOL_DECLARE(enet0_rx_pool, ENET0_RX_BUFF_COUNT, sizeof(my_custom_pbuf_t), "Custom RX PBUF pool");
static enet_frame_t enet0_frame[ENET0_RX_BUFF_COUNT] = {0};

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

#if defined(__USE_ENET_PTP) && __USE_ENET_PTP
static enet_ptp_ts_update_t ptp_timestamp0 = {0, 0};
static enet_ptp_config_t ptp_config0 = {.timestamp_rollover_mode = enet_ts_dig_rollover_control,
                                        .update_method = enet_ptp_time_fine_update,
                                        .addend = 0xffffffff,
                                       };
#endif

static hpm_enet_t enet0 = {.name            = "E0",
                           .base            = HPM_ENET0,
                           .clock_name      = clock_eth0,
                           .irq_num         = IRQn_ENET0,
                           .inf             = BOARD_ENET0_INF,
                           .eth_dev         = &eth0_dev,
                           .enet_dev        = &enet0_dev,
                           .rx_buff_cfg     = &enet0_rx_buff_cfg,
                           .tx_buff_cfg     = &enet0_tx_buff_cfg,
                           .dma_rx_desc_tab = enet0_dma_rx_desc_tab,
                           .dma_tx_desc_tab = enet0_dma_tx_desc_tab,
                           .frame           = enet0_frame,
#if !BOARD_ENET0_INF
                           .int_refclk      = BOARD_ENET0_INT_REF_CLK,
#else
                           .tx_delay        = BOARD_ENET0_TX_DLY,
                           .rx_delay        = BOARD_ENET0_RX_DLY,
#endif

#if defined(__USE_ENET_PTP) && __USE_ENET_PTP
                           .ptp_clk_src     = BOARD_ENET0_PTP_CLOCK,
                           .ptp_config      = &ptp_config0,
                           .ptp_timestamp   = &ptp_timestamp0
#endif
                          };
#endif

mac_init_t mac_init[] = {
    {MAC0_ADDR0, MAC0_ADDR1, MAC0_ADDR2, MAC0_ADDR3, MAC0_ADDR4, MAC0_ADDR5},
    {MAC1_ADDR0, MAC1_ADDR1, MAC1_ADDR2, MAC1_ADDR3, MAC1_ADDR4, MAC1_ADDR5}
};

#ifdef BSP_USING_ETH1

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_DESC_ADDR_ALIGNMENT)
__RW enet_rx_desc_t enet1_dma_rx_desc_tab[ENET1_RX_BUFF_COUNT]; /* Ethernet1 Rx DMA Descriptor */

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_DESC_ADDR_ALIGNMENT)
__RW enet_tx_desc_t enet1_dma_tx_desc_tab[ENET1_TX_BUFF_COUNT]; /* Ethernet1 Tx DMA Descriptor */

ATTR_PLACE_AT_WITH_ALIGNMENT(".fast_ram", ENET_SOC_BUFF_ADDR_ALIGNMENT)
__RW uint8_t enet1_rx_buff[ENET1_RX_BUFF_COUNT][ENET1_RX_BUFF_SIZE]; /* Ethernet1 Receive Buffer */

ATTR_PLACE_AT_WITH_ALIGNMENT(".fast_ram", ENET_SOC_BUFF_ADDR_ALIGNMENT)
__RW uint8_t enet1_tx_buff[ENET1_TX_BUFF_COUNT][ENET1_TX_BUFF_SIZE]; /* Ethernet1 Transmit Buffer */

LWIP_MEMPOOL_DECLARE(enet1_rx_pool, ENET1_RX_BUFF_COUNT, sizeof(my_custom_pbuf_t), "Custom RX PBUF pool");
static enet_frame_t enet1_frame[ENET1_RX_BUFF_COUNT] = {0};

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

#if defined(__USE_ENET_PTP) && __USE_ENET_PTP
static enet_ptp_ts_update_t ptp_timestamp1 = {0, 0};
static enet_ptp_config_t ptp_config1 = {.timestamp_rollover_mode = enet_ts_dig_rollover_control,
                                        .update_method = enet_ptp_time_fine_update,
                                        .addend = 0xffffffff,
                                       };
#endif

static hpm_enet_t enet1 = {.name            = "E1",
                           .base            = HPM_ENET1,
                           .clock_name      = clock_eth1,
                           .irq_num         = IRQn_ENET1,
                           .inf             = BOARD_ENET1_INF,
                           .eth_dev         = &eth1_dev,
                           .enet_dev        = &enet1_dev,
                           .rx_buff_cfg     = &enet1_rx_buff_cfg,
                           .tx_buff_cfg     = &enet1_tx_buff_cfg,
                           .dma_rx_desc_tab = enet1_dma_rx_desc_tab,
                           .dma_tx_desc_tab = enet1_dma_tx_desc_tab,
                           .frame           = enet1_frame,

#if !BOARD_ENET1_INF
                           .int_refclk      = BOARD_ENET1_INT_REF_CLK,
#else
                           .tx_delay        = BOARD_ENET1_TX_DLY,
                           .rx_delay        = BOARD_ENET1_RX_DLY,
#endif

#if defined(__USE_ENET_PTP) && __USE_ENET_PTP
                           .ptp_clk_src     = BOARD_ENET1_PTP_CLOCK,
                           .ptp_config      = &ptp_config1,
                           .ptp_timestamp   = &ptp_timestamp1
#endif
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

void free_rx_dma_descriptor(void *p)
{
    enet_frame_t *frame;

    /* Release descriptors to DMA */
    frame = (enet_frame_t *)p;

    /* Set Own bit in Rx descriptors: gives the buffers back to DMA */
    enet_rx_desc_t *dma_rx_desc = frame->rx_desc;

    for (uint32_t i = 0; i < frame->seg; i++) {
        dma_rx_desc->rdes0_bm.own = 1;
        dma_rx_desc = (enet_rx_desc_t *)(dma_rx_desc->rdes3_bm.next_desc);
    }

    /* Clear Segment_Count */
    frame->seg = 0;
    frame->free = 0;
}

#ifdef BSP_USING_ETH0
void enet0_pbuf_free_custom(struct pbuf *p)
{
    SYS_ARCH_DECL_PROTECT(old_level);
    my_custom_pbuf_t *my_pbuf = (my_custom_pbuf_t *)p;

    SYS_ARCH_PROTECT(old_level);
    free_rx_dma_descriptor((void *)my_pbuf->dma_descriptor);

    LWIP_MEMPOOL_FREE(enet0_rx_pool, my_pbuf);
    SYS_ARCH_UNPROTECT(old_level);
}
#endif

#ifdef BSP_USING_ETH1
void enet1_pbuf_free_custom(struct pbuf *p)
{
    SYS_ARCH_DECL_PROTECT(old_level);
    my_custom_pbuf_t *my_pbuf = (my_custom_pbuf_t *)p;

    SYS_ARCH_PROTECT(old_level);
    free_rx_dma_descriptor((void *)my_pbuf->dma_descriptor);

    LWIP_MEMPOOL_FREE(enet1_rx_pool, my_pbuf);
    SYS_ARCH_UNPROTECT(old_level);
}
#endif

ATTR_WEAK uint8_t enet_get_mac_address(ENET_Type *ptr, uint8_t *mac)
{
    uint32_t macl, mach;
    uint8_t i;

    i = (ptr == HPM_ENET0) ? 0 : 1;

        if (mac == NULL) {
            return ENET_MAC_ADDR_PARA_ERROR;
        }

        /* load mac address from OTP MAC area */
        if (i == 0) {
            macl = otp_read_from_shadow(OTP_SOC_MAC0_IDX);
            mach = otp_read_from_shadow(OTP_SOC_MAC0_IDX + 1);

            mac[0] = (macl >>  0) & 0xff;
            mac[1] = (macl >>  8) & 0xff;
            mac[2] = (macl >> 16) & 0xff;
            mac[3] = (macl >> 24) & 0xff;
            mac[4] = (mach >>  0) & 0xff;
            mac[5] = (mach >>  8) & 0xff;
        } else {
            macl = otp_read_from_shadow(OTP_SOC_MAC0_IDX + 1);
            mach = otp_read_from_shadow(OTP_SOC_MAC0_IDX + 2);

            mac[0] = (macl >> 16) & 0xff;
            mac[1] = (macl >> 24) & 0xff;
            mac[2] = (mach >>  0) & 0xff;
            mac[3] = (mach >>  8) & 0xff;
            mac[4] = (mach >> 16) & 0xff;
            mac[5] = (mach >> 24) & 0xff;
        }

        if (!IS_MAC_INVALID(mac)) {
            return ENET_MAC_ADDR_FROM_OTP_MAC;
        }

        /* load MAC address from MACRO definitions */
        memcpy(mac, &mac_init[i], ENET_MAC);
        return ENET_MAC_ADDR_FROM_MACRO;
}

static rt_err_t hpm_enet_init(enet_device *init)
{
    if (init->media_interface == enet_inf_rmii)
    {
        /* Initialize reference clock */
        board_init_enet_rmii_reference_clock(init->instance, init->int_refclk);
    }

    /* Set RGMII clock delay */
   if (init->media_interface == enet_inf_rgmii)
   {
        clock_add_to_group(init->clock_name, BOARD_RUNNING_CORE & 0x1);
        enet_rgmii_set_clock_delay(init->instance, init->tx_delay, init->rx_delay);
   }

    /* Get the default interrupt config */
    enet_get_default_interrupt_config(init->instance, &init->int_config);

    /* Initialize eth controller */
    enet_controller_init(init->instance, init->media_interface, &init->desc, &init->mac_config, &init->int_config);

    /* Disable LPI interrupt */
    enet_disable_lpi_interrupt(init->instance);

#if defined(__USE_ENET_PTP) && __USE_ENET_PTP
   /* initialize PTP Clock */
   board_init_enet_ptp_clock(init->instance);

   /* initialize Ethernet PTP Module */
   init->ptp_config.ssinc = ENET_ONE_SEC_IN_NANOSEC / clock_get_frequency(init->ptp_clk_src);
   enet_init_ptp(init->instance, &init->ptp_config);

   /* set the initial timestamp */
   enet_set_ptp_timestamp(init->instance, &init->ptp_timestamp);
#endif

   /* enable irq */
   intc_m_enable_irq(init->irq_number);

   return RT_EOK;
}

static rt_err_t rt_hpm_eth_init(rt_device_t dev)
{
    uint8_t mac[ENET_MAC];

    enet_device *enet_dev = (enet_device *)dev->user_data;

    /* Initialize GPIOs */
    board_init_enet_pins(enet_dev->instance);

    /* Reset an enet PHY */
    board_reset_enet_phy(enet_dev->instance);

    /* Get MAC address */
    enet_get_mac_address(enet_dev->instance, mac);

    /* Set mac0 address */
    enet_dev->mac_config.mac_addr_high[0] = mac[5] << 8 | mac[4];
    enet_dev->mac_config.mac_addr_low[0] = mac[3] << 24 | mac[2] << 16 | mac[1] << 8 | mac[0];
    enet_dev->mac_config.valid_max_count = 1;

    /* Initialize MAC and DMA */
    if (hpm_enet_init(enet_dev) == 0)
    {
        LOG_D("Ethernet control initialize successfully\n");
        return RT_EOK;
    }
    else
    {
        LOG_D("Ethernet control initialize unsuccessfully\n");
        return -RT_ERROR;
    }
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
    uint8_t *mac = (uint8_t *)args;
    enet_device *enet_dev = (enet_device *)dev->user_data;

    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (args != NULL)
        {
            enet_get_mac_address(enet_dev->instance, (uint8_t *)mac);
            SMEMCPY(args, mac, ENET_MAC);
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
    rt_tick_t t_start;

    /* copy frame from pbufs to driver buffers */
    for (q = p; q != NULL; q = q->next)
    {
        /* Get bytes in current lwIP buffer */
        bytes_left_to_copy = q->len;
        payload_offset = 0;

        /* Check if the length of data to copy is bigger than Tx buffer size*/
        while ((bytes_left_to_copy + buffer_offset) > tx_buff_size)
        {
            /* check DMA own status within timeout */
            t_start = rt_tick_get();
            while (dma_tx_desc->tdes0_bm.own)
            {
                if (rt_tick_get() - t_start > RT_TICK_PER_SECOND / 100)
                {
                    return ERR_TIMEOUT;
                }
            }

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
                return ERR_INPROGRESS;
            }

            buffer = (uint8_t *)(dma_tx_desc->tdes2_bm.buffer1);

            bytes_left_to_copy = bytes_left_to_copy - (tx_buff_size - buffer_offset);
            payload_offset = payload_offset + (tx_buff_size - buffer_offset);
            frame_length = frame_length + (tx_buff_size - buffer_offset);
            buffer_offset = 0;
        }

        /* check DMA own status within timeout */
        t_start = rt_tick_get();
        while (dma_tx_desc->tdes0_bm.own)
        {
            if (rt_tick_get() - t_start > RT_TICK_PER_SECOND / 100)
            {
                return ERR_TIMEOUT;
            }
        }

        /* Copy the remaining bytes */
        buffer = (void *)sys_address_to_core_local_mem(BOARD_RUNNING_CORE, (uint32_t)buffer);
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
    enet_rx_desc_t *dma_rx_desc;
    uint32_t buffer_offset = 0;
    uint32_t payload_offset = 0;
    uint32_t bytes_left_to_copy = 0;
    uint32_t i = 0;

    /* Get a received frame */
    RT_ASSERT(!enet_dev->frame[enet_dev->cnt].free);
    if (enet_dev->frame[enet_dev->cnt].free == 0) {
        enet_dev->frame[enet_dev->cnt] = enet_get_received_frame_interrupt(&enet_dev->desc.rx_desc_list_cur, &enet_dev->desc.rx_frame_info, enet_dev->desc.rx_buff_cfg.count);
    } else {
        return p;
    }

    /* Obtain the size of the packet and put it into the "len" variable. */
    len = enet_dev->frame[enet_dev->cnt].length;
    buffer = (uint8_t *)sys_address_to_core_local_mem(BOARD_RUNNING_CORE, enet_dev->frame[enet_dev->cnt].buffer);
    LOG_D("The current received frame length : %d\n", len);

    if (len > 0)
    {
        enet_dev->frame[enet_dev->cnt].free = 1;

#ifdef BSP_USING_ETH0
        if (enet_dev->instance == HPM_ENET0) {
            my_custom_pbuf_t *my_pbuf = (my_custom_pbuf_t *)LWIP_MEMPOOL_ALLOC(enet0_rx_pool);
            my_pbuf->p.custom_free_function = enet0_pbuf_free_custom;
            my_pbuf->dma_descriptor = (void *)&enet_dev->frame[enet_dev->cnt];
            p = pbuf_alloced_custom(PBUF_RAW, enet_dev->frame[enet_dev->cnt].length, PBUF_REF, &my_pbuf->p, buffer, enet_dev->desc.rx_buff_cfg.size);
            enet_dev->cnt = ++enet_dev->cnt % enet_dev->desc.rx_buff_cfg.count;
        }
#endif

#ifdef BSP_USING_ETH1
        if (enet_dev->instance == HPM_ENET1) {
            my_custom_pbuf_t *my_pbuf = (my_custom_pbuf_t *)LWIP_MEMPOOL_ALLOC(enet1_rx_pool);
            my_pbuf->p.custom_free_function = enet1_pbuf_free_custom;
            my_pbuf->dma_descriptor = (void *)&enet_dev->frame[enet_dev->cnt];
            p = pbuf_alloced_custom(PBUF_RAW, enet_dev->frame[enet_dev->cnt].length, PBUF_REF, &my_pbuf->p, buffer, enet_dev->desc.rx_buff_cfg.size);
            enet_dev->cnt = ++enet_dev->cnt % enet_dev->desc.rx_buff_cfg.count;
        }
#endif
        /* Clear Segment_Count */
        enet_dev->desc.rx_frame_info.seg_count = 0;
    }

    /* Resume Rx Process */
    enet_rx_resume(enet_dev->instance);

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
        obj->base->LPI_CSR;
    }

    if (ENET_DMA_STATUS_RI_GET(status)) {
        obj->base->DMA_STATUS |= ENET_DMA_STATUS_RI_SET(ENET_DMA_STATUS_RI_GET(status));
        eth_rx_callback(obj->eth_dev);
    }
}

#ifdef BSP_USING_ETH0
SDK_DECLARE_EXT_ISR_M(IRQn_ENET0, isr_enet0)
void isr_enet0(void)
{
    isr_enet(&enet0);
}
#endif

#ifdef BSP_USING_ETH1
SDK_DECLARE_EXT_ISR_M(IRQn_ENET1, isr_enet1)
void isr_enet1(void)
{
    isr_enet(&enet1);
}
#endif

int rt_hw_eth_init(void)
{
    rt_err_t err = RT_ERROR;

#ifdef BSP_USING_ETH0
    LWIP_MEMPOOL_INIT(enet0_rx_pool);
#endif

#ifdef BSP_USING_ETH1
    LWIP_MEMPOOL_INIT(enet1_rx_pool);
#endif

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

        /* Set DMA PBL */
        s_geths[i]->enet_dev->mac_config.dma_pbl = board_get_enet_dma_pbl(s_geths[i]->base);

        /* Set instance */
        s_geths[i]->enet_dev->instance = s_geths[i]->base;

        /* Set clock name */
        s_geths[i]->enet_dev->clock_name = s_geths[i]->clock_name;

        /* Set media interface */
        s_geths[i]->enet_dev->media_interface = s_geths[i]->inf ? enet_inf_rgmii : enet_inf_rmii;

        if (s_geths[i]->enet_dev->media_interface == enet_inf_rmii)
        {
            /* Set refclk  */
            s_geths[i]->enet_dev->int_refclk = s_geths[i]->int_refclk;
        } else {
            /* Set TX/RX delay */
            s_geths[i]->enet_dev->tx_delay = s_geths[i]->tx_delay;
            s_geths[i]->enet_dev->rx_delay = s_geths[i]->rx_delay;
        }


#if defined(__USE_ENET_PTP) && __USE_ENET_PTP
        /* Set PTP function */
        s_geths[i]->enet_dev->ptp_clk_src   = s_geths[i]->ptp_clk_src;
        s_geths[i]->enet_dev->ptp_config    = *s_geths[i]->ptp_config;
        s_geths[i]->enet_dev->ptp_timestamp = *s_geths[i]->ptp_timestamp;
#endif

        /* Set the irq number */
        s_geths[i]->enet_dev->irq_number = s_geths[i]->irq_num;

        /* Set the frame buffer and counter */
        s_geths[i]->enet_dev->frame = s_geths[i]->frame;
        s_geths[i]->enet_dev->cnt = 0;

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
            LOG_D("Ethernet device %d initialize successfully!\n", i);
        }
        else
        {
            LOG_D("Ethernet device %d initialize unsuccessfully!\n");
            return err;
        }
    }

    return err;

}
INIT_DEVICE_EXPORT(rt_hw_eth_init);
#endif /* BSP_USING_ETH */
