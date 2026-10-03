/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_ETHERNET_K1X_EMAC_PTP
#include <drivers/ptp.h>
#include <time.h>
#endif
#ifdef RT_USING_SYSTEM_WORKQUEUE
#include <ipc/workqueue.h>
#endif

#include <spacemit.h>
#include "ethernet_dm.h"

#define DBG_TAG                         "ethernet.k1x"
#define DBG_LVL                         DBG_INFO
#include <rtdbg.h>

/* K1X APMU Ethernet control bits. */
#define K1X_APMU_BASE_DEFAULT           0xd4282800UL
#define K1X_PHY_INTF_RGMII              RT_BIT(2)
#define K1X_REF_CLK_SEL                 RT_BIT(3)
#define K1X_RMII_TX_CLK_SEL             RT_BIT(6)
#define K1X_RMII_RX_CLK_SEL             RT_BIT(7)
#define K1X_RGMII_TX_CLK_SEL            RT_BIT(8)
#define K1X_AXI_SINGLE_ID               RT_BIT(13)
#define K1X_RMII_TX_PHASE_SHIFT         16
#define K1X_RMII_TX_PHASE_MASK          RT_GENMASK(18, 16)
#define K1X_RMII_RX_PHASE_SHIFT         20
#define K1X_RMII_RX_PHASE_MASK          RT_GENMASK(22, 20)
#define K1X_RGMII_TX_PHASE_SHIFT        24
#define K1X_RGMII_TX_PHASE_MASK         RT_GENMASK(26, 24)
#define K1X_RGMII_RX_PHASE_SHIFT        28
#define K1X_RGMII_RX_PHASE_MASK         RT_GENMASK(30, 28)

#define K1X_RX_DLINE_EN                 RT_BIT(0)
#define K1X_RX_DLINE_CODE_SHIFT         8
#define K1X_RX_DLINE_CODE_MASK          RT_GENMASK(15, 8)
#define K1X_TX_DLINE_EN                 RT_BIT(16)
#define K1X_TX_DLINE_CODE_SHIFT         24
#define K1X_TX_DLINE_CODE_MASK          RT_GENMASK(31, 24)

/* DMA registers. */
#define K1X_DMA_CONFIGURATION           0x0000
#define K1X_DMA_CONTROL                 0x0004
#define K1X_DMA_STATUS_IRQ              0x0008
#define K1X_DMA_INTERRUPT_ENABLE        0x000c
#define K1X_DMA_TX_AUTO_POLL_COUNTER    0x0010
#define K1X_DMA_TX_POLL_DEMAND          0x0014
#define K1X_DMA_RX_POLL_DEMAND          0x0018
#define K1X_DMA_TX_BASE                 0x001c
#define K1X_DMA_RX_BASE                 0x0020
#define K1X_DMA_RX_IRQ_MITIGATION       0x002c

/* MAC registers. */
#define K1X_MAC_GLOBAL_CONTROL          0x0100
#define K1X_MAC_TRANSMIT_CONTROL        0x0104
#define K1X_MAC_RECEIVE_CONTROL         0x0108
#define K1X_MAC_ADDRESS_CONTROL         0x0118
#define K1X_MAC_ADDRESS1_HIGH           0x0120
#define K1X_MAC_ADDRESS1_MED            0x0124
#define K1X_MAC_ADDRESS1_LOW            0x0128
#define K1X_MAC_HASH_TABLE1             0x0150
#define K1X_MAC_HASH_TABLE2             0x0154
#define K1X_MAC_HASH_TABLE3             0x0158
#define K1X_MAC_HASH_TABLE4             0x015c
#define K1X_MAC_FC_CONTROL              0x0160
#define K1X_MAC_MDIO_CONTROL            0x01a0
#define K1X_MAC_MDIO_DATA               0x01a4
#define K1X_MAC_TX_FIFO_AF              0x01c0
#define K1X_MAC_TX_THRESHOLD            0x01c4
#define K1X_MAC_RX_THRESHOLD            0x01c8
#define K1X_MAC_INTERRUPT_ENABLE        0x01e4

#ifdef RT_ETHERNET_K1X_EMAC_PTP
/* PTP 1588 registers. The system timer is a 17-bit fixed-point ns counter. */
#define K1X_PTP_CONTROL                 0x0300
#define K1X_PTP_INCREMENT               0x0304
#define K1X_PTP_ETHERTYPE               0x0308
#define K1X_PTP_MESSAGE_ID              0x030c
#define K1X_PTP_UDP_PORT                0x0310
#define K1X_PTP_TIME_LOW                0x0320
#define K1X_PTP_TIME_HIGH               0x0324
#define K1X_PTP_TX_TIME_LOW             0x0330
#define K1X_PTP_TX_TIME_HIGH            0x0334
#define K1X_PTP_RX_TIME_LOW             0x0340
#define K1X_PTP_RX_TIME_HIGH            0x0344
#define K1X_PTP_IRQ_STATUS              0x0360
#define K1X_PTP_IRQ_ENABLE              0x0364

#define K1X_PTP_TX_TIMESTAMP_ENABLE     RT_BIT(1)
#define K1X_PTP_RX_TIMESTAMP_ENABLE     RT_BIT(2)
#define K1X_PTP_RX_TYPE_SHIFT           3
#define K1X_PTP_RX_TYPE_MASK            RT_GENMASK(5, 3)
#define K1X_PTP_RX_TYPE_V2_L2_L4        2U
#define K1X_PTP_IRQ_TX_TIMESTAMP        RT_BIT(0)
#define K1X_PTP_IRQ_RX_TIMESTAMP        RT_BIT(1)
#define K1X_PTP_IRQ_ALL                 (K1X_PTP_IRQ_TX_TIMESTAMP | \
                                         K1X_PTP_IRQ_RX_TIMESTAMP)

#define K1X_PTP_INCREMENT_MASK          RT_GENMASK(23, 0)
#define K1X_PTP_PERIOD_SHIFT            24
#define K1X_PTP_INCREMENT_SHIFT         17U
#define K1X_PTP_INCREMENT_FRAC_MASK     ((1ULL << K1X_PTP_INCREMENT_SHIFT) - 1)
#define K1X_PTP_DEFAULT_INCREMENT       (10U << K1X_PTP_INCREMENT_SHIFT)
#define K1X_PTP_DEFAULT_PERIOD          1U
#define K1X_PTP_MAX_ADJ_PPB             1000000000L
#define K1X_PTP_NSEC_PER_SEC            1000000000ULL
#define K1X_PTP_ETHERTYPE_VALUE         0x88f7U
#define K1X_PTP_UDP_EVENT_PORT          319U
#define K1X_PTP_ALL_EVENT_MESSAGES      0x03020100U
#define K1X_PTP_OVERFLOW_POLL_MS        (4U * 60U * 60U * 1000U)
#endif

/* DMA configuration and control. */
#define K1X_DMA_SOFT_RESET              RT_BIT(0)
#define K1X_DMA_STRICT_BURST            RT_BIT(17)
#define K1X_DMA_64BIT_MODE              RT_BIT(18)
#define K1X_DMA_START_TX                RT_BIT(0)
#define K1X_DMA_START_RX                RT_BIT(1)

/* DMA status/interrupt bits. */
#define K1X_DMA_IRQ_TX_DONE             RT_BIT(0)
#define K1X_DMA_IRQ_TX_UNAVAILABLE      RT_BIT(1)
#define K1X_DMA_IRQ_TX_STOPPED          RT_BIT(2)
#define K1X_DMA_IRQ_RX_DONE             RT_BIT(4)
#define K1X_DMA_IRQ_RX_UNAVAILABLE      RT_BIT(5)
#define K1X_DMA_IRQ_RX_STOPPED          RT_BIT(6)
#define K1X_DMA_IRQ_RX_MISSED           RT_BIT(7)
#define K1X_DMA_IRQ_MAC                 RT_BIT(8)
#define K1X_DMA_IRQ_ALL                 RT_GENMASK(8, 0)
#define K1X_DMA_IRQ_DEFAULT             (K1X_DMA_IRQ_TX_DONE | \
                                         K1X_DMA_IRQ_TX_UNAVAILABLE | \
                                         K1X_DMA_IRQ_TX_STOPPED | \
                                         K1X_DMA_IRQ_RX_DONE | \
                                         K1X_DMA_IRQ_RX_UNAVAILABLE | \
                                         K1X_DMA_IRQ_RX_STOPPED | \
                                         K1X_DMA_IRQ_RX_MISSED)

/* MAC control bits. */
#define K1X_MAC_SPEED_MASK              RT_GENMASK(1, 0)
#define K1X_MAC_SPEED_10                0
#define K1X_MAC_SPEED_100               RT_BIT(0)
#define K1X_MAC_SPEED_1000              RT_BIT(1)
#define K1X_MAC_FULL_DUPLEX             RT_BIT(2)
#define K1X_MAC_TX_ENABLE               RT_BIT(0)
#define K1X_MAC_TX_AUTO_RETRY           RT_BIT(3)
#define K1X_MAC_TX_IFG_MASK             RT_GENMASK(6, 4)
#define K1X_MAC_RX_ENABLE               RT_BIT(0)
#define K1X_MAC_RX_STORE_FORWARD        RT_BIT(3)
#define K1X_MAC_ADDR1_ENABLE            RT_BIT(0)
#define K1X_MAC_FC_DECODE_ENABLE        RT_BIT(0)
#define K1X_MDIO_START                  RT_BIT(15)
#define K1X_MDIO_READ                   RT_BIT(10)

