/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#ifndef __SDIO_DW_H__
#define __SDIO_DW_H__

#include "../dev_sdio_dm.h"

#define SDIO_DW_CTRL                    0x000
#define SDIO_DW_PWREN                   0x004
#define SDIO_DW_CLKDIV                  0x008
#define SDIO_DW_CLKSRC                  0x00c
#define SDIO_DW_CLKENA                  0x010
#define SDIO_DW_TMOUT                   0x014
#define SDIO_DW_CTYPE                   0x018
#define SDIO_DW_BLKSIZ                  0x01c
#define SDIO_DW_BYTCNT                  0x020
#define SDIO_DW_INTMASK                 0x024
#define SDIO_DW_CMDARG                  0x028
#define SDIO_DW_CMD                     0x02c
#define SDIO_DW_RESP0                   0x030
#define SDIO_DW_RESP1                   0x034
#define SDIO_DW_RESP2                   0x038
#define SDIO_DW_RESP3                   0x03c
#define SDIO_DW_MINTSTS                 0x040
#define SDIO_DW_RINTSTS                 0x044
#define SDIO_DW_STATUS                  0x048
#define SDIO_DW_FIFOTH                  0x04c
#define SDIO_DW_CDETECT                 0x050
#define SDIO_DW_WRTPRT                  0x054
#define SDIO_DW_GPIO                    0x058
#define SDIO_DW_TCBCNT                  0x05c
#define SDIO_DW_TBBCNT                  0x060
#define SDIO_DW_DEBNCE                  0x064
#define SDIO_DW_USRID                   0x068
#define SDIO_DW_VERID                   0x06c
#define SDIO_DW_HCON                    0x070
#define SDIO_DW_UHS_REG                 0x074
#define SDIO_DW_RST_N                   0x078
#define SDIO_DW_BMOD                    0x080
#define SDIO_DW_PLDMND                  0x084
#define SDIO_DW_DBADDR                  0x088
#define SDIO_DW_IDSTS                   0x08c
#define SDIO_DW_IDINTEN                 0x090
#define SDIO_DW_DSCADDR                 0x094
#define SDIO_DW_BUFADDR                 0x098
#define SDIO_DW_CDTHRCTL                0x100
#define SDIO_DW_UHS_REG_EXT             0x108
#define SDIO_DW_DDR_REG                 0x10c
#define SDIO_DW_ENABLE_SHIFT            0x110
#define SDIO_DW_DATA(x)                 (x)
/*
 * Registers to support idmac 64-bit address mode
 */
#define SDIO_DW_DBADDRL                 0x088
#define SDIO_DW_DBADDRU                 0x08c
#define SDIO_DW_IDSTS64                 0x090
#define SDIO_DW_IDINTEN64               0x094
#define SDIO_DW_DSCADDRL                0x098
#define SDIO_DW_DSCADDRU                0x09c
#define SDIO_DW_BUFADDRL                0x0a0
#define SDIO_DW_BUFADDRU                0x0a4

/* Support for longer data read timeout */
#define SDIO_DW_QUIRK_EXTENDED_TMOUT    RT_BIT(0)

#define SDIO_DW_240A                    0x240a
#define SDIO_DW_280A                    0x280a

/*
 * Data offset is difference according to Version
 * Lower than 2.40a : data register offest is 0x100
 */
#define DATA_OFFSET                     0x100
#define DATA_240A_OFFSET                0x200

