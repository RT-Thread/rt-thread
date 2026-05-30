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
#include <bitmap.h>

#define DBG_TAG "dma.pl330"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define _FIELD_READ(h, l, x)                ((RT_GENMASK(h, l) & (x)) >> l)

#define PL330_REG_DSR                       0x000                   /* DMA Manager Status Register */
#define PL330_REG_DPC                       0x004                   /* DMA Program Counter Register */
#define PL330_REG_INTEN                     0x020                   /* Interrupt Enable Register */
#define PL330_REG_INT_EVENT_RIS             0x024                   /* Event-Interrupt Raw Status Register */
#define PL330_REG_INTMIS                    0x028                   /* Interrupt Status Register */
#define PL330_REG_INTCLR                    0x02c                   /* Interrupt Clear Register */
#define PL330_REG_FSRD                      0x030                   /* Fault Status DMA Manager Register */
#define PL330_REG_FSRC                      0x034                   /* Fault Status DMA Channel Register */
#define PL330_REG_FTRD                      0x038                   /* Fault Type DMA Manager Register */
#define PL330_REG_FTR(n)                    (0x040 + (n) * 0x4)     /* Fault Type DMA Channel [n] */
#define   PL330_FT_UNDEF_INSTR              RT_BIT(0)
#define   PL330_FT_OPERAND_INVALID          RT_BIT(1)
#define   PL330_FT_DMAGO_ERR                RT_BIT(4)
#define   PL330_FT_EVENT_ERR                RT_BIT(5)
#define   PL330_FT_CH_PERIPH_ERR            RT_BIT(6)
#define   PL330_FT_CH_RDWR_ERR              RT_BIT(7)
#define   PL330_FT_ST_DATA_UNAVAILABLE      RT_BIT(12)
#define   PL330_FT_FIFOEMPTY_ERR            RT_BIT(13)
#define   PL330_FT_INSTR_FETCH_ERR          RT_BIT(16)
#define   PL330_FT_DATA_WRITE_ERR           RT_BIT(17)
#define   PL330_FT_DATA_READ_ERR            RT_BIT(18)
#define   PL330_FT_DBG_INSTR                RT_BIT(30)
#define   PL330_FT_LOCKUP_ERR               RT_BIT(31)
#define PL330_REG_CSR(n)                    (0x100 + (n) * 0x8)     /* Channel [n] Status Register */
#define   PL330_CS_STOP                     0x0
#define   PL330_CS_EXEC                     0x1
#define   PL330_CS_CMISS                    0x2
#define   PL330_CS_UPDTPC                   0x3
#define   PL330_CS_WFE                      0x4
#define   PL330_CS_ATBRR                    0x5
#define   PL330_CS_QBUSY                    0x6
#define   PL330_CS_WFP                      0x7
#define   PL330_CS_KILL                     0x8
#define   PL330_CS_CMPLT                    0x9
#define   PL330_CS_FLTCMP                   0xe
#define   PL330_CS_FAULT                    0xf
#define PL330_REG_CPC(n)                    (0x104 + (n) * 0x8)     /* Channel [n] Program Counter Register */
#define pl330_REG_SAR(n)                    (0x0400 + (n) * 0x20)   /* Channel [n] Source Address Register */
#define pl330_REG_DAR(n)                    (0x0404 + (n) * 0x20)   /* Channel [n] Destination Address Register */
#define pl330_REG_CCR(n)                    (0x0408 + (n) * 0x20)   /* Channel [n] Channel Control Register */
#define pl330_REG_LC0(n)                    (0x040c + (n) * 0x20)   /* Channel [n] Loop Counter 0 Register */
#define pl330_REG_LC1(n)                    (0x0410 + (n) * 0x20)   /* Channel [n] Loop Counter 1 Register */
#define PL330_REG_DBGSTATUS                 0xd00                   /* Debug Status Register */
#define   PL330_DBGSTATUS_IDLE              0
#define   PL330_DBGSTATUS_BUSY              RT_BIT(0)
#define PL330_REG_DBGCMD                    0xd04                   /* Debug Command Register */
#define PL330_REG_DBGINST0                  0xd08                   /* Debug Instruction-0 Register */
#define PL330_REG_DBGINST1                  0xd0c                   /* Debug Instruction-1 Register */
#define PL330_REG_CR(n)                     (0xe00 + (n) * 0x4)     /* Configuration Register [n] */
#define   PL330_CR0_PERIPH_REQ_SET          RT_BIT(0)
#define   PL330_CR0_MGR_NS_AT_RST(x)        _FIELD_READ(2, 2, x)
#define   PL330_CR0_NUM_CHNLS(x)            _FIELD_READ(6, 4, x)
#define   PL330_CR0_NUM_PERIPH(x)           _FIELD_READ(16, 12, x)
#define   PL330_CR0_NUM_EVENTS(x)           _FIELD_READ(21, 17, x)
#define PL330_REG_CRD                       0x0e14                  /* Configuration Register */
#define   PL330_CRD_DATA_WIDTH(x)           _FIELD_READ(2, 0, x)
#define   PL330_CRD_WR_CAP(x)               _FIELD_READ(6, 4, x)
#define   PL330_CRD_WR_Q_DEP(x)             _FIELD_READ(11, 8, x)
#define   PL330_CRD_RD_CAP(x)               _FIELD_READ(14, 12, x)
#define   PL330_CRD_RD_Q_DEP(x)             _FIELD_READ(19, 16, x)
#define   PL330_CRD_DATA_BUFFER_DEP(x)      _FIELD_READ(29, 20, x)
#define PL330_REG_WDT                       0x0e80                  /* DMA Watchdog Register */
#define PL330_REG_PERIPH_ID                 0x0fe0                  /* Periph ID Register */
#define   PL330_PERIPH_REV(x)               _FIELD_READ(23, 20, x)
#define   PL330_PERIPH_REV_R0P0             0
#define   PL330_PERIPH_REV_R1P0             1
#define   PL330_PERIPH_REV_R1P1             2

