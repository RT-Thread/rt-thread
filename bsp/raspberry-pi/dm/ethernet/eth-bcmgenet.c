/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "eth.bcmgenet"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#include <cpuport.h>
#include <drivers/dma.h>
#include <drivers/phy.h>
#include <netif/ethernetif.h>
#ifdef RT_USING_SYSTEM_WORKQUEUE
#include <ipc/workqueue.h>
#endif
#include <firmware-raspberrypi.h>

#define SYS_REV_CTRL                    0x00

#define SYS_PORT_CTRL                   0x04
#define PORT_MODE_EXT_GPHY              3

#define GENET_SYS_OFF                   0x0000
#define SYS_RBUF_FLUSH_CTRL             (GENET_SYS_OFF  + 0x08)
#define SYS_TBUF_FLUSH_CTRL             (GENET_SYS_OFF  + 0x0c)

#define GENET_EXT_OFF                   0x0080
#define EXT_RGMII_OOB_CTRL              (GENET_EXT_OFF + 0x0c)
#define RGMII_LINK                      RT_BIT(4)
#define OOB_DISABLE                     RT_BIT(5)
#define RGMII_MODE_EN                   RT_BIT(6)
#define ID_MODE_DIS                     RT_BIT(16)

#define GENET_RBUF_OFF                  0x0300
#define RBUF_CTRL                       (GENET_RBUF_OFF + 0x00)
#define RBUF_64B_EN                     RT_BIT(0)
#define RBUF_ALIGN_2B                   RT_BIT(1)
#define RBUF_CHK_CTRL                   (GENET_RBUF_OFF + 0x14)
#define RBUF_RXCHK_EN                   RT_BIT(0)
#define RBUF_L3_PARSE_DIS               RT_BIT(1)
#define RBUF_TBUF_SIZE_CTRL             (GENET_RBUF_OFF + 0xb4)

#define GENET_TBUF_OFF                  0x0600
#define TBUF_CTRL                       (GENET_TBUF_OFF + 0x00)
#define TBUF_64B_EN                     RT_BIT(0)

#define GENET_UMAC_OFF                  0x0800
#define UMAC_MIB_CTRL                   (GENET_UMAC_OFF + 0x580)
#define UMAC_MAX_FRAME_LEN              (GENET_UMAC_OFF + 0x014)
#define UMAC_MAC0                       (GENET_UMAC_OFF + 0x00c)
#define UMAC_MAC1                       (GENET_UMAC_OFF + 0x010)
#define UMAC_CMD                        (GENET_UMAC_OFF + 0x008)
#define MDIO_CMD                        (GENET_UMAC_OFF + 0x614)
#define UMAC_TX_FLUSH                   (GENET_UMAC_OFF + 0x334)
#define MDIO_START_BUSY                 RT_BIT(29)
#define MDIO_READ_FAIL                  RT_BIT(28)
#define MDIO_RD                         (2 << 26)
#define MDIO_WR                         RT_BIT(26)
#define MDIO_PMD_SHIFT                  21
#define MDIO_PMD_MASK                   0x1f
#define MDIO_REG_SHIFT                  16
#define MDIO_REG_MASK                   0x1f

#define CMD_TX_EN                       RT_BIT(0)
#define CMD_RX_EN                       RT_BIT(1)
#define UMAC_SPEED_10                   0
#define UMAC_SPEED_100                  1
#define UMAC_SPEED_1000                 2
#define UMAC_SPEED_2500                 3
#define CMD_SPEED_SHIFT                 2
#define CMD_SPEED_MASK                  3
#define CMD_HD_EN                       RT_BIT(10)
#define CMD_RX_PAUSE_IGNORE             RT_BIT(8)
#define CMD_TX_PAUSE_IGNORE             RT_BIT(28)
#define CMD_SW_RESET                    RT_BIT(13)
#define CMD_LCL_LOOP_EN                 RT_BIT(15)
#define CMD_PROMISC                     RT_BIT(4)

#define UMAC_MDF_CTRL                   (GENET_UMAC_OFF + 0x650)
#define UMAC_MDF_ADDR                   (GENET_UMAC_OFF + 0x654)
#define MAX_MDF_FILTER                  17

#define MIB_RESET_RX                    RT_BIT(0)
#define MIB_RESET_RUNT                  RT_BIT(1)
#define MIB_RESET_TX                    RT_BIT(2)

/* Total number of Buffer Descriptors, same for Rx/Tx */
#define TOTAL_DESCS                     256
#define RX_DESCS                        TOTAL_DESCS
#define DESC_INDEX                      16
#define DEFAULT_RING                    16
#define TX_DESCS                        TOTAL_DESCS

/* Per-ring register block size and total ring control area (rings 0..16). */
#define DMA_RING_SIZE                   0x40
#define DMA_RINGS_SIZE                  (DMA_RING_SIZE * (DESC_INDEX + 1))

/*
 * Body(1500) + EH_SIZE(14) + VLANTAG(4) + BRCMTAG(6) + FCS(4) = 1528.
 * 1536 is multiple of 256 bytes
 */
#define ENET_BRCM_TAG_LEN               6
#define ENET_PAD                        8
#define ENET_DATA_LEN                   1500    /* Max. octets in payload */
#define ENET_HLEN                       14      /* Total octets in header */
#define ENET_FCS_LEN                    4       /* Octets in the FCS */
#define ENET_VLAN_HLEN                  4
#define ENET_MAX_MTU_SIZE               (ENET_DATA_LEN + ENET_HLEN + ENET_VLAN_HLEN + ENET_BRCM_TAG_LEN + ENET_FCS_LEN + ENET_PAD)

/* Tx/Rx Dma Descriptor common bits */
#define DMA_EN                          RT_BIT(0)
#define DMA_RING_BUF_EN_SHIFT           0x01
#define DMA_RING_BUF_EN_MASK            0xffff
#define DMA_BUFLENGTH_MASK              0x0fff
#define DMA_BUFLENGTH_SHIFT             16
#define DMA_RING_SIZE_SHIFT             16
#define DMA_OWN                         0x8000
#define DMA_EOP                         0x4000
#define DMA_SOP                         0x2000
#define DMA_WRAP                        0x1000
#define DMA_MAX_BURST_LENGTH            0x8
/* Tx specific DMA descriptor bits */
#define DMA_TX_UNDERRUN                 0x0200
#define DMA_TX_APPEND_CRC               0x0040
#define DMA_TX_OW_CRC                   0x0020
#define DMA_TX_DO_CSUM                  0x0010
#define DMA_TX_QTAG_SHIFT               7

