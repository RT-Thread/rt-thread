/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2013-01-30     weety     first version
 */

#ifndef _DAVINCI_EMAC_H
#define _DAVINCI_EMAC_H
#include <mii.h>

#ifndef NET_IP_ALIGN
#define NET_IP_ALIGN 2
#endif

enum {
    EMAC_VERSION_1, /* DM644x */
    EMAC_VERSION_2, /* DM646x */
};


#define __iomem

#define BIT(nr)         (1UL << (nr))


/* Configuration items */
#define EMAC_DEF_PASS_CRC       (0) /* Do not pass CRC upto frames */
#define EMAC_DEF_QOS_EN         (0) /* EMAC proprietary QoS disabled */
#define EMAC_DEF_NO_BUFF_CHAIN      (0) /* No buffer chain */
#define EMAC_DEF_MACCTRL_FRAME_EN   (0) /* Discard Maccontrol frames */
#define EMAC_DEF_SHORT_FRAME_EN     (0) /* Discard short frames */
#define EMAC_DEF_ERROR_FRAME_EN     (0) /* Discard error frames */
#define EMAC_DEF_PROM_EN        (0) /* Promiscous disabled */
#define EMAC_DEF_PROM_CH        (0) /* Promiscous channel is 0 */
#define EMAC_DEF_BCAST_EN       (1) /* Broadcast enabled */
#define EMAC_DEF_BCAST_CH       (0) /* Broadcast channel is 0 */
#define EMAC_DEF_MCAST_EN       (1) /* Multicast enabled */
#define EMAC_DEF_MCAST_CH       (0) /* Multicast channel is 0 */

#define EMAC_DEF_TXPRIO_FIXED       (1) /* TX Priority is fixed */
#define EMAC_DEF_TXPACING_EN        (0) /* TX pacing NOT supported*/

#define EMAC_DEF_BUFFER_OFFSET      (0) /* Buffer offset to DMA (future) */
#define EMAC_DEF_MIN_ETHPKTSIZE     (60) /* Minimum ethernet pkt size */
#define EMAC_DEF_MAX_FRAME_SIZE     (1500 + 14 + 4 + 4)
#define EMAC_DEF_TX_CH          (0) /* Default 0th channel */
#define EMAC_DEF_RX_CH          (0) /* Default 0th channel */
#define EMAC_DEF_MDIO_TICK_MS       (10) /* typically 1 tick=1 ms) */
#define EMAC_DEF_MAX_TX_CH      (1) /* Max TX channels configured */
#define EMAC_DEF_MAX_RX_CH      (1) /* Max RX channels configured */
#define EMAC_POLL_WEIGHT        (64) /* Default NAPI poll weight */

/* Buffer descriptor parameters */
#define EMAC_DEF_TX_MAX_SERVICE     (32) /* TX max service BD's */
#define EMAC_DEF_RX_MAX_SERVICE     (64) /* should = netdev->weight */

/* EMAC register related defines */
#define EMAC_ALL_MULTI_REG_VALUE    (0xFFFFFFFF)
#define EMAC_NUM_MULTICAST_BITS     (64)
#define EMAC_TEARDOWN_VALUE     (0xFFFFFFFC)
#define EMAC_TX_CONTROL_TX_ENABLE_VAL   (0x1)
#define EMAC_RX_CONTROL_RX_ENABLE_VAL   (0x1)
#define EMAC_MAC_HOST_ERR_INTMASK_VAL   (0x2)
#define EMAC_RX_UNICAST_CLEAR_ALL   (0xFF)
#define EMAC_INT_MASK_CLEAR     (0xFF)

/* RX MBP register bit positions */
#define EMAC_RXMBP_PASSCRC_MASK     BIT(30)
#define EMAC_RXMBP_QOSEN_MASK       BIT(29)
#define EMAC_RXMBP_NOCHAIN_MASK     BIT(28)
#define EMAC_RXMBP_CMFEN_MASK       BIT(24)
#define EMAC_RXMBP_CSFEN_MASK       BIT(23)
#define EMAC_RXMBP_CEFEN_MASK       BIT(22)
#define EMAC_RXMBP_CAFEN_MASK       BIT(21)
#define EMAC_RXMBP_PROMCH_SHIFT     (16)
#define EMAC_RXMBP_PROMCH_MASK      (0x7 << 16)
#define EMAC_RXMBP_BROADEN_MASK     BIT(13)
#define EMAC_RXMBP_BROADCH_SHIFT    (8)
#define EMAC_RXMBP_BROADCH_MASK     (0x7 << 8)
#define EMAC_RXMBP_MULTIEN_MASK     BIT(5)
#define EMAC_RXMBP_MULTICH_SHIFT    (0)
#define EMAC_RXMBP_MULTICH_MASK     (0x7)
#define EMAC_RXMBP_CHMASK       (0x7)