/* RX interrupt mitigation fields. */
#define K1X_RX_COAL_FRAMES_MASK         RT_GENMASK(7, 0)
#define K1X_RX_COAL_TIMEOUT_SHIFT       8
#define K1X_RX_COAL_TIMEOUT_MASK        RT_GENMASK(27, 8)
#define K1X_RX_COAL_ENABLE              RT_BIT(31)
#define K1X_AXI_CYCLES_PER_US           312U

/* Four-word K1X DMA descriptor. */
struct k1x_emac_desc
{
    volatile rt_uint32_t des0;
    volatile rt_uint32_t des1;
    volatile rt_uint32_t des2;
    volatile rt_uint32_t des3;
};

#define K1X_DESC_OWN                    RT_BIT(31)
#define K1X_RX_DESC_FIRST               RT_BIT(30)
#define K1X_RX_DESC_LAST                RT_BIT(29)
#define K1X_DESC_END_RING               RT_BIT(26)
#define K1X_DESC_BUFFER1_SIZE_MASK      RT_GENMASK(11, 0)
#define K1X_TX_DESC_FIRST               RT_BIT(29)
#define K1X_TX_DESC_LAST                RT_BIT(30)
#define K1X_TX_DESC_IRQ                 RT_BIT(31)
#define K1X_RX_FRAME_LENGTH_MASK        RT_GENMASK(13, 0)
#define K1X_RX_APP_STATUS_SHIFT         14
#define K1X_RX_APP_STATUS_MASK          RT_GENMASK(28, 14)
#define K1X_RX_ERR_ALIGN                RT_BIT(0)
#define K1X_RX_ERR_RUNT                 RT_BIT(1)
#define K1X_RX_ERR_CRC                  RT_BIT(6)
#define K1X_RX_ERR_MAX_LEN              RT_BIT(7)
#define K1X_RX_ERR_JABBER               RT_BIT(8)
#define K1X_RX_ERR_LENGTH               RT_BIT(9)
#define K1X_RX_ERROR_MASK               (K1X_RX_ERR_ALIGN | K1X_RX_ERR_RUNT | \
                                         K1X_RX_ERR_CRC | K1X_RX_ERR_MAX_LEN | \
                                         K1X_RX_ERR_JABBER | K1X_RX_ERR_LENGTH)

#define K1X_EMAC_BUFFER_SIZE            1536U
#define K1X_EMAC_TX_RING_DEFAULT        128U
#define K1X_EMAC_RX_RING_DEFAULT        128U
#define K1X_EMAC_RING_MIN               4U
#define K1X_EMAC_RING_MAX               128U
#define K1X_EMAC_TX_THRESHOLD_DEFAULT   192U
#define K1X_EMAC_RX_THRESHOLD_DEFAULT   12U
#define K1X_EMAC_DMA_BURST_DEFAULT      1U
#define K1X_EMAC_RX_COAL_FRAMES         64U
#define K1X_EMAC_RX_COAL_TIMEOUT_US     120U
#define K1X_EMAC_FCS_SIZE               4U
#define K1X_EMAC_LINK_POLL_MS           2000U
#define K1X_EMAC_DMA_FLAGS              (RT_DMA_F_LINEAR | RT_DMA_F_32BITS | \
                                         RT_DMA_F_NOCACHE)

enum k1x_clk_tuning_way
{
    K1X_CLK_TUNING_BY_REG,
    K1X_CLK_TUNING_BY_DLINE,
    K1X_CLK_TUNING_BY_CLK_REVERT,
};

struct k1x_emac
{
    struct eth_device parent;
    struct rt_device *dev;

    void *base;
    void *ctrl_reg;
    void *dline_reg;
    struct rt_clk *mac_clk;
#ifdef RT_ETHERNET_K1X_EMAC_PTP
    struct rt_clk *ptp_clk;
#endif
    struct rt_reset_control *rstc;
    int irq;

    struct mii_bus *mii;
    struct rt_phy_device *phy;
    rt_phy_interface phy_interface;
    struct rt_mutex mdio_lock;
    rt_bool_t mdio_lock_inited;

    rt_uint8_t mac[6];
    rt_bool_t hw_ready;
    rt_bool_t net_registered;
    rt_bool_t irq_installed;
    rt_bool_t link_up;
    int speed;
    int duplex;

    struct k1x_emac_desc *tx_ring;
    struct k1x_emac_desc *rx_ring;
    rt_uint8_t *tx_buffers;
    rt_uint8_t *rx_buffers;
    rt_uint32_t tx_ring_num;
    rt_uint32_t rx_ring_num;
    rt_uint32_t tx_head;
    rt_uint32_t tx_tail;
    rt_uint32_t rx_tail;
    rt_ubase_t tx_ring_dma;
    rt_ubase_t rx_ring_dma;
    rt_ubase_t tx_buffers_dma;
    rt_ubase_t rx_buffers_dma;
    void *dma_blob;
    rt_ubase_t dma_blob_handle;
    rt_size_t dma_blob_size;
    rt_sem_t tx_sem;
    struct rt_mutex tx_mutex;
    rt_bool_t tx_mutex_inited;
    struct rt_spinlock tx_lock;

    rt_uint32_t tx_threshold;
    rt_uint32_t rx_threshold;
    rt_uint32_t dma_burst_len;
    rt_bool_t ref_clk_from_soc;
    rt_bool_t clk_tuning_enable;
    enum k1x_clk_tuning_way clk_tuning_way;
    rt_uint8_t tx_phase;
    rt_uint8_t rx_phase;

    rt_base_t phy_reset_pin;
    rt_uint8_t phy_reset_active;
    rt_uint32_t phy_reset_delays[3];

#ifdef RT_ETHERNET_K1X_EMAC_PTP
    struct rt_ptp_clock ptp_parent;
    struct rt_spinlock ptp_lock;
    rt_uint64_t ptp_cycle_last;
    rt_uint64_t ptp_nsec;
    rt_uint64_t ptp_frac;
    rt_uint32_t ptp_clk_rate;
    rt_uint32_t ptp_increment;
    rt_bool_t ptp_supported;
    rt_bool_t ptp_clk_enabled;
    rt_bool_t ptp_registered;
#ifdef RT_USING_SYSTEM_WORKQUEUE
    struct rt_work ptp_overflow_work;
    rt_bool_t ptp_work_inited;
    rt_bool_t ptp_stopping;
#endif
#endif

#ifdef RT_USING_SYSTEM_WORKQUEUE
    struct rt_work link_work;
    rt_bool_t link_work_inited;
    rt_bool_t stopping;
#endif
};

#define raw_to_k1x_emac(dev) \
    rt_container_of(dev, struct k1x_emac, parent.parent)
#ifdef RT_ETHERNET_K1X_EMAC_PTP
#define ptp_to_k1x_emac(ptp) \
    rt_container_of(ptp, struct k1x_emac, ptp_parent)
#endif

rt_inline rt_uint32_t k1x_emac_readl(struct k1x_emac *emac,
        rt_uint32_t reg)
{
    return HWREG32((rt_uint8_t *)emac->base + reg);
}

rt_inline void k1x_emac_writel(struct k1x_emac *emac,
        rt_uint32_t reg, rt_uint32_t value)
{
    HWREG32((rt_uint8_t *)emac->base + reg) = value;
}

static rt_uint32_t k1x_emac_next(rt_uint32_t index, rt_uint32_t count)
{
    return ++index == count ? 0 : index;
}

#ifdef RT_ETHERNET_K1X_EMAC_PTP
static rt_uint64_t k1x_emac_ptp_read_cycles(struct k1x_emac *emac)
{
    rt_uint64_t low;
    rt_uint64_t high;

    /* Reading LOW first latches the matching HIGH word on K1X. */
    low = k1x_emac_readl(emac, K1X_PTP_TIME_LOW);
    high = k1x_emac_readl(emac, K1X_PTP_TIME_HIGH);

    return (high << 32) | low;
}

static rt_uint64_t k1x_emac_ptp_update_locked(struct k1x_emac *emac)
{
    rt_uint64_t now = k1x_emac_ptp_read_cycles(emac);
    rt_uint64_t delta = now - emac->ptp_cycle_last;
    rt_uint64_t scaled = delta + emac->ptp_frac;

    emac->ptp_frac = scaled & K1X_PTP_INCREMENT_FRAC_MASK;
    emac->ptp_nsec += scaled >> K1X_PTP_INCREMENT_SHIFT;
    emac->ptp_cycle_last = now;

    return emac->ptp_nsec;
}

static rt_err_t k1x_emac_ptp_adjfreq(struct rt_ptp_clock *ptp,
        rt_base_t freq)
{
    rt_bool_t negative;
    rt_uint64_t magnitude;
    rt_uint64_t adjustment;
    rt_uint32_t increment;
    rt_ubase_t level;
    struct k1x_emac *emac = ptp_to_k1x_emac(ptp);

    if (freq > K1X_PTP_MAX_ADJ_PPB || freq <= -K1X_PTP_MAX_ADJ_PPB)
    {
        return -RT_EINVAL;
    }

    negative = freq < 0;
    magnitude = negative ? (rt_uint64_t)(-(rt_int64_t)freq) :
            (rt_uint64_t)freq;
    adjustment = (rt_uint64_t)K1X_PTP_DEFAULT_INCREMENT * magnitude /
            K1X_PTP_NSEC_PER_SEC;
    increment = negative ? K1X_PTP_DEFAULT_INCREMENT - adjustment :
            K1X_PTP_DEFAULT_INCREMENT + adjustment;
    if (!increment || increment > K1X_PTP_INCREMENT_MASK)
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&emac->ptp_lock);
    k1x_emac_ptp_update_locked(emac);
    k1x_emac_writel(emac, K1X_PTP_INCREMENT,
            (K1X_PTP_DEFAULT_PERIOD << K1X_PTP_PERIOD_SHIFT) |
            increment);
    emac->ptp_increment = increment;
    rt_spin_unlock_irqrestore(&emac->ptp_lock, level);

    return RT_EOK;
}

