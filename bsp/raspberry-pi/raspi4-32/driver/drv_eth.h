
/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-10-30     bigmagic       first version
 */

#ifndef __DRV_ETH_H__
#define __DRV_ETH_H__

#define MAC_REG                     (void *)(0xfd580000)

//#define BIT(nr)                     (1UL << (nr))

#define SYS_REV_CTRL                (0x00)
#define SYS_PORT_CTRL               (0x04)
#define PORT_MODE_EXT_GPHY          (3)

#define GENET_SYS_OFF               (0x0000)
#define SYS_RBUF_FLUSH_CTRL         (GENET_SYS_OFF  + 0x08)
#define SYS_TBUF_FLUSH_CTRL         (GENET_SYS_OFF  + 0x0c)

#define GENET_EXT_OFF               (0x0080)
#define EXT_RGMII_OOB_CTRL          (GENET_EXT_OFF + 0x0c)
#define RGMII_LINK                  BIT(4)
#define OOB_DISABLE                 BIT(5)
#define RGMII_MODE_EN               BIT(6)
#define ID_MODE_DIS                 BIT(16)

#define GENET_RBUF_OFF              (0x0300)
#define RBUF_TBUF_SIZE_CTRL         (GENET_RBUF_OFF + 0xb4)
#define RBUF_CTRL                   (GENET_RBUF_OFF + 0x00)
#define RBUF_ALIGN_2B               BIT(1)

#define GENET_UMAC_OFF              (0x0800)
#define UMAC_MIB_CTRL               (GENET_UMAC_OFF + 0x580)
#define UMAC_MAX_FRAME_LEN          (GENET_UMAC_OFF + 0x014)
#define UMAC_MAC0                   (GENET_UMAC_OFF + 0x00c)
#define UMAC_MAC1                   (GENET_UMAC_OFF + 0x010)
#define UMAC_CMD                    (GENET_UMAC_OFF + 0x008)
#define MDIO_CMD                    (GENET_UMAC_OFF + 0x614)
#define UMAC_TX_FLUSH               (GENET_UMAC_OFF + 0x334)
#define MDIO_START_BUSY             BIT(29)
#define MDIO_READ_FAIL              BIT(28)
#define MDIO_RD                     (2 << 26)
#define MDIO_WR                     BIT(26)
#define MDIO_PMD_SHIFT              (21)
#define MDIO_PMD_MASK               (0x1f)
#define MDIO_REG_SHIFT              (16)
#define MDIO_REG_MASK               (0x1f)

#define CMD_TX_EN                   BIT(0)
#define CMD_RX_EN                   BIT(1)
#define UMAC_SPEED_10               (0)
#define UMAC_SPEED_100              (1)
#define UMAC_SPEED_1000             (2)
#define UMAC_SPEED_2500             (3)
#define CMD_SPEED_SHIFT             (2)
#define CMD_SPEED_MASK              (3)
#define CMD_SW_RESET                BIT(13)
#define CMD_LCL_LOOP_EN             BIT(15)
#define CMD_TX_EN                   BIT(0)
#define CMD_RX_EN                   BIT(1)

#define MIB_RESET_RX                BIT(0)
#define MIB_RESET_RUNT              BIT(1)
#define MIB_RESET_TX                BIT(2)

/* total number of Buffer Descriptors, same for Rx/Tx */
#define TOTAL_DESCS                 (256)
#define RX_DESCS                    TOTAL_DESCS
#define TX_DESCS                    TOTAL_DESCS

#define DEFAULT_Q                   (0x10)

#define ETH_DATA_LEN                (1500)
#define ETH_HLEN                    (14)
#define VLAN_HLEN                   (4)
#define ETH_FCS_LEN                 (4)
/* Body(1500) + EH_SIZE(14) + VLANTAG(4) + BRCMTAG(6) + FCS(4) = 1528.
 * 1536 is multiple of 256 bytes
 */
#define ENET_BRCM_TAG_LEN           (6)
#define ENET_PAD                    (8)
#define ENET_MAX_MTU_SIZE        (ETH_DATA_LEN + ETH_HLEN +     \
                     VLAN_HLEN + ENET_BRCM_TAG_LEN + \
                     ETH_FCS_LEN + ENET_PAD)

/* Tx/Rx Dma Descriptor common bits */
#define DMA_EN                       BIT(0)
#define DMA_RING_BUF_EN_SHIFT        (0x01)
#define DMA_RING_BUF_EN_MASK         (0xffff)
#define DMA_BUFLENGTH_MASK           (0x0fff)
#define DMA_BUFLENGTH_SHIFT          (16)
#define DMA_RING_SIZE_SHIFT          (16)
#define DMA_OWN                      (0x8000)
#define DMA_EOP                      (0x4000)
#define DMA_SOP                      (0x2000)
#define DMA_WRAP                     (0x1000)
#define DMA_MAX_BURST_LENGTH         (0x8)
/* Tx specific DMA descriptor bits */
#define DMA_TX_UNDERRUN              (0x0200)
#define DMA_TX_APPEND_CRC            (0x0040)
#define DMA_TX_OW_CRC                (0x0020)
#define DMA_TX_DO_CSUM               (0x0010)
#define DMA_TX_QTAG_SHIFT            (7)

/* DMA rings size */
#define DMA_RING_SIZE                (0x40)
#define DMA_RINGS_SIZE               (DMA_RING_SIZE * (DEFAULT_Q + 1))

/* DMA descriptor */
#define DMA_DESC_LENGTH_STATUS       (0x00)
#define DMA_DESC_ADDRESS_LO          (0x04)
#define DMA_DESC_ADDRESS_HI          (0x08)
#define DMA_DESC_SIZE                (12)