/* EMAC register definitions/bit maps used */
# define EMAC_MBP_RXPROMISC     (0x00200000)
# define EMAC_MBP_PROMISCCH(ch)     (((ch) & 0x7) << 16)
# define EMAC_MBP_RXBCAST       (0x00002000)
# define EMAC_MBP_BCASTCHAN(ch)     (((ch) & 0x7) << 8)
# define EMAC_MBP_RXMCAST       (0x00000020)
# define EMAC_MBP_MCASTCHAN(ch)     ((ch) & 0x7)

/* EMAC mac_control register */
#define EMAC_MACCONTROL_TXPTYPE     BIT(9)
#define EMAC_MACCONTROL_TXPACEEN    BIT(6)
#define EMAC_MACCONTROL_GMIIEN      BIT(5)
#define EMAC_MACCONTROL_GIGABITEN   BIT(7)
#define EMAC_MACCONTROL_FULLDUPLEXEN    BIT(0)
#define EMAC_MACCONTROL_RMIISPEED_MASK  BIT(15)

/* GIGABIT MODE related bits */
#define EMAC_DM646X_MACCONTORL_GIG  BIT(7)
#define EMAC_DM646X_MACCONTORL_GIGFORCE BIT(17)

/* EMAC mac_status register */
#define EMAC_MACSTATUS_TXERRCODE_MASK   (0xF00000)
#define EMAC_MACSTATUS_TXERRCODE_SHIFT  (20)
#define EMAC_MACSTATUS_TXERRCH_MASK (0x7)
#define EMAC_MACSTATUS_TXERRCH_SHIFT    (16)
#define EMAC_MACSTATUS_RXERRCODE_MASK   (0xF000)
#define EMAC_MACSTATUS_RXERRCODE_SHIFT  (12)
#define EMAC_MACSTATUS_RXERRCH_MASK (0x7)
#define EMAC_MACSTATUS_RXERRCH_SHIFT    (8)

/* EMAC RX register masks */
#define EMAC_RX_MAX_LEN_MASK        (0xFFFF)
#define EMAC_RX_BUFFER_OFFSET_MASK  (0xFFFF)

/* MAC_IN_VECTOR (0x180) register bit fields */
#define EMAC_DM644X_MAC_IN_VECTOR_HOST_INT  BIT(17)
#define EMAC_DM644X_MAC_IN_VECTOR_STATPEND_INT  BIT(16)
#define EMAC_DM644X_MAC_IN_VECTOR_RX_INT_VEC    BIT(8)
#define EMAC_DM644X_MAC_IN_VECTOR_TX_INT_VEC    BIT(0)

/** NOTE:: For DM646x the IN_VECTOR has changed */
#define EMAC_DM646X_MAC_IN_VECTOR_RX_INT_VEC    BIT(EMAC_DEF_RX_CH)
#define EMAC_DM646X_MAC_IN_VECTOR_TX_INT_VEC    BIT(16 + EMAC_DEF_TX_CH)
#define EMAC_DM646X_MAC_IN_VECTOR_HOST_INT  BIT(26)
#define EMAC_DM646X_MAC_IN_VECTOR_STATPEND_INT  BIT(27)

/* CPPI bit positions */
#define EMAC_CPPI_SOP_BIT       BIT(31)
#define EMAC_CPPI_EOP_BIT       BIT(30)
#define EMAC_CPPI_OWNERSHIP_BIT     BIT(29)
#define EMAC_CPPI_EOQ_BIT       BIT(28)
#define EMAC_CPPI_TEARDOWN_COMPLETE_BIT BIT(27)
#define EMAC_CPPI_PASS_CRC_BIT      BIT(26)
#define EMAC_RX_BD_BUF_SIZE     (0xFFFF)
#define EMAC_BD_LENGTH_FOR_CACHE    (16) /* only CPPI bytes */
#define EMAC_RX_BD_PKT_LENGTH_MASK  (0xFFFF)