/* Control register defines */
#define SDIO_DW_CTRL_USE_IDMAC          RT_BIT(25)
#define SDIO_DW_CTRL_CEATA_INT_EN       RT_BIT(11)
#define SDIO_DW_CTRL_SEND_AS_CCSD       RT_BIT(10)
#define SDIO_DW_CTRL_SEND_CCSD          RT_BIT(9)
#define SDIO_DW_CTRL_ABRT_READ_DATA     RT_BIT(8)
#define SDIO_DW_CTRL_SEND_IRQ_RESP      RT_BIT(7)
#define SDIO_DW_CTRL_READ_WAIT          RT_BIT(6)
#define SDIO_DW_CTRL_DMA_ENABLE         RT_BIT(5)
#define SDIO_DW_CTRL_INT_ENABLE         RT_BIT(4)
#define SDIO_DW_CTRL_DMA_RESET          RT_BIT(2)
#define SDIO_DW_CTRL_FIFO_RESET         RT_BIT(1)
#define SDIO_DW_CTRL_RESET              RT_BIT(0)
/* Clock Enable register defines */
#define SDIO_DW_CLKEN_LOW_PWR           RT_BIT(16)
#define SDIO_DW_CLKEN_ENABLE            RT_BIT(0)
/* Time-out register defines */
#define SDIO_DW_TMOUT_DATA(n)           ((n) << 8)
#define SDIO_DW_TMOUT_DATA_MSK          0xffffff00
#define SDIO_DW_TMOUT_RESP(n)           ((n) & 0xff)
#define SDIO_DW_TMOUT_RESP_MSK          0xff
/* Card-type register defines */
#define SDIO_DW_CTYPE_8BIT              RT_BIT(16)
#define SDIO_DW_CTYPE_4BIT              RT_BIT(0)
#define SDIO_DW_CTYPE_1BIT              0
/* Interrupt status & mask register defines */
#define SDIO_DW_INT_SDIO(n)             RT_BIT(16 + (n))
#define SDIO_DW_INT_RAW_SDIO            RT_BIT(24)
#define SDIO_DW_INT_EBE                 RT_BIT(15)
#define SDIO_DW_INT_ACD                 RT_BIT(14)
#define SDIO_DW_INT_SBE                 RT_BIT(13)
#define SDIO_DW_INT_HLE                 RT_BIT(12)
#define SDIO_DW_INT_FRUN                RT_BIT(11)
#define SDIO_DW_INT_HTO                 RT_BIT(10)
#define SDIO_DW_INT_VOLT_SWITCH         RT_BIT(10)
#define SDIO_DW_INT_DRTO                RT_BIT(9)
#define SDIO_DW_INT_RTO                 RT_BIT(8)
#define SDIO_DW_INT_DCRC                RT_BIT(7)
#define SDIO_DW_INT_RCRC                RT_BIT(6)
#define SDIO_DW_INT_RXDR                RT_BIT(5)
#define SDIO_DW_INT_TXDR                RT_BIT(4)
#define SDIO_DW_INT_DATA_OVER           RT_BIT(3)
#define SDIO_DW_INT_CMD_DONE            RT_BIT(2)
#define SDIO_DW_INT_RESP_ERR            RT_BIT(1)
#define SDIO_DW_INT_CD                  RT_BIT(0)
#define SDIO_DW_INT_ERROR               0xbfc2
/* Command register defines */
#define SDIO_DW_CMD_START               RT_BIT(31)
#define SDIO_DW_CMD_USE_HOLD_REG        RT_BIT(29)
#define SDIO_DW_CMD_VOLT_SWITCH         RT_BIT(28)
#define SDIO_DW_CMD_CCS_EXP             RT_BIT(23)
#define SDIO_DW_CMD_CEATA_RD            RT_BIT(22)
#define SDIO_DW_CMD_UPD_CLK             RT_BIT(21)
#define SDIO_DW_CMD_INIT                RT_BIT(15)
#define SDIO_DW_CMD_STOP                RT_BIT(14)
#define SDIO_DW_CMD_PRV_DAT_WAIT        RT_BIT(13)
#define SDIO_DW_CMD_SEND_STOP           RT_BIT(12)
#define SDIO_DW_CMD_STRM_MODE           RT_BIT(11)
#define SDIO_DW_CMD_DAT_WR              RT_BIT(10)
#define SDIO_DW_CMD_DAT_EXP             RT_BIT(9)
#define SDIO_DW_CMD_RESP_CRC            RT_BIT(8)
#define SDIO_DW_CMD_RESP_LONG           RT_BIT(7)
#define SDIO_DW_CMD_RESP_EXP            RT_BIT(6)
#define SDIO_DW_CMD_INDX(n)             ((n) & 0x1f)
/* Status register defines */
#define SDIO_DW_GET_FCNT(x)             (((x) >> 17) & 0x1fff)
#define SDIO_DW_STATUS_DMA_REQ          RT_BIT(31)
#define SDIO_DW_STATUS_BUSY             RT_BIT(9)
/* FIFOTH register defines */
#define SDIO_DW_SET_FIFOTH(m, r, t)     (((m) & 0x7) << 28 | ((r) & 0xfff) << 16 | ((t) & 0xfff))
/* HCON register defines */
#define DMA_INTERFACE_IDMA              (0x0)
#define DMA_INTERFACE_DWDMA             (0x1)
#define DMA_INTERFACE_GDMA              (0x2)
#define DMA_INTERFACE_NODMA             (0x3)
#define SDIO_DW_GET_TRANS_MODE(x)       (((x) >> 16) & 0x3)
#define SDIO_DW_GET_SLOT_NUM(x)         ((((x) >> 1) & 0x1f) + 1)
#define SDIO_DW_GET_HDATA_WIDTH(x)      (((x) >> 7) & 0x7)
#define SDIO_DW_GET_ADDR_CONFIG(x)      (((x) >> 27) & 0x1)
/* Internal DMAC interrupt defines */
#define SDIO_DW_IDMAC_INT_AI            RT_BIT(9)
#define SDIO_DW_IDMAC_INT_NI            RT_BIT(8)
#define SDIO_DW_IDMAC_INT_CES           RT_BIT(5)
#define SDIO_DW_IDMAC_INT_DU            RT_BIT(4)
#define SDIO_DW_IDMAC_INT_FBE           RT_BIT(2)
#define SDIO_DW_IDMAC_INT_RI            RT_BIT(1)
#define SDIO_DW_IDMAC_INT_TI            RT_BIT(0)
/* Internal DMAC bus mode bits */
#define SDIO_DW_IDMAC_ENABLE            RT_BIT(7)
#define SDIO_DW_IDMAC_FB                RT_BIT(1)
#define SDIO_DW_IDMAC_SWRESET           RT_BIT(0)
/* H/W reset */
#define SDIO_DW_RST_HWACTIVE            0x1
/* Version ID register define */
#define SDIO_DW_GET_VERID(x)            ((x) & 0xffff)
/* Card read threshold */
#define SDIO_DW_SET_THLD(v, x)          (((v) & 0xfff) << 16 | (x))
#define SDIO_DW_CARD_WR_THR_EN          RT_BIT(2)
#define SDIO_DW_CARD_RD_THR_EN          RT_BIT(0)
/* UHS-1 register defines */
#define SDIO_DW_UHS_DDR                 RT_BIT(16)
#define SDIO_DW_UHS_18V                 RT_BIT(0)
/* DDR register defines */
#define SDIO_DW_DDR_HS400               RT_BIT(31)
/* Enable shift register defines */
#define SDIO_DW_ENABLE_PHASE            RT_BIT(0)
/* All ctrl reset bits */
#define SDIO_DW_CTRL_ALL_RESET_FLAGS    (SDIO_DW_CTRL_RESET | SDIO_DW_CTRL_FIFO_RESET | SDIO_DW_CTRL_DMA_RESET)

