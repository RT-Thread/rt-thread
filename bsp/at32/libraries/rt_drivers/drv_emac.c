/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 * 2022-07-11     shelton      optimize code to improve network throughput
 *                             performance
 * 2022-10-15     shelton      optimize code
 */

#include "drv_emac.h"
#include <netif/ethernetif.h>
#include <lwipopts.h>

/* debug option */
//#define EMAC_RX_DUMP
//#define EMAC_TX_DUMP
//#define DRV_DEBUG
#define LOG_TAG                         "drv.emac"
#include <drv_log.h>

#define CRYSTAL_ON_PHY                  0

/* emac memory buffer configuration */
#define EMAC_NUM_RX_BUF                 5    /* rx (5 * 1500) */
#define EMAC_NUM_TX_BUF                 5    /* tx (5 * 1500) */

#define MAX_ADDR_LEN                    6

struct rt_at32_emac
{
    /* inherit from ethernet device */
    struct eth_device parent;
#ifndef PHY_USING_INTERRUPT_MODE
    rt_timer_t poll_link_timer;
#endif

    /* interface address info, hw address */
    rt_uint8_t dev_addr[MAX_ADDR_LEN];
    /* emac_speed */
    emac_speed_type emac_speed;
    /* emac_duplex_mode */
    emac_duplex_type emac_mode;
};

static emac_dma_desc_type *dma_rx_dscr_tab, *dma_tx_dscr_tab;
extern emac_dma_desc_type *dma_rx_desc_to_get, *dma_tx_desc_to_set;

static rt_uint8_t *rx_buff, *tx_buff;
static struct rt_at32_emac at32_emac_device;
static uint8_t phy_addr = 0xFF;

#if defined(EMAC_RX_DUMP) || defined(EMAC_TX_DUMP)
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

/**
  * @brief phy reset
  */
