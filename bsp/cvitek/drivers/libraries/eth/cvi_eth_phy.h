/*
 * Copyright (C) Cvitek Co., Ltd. 2019-2020. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * @file     phy.h
 * @brief    header file for generic PHY Driver
 * @version  V1.0
 * @date     21 March 2019
 ******************************************************************************/
#ifndef _ETH_PHY_H_
#define _ETH_PHY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "mmio.h"
#include "drv_ioremap.h"

/**
\brief Ethernet link speed
*/
#define CSI_ETH_SPEED_10M               (0)     ///< 10 Mbps link speed
#define CSI_ETH_SPEED_100M              (1)     ///< 100 Mbps link speed
#define CSI_ETH_SPEED_1G                (2)     ///< 1 Gpbs link speed

/**
\brief Ethernet duplex mode
*/
#define CSI_ETH_DUPLEX_HALF             (0)     ///< Half duplex link
#define CSI_ETH_DUPLEX_FULL             (1)     ///< Full duplex link

typedef void *eth_phy_handle_t;

typedef enum eth_power_state
{
    CSI_ETH_POWER_OFF,                        ///< Power off: no operation possible
    CSI_ETH_POWER_LOW,                        ///< Low Power mode: retain state, detect and signal wake-up events
    CSI_ETH_POWER_FULL                        ///< Power on: full operation at maximum performance
} eth_power_state_t;

typedef int32_t (*csi_eth_phy_read_t)(uint8_t phy_addr, uint8_t reg_addr, uint16_t *data);   ///< Read Ethernet PHY Register.
typedef int32_t (*csi_eth_phy_write_t)(uint8_t phy_addr, uint8_t reg_addr, uint16_t  data);  ///< Write Ethernet PHY Register.

typedef volatile struct eth_link_info
{
    uint32_t speed              : 2;                ///< Link speed: 0= 10 MBit, 1= 100 MBit, 2= 1 GBit
    uint32_t duplex             : 1;                ///< Duplex mode: 0= Half, 1= Full
    uint32_t autoneg            : 1;                ///< Set the interface to Auto Negotiation mode of transmission parameters
    uint32_t loopback           : 1;                ///< Set the interface into a Loop-back test mode
    uint32_t isolation          : 1;                ///< Set to indicate electrical isolation of PHY interface from MII/RMII interface
    uint32_t reserved           : 26;
} eth_link_info_t;

typedef struct
{
    csi_eth_phy_read_t  phy_read;
    csi_eth_phy_write_t phy_write;
    eth_link_info_t     link_info;
} eth_phy_priv_t;

typedef enum eth_link_state
{
    ETH_LINK_DOWN,                    ///< Link is down
    ETH_LINK_UP                       ///< Link is up
} eth_link_state_t;

/* Basic mode control register */
#define CVI_BMCR_RESV           (0x003f)
#define CVI_BMCR_SPEED1000      (0x0040)
#define CVI_BMCR_CTST           (0x0080)
#define CVI_BMCR_FULLDPLX       (0x0100)
#define CVI_BMCR_ANRESTART      (0x0200)
#define CVI_BMCR_ISOLATE        (0x0400)
#define CVI_BMCR_PDOWN          (0x0800)
#define CVI_BMCR_ANENABLE       (0x1000)
#define CVI_BMCR_SPEED100       (0x2000)
#define CVI_BMCR_LOOPBACK       (0x4000)
#define CVI_BMCR_RESET          (0x8000)
#define BMCR_SPEED10            (0x0000)