struct rt_dma_chan;

struct sdio_dw
{
    struct rt_device parent;
    struct rt_device *bus_dev;

    struct rt_workqueue *state_wq;
    struct rt_work state_work;

    void *base;
    void *fifo_base;
    rt_ubase_t base_phy;
    rt_uint32_t data_addr_override;
    rt_bool_t wm_aligned;

    int irq;
    int sdio_id0;
    rt_uint32_t verid;
    rt_uint32_t quirks;
    rt_uint32_t bus_hz;
    rt_bool_t fifo_mode;
    rt_uint32_t fifo_depth;
    rt_uint32_t fifoth_val;
    rt_uint32_t detect_delay_ms;
    rt_uint32_t current_speed;
    rt_uint32_t minimum_speed;
    void *priv;

    rt_uint32_t vqmmc_enabled;
    rt_uint32_t cmd_status;
    rt_uint32_t data_status;
    rt_uint32_t stop_cmdr;
    rt_uint32_t dir_status;
#define STATE_IDLE                  0
#define STATE_SENDING_CMD           1
#define STATE_SENDING_DATA          2
#define STATE_DATA_BUSY             3
#define STATE_SENDING_STOP          4
#define STATE_DATA_ERROR            5
#define STATE_SENDING_CMD11         6
#define STATE_WAITING_CMD11_DONE    7
    rt_uint32_t state;
#define EVENT_CMD_COMPLETE          0
#define EVENT_XFER_COMPLETE         1
#define EVENT_DATA_COMPLETE         2
#define EVENT_DATA_ERROR            3
    rt_bitmap_t pending_events;

    struct rt_mmcsd_req *req;
    struct rt_mmcsd_data *data;
    struct rt_mmcsd_cmd *cmd;
    struct rt_mmcsd_cmd stop_abort;
    rt_uint32_t prev_blksz;
    rt_uint8_t timing;

    struct rt_clk *biu_clk;
    struct rt_clk *ciu_clk;

    void *last_buf;
    rt_uint32_t last_remain;

    int data_shift;
    rt_uint8_t part_buf_start;
    rt_uint8_t part_buf_count;
    union
    {
        rt_uint64_t part_buf;
        rt_uint16_t part_buf16;
        rt_uint32_t part_buf32;
        rt_uint64_t part_buf64;
    };
    void (*push_data)(struct sdio_dw *sd, void *buf, int cnt);
    void (*pull_data)(struct sdio_dw *sd, void *buf, int cnt);