static void phy_reset(void)
{
    gpio_init_type gpio_init_struct;

#if defined (SOC_SERIES_AT32F437)
    crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOG_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_pins = GPIO_PINS_15;
    gpio_init(GPIOE, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_15;
    gpio_init(GPIOG, &gpio_init_struct);

    gpio_bits_reset(GPIOE, GPIO_PINS_15);
    gpio_bits_reset(GPIOG, GPIO_PINS_15);
    rt_thread_mdelay(2);
    gpio_bits_set(GPIOE, GPIO_PINS_15);
#endif
#if defined (SOC_SERIES_AT32F407)
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_pins = GPIO_PINS_8;
    gpio_init(GPIOC, &gpio_init_struct);

    gpio_bits_reset(GPIOC, GPIO_PINS_8);
    rt_thread_mdelay(2);
    gpio_bits_set(GPIOC, GPIO_PINS_8);
#endif
    rt_thread_mdelay(2000);
}

/**
  * @brief phy clock config
  */
static void phy_clock_config(void)
{
#if (CRYSTAL_ON_PHY == 0)
    /* if CRYSTAL_NO_PHY, output clock with pa8 of mcu */
    gpio_init_type gpio_init_struct;

    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_pins = GPIO_PINS_8;
    gpio_init(GPIOA, &gpio_init_struct);

    /* 9162 clkout output 25 mhz */
    /* 83848 clkout output 50 mhz */
#if defined (SOC_SERIES_AT32F407)
    crm_clock_out_set(CRM_CLKOUT_SCLK);
#if defined (PHY_USING_DM9162)
    crm_clkout_div_set(CRM_CLKOUT_DIV_8);
#elif defined (PHY_USING_DP83848)
    crm_clkout_div_set(CRM_CLKOUT_DIV_4);
#endif
#endif

#if defined (SOC_SERIES_AT32F437)
    crm_clock_out1_set(CRM_CLKOUT1_PLL);
#if defined (PHY_USING_DM9162)
    crm_clkout_div_set(CRM_CLKOUT_INDEX_1, CRM_CLKOUT_DIV1_5, CRM_CLKOUT_DIV2_2);
#elif defined (PHY_USING_DP83848)
    crm_clkout_div_set(CRM_CLKOUT_INDEX_1, CRM_CLKOUT_DIV1_5, CRM_CLKOUT_DIV2_1);
#endif
#endif
#endif
}

/**
  * @brief reset phy register
  */
static error_status emac_phy_register_reset(void)
{
    uint16_t data = 0;
    uint32_t timeout = 0;
    uint32_t i = 0;

    if(emac_phy_register_write(phy_addr, PHY_CONTROL_REG, PHY_RESET_BIT) == ERROR)
    {
        return ERROR;
    }

    for(i = 0; i < 0x000FFFFF; i++);

    do
    {
        timeout++;
        if(emac_phy_register_read(phy_addr, PHY_CONTROL_REG, &data) == ERROR)
        {
            return ERROR;
        }
    } while((data & PHY_RESET_BIT) && (timeout < PHY_TIMEOUT));

    for(i = 0; i < 0x00FFFFF; i++);
    if(timeout == PHY_TIMEOUT)
    {
        return ERROR;
    }
    return SUCCESS;
}

/**
  * @brief set mac speed related parameters
  */
static error_status emac_speed_config(emac_auto_negotiation_type nego, emac_duplex_type mode, emac_speed_type speed)
{
    uint16_t data = 0;
    uint32_t timeout = 0;
    if(nego == EMAC_AUTO_NEGOTIATION_ON)
    {
        do
        {
            timeout++;
            if(emac_phy_register_read(phy_addr, PHY_STATUS_REG, &data) == ERROR)
            {
              return ERROR;
            }
        } while(!(data & PHY_LINKED_STATUS_BIT) && (timeout < PHY_TIMEOUT));

        if(timeout == PHY_TIMEOUT)
        {
            return ERROR;
        }

        timeout = 0;

        if(emac_phy_register_write(phy_addr, PHY_CONTROL_REG, PHY_AUTO_NEGOTIATION_BIT) == ERROR)
        {
            return ERROR;
        }

        do
        {
            timeout++;
            if(emac_phy_register_read(phy_addr, PHY_STATUS_REG, &data) == ERROR)
            {
                return ERROR;
            }
        } while(!(data & PHY_NEGO_COMPLETE_BIT) && (timeout < PHY_TIMEOUT));

        if(timeout == PHY_TIMEOUT)
        {
            return ERROR;
        }

        if(emac_phy_register_read(phy_addr, PHY_SPECIFIED_CS_REG, &data) == ERROR)
        {
            return ERROR;
        }
#ifdef PHY_USING_DM9162
        if(data & PHY_FULL_DUPLEX_100MBPS_BIT)
        {
            emac_fast_speed_set(EMAC_SPEED_100MBPS);
            emac_duplex_mode_set(EMAC_FULL_DUPLEX);
        }
        else if(data & PHY_HALF_DUPLEX_100MBPS_BIT)
        {
            emac_fast_speed_set(EMAC_SPEED_100MBPS);
            emac_duplex_mode_set(EMAC_HALF_DUPLEX);
        }
        else if(data & PHY_FULL_DUPLEX_10MBPS_BIT)
        {
            emac_fast_speed_set(EMAC_SPEED_10MBPS);
            emac_duplex_mode_set(EMAC_FULL_DUPLEX);
        }
        else if(data & PHY_HALF_DUPLEX_10MBPS_BIT)
        {
            emac_fast_speed_set(EMAC_SPEED_10MBPS);
            emac_duplex_mode_set(EMAC_HALF_DUPLEX);
        }
#endif
#ifdef PHY_USING_DP83848
        if(data & PHY_DUPLEX_MODE)
        {
            emac_duplex_mode_set(EMAC_FULL_DUPLEX);
        }
        else
        {
            emac_duplex_mode_set(EMAC_HALF_DUPLEX);
        }
        if(data & PHY_SPEED_MODE)
        {
            emac_fast_speed_set(EMAC_SPEED_10MBPS);
        }
        else
        {
            emac_fast_speed_set(EMAC_SPEED_100MBPS);
        }
#endif
    }
    else
    {
        if(emac_phy_register_write(phy_addr, PHY_CONTROL_REG, (uint16_t)((mode << 8) | (speed << 13))) == ERROR)
        {
            return ERROR;
        }
        if(speed == EMAC_SPEED_100MBPS)
        {
            emac_fast_speed_set(EMAC_SPEED_100MBPS);
        }
        else
        {
            emac_fast_speed_set(EMAC_SPEED_10MBPS);
        }
        if(mode == EMAC_FULL_DUPLEX)
        {
            emac_duplex_mode_set(EMAC_FULL_DUPLEX);
        }
        else
        {
            emac_duplex_mode_set(EMAC_HALF_DUPLEX);
        }
    }

    return SUCCESS;
}

/**
  * @brief initialize emac phy
  */
static error_status emac_phy_init(emac_control_config_type *control_para)
{
    emac_clock_range_set();
    if(emac_phy_register_reset() == ERROR)
    {
        return ERROR;
    }
    if(emac_speed_config(control_para->auto_nego, control_para->duplex_mode, control_para->fast_ethernet_speed) == ERROR)
    {
        return ERROR;
    }

    emac_control_config(control_para);
    return SUCCESS;
}

/**
  * @brief emac initialization function
  */
static rt_err_t rt_at32_emac_init(rt_device_t dev)
{
    emac_control_config_type mac_control_para;
    emac_dma_config_type dma_control_para;

    /* check till phy detected */
    while(phy_addr == 0xFF)
    {
        rt_thread_mdelay(1000);
    }

    /* emac reset */
    emac_reset();

    /* software reset emac dma */
    emac_dma_software_reset_set();
    while(emac_dma_software_reset_get() == SET);

    emac_control_para_init(&mac_control_para);
    mac_control_para.auto_nego = EMAC_AUTO_NEGOTIATION_ON;

    if(emac_phy_init(&mac_control_para) == ERROR)
    {
        LOG_E("emac hardware init failed");
        return -RT_ERROR;
    }
    else
    {
        LOG_D("emac hardware init success");
    }

    emac_transmit_flow_control_enable(TRUE);
    emac_zero_quanta_pause_disable(TRUE);

    /* set mac address */
    emac_local_address_set(at32_emac_device.dev_addr);

    /* set emac dma rx link list */
    emac_dma_descriptor_list_address_set(EMAC_DMA_RECEIVE, dma_rx_dscr_tab, rx_buff, EMAC_NUM_RX_BUF);
    /* set emac dma tx link list */
    emac_dma_descriptor_list_address_set(EMAC_DMA_TRANSMIT, dma_tx_dscr_tab, tx_buff, EMAC_NUM_TX_BUF);

    emac_dma_para_init(&dma_control_para);
    dma_control_para.rsf_enable = TRUE;
    dma_control_para.tsf_enable = TRUE;
    dma_control_para.osf_enable = TRUE;
    dma_control_para.aab_enable = TRUE;
    dma_control_para.usp_enable = TRUE;
    dma_control_para.fb_enable = TRUE;
    dma_control_para.flush_rx_disable = TRUE;
    dma_control_para.rx_dma_pal = EMAC_DMA_PBL_32;
    dma_control_para.tx_dma_pal = EMAC_DMA_PBL_32;
    dma_control_para.priority_ratio = EMAC_DMA_2_RX_1_TX;
    emac_dma_config(&dma_control_para);
    /* emac interrupt init */
    emac_dma_interrupt_enable(EMAC_DMA_INTERRUPT_NORMAL_SUMMARY, TRUE);
    emac_dma_interrupt_enable(EMAC_DMA_INTERRUPT_RX, TRUE);
    nvic_irq_enable(EMAC_IRQn, 0x07, 0);

    /* enable emac */
    emac_start();

    return RT_EOK;
}

static rt_err_t rt_at32_emac_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("emac open");
    return RT_EOK;
}