/* DMA descriptor */
#define DMA_DESC_LENGTH_STATUS          0x00
#define DMA_DESC_ADDRESS_LO             0x04
#define DMA_DESC_ADDRESS_HI             0x08
#define DMA_DESC_SIZE                   12

#define GENET_RX_OFF                    0x2000
#define GENET_RDMA_REG_OFF              (GENET_RX_OFF + TOTAL_DESCS * DMA_DESC_SIZE)
#define GENET_TX_OFF                    0x4000
#define GENET_TDMA_REG_OFF              (GENET_TX_OFF + TOTAL_DESCS * DMA_DESC_SIZE)

#define DMA_FC_THRESH_HI                (RX_DESCS >> 4)
#define DMA_FC_THRESH_LO                5
#define DMA_FC_THRESH_VALUE             ((DMA_FC_THRESH_LO << 16) | DMA_FC_THRESH_HI)

#define DMA_XOFF_THRESHOLD_SHIFT        16

#define TDMA_RING_REG_BASE              (GENET_TDMA_REG_OFF + DEFAULT_RING * DMA_RING_SIZE)
#define TDMA_READ_PTR                   (TDMA_RING_REG_BASE + 0x00)
#define TDMA_CONS_INDEX                 (TDMA_RING_REG_BASE + 0x08)
#define TDMA_PROD_INDEX                 (TDMA_RING_REG_BASE + 0x0c)
#define DMA_RING_BUF_SIZE               0x10
#define DMA_START_ADDR                  0x14
#define DMA_END_ADDR                    0x1c
#define DMA_MBUF_DONE_THRESH            0x24
#define TDMA_FLOW_PERIOD                (TDMA_RING_REG_BASE + 0x28)
#define TDMA_WRITE_PTR                  (TDMA_RING_REG_BASE + 0x2c)

#define RDMA_RING_REG_BASE              (GENET_RDMA_REG_OFF + DEFAULT_RING * DMA_RING_SIZE)
#define RDMA_WRITE_PTR                  (RDMA_RING_REG_BASE + 0x00)
#define RDMA_PROD_INDEX                 (RDMA_RING_REG_BASE + 0x08)
#define RDMA_CONS_INDEX                 (RDMA_RING_REG_BASE + 0x0c)
#define RDMA_XON_XOFF_THRESH            (RDMA_RING_REG_BASE + 0x28)
#define RDMA_READ_PTR                   (RDMA_RING_REG_BASE + 0x2c)

#define TDMA_REG_BASE                   (GENET_TDMA_REG_OFF + DMA_RINGS_SIZE)
#define RDMA_REG_BASE                   (GENET_RDMA_REG_OFF + DMA_RINGS_SIZE)
#define DMA_RING_CFG                    0x00
#define DMA_CTRL                        0x04
#define DMA_SCB_BURST_SIZE              0x0c

#define DMA_P_INDEX_MASK                0xffff

#define RX_BUF_LENGTH                   2048
#define RX_TOTAL_BUFSIZE                (RX_BUF_LENGTH * RX_DESCS)
#define TX_TOTAL_BUFSIZE                RX_TOTAL_BUFSIZE
#define GENET_RX_RSB_SIZE               66
#define GENET_TX_TSB_SIZE               64
#define RX_BUF_OFFSET                   2

#define PHY_RETRY_INTERVAL_MS           2000
#define PHY_RETRY_MAX                   15

#define GENET_INTRL2_0_OFF              0x0200
#define GENET_INTRL2_1_OFF              0x0240
/* uniMac intrl2 registers */
#define INTRL2_CPU_STAT                 0x00
#define INTRL2_CPU_SET                  0x04
#define INTRL2_CPU_CLEAR                0x08
#define INTRL2_CPU_MASK_STATUS          0x0c
#define INTRL2_CPU_MASK_SET             0x10
#define INTRL2_CPU_MASK_CLEAR           0x14

/* INTRL2 instance 0 definitions */
#define UMAC_IRQ_SCB                    RT_BIT(0)
#define UMAC_IRQ_EPHY                   RT_BIT(1)
#define UMAC_IRQ_PHY_DET_R              RT_BIT(2)
#define UMAC_IRQ_PHY_DET_F              RT_BIT(3)
#define UMAC_IRQ_LINK_UP                RT_BIT(4)
#define UMAC_IRQ_LINK_DOWN              RT_BIT(5)
#define UMAC_IRQ_LINK_EVENT             (UMAC_IRQ_LINK_UP | UMAC_IRQ_LINK_DOWN)
#define UMAC_IRQ_UMAC                   RT_BIT(6)
#define UMAC_IRQ_UMAC_TSV               RT_BIT(7)
#define UMAC_IRQ_TBUF_UNDERRUN          RT_BIT(8)
#define UMAC_IRQ_RBUF_OVERFLOW          RT_BIT(9)
#define UMAC_IRQ_HFB_SM                 RT_BIT(10)
#define UMAC_IRQ_HFB_MM                 RT_BIT(11)
#define UMAC_IRQ_MPD_R                  RT_BIT(12)
#define UMAC_IRQ_WAKE_EVENT             (UMAC_IRQ_HFB_SM | UMAC_IRQ_HFB_MM | UMAC_IRQ_MPD_R)
#define UMAC_IRQ_RXDMA_MBDONE           RT_BIT(13)
#define UMAC_IRQ_RXDMA_PDONE            RT_BIT(14)
#define UMAC_IRQ_RXDMA_BDONE            RT_BIT(15)
#define UMAC_IRQ_RXDMA_DONE             UMAC_IRQ_RXDMA_MBDONE
#define UMAC_IRQ_TXDMA_MBDONE           RT_BIT(16)
#define UMAC_IRQ_TXDMA_PDONE            RT_BIT(17)
#define UMAC_IRQ_TXDMA_BDONE            RT_BIT(18)
#define UMAC_IRQ_TXDMA_DONE             UMAC_IRQ_TXDMA_MBDONE

