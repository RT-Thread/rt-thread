/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-13     weety     first version
 */


#include <edma.h>

/* Offsets matching "struct edmacc_param" */
#define PARM_OPT        0x00
#define PARM_SRC        0x04
#define PARM_A_B_CNT        0x08
#define PARM_DST        0x0c
#define PARM_SRC_DST_BIDX   0x10
#define PARM_LINK_BCNTRLD   0x14
#define PARM_SRC_DST_CIDX   0x18
#define PARM_CCNT       0x1c

#define PARM_SIZE       0x20

/* Offsets for EDMA CC global channel registers and their shadows */
#define SH_ER       0x00    /* 64 bits */
#define SH_ECR      0x08    /* 64 bits */
#define SH_ESR      0x10    /* 64 bits */
#define SH_CER      0x18    /* 64 bits */
#define SH_EER      0x20    /* 64 bits */
#define SH_EECR     0x28    /* 64 bits */
#define SH_EESR     0x30    /* 64 bits */
#define SH_SER      0x38    /* 64 bits */
#define SH_SECR     0x40    /* 64 bits */
#define SH_IER      0x50    /* 64 bits */
#define SH_IECR     0x58    /* 64 bits */
#define SH_IESR     0x60    /* 64 bits */
#define SH_IPR      0x68    /* 64 bits */
#define SH_ICR      0x70    /* 64 bits */
#define SH_IEVAL    0x78
#define SH_QER      0x80
#define SH_QEER     0x84
#define SH_QEECR    0x88
#define SH_QEESR    0x8c
#define SH_QSER     0x90
#define SH_QSECR    0x94
#define SH_SIZE     0x200

/* Offsets for EDMA CC global registers */
#define EDMA_REV    0x0000
#define EDMA_CCCFG  0x0004
#define EDMA_QCHMAP 0x0200  /* 8 registers */
#define EDMA_DMAQNUM    0x0240  /* 8 registers (4 on OMAP-L1xx) */
#define EDMA_QDMAQNUM   0x0260
#define EDMA_QUETCMAP   0x0280
#define EDMA_QUEPRI 0x0284
#define EDMA_EMR    0x0300  /* 64 bits */
#define EDMA_EMCR   0x0308  /* 64 bits */
#define EDMA_QEMR   0x0310
#define EDMA_QEMCR  0x0314
#define EDMA_CCERR  0x0318
#define EDMA_CCERRCLR   0x031c
#define EDMA_EEVAL  0x0320
#define EDMA_DRAE   0x0340  /* 4 x 64 bits*/
#define EDMA_QRAE   0x0380  /* 4 registers */
#define EDMA_QUEEVTENTRY    0x0400  /* 2 x 16 registers */
#define EDMA_QSTAT  0x0600  /* 2 registers */
#define EDMA_QWMTHRA    0x0620
#define EDMA_QWMTHRB    0x0624
#define EDMA_CCSTAT 0x0640

#define EDMA_M      0x1000  /* global channel registers */
#define EDMA_ECR    0x1008
#define EDMA_ECRH   0x100C
#define EDMA_SHADOW0    0x2000  /* 4 regions shadowing global channels */
#define EDMA_PARM   0x4000  /* 128 param entries */

#define PARM_OFFSET(param_no)   (EDMA_PARM + ((param_no) << 5))

#define EDMA_DCHMAP 0x0100  /* 64 registers */
#define CHMAP_EXIST BIT(24)

#define EDMA_MAX_DMACH           64
#define EDMA_MAX_PARAMENTRY     512

#define EDMA_CC0_BASE_REG   0x01c00000
#define EDMA_TC0_BASE_REG   0x01c10000
#define EDMA_TC1_BASE_REG   0x01c10400
#define EDMA_TC2_BASE_REG   0x01c10800
#define EDMA_TC3_BASE_REG   0x01c10c00

#define min_t(type, x, y) ({            \
    type __min1 = (x);          \
    type __min2 = (y);          \
    __min1 < __min2 ? __min1: __min2; })



/*****************************************************************************/

static void volatile *edmacc_regs_base[EDMA_MAX_CC];

static inline unsigned int edma_read(unsigned ctlr, int offset)
{
    return (unsigned int)davinci_readl(edmacc_regs_base[ctlr] + offset);
}

static inline void edma_write(unsigned ctlr, int offset, int val)
{
    davinci_writel(val, edmacc_regs_base[ctlr] + offset);
}
static inline void edma_modify(unsigned ctlr, int offset, unsigned and,
        unsigned or)
{
    unsigned val = edma_read(ctlr, offset);
    val &= and;
    val |= or;
    edma_write(ctlr, offset, val);
}
static inline void edma_and(unsigned ctlr, int offset, unsigned and)
{
    unsigned val = edma_read(ctlr, offset);
    val &= and;
    edma_write(ctlr, offset, val);
}
static inline void edma_or(unsigned ctlr, int offset, unsigned or)
{
    unsigned val = edma_read(ctlr, offset);
    val |= or;
    edma_write(ctlr, offset, val);
}
static inline unsigned int edma_read_array(unsigned ctlr, int offset, int i)
{
    return edma_read(ctlr, offset + (i << 2));
}
static inline void edma_write_array(unsigned ctlr, int offset, int i,
        unsigned val)
{
    edma_write(ctlr, offset + (i << 2), val);
}
static inline void edma_modify_array(unsigned ctlr, int offset, int i,
        unsigned and, unsigned or)
{
    edma_modify(ctlr, offset + (i << 2), and, or);
}
static inline void edma_or_array(unsigned ctlr, int offset, int i, unsigned or)
{
    edma_or(ctlr, offset + (i << 2), or);
}
static inline void edma_or_array2(unsigned ctlr, int offset, int i, int j,
        unsigned or)
{
    edma_or(ctlr, offset + ((i*2 + j) << 2), or);
}
static inline void edma_write_array2(unsigned ctlr, int offset, int i, int j,
        unsigned val)
{
    edma_write(ctlr, offset + ((i*2 + j) << 2), val);
}
static inline unsigned int edma_shadow0_read(unsigned ctlr, int offset)
{
    return edma_read(ctlr, EDMA_SHADOW0 + offset);
}
static inline unsigned int edma_shadow0_read_array(unsigned ctlr, int offset,
        int i)
{
    return edma_read(ctlr, EDMA_SHADOW0 + offset + (i << 2));
}
static inline void edma_shadow0_write(unsigned ctlr, int offset, unsigned val)
{
    edma_write(ctlr, EDMA_SHADOW0 + offset, val);
}
static inline void edma_shadow0_write_array(unsigned ctlr, int offset, int i,
        unsigned val)
{
    edma_write(ctlr, EDMA_SHADOW0 + offset + (i << 2), val);
}
static inline unsigned int edma_parm_read(unsigned ctlr, int offset,
        int param_no)
{
    return edma_read(ctlr, EDMA_PARM + offset + (param_no << 5));
}
static inline void edma_parm_write(unsigned ctlr, int offset, int param_no,
        unsigned val)
{
    edma_write(ctlr, EDMA_PARM + offset + (param_no << 5), val);
}
static inline void edma_parm_modify(unsigned ctlr, int offset, int param_no,
        unsigned and, unsigned or)
{
    edma_modify(ctlr, EDMA_PARM + offset + (param_no << 5), and, or);
}
static inline void edma_parm_and(unsigned ctlr, int offset, int param_no,
        unsigned and)
{
    edma_and(ctlr, EDMA_PARM + offset + (param_no << 5), and);
}
static inline void edma_parm_or(unsigned ctlr, int offset, int param_no,
        unsigned or)
{
    edma_or(ctlr, EDMA_PARM + offset + (param_no << 5), or);
}
#if 0
static inline void set_bits(int offset, int len, unsigned long *p)
{
    for (; len > 0; len--)
        set_bit(offset + (len - 1), p);
}