static rt_err_t rt_at32_emac_close(rt_device_t dev)
{
    LOG_D("emac close");
    return RT_EOK;
}

static rt_ssize_t rt_at32_emac_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("emac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_at32_emac_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("emac write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_at32_emac_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args)
        {
            SMEMCPY(args, at32_emac_device.dev_addr, 6);
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

/**
  * @brief transmit data
  */
rt_err_t rt_at32_emac_tx(rt_device_t dev, struct pbuf *p)
{
    rt_err_t ret = RT_ERROR;
    struct pbuf *q;
    rt_uint32_t offset;

    if ((dma_tx_desc_to_set->status & EMAC_DMATXDESC_OWN) != RESET)
    {
        LOG_D("buffer not valid");
        ret = ERR_USE;
        goto __error;
    }

    offset = 0;
    for (q = p; q != NULL; q = q->next)
    {
        uint8_t *buffer;

        /* copy the frame to be sent into memory pointed by the current ethernet dma tx descriptor */
        buffer = (uint8_t*)((dma_tx_desc_to_set->buf1addr) + offset);
        SMEMCPY(buffer, q->payload, q->len);
        offset += q->len;
    }

#ifdef EMAC_TX_DUMP
    dump_hex(p->payload, p->tot_len);
#endif

    /* prepare transmit descriptors to give to dma */
    LOG_D("transmit frame length :%d", p->tot_len);

    /* setting the frame length: bits[12:0] */
    dma_tx_desc_to_set->controlsize = (p->tot_len & EMAC_DMATXDESC_TBS1);
    /* Setting the last segment and first segment bits (in this case a frame is transmitted in one descriptor) */
    dma_tx_desc_to_set->status |= EMAC_DMATXDESC_LS | EMAC_DMATXDESC_FS;
    /* enable tx completion interrupt */
    dma_tx_desc_to_set->status |= EMAC_DMATXDESC_IC;
    /* set own bit of the tx descriptor status: gives the buffer back to ethernet dma */
    dma_tx_desc_to_set->status |= EMAC_DMATXDESC_OWN;

    /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
    if(emac_dma_flag_get(EMAC_DMA_TBU_FLAG) != RESET)
    {
        emac_dma_flag_clear(EMAC_DMA_TBU_FLAG);
        emac_dma_poll_demand_set(EMAC_DMA_TRANSMIT, 0);
    }

    /* selects the next dma tx descriptor list for next buffer to send */
    dma_tx_desc_to_set = (emac_dma_desc_type*) (dma_tx_desc_to_set->buf2nextdescaddr);

    return ERR_OK;

__error:
    if (emac_dma_flag_get(EMAC_DMA_UNF_FLAG) != (uint32_t)RESET)
    {
        /* clear underflow ethernet dma flag */
        emac_dma_flag_clear(EMAC_DMA_UNF_FLAG);

        /* resume dma transmission*/
        EMAC_DMA->tpd = 0;
    }

    return ret;
}

/**
  * @brief receive data
  */
struct pbuf *rt_at32_emac_rx(rt_device_t dev)
{
    struct pbuf *p = NULL;
    struct pbuf *q = NULL;
    rt_uint32_t offset = 0;
    uint16_t len = 0;
    uint8_t *buffer;

    /* get received frame */
    len = emac_received_packet_size_get();
    if(len > 0)
    {
        LOG_D("receive frame len : %d", len);
        /* we allocate a pbuf chain of pbufs from the lwip buffer pool */
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);

        if(p != NULL)
        {
            for (q = p; q != RT_NULL; q= q->next)
            {
                /* get rx buffer */
                buffer = (uint8_t *)(dma_rx_desc_to_get->buf1addr);
#ifdef EMAC_RX_DUMP
                dump_hex(buffer, len);
#endif
                /* copy the received frame into buffer from memory pointed by the current ethernet dma rx descriptor */
                SMEMCPY(q->payload, (buffer + offset), q->len);
                offset += q->len;
            }
        }
    }
    else
    {
        return p;
    }

    /* release descriptors to dma */
    dma_rx_desc_to_get->status |= EMAC_DMARXDESC_OWN;

    /* when rx buffer unavailable flag is set: clear it and resume reception */
    if(emac_dma_flag_get(EMAC_DMA_RBU_FLAG) != RESET)
    {
        /* clear rbu ethernet dma flag */
        emac_dma_flag_clear(EMAC_DMA_RBU_FLAG);
        /* resume dma reception */
        emac_dma_poll_demand_set(EMAC_DMA_RECEIVE, 0);
    }

    /* update the ethernet dma global rx descriptor with next rx decriptor */
    /* chained mode */
    if((dma_rx_desc_to_get->controlsize & EMAC_DMARXDESC_RCH) != RESET)
    {
        /* selects the next dma rx descriptor list for next buffer to read */
        dma_rx_desc_to_get = (emac_dma_desc_type*) (dma_rx_desc_to_get->buf2nextdescaddr);
    }
    /* ring mode */
    else
    {
        if((dma_rx_desc_to_get->controlsize & EMAC_DMARXDESC_RER) != RESET)
        {
            /* selects the first dma rx descriptor for next buffer to read: last rx descriptor was used */
            dma_rx_desc_to_get = (emac_dma_desc_type*) (EMAC_DMA->rdladdr);
        }
        else
        {
            /* selects the next dma rx descriptor list for next buffer to read */
            dma_rx_desc_to_get = (emac_dma_desc_type*) ((uint32_t)dma_rx_desc_to_get + 0x10 + ((EMAC_DMA->bm & 0x0000007C) >> 2));
        }
    }
    return p;
}