    /* DMA interface members */
#define TRANS_MODE_PIO      0
#define TRANS_MODE_IDMAC    1
#define TRANS_MODE_EDMAC    2
    rt_bool_t use_dma;
    rt_bool_t using_dma;
    rt_bool_t dma_64bit_address;
    rt_size_t ring_size;
    void *dma_buf;
    rt_ubase_t dma_buf_phy;
    struct rt_dma_chan *edma_chan;
    const struct sdio_dw_dma_ops *dma_ops;

    struct rt_timer cmd11_timer;
    struct rt_timer cto_timer;
    struct rt_timer dto_timer;

    struct rt_reset_control *rstc;

    struct sdio_dw_slot *slot;
    const struct sdio_dw_drv_data *drv_data;

    struct rt_spinlock lock, irq_lock;
};

/* DMA ops for Internal/External DMAC interface */
struct sdio_dw_dma_ops
{
    rt_err_t (*init)(struct sdio_dw *sd);
    rt_err_t (*start)(struct sdio_dw *sd);
    rt_err_t (*complete)(struct sdio_dw *sd);
    rt_err_t (*stop)(struct sdio_dw *sd);
    rt_err_t (*cleanup)(struct sdio_dw *sd);
    rt_err_t (*exit)(struct sdio_dw *sd);
};

struct sdio_dw_slot
{
    struct rt_mmcsd_host *host;
    struct sdio_dw *sd;

    rt_uint32_t ctype;

    struct rt_mmcsd_req *req;

    rt_uint32_t clock;
    rt_uint32_t clk_old;

#define DW_MMC_CARD_PRESENT     0
#define DW_MMC_CARD_NEED_INIT   1
#define DW_MMC_CARD_NO_LOW_PWR  2
#define DW_MMC_CARD_NO_USE_HOLD 3
#define DW_MMC_CARD_NEEDS_POLL  4
    rt_bitmap_t flags;

    int id;
    int sdio_id;
};

struct sdio_dw_drv_data
{
    rt_ubase_t *caps;
    rt_uint32_t num_caps;
    rt_uint32_t common_caps;

    rt_err_t    (*init)(struct sdio_dw *sd);
    rt_err_t    (*set_iocfg)(struct sdio_dw *sd, struct rt_mmcsd_io_cfg *ios);
    rt_err_t    (*parse_ofw)(struct sdio_dw *sd);
    rt_err_t    (*execute_tuning)(struct sdio_dw_slot *slot, rt_uint32_t opcode);
    rt_err_t    (*prepare_hs400_tuning)(struct sdio_dw *sd, struct rt_mmcsd_io_cfg *ios);
    rt_err_t    (*switch_voltage)(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *ios);
    rt_err_t    (*set_data_timeout)(struct sdio_dw *sd, rt_uint32_t timeout_ns);
    rt_uint32_t (*get_drto_clks)(struct sdio_dw *sd);
};

#define sdio_dw_writel(sd, reg, val)    HWREG32((sd)->base + SDIO_DW_##reg) = (val)
#define sdio_dw_writew(sd, reg, val)    HWREG16((sd)->base + SDIO_DW_##reg) = (val)
#define sdio_dw_writeb(sd, reg, val)    HWREG8((sd)->base + SDIO_DW_##reg) = (val)

#define sdio_dw_readl(sd, reg)          HWREG32((sd)->base + SDIO_DW_##reg)
#define sdio_dw_readw(sd, reg)          HWREG16((sd)->base + SDIO_DW_##reg)
#define sdio_dw_readb(sd, reg)          HWREG8((sd)->base + SDIO_DW_##reg)

#define sdio_dw_fifo_writew(sd, val)    HWREG16((sd)->fifo_base) = (val)
#define sdio_dw_fifo_writel(sd, val)    HWREG32((sd)->fifo_base) = (val)
#define sdio_dw_fifo_writeq(sd, val)    HWREG64((sd)->fifo_base) = (val)

#define sdio_dw_fifo_readw(sd)          HWREG16((sd)->fifo_base)
#define sdio_dw_fifo_readl(sd)          HWREG32((sd)->fifo_base)
#define sdio_dw_fifo_readq(sd)          HWREG64((sd)->fifo_base)

rt_err_t sdio_dw_probe(struct sdio_dw *sd);
rt_err_t sdio_dw_remove(struct sdio_dw *sd);

#endif /* __SDIO_DW_H__ */
