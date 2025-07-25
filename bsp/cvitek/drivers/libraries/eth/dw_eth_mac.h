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
#ifndef _DW_GMAC_182x_H_
#define _DW_GMAC_182x_H_

#include "cvi_eth_phy.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __aligned
#define __aligned(x) __attribute__((aligned(x)))
#endif

typedef void *eth_mac_handle_t;

#define CSI_ETH_MAC_CONFIGURE           (0x01)      ///< Configure MAC; arg = configuration
#define CSI_ETH_MAC_CONTROL_TX          (0x02)      ///< Transmitter; arg: 0=disabled (default), 1=enabled
#define CSI_ETH_MAC_CONTROL_RX          (0x03)      ///< Receiver; arg: 0=disabled (default), 1=enabled
#define CSI_ETH_MAC_FLUSH               (0x04)      ///< Flush buffer; arg = CSI_ETH_MAC_FLUSH_...
#define CSI_ETH_MAC_SLEEP               (0x05)      ///< Sleep mode; arg: 1=enter and wait for Magic packet, 0=exit
#define CSI_ETH_MAC_VLAN_FILTER         (0x06)      ///< VLAN Filter for received frames; arg15..0: VLAN Tag; arg16: optional CSI_ETH_MAC_VLAN_FILTER_ID_ONLY; 0=disabled (default)
#define DRV_ETH_MAC_ADJUST_LINK         (0x07)      ///< Adjust MAC link state according to phy state; arg: phy handle
#define DRV_ETH_MAC_CONTROL_IRQ         (0x08)      ///< Interrupt request; arg: 0=disable, 1=enable

#define DW_GMAC_DMA_ALIGN               128

#ifndef _DW_ETH_H
#define _DW_ETH_H

#define CVI_CONFIG_SYS_HZ               1000
#define CVI_CONFIG_TX_DESCR_NUM         16
#define CVI_CONFIG_RX_DESCR_NUM         16
#define CVI_CONFIG_ETH_BUFSIZE          2048
#define CVI_TX_TOTAL_BUFSIZE            (CVI_CONFIG_ETH_BUFSIZE * CVI_CONFIG_TX_DESCR_NUM)
#define CVI_RX_TOTAL_BUFSIZE            (CVI_CONFIG_ETH_BUFSIZE * CVI_CONFIG_RX_DESCR_NUM)

#define CVI_CONFIG_MACRESET_TIMEOUT (3 * CVI_CONFIG_SYS_HZ)
#define CVI_CONFIG_MDIO_TIMEOUT     (3 * CVI_CONFIG_SYS_HZ)

struct dw_gmac_mac_regs {
    volatile uint32_t conf;     /* 0x00 */
    volatile uint32_t framefilt;        /* 0x04 */
    volatile uint32_t hashtablehigh;    /* 0x08 */
    volatile uint32_t hashtablelow; /* 0x0c */
    volatile uint32_t miiaddr;      /* 0x10 */
    volatile uint32_t miidata;      /* 0x14 */
    volatile uint32_t flowcontrol;  /* 0x18 */
    volatile uint32_t vlantag;      /* 0x1c */
    volatile uint32_t version;      /* 0x20 */
    volatile uint32_t reserved_1[5];
    volatile uint32_t intreg;       /* 0x38 */
    volatile uint32_t intmask;      /* 0x3c */
    volatile uint32_t macaddr0hi;       /* 0x40 */
    volatile uint32_t macaddr0lo;       /* 0x44 */
};

/* MAC configuration register definitions */
#define CVI_FRAMEBURSTENABLE    (1 << 21)
#define CVI_MII_PORTSELECT      (1 << 15)
#define CVI_FES_100         (1 << 14)
#define CVI_DISABLERXOWN        (1 << 13)
#define CVI_FULLDPLXMODE        (1 << 11)
#define CVI_RXENABLE        (1 << 2)
#define CVI_TXENABLE        (1 << 3)

/* MII address register definitions */
#define CVI_MII_BUSY        (1 << 0)
#define CVI_MII_WRITE       (1 << 1)
#define CVI_MII_CLKRANGE_60_100M    (0)
#define CVI_MII_CLKRANGE_100_150M   (0x4)
#define CVI_MII_CLKRANGE_20_35M (0x8)
#define CVI_MII_CLKRANGE_35_60M (0xC)
#define CVI_MII_CLKRANGE_150_250M   (0x10)
#define CVI_MII_CLKRANGE_250_300M   (0x14)

#define CVI_MIIADDRSHIFT        (11)
#define CVI_MIIREGSHIFT     (6)
#define CVI_MII_REGMSK      (0x1F << 6)
#define CVI_MII_ADDRMSK     (0x1F << 11)