static inline void clear_bits(int offset, int len, unsigned long *p)
{
    for (; len > 0; len--)
        clear_bit(offset + (len - 1), p);
}
#endif
/*****************************************************************************/

#define BIT(nr)         (1UL << (nr))
#define BITS_PER_LONG 32
#define BIT_MASK(nr)        (1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)        ((nr) / BITS_PER_LONG)
#define BITS_PER_BYTE       8
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

#define BITS_TO_LONGS(nr)   DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))

#define DECLARE_BITMAP(name,bits) \
    unsigned long name[BITS_TO_LONGS(bits)]

/**
 * test_bit - Determine whether a bit is set
 * @nr: bit number to test
 * @addr: Address to start counting from
 */
static inline int test_bit(int nr, const volatile unsigned long *addr)
{
    return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG-1)));
}

static inline void clear_bit(int nr, volatile unsigned long *addr)
{
    unsigned long mask = BIT_MASK(nr);
    unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    *p &= ~mask;
    rt_hw_interrupt_enable(level);
}

static inline int test_and_set_bit(int nr, volatile unsigned long *addr)
{
    unsigned long mask = BIT_MASK(nr);
    unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);
    unsigned long old;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    old = *p;
    *p = old | mask;
    rt_hw_interrupt_enable(level);

    return (old & mask) != 0;
}

static inline void set_bit(int nr, volatile unsigned long *addr)
{
    unsigned long mask = BIT_MASK(nr);
    unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    *p  |= mask;
    rt_hw_interrupt_enable(level);
}

/*
 * Little endian assembly bitops.  nr = 0 -> byte 0 bit 0.
 */
extern int _find_first_zero_bit_le(const void * p, unsigned size);
extern int _find_next_zero_bit_le(const void * p, int size, int offset);
extern int _find_first_bit_le(const unsigned long *p, unsigned size);
extern int _find_next_bit_le(const unsigned long *p, int size, int offset);

/*
 * These are the little endian, atomic definitions.
 */
#define find_first_zero_bit(p,sz)   _find_first_zero_bit_le(p,sz)
#define find_next_zero_bit(p,sz,off)    _find_next_zero_bit_le(p,sz,off)
#define find_first_bit(p,sz)        _find_first_bit_le(p,sz)
#define find_next_bit(p,sz,off)     _find_next_bit_le(p,sz,off)



/* actual number of DMA channels and slots on this silicon */
struct edma {
    /* how many dma resources of each type */
    unsigned    num_channels;
    unsigned    num_region;
    unsigned    num_slots;
    unsigned    num_tc;
    unsigned    num_cc;
    enum dma_event_q    default_queue;

    /* list of channels with no even trigger; terminated by "-1" */
    const rt_int8_t *noevent;

    /* The edma_inuse bit for each PaRAM slot is clear unless the
     * channel is in use ... by ARM or DSP, for QDMA, or whatever.
     */
    DECLARE_BITMAP(edma_inuse, EDMA_MAX_PARAMENTRY);

    /* The edma_unused bit for each channel is clear unless
     * it is not being used on this platform. It uses a bit
     * of SOC-specific initialization code.
     */
    DECLARE_BITMAP(edma_unused, EDMA_MAX_DMACH);

    unsigned    irq_res_start;
    unsigned    irq_res_end;

    struct dma_interrupt_data {
        void (*callback)(unsigned channel, unsigned short ch_status,
                void *data);
        void *data;
    } intr_data[EDMA_MAX_DMACH];
};

static struct edma *edma_cc[EDMA_MAX_CC];
static int arch_num_cc;

/* dummy param set used to (re)initialize parameter RAM slots */
static const struct edmacc_param dummy_paramset = {
    .link_bcntrld = 0xffff,
    .ccnt = 1,
};

/*****************************************************************************/

static void map_dmach_queue(unsigned ctlr, unsigned ch_no,
        enum dma_event_q queue_no)
{
    int bit = (ch_no & 0x7) * 4;

    /* default to low priority queue */
    if (queue_no == EVENTQ_DEFAULT)
        queue_no = edma_cc[ctlr]->default_queue;

    queue_no &= 7;
    edma_modify_array(ctlr, EDMA_DMAQNUM, (ch_no >> 3),
            ~(0x7 << bit), queue_no << bit);
}

static void map_queue_tc(unsigned ctlr, int queue_no, int tc_no)
{
    int bit = queue_no * 4;
    edma_modify(ctlr, EDMA_QUETCMAP, ~(0x7 << bit), ((tc_no & 0x7) << bit));
}

static void assign_priority_to_queue(unsigned ctlr, int queue_no,
        int priority)
{
    int bit = queue_no * 4;
    edma_modify(ctlr, EDMA_QUEPRI, ~(0x7 << bit),
            ((priority & 0x7) << bit));
}

/**
 * map_dmach_param - Maps channel number to param entry number
 *
 * This maps the dma channel number to param entry numberter. In
 * other words using the DMA channel mapping registers a param entry
 * can be mapped to any channel
 *
 * Callers are responsible for ensuring the channel mapping logic is
 * included in that particular EDMA variant (Eg : dm646x)
 *
 */
static void map_dmach_param(unsigned ctlr)
{
    int i;
    for (i = 0; i < EDMA_MAX_DMACH; i++)
        edma_write_array(ctlr, EDMA_DCHMAP , i , (i << 5));
}

static inline void
setup_dma_interrupt(unsigned lch,
    void (*callback)(unsigned channel, rt_uint16_t ch_status, void *data),
    void *data)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(lch);
    lch = EDMA_CHAN_SLOT(lch);

    if (!callback)
        edma_shadow0_write_array(ctlr, SH_IECR, lch >> 5,
                BIT(lch & 0x1f));

    edma_cc[ctlr]->intr_data[lch].callback = callback;
    edma_cc[ctlr]->intr_data[lch].data = data;

    if (callback) {
        edma_shadow0_write_array(ctlr, SH_ICR, lch >> 5,
                BIT(lch & 0x1f));
        edma_shadow0_write_array(ctlr, SH_IESR, lch >> 5,
                BIT(lch & 0x1f));
    }
}