#define PL330_CMD_DMAADDH                   0x54
#define PL330_CMD_DMAEND                    0x00
#define PL330_CMD_DMAFLUSHP                 0x35
#define PL330_CMD_DMAGO                     0xa0
#define PL330_CMD_DMALD                     0x04
#define PL330_CMD_DMALDP                    0x25
#define PL330_CMD_DMALP                     0x20
#define PL330_CMD_DMALPEND                  0x28
#define PL330_CMD_DMAKILL                   0x01
#define PL330_CMD_DMAMOV                    0xbc
#define PL330_CMD_DMANOP                    0x18
#define PL330_CMD_DMARMB                    0x12
#define PL330_CMD_DMASEV                    0x34
#define PL330_CMD_DMAST                     0x08
#define PL330_CMD_DMASTP                    0x29
#define PL330_CMD_DMASTZ                    0x0c
#define PL330_CMD_DMAWFE                    0x36
#define PL330_CMD_DMAWFP                    0x30
#define PL330_CMD_DMAWMB                    0x13

#define PL330_SIZE_DMAADDH                  3
#define PL330_SIZE_DMAEND                   1
#define PL330_SIZE_DMAFLUSHP                2
#define PL330_SIZE_DMALD                    1
#define PL330_SIZE_DMALDP                   2
#define PL330_SIZE_DMALP                    2
#define PL330_SIZE_DMALPEND                 2
#define PL330_SIZE_DMAKILL                  1
#define PL330_SIZE_DMAMOV                   6
#define PL330_SIZE_DMANOP                   1
#define PL330_SIZE_DMARMB                   1
#define PL330_SIZE_DMASEV                   2
#define PL330_SIZE_DMAST                    1
#define PL330_SIZE_DMASTP                   2
#define PL330_SIZE_DMASTZ                   1
#define PL330_SIZE_DMAWFE                   2
#define PL330_SIZE_DMAWFP                   2
#define PL330_SIZE_DMAWMB                   1
#define PL330_SIZE_DMAGO                    6

#define PL330_DIR_SAR                       0
#define PL330_DIR_CCR                       1
#define PL330_DIR_DAR                       2

#define PL330_SRC_INC                       RT_BIT(0)
#define PL330_SRC_BURST_SIZE_SHIFT          1
#define PL330_SRC_BURST_LEN_SHIFT           4
#define PL330_DST_INC                       RT_BIT(14)
#define PL330_DST_BURST_SIZE_SHIFT          15
#define PL330_DST_BURST_LEN_SHIFT           18

#define PL330_COND_SINGLE                   0
#define PL330_COND_BURST                    1
#define PL330_COND_ALWAYS                   2

#define PL330_MICROCODE_SIZE                128
#define AMBA_NR_IRQS                        9

struct pl330_chan
{
    struct rt_dma_chan parent;

    rt_bool_t enabled;
    rt_size_t size;

    void *microcode;
    rt_size_t microcode_len;
    rt_ubase_t microcode_dma;
    rt_uint8_t microcode_raw[PL330_MICROCODE_SIZE + 4]; /* For align */
};

struct pl330
{
    struct rt_dma_controller parent;

    void *regs;
    int irqs_nr;
    int irqs[AMBA_NR_IRQS];

#define PL330_QUIRK_BROKEN_NO_FLUSHP    RT_BIT(0)
#define PL330_QUIRK_PERIPH_BURST        RT_BIT(1)
    rt_uint32_t quirk;