/* Max hardware defines */
#define EMAC_MAX_TXRX_CHANNELS       (8)  /* Max hardware channels */
#define EMAC_DEF_MAX_MULTICAST_ADDRESSES (64) /* Max mcast addr's */

/* EMAC Peripheral Device Register Memory Layout structure */
#define EMAC_TXIDVER        0x0
#define EMAC_TXCONTROL      0x4
#define EMAC_TXTEARDOWN     0x8
#define EMAC_RXIDVER        0x10
#define EMAC_RXCONTROL      0x14
#define EMAC_RXTEARDOWN     0x18
#define EMAC_TXINTSTATRAW   0x80
#define EMAC_TXINTSTATMASKED    0x84
#define EMAC_TXINTMASKSET   0x88
#define EMAC_TXINTMASKCLEAR 0x8C
#define EMAC_MACINVECTOR    0x90

#define EMAC_DM646X_MACEOIVECTOR    0x94

#define EMAC_RXINTSTATRAW   0xA0
#define EMAC_RXINTSTATMASKED    0xA4
#define EMAC_RXINTMASKSET   0xA8
#define EMAC_RXINTMASKCLEAR 0xAC
#define EMAC_MACINTSTATRAW  0xB0
#define EMAC_MACINTSTATMASKED   0xB4
#define EMAC_MACINTMASKSET  0xB8
#define EMAC_MACINTMASKCLEAR    0xBC

#define EMAC_RXMBPENABLE    0x100
#define EMAC_RXUNICASTSET   0x104
#define EMAC_RXUNICASTCLEAR 0x108
#define EMAC_RXMAXLEN       0x10C
#define EMAC_RXBUFFEROFFSET 0x110
#define EMAC_RXFILTERLOWTHRESH  0x114

#define EMAC_MACCONTROL     0x160
#define EMAC_MACSTATUS      0x164
#define EMAC_EMCONTROL      0x168
#define EMAC_FIFOCONTROL    0x16C
#define EMAC_MACCONFIG      0x170
#define EMAC_SOFTRESET      0x174
#define EMAC_MACSRCADDRLO   0x1D0
#define EMAC_MACSRCADDRHI   0x1D4
#define EMAC_MACHASH1       0x1D8
#define EMAC_MACHASH2       0x1DC
#define EMAC_MACADDRLO      0x500
#define EMAC_MACADDRHI      0x504
#define EMAC_MACINDEX       0x508

/* EMAC HDP and Completion registors */
#define EMAC_TXHDP(ch)      (0x600 + (ch * 4))
#define EMAC_RXHDP(ch)      (0x620 + (ch * 4))
#define EMAC_TXCP(ch)       (0x640 + (ch * 4))
#define EMAC_RXCP(ch)       (0x660 + (ch * 4))

/* EMAC statistics registers */
#define EMAC_RXGOODFRAMES   0x200
#define EMAC_RXBCASTFRAMES  0x204
#define EMAC_RXMCASTFRAMES  0x208
#define EMAC_RXPAUSEFRAMES  0x20C
#define EMAC_RXCRCERRORS    0x210
#define EMAC_RXALIGNCODEERRORS  0x214
#define EMAC_RXOVERSIZED    0x218
#define EMAC_RXJABBER       0x21C
#define EMAC_RXUNDERSIZED   0x220
#define EMAC_RXFRAGMENTS    0x224
#define EMAC_RXFILTERED     0x228
#define EMAC_RXQOSFILTERED  0x22C
#define EMAC_RXOCTETS       0x230
#define EMAC_TXGOODFRAMES   0x234
#define EMAC_TXBCASTFRAMES  0x238
#define EMAC_TXMCASTFRAMES  0x23C
#define EMAC_TXPAUSEFRAMES  0x240
#define EMAC_TXDEFERRED     0x244
#define EMAC_TXCOLLISION    0x248
#define EMAC_TXSINGLECOLL   0x24C
#define EMAC_TXMULTICOLL    0x250
#define EMAC_TXEXCESSIVECOLL    0x254
#define EMAC_TXLATECOLL     0x258
#define EMAC_TXUNDERRUN     0x25C
#define EMAC_TXCARRIERSENSE 0x260
#define EMAC_TXOCTETS       0x264
#define EMAC_NETOCTETS      0x280
#define EMAC_RXSOFOVERRUNS  0x284
#define EMAC_RXMOFOVERRUNS  0x288
#define EMAC_RXDMAOVERRUNS  0x28C