typedef uint32_t  reg_type;
struct dw_gmac_dma_regs
{
    volatile reg_type busmode;      /* 0x00 */
    volatile reg_type txpolldemand; /* 0x04 */
    volatile reg_type rxpolldemand; /* 0x08 */
    volatile reg_type rxdesclistaddr;   /* 0x0c */
    volatile reg_type txdesclistaddr;   /* 0x10 */
    volatile reg_type status;       /* 0x14 */
    volatile reg_type opmode;       /* 0x18 */
    volatile reg_type intenable;        /* 0x1c */
    volatile reg_type discardedcount;       /* 0x20 */
    volatile reg_type wdtforri;     /* 0x24 */
    //volatile reg_type reserved1[2];
    volatile reg_type axibus;       /* 0x28 */
    volatile reg_type reserved2[7];
    volatile reg_type currhosttxdesc;   /* 0x48 */
    volatile reg_type currhostrxdesc;   /* 0x4c */
    volatile reg_type currhosttxbuffaddr;   /* 0x50 */
    volatile reg_type currhostrxbuffaddr;   /* 0x54 */
};

/* Operation mode definitions */
#define CVI_RXSTART             (1 << 1)
#define CVI_TXSECONDFRAME       (1 << 2)
#define CVI_TXSTART             (1 << 13)
#define CVI_FLUSHTXFIFO         (1 << 20)
#define CVI_STOREFORWARD        (1 << 21)
#define CVI_DW_DMA_BASE_OFFSET  (0x1000)

/* Default DMA Burst length */
#ifndef CONFIG_DW_GMAC_DEFAULT_DMA_PBL
#define CONFIG_DW_GMAC_DEFAULT_DMA_PBL 8
#endif
/* Status definitions */
#define CVI_DMA_STATUS_ERI  0x00004000  /* Early Receive Interrupt */
#define CVI_DMA_STATUS_RI   0x00000040  /* Receive Interrupt */
#define CVI_DMA_STATUS_TI   0x00000001  /* Transmit Interrupt */

/* Bus mode register definitions */

#define CVI_DMAMAC_SRST     (1 << 0)
#define CVI_RXHIGHPRIO      (1 << 1)
#define CVI_FIXEDBURST      (1 << 16)
#define CVI_PRIORXTX_11     (0 << 14)
#define CVI_PRIORXTX_21     (1 << 14)
#define CVI_PRIORXTX_31     (2 << 14)
#define CVI_PRIORXTX_41     (3 << 14)
#define CVI_DMA_PBL         (CONFIG_DW_GMAC_DEFAULT_DMA_PBL<<8)

/* Poll demand definitions */
#define CVI_POLL_DATA       (0xFFFFFFFF)


/* Descriptior related definitions */
#define CVI_MAC_MAX_FRAME_SZ    (1600)

struct dmamacdescr
{
    unsigned int txrx_status;
    unsigned int dmamac_cntl;
    unsigned int dmamac_addr;
    unsigned int dmamac_next;
} __attribute__((aligned(DW_GMAC_DMA_ALIGN)));

/*
 * txrx_status definitions
 */

/* tx status bits definitions */
#if defined(CONFIG_DW_ALTDESCRIPTOR)

#define CVI_DESC_TXSTS_OWNBYDMA         (1 << 31)
#define CVI_DESC_TXSTS_TXINT            (1 << 30)
#define CVI_DESC_TXSTS_TXLAST           (1 << 29)
#define CVI_DESC_TXSTS_TXFIRST          (1 << 28)
#define CVI_DESC_TXSTS_TXCRCDIS         (1 << 27)

#define CVI_DESC_TXSTS_TXPADDIS         (1 << 26)
#define CVI_DESC_TXSTS_TXCHECKINSCTRL   (3 << 22)
#define CVI_DESC_TXSTS_TXRINGEND        (1 << 21)
#define CVI_DESC_TXSTS_TXCHAIN          (1 << 20)
#define CVI_DESC_TXSTS_MSK              (0x1FFFF << 0)

#else

#define CVI_DESC_TXSTS_OWNBYDMA         (1 << 31)
#define CVI_DESC_TXSTS_MSK              (0x1FFFF << 0)

#endif

/* rx status bits definitions */
#define CVI_DESC_RXSTS_OWNBYDMA         (1 << 31)
#define CVI_DESC_RXSTS_DAFILTERFAIL     (1 << 30)
#define CVI_DESC_RXSTS_FRMLENMSK        (0x3FFF << 16)
#define CVI_DESC_RXSTS_FRMLENSHFT       (16)