    rt_uint32_t mode_ns;
    rt_uint32_t num_chan;
    rt_uint32_t num_peri;
    rt_uint32_t num_events;
    rt_uint32_t data_width;
    rt_uint32_t data_buffer_dep;
    rt_uint32_t ins;

    struct pl330_chan *chans;

    struct rt_clk *pclk;
    struct rt_reset_control *rstc;
    struct rt_reset_control *rstc_ocp;
};
#define raw_to_pl330(raw)   rt_container_of(raw, struct pl330, parent)

static void pl330_read_config(struct pl330 *pl330)
{
    rt_uint32_t value;
    void *regs = pl330->regs;

    value = HWREG32(regs + PL330_REG_CR(0));
    pl330->mode_ns = !!PL330_CR0_NUM_EVENTS(value);
    pl330->num_chan = PL330_CR0_NUM_CHNLS(value) + 1;
    pl330->num_events = PL330_CR0_NUM_EVENTS(value) + 1;

    if (value & PL330_CR0_PERIPH_REQ_SET)
    {
        pl330->num_peri = PL330_CR0_NUM_PERIPH(value) + 1;
    }

    value = HWREG32(regs + PL330_REG_CRD);
    pl330->data_width = 8 * (1 << PL330_CRD_DATA_WIDTH(value));
    pl330->data_buffer_dep = PL330_CRD_DATA_BUFFER_DEP(value) + 1;

    pl330->ins = HWREG32(regs + PL330_REG_CR(3));
}