static int irq2ctlr(int irq)
{
    if (irq >= edma_cc[0]->irq_res_start && irq <= edma_cc[0]->irq_res_end)
        return 0;
    else if (irq >= edma_cc[1]->irq_res_start &&
        irq <= edma_cc[1]->irq_res_end)
        return 1;

    return -1;
}

/******************************************************************************
 *
 * DMA interrupt handler
 *
 *****************************************************************************/
static void dma_irq_handler(int irq, void *data)
{
    int i;
    int ctlr;
    unsigned int cnt = 0;

    ctlr = irq2ctlr(irq);
    if (ctlr < 0)
        return ;

    edma_dbg("dma_irq_handler\n");

    if ((edma_shadow0_read_array(ctlr, SH_IPR, 0) == 0) &&
        (edma_shadow0_read_array(ctlr, SH_IPR, 1) == 0))
        return ;

    while (1) {
        int j;
        if (edma_shadow0_read_array(ctlr, SH_IPR, 0) &
                edma_shadow0_read_array(ctlr, SH_IER, 0))
            j = 0;
        else if (edma_shadow0_read_array(ctlr, SH_IPR, 1) &
                edma_shadow0_read_array(ctlr, SH_IER, 1))
            j = 1;
        else
            break;
        edma_dbg("IPR%d %08x\n", j,
                edma_shadow0_read_array(ctlr, SH_IPR, j));
        for (i = 0; i < 32; i++) {
            int k = (j << 5) + i;
            if ((edma_shadow0_read_array(ctlr, SH_IPR, j) & BIT(i))
                    && (edma_shadow0_read_array(ctlr,
                            SH_IER, j) & BIT(i))) {
                /* Clear the corresponding IPR bits */
                edma_shadow0_write_array(ctlr, SH_ICR, j,
                            BIT(i));
                if (edma_cc[ctlr]->intr_data[k].callback)
                    edma_cc[ctlr]->intr_data[k].callback(
                        k, DMA_COMPLETE,
                        edma_cc[ctlr]->intr_data[k].
                        data);
            }
        }
        cnt++;
        if (cnt > 10)
            break;
    }
    edma_shadow0_write(ctlr, SH_IEVAL, 1);
    return ;
}

/******************************************************************************
 *
 * DMA error interrupt handler
 *
 *****************************************************************************/
static void dma_ccerr_handler(int irq, void *data)
{
    int i;
    int ctlr;
    unsigned int cnt = 0;

    ctlr = irq2ctlr(irq);
    if (ctlr < 0)
        return ;

    edma_dbg("dma_ccerr_handler\n");

    if ((edma_read_array(ctlr, EDMA_EMR, 0) == 0) &&
        (edma_read_array(ctlr, EDMA_EMR, 1) == 0) &&
        (edma_read(ctlr, EDMA_QEMR) == 0) &&
        (edma_read(ctlr, EDMA_CCERR) == 0))
        return ;

    while (1) {
        int j = -1;
        if (edma_read_array(ctlr, EDMA_EMR, 0))
            j = 0;
        else if (edma_read_array(ctlr, EDMA_EMR, 1))
            j = 1;
        if (j >= 0) {
            edma_dbg("EMR%d %08x\n", j,
                    edma_read_array(ctlr, EDMA_EMR, j));
            for (i = 0; i < 32; i++) {
                int k = (j << 5) + i;
                if (edma_read_array(ctlr, EDMA_EMR, j) &
                            BIT(i)) {
                    /* Clear the corresponding EMR bits */
                    edma_write_array(ctlr, EDMA_EMCR, j,
                            BIT(i));
                    /* Clear any SER */
                    edma_shadow0_write_array(ctlr, SH_SECR,
                                j, BIT(i));
                    if (edma_cc[ctlr]->intr_data[k].
                                callback) {
                        edma_cc[ctlr]->intr_data[k].
                        callback(k,
                        DMA_CC_ERROR,
                        edma_cc[ctlr]->intr_data
                        [k].data);
                    }
                }
            }
        } else if (edma_read(ctlr, EDMA_QEMR)) {
            edma_dbg("QEMR %02x\n",
                edma_read(ctlr, EDMA_QEMR));
            for (i = 0; i < 8; i++) {
                if (edma_read(ctlr, EDMA_QEMR) & BIT(i)) {
                    /* Clear the corresponding IPR bits */
                    edma_write(ctlr, EDMA_QEMCR, BIT(i));
                    edma_shadow0_write(ctlr, SH_QSECR,
                                BIT(i));

                    /* NOTE:  not reported!! */
                }
            }
        } else if (edma_read(ctlr, EDMA_CCERR)) {
            edma_dbg("CCERR %08x\n",
                edma_read(ctlr, EDMA_CCERR));
            /* FIXME:  CCERR.BIT(16) ignored!  much better
             * to just write CCERRCLR with CCERR value...
             */
            for (i = 0; i < 8; i++) {
                if (edma_read(ctlr, EDMA_CCERR) & BIT(i)) {
                    /* Clear the corresponding IPR bits */
                    edma_write(ctlr, EDMA_CCERRCLR, BIT(i));

                    /* NOTE:  not reported!! */
                }
            }
        }
        if ((edma_read_array(ctlr, EDMA_EMR, 0) == 0) &&
            (edma_read_array(ctlr, EDMA_EMR, 1) == 0) &&
            (edma_read(ctlr, EDMA_QEMR) == 0) &&
            (edma_read(ctlr, EDMA_CCERR) == 0))
            break;
        cnt++;
        if (cnt > 10)
            break;
    }
    edma_write(ctlr, EDMA_EEVAL, 1);
    return ;
}

/******************************************************************************
 *
 * Transfer controller error interrupt handlers
 *
 *****************************************************************************/

#define tc_errs_handled RT_FALSE/* disabled as long as they're NOPs */

static void dma_tc0err_handler(int irq, void *data)
{
    edma_dbg("dma_tc0err_handler\n");
    return ;
}

static void dma_tc1err_handler(int irq, void *data)
{
    edma_dbg("dma_tc1err_handler\n");
    return ;
}

