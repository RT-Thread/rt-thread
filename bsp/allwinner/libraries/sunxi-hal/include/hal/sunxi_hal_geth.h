/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the People's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __SUNXI_HAL_GETH_H__
#define __SUNXI_HAL_GETH_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <rtthread.h>
#include <netif/ethernetif.h>
#include <sunxi_hal_common.h>
#include <sunxi_hal_phy.h>
#include <interrupt.h>
#include <hal_gpio.h>

#define CONFIG_DRIVERS_GETH_DEBUG

#ifdef CONFIG_DRIVERS_GETH_DEBUG
#define GETH_INFO(fmt, arg...) printf("GPIO : %s()%d "fmt, __func__, __LINE__, ##arg)
#define GETH_ERR(fmt, arg...) printf("GPIO : %s()%d "fmt, __func__, __LINE__, ##arg)
#else
#define GETH_INFO(fmt, arg...) do {}while(0)
#define GETH_ERR(fmt, arg...) do {}while(0)
#endif

/* Base config for geth */
#define IOBASE                  0x04500000
#define PHY_CLK_REG             (0x03000000 + 0x30)
#define CCMU_BASE               0x02001000

#define CCMU_GETH_CLK_REG       0x097c
#define CCMU_GETH_RST_BIT       16
#define CCMU_GETH_GATING_BIT    0
#define CCMU_EPHY_CLK_REG       0x0970
#define CCMU_EPHY_SCLK_GATING_BIT       31
#define CCMU_EPHY_PLL_PERI0_GATING_BIT  30

//#define DISABLE_AUTONEG
#define CONFIG_HARD_CHECKSUM
#define USE_EPHY25M

#define GETH_IRQ_NUM 62

/* Geth register list */
#define GETH_BASIC_CTL0         0x00
#define GETH_BASIC_CTL1         0x04
#define GETH_INT_STA            0x08
#define GETH_INT_EN             0x0C
#define GETH_TX_CTL0            0x10
#define GETH_TX_CTL1            0x14
#define GETH_TX_FLOW_CTL        0x1C
#define GETH_TX_DESC_LIST       0x20
#define GETH_RX_CTL0            0x24
#define GETH_RX_CTL1            0x28
#define GETH_RX_DESC_LIST       0x34
#define GETH_RX_FRM_FLT         0x38
#define GETH_RX_HASH0           0x40
#define GETH_RX_HASH1           0x44
#define GETH_MDIO_ADDR          0x48
#define GETH_MDIO_DATA          0x4C
#define GETH_ADDR_HI(reg)       (0x50 + ((reg) << 3))
#define GETH_ADDR_LO(reg)       (0x54 + ((reg) << 3))
#define GETH_TX_DMA_STA         0xB0
#define GETH_TX_CUR_DESC        0xB4
#define GETH_TX_CUR_BUF         0xB8
#define GETH_RX_DMA_STA         0xC0
#define GETH_RX_CUR_DESC        0xC4
#define GETH_RX_CUR_BUF         0xC8
#define GETH_RGMII_STA          0xD0

#define MII_BUSY                0x00000001
#define MII_WRITE               0x00000002

#define CTL0_DM                 0x01
#define CTL0_LM                 0x02
#define CTL0_SPEED              0x04

#define BURST_LEN               0x3F000000
#define RX_TX_PRI               0x02
#define SOFT_RST                0x01

#define TX_FLUSH                0x01
#define TX_MD                   0x02
#define TX_NEXT_FRM             0x04
#define TX_TH                   0x0700

#define RX_FLUSH                0x01
#define RX_MD                   0x02
#define RX_RUNT_FRM             0x04
#define RX_ERR_FRM              0x08
#define RX_TH                   0x0030
#define STRIP_FCS               0x10000000

#define TX_INT                  0x00000001
#define TX_STOP_INT             0x00000002
#define TX_UA_INT               0x00000004
#define TX_TOUT_INT             0x00000008
#define TX_UNF_INT              0x00000010
#define TX_EARLY_INT            0x00000020
#define RX_INT                  0x00000100
#define RX_UA_INT               0x00000200
#define RX_STOP_INT             0x00000400
#define RX_TOUT_INT             0x00000800
#define RX_OVF_INT              0x00001000
#define RX_EARLY_INT            0x00002000
#define LINK_STA_INT            0x00010000

/* PHY address */
#define PHY_DM                  0x0010
#define PHY_AUTO_NEG            0x0020
#define PHY_POWERDOWN           0x0080
#define PHY_NEG_EN              0x1000