static rt_err_t pl330_ccr_config(struct rt_dma_slave_config *conf, rt_uint32_t *ccr)
{
    *ccr = PL330_SRC_INC | PL330_DST_INC;
    *ccr |= conf->src_maxburst << PL330_SRC_BURST_LEN_SHIFT;
    *ccr |= conf->dst_maxburst << PL330_DST_BURST_LEN_SHIFT;

    switch (conf->src_addr_width)
    {
    case RT_DMA_SLAVE_BUSWIDTH_1_BYTE:
        *ccr |= 0 << PL330_SRC_BURST_SIZE_SHIFT;
        break;
    case RT_DMA_SLAVE_BUSWIDTH_2_BYTES:
        *ccr |= 1 << PL330_SRC_BURST_SIZE_SHIFT;
        break;
    case RT_DMA_SLAVE_BUSWIDTH_4_BYTES:
        *ccr |= 2 << PL330_SRC_BURST_SIZE_SHIFT;
        break;

    default:
        return -RT_EINVAL;
    }

    switch (conf->dst_addr_width)
    {
    case RT_DMA_SLAVE_BUSWIDTH_1_BYTE:
        *ccr |= 0 << PL330_DST_BURST_SIZE_SHIFT;
        break;
    case RT_DMA_SLAVE_BUSWIDTH_2_BYTES:
        *ccr |= 1 << PL330_DST_BURST_SIZE_SHIFT;
        break;
    case RT_DMA_SLAVE_BUSWIDTH_4_BYTES:
        *ccr |= 2 << PL330_DST_BURST_SIZE_SHIFT;
        break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static int pl330_cmd_dmamov(rt_uint8_t *microcode, rt_uint8_t rd, rt_uint32_t imm)
{
    /*
     * DMAMOV encoding
     * 15 4 3 2 1 10 ... 8 7 6 5 4 3 2 1 0
     *  0 0 0 0 0 |rd[2:0]|1 0 1 1 1 1 0 0
     *
     * 47 ... 16
     *  imm[32:0]
     *
     * rd: b000 for SAR, b001 CCR, b010 DAR
     */

    *microcode++ = PL330_CMD_DMAMOV;
    *microcode++ = rd;
    *microcode++ = imm;
    *microcode++ = imm >> 8;
    *microcode++ = imm >> 16;
    *microcode++ = imm >> 24;

    LOG_D("DMAMOV %s, %#x", ((const char *const []){
            [PL330_DIR_SAR] = "SAR",
            [PL330_DIR_CCR] = "CCR",
            [PL330_DIR_DAR] = "DAR"
        })[rd], imm);

    return PL330_SIZE_DMAMOV;
}

static int pl330_cmd_dmald(rt_uint8_t *microcode, rt_uint32_t cond)
{
    /*
     * DMALD encoding
     * 7 6 5 4 3 2 1  0
     * 0 0 0 0 0 1 bs x
     */
    *microcode = PL330_CMD_DMALD;

    if (cond == PL330_COND_SINGLE)
    {
        *microcode |= (0 << 1) | (1 << 0);
    }
    else if (cond == PL330_COND_BURST)
    {
        *microcode |= (1 << 1) | (1 << 0);
    }

    LOG_D("DMALD %c", ((char []){
            [PL330_COND_SINGLE] = 'S',
            [PL330_COND_BURST] = 'B',
            [PL330_COND_ALWAYS] = 'A'
        })[cond]);

    return PL330_SIZE_DMALD;
}

static int pl330_cmd_dmast(rt_uint8_t *microcode, rt_uint32_t cond)
{
    /*
     * DMAST encoding
     * 7 6 5 4 3 2 1  0
     * 0 0 0 0 1 0 bs x
     */
    *microcode = PL330_CMD_DMAST;

    if (cond == PL330_COND_SINGLE)
    {
        *microcode |= (0 << 1) | (1 << 0);
    }
    else if (cond == PL330_COND_BURST)
    {
        *microcode |= (1 << 1) | (1 << 0);
    }

    LOG_D("DMAST %c", ((char []){
            [PL330_COND_SINGLE] = 'S',
            [PL330_COND_BURST] = 'B',
            [PL330_COND_ALWAYS] = 'A'
        })[cond]);

    return PL330_SIZE_DMAST;
}

static int pl330_cmd_dmalp(rt_uint8_t *microcode, rt_uint8_t lc, rt_uint16_t loops)
{
    /*
     * DMALP encoding
     * 15   ...   8 7 6 5 4 3 2 1  0
     * | iter[7:0] |0 0 1 0 0 0 lc 0
     */
    *microcode++ = PL330_CMD_DMALP | ((lc & 1) << 1);
    *microcode |= loops - 1;

    LOG_D("DMALP %u (lc: %c)", loops - 1, lc ? '1' : '0');

    return PL330_SIZE_DMALP;
}

static int pl330_cmd_dmalpend(rt_uint8_t *microcode, rt_uint32_t cond,
        rt_bool_t forever, rt_uint32_t loop, rt_uint8_t bjump)
{
    /*
     * DMALPEND encoding
     * 15       ...        8 7 6 5 4  3 2  1  0
     * | backward_jump[7:0] |0 0 1 nf 1 lc bs x
     */
    *microcode = PL330_CMD_DMALPEND;

    if (loop)
    {
        *microcode |= (1 << 2);
    }

    if (!forever)
    {
        *microcode |= (1 << 4);
    }

    if (cond == PL330_COND_SINGLE)
    {
        *microcode |= (0 << 1) | (1 << 0);
    }
    else if (cond == PL330_COND_BURST)
    {
        *microcode |= (1 << 1) | (1 << 0);
    }

    ++microcode;

    *microcode = bjump;

    LOG_D("DMALPEND %c (%sloop: %c bjump: %d)", ((char []){
            [PL330_COND_SINGLE] = 'S',
            [PL330_COND_BURST] = 'B',
            [PL330_COND_ALWAYS] = 'A'
        })[cond], forever ? "FE, " : "", loop ? 'Y' : 'N', bjump);

    return PL330_SIZE_DMALPEND;
}

static int pl330_cmd_dmasev(rt_uint8_t *microcode, int event)
{
    *microcode++ = PL330_CMD_DMASEV;
    *microcode++ = (event & 0x1f) << 3;

    LOG_D("DMASEV %u", event & 0x1f);

    return PL330_SIZE_DMASEV;
}

static int pl330_cmd_dmaend(rt_uint8_t *microcode)
{
    /*
     * DMAEND encoding:
     * 7 6 5 4 3 2 1 0
     * 0 0 0 0 0 0 0 0
     */
    *microcode = PL330_CMD_DMAEND;

    LOG_D("DMAEND");

    return PL330_SIZE_DMAEND;
}

static rt_uint32_t pl330_chan_id(struct pl330 *pl330, struct pl330_chan *pc)
{
    return pc - pl330->chans;
}

static struct rt_dma_chan *pl330_dma_request_chan(struct rt_dma_controller *ctrl,
        struct rt_device *slave, void *fw_data)
{
    int idx = -1;
    struct pl330_chan *pc;
    struct pl330 *pl330 = raw_to_pl330(ctrl);
    struct rt_ofw_cell_args *args = fw_data;

    if (args && (idx = args->args[0]) >= pl330->num_chan)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

    if (idx >= 0)
    {
        pc = &pl330->chans[idx];

        if (pc->enabled)
        {
            return rt_err_ptr(-RT_EBUSY);
        }
    }
    else
    {
        /*
         * Memory to Memory is often called after after DM has been initialized,
         * So just return unused chan
         */
        for (int i = 0; i < pl330->num_chan; ++i)
        {
            pc = &pl330->chans[i];

            if (!pc->enabled)
            {
                goto _found;
            }
        }

        return RT_NULL;
    }

_found:
    pc->enabled = RT_TRUE;
    HWREG32(pl330->regs + PL330_REG_INTEN) |= RT_BIT(pl330_chan_id(pl330, pc));

    return &pc->parent;
}

static rt_err_t pl330_dma_release_chan(struct rt_dma_chan *chan)
{
    struct pl330_chan *pc = rt_container_of(chan, struct pl330_chan, parent);

    pc->enabled = RT_FALSE;

    return RT_EOK;
}

static rt_err_t pl330_dma_start(struct rt_dma_chan *chan)
{
    struct pl330_chan *pc = rt_container_of(chan, struct pl330_chan, parent);
    struct pl330 *pl330 = raw_to_pl330(chan->ctrl);

    while (HWREG32(pl330->regs + PL330_REG_DBGSTATUS) & PL330_DBGSTATUS_BUSY)
    {
        rt_hw_cpu_relax();
    }

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, pc->microcode, pc->microcode_len);

    HWREG32(pl330->regs + PL330_REG_DBGINST0) = ((pl330_chan_id(pl330, pc) + 1) << 8) | (PL330_CMD_DMAGO << 16);
    HWREG32(pl330->regs + PL330_REG_DBGINST1) = pc->microcode_dma;
    HWREG32(pl330->regs + PL330_REG_DBGCMD) = 0;

    return RT_EOK;
}

static rt_err_t pl330_dma_stop(struct rt_dma_chan *chan)
{
    struct pl330_chan *pc = rt_container_of(chan, struct pl330_chan, parent);
    struct pl330 *pl330 = raw_to_pl330(chan->ctrl);

    while (HWREG32(pl330->regs + PL330_REG_DBGSTATUS) & PL330_DBGSTATUS_BUSY)
    {
        rt_hw_cpu_relax();
    }

    HWREG32(pl330->regs + PL330_REG_DBGINST0) = ((pl330_chan_id(pl330, pc) + 1) << 8) | PL330_CMD_DMAKILL;
    HWREG32(pl330->regs + PL330_REG_DBGINST1) = 0;
    HWREG32(pl330->regs + PL330_REG_DBGCMD) = 0;

    return RT_EOK;
}

static rt_err_t pl330_dma_config(struct rt_dma_chan *chan,
        struct rt_dma_slave_config *conf)
{
    return RT_EOK;
}

static rt_err_t pl330_dma_prep_memcpy(struct rt_dma_chan *chan,
        rt_ubase_t dma_addr_src, rt_ubase_t dma_addr_dst, rt_size_t len)
{
    void *mc;
    rt_err_t err;
    rt_uint32_t value;
    rt_size_t burst_bytes;
    rt_uint8_t ljmp_inner, ljmp_outer;
    rt_uint16_t loop, outer, rem, inner_first;
    struct pl330_chan *pc = rt_container_of(chan, struct pl330_chan, parent);
    struct pl330 *pl330 = raw_to_pl330(chan->ctrl);
    struct rt_dma_slave_config *conf = &chan->conf;

    mc = pc->microcode;

    if ((err = pl330_ccr_config(conf, &value)))
    {
        return err;
    }
    mc += pl330_cmd_dmamov(mc, PL330_DIR_CCR, value);

    mc += pl330_cmd_dmamov(mc, PL330_DIR_SAR, dma_addr_src);

    mc += pl330_cmd_dmamov(mc, PL330_DIR_DAR, dma_addr_dst);

    burst_bytes = conf->src_addr_width * conf->src_maxburst;

    if (!burst_bytes || !len)
    {
        return -RT_EINVAL;
    }

    if (len % burst_bytes)
    {
        LOG_E("Memcpy len(%lu) must be multiple of burst(%lu)", len, burst_bytes);
        return -RT_EINVAL;
    }

    /* Total iterations */
    loop = len / burst_bytes;
    if (loop == 0)
    {
        return -RT_EINVAL;
    }

    outer = loop / 256;
    rem = loop % 256;

    if (outer == 0)
    {
        outer = 1;
    }

    inner_first = (loop < 256) ? loop : 256;

    mc += pl330_cmd_dmalp(mc, 1, outer);
    ljmp_outer = mc - pc->microcode;

    mc += pl330_cmd_dmalp(mc, 0, inner_first);
    ljmp_inner = mc - pc->microcode;

    mc += pl330_cmd_dmald(mc, PL330_COND_ALWAYS);
    mc += pl330_cmd_dmast(mc, PL330_COND_ALWAYS);

    mc += pl330_cmd_dmalpend(mc, PL330_COND_ALWAYS, RT_FALSE, 0,
                             mc - pc->microcode - ljmp_inner);

    if (rem && loop > 256)
    {
        rt_uint8_t ljmp_inner2;

        mc += pl330_cmd_dmalp(mc, 0, rem);
        ljmp_inner2 = mc - pc->microcode;

        mc += pl330_cmd_dmald(mc, PL330_COND_ALWAYS);
        mc += pl330_cmd_dmast(mc, PL330_COND_ALWAYS);

        mc += pl330_cmd_dmalpend(mc, PL330_COND_ALWAYS, RT_FALSE, 0,
                                 mc - pc->microcode - ljmp_inner2);
    }

    mc += pl330_cmd_dmalpend(mc, PL330_COND_ALWAYS, RT_FALSE, 1,
                             mc - pc->microcode - ljmp_outer);

    mc += pl330_cmd_dmasev(mc, pl330_chan_id(pl330, pc));

    mc += pl330_cmd_dmaend(mc);

    pc->size = len;
    pc->microcode_len = mc - pc->microcode;

    return RT_EOK;
}

static rt_err_t pl330_dma_prep_cyclic(struct rt_dma_chan *chan,
        rt_ubase_t dma_buf_addr, rt_size_t buf_len, rt_size_t period_len,
        enum rt_dma_transfer_direction dir)
{
    void *mc;
    rt_err_t err;
    rt_uint32_t ccr_val;
    rt_size_t burst_bytes;
    rt_uint16_t period_loop, total_periods;
    struct pl330_chan *pc = rt_container_of(chan, struct pl330_chan, parent);
    struct pl330 *pl330 = raw_to_pl330(chan->ctrl);
    struct rt_dma_slave_config *conf = &chan->conf;

    mc = pc->microcode;

    if ((err = pl330_ccr_config(conf, &ccr_val)))
    {
        return err;
    }

    mc += pl330_cmd_dmamov(mc, PL330_DIR_CCR, ccr_val);

    if (dir == RT_DMA_MEM_TO_DEV)
    {
        mc += pl330_cmd_dmamov(mc, PL330_DIR_SAR, dma_buf_addr);
        mc += pl330_cmd_dmamov(mc, PL330_DIR_DAR, conf->dst_addr);
    }
    else if (dir == RT_DMA_DEV_TO_MEM)
    {
        mc += pl330_cmd_dmamov(mc, PL330_DIR_SAR, conf->src_addr);
        mc += pl330_cmd_dmamov(mc, PL330_DIR_DAR, dma_buf_addr);
    }

    burst_bytes = conf->src_addr_width * conf->src_maxburst;
    if (!burst_bytes)
    {
        return -RT_EINVAL;
    }

    if (period_len % burst_bytes)
    {
        return -RT_EINVAL;
    }

    if (buf_len % period_len)
    {
        return -RT_EINVAL;
    }

    period_loop = period_len / burst_bytes;

    if (period_loop == 0 || period_loop > 255)
    {
        return -RT_EINVAL;
    }

    total_periods = buf_len / period_len;
    if (total_periods == 0)
    {
        return -RT_EINVAL;
    }

    /* Outer Loop */
    mc += pl330_cmd_dmalp(mc, 1 /* LC1 */, 0 /* Infinite loop */);
    rt_uint8_t outer_ljmp = mc - pc->microcode;

    /* Inner Loop */
    mc += pl330_cmd_dmalp(mc, 0 /* LC0 */, period_loop);
    rt_uint8_t inner_ljmp = mc - pc->microcode;

    mc += pl330_cmd_dmald(mc, PL330_COND_ALWAYS);
    mc += pl330_cmd_dmast(mc, PL330_COND_ALWAYS);

    mc += pl330_cmd_dmalpend(mc, PL330_COND_ALWAYS,
                             RT_FALSE, 0,
                             mc - pc->microcode - inner_ljmp);

    mc += pl330_cmd_dmasev(mc, pl330_chan_id(pl330, pc));

    /* Outer loop end */
    mc += pl330_cmd_dmalpend(mc, PL330_COND_ALWAYS,
                             RT_FALSE, 1,  /* LC1 */
                             mc - pc->microcode - outer_ljmp);

    pc->microcode_len = mc - pc->microcode;

    return RT_EOK;
}

static rt_err_t pl330_dma_prep_single(struct rt_dma_chan *chan,
        rt_ubase_t dma_buf_addr, rt_size_t buf_len,
        enum rt_dma_transfer_direction dir)
{
    void *mc;
    rt_err_t err;
    rt_uint16_t loop;
    rt_uint32_t ccr_val;
    rt_size_t burst_bytes;
    struct pl330_chan *pc = rt_container_of(chan, struct pl330_chan, parent);
    struct pl330 *pl330 = raw_to_pl330(chan->ctrl);
    struct rt_dma_slave_config *conf = &chan->conf;

    mc = pc->microcode;

    if ((err = pl330_ccr_config(conf, &ccr_val)))
    {
        return err;
    }

    mc += pl330_cmd_dmamov(mc, PL330_DIR_CCR, ccr_val);

    if (dir == RT_DMA_MEM_TO_DEV)
    {
        mc += pl330_cmd_dmamov(mc, PL330_DIR_SAR, dma_buf_addr);
        mc += pl330_cmd_dmamov(mc, PL330_DIR_DAR, conf->dst_addr);
    }
    else if (dir == RT_DMA_DEV_TO_MEM)
    {
        mc += pl330_cmd_dmamov(mc, PL330_DIR_SAR, conf->src_addr);
        mc += pl330_cmd_dmamov(mc, PL330_DIR_DAR, dma_buf_addr);
    }

    burst_bytes = conf->src_addr_width * conf->src_maxburst;
    if (!burst_bytes || !buf_len)
    {
        return -RT_EINVAL;
    }

    if (buf_len % burst_bytes)
    {
        return -RT_EINVAL;
    }

    loop = buf_len / burst_bytes;
    if (loop == 0 || loop > 255)
    {
        return -RT_EINVAL;
    }

    mc += pl330_cmd_dmalp(mc, 0 /* LC0 */, loop);
    rt_uint8_t ljmp = mc - pc->microcode;

    mc += pl330_cmd_dmald(mc, PL330_COND_ALWAYS);
    mc += pl330_cmd_dmast(mc, PL330_COND_ALWAYS);

    mc += pl330_cmd_dmalpend(mc,
            PL330_COND_ALWAYS,
            RT_FALSE,
            0, /* LC0 */
            mc - pc->microcode - ljmp);

    mc += pl330_cmd_dmasev(mc, pl330_chan_id(pl330, pc));

    mc += pl330_cmd_dmaend(mc);

    pc->microcode_len = mc - pc->microcode;
    pc->size = buf_len;

    return RT_EOK;
}

static const struct rt_dma_controller_ops pl330_dma_ops =
{
    .request_chan = pl330_dma_request_chan,
    .release_chan = pl330_dma_release_chan,
    .start = pl330_dma_start,
    .stop = pl330_dma_stop,
    .config = pl330_dma_config,
    .prep_memcpy = pl330_dma_prep_memcpy,
    .prep_cyclic = pl330_dma_prep_cyclic,
    .prep_single = pl330_dma_prep_single,
};

static void pl330_isr(int irqno, void *params)
{
    rt_uint32_t isr, csr;
    struct pl330_chan *pc;
    struct pl330 *pl330 = params;

    isr = HWREG32(pl330->regs + PL330_REG_INTMIS);

    for (int i = 0; i < pl330->num_chan; ++i)
    {
        if (!(isr & RT_BIT(i)))
        {
            continue;
        }

        pc = &pl330->chans[i];

        HWREG32(pl330->regs + PL330_REG_INTCLR) = RT_BIT(i);

        csr = HWREG32(pl330->regs + PL330_REG_CSR(i)) & 0xf;

        switch (csr)
        {
        case PL330_CS_CMPLT:
        case PL330_CS_STOP:
            rt_dma_chan_done(&pc->parent, pc->size);
            break;

        case PL330_CS_FAULT:
        case PL330_CS_FLTCMP:
            LOG_E("Channel[%d] fault", i);
            rt_dma_chan_done(&pc->parent, 0);
            break;

        default:
            LOG_E("Unhandle CSR = %x", csr);
            break;
        }
    }
}

static void pl330_free(struct pl330 *pl330)
{
    if (pl330->regs)
    {
        rt_iounmap(pl330->regs);
    }

    if (!rt_is_err_or_null(pl330->pclk))
    {
        rt_clk_disable_unprepare(pl330->pclk);
        rt_clk_put(pl330->pclk);
    }

    if (!rt_is_err_or_null(pl330->rstc))
    {
        rt_reset_control_assert(pl330->rstc);
        rt_reset_control_put(pl330->rstc);
    }

    if (!rt_is_err_or_null(pl330->rstc_ocp))
    {
        rt_reset_control_assert(pl330->rstc_ocp);
        rt_reset_control_put(pl330->rstc_ocp);
    }

    if (pl330->chans)
    {
        rt_free(pl330->chans);
    }

    rt_free(pl330);
}

static rt_err_t pl330_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    char isr_name[RT_NAME_MAX];
    struct rt_device *dev = &pdev->parent;
    struct pl330 *pl330 = rt_calloc(1, sizeof(*pl330));

    if (!pl330)
    {
        return -RT_ENOMEM;
    }

    pl330->regs = rt_dm_dev_iomap(dev, 0);

    if (!pl330->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    pl330->irqs_nr = rt_dm_dev_get_irq_count(dev);

    if (pl330->irqs_nr < 0)
    {
        err = pl330->irqs_nr;
        goto _fail;
    }
    else if (pl330->irqs_nr == 0)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    for (int i = 0; i < pl330->irqs_nr; ++i)
    {
        int irq = rt_dm_dev_get_irq(dev, i);

        if (irq < 0)
        {
            err = irq;
            goto _fail;
        }

        pl330->irqs[i] = irq;
    }

    pl330->pclk = rt_clk_get_by_name(dev, "apb_pclk");

    if (rt_is_err(pl330->pclk))
    {
        err = rt_ptr_err(pl330->pclk);
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(pl330->pclk)))
    {
        goto _fail;
    }

    pl330->rstc = rt_reset_control_get_by_name(dev, "dma");

    if (rt_is_err(pl330->rstc))
    {
        err = rt_ptr_err(pl330->rstc);
        goto _fail;
    }

    if (pl330->rstc && (err = rt_reset_control_deassert(pl330->rstc)))
    {
        goto _fail;
    }

    pl330->rstc_ocp = rt_reset_control_get_by_name(dev, "dma-ocp");

    if (rt_is_err(pl330->rstc_ocp))
    {
        err = rt_ptr_err(pl330->rstc_ocp);
        goto _fail;
    }

    if (pl330->rstc_ocp && (err = rt_reset_control_deassert(pl330->rstc_ocp)))
    {
        goto _fail;
    }

    if (rt_dm_dev_prop_read_bool(dev, "arm,pl330-broken-no-flushp"))
    {
        pl330->quirk |= PL330_QUIRK_BROKEN_NO_FLUSHP;
    }

    if (rt_dm_dev_prop_read_bool(dev, "arm,pl330-periph-burst"))
    {
        pl330->quirk |= PL330_QUIRK_PERIPH_BURST;
    }

    pl330_read_config(pl330);

    pl330->chans = rt_calloc(pl330->num_chan, sizeof(pl330->chans[0]));

    if (!pl330->chans)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    for (int i = 0; i < pl330->num_chan; ++i)
    {
        int offset = 0;
        struct pl330_chan *chan = &pl330->chans[i];

        chan->microcode_dma = (rt_ubase_t)rt_kmem_v2p(chan->microcode_raw);
        offset = RT_ALIGN(chan->microcode_dma, 4) - chan->microcode_dma;

        chan->microcode = chan->microcode_raw + offset;
        chan->microcode_dma += offset;
    }

    pl330->parent.dev = dev;
    pl330->parent.ops = &pl330_dma_ops;
    rt_dma_controller_add_direction(&pl330->parent, RT_DMA_MEM_TO_MEM);
    rt_dma_controller_add_direction(&pl330->parent, RT_DMA_MEM_TO_DEV);
    rt_dma_controller_add_direction(&pl330->parent, RT_DMA_DEV_TO_MEM);
    rt_dma_controller_set_addr_mask(&pl330->parent, RT_DMA_ADDR_MASK(32));

    if ((err = rt_dma_controller_register(&pl330->parent)))
    {
        goto _fail;
    }

    dev->user_data = pl330;

    for (int i = 0; i < pl330->irqs_nr; ++i)
    {
        rt_snprintf(isr_name, RT_NAME_MAX, "%s-%u", rt_dm_dev_get_name(dev), i);
        rt_hw_interrupt_install(pl330->irqs[i], pl330_isr, pl330, isr_name);
        rt_hw_interrupt_umask(pl330->irqs[i]);
    }

    return RT_EOK;

_fail:
    pl330_free(pl330);

    return err;
}

static rt_err_t pl330_remove(struct rt_platform_device *pdev)
{
    struct pl330 *pl330 = pdev->parent.user_data;

    for (int i = 0; i < pl330->irqs_nr; ++i)
    {
        rt_hw_interrupt_mask(pl330->irqs[i]);
        rt_pic_detach_irq(pl330->irqs[i], pl330);
    }

    rt_dma_controller_unregister(&pl330->parent);

    pl330_free(pl330);

    return RT_EOK;
}

static const struct rt_ofw_node_id pl330_ofw_ids[] =
{
    { .compatible = "arm,pl330" },
    { /* sentinel */ }
};

static struct rt_platform_driver pl330_driver =
{
    .name = "dma-pl330",
    .ids = pl330_ofw_ids,

    .probe = pl330_probe,
    .remove = pl330_remove,
};

static int pl330_drv_register(void)
{
    rt_platform_driver_register(&pl330_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(pl330_drv_register);