/* Only valid for GENETv3+ */
#define UMAC_IRQ_MDIO_DONE              RT_BIT(23)
#define UMAC_IRQ_MDIO_ERROR             RT_BIT(24)

/* INTRL2 instance 1 definitions */
#define UMAC_IRQ1_RX_INTR_SHIFT         16
#define UMAC_IRQ1_TX_INTR(ring)         RT_BIT(ring)
#define UMAC_IRQ1_RX_INTR(ring)         RT_BIT(UMAC_IRQ1_RX_INTR_SHIFT + (ring))

#define HWREGCLR32(reg, clr)            HWREG32(reg) &= ~(clr)
#define HWREGSET32(reg, set)            HWREG32(reg) |= (set)
#define HWREGCLRSET32(reg, clr, set)    HWREG32(reg) = (HWREG32(reg) & ~(clr)) | (set)

struct bcmgenet_eth
{
    struct eth_device parent;
    struct rt_phy_device *phy;
    struct rt_device *dev;

    void *base;
    void *tx_desc_base;
    void *rx_desc_base;
    int irq0, irq1;

    rt_uint8_t mac[6];
    rt_uint32_t speed;
    rt_phy_interface interface;

    int tx_index;
    int rx_index;
    int c_index;
    rt_uint8_t *rxbuffer;
    rt_uint8_t *txbuffer;
    rt_ubase_t rxbuffer_dma;
    rt_ubase_t txbuffer_dma;

    struct rt_semaphore tx_done;

#ifdef RT_USING_SYSTEM_WORKQUEUE
    struct rt_work link_work;
    struct rt_work phy_retry_work;
    int phy_retry_count;
#endif

    rt_size_t dma_buf_size;

#ifdef RT_USING_OFW
    struct rt_ofw_node *phy_np;
#endif
};

#define raw_to_bcmgenet_eth(raw) \
        rt_container_of(rt_container_of(raw, struct eth_device, parent), struct bcmgenet_eth, parent)

static void bcmgenet_umac_reset(struct bcmgenet_eth *eth)
{
    rt_uint32_t reg;

    reg = HWREG32(eth->base + SYS_RBUF_FLUSH_CTRL);
    reg |= RT_BIT(1);
    HWREG32(eth->base + SYS_RBUF_FLUSH_CTRL) = reg;
    rt_hw_us_delay(10);

    reg &= ~RT_BIT(1);
    HWREG32(eth->base + SYS_RBUF_FLUSH_CTRL) = reg;
    rt_hw_us_delay(10);

    HWREG32(eth->base + SYS_RBUF_FLUSH_CTRL) = 0;
    rt_hw_us_delay(10);

    HWREG32(eth->base + UMAC_CMD) = 0;

    HWREG32(eth->base + UMAC_CMD) = CMD_SW_RESET | CMD_LCL_LOOP_EN;
    rt_hw_us_delay(2);
    HWREG32(eth->base + UMAC_CMD) = 0;

    /* Clear tx/rx counter */
    HWREG32(eth->base + UMAC_MIB_CTRL) = MIB_RESET_RX | MIB_RESET_TX | MIB_RESET_RUNT;
    HWREG32(eth->base + UMAC_MIB_CTRL) = 0;

    HWREG32(eth->base + UMAC_MAX_FRAME_LEN) = ENET_MAX_MTU_SIZE;

    /* Enable 64-byte transmit status block */
    reg = HWREG32(eth->base + TBUF_CTRL);
    reg |= TBUF_64B_EN;
    HWREG32(eth->base + TBUF_CTRL) = reg;

    /* Enable 2-byte IP align (matches working raspi4 drv_eth, no 64B RSB). */
    reg = HWREG32(eth->base + RBUF_CTRL);
    reg |= RBUF_ALIGN_2B;
    reg &= ~RBUF_64B_EN;
    HWREG32(eth->base + RBUF_CTRL) = reg;

    reg = HWREG32(eth->base + RBUF_CHK_CTRL);
    reg |= RBUF_RXCHK_EN | RBUF_L3_PARSE_DIS;
    HWREG32(eth->base + RBUF_CHK_CTRL) = reg;

    HWREG32(eth->base + RBUF_TBUF_SIZE_CTRL) = 1;
}

static void bcmgenet_gmac_write_hwaddr(struct bcmgenet_eth *eth)
{
    rt_uint32_t reg;
    rt_uint8_t *addr = eth->mac;

    reg = addr[0] << 24 | addr[1] << 16 | addr[2] << 8 | addr[3];
    HWREG32(eth->base + UMAC_MAC0) = reg;
    rt_hw_wmb();

    reg = addr[4] << 8 | addr[5];
    HWREG32(eth->base + UMAC_MAC1) = reg;
    rt_hw_wmb();
}

static void bcmgenet_disable_dma(struct bcmgenet_eth *eth)
{
    HWREGCLR32(eth->base + TDMA_REG_BASE + DMA_CTRL, DMA_EN);
    HWREGCLR32(eth->base + RDMA_REG_BASE + DMA_CTRL, DMA_EN);

    HWREG32(eth->base + UMAC_TX_FLUSH) = 1;
    rt_hw_us_delay(10);
    HWREG32(eth->base + UMAC_TX_FLUSH) = 0;
}

static void bcmgenet_enable_dma(struct bcmgenet_eth *eth)
{
    rt_uint32_t dma_ctrl = (1 << (DEFAULT_RING + DMA_RING_BUF_EN_SHIFT)) | DMA_EN;

    HWREG32(eth->base + TDMA_REG_BASE + DMA_CTRL) = dma_ctrl;
    HWREGSET32(eth->base + RDMA_REG_BASE + DMA_CTRL, dma_ctrl);
}