/* EMAC DM644x control registers */
#define EMAC_CTRL_EWCTL     (0x4)
#define EMAC_CTRL_EWINTTCNT (0x8)

/* EMAC MDIO related */
/* Mask & Control defines */
#define MDIO_CONTROL_CLKDIV (0xFF)
#define MDIO_CONTROL_ENABLE BIT(30)
#define MDIO_USERACCESS_GO  BIT(31)
#define MDIO_USERACCESS_WRITE   BIT(30)
#define MDIO_USERACCESS_READ    (0)
#define MDIO_USERACCESS_REGADR  (0x1F << 21)
#define MDIO_USERACCESS_PHYADR  (0x1F << 16)
#define MDIO_USERACCESS_DATA    (0xFFFF)
#define MDIO_USERPHYSEL_LINKSEL BIT(7)
#define MDIO_VER_MODID      (0xFFFF << 16)
#define MDIO_VER_REVMAJ     (0xFF   << 8)
#define MDIO_VER_REVMIN     (0xFF)

#define MDIO_USERACCESS(inst)   (0x80 + (inst * 8))
#define MDIO_USERPHYSEL(inst)   (0x84 + (inst * 8))
#define MDIO_CONTROL        (0x04)

/* EMAC DM646X control module registers */
#define EMAC_DM646X_CMRXINTEN   (0x14)
#define EMAC_DM646X_CMTXINTEN   (0x18)

/* EMAC EOI codes for C0 */
#define EMAC_DM646X_MAC_EOI_C0_RXEN (0x01)
#define EMAC_DM646X_MAC_EOI_C0_TXEN (0x02)

/* EMAC Stats Clear Mask */
#define EMAC_STATS_CLR_MASK    (0xFFFFFFFF)

/** net_buf_obj: EMAC network bufferdata structure
 *
 * EMAC network buffer data structure
 */
struct emac_netbufobj {
    void *buf_token;
    char *data_ptr;
    int length;
};

/** net_pkt_obj: EMAC network packet data structure
 *
 * EMAC network packet data structure - supports buffer list (for future)
 */
struct emac_netpktobj {
    void *pkt_token; /* data token may hold tx/rx chan id */
    struct emac_netbufobj *buf_list; /* array of network buffer objects */
    int num_bufs;
    int pkt_length;
};

/** emac_tx_bd: EMAC TX Buffer descriptor data structure
 *
 * EMAC TX Buffer descriptor data structure
 */
struct emac_tx_bd {
    int h_next;
    int buff_ptr;
    int off_b_len;
    int mode; /* SOP, EOP, ownership, EOQ, teardown,Qstarv, length */
    struct emac_tx_bd __iomem *next;
    void *buf_token;
};

/** emac_txch: EMAC TX Channel data structure
 *
 * EMAC TX Channel data structure
 */
struct emac_txch {
    /* Config related */
    rt_uint32_t num_bd;
    rt_uint32_t service_max;

    /* CPPI specific */
    rt_uint32_t alloc_size;
    void __iomem *bd_mem;
    struct emac_tx_bd __iomem *bd_pool_head;
    struct emac_tx_bd __iomem *active_queue_head;
    struct emac_tx_bd __iomem *active_queue_tail;
    struct emac_tx_bd __iomem *last_hw_bdprocessed;
    rt_uint32_t queue_active;
    rt_uint32_t teardown_pending;
    rt_uint32_t *tx_complete;

    /** statistics */
    rt_uint32_t proc_count;     /* TX: # of times emac_tx_bdproc is called */
    rt_uint32_t mis_queued_packets;
    rt_uint32_t queue_reinit;
    rt_uint32_t end_of_queue_add;
    rt_uint32_t out_of_tx_bd;
    rt_uint32_t no_active_pkts; /* IRQ when there were no packets to process */
    rt_uint32_t active_queue_count;
};

/** emac_rx_bd: EMAC RX Buffer descriptor data structure
 *
 * EMAC RX Buffer descriptor data structure
 */
struct emac_rx_bd {
    int h_next;
    int buff_ptr;
    int off_b_len;
    int mode;
    struct emac_rx_bd __iomem *next;
    void *data_ptr;
    void *buf_token;
};

/** emac_rxch: EMAC RX Channel data structure
 *
 * EMAC RX Channel data structure
 */
struct emac_rxch {
    /* configuration info */
    rt_uint32_t num_bd;
    rt_uint32_t service_max;
    rt_uint32_t buf_size;
    char mac_addr[6];