/* Generic MII registers */
#define CVI_MII_BMCR            (0x00)
#define CVI_MII_BMSR            (0x01)
#define CVI_MII_PHYSID1         (0x02)
#define CVI_MII_PHYSID2         (0x03)
#define CVI_MII_ADVERTISE       (0x04)
#define CVI_MII_LPA             (0x05)
#define CVI_MII_EXPANSION       (0x06)
#define CVI_MII_CTRL1000        (0x09)
#define CVI_MII_STAT1000        (0x0a)
#define MII_MMD_CTRL            (0x0d)
#define MII_MMD_DATA            (0x0e)
#define CVI_MII_ESTATUS         (0x0f)
#define CVI_MII_DCOUNTER        (0x12)
#define CVI_MII_FCSCOUNTER      (0x13)
#define CVI_MII_NWAYTEST        (0x14)
#define CVI_MII_RERRCOUNTER     (0x15)
#define CVI_MII_SREVISION       (0x16)
#define CVI_MII_RESV1           (0x17)
#define CVI_MII_LBRERROR        (0x18)
#define CVI_MII_PHYADDR         (0x19)
#define CVI_MII_RESV2           (0x1a)
#define CVI_MII_TPISTATUS       (0x1b)
#define CVI_MII_NCONFIG         (0x1c)

/* Advertisement control register. */
#define CVI_ADVERTISE_CSMA          (0x0001)
#define CVI_ADVERTISE_SLCT          (0x001f)
#define CVI_ADVERTISE_10HALF        (0x0020)
#define CVI_ADVERTISE_1000XFULL     (0x0020)
#define CVI_ADVERTISE_10FULL        (0x0040)
#define CVI_ADVERTISE_1000XHALF     (0x0040)
#define CVI_ADVERTISE_100HALF       (0x0080)
#define CVI_ADVERTISE_1000XPAUSE    (0x0080)
#define CVI_ADVERTISE_100FULL       (0x0100)
#define CVI_ADVERTISE_1000XPSE_ASYM (0x0100)
#define CVI_ADVERTISE_100BASE4      (0x0200)
#define CVI_ADVERTISE_PAUSE_CAP     (0x0400)
#define CVI_ADVERTISE_PAUSE_ASYM    (0x0800)
#define CVI_ADVERTISE_RESV          (0x1000)
#define CVI_ADVERTISE_RFAULT        (0x2000)
#define CVI_ADVERTISE_LPACK         (0x4000)
#define CVI_ADVERTISE_NPAGE         (0x8000)

/* Basic mode status register. */
#define CVI_BMSR_ERCAP          (0x0001)
#define CVI_BMSR_JCD            (0x0002)
#define CVI_BMSR_LSTATUS        (0x0004)
#define CVI_BMSR_ANEGCAPABLE    (0x0008)
#define CVI_BMSR_RFAULT         (0x0010)
#define CVI_BMSR_ANEGCOMPLETE   (0x0020)
#define CVI_BMSR_RESV           (0x00c0)
#define CVI_BMSR_ESTATEN        (0x0100)
#define CVI_BMSR_100HALF2       (0x0200)
#define CVI_BMSR_100FULL2       (0x0400)
#define CVI_BMSR_10HALF         (0x0800)
#define CVI_BMSR_10FULL         (0x1000)
#define CVI_BMSR_100HALF        (0x2000)
#define CVI_BMSR_100FULL        (0x4000)
#define CVI_BMSR_100BASE4       (0x8000)

#define CVI_ADVERTISE_FULL  (CVI_ADVERTISE_100FULL | CVI_ADVERTISE_10FULL | \
                         CVI_ADVERTISE_CSMA)
#define CVI_ADVERTISE_ALL   (CVI_ADVERTISE_10HALF | CVI_ADVERTISE_10FULL | \
                         CVI_ADVERTISE_100HALF | CVI_ADVERTISE_100FULL)