void EMAC_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* packet receiption */
    if (emac_dma_flag_get(EMAC_DMA_RI_FLAG) == SET)
    {
        /* a frame has been received */
        eth_device_ready(&(at32_emac_device.parent));
        emac_dma_flag_clear(EMAC_DMA_RI_FLAG);
    }

    /* packet transmission */
    if (emac_dma_flag_get(EMAC_DMA_TI_FLAG) == SET)
    {
        emac_dma_flag_clear(EMAC_DMA_TI_FLAG);
    }

    /* clear normal interrupt */
    emac_dma_flag_clear(EMAC_DMA_NIS_FLAG);

    /* clear dma error */
    if(emac_dma_flag_get(EMAC_DMA_AIS_FLAG) != RESET)
    {
        if(emac_dma_flag_get(EMAC_DMA_RBU_FLAG) != RESET)
        {
            emac_dma_flag_clear(EMAC_DMA_RBU_FLAG);
        }
        if(emac_dma_flag_get(EMAC_DMA_OVF_FLAG) != RESET)
        {
            emac_dma_flag_clear(EMAC_DMA_OVF_FLAG);
        }

        emac_dma_flag_clear(EMAC_DMA_AIS_FLAG);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

enum {
    PHY_LINK        = (1 << 0),
    PHY_10M         = (1 << 1),
    PHY_FULLDUPLEX  = (1 << 2),
};

static void phy_linkchange()
{
    static rt_uint8_t phy_speed = 0;
    rt_uint8_t phy_speed_new = 0;
    rt_uint16_t status;

    emac_phy_register_read(phy_addr, PHY_BASIC_STATUS_REG, (uint16_t *)&status);
    LOG_D("phy basic status reg is 0x%X", status);

    if (status & (PHY_AUTONEGO_COMPLETE_MASK | PHY_LINKED_STATUS_MASK))
    {
        rt_uint16_t SR = 0;

        phy_speed_new |= PHY_LINK;

        emac_phy_register_read(phy_addr, PHY_SPECIFIED_CS_REG, (uint16_t *)&SR);
        LOG_D("phy control status reg is 0x%X", SR);

        if (SR & (PHY_SPEED_MODE))
        {
            phy_speed_new |= PHY_10M;
        }

        if (SR & (PHY_DUPLEX_MODE))
        {
            phy_speed_new |= PHY_FULLDUPLEX;
        }
    }

    if (phy_speed != phy_speed_new)
    {
        phy_speed = phy_speed_new;
        if (phy_speed & PHY_LINK)
        {
            LOG_D("link up");
            if (phy_speed & PHY_10M)
            {
                LOG_D("10Mbps");
                at32_emac_device.emac_speed = EMAC_SPEED_10MBPS;
            }
            else
            {
                at32_emac_device.emac_speed = EMAC_SPEED_100MBPS;
                LOG_D("100Mbps");
            }

            if (phy_speed & PHY_FULLDUPLEX)
            {
                LOG_D("full-duplex");
                at32_emac_device.emac_mode = EMAC_FULL_DUPLEX;
            }
            else
            {
                LOG_D("half-duplex");
                at32_emac_device.emac_mode = EMAC_HALF_DUPLEX;
            }

            /* send link up. */
            eth_device_linkchange(&at32_emac_device.parent, RT_TRUE);
        }
        else
        {
            LOG_I("link down");
            eth_device_linkchange(&at32_emac_device.parent, RT_FALSE);
        }
    }
}

#ifdef PHY_USING_INTERRUPT_MODE
static void emac_phy_isr(void *args)
{
    rt_uint32_t status = 0;

    emac_phy_register_read(phy_addr, PHY_INTERRUPT_FLAG_REG, (uint16_t *)&status);
    LOG_D("phy interrupt status reg is 0x%X", status);

    phy_linkchange();
}
#endif /* PHY_USING_INTERRUPT_MODE */

static void phy_monitor_thread_entry(void *parameter)
{
    uint8_t detected_count = 0;

    while(phy_addr == 0xFF)
    {
        /* phy search */
        rt_uint32_t i, temp;
        for (i = 0; i <= 0x1F; i++)
        {
            emac_phy_register_read(i, PHY_BASIC_STATUS_REG, (uint16_t *)&temp);

            if (temp != 0xFFFF && temp != 0x00)
            {
                phy_addr = i;
                break;
            }
        }

        detected_count++;
        rt_thread_mdelay(1000);

        if (detected_count > 10)
        {
            LOG_E("No PHY device was detected, please check hardware!");
        }
    }

    LOG_D("Found a phy, address:0x%02X", phy_addr);

    /* reset phy */
    LOG_D("RESET PHY!");
    emac_phy_register_write(phy_addr, PHY_BASIC_CONTROL_REG, PHY_RESET_MASK);
    rt_thread_mdelay(2000);
    emac_phy_register_write(phy_addr, PHY_BASIC_CONTROL_REG, PHY_AUTO_NEGOTIATION_MASK);

    phy_linkchange();
#ifdef PHY_USING_INTERRUPT_MODE
    /* configuration intterrupt pin */
    rt_pin_mode(PHY_INT_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(PHY_INT_PIN, PIN_IRQ_MODE_FALLING, emac_phy_isr, (void *)"callbackargs");
    rt_pin_irq_enable(PHY_INT_PIN, PIN_IRQ_ENABLE);

    /* enable phy interrupt */
    emac_phy_register_write(phy_addr, PHY_INTERRUPT_MASK_REG, PHY_INT_MASK);
#if defined(PHY_INTERRUPT_CTRL_REG)
    emac_phy_register_write(phy_addr, PHY_INTERRUPT_CTRL_REG, PHY_INTERRUPT_EN);
#endif
#else /* PHY_USING_INTERRUPT_MODE */
    at32_emac_device.poll_link_timer = rt_timer_create("phylnk", (void (*)(void*))phy_linkchange,
                                        NULL, RT_TICK_PER_SECOND, RT_TIMER_FLAG_PERIODIC);
    if (!at32_emac_device.poll_link_timer || rt_timer_start(at32_emac_device.poll_link_timer) != RT_EOK)
    {
        LOG_E("Start link change detection timer failed");
    }
#endif /* PHY_USING_INTERRUPT_MODE */
}

/* Register the EMAC device */
static int rt_hw_at32_emac_init(void)
{
    rt_err_t state = RT_EOK;

    /* Prepare receive and send buffers */
    rx_buff = (rt_uint8_t *)rt_calloc(EMAC_NUM_RX_BUF, EMAC_MAX_PACKET_LENGTH);
    if (rx_buff == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }

    tx_buff = (rt_uint8_t *)rt_calloc(EMAC_NUM_TX_BUF, EMAC_MAX_PACKET_LENGTH);
    if (tx_buff == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }

    dma_rx_dscr_tab = (emac_dma_desc_type *)rt_calloc(EMAC_NUM_RX_BUF, sizeof(emac_dma_desc_type));
    if (dma_rx_dscr_tab == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }

    dma_tx_dscr_tab = (emac_dma_desc_type *)rt_calloc(EMAC_NUM_TX_BUF, sizeof(emac_dma_desc_type));
    if (dma_tx_dscr_tab == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }

    /* phy clock */
    phy_clock_config();

    /* enable periph clock */
    crm_periph_clock_enable(CRM_EMAC_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_EMACTX_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_EMACRX_PERIPH_CLOCK, TRUE);

    /* interface mode */
#if defined (SOC_SERIES_AT32F407)
    gpio_pin_remap_config(MII_RMII_SEL_GMUX, TRUE);
#endif
#if defined (SOC_SERIES_AT32F437)
    scfg_emac_interface_set(SCFG_EMAC_SELECT_RMII);
#endif

    /* emac gpio init */
    at32_msp_emac_init(NULL);

    at32_emac_device.emac_speed = EMAC_SPEED_100MBPS;
    at32_emac_device.emac_mode  = EMAC_FULL_DUPLEX;

    at32_emac_device.dev_addr[0] = 0x00;
    at32_emac_device.dev_addr[1] = 0x66;
    at32_emac_device.dev_addr[2] = 0x88;
    /* generate mac addr from unique id (only for test). */
    at32_emac_device.dev_addr[3] = *(rt_uint8_t *)(0x1FFFF7E8 + 4);
    at32_emac_device.dev_addr[4] = *(rt_uint8_t *)(0x1FFFF7E8 + 2);
    at32_emac_device.dev_addr[5] = *(rt_uint8_t *)(0x1FFFF7E8 + 0);

    at32_emac_device.parent.parent.init = rt_at32_emac_init;
    at32_emac_device.parent.parent.open = rt_at32_emac_open;
    at32_emac_device.parent.parent.close = rt_at32_emac_close;
    at32_emac_device.parent.parent.read = rt_at32_emac_read;
    at32_emac_device.parent.parent.write = rt_at32_emac_write;
    at32_emac_device.parent.parent.control = rt_at32_emac_control;
    at32_emac_device.parent.parent.user_data = RT_NULL;

    at32_emac_device.parent.eth_rx = rt_at32_emac_rx;
    at32_emac_device.parent.eth_tx = rt_at32_emac_tx;

    /* reset phy */
    phy_reset();

    /* start phy monitor */
    rt_thread_t tid;
    tid = rt_thread_create("phy",
                           phy_monitor_thread_entry,
                           RT_NULL,
                           1024,
                           RT_THREAD_PRIORITY_MAX - 2,
                           2);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        state = -RT_ERROR;
    }

    /* register eth device */
    state = eth_device_init(&(at32_emac_device.parent), "e0");
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
__exit:
    if (state != RT_EOK)
    {
        if (rx_buff)
        {
            rt_free(rx_buff);
        }

        if (tx_buff)
        {
            rt_free(tx_buff);
        }

        if (dma_rx_dscr_tab)
        {
            rt_free(dma_rx_dscr_tab);
        }

        if (dma_tx_dscr_tab)
        {
            rt_free(dma_tx_dscr_tab);
        }
    }

    return state;
}

INIT_DEVICE_EXPORT(rt_hw_at32_emac_init);