    /** CPPI specific */
    rt_uint32_t alloc_size;
    void __iomem *bd_mem;
    struct emac_rx_bd __iomem *bd_pool_head;
    struct emac_rx_bd __iomem *active_queue_head;
    struct emac_rx_bd __iomem *active_queue_tail;
    rt_uint32_t queue_active;
    rt_uint32_t teardown_pending;

    /* packet and buffer objects */
    struct emac_netpktobj pkt_queue;
    struct emac_netbufobj buf_queue;

    /** statistics */
    rt_uint32_t proc_count; /* number of times emac_rx_bdproc is called */
    rt_uint32_t processed_bd;
    rt_uint32_t recycled_bd;
    rt_uint32_t out_of_rx_bd;
    rt_uint32_t out_of_rx_buffers;
    rt_uint32_t queue_reinit;
    rt_uint32_t end_of_queue_add;
    rt_uint32_t end_of_queue;
    rt_uint32_t mis_queued_packets;
};

struct net_device_stats
{
    unsigned long   rx_packets;     /* total packets received   */
    unsigned long   tx_packets;     /* total packets transmitted    */
    unsigned long   rx_bytes;       /* total bytes received     */
    unsigned long   tx_bytes;       /* total bytes transmitted  */
    unsigned long   rx_errors;      /* bad packets received     */
    unsigned long   tx_errors;      /* packet transmit problems */
    unsigned long   rx_dropped;     /* no space in linux buffers    */
    unsigned long   tx_dropped;     /* no space available in linux  */
    unsigned long   multicast;      /* multicast packets received   */
    unsigned long   collisions;

    /* detailed rx_errors: */
    unsigned long   rx_length_errors;
    unsigned long   rx_over_errors;     /* receiver ring buff overflow  */
    unsigned long   rx_crc_errors;      /* recved pkt with crc error    */
    unsigned long   rx_frame_errors;    /* recv'd frame alignment error */
    unsigned long   rx_fifo_errors;     /* recv'r fifo overrun      */
    unsigned long   rx_missed_errors;   /* receiver missed packet   */

    /* detailed tx_errors */
    unsigned long   tx_aborted_errors;
    unsigned long   tx_carrier_errors;
    unsigned long   tx_fifo_errors;
    unsigned long   tx_heartbeat_errors;
    unsigned long   tx_window_errors;

    /* for cslip etc */
    unsigned long   rx_compressed;
    unsigned long   tx_compressed;
};


/* emac_priv: EMAC private data structure
 *
 * EMAC adapter private data structure
 */
#define MAX_ADDR_LEN 6

struct emac_priv {
    /* inherit from ethernet device */
    struct eth_device parent;

    /* interface address info. */
    rt_uint8_t  mac_addr[MAX_ADDR_LEN];     /* hw address   */
    unsigned short      phy_addr;

    struct rt_semaphore tx_lock;
    struct rt_semaphore rx_lock;
    void __iomem *remap_addr;
    rt_uint32_t emac_base_phys;
    void __iomem *emac_base;
    void __iomem *ctrl_base;
    void __iomem *emac_ctrl_ram;
    void __iomem *mdio_base;
    rt_uint32_t ctrl_ram_size;
    rt_uint32_t hw_ram_addr;
    struct emac_txch *txch[EMAC_DEF_MAX_TX_CH];
    struct emac_rxch *rxch[EMAC_DEF_MAX_RX_CH];
    rt_uint32_t link; /* 1=link on, 0=link off */
    rt_uint32_t speed; /* 0=Auto Neg, 1=No PHY, 10,100, 1000 - mbps */
    rt_uint32_t duplex; /* Link duplex: 0=Half, 1=Full */
    rt_uint32_t rx_buf_size;
    rt_uint32_t isr_count;
    rt_uint8_t rmii_en;
    rt_uint8_t version;
    struct net_device_stats net_dev_stats;
    rt_uint32_t mac_hash1;
    rt_uint32_t mac_hash2;
    rt_uint32_t multicast_hash_cnt[EMAC_NUM_MULTICAST_BITS];
    rt_uint32_t rx_addr_type;
    /* periodic timer required for MDIO polling */
    struct rt_timer  timer;
    rt_uint32_t periodic_ticks;
    rt_uint32_t timer_active;
    rt_uint32_t phy_mask;
    /* mii_bus,phy members */
    struct rt_semaphore lock;
};


#endif /* _DAVINCI_EMAC_H */