/* Link partner ability register. */
#define CVI_LPA_SLCT            (0x001f)  /* Same as advertise selector */
#define CVI_LPA_10HALF          (0x0020)  /* Can do 10mbps half-duplex */
#define CVI_LPA_1000XFULL       (0x0020)  /* Can do 1000BASE-X full-duplex */
#define CVI_LPA_10FULL          (0x0040)  /* Can do 10mbps full-duplex */
#define CVI_LPA_1000XHALF       (0x0040)  /* Can do 1000BASE-X half-duplex */
#define CVI_LPA_100HALF         (0x0080)  /* Can do 100mbps half-duplex */
#define CVI_LPA_1000XPAUSE      (0x0080)  /* Can do 1000BASE-X pause */
#define CVI_LPA_100FULL         (0x0100)  /* Can do 100mbps full-duplex */
#define CVI_LPA_1000XPAUSE_ASYM (0x0100)  /* Can do 1000BASE-X pause asym */
#define CVI_LPA_100BASE4        (0x0200)  /* Can do 100mbps 4k packets */
#define CVI_LPA_PAUSE_CAP       (0x0400)  /* Can pause */
#define CVI_LPA_PAUSE_ASYM      (0x0800)  /* Can pause asymetrically */
#define CVI_LPA_RESV            (0x1000)  /* Unused */
#define CVI_LPA_RFAULT          (0x2000)  /* Link partner faulted */
#define CVI_LPA_LPACK           (0x4000)  /* Link partner acked us */
#define CVI_LPA_NPAGE           (0x8000)  /* Next page bit */

#define CVI_LPA_DUPLEX  (CVI_LPA_10FULL | CVI_LPA_100FULL)
#define CVI_LPA_100     (CVI_LPA_100FULL | CVI_LPA_100HALF | CVI_LPA_100BASE4)

/* Expansion register for auto-negotiation. */
#define CVI_EXPANSION_NWAY          (0x0001)  /* Can do N-way auto-nego */
#define CVI_EXPANSION_LCWP          (0x0002)  /* Got new RX page code word */
#define CVI_EXPANSION_ENABLENPAGE   (0x0004)  /* This enables npage words */
#define CVI_EXPANSION_NPCAPABLE     (0x0008)  /* Link partner supports npage */
#define CVI_EXPANSION_MFAULTS       (0x0010)  /* Multiple faults detected */
#define CVI_EXPANSION_RESV          (0xffe0)  /* Unused */

#define CVI_ESTATUS_1000_XFULL  (0x8000)  /* Can do 1000BX Full */
#define CVI_ESTATUS_1000_XHALF  (0x4000)  /* Can do 1000BX Half */
#define CVI_ESTATUS_1000_TFULL  (0x2000)  /* Can do 1000BT Full */
#define CVI_ESTATUS_1000_THALF  (0x1000)  /* Can do 1000BT Half */

/* N-way test register. */
#define CVI_NWAYTEST_RESV1      (0x00ff)  /* Unused */
#define CVI_NWAYTEST_LOOPBACK   (0x0100)  /* Enable loopback for N-way */
#define CVI_NWAYTEST_RESV2      (0xfe00)  /* Unused */

/* 1000BASE-T Control register */
#define CVI_ADVERTISE_1000FULL      0x0200  /* Advertise 1000BASE-T full duplex */
#define CVI_ADVERTISE_1000HALF      0x0100  /* Advertise 1000BASE-T half duplex */
#define CTL1000_AS_MASTER           0x0800
#define CTL1000_ENABLE_MASTER       0x1000

/* 1000BASE-T Status register */
#define CVI_LPA_1000LOCALRXOK   0x2000  /* Link partner local receiver status */
#define CVI_LPA_1000REMRXOK     0x1000  /* Link partner remote receiver status */
#define CVI_LPA_1000FULL        0x0800  /* Link partner 1000BASE-T full duplex */
#define CVI_LPA_1000HALF        0x0400  /* Link partner 1000BASE-T half duplex */

/* Flow control flags */
#define CVI_FLOW_CTRL_TX        0x01
#define CVI_FLOW_CTRL_RX        0x02

/* MMD Access Control register fields */
#define CVI_MII_MMD_CTRL_DEVAD_MASK 0x1f    /* Mask MMD DEVAD*/
#define CVI_MII_MMD_CTRL_ADDR       0x0000  /* Address */
#define CVI_MII_MMD_CTRL_NOINCR     0x4000  /* no post increment */
#define CVI_MII_MMD_CTRL_INCR_RDWT  0x8000  /* post increment on reads & writes */
#define CVI_MII_MMD_CTRL_INCR_ON_WT 0xC000  /* post increment on writes only */