#define EXT_PHY                 0
#define INT_PHY                 1

#define MAX_ADDR_LEN 6

#define ENET_FRAME_MAX_FRAMELEN 1518
#define DMA_DESC_RX_NUM 64
#define DMA_DESC_TX_NUM 64
#define DMA_MEM_ALIGN_SIZE  2048

#define SYS_PAGE_SIZE (4096U)
#define TX_BUFFER_INDEX_NUM (6)
#define RX_BUFFER_INDEX_NUM (6)
#define TX_BD_INDEX_NUM (1)
#define RX_BD_INDEX_NUM (1)

#define PBUF_MAX_BUFF_SIZE 1514

#define SZ_2K               0x00000800
#define MAX_BUF_SZ  (SZ_2K - 1)
#define circ_inc(n, s) (((n) + 1) % (s))

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

typedef enum rx_frame_status {
    good_frame = 0,
    discard_frame = 1,
    csum_none = 2,
    llc_snap = 4,
} hal_geth_rx_frame_status_t;

typedef union {
    struct {
        /* TDES0 */
        u32 deferred:1;         /* Deferred bit (only half-duplex) */
        u32 under_err:1;        /* Underflow error */
        u32 ex_deferral:1;      /* Excessive deferral */
        u32 coll_cnt:4;         /* Collision count */
        u32 vlan_tag:1;         /* VLAN Frame */

        u32 ex_coll:1;          /* Excessive collision */
        u32 late_coll:1;        /* Late collision */
        u32 no_carr:1;          /* No carrier */
        u32 loss_carr:1;        /* Loss of collision */

        u32 ipdat_err:1;        /* IP payload error */
        u32 frm_flu:1;          /* Frame flushed */
        u32 jab_timeout:1;      /* Jabber timeout */
        u32 err_sum:1;          /* Error summary */

        u32 iphead_err:1;       /* IP header error */
        u32 ttss:1;             /* Transmit time stamp status */
        u32 reserved0:13;
        u32 own:1;              /* Own bit. CPU:0, DMA:1 */
    } tx;

    struct {
        /* RDES0 */
        u32 chsum_err:1;        /* Payload checksum error */
        u32 crc_err:1;          /* CRC error */
        u32 dribbling:1;        /* Dribble bit error */
        u32 mii_err:1;          /* Received error (bit3) */

        u32 recv_wt:1;          /* Received watchdog timeout */
        u32 frm_type:1;         /* Frame type */
        u32 late_coll:1;        /* Late Collision */
        u32 ipch_err:1;         /* IPv header checksum error (bit7) */

        u32 last_desc:1;        /* Laset descriptor */
        u32 first_desc:1;       /* First descriptor */
        u32 vlan_tag:1;         /* VLAN Tag */
        u32 over_err:1;         /* Overflow error (bit11) */

        u32 len_err:1;          /* Length error */
        u32 sou_filter:1;       /* Source address filter fail */
        u32 desc_err:1;         /* Descriptor error */
        u32 err_sum:1;          /* Error summary (bit15) */

        u32 frm_len:14;         /* Frame length */
        u32 des_filter:1;       /* Destination address filter fail */
        u32 own:1;              /* Own bit. CPU:0, DMA:1 */
        #define RX_PKT_OK               0x7FFFB77C
        #define RX_LEN                  0x3FFF0000
    } rx;

    u32 all;
} desc0_u;

typedef union {
    struct {
        /* TDES1 */
        u32 buf1_size:11;       /* Transmit buffer1 size */
        u32 buf2_size:11;       /* Transmit buffer2 size */
        u32 ttse:1;             /* Transmit time stamp enable */
        u32 dis_pad:1;          /* Disable pad (bit23) */

        u32 adr_chain:1;        /* Second address chained */
        u32 end_ring:1;         /* Transmit end of ring */
        u32 crc_dis:1;          /* Disable CRC */
        u32 cic:2;              /* Checksum insertion control (bit27:28) */
        u32 first_sg:1;         /* First Segment */
        u32 last_seg:1;         /* Last Segment */
        u32 interrupt:1;        /* Interrupt on completion */
    } tx;

    struct {
        /* RDES1 */
        u32 buf1_size:11;       /* Received buffer1 size */
        u32 buf2_size:11;       /* Received buffer2 size */
        u32 reserved1:2;

        u32 adr_chain:1;        /* Second address chained */
        u32 end_ring:1;         /* Received end of ring */
        u32 reserved2:5;
        u32 dis_ic:1;           /* Disable interrupt on completion */
    } rx;

    u32 all;
} desc1_u;