static void bcmgenet_rx_descs_init(struct bcmgenet_eth *eth)
{
    void *desc = eth->rx_desc_base;
    rt_ubase_t rxbuffs_dma = eth->rxbuffer_dma;
    rt_uint32_t len_stat = (RX_BUF_LENGTH << DMA_BUFLENGTH_SHIFT) | DMA_OWN;

    for (int i = 0; i < RX_DESCS; ++i)
    {
        HWREG32(desc + DMA_DESC_ADDRESS_LO) = rt_lower_32_bits(rxbuffs_dma);
        HWREG32(desc + DMA_DESC_ADDRESS_HI) = rt_upper_32_bits(rxbuffs_dma);
        HWREG32(desc + DMA_DESC_LENGTH_STATUS) = len_stat;

        desc += DMA_DESC_SIZE;
        rxbuffs_dma += RX_BUF_LENGTH;
    }
}

static void bcmgenet_rx_ring_init(struct bcmgenet_eth *eth)
{
    HWREG32(eth->base + RDMA_REG_BASE + DMA_SCB_BURST_SIZE) = DMA_MAX_BURST_LENGTH;

    HWREG32(eth->base + RDMA_RING_REG_BASE + DMA_START_ADDR) = 0x0;
    HWREG32(eth->base + RDMA_READ_PTR) = 0x0;
    HWREG32(eth->base + RDMA_WRITE_PTR) = 0x0;
    HWREG32(eth->base + RDMA_RING_REG_BASE + DMA_END_ADDR) = RX_DESCS * DMA_DESC_SIZE / 4 - 1;

    HWREG32(eth->base + RDMA_PROD_INDEX) = 0;
    HWREG32(eth->base + RDMA_CONS_INDEX) = 0;
    eth->c_index = 0;
    eth->rx_index = 0;

    HWREG32(eth->base + RDMA_RING_REG_BASE + DMA_RING_BUF_SIZE) =
            (RX_DESCS << DMA_RING_SIZE_SHIFT) | RX_BUF_LENGTH;
    HWREG32(eth->base + RDMA_RING_REG_BASE + DMA_MBUF_DONE_THRESH) = 0x1;
    HWREG32(eth->base + RDMA_XON_XOFF_THRESH) =
            (DMA_FC_THRESH_LO << DMA_XOFF_THRESHOLD_SHIFT) | DMA_FC_THRESH_HI;
    HWREG32(eth->base + RDMA_REG_BASE + DMA_RING_CFG) = 1 << DEFAULT_RING;
}

static void bcmgenet_tx_ring_init(struct bcmgenet_eth *eth)
{
    HWREG32(eth->base + TDMA_REG_BASE + DMA_SCB_BURST_SIZE) = DMA_MAX_BURST_LENGTH;

    HWREG32(eth->base + TDMA_RING_REG_BASE + DMA_START_ADDR) = 0x0;
    HWREG32(eth->base + TDMA_READ_PTR) = 0x0;
    HWREG32(eth->base + TDMA_WRITE_PTR) = 0x0;
    HWREG32(eth->base + TDMA_RING_REG_BASE + DMA_END_ADDR) = TX_DESCS * DMA_DESC_SIZE / 4 - 1;

    HWREG32(eth->base + TDMA_PROD_INDEX) = 0;
    HWREG32(eth->base + TDMA_CONS_INDEX) = 0;
    eth->tx_index = 0;

    HWREG32(eth->base + TDMA_RING_REG_BASE + DMA_MBUF_DONE_THRESH) = 0x1;
    HWREG32(eth->base + TDMA_FLOW_PERIOD) = 0x0;
    HWREG32(eth->base + TDMA_RING_REG_BASE + DMA_RING_BUF_SIZE) =
            (TX_DESCS << DMA_RING_SIZE_SHIFT) | RX_BUF_LENGTH;

    HWREG32(eth->base + TDMA_REG_BASE + DMA_RING_CFG) = 1 << DEFAULT_RING;
}

static void bcmgenet_mii_config(struct bcmgenet_eth *eth)
{
    rt_uint32_t reg;

    HWREG32(eth->base + SYS_PORT_CTRL) = PORT_MODE_EXT_GPHY;

    reg = HWREG32(eth->base + EXT_RGMII_OOB_CTRL);
    reg &= ~OOB_DISABLE;
    reg &= ~ID_MODE_DIS;
    if (eth->interface == RT_PHY_INTERFACE_MODE_RGMII)
        reg |= ID_MODE_DIS;
    reg |= RGMII_MODE_EN;
    HWREG32(eth->base + EXT_RGMII_OOB_CTRL) = reg;
}

static void bcmgenet_set_rx_mode(struct bcmgenet_eth *eth)
{
    /* Promiscuous: bypass MDF until full multicast/uc filter support. */
    HWREGSET32(eth->base + UMAC_CMD, CMD_PROMISC);
    HWREG32(eth->base + UMAC_MDF_CTRL) = 0;
}

static rt_err_t bcmgenet_adjust_link(struct bcmgenet_eth *eth, rt_bool_t link_up)
{
    rt_uint32_t reg, cmd_bits = 0;
    struct rt_phy_device *phy = eth->phy;

    reg = HWREG32(eth->base + EXT_RGMII_OOB_CTRL);
    if (link_up)
        reg |= RGMII_LINK;
    else
        reg &= ~RGMII_LINK;
    HWREG32(eth->base + EXT_RGMII_OOB_CTRL) = reg;

    if (!link_up)
        return RT_EOK;

    switch (phy->speed)
    {
    case SPEED_1000:
        cmd_bits = UMAC_SPEED_1000;
        break;

    case SPEED_100:
        cmd_bits = UMAC_SPEED_100;
        break;

    case SPEED_10:
        cmd_bits = UMAC_SPEED_10;
        break;

    default:
        LOG_E("Unsupported PHY speed: %d", phy->speed);
        return -RT_EINVAL;
    }
    cmd_bits <<= CMD_SPEED_SHIFT;

    if (phy->duplex != DUPLEX_FULL)
        cmd_bits |= CMD_HD_EN | CMD_RX_PAUSE_IGNORE | CMD_TX_PAUSE_IGNORE;

    reg = HWREG32(eth->base + UMAC_CMD);
    reg &= ~((CMD_SPEED_MASK << CMD_SPEED_SHIFT) |
             CMD_HD_EN | CMD_RX_PAUSE_IGNORE | CMD_TX_PAUSE_IGNORE);
    reg |= cmd_bits;
    reg |= CMD_TX_EN | CMD_RX_EN;
    HWREG32(eth->base + UMAC_CMD) = reg;

    return RT_EOK;
}