static rt_err_t k1x_emac_ptp_adjtime(struct rt_ptp_clock *ptp,
        rt_int64_t delta)
{
    rt_uint64_t magnitude;
    rt_ubase_t level;
    struct k1x_emac *emac = ptp_to_k1x_emac(ptp);

    level = rt_spin_lock_irqsave(&emac->ptp_lock);
    k1x_emac_ptp_update_locked(emac);

    if (delta < 0)
    {
        magnitude = (rt_uint64_t)(-(delta + 1)) + 1;
        if (magnitude > emac->ptp_nsec)
        {
            rt_spin_unlock_irqrestore(&emac->ptp_lock, level);
            return -RT_EINVAL;
        }
        emac->ptp_nsec -= magnitude;
    }
    else
    {
        magnitude = (rt_uint64_t)delta;
        if (magnitude > RT_UINT64_MAX - emac->ptp_nsec)
        {
            rt_spin_unlock_irqrestore(&emac->ptp_lock, level);
            return -RT_EINVAL;
        }
        emac->ptp_nsec += magnitude;
    }

    rt_spin_unlock_irqrestore(&emac->ptp_lock, level);
    return RT_EOK;
}

static rt_err_t k1x_emac_ptp_gettime(struct rt_ptp_clock *ptp,
        struct rt_ptp_clock_time *ts)
{
    rt_uint64_t ns;
    rt_ubase_t level;
    struct k1x_emac *emac = ptp_to_k1x_emac(ptp);

    level = rt_spin_lock_irqsave(&emac->ptp_lock);
    ns = k1x_emac_ptp_update_locked(emac);
    rt_spin_unlock_irqrestore(&emac->ptp_lock, level);

    ts->sec = ns / K1X_PTP_NSEC_PER_SEC;
    ts->nsec = ns % K1X_PTP_NSEC_PER_SEC;

    return RT_EOK;
}

static rt_err_t k1x_emac_ptp_settime(struct rt_ptp_clock *ptp,
        const struct rt_ptp_clock_time *ts)
{
    rt_uint64_t ns;
    rt_ubase_t level;
    struct k1x_emac *emac = ptp_to_k1x_emac(ptp);

    if (ts->sec < 0 || ts->nsec < 0 ||
        (rt_uint64_t)ts->nsec >= K1X_PTP_NSEC_PER_SEC ||
        (rt_uint64_t)ts->sec >
        (RT_UINT64_MAX - (rt_uint64_t)ts->nsec) /
        K1X_PTP_NSEC_PER_SEC)
    {
        return -RT_EINVAL;
    }
    ns = (rt_uint64_t)ts->sec * K1X_PTP_NSEC_PER_SEC + ts->nsec;

    level = rt_spin_lock_irqsave(&emac->ptp_lock);
    emac->ptp_cycle_last = k1x_emac_ptp_read_cycles(emac);
    emac->ptp_nsec = ns;
    emac->ptp_frac = 0;
    rt_spin_unlock_irqrestore(&emac->ptp_lock, level);

    return RT_EOK;
}

static const struct rt_ptp_ops k1x_emac_ptp_ops =
{
    .adjfreq = k1x_emac_ptp_adjfreq,
    .adjtime = k1x_emac_ptp_adjtime,
    .gettime = k1x_emac_ptp_gettime,
    .settime = k1x_emac_ptp_settime,
};

static void k1x_emac_ptp_hw_enable(struct k1x_emac *emac)
{
    rt_uint32_t control;

    emac->ptp_increment = K1X_PTP_DEFAULT_INCREMENT;
    k1x_emac_writel(emac, K1X_PTP_INCREMENT,
            (K1X_PTP_DEFAULT_PERIOD << K1X_PTP_PERIOD_SHIFT) |
            emac->ptp_increment);
    k1x_emac_writel(emac, K1X_PTP_MESSAGE_ID,
            K1X_PTP_ALL_EVENT_MESSAGES);
    k1x_emac_writel(emac, K1X_PTP_ETHERTYPE,
            K1X_PTP_ETHERTYPE_VALUE);
    k1x_emac_writel(emac, K1X_PTP_UDP_PORT,
            K1X_PTP_UDP_EVENT_PORT);

    control = K1X_PTP_TX_TIMESTAMP_ENABLE |
            K1X_PTP_RX_TIMESTAMP_ENABLE |
            ((K1X_PTP_RX_TYPE_V2_L2_L4 << K1X_PTP_RX_TYPE_SHIFT) &
             K1X_PTP_RX_TYPE_MASK);
    k1x_emac_writel(emac, K1X_PTP_CONTROL, control);
    k1x_emac_writel(emac, K1X_PTP_IRQ_STATUS, K1X_PTP_IRQ_ALL);
    k1x_emac_writel(emac, K1X_PTP_IRQ_ENABLE, K1X_PTP_IRQ_ALL);
    rt_hw_dsb();
}

static void k1x_emac_ptp_hw_disable(struct k1x_emac *emac)
{
    k1x_emac_writel(emac, K1X_PTP_IRQ_ENABLE, 0);
    k1x_emac_writel(emac, K1X_PTP_CONTROL, 0);
    k1x_emac_writel(emac, K1X_PTP_IRQ_STATUS, K1X_PTP_IRQ_ALL);
    rt_hw_dsb();
}

#ifdef RT_USING_SYSTEM_WORKQUEUE
static void k1x_emac_ptp_overflow_work(struct rt_work *work, void *work_data)
{
    rt_ubase_t level;
    struct k1x_emac *emac = work_data;

    RT_UNUSED(work);

    if (emac->ptp_stopping || !emac->ptp_registered)
    {
        return;
    }

    level = rt_spin_lock_irqsave(&emac->ptp_lock);
    k1x_emac_ptp_update_locked(emac);
    rt_spin_unlock_irqrestore(&emac->ptp_lock, level);

    if (!emac->ptp_stopping)
    {
        rt_work_submit(&emac->ptp_overflow_work,
                rt_tick_from_millisecond(K1X_PTP_OVERFLOW_POLL_MS));
    }
}
#endif

static rt_err_t k1x_emac_ptp_register(struct k1x_emac *emac)
{
    rt_err_t err;
    rt_uint64_t start_ns = 0;
    struct timespec now;
    struct rt_ptp_clock *ptp = &emac->ptp_parent;

    if (!emac->ptp_supported)
    {
        return RT_EOK;
    }

    emac->ptp_clk = rt_clk_get_by_name(emac->dev, "ptp-clk");
    if (rt_is_err_or_null(emac->ptp_clk))
    {
        LOG_E("ptp-clk is missing");
        emac->ptp_clk = RT_NULL;
        return -RT_ENOSYS;
    }
    if ((err = rt_clk_prepare_enable(emac->ptp_clk)))
    {
        rt_clk_put(emac->ptp_clk);
        emac->ptp_clk = RT_NULL;
        return err;
    }
    emac->ptp_clk_enabled = RT_TRUE;

    if (!emac->ptp_clk_rate)
    {
        emac->ptp_clk_rate = (rt_uint32_t)rt_clk_get_rate(emac->ptp_clk);
    }

    rt_spin_lock_init(&emac->ptp_lock);
    k1x_emac_ptp_hw_enable(emac);
    emac->ptp_cycle_last = k1x_emac_ptp_read_cycles(emac);
    if (!clock_gettime(CLOCK_REALTIME, &now) && now.tv_sec >= 0 &&
        now.tv_nsec >= 0 &&
        (rt_uint64_t)now.tv_sec <=
        (RT_UINT64_MAX - (rt_uint64_t)now.tv_nsec) /
        K1X_PTP_NSEC_PER_SEC)
    {
        start_ns = (rt_uint64_t)now.tv_sec * K1X_PTP_NSEC_PER_SEC +
                now.tv_nsec;
    }
    emac->ptp_nsec = start_ns;
    emac->ptp_frac = 0;

    ptp->ops = &k1x_emac_ptp_ops;
    ptp->max_freq = K1X_PTP_MAX_ADJ_PPB;
    if ((err = rt_ptp_clock_register(ptp)))
    {
        ptp->ops = RT_NULL;
        k1x_emac_ptp_hw_disable(emac);
        rt_clk_disable_unprepare(emac->ptp_clk);
        emac->ptp_clk_enabled = RT_FALSE;
        rt_clk_put(emac->ptp_clk);
        emac->ptp_clk = RT_NULL;
        return err;
    }
    emac->ptp_registered = RT_TRUE;

#ifdef RT_USING_SYSTEM_WORKQUEUE
    rt_work_init(&emac->ptp_overflow_work, k1x_emac_ptp_overflow_work, emac);
    emac->ptp_work_inited = RT_TRUE;
    rt_work_submit(&emac->ptp_overflow_work,
            rt_tick_from_millisecond(K1X_PTP_OVERFLOW_POLL_MS));
#endif

    LOG_D("%s: PTP clock registered as %s, source %u Hz",
            rt_dm_dev_get_name(&emac->parent.parent),
            rt_dm_dev_get_name(&ptp->parent), emac->ptp_clk_rate);
    return RT_EOK;
}