typedef struct dma_desc {
        desc0_u desc0;
        desc1_u desc1;
        u32 desc2;
        u32 desc3;
        u32 resever0;
        u32 resever1;
        u32 resever2;
        u32 resever3;
        u32 resever4;
        u32 resever5;
        u32 resever6;
        u32 resever7;
        u32 resever8;
        u32 resever9;
        u32 resever10;
        u32 resever11;
} hal_geth_dma_desc_t;

typedef struct geth_buffer_config
{
    hal_geth_dma_desc_t *dma_desc_tx;
    hal_geth_dma_desc_t *dma_desc_rx;
    hal_geth_dma_desc_t *phy_dma_desc_tx;
    hal_geth_dma_desc_t *phy_dma_desc_rx;

    void *tx_buff_addr;
    void *rx_buff_addr;
    void *phy_tx_buff_addr;
    void *phy_rx_buff_addr;

} geth_buffer_config_t;

struct geth_device {
    /* inherit from ethernet device */
    struct eth_device parent;
    /* interface address info, hw address */
    uint8_t dev_addr[MAX_ADDR_LEN];
    /* ethernet device base address */
    unsigned long iobase;
    /* phy mode */
    phy_interface_t phy_interface;
    rt_bool_t phy_link_status;
    geth_buffer_config_t get_buffer_config;

    uint32_t used_type;
    uint32_t tx_delay;
    uint32_t rx_delay;
};

typedef struct geth_priv {
    struct hal_gmac_dma_desc_t *dma_desc_tx;
    struct hal_gmac_dma_desc_t *dma_desc_rx;
    char *rx_handle_buf;

    int32_t base;
    int32_t phy_tpye;
    int32_t phy_interface;
} hal_geth_priv_data_t;

typedef struct sunxi_hal_driver_geth {
    rt_err_t (*initialize)(rt_device_t dev);
    void (*uninitialize)(rt_device_t dev);
    int32_t (*get_mac_address)(const unsigned char *addr);
    int32_t (*set_mac_address)(unsigned char *addr);
    int32_t (*set_address_filter)(void);
    rt_err_t (*send)(rt_device_t dev, struct pbuf *p);
    struct pbuf* (*recv)(rt_device_t dev);
    //int32_t (*phy_read)(uint8_t phy_addr, uint8_t reg_addr, uint16_t *data);
    //int32_t (*phy_write)(uint8_t phy_addr, uint8_t reg_addr, uint16_t data);
} const sunxi_hal_driver_geth_t;

void random_ether_addr(u8 *addr);
void geth_set_link_mode(unsigned long iobase, int duplex, int speed);
void geth_mac_loopback(unsigned long iobase, int enable);
void geth_start_tx(unsigned long iobase);
void geth_stop_tx(unsigned long iobase);
void geth_start_rx(unsigned long iobase);
void geth_stop_rx(unsigned long iobase);
uint32_t geth_mac_reset(unsigned long iobase);
void geth_mac_init(unsigned long iobase);
void geth_set_filter(unsigned long iobase);
void geth_set_mac_addr(unsigned long iobase, unsigned char *addr, int index);
void geth_mac_enable(unsigned long iobase);
void geth_mac_disable(unsigned long iobase);
void geth_tx_poll(unsigned long iobase);
void geth_rx_poll(unsigned long iobase);
void geth_flush_tx(unsigned long iobase);
void geth_rx_int_enable(unsigned long iobase);
void geth_rx_int_disable(unsigned long iobase);
void geth_tx_int_enable(unsigned long iobase);
void geth_tx_int_disable(unsigned long iobase);
void geth_all_int_disable(unsigned long iobase);
void geth_clk_enable(uint32_t used_type,uint32_t phy_interface,uint32_t tx_delay,uint32_t rx_delay);
void geth_clk_disable(void);
uint32_t geth_mdio_read(unsigned long iobase, int phy_addr, u8 reg);
uint32_t geth_mdio_write(unsigned long iobase, int phy_addr, u8 reg, u16 data);
void rt_geth_driver_init(void);
void geth_loopback_enable(unsigned long iobase);
void geth_loopback_disable(unsigned long iobase);


#ifdef  __cplusplus
}
#endif

#endif /* __SUNXI_HAL_GETH_H__ */