/* Indicates what features are advertised by the interface. */
#define CVI_ADVERTISED_10baseT_Half         (1 << 0)
#define CVI_ADVERTISED_10baseT_Full         (1 << 1)
#define CVI_ADVERTISED_100baseT_Half        (1 << 2)
#define CVI_ADVERTISED_100baseT_Full        (1 << 3)
#define CVI_ADVERTISED_1000baseT_Half       (1 << 4)
#define CVI_ADVERTISED_1000baseT_Full       (1 << 5)
#define CVI_ADVERTISED_Autoneg              (1 << 6)
#define CVI_ADVERTISED_TP                   (1 << 7)
#define CVI_ADVERTISED_AUI                  (1 << 8)
#define CVI_ADVERTISED_MII                  (1 << 9)
#define CVI_ADVERTISED_FIBRE                (1 << 10)
#define CVI_ADVERTISED_BNC                  (1 << 11)
#define CVI_ADVERTISED_10000baseT_Full      (1 << 12)
#define CVI_ADVERTISED_Pause                (1 << 13)
#define CVI_ADVERTISED_Asym_Pause           (1 << 14)
#define CVI_ADVERTISED_2500baseX_Full       (1 << 15)
#define CVI_ADVERTISED_Backplane            (1 << 16)
#define CVI_ADVERTISED_1000baseKX_Full      (1 << 17)
#define CVI_ADVERTISED_10000baseKX4_Full    (1 << 18)
#define CVI_ADVERTISED_10000baseKR_Full     (1 << 19)
#define CVI_ADVERTISED_10000baseR_FEC       (1 << 20)
#define CVI_ADVERTISED_1000baseX_Half       (1 << 21)
#define CVI_ADVERTISED_1000baseX_Full       (1 << 22)


/* Indicates what features are supported by the interface. */
#define CVI_SUPPORTED_10baseT_Half      (1 << 0)
#define CVI_SUPPORTED_10baseT_Full      (1 << 1)
#define CVI_SUPPORTED_100baseT_Half     (1 << 2)
#define CVI_SUPPORTED_100baseT_Full     (1 << 3)
#define CVI_SUPPORTED_1000baseT_Half    (1 << 4)
#define CVI_SUPPORTED_1000baseT_Full    (1 << 5)
#define CVI_SUPPORTED_Autoneg           (1 << 6)
#define CVI_SUPPORTED_TP                (1 << 7)
#define CVI_SUPPORTED_AUI               (1 << 8)
#define CVI_SUPPORTED_MII               (1 << 9)
#define CVI_SUPPORTED_FIBRE             (1 << 10)
#define CVI_SUPPORTED_BNC               (1 << 11)
#define CVI_SUPPORTED_10000baseT_Full   (1 << 12)
#define CVI_SUPPORTED_Pause             (1 << 13)
#define CVI_SUPPORTED_Asym_Pause        (1 << 14)
#define CVI_SUPPORTED_2500baseX_Full    (1 << 15)
#define CVI_SUPPORTED_Backplane         (1 << 16)
#define CVI_SUPPORTED_1000baseKX_Full   (1 << 17)
#define CVI_SUPPORTED_10000baseKX4_Full (1 << 18)
#define CVI_SUPPORTED_10000baseKR_Full  (1 << 19)
#define CVI_SUPPORTED_10000baseR_FEC    (1 << 20)
#define CVI_SUPPORTED_1000baseX_Half    (1 << 21)
#define CVI_SUPPORTED_1000baseX_Full    (1 << 22)

/* PHY features */
#define CVI_PHY_DEFAULT_FEATURES    (CVI_SUPPORTED_Autoneg | \
                                 CVI_SUPPORTED_TP | \
                                 CVI_SUPPORTED_MII)

#define CVI_PHY_10BT_FEATURES   (CVI_SUPPORTED_10baseT_Half | \
                             CVI_SUPPORTED_10baseT_Full)

#define CVI_PHY_100BT_FEATURES  (CVI_SUPPORTED_100baseT_Half | \
                             CVI_SUPPORTED_100baseT_Full)

#define CVI_PHY_1000BT_FEATURES (CVI_SUPPORTED_1000baseT_Half | \
                             CVI_SUPPORTED_1000baseT_Full)