static int reserve_contiguous_slots(int ctlr, unsigned int id,
                     unsigned int num_slots,
                     unsigned int start_slot)
{
    int i, j;
    unsigned int count = num_slots;
    int stop_slot = start_slot;
    DECLARE_BITMAP(tmp_inuse, EDMA_MAX_PARAMENTRY);

    for (i = start_slot; i < edma_cc[ctlr]->num_slots; ++i) {
        j = EDMA_CHAN_SLOT(i);
        if (!test_and_set_bit(j, edma_cc[ctlr]->edma_inuse)) {
            /* Record our current beginning slot */
            if (count == num_slots)
                stop_slot = i;

            count--;
            set_bit(j, tmp_inuse);

            if (count == 0)
                break;
        } else {
            clear_bit(j, tmp_inuse);

            if (id == EDMA_CONT_PARAMS_FIXED_EXACT) {
                stop_slot = i;
                break;
            } else {
                count = num_slots;
            }
        }
    }

    /*
     * We have to clear any bits that we set
     * if we run out parameter RAM slots, i.e we do find a set
     * of contiguous parameter RAM slots but do not find the exact number
     * requested as we may reach the total number of parameter RAM slots
     */
    if (i == edma_cc[ctlr]->num_slots)
        stop_slot = i;

    for (j = start_slot; j < stop_slot; j++)
        if (test_bit(j, tmp_inuse))
            clear_bit(j, edma_cc[ctlr]->edma_inuse);

    if (count)
        return -RT_EBUSY;

    for (j = i - num_slots + 1; j <= i; ++j)
        rt_memcpy((void *)(edmacc_regs_base[ctlr] + PARM_OFFSET(j)),
            &dummy_paramset, PARM_SIZE);

    return EDMA_CTLR_CHAN(ctlr, i - num_slots + 1);
}

#if 0
static int prepare_unused_channel_list(struct device *dev, void *data)
{
    struct platform_device *pdev = to_platform_device(dev);
    int i, ctlr;

    for (i = 0; i < pdev->num_resources; i++) {
        if ((pdev->resource[i].flags & IORESOURCE_DMA) &&
                (int)pdev->resource[i].start >= 0) {
            ctlr = EDMA_CTLR(pdev->resource[i].start);
            clear_bit(EDMA_CHAN_SLOT(pdev->resource[i].start),
                    edma_cc[ctlr]->edma_unused);
        }
    }

    return 0;
}
#endif

/*-----------------------------------------------------------------------*/

static rt_bool_t unused_chan_list_done;

/* Resource alloc/free:  dma channels, parameter RAM slots */

/**
 * edma_alloc_channel - allocate DMA channel and paired parameter RAM
 * @channel: specific channel to allocate; negative for "any unmapped channel"
 * @callback: optional; to be issued on DMA completion or errors
 * @data: passed to callback
 * @eventq_no: an EVENTQ_* constant, used to choose which Transfer
 *  Controller (TC) executes requests using this channel.  Use
 *  EVENTQ_DEFAULT unless you really need a high priority queue.
 *
 * This allocates a DMA channel and its associated parameter RAM slot.
 * The parameter RAM is initialized to hold a dummy transfer.
 *
 * Normal use is to pass a specific channel number as @channel, to make
 * use of hardware events mapped to that channel.  When the channel will
 * be used only for software triggering or event chaining, channels not
 * mapped to hardware events (or mapped to unused events) are preferable.
 *
 * DMA transfers start from a channel using edma_start(), or by
 * chaining.  When the transfer described in that channel's parameter RAM
 * slot completes, that slot's data may be reloaded through a link.
 *
 * DMA errors are only reported to the @callback associated with the
 * channel driving that transfer, but transfer completion callbacks can
 * be sent to another channel under control of the TCC field in
 * the option word of the transfer's parameter RAM set.  Drivers must not
 * use DMA transfer completion callbacks for channels they did not allocate.
 * (The same applies to TCC codes used in transfer chaining.)
 *
 * Returns the number of the channel, else negative errno.
 */
int edma_alloc_channel(int channel,
        void (*callback)(unsigned channel, rt_uint16_t ch_status, void *data),
        void *data,
        enum dma_event_q eventq_no)
{
    unsigned i, done = 0, ctlr = 0;
    int ret = 0;
#if 0
    if (!unused_chan_list_done) {
        /*
         * Scan all the platform devices to find out the EDMA channels
         * used and clear them in the unused list, making the rest
         * available for ARM usage.
         */
        ret = bus_for_each_dev(&platform_bus_type, NULL, NULL,
                prepare_unused_channel_list);
        if (ret < 0)
            return ret;

        unused_chan_list_done = true;
    }
#endif

    if (channel >= 0) {
        ctlr = EDMA_CTLR(channel);
        channel = EDMA_CHAN_SLOT(channel);
        clear_bit(channel, edma_cc[ctlr]->edma_unused);
    }

    if (channel < 0) {
        for (i = 0; i < arch_num_cc; i++) {
            channel = 0;
            for (;;) {
                channel = find_next_bit(edma_cc[i]->edma_unused,
                        edma_cc[i]->num_channels,
                        channel);
                if (channel == edma_cc[i]->num_channels)
                    break;
                if (!test_and_set_bit(channel,
                        edma_cc[i]->edma_inuse)) {
                    done = 1;
                    ctlr = i;
                    break;
                }
                channel++;
            }
            if (done)
                break;
        }
        if (!done)
            return -RT_ENOMEM;
    } else if (channel >= edma_cc[ctlr]->num_channels) {
        return -RT_ERROR;
    } else if (test_and_set_bit(channel, edma_cc[ctlr]->edma_inuse)) {
        return -RT_EBUSY;
    }

    /* ensure access through shadow region 0 */
    edma_or_array2(ctlr, EDMA_DRAE, 0, channel >> 5, BIT(channel & 0x1f));

    /* ensure no events are pending */
    edma_stop(EDMA_CTLR_CHAN(ctlr, channel));
    rt_memcpy((void *)(edmacc_regs_base[ctlr] + PARM_OFFSET(channel)),
            &dummy_paramset, PARM_SIZE);

    if (callback)
        setup_dma_interrupt(EDMA_CTLR_CHAN(ctlr, channel),
                    callback, data);

    map_dmach_queue(ctlr, channel, eventq_no);

    return EDMA_CTLR_CHAN(ctlr, channel);
}


/**
 * edma_free_channel - deallocate DMA channel
 * @channel: dma channel returned from edma_alloc_channel()
 *
 * This deallocates the DMA channel and associated parameter RAM slot
 * allocated by edma_alloc_channel().
 *
 * Callers are responsible for ensuring the channel is inactive, and
 * will not be reactivated by linking, chaining, or software calls to
 * edma_start().
 */
void edma_free_channel(unsigned channel)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(channel);
    channel = EDMA_CHAN_SLOT(channel);

    if (channel >= edma_cc[ctlr]->num_channels)
        return;

    setup_dma_interrupt(channel, RT_NULL, RT_NULL);
    /* REVISIT should probably take out of shadow region 0 */

    rt_memcpy((void *)(edmacc_regs_base[ctlr] + PARM_OFFSET(channel)),
            &dummy_paramset, PARM_SIZE);
    clear_bit(channel, edma_cc[ctlr]->edma_inuse);
}