#ifdef RT_USING_SYSTEM_WORKQUEUE
static rt_bool_t bcmgenet_phy_poll_link(struct bcmgenet_eth *eth)
{
    int bmsr;

    bmsr = rt_phy_read(eth->phy, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);
    if (bmsr < 0)
    {
        return RT_FALSE;
    }

    bmsr = rt_phy_read(eth->phy, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);
    if (!(bmsr & RT_BMSR_LSTATUS))
    {
        eth->phy->link = 0;
        return RT_FALSE;
    }

    eth->phy->link = 1;
    if (rt_genphy_parse_link(eth->phy))
    {
        eth->phy->link = 0;
        return RT_FALSE;
    }

    return RT_TRUE;
}

static void bcmgenet_phy_link_up(struct bcmgenet_eth *eth)
{
    if (bcmgenet_adjust_link(eth, RT_TRUE))
    {
        LOG_E("Adjust PHY link failed");
        return;
    }

    bcmgenet_set_rx_mode(eth);
    LOG_I("Link up speed=%d duplex=%d", eth->phy->speed, eth->phy->duplex);
    eth_device_linkchange(&eth->parent, RT_TRUE);
}

static void bcmgenet_phy_link_down(struct bcmgenet_eth *eth)
{
    eth->phy->link = 0;

    if (bcmgenet_adjust_link(eth, RT_FALSE))
    {
        LOG_E("Adjust PHY link failed");
        return;
    }

    LOG_W("Link down");
    eth_device_linkchange(&eth->parent, RT_FALSE);
}

static void bcmgenet_phy_retry_work(struct rt_work *work, void *work_data)
{
    struct bcmgenet_eth *eth = work_data;

    RT_UNUSED(work);

    if (eth->phy->link)
    {
        eth->phy_retry_count = 0;
        return;
    }

    if (bcmgenet_phy_poll_link(eth))
    {
        eth->phy_retry_count = 0;
        bcmgenet_phy_link_up(eth);
        return;
    }

    eth->phy_retry_count++;
    if (eth->phy_retry_count < PHY_RETRY_MAX)
    {
        rt_work_submit(&eth->phy_retry_work,
                       rt_tick_from_millisecond(PHY_RETRY_INTERVAL_MS));
    }
    else
    {
        LOG_W("PHY link retry stopped, wait for link IRQ");
        eth->phy_retry_count = 0;
    }
}

static void bcmgenet_link_work(struct rt_work *work, void *work_data)
{
    struct bcmgenet_eth *eth = work_data;
    rt_bool_t link_up;

    RT_UNUSED(work);

    link_up = bcmgenet_phy_poll_link(eth);
    eth->phy_retry_count = 0;

    if (link_up)
    {
        bcmgenet_phy_link_up(eth);
    }
    else
    {
        bcmgenet_phy_link_down(eth);
    }
}
#endif

static struct pbuf *bcmgenet_eth_rx(rt_device_t dev);

static void bcmgenet_enable_intr(struct bcmgenet_eth *eth)
{
    rt_uint32_t intr;

    /* Ring 16 (raspi4 drv_eth): TX/RX done on INTRL2_0 bits 16/13. */
    intr = UMAC_IRQ_LINK_EVENT;
    intr |= UMAC_IRQ_MDIO_DONE | UMAC_IRQ_MDIO_ERROR;
    intr |= UMAC_IRQ_RXDMA_DONE | UMAC_IRQ_TXDMA_DONE;
    HWREG32(eth->base + GENET_INTRL2_0_OFF + INTRL2_CPU_MASK_CLEAR) = intr;

#if DEFAULT_RING <= 15
    intr = UMAC_IRQ1_TX_INTR(DEFAULT_RING) | UMAC_IRQ1_RX_INTR(DEFAULT_RING);
    HWREG32(eth->base + GENET_INTRL2_1_OFF + INTRL2_CPU_MASK_CLEAR) = intr;
#endif
}

static void bcmgenet_disable_intr(struct bcmgenet_eth *eth)
{
    HWREG32(eth->base + GENET_INTRL2_0_OFF + INTRL2_CPU_MASK_SET) = 0xffffffff;
    HWREG32(eth->base + GENET_INTRL2_0_OFF + INTRL2_CPU_CLEAR) = 0xffffffff;
    HWREG32(eth->base + GENET_INTRL2_1_OFF + INTRL2_CPU_MASK_SET) = 0xffffffff;
    HWREG32(eth->base + GENET_INTRL2_1_OFF + INTRL2_CPU_CLEAR) = 0xffffffff;
}

static rt_err_t bcmgenet_start(struct bcmgenet_eth *eth)
{
    rt_err_t err;

    eth->tx_desc_base = eth->base + GENET_TX_OFF;
    eth->rx_desc_base = eth->base + GENET_RX_OFF;

    bcmgenet_umac_reset(eth);

    bcmgenet_gmac_write_hwaddr(eth);

    /* Disable RX/TX DMA and flush TX queues */
    bcmgenet_disable_dma(eth);

    bcmgenet_rx_ring_init(eth);
    bcmgenet_rx_descs_init(eth);

    bcmgenet_tx_ring_init(eth);

    /* Enable RX/TX DMA */
    bcmgenet_enable_dma(eth);

    /* Sync RX ring indices with hardware (raspi4 drv_eth). */
    eth->c_index = HWREG32(eth->base + RDMA_PROD_INDEX) & DMA_P_INDEX_MASK;
    eth->rx_index = eth->c_index % RX_DESCS;
    HWREG32(eth->base + RDMA_CONS_INDEX) = eth->c_index;
    HWREG32(eth->base + RDMA_PROD_INDEX) = eth->c_index;

    if ((err = rt_phy_config(eth->phy)))
    {
        LOG_E("PHY config failed: %s", rt_strerror(err));
        return err;
    }

    if ((err = rt_phy_startup(eth->phy)))
    {
        LOG_E("PHY startup failed: %s", rt_strerror(err));
        return err;
    }

    /* Update MAC registers based on PHY property */
    if ((err = bcmgenet_adjust_link(eth, eth->phy->link)))
    {
        LOG_E("Adjust PHY link failed: %s", rt_strerror(err));
        return err;
    }

    /* Enable Rx/Tx */
    HWREGSET32(eth->base + UMAC_CMD, CMD_TX_EN | CMD_RX_EN);

    bcmgenet_set_rx_mode(eth);
    bcmgenet_enable_intr(eth);

    LOG_I("Started: link=%d speed=%d duplex=%d",
          eth->phy->link, eth->phy->speed, eth->phy->duplex);

    return RT_EOK;
}