#define CVI_PHY_BASIC_FEATURES  (CVI_PHY_10BT_FEATURES | \
                             CVI_PHY_100BT_FEATURES | \
                             CVI_PHY_DEFAULT_FEATURES)

#define CVI_PHY_GBIT_FEATURES   (CVI_PHY_BASIC_FEATURES | \
                             CVI_PHY_1000BT_FEATURES)

#define CVI_PHY_ANEG_TIMEOUT    5000    /* in ms */

typedef enum {
    LOOPBACK_XMII2MAC,
    LOOPBACK_PCS2MAC,
    LOOPBACK_PMA2MAC,
    LOOPBACK_RMII2PHY,
} phy_loopback_mode_t;

/* phy interface mode */
typedef enum {
    PHY_IF_MODE_MII,
    PHY_IF_MODE_GMII,
    PHY_IF_MODE_SGMII,
    PHY_IF_MODE_TBI,
    PHY_IF_MODE_RMII,
    PHY_IF_MODE_RGMII,
    PHY_IF_MODE_RGMII_ID,
    PHY_IF_MODE_RGMII_RXID,
    PHY_IF_MODE_RGMII_TXID,
    PHY_IF_MODE_RTBI,

    PHY_IF_MODE_NONE,   /* Last One */
    PHY_IF_MODE_COUNT,
} phy_if_mode_t;

typedef struct {
    eth_phy_priv_t *priv;
    eth_link_state_t link_state;

    uint32_t supported;
    uint32_t advertising;

    /*
     * platform specific
     */
    uint32_t phy_addr;
    phy_if_mode_t interface;

    /*
     * driver specific
     */
    uint32_t phy_id;
    uint32_t mask;
    uint32_t features;
    int8_t name[20];
    /* config() should be called before calling start() */
    int32_t (*config)(eth_phy_handle_t phy_dev);
    int32_t (*start)(eth_phy_handle_t phy_dev);
    int32_t (*stop)(eth_phy_handle_t phy_dev);
    int32_t (*loopback)(eth_phy_handle_t phy_dev);
    int32_t (*update_link)(eth_phy_handle_t phy_dev);
} eth_phy_dev_t;

/* ethernet phy config */
#define ETH_PHY_BASE            (uintptr_t)DRV_IOREMAP((void *)0x03009000, 0x1000)
#define ETH_PHY_INIT_MASK       0xFFFFFFF9
#define ETH_PHY_SHUTDOWN        (1 << 1)
#define ETH_PHY_POWERUP         0xFFFFFFFD
#define ETH_PHY_RESET           0xFFFFFFFB
#define ETH_PHY_RESET_N         (1 << 2)
#define ETH_PHY_LED_LOW_ACTIVE  (1 << 3)

int generic_phy_config_aneg(eth_phy_dev_t *dev);
int generic_phy_restart_aneg(eth_phy_dev_t *dev);
int generic_phy_update_link(eth_phy_dev_t *dev);

int32_t eth_phy_read(eth_phy_priv_t *priv, uint8_t phy_addr, uint8_t reg_addr, uint16_t *data);
int32_t eth_phy_write(eth_phy_priv_t *priv, uint8_t phy_addr, uint8_t reg_addr, uint16_t data);

int32_t eth_phy_reset(eth_phy_handle_t handle);
int32_t eth_phy_config(eth_phy_handle_t handle);
int32_t eth_phy_start(eth_phy_handle_t handle);
int32_t eth_phy_update_link(eth_phy_handle_t handle);

int32_t genphy_config(eth_phy_dev_t *phy_dev);
int32_t genphy_update_link(eth_phy_dev_t *phy_dev);

int32_t cvi_eth_phy_power_control(eth_phy_handle_t handle, eth_power_state_t state);

eth_phy_handle_t cvi_eth_phy_init(csi_eth_phy_read_t  fn_read, csi_eth_phy_write_t fn_write);


#ifdef __cplusplus
}
#endif

#endif /* _ETH_PHY_H_ */
