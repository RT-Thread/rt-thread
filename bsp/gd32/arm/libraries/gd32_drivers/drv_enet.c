/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <board.h>

#if defined(SOC_SERIES_GD32H77x_H78X) && defined(BSP_USING_ETH)

#include <netif/ethernetif.h>
#include <lwip/pbuf.h>
#include "gd32h77x_78x_enet.h"

#define DBG_TAG                 "drv.enet"
#define DBG_LVL                 DBG_INFO
#include <rtdbg.h>

#define ENET_DEVICE_NAME        "e0"
#define ENET_PERIPH             ENET1
#define ENET_PHY_ADDR_INVALID   0xFFU
#define ENET_PHY_ID1_REG        2U
#define ENET_PHY_ID2_REG        3U
#define ENET_PHY_ANAR_REG       4U
#define ENET_PHY_ANLPAR_REG     5U
#define ENET_PHY_EXT_DATA_REG   0x0DU
#define ENET_PHY_EXT_ADDR_REG   0x0EU
#define ENET_PHY_LED_CTRL0_EXT  0x1E33U
#define ENET_PHY_LED_MODE_MASK  0x0070U
#define ENET_PHY_GD30PH201D_ID1 0xADB4U
#define ENET_PHY_GD30PH201D_ID2 0x0400U
#define ENET_PHY_GD30PH201D_ID2_MASK 0xFFF0U
#define ENET_PHY_AN_10_HALF     (1U << 5)
#define ENET_PHY_AN_10_FULL     (1U << 6)
#define ENET_PHY_AN_100_HALF    (1U << 7)
#define ENET_PHY_AN_100_FULL    (1U << 8)
#define ENET_PHY_POLL_TICKS     RT_TICK_PER_SECOND
#define ENET_TX_WAIT_TICKS      RT_TICK_PER_SECOND
#define ENET_DMA_RAM_BASE       0x30004000U
#define ENET_DMA_RAM_SIZE       0x00004000U
#define ENET_DMA_STATUS_W1C     0x0001E7FFU

#ifdef RT_LWIP_USING_HW_CHECKSUM
#define ENET_RX_CHECKSUM_MODE   ENET_AUTOCHECKSUM_DROP_FAILFRAMES
#define ENET_TX_CHECKSUM_MODE   ENET_CHECKSUM_TCPUDPICMP_FULL
#else
#define ENET_RX_CHECKSUM_MODE   ENET_NO_AUTOCHECKSUM
#define ENET_TX_CHECKSUM_MODE   ENET_CHECKSUM_DISABLE
#endif

struct gd32_enet_dma
{
    volatile enet_descriptors_struct rx_desc[ENET_RXBUF_NUM];
    volatile enet_descriptors_struct tx_desc[ENET_TXBUF_NUM];
    volatile rt_uint8_t rx_buffer[ENET_RXBUF_NUM][ENET_RXBUF_SIZE];
    volatile rt_uint8_t tx_buffer[ENET_TXBUF_NUM][ENET_TXBUF_SIZE];
};

struct gd32_enet
{
    struct eth_device parent;
    rt_uint8_t mac[6];
    rt_uint8_t phy_addr;
    rt_bool_t link_up;
    rt_uint32_t media_mode;
    volatile rt_uint32_t dma_error_status;
    struct rt_mutex tx_lock;
    volatile enet_descriptors_struct *rx_desc;
    volatile enet_descriptors_struct *tx_desc;
};

static struct gd32_enet gd32_enet_device;
static struct gd32_enet_dma gd32_enet_dma
    __attribute__((section(".enet_dma"), aligned(32)));

typedef char gd32_enet_dma_size_check[
    (sizeof(struct gd32_enet_dma) <= ENET_DMA_RAM_SIZE) ? 1 : -1];