static void bcmgenet_stop(struct bcmgenet_eth *eth)
{
    HWREGCLR32(eth->base + UMAC_CMD, CMD_TX_EN | CMD_RX_EN);

    bcmgenet_disable_intr(eth);

    bcmgenet_disable_dma(eth);
}

static void bcmgenet_rx_refill_desc(struct bcmgenet_eth *eth, void *desc, rt_ubase_t packet_dma)
{
    rt_uint32_t len_stat = (RX_BUF_LENGTH << DMA_BUFLENGTH_SHIFT) | DMA_OWN;

    HWREG32(desc + DMA_DESC_ADDRESS_LO) = rt_lower_32_bits(packet_dma);
    HWREG32(desc + DMA_DESC_ADDRESS_HI) = rt_upper_32_bits(packet_dma);
    HWREG32(desc + DMA_DESC_LENGTH_STATUS) = len_stat;
}

static void bcmgenet_tx_wait_done(struct bcmgenet_eth *eth, rt_uint32_t prod_index)
{
    rt_uint32_t cons;
    rt_tick_t start = rt_tick_get();
    rt_tick_t limit = rt_tick_from_millisecond(50);

    while (rt_tick_get() - start < limit)
    {
        cons = HWREG32(eth->base + TDMA_CONS_INDEX) & 0xffff;
        if (cons == prod_index)
        {
            return;
        }
        rt_thread_mdelay(1);
    }

    if (rt_sem_take(&eth->tx_done, rt_tick_from_millisecond(50)) == RT_EOK)
    {
        return;
    }

    LOG_W("TX timeout prod=%u cons=%u", prod_index,
          HWREG32(eth->base + TDMA_CONS_INDEX) & 0xffff);
}

static rt_err_t bcmgenet_eth_tx(rt_device_t dev, struct pbuf *p)
{
    void *desc, *packet;
    rt_ubase_t packet_dma;
    rt_uint32_t len_stat, prod_index, cons_index, n;
    struct bcmgenet_eth *eth = raw_to_bcmgenet_eth(dev);

    prod_index = HWREG32(eth->base + TDMA_PROD_INDEX) & 0xffff;
    cons_index = HWREG32(eth->base + TDMA_CONS_INDEX) & 0xffff;

    for (n = 0; ((prod_index + 1) & 0xffff) == cons_index && n < 50; n++)
    {
        cons_index = HWREG32(eth->base + TDMA_CONS_INDEX) & 0xffff;
        rt_thread_mdelay(1);
    }

    if (((prod_index + 1) & 0xffff) == cons_index)
    {
        LOG_W("TX ring full prod=%u cons=%u", prod_index, cons_index);
        return -RT_EBUSY;
    }

    packet = eth->txbuffer + eth->tx_index * RX_BUF_LENGTH;
    packet_dma = eth->txbuffer_dma + (packet - (void *)eth->txbuffer);

    rt_memset(packet, 0, GENET_TX_TSB_SIZE);
    pbuf_copy_partial(p, packet + GENET_TX_TSB_SIZE, p->tot_len, 0);

    len_stat = (GENET_TX_TSB_SIZE + p->tot_len) << DMA_BUFLENGTH_SHIFT;
    len_stat |= 0x3f << DMA_TX_QTAG_SHIFT;
    len_stat |= DMA_TX_APPEND_CRC | DMA_SOP | DMA_EOP;
    desc = eth->tx_desc_base + eth->tx_index * DMA_DESC_SIZE;

    HWREG32(desc + DMA_DESC_ADDRESS_LO) = rt_lower_32_bits(packet_dma);
    HWREG32(desc + DMA_DESC_ADDRESS_HI) = rt_upper_32_bits(packet_dma);
    HWREG32(desc + DMA_DESC_LENGTH_STATUS) = len_stat;

    if (++eth->tx_index >= TX_DESCS)
    {
        eth->tx_index = 0;
    }

    prod_index = (prod_index + 1) & 0xffff;
    HWREG32(eth->base + TDMA_PROD_INDEX) = prod_index;

    bcmgenet_tx_wait_done(eth, prod_index);
    eth_device_ready(&eth->parent);

    return RT_EOK;
}

static struct pbuf *bcmgenet_eth_rx(rt_device_t dev)
{
    void *desc, *packet;
    rt_uint64_t packet_dma;
    rt_uint32_t prod_index, length, length_status;
    struct pbuf *p = RT_NULL;
    struct bcmgenet_eth *eth = raw_to_bcmgenet_eth(dev);

    prod_index = HWREG32(eth->base + RDMA_PROD_INDEX) & DMA_P_INDEX_MASK;

    HWREG32(eth->base + GENET_INTRL2_0_OFF + INTRL2_CPU_CLEAR) =
            UMAC_IRQ_RXDMA_DONE;
#if DEFAULT_RING <= 15
    HWREG32(eth->base + GENET_INTRL2_1_OFF + INTRL2_CPU_CLEAR) =
            UMAC_IRQ1_RX_INTR(DEFAULT_RING);
#endif

    if (prod_index == eth->c_index)
    {
        return RT_NULL;
    }

    desc = eth->rx_desc_base + eth->rx_index * DMA_DESC_SIZE;

    rt_hw_rmb();
    length_status = HWREG32(desc + DMA_DESC_LENGTH_STATUS);

    length = (length_status >> DMA_BUFLENGTH_SHIFT) & DMA_BUFLENGTH_MASK;