#define CVI_DESC_RXSTS_ERROR            (1 << 15)
#define CVI_DESC_RXSTS_RXTRUNCATED      (1 << 14)
#define CVI_DESC_RXSTS_SAFILTERFAIL     (1 << 13)
#define CVI_DESC_RXSTS_RXIPC_GIANTFRAME (1 << 12)
#define CVI_DESC_RXSTS_RXDAMAGED        (1 << 11)
#define CVI_DESC_RXSTS_RXVLANTAG        (1 << 10)
#define CVI_DESC_RXSTS_RXFIRST          (1 << 9)
#define CVI_DESC_RXSTS_RXLAST           (1 << 8)
#define CVI_DESC_RXSTS_RXIPC_GIANT      (1 << 7)
#define CVI_DESC_RXSTS_RXCOLLISION      (1 << 6)
#define CVI_DESC_RXSTS_RXFRAMEETHER     (1 << 5)
#define CVI_DESC_RXSTS_RXWATCHDOG       (1 << 4)
#define CVI_DESC_RXSTS_RXMIIERROR       (1 << 3)
#define CVI_DESC_RXSTS_RXDRIBBLING      (1 << 2)
#define CVI_DESC_RXSTS_RXCRC            (1 << 1)

/*
 * dmamac_cntl definitions
 */

/* tx control bits definitions */
#if defined(CONFIG_DW_ALTDESCRIPTOR)

#define CVI_DESC_TXCTRL_SIZE1MASK       (0x1FFF << 0)
#define CVI_DESC_TXCTRL_SIZE1SHFT       (0)
#define CVI_DESC_TXCTRL_SIZE2MASK       (0x1FFF << 16)
#define CVI_DESC_TXCTRL_SIZE2SHFT       (16)

#else

#define CVI_DESC_TXCTRL_TXINT           (1 << 31)
#define CVI_DESC_TXCTRL_TXLAST          (1 << 30)
#define CVI_DESC_TXCTRL_TXFIRST         (1 << 29)
#define CVI_DESC_TXCTRL_TXCHECKINSCTRL  (3 << 27)
#define CVI_DESC_TXCTRL_TXCRCDIS        (1 << 26)
#define CVI_DESC_TXCTRL_TXRINGEND       (1 << 25)
#define CVI_DESC_TXCTRL_TXCHAIN         (1 << 24)

#define CVI_DESC_TXCTRL_SIZE1MASK       (0x7FF << 0)
#define CVI_DESC_TXCTRL_SIZE1SHFT       (0)
#define CVI_DESC_TXCTRL_SIZE2MASK       (0x7FF << 11)
#define CVI_DESC_TXCTRL_SIZE2SHFT       (11)

#endif

/* rx control bits definitions */
#if defined(CONFIG_DW_ALTDESCRIPTOR)

#define CVI_DESC_RXCTRL_RXINTDIS        (1 << 31)
#define CVI_DESC_RXCTRL_RXRINGEND       (1 << 15)
#define CVI_DESC_RXCTRL_RXCHAIN         (1 << 14)

#define CVI_DESC_RXCTRL_SIZE1MASK       (0x1FFF << 0)
#define CVI_DESC_RXCTRL_SIZE1SHFT       (0)
#define CVI_DESC_RXCTRL_SIZE2MASK       (0x1FFF << 16)
#define CVI_DESC_RXCTRL_SIZE2SHFT       (16)

#else

#define CVI_DESC_RXCTRL_RXINTDIS        (1 << 31)
#define CVI_DESC_RXCTRL_RXRINGEND       (1 << 25)
#define CVI_DESC_RXCTRL_RXCHAIN         (1 << 24)

#define CVI_DESC_RXCTRL_SIZE1MASK       (0x7FF << 0)
#define CVI_DESC_RXCTRL_SIZE1SHFT       (0)
#define CVI_DESC_RXCTRL_SIZE2MASK       (0x7FF << 11)
#define CVI_DESC_RXCTRL_SIZE2SHFT       (11)

#endif

struct dw_gmac_priv
{
    struct dmamacdescr tx_mac_descrtable[CVI_CONFIG_TX_DESCR_NUM] __aligned(DW_GMAC_DMA_ALIGN);
    struct dmamacdescr rx_mac_descrtable[CVI_CONFIG_RX_DESCR_NUM] __aligned(DW_GMAC_DMA_ALIGN);
    char txbuffs[CVI_TX_TOTAL_BUFSIZE] __aligned(DW_GMAC_DMA_ALIGN);
    char rxbuffs[CVI_RX_TOTAL_BUFSIZE] __aligned(DW_GMAC_DMA_ALIGN);

    uint32_t interface;
    uint32_t max_speed;
    uint32_t tx_currdescnum;
    uint32_t rx_currdescnum;

    struct dw_gmac_mac_regs *mac_regs_p;
    struct dw_gmac_dma_regs *dma_regs_p;
};

#ifdef CONFIG_DM_ETH
int designware_eth_ofdata_to_platdata(struct udevice *dev);
int designware_eth_probe(struct udevice *dev);
extern const struct eth_ops designware_eth_ops;