/**
 * edma_alloc_slot - allocate DMA parameter RAM
 * @slot: specific slot to allocate; negative for "any unused slot"
 *
 * This allocates a parameter RAM slot, initializing it to hold a
 * dummy transfer.  Slots allocated using this routine have not been
 * mapped to a hardware DMA channel, and will normally be used by
 * linking to them from a slot associated with a DMA channel.
 *
 * Normal use is to pass EDMA_SLOT_ANY as the @slot, but specific
 * slots may be allocated on behalf of DSP firmware.
 *
 * Returns the number of the slot, else negative errno.
 */
int edma_alloc_slot(unsigned ctlr, int slot)
{
    if (slot >= 0)
        slot = EDMA_CHAN_SLOT(slot);

    if (slot < 0) {
        slot = edma_cc[ctlr]->num_channels;
        for (;;) {
            slot = find_next_zero_bit(edma_cc[ctlr]->edma_inuse,
                    edma_cc[ctlr]->num_slots, slot);
            if (slot == edma_cc[ctlr]->num_slots)
                return -RT_ENOMEM;
            if (!test_and_set_bit(slot, edma_cc[ctlr]->edma_inuse))
                break;
        }
    } else if (slot < edma_cc[ctlr]->num_channels ||
            slot >= edma_cc[ctlr]->num_slots) {
        return -RT_ERROR;
    } else if (test_and_set_bit(slot, edma_cc[ctlr]->edma_inuse)) {
        return -RT_EBUSY;
    }

    rt_memcpy((void *)(edmacc_regs_base[ctlr] + PARM_OFFSET(slot)),
            &dummy_paramset, PARM_SIZE);

    return EDMA_CTLR_CHAN(ctlr, slot);
}


/**
 * edma_free_slot - deallocate DMA parameter RAM
 * @slot: parameter RAM slot returned from edma_alloc_slot()
 *
 * This deallocates the parameter RAM slot allocated by edma_alloc_slot().
 * Callers are responsible for ensuring the slot is inactive, and will
 * not be activated.
 */
void edma_free_slot(unsigned slot)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(slot);
    slot = EDMA_CHAN_SLOT(slot);

    if (slot < edma_cc[ctlr]->num_channels ||
        slot >= edma_cc[ctlr]->num_slots)
        return;

    rt_memcpy((void *)(edmacc_regs_base[ctlr] + PARM_OFFSET(slot)),
            &dummy_paramset, PARM_SIZE);
    clear_bit(slot, edma_cc[ctlr]->edma_inuse);
}



/**
 * edma_alloc_cont_slots- alloc contiguous parameter RAM slots
 * The API will return the starting point of a set of
 * contiguous parameter RAM slots that have been requested
 *
 * @id: can only be EDMA_CONT_PARAMS_ANY or EDMA_CONT_PARAMS_FIXED_EXACT
 * or EDMA_CONT_PARAMS_FIXED_NOT_EXACT
 * @count: number of contiguous Paramter RAM slots
 * @slot  - the start value of Parameter RAM slot that should be passed if id
 * is EDMA_CONT_PARAMS_FIXED_EXACT or EDMA_CONT_PARAMS_FIXED_NOT_EXACT
 *
 * If id is EDMA_CONT_PARAMS_ANY then the API starts looking for a set of
 * contiguous Parameter RAM slots from parameter RAM 64 in the case of
 * DaVinci SOCs and 32 in the case of DA8xx SOCs.
 *
 * If id is EDMA_CONT_PARAMS_FIXED_EXACT then the API starts looking for a
 * set of contiguous parameter RAM slots from the "slot" that is passed as an
 * argument to the API.
 *
 * If id is EDMA_CONT_PARAMS_FIXED_NOT_EXACT then the API initially tries
 * starts looking for a set of contiguous parameter RAMs from the "slot"
 * that is passed as an argument to the API. On failure the API will try to
 * find a set of contiguous Parameter RAM slots from the remaining Parameter
 * RAM slots
 */
int edma_alloc_cont_slots(unsigned ctlr, unsigned int id, int slot, int count)
{
    /*
     * The start slot requested should be greater than
     * the number of channels and lesser than the total number
     * of slots
     */
    if ((id != EDMA_CONT_PARAMS_ANY) &&
        (slot < edma_cc[ctlr]->num_channels ||
        slot >= edma_cc[ctlr]->num_slots))
        return -RT_ERROR;

    /*
     * The number of parameter RAM slots requested cannot be less than 1
     * and cannot be more than the number of slots minus the number of
     * channels
     */
    if (count < 1 || count >
        (edma_cc[ctlr]->num_slots - edma_cc[ctlr]->num_channels))
        return -RT_ERROR;

    switch (id) {
    case EDMA_CONT_PARAMS_ANY:
        return reserve_contiguous_slots(ctlr, id, count,
                         edma_cc[ctlr]->num_channels);
    case EDMA_CONT_PARAMS_FIXED_EXACT:
    case EDMA_CONT_PARAMS_FIXED_NOT_EXACT:
        return reserve_contiguous_slots(ctlr, id, count, slot);
    default:
        return -RT_ERROR;
    }

}


/**
 * edma_free_cont_slots - deallocate DMA parameter RAM slots
 * @slot: first parameter RAM of a set of parameter RAM slots to be freed
 * @count: the number of contiguous parameter RAM slots to be freed
 *
 * This deallocates the parameter RAM slots allocated by
 * edma_alloc_cont_slots.
 * Callers/applications need to keep track of sets of contiguous
 * parameter RAM slots that have been allocated using the edma_alloc_cont_slots
 * API.
 * Callers are responsible for ensuring the slots are inactive, and will
 * not be activated.
 */
int edma_free_cont_slots(unsigned slot, int count)
{
    unsigned ctlr, slot_to_free;
    int i;

    ctlr = EDMA_CTLR(slot);
    slot = EDMA_CHAN_SLOT(slot);

    if (slot < edma_cc[ctlr]->num_channels ||
        slot >= edma_cc[ctlr]->num_slots ||
        count < 1)
        return -RT_ERROR;

    for (i = slot; i < slot + count; ++i) {
        ctlr = EDMA_CTLR(i);
        slot_to_free = EDMA_CHAN_SLOT(i);

        rt_memcpy((void *)(edmacc_regs_base[ctlr] + PARM_OFFSET(slot_to_free)),
            &dummy_paramset, PARM_SIZE);
        clear_bit(slot_to_free, edma_cc[ctlr]->edma_inuse);
    }

    return 0;
}


/*-----------------------------------------------------------------------*/

/* Parameter RAM operations (i) -- read/write partial slots */

/**
 * edma_set_src - set initial DMA source address in parameter RAM slot
 * @slot: parameter RAM slot being configured
 * @src_port: physical address of source (memory, controller FIFO, etc)
 * @addressMode: INCR, except in very rare cases
 * @fifoWidth: ignored unless @addressMode is FIFO, else specifies the
 *  width to use when addressing the fifo (e.g. W8BIT, W32BIT)
 *
 * Note that the source address is modified during the DMA transfer
 * according to edma_set_src_index().
 */