    packet_dma = HWREG32(desc + DMA_DESC_ADDRESS_HI);
    packet_dma <<= 32;
    packet_dma |= HWREG32(desc + DMA_DESC_ADDRESS_LO);
    packet = eth->rxbuffer + (packet_dma - eth->rxbuffer_dma);

    if (length <= RX_BUF_OFFSET)
    {
        goto _repost;
    }

    packet += RX_BUF_OFFSET;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, packet, length);

    if (!(p = pbuf_alloc(PBUF_RAW, length, PBUF_RAM)))
    {
        goto _repost;
    }

    rt_memcpy(p->payload, packet, length);

_repost:
    packet_dma = HWREG32(desc + DMA_DESC_ADDRESS_HI);
    packet_dma <<= 32;
    packet_dma |= HWREG32(desc + DMA_DESC_ADDRESS_LO);

    bcmgenet_rx_refill_desc(eth, desc, packet_dma);

    eth->c_index = (eth->c_index + 1) & 0xffff;
    HWREG32(eth->base + RDMA_CONS_INDEX) = eth->c_index;

    if (++eth->rx_index >= RX_DESCS)
    {
        eth->rx_index = 0;
    }

    return p;
}

static rt_err_t bcmgenet_eth_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct bcmgenet_eth *eth = raw_to_bcmgenet_eth(dev);

    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (args)
        {
            rt_memcpy(args, eth->mac, sizeof(eth->mac));
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    default:
        err = -RT_ENOSYS;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops bcmgenet_eth_ops =
{
    .control = bcmgenet_eth_control,
};
#endif

/* Handle Rx and Tx default queues + other stuff */
static void bcmgenet_eth_isr0(int irq, void *param)
{
    rt_uint32_t status;
    struct bcmgenet_eth *eth = param;

    /* Read irq status */
    status = HWREG32(eth->base + GENET_INTRL2_0_OFF + INTRL2_CPU_STAT) &
            ~HWREG32(eth->base + GENET_INTRL2_0_OFF + INTRL2_CPU_MASK_STATUS);

    /* Clear interrupts */
    HWREG32(eth->base + GENET_INTRL2_0_OFF + INTRL2_CPU_CLEAR) = status;

    if (status & UMAC_IRQ_TXDMA_DONE)
    {
        rt_sem_release(&eth->tx_done);
    }

    if (status & UMAC_IRQ_RXDMA_DONE)
    {
        eth_device_ready(&eth->parent);
    }

    if (status & UMAC_IRQ_RBUF_OVERFLOW)
    {
        LOG_W("RX buffer overflow");
    }

    status &= (UMAC_IRQ_LINK_EVENT | UMAC_IRQ_PHY_DET_R);
    if (status & UMAC_IRQ_LINK_EVENT)
    {
#ifdef RT_USING_SYSTEM_WORKQUEUE
        rt_work_submit(&eth->link_work, 0);
#endif
    }
}

/* Handle Rx and Tx priority queues */
static void bcmgenet_eth_isr1(int irq, void *param)
{
    rt_uint32_t status;
    struct bcmgenet_eth *eth = param;

    /* Read irq status */
    status = HWREG32(eth->base + GENET_INTRL2_1_OFF + INTRL2_CPU_STAT) &
            ~HWREG32(eth->base + GENET_INTRL2_1_OFF + INTRL2_CPU_MASK_STATUS);

    /* Clear interrupts */
    HWREG32(eth->base + GENET_INTRL2_1_OFF + INTRL2_CPU_CLEAR) = status;

#if DEFAULT_RING <= 15
    if (status & UMAC_IRQ1_TX_INTR(DEFAULT_RING))
    {
        rt_sem_release(&eth->tx_done);
    }
#endif

#if DEFAULT_RING <= 15
    if (status & UMAC_IRQ1_RX_INTR(DEFAULT_RING))
    {
        eth_device_ready(&eth->parent);
    }
#endif
}

static rt_err_t bcmgenet_eth_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t value;
    struct mii_bus *bus;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *mdio_np, *phy_np, *fw_np;
    struct bcmgenet_eth *eth = rt_calloc(1, sizeof(*eth));

    if (!eth)
    {
        return -RT_ENOMEM;
    }

    eth->dev = dev;
    eth->dma_buf_size = RX_TOTAL_BUFSIZE + TX_TOTAL_BUFSIZE;

    if (!(eth->base = rt_dm_dev_iomap(dev, 0)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    value = HWREG32(eth->base + SYS_REV_CTRL);
    value = (value >> 24) & 0x0f;

    if (value != 6)
    {
        if (value == 5)
        {
            value = 4;
        }
        else if (value == 0)
        {
            value = 1;
        }

        LOG_E("Unsupported GENETv%d.%d",
                value, (HWREG32(eth->base + SYS_REV_CTRL) >> 16) & 0x0f);

        err = -RT_ENOSYS;
        goto _fail;
    }

    if ((eth->irq0 = rt_dm_dev_get_irq(dev, 0)) < 0)
    {
        err = eth->irq0;
        goto _fail;
    }

    if ((eth->irq1 = rt_dm_dev_get_irq(dev, 1)) < 0)
    {
        err = eth->irq1;
        goto _fail;
    }

    /* For PHY & MDIO */
    mdio_np = rt_ofw_get_child_by_tag(np, "mdio");
    rt_platform_ofw_device_probe_child(mdio_np);
    rt_ofw_node_put(mdio_np);

    if (!(bus = rt_mdio_get_bus_by_name("unimac MII bus")))
    {
        err = -RT_ENOSYS;
        goto _fail;
    }

    if (!(phy_np = rt_ofw_parse_phandle(np, "phy-handle", 0)))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (rt_ofw_prop_read_u32(phy_np, "reg", &value))
    {
        rt_ofw_node_put(phy_np);
        err = -RT_EINVAL;
        goto _fail;
    }

    if (!(eth->phy = rt_phy_find_by_mask(bus, 1 << value)))
    {
        rt_ofw_node_put(phy_np);
        err = -RT_ENOSYS;
        goto _fail;
    }

    eth->phy_np = phy_np;
    eth->phy->node = phy_np;

    rt_ofw_get_interface(np, &eth->interface);
    eth->phy->interface = eth->interface;

    switch (eth->interface)
    {
    case RT_PHY_INTERFACE_MODE_RGMII:
    case RT_PHY_INTERFACE_MODE_RGMII_RXID:
        break;

    default:
        LOG_E("Unknown PHY mode: %d", eth->interface);
        err = -RT_ENOSYS;
        goto _fail;
    }

    bcmgenet_mii_config(eth);

    HWREG32(eth->base + SYS_RBUF_FLUSH_CTRL) = 0;
    rt_hw_us_delay(10);
    /* Disable MAC while updating its registers */
    HWREG32(eth->base + UMAC_CMD) = 0;
    /* Issue soft reset with (rg)mii loopback to ensure a stable rxclk */
    HWREG32(eth->base + UMAC_CMD) = CMD_SW_RESET | CMD_LCL_LOOP_EN;

    /* Connect PHY */
    if (!rt_dm_dev_prop_read_u32(dev, "max-speed", &eth->speed))
    {
        if ((err = rt_phy_set_supported(eth->phy, eth->speed)))
        {
            goto _fail;
        }
    }

    /* PHY config/startup deferred until MAC rings are ready in bcmgenet_start() */

    /* For MAC address */
    if ((fw_np = rpi_firmware_find_node()))
    {
        struct rpi_firmware *rpi_fw = rpi_firmware_get(fw_np);

        err = rpi_firmware_property(rpi_fw, RPI_FIRMWARE_GET_BOARD_MAC_ADDRESS,
                eth->mac, sizeof(eth->mac));

        rt_ofw_node_put(fw_np);
        rpi_firmware_put(rpi_fw);
    }

    if ((!fw_np || err) && (err = rt_ofw_get_mac_addr(np, eth->mac)))
    {
        goto _fail;
    }

    if (!(eth->rxbuffer = rt_dma_alloc_coherent(dev, eth->dma_buf_size, &eth->rxbuffer_dma)))
    {
        err = -RT_ENOMEM;
        goto _fail;
    }
    eth->txbuffer = eth->rxbuffer + RX_TOTAL_BUFSIZE;
    eth->txbuffer_dma = eth->rxbuffer_dma + RX_TOTAL_BUFSIZE;

    rt_sem_init(&eth->tx_done, "genet_tx", 0, RT_IPC_FLAG_FIFO);

    if ((err = bcmgenet_start(eth)))
    {
        goto _fail;
    }

#ifdef RT_USING_DEVICE_OPS
    eth->parent.parent.ops = &bcmgenet_eth_ops;
#else
    eth->parent.parent.control = bcmgenet_eth_control;
#endif
    eth->parent.eth_tx = bcmgenet_eth_tx;
    eth->parent.eth_rx = bcmgenet_eth_rx;

#ifdef RT_USING_SYSTEM_WORKQUEUE
    rt_work_init(&eth->link_work, bcmgenet_link_work, eth);
    rt_work_init(&eth->phy_retry_work, bcmgenet_phy_retry_work, eth);
#endif

    dev->user_data = eth;

    if ((err = rt_dm_dev_set_name_auto(&eth->parent.parent, "e")) < 0)
    {
        goto _stop;
    }

    if ((err = eth_device_init(&eth->parent, rt_dm_dev_get_name(&eth->parent.parent))))
    {
        goto _stop;
    }

    rt_hw_interrupt_install(eth->irq0, bcmgenet_eth_isr0, eth, "bcmgenet0");
    rt_hw_interrupt_umask(eth->irq0);

    rt_hw_interrupt_install(eth->irq1, bcmgenet_eth_isr1, eth, "bcmgenet1");
    rt_hw_interrupt_umask(eth->irq1);

    if (eth->phy->link)
    {
        eth_device_linkchange(&eth->parent, RT_TRUE);
    }
    else
    {
#ifdef RT_USING_SYSTEM_WORKQUEUE
        eth->phy_retry_count = 0;
        rt_work_submit(&eth->phy_retry_work,
                       rt_tick_from_millisecond(PHY_RETRY_INTERVAL_MS));
#endif
    }

    return RT_EOK;

_stop:
    bcmgenet_stop(eth);
    rt_sem_detach(&eth->tx_done);

_fail:
    if (eth && eth->phy_np)
    {
        rt_ofw_node_put(eth->phy_np);
    }

    if (eth && eth->base)
    {
        rt_iounmap(eth->base);
    }

    if (eth->rxbuffer)
    {
        rt_dma_free_coherent(eth->dev, eth->dma_buf_size,
                             eth->rxbuffer, eth->rxbuffer_dma);
    }

    rt_free(eth);

    return err;
}

static rt_err_t bcmgenet_eth_remove(struct rt_platform_device *pdev)
{
    struct bcmgenet_eth *eth = pdev->parent.user_data;

    eth_device_linkchange(&eth->parent, RT_FALSE);
    eth_device_deinit(&eth->parent);

#ifdef RT_USING_SYSTEM_WORKQUEUE
    rt_work_cancel(&eth->link_work);
    rt_work_cancel(&eth->phy_retry_work);
#endif

    rt_sem_detach(&eth->tx_done);
    bcmgenet_stop(eth);

    rt_hw_interrupt_mask(eth->irq0);
    rt_pic_detach_irq(eth->irq0, eth);

    rt_hw_interrupt_mask(eth->irq1);
    rt_pic_detach_irq(eth->irq1, eth);

    if (eth->phy_np)
    {
        rt_ofw_node_put(eth->phy_np);
    }

    rt_dma_free_coherent(eth->dev, eth->dma_buf_size, eth->rxbuffer, eth->rxbuffer_dma);

    rt_free(eth);

    return RT_EOK;
}

static const struct rt_ofw_node_id bcmgenet_eth_ofw_ids[] =
{
    { .compatible = "brcm,genet-v5" },
    { .compatible = "brcm,bcm2711-genet-v5" },
    { /* sentinel */ }
};

static struct rt_platform_driver bcmgenet_eth_driver =
{
    .name = "eth-bcmgenet",
    .ids = bcmgenet_eth_ofw_ids,

    .probe = bcmgenet_eth_probe,
    .remove = bcmgenet_eth_remove,
};
RT_PLATFORM_DRIVER_EXPORT(bcmgenet_eth_driver);