static void enet_tx_desc_reset(void)
{
    rt_uint32_t index;

    rt_memset((void *)&gd32_enet_dma.tx_desc[0], 0, sizeof(gd32_enet_dma.tx_desc));
    for (index = 0; index < ENET_TXBUF_NUM; index++)
    {
        volatile enet_descriptors_struct *desc = &gd32_enet_dma.tx_desc[index];

        desc->status = ENET_TDES0_TCHM;
        desc->buffer1_addr = (rt_uint32_t)&gd32_enet_dma.tx_buffer[index][0];
        desc->buffer2_next_desc_addr = (rt_uint32_t)&gd32_enet_dma.tx_desc[
            (index + 1U) % ENET_TXBUF_NUM];
    }

    gd32_enet_device.tx_desc = &gd32_enet_dma.tx_desc[0];
    __DMB();
    ENET_DMA_TDTADDR(ENET_PERIPH) = (rt_uint32_t)&gd32_enet_dma.tx_desc[0];
    __DSB();
}

static rt_err_t enet_tx_stop(void)
{
    rt_tick_t start;

    enet_tx_disable(ENET_PERIPH);
    start = rt_tick_get();
    while (GET_DMA_STAT_TP(ENET_DMA_STAT(ENET_PERIPH)) != 0U)
    {
        if ((rt_tick_get() - start) >= rt_tick_from_millisecond(100))
        {
            return -RT_ETIMEOUT;
        }
        rt_thread_mdelay(1);
    }

    return RT_EOK;
}

static void enet_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOG);
    rcu_periph_clock_enable(RCU_SYSCFG);

    syscfg_enet_phy_interface_config(ENET_PERIPH, SYSCFG_ENET_PHY_RMII);

    /* PC12: REF_CLK, PC6: MDIO, PC7: TX_EN. */
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE,
                  GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_12);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_12);
    gpio_af_set(GPIOC, GPIO_AF_3, GPIO_PIN_12);
    gpio_af_set(GPIOC, GPIO_AF_6, GPIO_PIN_6);
    gpio_af_set(GPIOC, GPIO_AF_0, GPIO_PIN_7);

    /* PD2: CRS_DV, PD4: RXD0, PD5: RXD1. */
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE,
                  GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5);
    gpio_af_set(GPIOD, GPIO_AF_6, GPIO_PIN_2 | GPIO_PIN_5);
    gpio_af_set(GPIOD, GPIO_AF_9, GPIO_PIN_4);

    /* PG6: MDC, PG13: TXD0, PG14: TXD1. */
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE,
                  GPIO_PIN_6 | GPIO_PIN_13 | GPIO_PIN_14);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_6 | GPIO_PIN_13 | GPIO_PIN_14);
    gpio_af_set(GPIOG, GPIO_AF_6, GPIO_PIN_6 | GPIO_PIN_13 | GPIO_PIN_14);
}

static void enet_dma_mpu_config(void)
{
    mpu_region_init_struct mpu_config;

    SCB_CleanInvalidateDCache_by_Addr((uint32_t *)ENET_DMA_RAM_BASE,
                                     ENET_DMA_RAM_SIZE);
    ARM_MPU_Disable();

    mpu_region_struct_para_init(&mpu_config);
    mpu_config.region_base_address = ENET_DMA_RAM_BASE;
    mpu_config.region_size = MPU_REGION_SIZE_16KB;
    mpu_config.access_permission = MPU_AP_FULL_ACCESS;
    /* Normal non-cacheable memory permits optimized CPU copies and stays DMA coherent. */
    mpu_config.access_bufferable = MPU_ACCESS_NON_BUFFERABLE;
    mpu_config.access_cacheable = MPU_ACCESS_NON_CACHEABLE;
    mpu_config.access_shareable = MPU_ACCESS_SHAREABLE;
    mpu_config.region_number = MPU_REGION_NUMBER7;
    mpu_config.subregion_disable = MPU_SUBREGION_ENABLE;
    mpu_config.instruction_exec = MPU_INSTRUCTION_EXEC_NOT_PERMIT;
    mpu_config.tex_type = MPU_TEX_TYPE1;
    mpu_region_config(&mpu_config);
    mpu_region_enable();

    ARM_MPU_Enable(MPU_MODE_PRIV_DEFAULT);
}