void edma_set_src(unsigned slot, rt_uint32_t src_port,
                enum address_mode mode, enum fifo_width width)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(slot);
    slot = EDMA_CHAN_SLOT(slot);

    if (slot < edma_cc[ctlr]->num_slots) {
        unsigned int i = edma_parm_read(ctlr, PARM_OPT, slot);

        if (mode) {
            /* set SAM and program FWID */
            i = (i & ~(EDMA_FWID)) | (SAM | ((width & 0x7) << 8));
        } else {
            /* clear SAM */
            i &= ~SAM;
        }
        edma_parm_write(ctlr, PARM_OPT, slot, i);

        /* set the source port address
           in source register of param structure */
        edma_parm_write(ctlr, PARM_SRC, slot, src_port);
    }
}


/**
 * edma_set_dest - set initial DMA destination address in parameter RAM slot
 * @slot: parameter RAM slot being configured
 * @dest_port: physical address of destination (memory, controller FIFO, etc)
 * @addressMode: INCR, except in very rare cases
 * @fifoWidth: ignored unless @addressMode is FIFO, else specifies the
 *  width to use when addressing the fifo (e.g. W8BIT, W32BIT)
 *
 * Note that the destination address is modified during the DMA transfer
 * according to edma_set_dest_index().
 */
void edma_set_dest(unsigned slot, rt_uint32_t dest_port,
                 enum address_mode mode, enum fifo_width width)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(slot);
    slot = EDMA_CHAN_SLOT(slot);

    if (slot < edma_cc[ctlr]->num_slots) {
        unsigned int i = edma_parm_read(ctlr, PARM_OPT, slot);

        if (mode) {
            /* set DAM and program FWID */
            i = (i & ~(EDMA_FWID)) | (DAM | ((width & 0x7) << 8));
        } else {
            /* clear DAM */
            i &= ~DAM;
        }
        edma_parm_write(ctlr, PARM_OPT, slot, i);
        /* set the destination port address
           in dest register of param structure */
        edma_parm_write(ctlr, PARM_DST, slot, dest_port);
    }
}


/**
 * edma_get_position - returns the current transfer points
 * @slot: parameter RAM slot being examined
 * @src: pointer to source port position
 * @dst: pointer to destination port position
 *
 * Returns current source and destination addresses for a particular
 * parameter RAM slot.  Its channel should not be active when this is called.
 */
void edma_get_position(unsigned slot, rt_uint32_t *src, rt_uint32_t *dst)
{
    struct edmacc_param temp;
    unsigned ctlr;

    ctlr = EDMA_CTLR(slot);
    slot = EDMA_CHAN_SLOT(slot);

    edma_read_slot(EDMA_CTLR_CHAN(ctlr, slot), &temp);
    if (src != RT_NULL)
        *src = temp.src;
    if (dst != RT_NULL)
        *dst = temp.dst;
}


/**
 * edma_set_src_index - configure DMA source address indexing
 * @slot: parameter RAM slot being configured
 * @src_bidx: byte offset between source arrays in a frame
 * @src_cidx: byte offset between source frames in a block
 *
 * Offsets are specified to support either contiguous or discontiguous
 * memory transfers, or repeated access to a hardware register, as needed.
 * When accessing hardware registers, both offsets are normally zero.
 */
void edma_set_src_index(unsigned slot, rt_int16_t src_bidx, rt_int16_t src_cidx)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(slot);
    slot = EDMA_CHAN_SLOT(slot);

    if (slot < edma_cc[ctlr]->num_slots) {
        edma_parm_modify(ctlr, PARM_SRC_DST_BIDX, slot,
                0xffff0000, src_bidx);
        edma_parm_modify(ctlr, PARM_SRC_DST_CIDX, slot,
                0xffff0000, src_cidx);
    }
}


/**
 * edma_set_dest_index - configure DMA destination address indexing
 * @slot: parameter RAM slot being configured
 * @dest_bidx: byte offset between destination arrays in a frame
 * @dest_cidx: byte offset between destination frames in a block
 *
 * Offsets are specified to support either contiguous or discontiguous
 * memory transfers, or repeated access to a hardware register, as needed.
 * When accessing hardware registers, both offsets are normally zero.
 */
void edma_set_dest_index(unsigned slot, rt_int16_t dest_bidx, rt_int16_t dest_cidx)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(slot);
    slot = EDMA_CHAN_SLOT(slot);

    if (slot < edma_cc[ctlr]->num_slots) {
        edma_parm_modify(ctlr, PARM_SRC_DST_BIDX, slot,
                0x0000ffff, dest_bidx << 16);
        edma_parm_modify(ctlr, PARM_SRC_DST_CIDX, slot,
                0x0000ffff, dest_cidx << 16);
    }
}


/**
 * edma_set_transfer_params - configure DMA transfer parameters
 * @slot: parameter RAM slot being configured
 * @acnt: how many bytes per array (at least one)
 * @bcnt: how many arrays per frame (at least one)
 * @ccnt: how many frames per block (at least one)
 * @bcnt_rld: used only for A-Synchronized transfers; this specifies
 *  the value to reload into bcnt when it decrements to zero
 * @sync_mode: ASYNC or ABSYNC
 *
 * See the EDMA3 documentation to understand how to configure and link
 * transfers using the fields in PaRAM slots.  If you are not doing it
 * all at once with edma_write_slot(), you will use this routine
 * plus two calls each for source and destination, setting the initial
 * address and saying how to index that address.
 *
 * An example of an A-Synchronized transfer is a serial link using a
 * single word shift register.  In that case, @acnt would be equal to
 * that word size; the serial controller issues a DMA synchronization
 * event to transfer each word, and memory access by the DMA transfer
 * controller will be word-at-a-time.
 *
 * An example of an AB-Synchronized transfer is a device using a FIFO.
 * In that case, @acnt equals the FIFO width and @bcnt equals its depth.
 * The controller with the FIFO issues DMA synchronization events when
 * the FIFO threshold is reached, and the DMA transfer controller will
 * transfer one frame to (or from) the FIFO.  It will probably use
 * efficient burst modes to access memory.
 */
void edma_set_transfer_params(unsigned slot,
        rt_uint16_t acnt, rt_uint16_t bcnt, rt_uint16_t ccnt,
        rt_uint16_t bcnt_rld, enum sync_dimension sync_mode)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(slot);
    slot = EDMA_CHAN_SLOT(slot);

    if (slot < edma_cc[ctlr]->num_slots) {
        edma_parm_modify(ctlr, PARM_LINK_BCNTRLD, slot,
                0x0000ffff, bcnt_rld << 16);
        if (sync_mode == ASYNC)
            edma_parm_and(ctlr, PARM_OPT, slot, ~SYNCDIM);
        else
            edma_parm_or(ctlr, PARM_OPT, slot, SYNCDIM);
        /* Set the acount, bcount, ccount registers */
        edma_parm_write(ctlr, PARM_A_B_CNT, slot, (bcnt << 16) | acnt);
        edma_parm_write(ctlr, PARM_CCNT, slot, ccnt);
    }
}