static void k1x_emac_ptp_unregister(struct k1x_emac *emac)
{
#ifdef RT_USING_SYSTEM_WORKQUEUE
    emac->ptp_stopping = RT_TRUE;
    if (emac->ptp_work_inited)
    {
        rt_work_cancel(&emac->ptp_overflow_work);
        emac->ptp_work_inited = RT_FALSE;
    }
#endif

    if (emac->ptp_clk_enabled)
    {
        k1x_emac_ptp_hw_disable(emac);
    }
    if (emac->ptp_registered)
    {
        rt_ptp_clock_unregister(&emac->ptp_parent);
        emac->ptp_parent.ops = RT_NULL;
        emac->ptp_registered = RT_FALSE;
    }
    if (emac->ptp_clk_enabled)
    {
        rt_clk_disable_unprepare(emac->ptp_clk);
        emac->ptp_clk_enabled = RT_FALSE;
    }
    if (!rt_is_err_or_null(emac->ptp_clk))
    {
        rt_clk_put(emac->ptp_clk);
        emac->ptp_clk = RT_NULL;
    }
}
#endif

static void k1x_emac_delay_us(rt_uint32_t delay)
{
    if (delay >= 1000)
    {
        rt_thread_mdelay((delay + 999) / 1000);
    }
    else if (delay)
    {
        rt_hw_us_delay(delay);
    }
}

static void k1x_emac_reset_hw(struct k1x_emac *emac)
{
    k1x_emac_writel(emac, K1X_MAC_INTERRUPT_ENABLE, 0);
    k1x_emac_writel(emac, K1X_DMA_INTERRUPT_ENABLE, 0);
    k1x_emac_writel(emac, K1X_MAC_RECEIVE_CONTROL, 0);
    k1x_emac_writel(emac, K1X_MAC_TRANSMIT_CONTROL, 0);
    k1x_emac_writel(emac, K1X_DMA_CONTROL, 0);
    k1x_emac_writel(emac, K1X_MAC_GLOBAL_CONTROL, 0x18);
    k1x_emac_writel(emac, K1X_MAC_GLOBAL_CONTROL, 0);
}

static rt_err_t k1x_emac_parse_phy_interface(struct k1x_emac *emac)
{
    rt_err_t err = -RT_ERROR;
    struct rt_ofw_node *phy_np;

    phy_np = rt_ofw_parse_phandle(emac->dev->ofw_node, "phy-handle", 0);
    if (phy_np)
    {
        err = rt_ofw_get_interface(phy_np, &emac->phy_interface);
        rt_ofw_node_put(phy_np);
    }
    if (err)
    {
        err = rt_ofw_get_interface(emac->dev->ofw_node,
                &emac->phy_interface);
    }
    if (err)
    {
        emac->phy_interface = RT_PHY_INTERFACE_MODE_RGMII;
    }

    switch (emac->phy_interface)
    {
    case RT_PHY_INTERFACE_MODE_RMII:
    case RT_PHY_INTERFACE_MODE_RGMII:
    case RT_PHY_INTERFACE_MODE_RGMII_ID:
    case RT_PHY_INTERFACE_MODE_RGMII_RXID:
    case RT_PHY_INTERFACE_MODE_RGMII_TXID:
        return RT_EOK;
    default:
        LOG_E("unsupported PHY interface %d", emac->phy_interface);
        return -RT_EINVAL;
    }
}

static rt_err_t k1x_emac_parse_dt(struct k1x_emac *emac)
{
    struct rt_device *dev = emac->dev;
    rt_uint32_t apmu_base = K1X_APMU_BASE_DEFAULT;
    rt_uint32_t offset;
    rt_uint32_t value;

    emac->tx_threshold = K1X_EMAC_TX_THRESHOLD_DEFAULT;
    emac->rx_threshold = K1X_EMAC_RX_THRESHOLD_DEFAULT;
    emac->tx_ring_num = K1X_EMAC_TX_RING_DEFAULT;
    emac->rx_ring_num = K1X_EMAC_RX_RING_DEFAULT;
    emac->dma_burst_len = K1X_EMAC_DMA_BURST_DEFAULT;
    emac->phy_reset_pin = -1;

    rt_dm_dev_prop_read_u32(dev, "k1x,apmu-base-reg", &apmu_base);
    if (rt_dm_dev_prop_read_u32(dev, "ctrl-reg", &offset))
    {
        LOG_E("ctrl-reg is missing");
        return -RT_EINVAL;
    }
    emac->ctrl_reg = rt_ioremap((void *)(rt_ubase_t)(apmu_base + offset), 4);
    if (!emac->ctrl_reg)
    {
        return -RT_ENOMEM;
    }

    rt_dm_dev_prop_read_u32(dev, "tx-threshold", &emac->tx_threshold);
    rt_dm_dev_prop_read_u32(dev, "rx-threshold", &emac->rx_threshold);
    rt_dm_dev_prop_read_u32(dev, "tx-ring-num", &emac->tx_ring_num);
    rt_dm_dev_prop_read_u32(dev, "rx-ring-num", &emac->rx_ring_num);
    rt_dm_dev_prop_read_u32(dev, "dma-burst-len", &emac->dma_burst_len);

    if (emac->tx_ring_num < K1X_EMAC_RING_MIN)
    {
        LOG_D("invalid tx-ring-num %u, use %u", emac->tx_ring_num,
                K1X_EMAC_TX_RING_DEFAULT);
        emac->tx_ring_num = K1X_EMAC_TX_RING_DEFAULT;
    }
    else if (emac->tx_ring_num > K1X_EMAC_RING_MAX)
    {
        LOG_D("tx-ring-num %u exceeds BSP limit, clamp to %u",
                emac->tx_ring_num, K1X_EMAC_RING_MAX);
        emac->tx_ring_num = K1X_EMAC_RING_MAX;
    }
    if (emac->rx_ring_num < K1X_EMAC_RING_MIN)
    {
        LOG_D("invalid rx-ring-num %u, use %u", emac->rx_ring_num,
                K1X_EMAC_RX_RING_DEFAULT);
        emac->rx_ring_num = K1X_EMAC_RX_RING_DEFAULT;
    }
    else if (emac->rx_ring_num > K1X_EMAC_RING_MAX)
    {
        LOG_D("rx-ring-num %u exceeds BSP limit, clamp to %u",
                emac->rx_ring_num, K1X_EMAC_RING_MAX);
        emac->rx_ring_num = K1X_EMAC_RING_MAX;
    }
    if (!emac->dma_burst_len || emac->dma_burst_len > 7)
    {
        emac->dma_burst_len = K1X_EMAC_DMA_BURST_DEFAULT;
    }

    emac->ref_clk_from_soc =
            !rt_dm_dev_prop_read_bool(dev, "ref-clock-from-phy");
    emac->clk_tuning_enable =
            rt_dm_dev_prop_read_bool(dev, "clk-tuning-enable");
    if (emac->clk_tuning_enable)
    {
        if (rt_dm_dev_prop_read_bool(dev, "clk-tuning-by-delayline"))
        {
            emac->clk_tuning_way = K1X_CLK_TUNING_BY_DLINE;
            if (rt_dm_dev_prop_read_u32(dev, "dline-reg", &offset))
            {
                LOG_E("dline-reg is missing");
                return -RT_EINVAL;
            }
            emac->dline_reg = rt_ioremap(
                    (void *)(rt_ubase_t)(apmu_base + offset), 4);
            if (!emac->dline_reg)
            {
                return -RT_ENOMEM;
            }
        }
        else if (rt_dm_dev_prop_read_bool(dev, "clk-tuning-by-clk-revert"))
        {
            emac->clk_tuning_way = K1X_CLK_TUNING_BY_CLK_REVERT;
        }
        else
        {
            emac->clk_tuning_way = K1X_CLK_TUNING_BY_REG;
        }

        if (!rt_dm_dev_prop_read_u32(dev, "tx-phase", &value))
        {
            emac->tx_phase = value;
        }
        if (!rt_dm_dev_prop_read_u32(dev, "rx-phase", &value))
        {
            emac->rx_phase = value;
        }
    }

    emac->phy_reset_pin = rt_pin_get_named_pin(dev, "emac,reset", 0,
            RT_NULL, RT_NULL);
    emac->phy_reset_active =
            rt_dm_dev_prop_read_bool(dev, "emac,reset-active-low") ?
            PIN_LOW : PIN_HIGH;
    rt_dm_dev_prop_read_u32_array_index(dev, "emac,reset-delays-us", 0,
            RT_ARRAY_SIZE(emac->phy_reset_delays),
            emac->phy_reset_delays);

#ifdef RT_ETHERNET_K1X_EMAC_PTP
    emac->ptp_supported = rt_dm_dev_prop_read_bool(dev, "ptp-support");
    rt_dm_dev_prop_read_u32(dev, "ptp-clk-rate", &emac->ptp_clk_rate);
#endif

    return k1x_emac_parse_phy_interface(emac);
}

static void k1x_emac_config_interface(struct k1x_emac *emac)
{
    rt_uint32_t value = HWREG32(emac->ctrl_reg);

    if (emac->phy_interface == RT_PHY_INTERFACE_MODE_RMII)
    {
        value &= ~K1X_PHY_INTF_RGMII;
        if (emac->ref_clk_from_soc)
        {
            value |= K1X_REF_CLK_SEL;
        }
        else
        {
            value &= ~K1X_REF_CLK_SEL;
        }
    }
    else
    {
        value |= K1X_PHY_INTF_RGMII;
        if (emac->ref_clk_from_soc)
        {
            value |= K1X_RGMII_TX_CLK_SEL;
        }
        else
        {
            value &= ~K1X_RGMII_TX_CLK_SEL;
        }
    }
    value |= K1X_AXI_SINGLE_ID;
    HWREG32(emac->ctrl_reg) = value;
}