#define GENET_RX_OFF                 (0x2000)
#define GENET_RDMA_REG_OFF                    \
    (GENET_RX_OFF + TOTAL_DESCS * DMA_DESC_SIZE)
#define GENET_TX_OFF                 (0x4000)
#define GENET_TDMA_REG_OFF                    \
    (GENET_TX_OFF + TOTAL_DESCS * DMA_DESC_SIZE)

#define DMA_FC_THRESH_HI             (RX_DESCS >> 4)
#define DMA_FC_THRESH_LO             (5)
#define DMA_FC_THRESH_VALUE        ((DMA_FC_THRESH_LO << 16) |    \
                      DMA_FC_THRESH_HI)

#define DMA_XOFF_THRESHOLD_SHIFT      (16)

#define TDMA_RING_REG_BASE                    \
    (GENET_TDMA_REG_OFF + DEFAULT_Q * DMA_RING_SIZE)
#define TDMA_READ_PTR              (TDMA_RING_REG_BASE + 0x00)
#define TDMA_CONS_INDEX            (TDMA_RING_REG_BASE + 0x08)
#define TDMA_PROD_INDEX            (TDMA_RING_REG_BASE + 0x0c)
#define DMA_RING_BUF_SIZE          (0x10)
#define DMA_START_ADDR             (0x14)
#define DMA_END_ADDR               (0x1c)
#define DMA_MBUF_DONE_THRESH       (0x24)
#define TDMA_FLOW_PERIOD           (TDMA_RING_REG_BASE + 0x28)
#define TDMA_WRITE_PTR             (TDMA_RING_REG_BASE + 0x2c)

#define RDMA_RING_REG_BASE                    \
    (GENET_RDMA_REG_OFF + DEFAULT_Q * DMA_RING_SIZE)
#define RDMA_WRITE_PTR             (RDMA_RING_REG_BASE + 0x00)
#define RDMA_PROD_INDEX            (RDMA_RING_REG_BASE + 0x08)
#define RDMA_CONS_INDEX            (RDMA_RING_REG_BASE + 0x0c)
#define RDMA_XON_XOFF_THRESH       (RDMA_RING_REG_BASE + 0x28)
#define RDMA_READ_PTR              (RDMA_RING_REG_BASE + 0x2c)

#define TDMA_REG_BASE              (GENET_TDMA_REG_OFF + DMA_RINGS_SIZE)
#define RDMA_REG_BASE              (GENET_RDMA_REG_OFF + DMA_RINGS_SIZE)
#define DMA_RING_CFG               (0x00)
#define DMA_CTRL                   (0x04)
#define DMA_SCB_BURST_SIZE         (0x0c)

#define RX_BUF_LENGTH              (2048)
#define RX_TOTAL_BUFSIZE           (RX_BUF_LENGTH * RX_DESCS)
#define RX_BUF_OFFSET              (2)

#define PHY_INTERFACE_MODE_RGMII                (7)
#define PHY_INTERFACE_MODE_RGMII_RXID           (9)

#define  BCM54213PE_MII_CONTROL                 (0x00)
#define  BCM54213PE_MII_STATUS                  (0x01)
#define  BCM54213PE_PHY_IDENTIFIER_HIGH         (0x02)
#define  BCM54213PE_PHY_IDENTIFIER_LOW          (0x03)

#define  BCM54213PE_AUTO_NEGOTIATION_ADV        (0x04)
#define  BCM54213PE_AUTO_NEGOTIATION_LINK       (0x05)
#define  BCM54213PE_AUTO_NEGOTIATION_EXPANSION  (0x06)

#define  BCM54213PE_NEXT_PAGE_TX                (0x07)

#define  BCM54213PE_PARTNER_RX                  (0x08)

#define  BCM54213PE_CONTROL                     (0x09)
#define  BCM54213PE_STATUS                      (0x0A)

#define  BCM54213PE_IEEE_EXTENDED_STATUS        (0x0F)
#define  BCM54213PE_PHY_EXTENDED_CONTROL        (0x10)
#define  BCM54213PE_PHY_EXTENDED_STATUS         (0x11)

#define  BCM54213PE_RECEIVE_ERROR_COUNTER       (0x12)
#define  BCM54213PE_FALSE_C_S_COUNTER           (0x13)
#define  BCM54213PE_RECEIVE_NOT_OK_COUNTER      (0x14)

#define BCM54213PE_VERSION_B1                   (0x600d84a2)
#define BCM54213PE_VERSION_X                    (0x600d84a0)

//BCM54213PE_MII_CONTROL
#define MII_CONTROL_PHY_RESET                   (1 << 15)
#define MII_CONTROL_AUTO_NEGOTIATION_ENABLED    (1 << 12)
#define MII_CONTROL_AUTO_NEGOTIATION_RESTART    (1 << 9)
#define MII_CONTROL_PHY_FULL_DUPLEX             (1 << 8)
#define MII_CONTROL_SPEED_SELECTION             (1 << 6)

//BCM54213PE_MII_STATUS
#define MII_STATUS_LINK_UP                      (1 << 2)

//BCM54213PE_CONTROL
#define CONTROL_FULL_DUPLEX_CAPABILITY          (1 << 9)
#define CONTROL_HALF_DUPLEX_CAPABILITY          (1 << 8)

#define SPEED_1000  (1000)
#define SPEED_100   (100)
#define SPEED_10    (10)

#endif/* __DRV_ETH_H__ */