/**
 * edma_link - link one parameter RAM slot to another
 * @from: parameter RAM slot originating the link
 * @to: parameter RAM slot which is the link target
 *
 * The originating slot should not be part of any active DMA transfer.
 */
void edma_link(unsigned from, unsigned to)
{
    unsigned ctlr_from, ctlr_to;

    ctlr_from = EDMA_CTLR(from);
    from = EDMA_CHAN_SLOT(from);
    ctlr_to = EDMA_CTLR(to);
    to = EDMA_CHAN_SLOT(to);

    if (from >= edma_cc[ctlr_from]->num_slots)
        return;
    if (to >= edma_cc[ctlr_to]->num_slots)
        return;
    edma_parm_modify(ctlr_from, PARM_LINK_BCNTRLD, from, 0xffff0000,
                PARM_OFFSET(to));
}


/**
 * edma_unlink - cut link from one parameter RAM slot
 * @from: parameter RAM slot originating the link
 *
 * The originating slot should not be part of any active DMA transfer.
 * Its link is set to 0xffff.
 */
void edma_unlink(unsigned from)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(from);
    from = EDMA_CHAN_SLOT(from);

    if (from >= edma_cc[ctlr]->num_slots)
        return;
    edma_parm_or(ctlr, PARM_LINK_BCNTRLD, from, 0xffff);
}


/*-----------------------------------------------------------------------*/

/* Parameter RAM operations (ii) -- read/write whole parameter sets */

/**
 * edma_write_slot - write parameter RAM data for slot
 * @slot: number of parameter RAM slot being modified
 * @param: data to be written into parameter RAM slot
 *
 * Use this to assign all parameters of a transfer at once.  This
 * allows more efficient setup of transfers than issuing multiple
 * calls to set up those parameters in small pieces, and provides
 * complete control over all transfer options.
 */
void edma_write_slot(unsigned slot, const struct edmacc_param *param)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(slot);
    slot = EDMA_CHAN_SLOT(slot);

    if (slot >= edma_cc[ctlr]->num_slots)
        return;
    rt_memcpy((void *)(edmacc_regs_base[ctlr] + PARM_OFFSET(slot)), param,
            PARM_SIZE);
}


/**
 * edma_read_slot - read parameter RAM data from slot
 * @slot: number of parameter RAM slot being copied
 * @param: where to store copy of parameter RAM data
 *
 * Use this to read data from a parameter RAM slot, perhaps to
 * save them as a template for later reuse.
 */
void edma_read_slot(unsigned slot, struct edmacc_param *param)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(slot);
    slot = EDMA_CHAN_SLOT(slot);

    if (slot >= edma_cc[ctlr]->num_slots)
        return;
    rt_memcpy(param, (void *)(edmacc_regs_base[ctlr] + PARM_OFFSET(slot)),
            PARM_SIZE);
}


/*-----------------------------------------------------------------------*/

/* Various EDMA channel control operations */

/**
 * edma_pause - pause dma on a channel
 * @channel: on which edma_start() has been called
 *
 * This temporarily disables EDMA hardware events on the specified channel,
 * preventing them from triggering new transfers on its behalf
 */
void edma_pause(unsigned channel)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(channel);
    channel = EDMA_CHAN_SLOT(channel);

    if (channel < edma_cc[ctlr]->num_channels) {
        unsigned int mask = BIT(channel & 0x1f);

        edma_shadow0_write_array(ctlr, SH_EECR, channel >> 5, mask);
    }
}


/**
 * edma_resume - resumes dma on a paused channel
 * @channel: on which edma_pause() has been called
 *
 * This re-enables EDMA hardware events on the specified channel.
 */
void edma_resume(unsigned channel)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(channel);
    channel = EDMA_CHAN_SLOT(channel);

    if (channel < edma_cc[ctlr]->num_channels) {
        unsigned int mask = BIT(channel & 0x1f);

        edma_shadow0_write_array(ctlr, SH_EESR, channel >> 5, mask);
    }
}


/**
 * edma_start - start dma on a channel
 * @channel: channel being activated
 *
 * Channels with event associations will be triggered by their hardware
 * events, and channels without such associations will be triggered by
 * software.  (At this writing there is no interface for using software
 * triggers except with channels that don't support hardware triggers.)
 *
 * Returns zero on success, else negative errno.
 */
int edma_start(unsigned channel)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(channel);
    channel = EDMA_CHAN_SLOT(channel);

    if (channel < edma_cc[ctlr]->num_channels) {
        int j = channel >> 5;
        unsigned int mask = BIT(channel & 0x1f);

        /* EDMA channels without event association */
        if (test_bit(channel, edma_cc[ctlr]->edma_unused)) {
            edma_dbg("EDMA: ESR%d %08x\n", j,
                edma_shadow0_read_array(ctlr, SH_ESR, j));
            edma_shadow0_write_array(ctlr, SH_ESR, j, mask);
            return 0;
        }

        /* EDMA channel with event association */
        edma_dbg("EDMA: ER%d %08x\n", j,
            edma_shadow0_read_array(ctlr, SH_ER, j));
        /* Clear any pending event or error */
        edma_write_array(ctlr, EDMA_ECR, j, mask);
        edma_write_array(ctlr, EDMA_EMCR, j, mask);
        /* Clear any SER */
        edma_shadow0_write_array(ctlr, SH_SECR, j, mask);
        edma_shadow0_write_array(ctlr, SH_EESR, j, mask);
        edma_dbg("EDMA: EER%d %08x\n", j,
            edma_shadow0_read_array(ctlr, SH_EER, j));
        return 0;
    }

    return -RT_ERROR;
}


/**
 * edma_stop - stops dma on the channel passed
 * @channel: channel being deactivated
 *
 * When @lch is a channel, any active transfer is paused and
 * all pending hardware events are cleared.  The current transfer
 * may not be resumed, and the channel's Parameter RAM should be
 * reinitialized before being reused.
 */
void edma_stop(unsigned channel)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(channel);
    channel = EDMA_CHAN_SLOT(channel);

    if (channel < edma_cc[ctlr]->num_channels) {
        int j = channel >> 5;
        unsigned int mask = BIT(channel & 0x1f);

        edma_shadow0_write_array(ctlr, SH_EECR, j, mask);
        edma_shadow0_write_array(ctlr, SH_ECR, j, mask);
        edma_shadow0_write_array(ctlr, SH_SECR, j, mask);
        edma_write_array(ctlr, EDMA_EMCR, j, mask);

        edma_dbg("EDMA: EER%d %08x\n", j,
                edma_shadow0_read_array(ctlr, SH_EER, j));

        /* REVISIT:  consider guarding against inappropriate event
         * chaining by overwriting with dummy_paramset.
         */
    }
}