static rt_err_t k1x_emac_config_clock_phase(struct k1x_emac *emac)
{
    rt_uint32_t value;

    if (!emac->clk_tuning_enable)
    {
        return RT_EOK;
    }

    if (emac->phy_interface == RT_PHY_INTERFACE_MODE_RMII)
    {
        value = HWREG32(emac->ctrl_reg);
        if (emac->clk_tuning_way == K1X_CLK_TUNING_BY_CLK_REVERT)
        {
            value &= ~(K1X_RMII_TX_CLK_SEL | K1X_RMII_RX_CLK_SEL);
            if (emac->tx_phase == 180)
            {
                value |= K1X_RMII_TX_CLK_SEL;
            }
            if (emac->rx_phase == 180)
            {
                value |= K1X_RMII_RX_CLK_SEL;
            }
        }
        else if (emac->clk_tuning_way == K1X_CLK_TUNING_BY_REG)
        {
            value &= ~(K1X_RMII_TX_PHASE_MASK | K1X_RMII_RX_PHASE_MASK);
            value |= (emac->tx_phase & 0x7) << K1X_RMII_TX_PHASE_SHIFT;
            value |= (emac->rx_phase & 0x7) << K1X_RMII_RX_PHASE_SHIFT;
        }
        else
        {
            return -RT_EINVAL;
        }
        HWREG32(emac->ctrl_reg) = value;
    }
    else if (emac->clk_tuning_way == K1X_CLK_TUNING_BY_DLINE)
    {
        if (!emac->dline_reg)
        {
            return -RT_EINVAL;
        }
        value = HWREG32(emac->dline_reg);
        value &= ~(K1X_TX_DLINE_CODE_MASK | K1X_RX_DLINE_CODE_MASK);
        value |= ((rt_uint32_t)emac->tx_phase << K1X_TX_DLINE_CODE_SHIFT) &
                K1X_TX_DLINE_CODE_MASK;
        value |= ((rt_uint32_t)emac->rx_phase << K1X_RX_DLINE_CODE_SHIFT) &
                K1X_RX_DLINE_CODE_MASK;
        value |= K1X_TX_DLINE_EN | K1X_RX_DLINE_EN;
        HWREG32(emac->dline_reg) = value;
    }
    else if (emac->clk_tuning_way == K1X_CLK_TUNING_BY_REG)
    {
        value = HWREG32(emac->ctrl_reg);
        value &= ~(K1X_RGMII_TX_PHASE_MASK | K1X_RGMII_RX_PHASE_MASK);
        value |= (emac->tx_phase & 0x7) << K1X_RGMII_TX_PHASE_SHIFT;
        value |= (emac->rx_phase & 0x7) << K1X_RGMII_RX_PHASE_SHIFT;
        HWREG32(emac->ctrl_reg) = value;
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static void k1x_emac_external_phy_reset(struct k1x_emac *emac)
{
    if (emac->phy_reset_pin < 0)
    {
        return;
    }

    rt_pin_write(emac->phy_reset_pin, !emac->phy_reset_active);
    rt_pin_mode(emac->phy_reset_pin, PIN_MODE_OUTPUT);
    k1x_emac_delay_us(emac->phy_reset_delays[0]);
    rt_pin_write(emac->phy_reset_pin, emac->phy_reset_active);
    k1x_emac_delay_us(emac->phy_reset_delays[1]);
    rt_pin_write(emac->phy_reset_pin, !emac->phy_reset_active);
    k1x_emac_delay_us(emac->phy_reset_delays[2]);
}

static rt_err_t k1x_emac_mdio_wait(struct k1x_emac *emac)
{
    rt_uint32_t value;

    return readl_poll_timeout((rt_uint8_t *)emac->base + K1X_MAC_MDIO_CONTROL,
            value, !(value & K1X_MDIO_START), 10, 10000);
}

static int k1x_emac_mdio_read(struct mii_bus *bus, int addr, int devad,
        int reg)
{
    rt_err_t err;
    rt_uint32_t command;
    struct k1x_emac *emac = bus->priv;

    RT_UNUSED(devad);

    rt_mutex_take(&emac->mdio_lock, RT_WAITING_FOREVER);
    err = k1x_emac_mdio_wait(emac);
    if (!err)
    {
        command = (addr & 0x1f) | ((reg & 0x1f) << 5) |
                K1X_MDIO_START | K1X_MDIO_READ;
        k1x_emac_writel(emac, K1X_MAC_MDIO_DATA, 0);
        k1x_emac_writel(emac, K1X_MAC_MDIO_CONTROL, command);
        err = k1x_emac_mdio_wait(emac);
    }
    command = err ? 0 : k1x_emac_readl(emac, K1X_MAC_MDIO_DATA) & 0xffff;
    rt_mutex_release(&emac->mdio_lock);

    return err ? err : (int)command;
}

static int k1x_emac_mdio_write(struct mii_bus *bus, int addr, int devad,
        int reg, rt_uint16_t value)
{
    rt_err_t err;
    rt_uint32_t command;
    struct k1x_emac *emac = bus->priv;

    RT_UNUSED(devad);

    rt_mutex_take(&emac->mdio_lock, RT_WAITING_FOREVER);
    err = k1x_emac_mdio_wait(emac);
    if (!err)
    {
        command = (addr & 0x1f) | ((reg & 0x1f) << 5) | K1X_MDIO_START;
        k1x_emac_writel(emac, K1X_MAC_MDIO_DATA, value);
        k1x_emac_writel(emac, K1X_MAC_MDIO_CONTROL, command);
        err = k1x_emac_mdio_wait(emac);
    }
    rt_mutex_release(&emac->mdio_lock);

    return err;
}

static int k1x_emac_find_phy_addr(struct k1x_emac *emac)
{
    struct rt_ofw_node *phy_np;
    rt_uint32_t reg;

    phy_np = rt_ofw_parse_phandle(emac->dev->ofw_node, "phy-handle", 0);
    if (phy_np)
    {
        if (!rt_ofw_prop_read_u32(phy_np, "reg", &reg))
        {
            rt_ofw_node_put(phy_np);
            return reg;
        }
        rt_ofw_node_put(phy_np);
    }

    for (int addr = 0; addr < 32; ++addr)
    {
        int id = k1x_emac_mdio_read(emac->mii, addr,
                RT_MDIO_DEVAD_NONE, RT_MII_PHYSID1);

        if (id > 0 && id != 0xffff)
        {
            return addr;
        }
    }

    return -1;
}

static rt_err_t k1x_emac_mdio_register(struct k1x_emac *emac)
{
    rt_err_t err;
    int alias_id = rt_ofw_get_alias_id(emac->dev->ofw_node, "ethernet");

    emac->mii = rt_mdio_alloc();
    if (!emac->mii)
    {
        return -RT_ENOMEM;
    }

    emac->mii->priv = emac;
    emac->mii->read = k1x_emac_mdio_read;
    emac->mii->write = k1x_emac_mdio_write;
    rt_snprintf(emac->mii->name, sizeof(emac->mii->name), "k1x-mdio%d",
            alias_id < 0 ? 0 : alias_id);

    err = rt_mdio_register(emac->mii);
    if (err)
    {
        rt_free(emac->mii);
        emac->mii = RT_NULL;
    }

    return err;
}

static void k1x_emac_mdio_unregister(struct k1x_emac *emac)
{
    if (emac->mii)
    {
        rt_mdio_unregister(emac->mii);
        rt_free(emac->mii);
        emac->mii = RT_NULL;
    }
}

static rt_err_t k1x_emac_dma_alloc(struct k1x_emac *emac)
{
    rt_size_t tx_desc_size = sizeof(*emac->tx_ring) * emac->tx_ring_num;
    rt_size_t rx_desc_size = sizeof(*emac->rx_ring) * emac->rx_ring_num;
    rt_size_t tx_buf_size = K1X_EMAC_BUFFER_SIZE * emac->tx_ring_num;
    rt_size_t rx_buf_size = K1X_EMAC_BUFFER_SIZE * emac->rx_ring_num;
    rt_size_t rx_desc_offset = RT_ALIGN(tx_desc_size, RT_MM_PAGE_SIZE);
    rt_size_t tx_buf_offset = RT_ALIGN(rx_desc_offset + rx_desc_size,
            RT_MM_PAGE_SIZE);
    rt_size_t rx_buf_offset = RT_ALIGN(tx_buf_offset + tx_buf_size,
            RT_MM_PAGE_SIZE);
    rt_ubase_t handle;
    rt_uint8_t *blob;

    /* Allocates each descriptor ring independently, so both DMA ring
     * bases are page aligned. Preserve that requirement in the shared pool. */
    emac->dma_blob_size = rx_buf_offset + rx_buf_size;
    blob = rt_dma_alloc(emac->dev, emac->dma_blob_size, &handle,
            K1X_EMAC_DMA_FLAGS);
    if (!blob)
    {
        return -RT_ENOMEM;
    }
    if ((handle & RT_MM_PAGE_MASK) || handle > 0xffffffffULL ||
        handle + emac->dma_blob_size - 1 > 0xffffffffULL)
    {
        LOG_E("DMA address %#lx is not page aligned or exceeds the 32-bit aperture",
                (unsigned long)handle);
        rt_dma_free(emac->dev, emac->dma_blob_size, blob, handle,
                K1X_EMAC_DMA_FLAGS);
        return -RT_EINVAL;
    }

    emac->dma_blob = blob;
    emac->dma_blob_handle = handle;
    emac->tx_ring = (struct k1x_emac_desc *)blob;
    emac->rx_ring = (struct k1x_emac_desc *)(blob + rx_desc_offset);
    emac->tx_buffers = blob + tx_buf_offset;
    emac->rx_buffers = blob + rx_buf_offset;
    emac->tx_ring_dma = handle;
    emac->rx_ring_dma = handle + rx_desc_offset;
    emac->tx_buffers_dma = handle + tx_buf_offset;
    emac->rx_buffers_dma = handle + rx_buf_offset;
    rt_memset(blob, 0, emac->dma_blob_size);

    return RT_EOK;
}

static void k1x_emac_dma_free(struct k1x_emac *emac)
{
    if (emac->dma_blob)
    {
        rt_dma_free(emac->dev, emac->dma_blob_size, emac->dma_blob,
                emac->dma_blob_handle, K1X_EMAC_DMA_FLAGS);
        emac->dma_blob = RT_NULL;
    }
}

static void k1x_emac_rx_refill(struct k1x_emac *emac, rt_uint32_t index)
{
    struct k1x_emac_desc *desc = &emac->rx_ring[index];
    rt_ubase_t buffer_dma = emac->rx_buffers_dma +
            index * K1X_EMAC_BUFFER_SIZE;

    desc->des0 = 0;
    desc->des1 = K1X_EMAC_BUFFER_SIZE & K1X_DESC_BUFFER1_SIZE_MASK;
    if (index == emac->rx_ring_num - 1)
    {
        desc->des1 |= K1X_DESC_END_RING;
    }
    desc->des2 = (rt_uint32_t)buffer_dma;
    desc->des3 = 0;
    rt_hw_wmb();
    desc->des0 = K1X_DESC_OWN;
    rt_hw_wmb();
}

static rt_err_t k1x_emac_rings_init(struct k1x_emac *emac)
{
    char sem_name[RT_NAME_MAX];
    int alias_id = rt_ofw_get_alias_id(emac->dev->ofw_node, "ethernet");

    for (rt_uint32_t i = 0; i < emac->rx_ring_num; ++i)
    {
        k1x_emac_rx_refill(emac, i);
    }
    emac->tx_head = 0;
    emac->tx_tail = 0;
    emac->rx_tail = 0;

    rt_snprintf(sem_name, sizeof(sem_name), "k1xtx%d",
            alias_id < 0 ? 0 : alias_id);
    emac->tx_sem = rt_sem_create(sem_name, emac->tx_ring_num - 1,
            RT_IPC_FLAG_FIFO);
    if (!emac->tx_sem)
    {
        return -RT_ENOMEM;
    }

    rt_spin_lock_init(&emac->tx_lock);
    rt_mutex_init(&emac->tx_mutex, "k1xtxm", RT_IPC_FLAG_PRIO);
    emac->tx_mutex_inited = RT_TRUE;

    return RT_EOK;
}

static void k1x_emac_rings_deinit(struct k1x_emac *emac)
{
    if (emac->tx_sem)
    {
        rt_sem_delete(emac->tx_sem);
        emac->tx_sem = RT_NULL;
    }
    if (emac->tx_mutex_inited)
    {
        rt_mutex_detach(&emac->tx_mutex);
        emac->tx_mutex_inited = RT_FALSE;
    }
}

static void k1x_emac_set_mac_address(struct k1x_emac *emac)
{
    k1x_emac_writel(emac, K1X_MAC_ADDRESS1_HIGH,
            ((rt_uint32_t)emac->mac[1] << 8) | emac->mac[0]);
    k1x_emac_writel(emac, K1X_MAC_ADDRESS1_MED,
            ((rt_uint32_t)emac->mac[3] << 8) | emac->mac[2]);
    k1x_emac_writel(emac, K1X_MAC_ADDRESS1_LOW,
            ((rt_uint32_t)emac->mac[5] << 8) | emac->mac[4]);
}

static rt_err_t k1x_emac_hw_init(struct k1x_emac *emac)
{
    rt_uint32_t value;

    k1x_emac_reset_hw(emac);

    k1x_emac_writel(emac, K1X_MAC_ADDRESS_CONTROL,
            K1X_MAC_ADDR1_ENABLE);
    k1x_emac_writel(emac, K1X_MAC_HASH_TABLE1, 0);
    k1x_emac_writel(emac, K1X_MAC_HASH_TABLE2, 0);
    k1x_emac_writel(emac, K1X_MAC_HASH_TABLE3, 0);
    k1x_emac_writel(emac, K1X_MAC_HASH_TABLE4, 0);
    k1x_emac_writel(emac, K1X_MAC_TX_FIFO_AF, 0x1f8);
    k1x_emac_writel(emac, K1X_MAC_TX_THRESHOLD, emac->tx_threshold);
    k1x_emac_writel(emac, K1X_MAC_RX_THRESHOLD, emac->rx_threshold);
    k1x_emac_writel(emac, K1X_MAC_FC_CONTROL,
            K1X_MAC_FC_DECODE_ENABLE);

    value = K1X_EMAC_RX_COAL_FRAMES & K1X_RX_COAL_FRAMES_MASK;
    value |= ((K1X_EMAC_RX_COAL_TIMEOUT_US * K1X_AXI_CYCLES_PER_US) <<
            K1X_RX_COAL_TIMEOUT_SHIFT) & K1X_RX_COAL_TIMEOUT_MASK;
    value |= K1X_RX_COAL_ENABLE;
    k1x_emac_writel(emac, K1X_DMA_RX_IRQ_MITIGATION, value);

    k1x_emac_writel(emac, K1X_DMA_CONFIGURATION, K1X_DMA_SOFT_RESET);
    rt_thread_mdelay(10);
    k1x_emac_writel(emac, K1X_DMA_CONFIGURATION, 0);
    rt_thread_mdelay(10);

    value = K1X_DMA_STRICT_BURST | K1X_DMA_64BIT_MODE |
            RT_BIT(emac->dma_burst_len);
    k1x_emac_writel(emac, K1X_DMA_CONFIGURATION, value);
    k1x_emac_writel(emac, K1X_DMA_STATUS_IRQ, K1X_DMA_IRQ_ALL);
    k1x_emac_set_mac_address(emac);

    k1x_emac_writel(emac, K1X_DMA_TX_BASE,
            (rt_uint32_t)emac->tx_ring_dma);
    k1x_emac_writel(emac, K1X_DMA_RX_BASE,
            (rt_uint32_t)emac->rx_ring_dma);

    emac->hw_ready = RT_TRUE;
    return RT_EOK;
}

static void k1x_emac_hw_start(struct k1x_emac *emac)
{
    rt_uint32_t value;

    value = k1x_emac_readl(emac, K1X_MAC_TRANSMIT_CONTROL);
    value &= ~K1X_MAC_TX_IFG_MASK;
    value |= K1X_MAC_TX_ENABLE | K1X_MAC_TX_AUTO_RETRY;
    k1x_emac_writel(emac, K1X_MAC_TRANSMIT_CONTROL, value);
    k1x_emac_writel(emac, K1X_DMA_TX_AUTO_POLL_COUNTER, 0);

    value = k1x_emac_readl(emac, K1X_MAC_RECEIVE_CONTROL);
    value |= K1X_MAC_RX_ENABLE | K1X_MAC_RX_STORE_FORWARD;
    k1x_emac_writel(emac, K1X_MAC_RECEIVE_CONTROL, value);

    value = k1x_emac_readl(emac, K1X_DMA_CONTROL);
    value |= K1X_DMA_START_TX | K1X_DMA_START_RX;
    k1x_emac_writel(emac, K1X_DMA_CONTROL, value);
    k1x_emac_writel(emac, K1X_DMA_RX_POLL_DEMAND, 0xff);
    rt_hw_dsb();
}

static void k1x_emac_tx_cleanup(struct k1x_emac *emac)
{
    rt_uint32_t released = 0;
    rt_ubase_t level = rt_spin_lock_irqsave(&emac->tx_lock);

    while (emac->tx_tail != emac->tx_head)
    {
        struct k1x_emac_desc *desc = &emac->tx_ring[emac->tx_tail];

        rt_hw_rmb();
        if (desc->des0 & K1X_DESC_OWN)
        {
            break;
        }

        desc->des0 = 0;
        emac->tx_tail = k1x_emac_next(emac->tx_tail, emac->tx_ring_num);
        ++released;
    }

    rt_spin_unlock_irqrestore(&emac->tx_lock, level);

    while (released--)
    {
        rt_sem_release(emac->tx_sem);
    }
}

static rt_err_t k1x_emac_adjust_link(struct k1x_emac *emac)
{
    rt_uint32_t control;

    if (!emac->phy || !emac->phy->link)
    {
        return -RT_ERROR;
    }

    control = k1x_emac_readl(emac, K1X_MAC_GLOBAL_CONTROL);
    control &= ~(K1X_MAC_SPEED_MASK | K1X_MAC_FULL_DUPLEX);

    if (emac->phy->duplex == DUPLEX_FULL)
    {
        control |= K1X_MAC_FULL_DUPLEX;
    }
    switch (emac->phy->speed)
    {
    case SPEED_1000:
        control |= K1X_MAC_SPEED_1000;
        break;
    case SPEED_100:
        control |= K1X_MAC_SPEED_100;
        break;
    case SPEED_10:
        control |= K1X_MAC_SPEED_10;
        break;
    default:
        return -RT_EINVAL;
    }

    k1x_emac_writel(emac, K1X_MAC_GLOBAL_CONTROL, control);
    emac->speed = emac->phy->speed;
    emac->duplex = emac->phy->duplex;
    return RT_EOK;
}

#ifdef RT_USING_SYSTEM_WORKQUEUE
static rt_bool_t k1x_emac_phy_poll_link(struct k1x_emac *emac)
{
    int bmsr;

    bmsr = rt_phy_read(emac->phy, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);
    if (bmsr < 0 || bmsr == 0xffff)
    {
        emac->phy->link = 0;
        return RT_FALSE;
    }

    /* BMSR link status is latched low, so read it again before deciding. */
    bmsr = rt_phy_read(emac->phy, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);
    if (bmsr < 0 || bmsr == 0xffff || !(bmsr & RT_BMSR_LSTATUS))
    {
        emac->phy->link = 0;
        return RT_FALSE;
    }

    emac->phy->link = 1;
    if (rt_genphy_parse_link(emac->phy))
    {
        emac->phy->link = 0;
        return RT_FALSE;
    }

    return RT_TRUE;
}

static void k1x_emac_link_work(struct rt_work *work, void *work_data)
{
    rt_bool_t link;
    struct k1x_emac *emac = work_data;

    RT_UNUSED(work);

    if (emac->stopping || !emac->phy)
    {
        return;
    }

    link = k1x_emac_phy_poll_link(emac);

    if (link)
    {
        if (!emac->link_up || emac->speed != emac->phy->speed ||
            emac->duplex != emac->phy->duplex)
        {
            if (!k1x_emac_adjust_link(emac))
            {
                LOG_I("%s: link up, %d Mbps, %s duplex",
                        rt_dm_dev_get_name(&emac->parent.parent),
                        emac->speed,
                        emac->duplex == DUPLEX_FULL ? "full" : "half");
            }
        }
        if (!emac->link_up)
        {
            emac->link_up = RT_TRUE;
            eth_device_linkchange(&emac->parent, RT_TRUE);
        }
    }
    else if (emac->link_up)
    {
        emac->link_up = RT_FALSE;
        emac->speed = 0;
        emac->duplex = -1;
        LOG_I("%s: link down", rt_dm_dev_get_name(&emac->parent.parent));
        eth_device_linkchange(&emac->parent, RT_FALSE);
    }

    if (!emac->stopping)
    {
        rt_work_submit(&emac->link_work,
                rt_tick_from_millisecond(K1X_EMAC_LINK_POLL_MS));
    }
}
#endif

static rt_err_t k1x_emac_eth_tx(rt_device_t dev, struct pbuf *p)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t index;
    rt_uint32_t next;
    rt_uint32_t length;
    rt_uint8_t *buffer;
    struct k1x_emac_desc *desc;
    struct k1x_emac *emac = raw_to_k1x_emac(dev);

    if (!emac->hw_ready || !emac->link_up || !emac->phy ||
        !emac->phy->link)
    {
        return -RT_EBUSY;
    }
    if (!p || !p->tot_len || p->tot_len > K1X_EMAC_BUFFER_SIZE)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&emac->tx_mutex, RT_WAITING_FOREVER);
    k1x_emac_tx_cleanup(emac);
    if (rt_sem_take(emac->tx_sem, rt_tick_from_millisecond(1000)) != RT_EOK)
    {
        k1x_emac_tx_cleanup(emac);
        if (rt_sem_take(emac->tx_sem, 0) != RT_EOK)
        {
            LOG_E("%s: TX ring timeout",
                    rt_dm_dev_get_name(&emac->parent.parent));
            err = -RT_ETIMEOUT;
            goto _out_unlock;
        }
    }

    index = emac->tx_head;
    next = k1x_emac_next(index, emac->tx_ring_num);
    desc = &emac->tx_ring[index];
    buffer = emac->tx_buffers + index * K1X_EMAC_BUFFER_SIZE;
    length = p->tot_len;
    pbuf_copy_partial(p, buffer, length, 0);

    desc->des0 = 0;
    desc->des1 = (length & K1X_DESC_BUFFER1_SIZE_MASK) |
            K1X_TX_DESC_FIRST | K1X_TX_DESC_LAST | K1X_TX_DESC_IRQ;
    if (index == emac->tx_ring_num - 1)
    {
        desc->des1 |= K1X_DESC_END_RING;
    }
    desc->des2 = (rt_uint32_t)(emac->tx_buffers_dma +
            index * K1X_EMAC_BUFFER_SIZE);
    desc->des3 = 0;
    rt_hw_wmb();
    desc->des0 = K1X_DESC_OWN;
    rt_hw_wmb();

    {
        rt_ubase_t level = rt_spin_lock_irqsave(&emac->tx_lock);
        emac->tx_head = next;
        rt_spin_unlock_irqrestore(&emac->tx_lock, level);
    }

    k1x_emac_writel(emac, K1X_DMA_TX_POLL_DEMAND, 0xff);
    rt_hw_dsb();

_out_unlock:
    rt_mutex_release(&emac->tx_mutex);
    return err;
}