static void enet_dma_desc_init(void)
{
    rt_uint32_t index;

    rt_memset(&gd32_enet_dma, 0, sizeof(gd32_enet_dma));

    for (index = 0; index < ENET_RXBUF_NUM; index++)
    {
        volatile enet_descriptors_struct *desc = &gd32_enet_dma.rx_desc[index];

        desc->status = ENET_RDES0_DAV;
        desc->control_buffer_size = ENET_RDES1_RCHM | ENET_RXBUF_SIZE;
        desc->buffer1_addr = (rt_uint32_t)&gd32_enet_dma.rx_buffer[index][0];
        desc->buffer2_next_desc_addr = (rt_uint32_t)&gd32_enet_dma.rx_desc[
            (index + 1U) % ENET_RXBUF_NUM];
    }

    gd32_enet_device.rx_desc = &gd32_enet_dma.rx_desc[0];
    __DMB();
    ENET_DMA_RDTADDR(ENET_PERIPH) = (rt_uint32_t)&gd32_enet_dma.rx_desc[0];
    enet_tx_desc_reset();
}

static rt_err_t enet_phy_read(rt_uint8_t address, rt_uint8_t reg, rt_uint16_t *value)
{
    return enet_phy_write_read(ENET_PERIPH, ENET_PHY_READ, address, reg, value) == SUCCESS
           ? RT_EOK : -RT_ERROR;
}

static rt_err_t enet_phy_write(rt_uint8_t address, rt_uint8_t reg, rt_uint16_t value)
{
    return enet_phy_write_read(ENET_PERIPH, ENET_PHY_WRITE, address, reg, &value) == SUCCESS
           ? RT_EOK : -RT_ERROR;
}

static rt_err_t enet_phy_ext_read(rt_uint8_t address, rt_uint16_t reg, rt_uint16_t *value)
{
    if (enet_phy_write(address, ENET_PHY_EXT_ADDR_REG, reg) != RT_EOK)
    {
        return -RT_ERROR;
    }

    return enet_phy_read(address, ENET_PHY_EXT_DATA_REG, value);
}

static rt_err_t enet_phy_ext_write(rt_uint8_t address, rt_uint16_t reg, rt_uint16_t value)
{
    if (enet_phy_write(address, ENET_PHY_EXT_ADDR_REG, reg) != RT_EOK)
    {
        return -RT_ERROR;
    }

    return enet_phy_write(address, ENET_PHY_EXT_DATA_REG, value);
}

static rt_err_t enet_phy_gd30ph201d_led_mode_init(rt_uint8_t address)
{
    rt_uint16_t id1;
    rt_uint16_t id2;
    rt_uint16_t value;

    if ((enet_phy_read(address, ENET_PHY_ID1_REG, &id1) != RT_EOK) ||
        (enet_phy_read(address, ENET_PHY_ID2_REG, &id2) != RT_EOK))
    {
        return -RT_ERROR;
    }

    if ((id1 != ENET_PHY_GD30PH201D_ID1) ||
        ((id2 & ENET_PHY_GD30PH201D_ID2_MASK) != ENET_PHY_GD30PH201D_ID2))
    {
        return RT_EOK;
    }

    if (enet_phy_ext_read(address, ENET_PHY_LED_CTRL0_EXT, &value) != RT_EOK)
    {
        return -RT_ERROR;
    }
    value &= (rt_uint16_t)~ENET_PHY_LED_MODE_MASK;

    return enet_phy_ext_write(address, ENET_PHY_LED_CTRL0_EXT, value);
}

static rt_bool_t enet_phy_address_valid(rt_uint8_t address)
{
    rt_uint16_t id1;
    rt_uint16_t id2;

    if ((enet_phy_read(address, ENET_PHY_ID1_REG, &id1) != RT_EOK) ||
        (enet_phy_read(address, ENET_PHY_ID2_REG, &id2) != RT_EOK))
    {
        return RT_FALSE;
    }

    return !((id1 == 0U && id2 == 0U) ||
             (id1 == 0xFFFFU && id2 == 0xFFFFU));
}

static rt_uint8_t enet_phy_detect(void)
{
    rt_uint8_t address;

    if (enet_phy_address_valid(BSP_ENET_PHY_ADDR))
    {
        return BSP_ENET_PHY_ADDR;
    }

    for (address = 0; address < 32U; address++)
    {
        if ((address != BSP_ENET_PHY_ADDR) && enet_phy_address_valid(address))
        {
            return address;
        }
    }

    return ENET_PHY_ADDR_INVALID;
}