/******************************************************************************
 *
 * It cleans ParamEntry qand bring back EDMA to initial state if media has
 * been removed before EDMA has finished.It is usedful for removable media.
 * Arguments:
 *      ch_no     - channel no
 *
 * Return: zero on success, or corresponding error no on failure
 *
 * FIXME this should not be needed ... edma_stop() should suffice.
 *
 *****************************************************************************/

void edma_clean_channel(unsigned channel)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(channel);
    channel = EDMA_CHAN_SLOT(channel);

    if (channel < edma_cc[ctlr]->num_channels) {
        int j = (channel >> 5);
        unsigned int mask = BIT(channel & 0x1f);

        edma_dbg("EDMA: EMR%d %08x\n", j,
                edma_read_array(ctlr, EDMA_EMR, j));
        edma_shadow0_write_array(ctlr, SH_ECR, j, mask);
        /* Clear the corresponding EMR bits */
        edma_write_array(ctlr, EDMA_EMCR, j, mask);
        /* Clear any SER */
        edma_shadow0_write_array(ctlr, SH_SECR, j, mask);
        edma_write(ctlr, EDMA_CCERRCLR, BIT(16) | BIT(1) | BIT(0));
    }
}


/*
 * edma_clear_event - clear an outstanding event on the DMA channel
 * Arguments:
 *  channel - channel number
 */
void edma_clear_event(unsigned channel)
{
    unsigned ctlr;

    ctlr = EDMA_CTLR(channel);
    channel = EDMA_CHAN_SLOT(channel);

    if (channel >= edma_cc[ctlr]->num_channels)
        return;
    if (channel < 32)
        edma_write(ctlr, EDMA_ECR, BIT(channel));
    else
        edma_write(ctlr, EDMA_ECRH, BIT(channel - 32));
}


/*-----------------------------------------------------------------------*/

int edma_init(struct edma_soc_info **info)
{
    //struct edma_soc_info  **info = pdev->dev.platform_data;
    const rt_int8_t     (*queue_priority_mapping)[2];
    const rt_int8_t     (*queue_tc_mapping)[2];
    int         i, j, off, ln, found = 0;
    int         status = -1;
    const rt_int16_t        (*rsv_chans)[2];
    const rt_int16_t        (*rsv_slots)[2];
    int         irq[EDMA_MAX_CC] = {0, 0};
    int         err_irq[EDMA_MAX_CC] = {0, 0};

    RT_ASSERT(info != RT_NULL);

    psc_change_state(DAVINCI_DM365_LPSC_TPCC, PSC_ENABLE);
    psc_change_state(DAVINCI_DM365_LPSC_TPTC0, PSC_ENABLE);
    psc_change_state(DAVINCI_DM365_LPSC_TPTC1, PSC_ENABLE);
    psc_change_state(DAVINCI_DM365_LPSC_TPTC2, PSC_ENABLE);
    psc_change_state(DAVINCI_DM365_LPSC_TPTC3, PSC_ENABLE);

    edmacc_regs_base[0] = (void *)EDMA_CC0_BASE_REG;

    edma_cc[0] = rt_malloc(sizeof(struct edma));
    if (!edma_cc[0]) {
        status = -RT_ENOMEM;
        goto fail1;
    }
    rt_memset(edma_cc[0], 0, sizeof(struct edma));

    edma_cc[0]->num_channels = min_t(unsigned, info[0]->n_channel,
                        EDMA_MAX_DMACH);
    edma_cc[0]->num_slots = min_t(unsigned, info[0]->n_slot,
                        EDMA_MAX_PARAMENTRY);
    edma_cc[0]->num_cc = min_t(unsigned, info[0]->n_cc,
                        EDMA_MAX_CC);

    edma_cc[0]->default_queue = info[0]->default_queue;
    if (!edma_cc[0]->default_queue)
        edma_cc[0]->default_queue = EVENTQ_1;

    edma_dbg("DMA REG BASE ADDR=%p\n",
        edmacc_regs_base[j]);

    for (i = 0; i < edma_cc[0]->num_slots; i++)
        rt_memcpy((void *)(edmacc_regs_base[0] + PARM_OFFSET(i)),
                &dummy_paramset, PARM_SIZE);

    /* Mark all channels as unused */
    rt_memset(edma_cc[0]->edma_unused, 0xff,
        sizeof(edma_cc[0]->edma_unused));

    edma_cc[0]->irq_res_start = IRQ_CCINT0;
    rt_hw_interrupt_install(IRQ_CCINT0, dma_irq_handler, RT_NULL, "edma");
    rt_hw_interrupt_umask(IRQ_CCINT0);

    edma_cc[0]->irq_res_end = IRQ_CCERRINT;
    rt_hw_interrupt_install(IRQ_CCERRINT, dma_ccerr_handler, RT_NULL, "edma_error");
    rt_hw_interrupt_umask(IRQ_CCERRINT);

    /* Everything lives on transfer controller 1 until otherwise
     * specified. This way, long transfers on the low priority queue
     * started by the codec engine will not cause audio defects.
     */
    for (i = 0; i < edma_cc[0]->num_channels; i++)
        map_dmach_queue(0, i, EVENTQ_1);

    queue_tc_mapping = info[0]->queue_tc_mapping;
    queue_priority_mapping = info[0]->queue_priority_mapping;

    /* Event queue to TC mapping */
    for (i = 0; queue_tc_mapping[i][0] != -1; i++)
        map_queue_tc(0, queue_tc_mapping[i][0],
                queue_tc_mapping[i][1]);

    /* Event queue priority mapping */
    for (i = 0; queue_priority_mapping[i][0] != -1; i++)
        assign_priority_to_queue(0,
                    queue_priority_mapping[i][0],
                    queue_priority_mapping[i][1]);

    /* Map the channel to param entry if channel mapping logic
     * exist
     */
    if (edma_read(0, EDMA_CCCFG) & CHMAP_EXIST)
        map_dmach_param(0);

    for (i = 0; i < info[0]->n_region; i++) {
        edma_write_array2(0, EDMA_DRAE, i, 0, 0x0);
        edma_write_array2(0, EDMA_DRAE, i, 1, 0x0);
        edma_write_array(0, EDMA_QRAE, i, 0x0);
    }
    arch_num_cc++;

    if (tc_errs_handled) {
        rt_hw_interrupt_install(IRQ_TCERRINT0, dma_tc0err_handler, "edma_tc0");
        rt_hw_interrupt_umask(IRQ_TCERRINT0);
        rt_hw_interrupt_install(IRQ_TCERRINT, dma_tc1err_handler, "edma_tc1");
        rt_hw_interrupt_umask(IRQ_TCERRINT);
    }

    return 0;

fail:

fail1:
    rt_free(edma_cc[0]);

    return status;
}