static rt_bool_t k1x_emac_rx_desc_valid(rt_uint32_t des0)
{
    rt_uint32_t status = (des0 & K1X_RX_APP_STATUS_MASK) >>
            K1X_RX_APP_STATUS_SHIFT;
    rt_uint32_t length = des0 & K1X_RX_FRAME_LENGTH_MASK;

    if (!(des0 & K1X_RX_DESC_FIRST) || !(des0 & K1X_RX_DESC_LAST))
    {
        return RT_FALSE;
    }
    if (status & K1X_RX_ERROR_MASK)
    {
        return RT_FALSE;
    }
    return length > K1X_EMAC_FCS_SIZE &&
            length <= K1X_EMAC_BUFFER_SIZE;
}

static struct pbuf *k1x_emac_eth_rx(rt_device_t dev)
{
    struct k1x_emac *emac = raw_to_k1x_emac(dev);

    for (rt_uint32_t count = 0; count < emac->rx_ring_num; ++count)
    {
        rt_uint32_t index = emac->rx_tail;
        struct k1x_emac_desc *desc = &emac->rx_ring[index];
        rt_uint32_t des0;
        struct pbuf *p = RT_NULL;

        rt_hw_rmb();
        des0 = desc->des0;
        if (des0 & K1X_DESC_OWN)
        {
            return RT_NULL;
        }

        if (k1x_emac_rx_desc_valid(des0))
        {
            rt_uint32_t length = (des0 & K1X_RX_FRAME_LENGTH_MASK) -
                    K1X_EMAC_FCS_SIZE;
            rt_uint8_t *buffer = emac->rx_buffers +
                    index * K1X_EMAC_BUFFER_SIZE;

            p = pbuf_alloc(PBUF_RAW, length, PBUF_RAM);
            if (p)
            {
                pbuf_take(p, buffer, length);
            }
        }

        k1x_emac_rx_refill(emac, index);
        emac->rx_tail = k1x_emac_next(index, emac->rx_ring_num);
        k1x_emac_writel(emac, K1X_DMA_RX_POLL_DEMAND, 0xff);

        if (p)
        {
            return p;
        }
    }