struct dw_eth_pdata
{
    struct eth_pdata eth_pdata;
    u32 reset_delays[3];
};

int designware_eth_init(struct dw_eth_dev *priv, u8 *enetaddr);
int designware_eth_enable(struct dw_eth_dev *priv);
int designware_eth_send(struct udevice *dev, void *packet, int length);
int designware_eth_recv(struct udevice *dev, int flags, uchar **packetp);
int designware_eth_free_pkt(struct udevice *dev, uchar *packet,
                   int length);
void designware_eth_stop(struct udevice *dev);
int designware_eth_write_hwaddr(struct udevice *dev);
#endif

#endif

typedef struct
{
    eth_phy_dev_t       *phy_dev;
    rt_ubase_t          base;
    uint8_t             irq;
    uint8_t             mac_addr[6];
    struct dw_gmac_priv *priv_unalign;
    struct dw_gmac_priv *priv;
} gmac_dev_t;

/**
\brief Ethernet MAC Address
*/
typedef struct eth_mac_addr
{
  uint8_t b[6];                         ///< MAC Address (6 bytes), MSB first
} eth_mac_addr_t;

static inline void *memalign(uint32_t align, uint32_t size, void **mem_unalign)
{
    void *mem;
    uint32_t offset;

    *mem_unalign = (void *)rt_malloc(size + align);

    if (!*mem_unalign) {
        return NULL;
    }

    offset = *(uint32_t *)mem_unalign % align;

    if (offset == 0) {
        mem = (struct eqos_priv *)*mem_unalign;
    } else {
        mem = (struct eqos_priv *)(*mem_unalign + (align - offset));
    }
    return mem;
}
/**
  \brief       Write Ethernet PHY Register through Management Interface.
  \param[in]   handle  ethernet handle
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[in]   data      16-bit data to write
  \return      error code
*/
int32_t dw_eth_mac_phy_write(eth_mac_handle_t handle, uint8_t phy_addr, uint8_t reg_addr, uint16_t data);

/**
  \brief       Control Ethernet Interface.
  \param[in]   handle  ethernet handle
  \param[in]   control  Operation
  \param[in]   arg      Argument of operation (optional)
  \return      error code
*/
int32_t cvi_eth_mac_control(eth_mac_handle_t handle, uint32_t control, uint32_t arg);
/**
  \brief       Get Ethernet MAC Address.
  \param[in]   handle  ethernet handle
  \param[in]   mac  Pointer to address
  \return      error code
*/
int32_t cvi_eth_mac_get_macaddr(eth_mac_handle_t handle, eth_mac_addr_t *mac);

/**
  \brief       Set Ethernet MAC Address.
  \param[in]   handle  ethernet handle
  \param[in]   mac  Pointer to address
  \return      error code
*/
int32_t cvi_eth_mac_set_macaddr(eth_mac_handle_t handle, const eth_mac_addr_t *mac);

/**
  \brief       Connect phy device to mac device.
  \param[in]   handle_mac  mac handle
  \param[in]   handle_phy  phy handle
*/
void dw_eth_mac_connect_phy(eth_mac_handle_t handle_mac, eth_phy_handle_t handle_phy);

/**
  \brief       Read Ethernet PHY Register through Management Interface.
  \param[in]   handle  ethernet handle
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[out]  data      Pointer where the result is written to
  \return      error code
*/
int32_t dw_eth_mac_phy_read(eth_mac_handle_t handle, uint8_t phy_addr, uint8_t reg_addr, uint16_t *data);

/**
  \brief       Send Ethernet frame.
  \param[in]   handle  ethernet handle
  \param[in]   frame  Pointer to frame buffer with data to send
  \param[in]   len    Frame buffer length in bytes
  \return      error code
*/
int32_t cvi_eth_mac_send_frame(eth_mac_handle_t handle, const uint8_t *frame, uint32_t len);

/**
  \brief       Read data of received Ethernet frame.
  \param[in]   handle  ethernet handle
  \param[in]   frame  Pointer to frame buffer for data to read into
  \param[in]   len    Frame buffer length in bytes
  \return      number of data bytes read or execution status
                 - value >= 0: number of data bytes read
                 - value < 0: error occurred, value is execution status as defined with execution_status
*/
int32_t cvi_eth_mac_read_frame(eth_mac_handle_t handle, uint8_t *frame, uint32_t len);

/**
  \brief       This function is used to initialize Ethernet device and register an event callback.
  \param[in]   idx device id
  \param[in]   cb  callback to handle ethernet event
  \return      return ethernet handle if success
 */
eth_mac_handle_t cvi_eth_mac_init(rt_ubase_t base);

#ifdef __cplusplus
}
#endif

#endif /* _DW_GMAC_182x_H_ */