static rt_err_t enet_phy_restart_autonegotiation(rt_uint8_t address)
{
    rt_tick_t start;
    rt_uint16_t value;

    if (enet_phy_write(address, PHY_REG_BCR, PHY_RESET) != RT_EOK)
    {
        return -RT_ERROR;
    }

    start = rt_tick_get();
    do
    {
        if ((enet_phy_read(address, PHY_REG_BCR, &value) == RT_EOK) &&
            ((value & PHY_RESET) == 0U))
        {
            if (enet_phy_gd30ph201d_led_mode_init(address) != RT_EOK)
            {
                LOG_W("GD30PH201D LED mode configuration failed");
            }

            return enet_phy_write(address, PHY_REG_BCR,
                                  PHY_AUTONEGOTIATION | PHY_RESTART_AUTONEGOTIATION);
        }
        rt_thread_mdelay(10);
    } while ((rt_tick_get() - start) < (RT_TICK_PER_SECOND * 2U));

    return -RT_ETIMEOUT;
}

static rt_err_t enet_phy_media_mode(rt_uint8_t address, rt_uint32_t *mode)
{
    rt_uint16_t advertise;
    rt_uint16_t partner;
    rt_uint16_t common;

    if ((enet_phy_read(address, ENET_PHY_ANAR_REG, &advertise) != RT_EOK) ||
        (enet_phy_read(address, ENET_PHY_ANLPAR_REG, &partner) != RT_EOK))
    {
        return -RT_ERROR;
    }
    common = advertise & partner;

    if (common & ENET_PHY_AN_100_FULL)
    {
        *mode = ENET_100M_FULLDUPLEX;
    }
    else if (common & ENET_PHY_AN_100_HALF)
    {
        *mode = ENET_100M_HALFDUPLEX;
    }
    else if (common & ENET_PHY_AN_10_FULL)
    {
        *mode = ENET_10M_FULLDUPLEX;
    }
    else if (common & ENET_PHY_AN_10_HALF)
    {
        *mode = ENET_10M_HALFDUPLEX;
    }
    else
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t enet_media_mode_set(rt_uint32_t mode)
{
    if (rt_mutex_take(&gd32_enet_device.tx_lock, ENET_TX_WAIT_TICKS) != RT_EOK)
    {
        return -RT_ETIMEOUT;
    }

    if (enet_tx_stop() != RT_EOK)
    {
        rt_mutex_release(&gd32_enet_device.tx_lock);
        return -RT_ETIMEOUT;
    }
    enet_rx_disable(ENET_PERIPH);
    enet_tx_desc_reset();
    ENET_MAC_CFG(ENET_PERIPH) &= ~(ENET_MAC_CFG_SPD | ENET_MAC_CFG_DPM);
    ENET_MAC_CFG(ENET_PERIPH) |= mode;
    enet_rx_enable(ENET_PERIPH);
    enet_tx_enable(ENET_PERIPH);
    gd32_enet_device.media_mode = mode;
    rt_mutex_release(&gd32_enet_device.tx_lock);

    return RT_EOK;
}

static void enet_link_disable(void)
{
    if (rt_mutex_take(&gd32_enet_device.tx_lock, ENET_TX_WAIT_TICKS) != RT_EOK)
    {
        return;
    }

    gd32_enet_device.link_up = RT_FALSE;
    if (enet_tx_stop() != RT_EOK)
    {
        LOG_E("TX DMA stop timed out");
        enet_rx_disable(ENET_PERIPH);
        rt_mutex_release(&gd32_enet_device.tx_lock);
        return;
    }
    enet_rx_disable(ENET_PERIPH);
    enet_tx_desc_reset();
    rt_mutex_release(&gd32_enet_device.tx_lock);
}

static void enet_phy_monitor(void *parameter)
{
    rt_uint16_t status = 0;
    rt_bool_t link_up;
    rt_uint32_t dma_error_status;

    (void)parameter;

    while (gd32_enet_device.phy_addr == ENET_PHY_ADDR_INVALID)
    {
        gd32_enet_device.phy_addr = enet_phy_detect();
        if (gd32_enet_device.phy_addr == ENET_PHY_ADDR_INVALID)
        {
            LOG_E("no PHY found, check RMII clock and MDIO/MDC wiring");
            rt_thread_mdelay(2000);
        }
    }

    LOG_I("PHY found at address %u", gd32_enet_device.phy_addr);
    if (enet_phy_restart_autonegotiation(gd32_enet_device.phy_addr) != RT_EOK)
    {
        LOG_E("PHY reset or auto-negotiation start failed");
    }

    while (1)
    {
        rt_base_t level;

        level = rt_hw_interrupt_disable();
        dma_error_status = gd32_enet_device.dma_error_status;
        gd32_enet_device.dma_error_status = 0U;
        rt_hw_interrupt_enable(level);
        if (dma_error_status != 0U)
        {
            LOG_E("DMA fatal bus error, status: 0x%08x", dma_error_status);
        }

        /* BSR link status is latch-low, so it must be read twice. */
        if (enet_phy_read(gd32_enet_device.phy_addr, PHY_REG_BSR, &status) != RT_EOK)
        {
            link_up = RT_FALSE;
        }
        else
        {
            link_up = (status & PHY_LINKED_STATUS) ? RT_TRUE : RT_FALSE;
        }

        link_up = link_up && (status & PHY_AUTONEGO_COMPLETE);
        if (link_up)
        {
            rt_uint32_t mode;

            if (enet_phy_media_mode(gd32_enet_device.phy_addr, &mode) != RT_EOK)
            {
                link_up = RT_FALSE;
            }
            else if ((!gd32_enet_device.link_up) ||
                     (mode != gd32_enet_device.media_mode))
            {
                if (enet_media_mode_set(mode) != RT_EOK)
                {
                    link_up = RT_FALSE;
                }
            }
        }

        if (link_up != gd32_enet_device.link_up)
        {
            if (!link_up)
            {
                enet_link_disable();
            }
            gd32_enet_device.link_up = link_up;
            eth_device_linkchange(&gd32_enet_device.parent, link_up);
            if (link_up)
            {
                LOG_I("link up: %sMbps %s-duplex",
                      (gd32_enet_device.media_mode & ENET_MAC_CFG_SPD) ? "100" : "10",
                      (gd32_enet_device.media_mode & ENET_MAC_CFG_DPM) ? "full" : "half");
            }
            else
            {
                LOG_I("link down");
            }
        }

        rt_thread_delay(ENET_PHY_POLL_TICKS);
    }
}

static rt_err_t gd32_enet_init(rt_device_t dev)
{
    (void)dev;

    RT_ASSERT((rt_ubase_t)&gd32_enet_dma == ENET_DMA_RAM_BASE);
    enet_dma_mpu_config();
    enet_gpio_config();

    rcu_periph_clock_enable(RCU_ENET1);
    rcu_periph_clock_enable(RCU_ENET1TX);
    rcu_periph_clock_enable(RCU_ENET1RX);

    enet_deinit(ENET_PERIPH);
    if (enet_software_reset(ENET_PERIPH) != SUCCESS)
    {
        LOG_E("MAC software reset timed out");
        return -RT_ETIMEOUT;
    }
    if (enet_phy_config(ENET_PERIPH) != SUCCESS)
    {
        LOG_E("MDC clock configuration failed");
        return -RT_ERROR;
    }
    if (enet_init(ENET_PERIPH, ENET_100M_FULLDUPLEX,
                  ENET_RX_CHECKSUM_MODE,
                  ENET_BROADCAST_FRAMES_PASS) != SUCCESS)
    {
        LOG_E("MAC initialization failed");
        return -RT_ERROR;
    }

    enet_mac_address_set(ENET_PERIPH, ENET_MAC_ADDRESS0, gd32_enet_device.mac);
    enet_dma_desc_init();

    ENET_DMA_STAT(ENET_PERIPH) = ENET_DMA_STATUS_W1C;
    enet_interrupt_enable(ENET_PERIPH, ENET_DMA_INT_NIE);
    enet_interrupt_enable(ENET_PERIPH, ENET_DMA_INT_RIE);
    nvic_irq_enable(ENET1_IRQn, 5U, 0U);

    return RT_EOK;
}

static rt_err_t gd32_enet_open(rt_device_t dev, rt_uint16_t oflag)
{
    (void)dev;
    (void)oflag;
    return RT_EOK;
}

static rt_err_t gd32_enet_close(rt_device_t dev)
{
    (void)dev;
    return RT_EOK;
}

static rt_ssize_t gd32_enet_read(rt_device_t dev, rt_off_t pos,
                                 void *buffer, rt_size_t size)
{
    (void)dev;
    (void)pos;
    (void)buffer;
    (void)size;
    return 0;
}

static rt_ssize_t gd32_enet_write(rt_device_t dev, rt_off_t pos,
                                  const void *buffer, rt_size_t size)
{
    (void)dev;
    (void)pos;
    (void)buffer;
    (void)size;
    return 0;
}

static rt_err_t gd32_enet_control(rt_device_t dev, int cmd, void *args)
{
    struct gd32_enet *enet = (struct gd32_enet *)dev;

    if (cmd == NIOCTL_GADDR)
    {
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
        rt_memcpy(args, enet->mac, sizeof(enet->mac));
        return RT_EOK;
    }

    return -RT_ENOSYS;
}

static rt_err_t gd32_enet_tx(rt_device_t dev, struct pbuf *p)
{
    struct gd32_enet *enet = (struct gd32_enet *)dev;
    volatile enet_descriptors_struct *desc;
    struct pbuf *q;
    rt_tick_t start;
    rt_uint32_t offset = 0;

    if ((p == RT_NULL) || (p->tot_len > ENET_TXBUF_SIZE))
    {
        return -RT_EINVAL;
    }

    if (rt_mutex_take(&enet->tx_lock, ENET_TX_WAIT_TICKS) != RT_EOK)
    {
        return -RT_ETIMEOUT;
    }

    if (!enet->link_up)
    {
        rt_mutex_release(&enet->tx_lock);
        return -RT_EBUSY;
    }

    desc = enet->tx_desc;
    start = rt_tick_get();
    while (desc->status & ENET_TDES0_DAV)
    {
        if ((rt_tick_get() - start) >= ENET_TX_WAIT_TICKS)
        {
            rt_mutex_release(&enet->tx_lock);
            LOG_E("TX timeout: stat=0x%08x ctl=0x%08x ctd=0x%08x desc=0x%08x",
                  ENET_DMA_STAT(ENET_PERIPH), ENET_DMA_CTL(ENET_PERIPH),
                  ENET_DMA_CTDADDR(ENET_PERIPH), (rt_uint32_t)desc);
            return -RT_ETIMEOUT;
        }
        rt_thread_mdelay(1);
    }

    for (q = p; q != RT_NULL; q = q->next)
    {
        rt_memcpy((void *)(desc->buffer1_addr + offset), q->payload, q->len);
        offset += q->len;
    }

    desc->control_buffer_size = p->tot_len;
    __DMB();
    desc->status = ENET_TDES0_TCHM | ENET_TDES0_FSG | ENET_TDES0_LSG |
                   ENET_TX_CHECKSUM_MODE | ENET_TDES0_DAV;
    __DSB();

    if (ENET_DMA_STAT(ENET_PERIPH) & (ENET_DMA_STAT_TBU | ENET_DMA_STAT_TU))
    {
        ENET_DMA_STAT(ENET_PERIPH) = ENET_DMA_STAT_TBU | ENET_DMA_STAT_TU;
    }
    ENET_DMA_TPEN(ENET_PERIPH) = 0U;

    enet->tx_desc = (enet_descriptors_struct *)desc->buffer2_next_desc_addr;
    rt_mutex_release(&enet->tx_lock);
    return RT_EOK;
}

static struct pbuf *gd32_enet_rx(rt_device_t dev)
{
    struct gd32_enet *enet = (struct gd32_enet *)dev;
    volatile enet_descriptors_struct *desc = enet->rx_desc;
    struct pbuf *p = RT_NULL;
    rt_uint32_t length;

    if (desc->status & ENET_RDES0_DAV)
    {
        return RT_NULL;
    }

    if (((desc->status & ENET_RDES0_ERRS) == 0U) &&
        (desc->status & ENET_RDES0_FDES) &&
        (desc->status & ENET_RDES0_LDES))
    {
        length = GET_RDES0_FRML(desc->status);
        if ((length >= 4U) && (length <= ENET_RXBUF_SIZE))
        {
            struct pbuf *q;
            rt_uint32_t offset = 0;

            length -= 4U;
            p = pbuf_alloc(PBUF_RAW, length, PBUF_POOL);
            if (p != RT_NULL)
            {
                for (q = p; q != RT_NULL; q = q->next)
                {
                    rt_memcpy(q->payload,
                              (const void *)(desc->buffer1_addr + offset), q->len);
                    offset += q->len;
                }
            }
        }
    }

    __DMB();
    desc->status = ENET_RDES0_DAV;
    __DSB();
    enet->rx_desc = (enet_descriptors_struct *)desc->buffer2_next_desc_addr;

    if (ENET_DMA_STAT(ENET_PERIPH) & ENET_DMA_STAT_RBU)
    {
        ENET_DMA_STAT(ENET_PERIPH) = ENET_DMA_STAT_RBU;
        ENET_DMA_RPEN(ENET_PERIPH) = 0U;
    }

    return p;
}

void ENET1_IRQHandler(void)
{
    rt_uint32_t status;
    rt_uint32_t clear = 0U;

    rt_interrupt_enter();
    status = ENET_DMA_STAT(ENET_PERIPH);

    if (status & ENET_DMA_STAT_RS)
    {
        clear |= ENET_DMA_STAT_RS | ENET_DMA_STAT_NI;
        eth_device_ready(&gd32_enet_device.parent);
    }

    if (status & ENET_DMA_STAT_FBE)
    {
        clear |= ENET_DMA_STAT_FBE | ENET_DMA_STAT_AI;
        gd32_enet_device.dma_error_status |= status;
    }
    ENET_DMA_STAT(ENET_PERIPH) = clear;
    rt_interrupt_leave();
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops gd32_enet_ops =
{
    gd32_enet_init,
    gd32_enet_open,
    gd32_enet_close,
    gd32_enet_read,
    gd32_enet_write,
    gd32_enet_control,
};
#endif

static int rt_hw_gd32_enet_init(void)
{
    rt_thread_t thread;
    rt_err_t result;
    struct rt_device *device = &gd32_enet_device.parent.parent;

    gd32_enet_device.mac[0] = 0x02;
    gd32_enet_device.mac[1] = 0x00;
    gd32_enet_device.mac[2] = 0x00;
    gd32_enet_device.mac[3] = 0x77;
    gd32_enet_device.mac[4] = 0x00;
    gd32_enet_device.mac[5] = 0x01;
    gd32_enet_device.phy_addr = ENET_PHY_ADDR_INVALID;
    gd32_enet_device.link_up = RT_FALSE;
    gd32_enet_device.media_mode = ENET_100M_FULLDUPLEX;
    gd32_enet_device.dma_error_status = 0U;

#ifdef RT_USING_DEVICE_OPS
    device->ops = &gd32_enet_ops;
#else
    device->init = gd32_enet_init;
    device->open = gd32_enet_open;
    device->close = gd32_enet_close;
    device->read = gd32_enet_read;
    device->write = gd32_enet_write;
    device->control = gd32_enet_control;
#endif
    device->user_data = RT_NULL;
    gd32_enet_device.parent.eth_rx = gd32_enet_rx;
    gd32_enet_device.parent.eth_tx = gd32_enet_tx;

    result = rt_mutex_init(&gd32_enet_device.tx_lock, "enet_tx", RT_IPC_FLAG_PRIO);
    if (result != RT_EOK)
    {
        return result;
    }

    result = eth_device_init_with_flag(&gd32_enet_device.parent, ENET_DEVICE_NAME,
                                       NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP);
    if (result != RT_EOK)
    {
        return result;
    }

    result = rt_device_init(device);
    if (result != RT_EOK)
    {
        LOG_E("hardware initialization failed: %d", result);
        return result;
    }

    thread = rt_thread_create("phy", enet_phy_monitor, RT_NULL, 1024, 20, 10);
    if (thread == RT_NULL)
    {
        return -RT_ENOMEM;
    }
    rt_thread_startup(thread);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_gd32_enet_init);

#endif /* SOC_SERIES_GD32H77x_H78X && BSP_USING_ETH */