    return RT_NULL;
}

static rt_err_t k1x_emac_eth_control(rt_device_t dev, int cmd, void *args)
{
    struct k1x_emac *emac = raw_to_k1x_emac(dev);

    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (!args)
        {
            return -RT_EINVAL;
        }
        rt_memcpy(args, emac->mac, sizeof(emac->mac));
        return RT_EOK;
    default:
        return -RT_EINVAL;
    }
}

static void k1x_emac_isr(int irq, void *param)
{
    rt_uint32_t status;
#ifdef RT_ETHERNET_K1X_EMAC_PTP
    rt_uint32_t ptp_status = 0;
#endif
    struct k1x_emac *emac = param;

    RT_UNUSED(irq);

    status = k1x_emac_readl(emac, K1X_DMA_STATUS_IRQ);
    status &= K1X_DMA_IRQ_ALL;
#ifdef RT_ETHERNET_K1X_EMAC_PTP
    if (emac->ptp_registered)
    {
        ptp_status = k1x_emac_readl(emac, K1X_PTP_IRQ_STATUS) &
                K1X_PTP_IRQ_ALL;
    }
    if (!status && !ptp_status)
#else
    if (!status)
#endif
    {
        return;
    }
    if (status)
    {
        k1x_emac_writel(emac, K1X_DMA_STATUS_IRQ, status);
    }
#ifdef RT_ETHERNET_K1X_EMAC_PTP
    if (ptp_status)
    {
        k1x_emac_writel(emac, K1X_PTP_IRQ_STATUS, ptp_status);
    }
#endif

    if (status & (K1X_DMA_IRQ_TX_DONE | K1X_DMA_IRQ_TX_UNAVAILABLE |
                  K1X_DMA_IRQ_TX_STOPPED))
    {
        k1x_emac_tx_cleanup(emac);
    }
    if (status & K1X_DMA_IRQ_RX_UNAVAILABLE)
    {
        k1x_emac_writel(emac, K1X_DMA_RX_POLL_DEMAND, 0xff);
    }
    if (emac->net_registered &&
        (status & (K1X_DMA_IRQ_RX_DONE | K1X_DMA_IRQ_RX_UNAVAILABLE |
                   K1X_DMA_IRQ_RX_STOPPED | K1X_DMA_IRQ_RX_MISSED)))
    {
        eth_device_ready(&emac->parent);
    }
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops k1x_emac_device_ops =
{
    .control = k1x_emac_eth_control,
};
#endif

static rt_err_t k1x_emac_net_register(struct k1x_emac *emac)
{
    rt_err_t err;

#ifdef RT_USING_DEVICE_OPS
    emac->parent.parent.ops = &k1x_emac_device_ops;
#else
    emac->parent.parent.control = k1x_emac_eth_control;
#endif
    emac->parent.eth_tx = k1x_emac_eth_tx;
    emac->parent.eth_rx = k1x_emac_eth_rx;

    err = rt_dm_dev_set_name_auto(&emac->parent.parent, "e");
    if (err < 0)
    {
        return err;
    }

    if (emac->irq >= 0)
    {
        rt_hw_interrupt_install(emac->irq, k1x_emac_isr, emac,
                "k1x-emac");
        rt_hw_interrupt_umask(emac->irq);
        emac->irq_installed = RT_TRUE;
    }

    err = eth_device_init(&emac->parent,
            rt_dm_dev_get_name(&emac->parent.parent));
    if (err)
    {
        if (emac->irq_installed)
        {
            rt_hw_interrupt_mask(emac->irq);
            rt_pic_detach_irq(emac->irq, emac);
            emac->irq_installed = RT_FALSE;
        }
        return err;
    }

    emac->net_registered = RT_TRUE;
    eth_device_linkchange(&emac->parent, RT_FALSE);

#ifdef RT_ETHERNET_K1X_EMAC_PTP
    if ((err = k1x_emac_ptp_register(emac)))
    {
        LOG_W("%s: PTP registration failed: %s",
                rt_dm_dev_get_name(&emac->parent.parent),
                rt_strerror(err));
    }
#endif

    k1x_emac_writel(emac, K1X_DMA_INTERRUPT_ENABLE,
            K1X_DMA_IRQ_DEFAULT);
    k1x_emac_hw_start(emac);

#ifdef RT_USING_SYSTEM_WORKQUEUE
    rt_work_init(&emac->link_work, k1x_emac_link_work, emac);
    emac->link_work_inited = RT_TRUE;
    rt_work_submit(&emac->link_work, 0);
#else
    rt_phy_startup(emac->phy);
    if (emac->phy->link && !k1x_emac_adjust_link(emac))
    {
        emac->link_up = RT_TRUE;
        eth_device_linkchange(&emac->parent, RT_TRUE);
    }
#endif

    return RT_EOK;
}

static void k1x_emac_net_unregister(struct k1x_emac *emac)
{
#ifdef RT_USING_SYSTEM_WORKQUEUE
    emac->stopping = RT_TRUE;
    if (emac->link_work_inited)
    {
        rt_work_cancel(&emac->link_work);
        emac->link_work_inited = RT_FALSE;
    }
#endif

    k1x_emac_writel(emac, K1X_DMA_INTERRUPT_ENABLE, 0);
    if (emac->irq_installed)
    {
        rt_hw_interrupt_mask(emac->irq);
        rt_pic_detach_irq(emac->irq, emac);
        emac->irq_installed = RT_FALSE;
    }
    if (emac->net_registered)
    {
        eth_device_linkchange(&emac->parent, RT_FALSE);
        eth_device_deinit(&emac->parent);
        emac->net_registered = RT_FALSE;
    }
}

static void k1x_emac_release(struct k1x_emac *emac)
{
    if (!emac)
    {
        return;
    }

#ifdef RT_ETHERNET_K1X_EMAC_PTP
    k1x_emac_ptp_unregister(emac);
#endif
    if (emac->base && emac->hw_ready)
    {
        k1x_emac_reset_hw(emac);
        emac->hw_ready = RT_FALSE;
    }
    if (emac->phy)
    {
        rt_phy_shutdown(emac->phy);
        emac->phy = RT_NULL;
    }
    k1x_emac_mdio_unregister(emac);
    k1x_emac_rings_deinit(emac);
    k1x_emac_dma_free(emac);

    if (emac->mdio_lock_inited)
    {
        rt_mutex_detach(&emac->mdio_lock);
        emac->mdio_lock_inited = RT_FALSE;
    }
    if (!rt_is_err_or_null(emac->rstc))
    {
        rt_reset_control_assert(emac->rstc);
        rt_reset_control_put(emac->rstc);
    }
    if (!rt_is_err_or_null(emac->mac_clk))
    {
        rt_clk_disable_unprepare(emac->mac_clk);
        rt_clk_put(emac->mac_clk);
    }
    if (emac->dline_reg)
    {
        rt_iounmap(emac->dline_reg);
    }
    if (emac->ctrl_reg)
    {
        rt_iounmap(emac->ctrl_reg);
    }
    if (emac->base)
    {
        rt_iounmap(emac->base);
    }
}

static rt_err_t k1x_emac_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    int phy_addr;
    struct rt_device *dev = &pdev->parent;
    struct k1x_emac *emac = rt_calloc(1, sizeof(*emac));

    if (!emac)
    {
        return -RT_ENOMEM;
    }
    emac->dev = dev;
    emac->irq = rt_dm_dev_get_irq(dev, 0);
    emac->speed = 0;
    emac->duplex = -1;

    emac->base = rt_dm_dev_iomap(dev, 0);
    if (!emac->base)
    {
        err = -RT_EIO;
        goto _fail;
    }
    if ((err = k1x_emac_parse_dt(emac)))
    {
        goto _fail;
    }

    emac->mac_clk = rt_clk_get_by_name(dev, "emac-clk");
    if (rt_is_err_or_null(emac->mac_clk))
    {
        LOG_E("emac-clk is missing");
        err = -RT_ENOSYS;
        goto _fail;
    }
    if ((err = rt_clk_prepare_enable(emac->mac_clk)))
    {
        goto _fail;
    }

    emac->rstc = rt_reset_control_get_by_name(dev, "emac-reset");
    if (rt_is_err_or_null(emac->rstc))
    {
        LOG_E("emac-reset is missing");
        err = -RT_ENOSYS;
        goto _fail;
    }
    if ((err = rt_reset_control_deassert(emac->rstc)))
    {
        goto _fail;
    }

    rt_mutex_init(&emac->mdio_lock, "k1xmdio", RT_IPC_FLAG_PRIO);
    emac->mdio_lock_inited = RT_TRUE;
    k1x_emac_config_interface(emac);
    if ((err = k1x_emac_config_clock_phase(emac)))
    {
        goto _fail;
    }
    k1x_emac_external_phy_reset(emac);

    if ((err = k1x_emac_dma_alloc(emac)))
    {
        goto _fail;
    }
    if ((err = k1x_emac_rings_init(emac)))
    {
        goto _fail;
    }
    if ((err = k1x_emac_hw_init(emac)))
    {
        goto _fail;
    }
    if ((err = k1x_emac_mdio_register(emac)))
    {
        goto _fail;
    }

    phy_addr = k1x_emac_find_phy_addr(emac);
    if (phy_addr < 0)
    {
        LOG_E("no PHY found on MDIO");
        err = -RT_ENOSYS;
        goto _fail;
    }
    LOG_D("%s: PHY attach begin at address %d",
            rt_dm_dev_get_name(dev), phy_addr);
    emac->phy = rt_phy_get_device(emac->mii, dev->ofw_node, phy_addr,
            emac->phy_interface);
    if (!emac->phy)
    {
        LOG_E("PHY attach failed at address %d", phy_addr);
        err = -RT_ERROR;
        goto _fail;
    }
    LOG_D("%s: PHY attach done, config begin", rt_dm_dev_get_name(dev));
    if ((err = rt_phy_config(emac->phy)) < 0)
    {
        LOG_E("PHY config failed: %s", rt_strerror(err));
        goto _fail;
    }
    LOG_D("%s: PHY config done", rt_dm_dev_get_name(dev));

    if (rt_ofw_get_mac_addr(dev->ofw_node, emac->mac))
    {
        ethernet_random_addr(&emac->parent, emac->mac);
    }
    k1x_emac_set_mac_address(emac);

    LOG_D("%s: network registration begin", rt_dm_dev_get_name(dev));
    if ((err = k1x_emac_net_register(emac)))
    {
        LOG_E("%s: network registration failed: %s",
                rt_dm_dev_get_name(dev), rt_strerror(err));
        goto _fail;
    }

    dev->user_data = emac;
    LOG_D("%s: PHY addr %d, MAC %02x:%02x:%02x:%02x:%02x:%02x, rings %u/%u",
            rt_dm_dev_get_name(&emac->parent.parent), phy_addr,
            emac->mac[0], emac->mac[1], emac->mac[2], emac->mac[3],
            emac->mac[4], emac->mac[5], emac->tx_ring_num,
            emac->rx_ring_num);

    return RT_EOK;

_fail:
    k1x_emac_release(emac);
    rt_free(emac);
    return err;
}

static rt_err_t k1x_emac_remove(struct rt_platform_device *pdev)
{
    struct k1x_emac *emac = pdev->parent.user_data;

    if (!emac)
    {
        return RT_EOK;
    }

    pdev->parent.user_data = RT_NULL;
    k1x_emac_net_unregister(emac);
    k1x_emac_release(emac);
    rt_free(emac);
    return RT_EOK;
}

static const struct rt_ofw_node_id k1x_emac_ofw_ids[] =
{
    { .compatible = "spacemit,k1x-emac" },
    { /* sentinel */ }
};

static struct rt_platform_driver k1x_emac_driver =
{
    .name = "k1x-emac",
    .ids = k1x_emac_ofw_ids,
    .probe = k1x_emac_probe,
    .remove = k1x_emac_remove,
};
RT_PLATFORM_DRIVER_EXPORT(k1x_emac_driver);
