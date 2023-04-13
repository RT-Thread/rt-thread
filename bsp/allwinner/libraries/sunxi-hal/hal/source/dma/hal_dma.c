/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
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

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <hal_reset.h>
#include <hal_cache.h>
#include <hal_mem.h>
#include <hal_atomic.h>
#include <hal_clk.h>
#include <hal_interrupt.h>
#include <interrupt.h>
#include <sunxi_hal_common.h>
#include <hal_dma.h>


#define DMA_ERR(fmt, arg...) printf("%s()%d " fmt, __func__, __LINE__, ##arg)

static struct sunxi_dma_chan    dma_chan_source[NR_MAX_CHAN];
static hal_spinlock_t dma_lock;
/*
 * Fix sconfig's bus width according to at_dmac.
 * 1 byte -> 0, 2 bytes -> 1, 4 bytes -> 2, 8bytes -> 3
 */
static inline uint32_t convert_buswidth(enum dma_slave_buswidth addr_width)
{
    if (addr_width > DMA_SLAVE_BUSWIDTH_8_BYTES)
    {
        return 0;
    }

    switch (addr_width)
    {
        case DMA_SLAVE_BUSWIDTH_2_BYTES:
            return 1;
        case DMA_SLAVE_BUSWIDTH_4_BYTES:
            return 2;
        case DMA_SLAVE_BUSWIDTH_8_BYTES:
            return 3;
        default:
            /* For 1 byte width or fallback */
            return 0;
    }
}

static inline void convert_burst(uint32_t *maxburst)
{
    switch (*maxburst)
    {
        case 1:
            *maxburst = 0;
            break;
        case 4:
            *maxburst = 1;
            break;
        case 8:
            *maxburst = 2;
            break;
        case 16:
            *maxburst = 3;
            break;
        default:
            printf("unknown maxburst\n");
            *maxburst = 0;
            break;
    }
}

static inline void sunxi_cfg_lli(struct sunxi_dma_lli *lli, uint32_t src_addr,
                            uint32_t dst_addr, uint32_t len,
                            struct dma_slave_config *config)
{
    uint32_t src_width = 0, dst_width = 0;

    if (NULL == lli && NULL == config)
    {
        return;
    }

    src_width = convert_buswidth(config->src_addr_width);
    dst_width = convert_buswidth(config->dst_addr_width);
    lli->cfg = SRC_BURST(config->src_maxburst) | \
               SRC_WIDTH(src_width) | \
               DST_BURST(config->dst_maxburst) | \
               DST_WIDTH(dst_width);

    lli->src = src_addr;
    lli->dst = dst_addr;
    lli->len = len;
    lli->para = NORMAL_WAIT;
}

static void sunxi_dump_lli(struct sunxi_dma_chan *chan, struct sunxi_dma_lli *lli)
{
#ifdef DMA_DEBUG
    printf("channum:%x\n"
           "\t\tdesc:desc - 0x%08x desc p - 0x%08x desc v - 0x%08x\n"
           "\t\tlli: v- 0x%08x v_lln - 0x%08x s - 0x%08x d - 0x%08x\n"
           "\t\tlen - 0x%08x para - 0x%08x p_lln - 0x%08x\n",
           chan->chan_count,
       (uint32_t)chan->desc, (uint32_t)chan->desc->p_lln, (uint32_t)chan->desc->vlln,
       (uint32_t)lli, (uint32_t)lli->vlln, (uint32_t)lli->src,
           (uint32_t)lli->dst, (uint32_t)lli->len, (uint32_t)lli->para, (uint32_t)lli->p_lln);
#endif
}

static void sunxi_dump_com_regs(void)
{
#ifdef DMA_DEBUG
    printf("Common register:\n"
           "\tmask0: 0x%08x\n"
           "\tmask1: 0x%08x\n"
           "\tpend0: 0x%08x\n"
           "\tpend1: 0x%08x\n"
#ifdef DMA_SECURE
           "\tsecur: 0x%08x\n"
#endif
#ifdef DMA_GATE
           "\t_gate: 0x%08x\n"
#endif
           "\tstats: 0x%08x\n",
           (uint32_t)hal_readl(DMA_IRQ_EN(0)),
           (uint32_t)hal_readl(DMA_IRQ_EN(1)),
           (uint32_t)hal_readl(DMA_IRQ_STAT(0)),
           (uint32_t)hal_readl(DMA_IRQ_STAT(1)),
#ifdef DMA_SECURE
           (uint32_t)hal_readl(DMA_SECURE),
#endif
#ifdef DMA_GATE
           (uint32_t)hal_readl(DMA_GATE),
#endif
           (uint32_t)hal_readl(DMA_STAT));
#endif
}

static inline void sunxi_dump_chan_regs(struct sunxi_dma_chan *ch)
{
#ifdef DMA_DEBUG
    u32 chan_num = ch->chan_count;
    printf("Chan %d reg:\n"
           "\t___en: \t0x%08x\n"
           "\tpause: \t0x%08x\n"
           "\tstart: \t0x%08x\n"
           "\t__cfg: \t0x%08x\n"
           "\t__src: \t0x%08x\n"
           "\t__dst: \t0x%08x\n"
           "\tcount: \t0x%08x\n"
           "\t_para: \t0x%08x\n\n",
           chan_num,
           (uint32_t)hal_readl(DMA_ENABLE(chan_num)),
           (uint32_t)hal_readl(DMA_PAUSE(chan_num)),
           (uint32_t)hal_readl(DMA_LLI_ADDR(chan_num)),
           (uint32_t)hal_readl(DMA_CFG(chan_num)),
           (uint32_t)hal_readl(DMA_CUR_SRC(chan_num)),
           (uint32_t)hal_readl(DMA_CUR_DST(chan_num)),
           (uint32_t)hal_readl(DMA_CNT(chan_num)),
           (uint32_t)hal_readl(DMA_PARA(chan_num)));
#endif
}

static void *sunxi_lli_list(struct sunxi_dma_lli *prev, struct sunxi_dma_lli *next,
                        struct sunxi_dma_chan *chan)
{
    if ((!prev && !chan) || !next)
    {
        return NULL;
    }
    if (!prev)
    {
        chan->desc = next;
        chan->desc->p_lln = __va_to_pa((unsigned long)next);
        chan->desc->vlln = next;
    }
    else
    {
        prev->p_lln = __va_to_pa((unsigned long)next);
        prev->vlln = next;
    }

    next->p_lln = LINK_END;
    next->vlln = NULL;

    return next;
}

static irqreturn_t sunxi_dma_irq_handle(int irq,  void *ptr)
{

    uint32_t status_l = 0, status_h = 0;
    int i = 0;

    status_l = hal_readl(DMA_IRQ_STAT(0));
#if NR_MAX_CHAN + START_CHAN_OFFSET > HIGH_CHAN
    status_h = hal_readl(DMA_IRQ_STAT(1));
#endif
    hal_writel(status_l, DMA_IRQ_STAT(0));
#if NR_MAX_CHAN + START_CHAN_OFFSET > HIGH_CHAN
    hal_writel(status_h, DMA_IRQ_STAT(1));
#endif

    for (i = 0; i < NR_MAX_CHAN; i++)
    {
        uint32_t __cpsr;
        struct sunxi_dma_chan *chan = &dma_chan_source[i];

        __cpsr = hal_spin_lock_irqsave(&dma_lock);
        uint32_t chan_num = chan->chan_count;
        uint32_t status = 0;

        if (chan->used == 0)
        {

            hal_spin_unlock_irqrestore(&dma_lock, __cpsr);
            continue;
        }

        status = (chan_num + START_CHAN_OFFSET >= HIGH_CHAN) \
                 ? (status_h >> ((chan_num + START_CHAN_OFFSET - HIGH_CHAN) << 2)) \
                 : (status_l >> ((chan_num + START_CHAN_OFFSET) << 2));

        if (!(chan->irq_type & status))
        {
            goto unlock;
        }

        if (chan->cyclic)
        {
            dma_callback cb = NULL;
            void *cb_data = NULL;

            chan->periods_pos ++;
            if (chan->periods_pos * chan->desc->len >= chan->buf_len)
            {
                chan->periods_pos = 0;
            }
            cb = chan->callback;
            cb_data = chan->callback_param;

            hal_spin_unlock_irqrestore(&dma_lock, __cpsr);
            if (cb)
            {
                cb(cb_data);
            }
            __cpsr = hal_spin_lock_irqsave(&dma_lock);
        }
        else
        {
            dma_callback cb = NULL;
            void *cb_data = NULL;

            cb = chan->callback;
            cb_data = chan->callback_param;

            hal_spin_unlock_irqrestore(&dma_lock, __cpsr);
            if (cb)
            {
                cb(cb_data);
            }
            __cpsr = hal_spin_lock_irqsave(&dma_lock);
        }
unlock:
        hal_spin_unlock_irqrestore(&dma_lock, __cpsr);
    }
    return 0;
}

static int sunxi_dma_clk_init(bool enable)
{
    hal_clk_status_t ret;
    hal_reset_type_t reset_type = HAL_SUNXI_RESET;
    u32  reset_id;
    hal_clk_type_t clk_type = HAL_SUNXI_CCU;
    hal_clk_id_t clk_id;
    hal_clk_t clk;
    struct reset_control *reset;

    clk_id = SUNXI_CLK_DMA;
    reset_id = SUNXI_RST_DMA;
    if (enable)
    {
    reset = hal_reset_control_get(reset_type, reset_id);
    hal_reset_control_deassert(reset);
    hal_reset_control_put(reset);

    hal_clock_enable(hal_clock_get(clk_type, SUNXI_CLK_MBUS_DMA));
    clk = hal_clock_get(clk_type, clk_id);
    ret = hal_clock_enable(clk);
    if (ret != HAL_CLK_STATUS_OK)
        DMA_ERR("DMA clock enable failed.\n");
    }
    else
    {
    clk = hal_clock_get(clk_type, clk_id);
    ret = hal_clock_disable(clk);
    if (ret != HAL_CLK_STATUS_OK)
        DMA_ERR("DMA clock disable failed.\n");
    hal_clock_disable(hal_clock_get(clk_type, SUNXI_CLK_MBUS_DMA));
    hal_clock_put(clk);
    }

    return ret;
}

void sunxi_dma_free_ill(struct sunxi_dma_chan *chan)
{
    struct sunxi_dma_lli *li_adr = NULL, *next = NULL;

    if (NULL == chan)
    {
        DMA_ERR("[dma] chan is NULL\n");
        return ;
    }

    li_adr = chan->desc;
    chan->desc = NULL;

    while (li_adr)
    {
        next = li_adr->vlln;
        dma_free_coherent(li_adr);
        li_adr = next;
    }

    chan->callback = NULL;
    chan->callback_param = NULL;
}

hal_dma_chan_status_t hal_dma_chan_request(struct sunxi_dma_chan **dma_chan)
{
    int i = 0;
    struct sunxi_dma_chan *chan;
    uint32_t __cpsr;

    for (i = 0; i < NR_MAX_CHAN; i++)
    {
        __cpsr = hal_spin_lock_irqsave(&dma_lock);
        chan = &dma_chan_source[i];
        if (chan->used == 0)
        {
            chan->used = 1;
            chan->chan_count = i;
            hal_spin_unlock_irqrestore(&dma_lock, __cpsr);
        *dma_chan = &dma_chan_source[i];
            return HAL_DMA_CHAN_STATUS_FREE;
        }
        hal_spin_unlock_irqrestore(&dma_lock, __cpsr);
    }

    return HAL_DMA_CHAN_STATUS_BUSY;
}

hal_dma_status_t hal_dma_prep_memcpy(struct sunxi_dma_chan *chan,
                       uint32_t dest, uint32_t src, uint32_t len)
{
    struct sunxi_dma_lli *l_item = NULL;
    struct dma_slave_config *config = NULL;
    uint32_t __cpsr;

    if ((NULL == chan) || (dest == 0 || src == 0))
    {
        DMA_ERR("[dma] chan is NULL\n");
        return HAL_DMA_STATUS_INVALID_PARAMETER;
    }

    __cpsr = hal_spin_lock_irqsave(&dma_lock);

    l_item = (struct sunxi_dma_lli *)dma_alloc_coherent(sizeof(struct sunxi_dma_lli));
    if (!l_item)
    {
        hal_spin_unlock_irqrestore(&dma_lock, __cpsr);
    return HAL_DMA_STATUS_NO_MEM;
    }
    memset(l_item, 0, sizeof(struct sunxi_dma_lli));

    config = &chan->cfg;

    dest = __va_to_pa(dest);
    src = __va_to_pa(src);
    sunxi_cfg_lli(l_item, src, dest, len, config);

    l_item->cfg |= SRC_DRQ(DRQSRC_SDRAM) \
                   | DST_DRQ(DRQDST_SDRAM) \
                   | DST_LINEAR_MODE \
                   | SRC_LINEAR_MODE;
    sunxi_lli_list(NULL, l_item, chan);

    sunxi_dump_lli(chan, l_item);

    hal_spin_unlock_irqrestore(&dma_lock, __cpsr);

    return HAL_DMA_STATUS_OK;
}

hal_dma_status_t hal_dma_prep_device(struct sunxi_dma_chan *chan,
                       uint32_t dest, uint32_t src,
                       uint32_t len, enum dma_transfer_direction dir)
{
    struct sunxi_dma_lli *l_item = NULL;
    struct dma_slave_config *config = NULL;
    uint32_t __cpsr;

    if ((NULL == chan) || (dest == 0 || src == 0))
    {
        DMA_ERR("[dma] chan is NULL\n");
        return HAL_DMA_STATUS_INVALID_PARAMETER;
    }

    l_item = (struct sunxi_dma_lli *)dma_alloc_coherent(sizeof(struct sunxi_dma_lli));
    if (!l_item)
    {
        return HAL_DMA_STATUS_NO_MEM;
    }
    memset(l_item, 0, sizeof(struct sunxi_dma_lli));

    __cpsr = hal_spin_lock_irqsave(&dma_lock);

    config = &chan->cfg;

    if (dir == DMA_MEM_TO_DEV)
    {
        src = __va_to_pa(src);
        sunxi_cfg_lli(l_item, src, dest, len, config);
        l_item->cfg |= GET_DST_DRQ(config->slave_id) \
                       | SRC_LINEAR_MODE \
                       | DST_IO_MODE \
                       | SRC_DRQ(DRQSRC_SDRAM);
    }
    else if (dir == DMA_DEV_TO_MEM)
    {
        dest = __va_to_pa(dest);
        sunxi_cfg_lli(l_item, src, dest, len, config);
        l_item ->cfg |= GET_SRC_DRQ(config->slave_id)  \
                        | DST_LINEAR_MODE \
                        | SRC_IO_MODE \
                        | DST_DRQ(DRQSRC_SDRAM);
    }
    else if (dir == DMA_DEV_TO_DEV)
    {
        sunxi_cfg_lli(l_item, src, dest, len, config);
        l_item->cfg |= GET_SRC_DRQ(config->slave_id) \
                       | DST_IO_MODE \
                       | SRC_IO_MODE \
                       | GET_DST_DRQ(config->slave_id);
    }

    sunxi_lli_list(NULL, l_item, chan);

    sunxi_dump_lli(chan, l_item);

    hal_spin_unlock_irqrestore(&dma_lock, __cpsr);

    return HAL_DMA_STATUS_OK;
}

hal_dma_status_t hal_dma_prep_cyclic(struct sunxi_dma_chan *chan,
                     uint32_t buf_addr, uint32_t buf_len,
                     uint32_t period_len, enum dma_transfer_direction dir)
{
    struct sunxi_dma_lli *l_item = NULL, *prev = NULL;
    uint32_t periods = buf_len / period_len;
    struct dma_slave_config *config = NULL;
    uint32_t i = 0;
    uint32_t __cpsr;

    if ((NULL == chan) || (0 == buf_addr))
    {
        DMA_ERR("[dma] chan or buf_addr is NULL\n");
        return HAL_DMA_STATUS_INVALID_PARAMETER;
    }

    __cpsr = hal_spin_lock_irqsave(&dma_lock);

    if (chan->desc) {
        struct sunxi_dma_lli *li_adr = NULL, *next = NULL;

        li_adr = chan->desc;
        chan->desc = NULL;

        while (li_adr)
        {
            next = li_adr->vlln;
            dma_free_coherent(li_adr);
            li_adr = next;
        }
    }

    config = &chan->cfg;
    for (i = 0; i < periods; i++)
    {
        hal_spin_unlock_irqrestore(&dma_lock, __cpsr);
        l_item = (struct sunxi_dma_lli *)dma_alloc_coherent(sizeof(struct sunxi_dma_lli));
        if (!l_item)
        {
            return HAL_DMA_STATUS_NO_MEM;
        }
        __cpsr = hal_spin_lock_irqsave(&dma_lock);
        memset(l_item, 0, sizeof(struct sunxi_dma_lli));
        if (dir == DMA_MEM_TO_DEV)
        {
            sunxi_cfg_lli(l_item, __va_to_pa(buf_addr + period_len * i),
                          config->dst_addr, period_len, config);
            l_item->cfg |= GET_DST_DRQ(config->slave_id) \
                           | SRC_LINEAR_MODE \
                           | DST_IO_MODE \
                           | SRC_DRQ(DRQSRC_SDRAM);
        }
        else if (dir == DMA_DEV_TO_MEM)
        {
            sunxi_cfg_lli(l_item, config->src_addr, \
                          __va_to_pa(buf_addr + period_len * i), \
                          period_len, config);
            l_item ->cfg |= GET_SRC_DRQ(config->slave_id)  \
                            | DST_LINEAR_MODE \
                            | SRC_IO_MODE \
                            | DST_DRQ(DRQSRC_SDRAM);
        }
        else if (dir == DMA_DEV_TO_DEV)
        {
            sunxi_cfg_lli(l_item, config->src_addr, \
                          config->dst_addr, period_len, config);
            l_item->cfg |= GET_SRC_DRQ(config->slave_id) \
                           | DST_IO_MODE \
                           | SRC_IO_MODE \
                           | GET_DST_DRQ(config->slave_id);

        }
        prev = sunxi_lli_list(prev, l_item, chan);
    }
    prev->p_lln = __va_to_pa((unsigned long)chan->desc);
    chan->cyclic = true;
#ifdef DMA_DEBUG
    for (prev = chan->desc; prev != NULL; prev = prev->vlln)
    {
        sunxi_dump_lli(chan, prev);
    }
#endif
    hal_spin_unlock_irqrestore(&dma_lock, __cpsr);

    return HAL_DMA_STATUS_OK;
}

hal_dma_status_t hal_dma_callback_install(struct sunxi_dma_chan *chan,
                      dma_callback callback,
                      void *callback_param)
{
    if (NULL == chan)
    {
        DMA_ERR("[dma] chan is NULL\n");
        return HAL_DMA_STATUS_INVALID_PARAMETER;
    }

    if (NULL == callback)
    {
        DMA_ERR("[dma] callback is NULL\n");
        return HAL_DMA_STATUS_INVALID_PARAMETER;
    }

    if (NULL == callback_param)
    {
        DMA_ERR("[dma] callback_param is NULL\n");
        return HAL_DMA_STATUS_INVALID_PARAMETER;
    }

    chan->callback = callback;
    chan->callback_param = callback_param;

    return HAL_DMA_STATUS_OK;
}

hal_dma_status_t hal_dma_slave_config(struct sunxi_dma_chan *chan,
                      struct dma_slave_config *config)
{
    uint32_t __cpsr;

    if (NULL == config || NULL == chan)
    {
        DMA_ERR("[dma] dma config is NULL\n");
        return HAL_DMA_STATUS_INVALID_PARAMETER;
    }

    __cpsr = hal_spin_lock_irqsave(&dma_lock);
    convert_burst(&config->src_maxburst);
    convert_burst(&config->dst_maxburst);
    memcpy((void *) & (chan->cfg), (void *)config, sizeof(struct dma_slave_config));
    hal_spin_unlock_irqrestore(&dma_lock, __cpsr);

    return HAL_DMA_STATUS_OK;
}

enum dma_status hal_dma_tx_status(struct sunxi_dma_chan *chan, uint32_t *left_size)
{
    uint32_t i = 0;
    struct sunxi_dma_lli *l_item = NULL;
    enum dma_status status = DMA_INVALID_PARAMETER;
    uint32_t __cpsr;

    if (NULL == chan || NULL == left_size)
    {
        DMA_ERR("[dma] chan or left_size is NULL\n");
        return HAL_DMA_STATUS_INVALID_PARAMETER;
    }

    __cpsr = hal_spin_lock_irqsave(&dma_lock);
    if (chan->cyclic)
    {
        for (i = 0, l_item = chan->desc; i <= chan->periods_pos; i++, l_item = l_item->vlln)
        {
            if (NULL == l_item)
            {
                *left_size = 0;
                status = DMA_COMPLETE;
                goto unlock;
            }
        }
        if (NULL == l_item)
        {
            *left_size = 0;
            status = DMA_COMPLETE;
        }
        else
        {
            uint32_t pos = 0;
            bool count = false;

            pos = hal_readl(DMA_LLI_ADDR(chan->chan_count));
            *left_size = hal_readl(DMA_CNT(chan->chan_count));
            if (pos == LINK_END)
            {
                status = DMA_COMPLETE;
                goto unlock;
            }
            for (l_item = chan->desc; l_item != NULL; l_item = l_item->vlln)
            {
                if (l_item->p_lln == pos)
                {
                    count = true;
                    continue;
                }
                if (count)
                {
                    *left_size += l_item->len;
                }
            }
            status = DMA_IN_PROGRESS;
        }
    }
    else
    {
        *left_size = hal_readl(DMA_CNT(chan->chan_count));

        if (*left_size == 0)
        {
            status = DMA_COMPLETE;
        }
        else
        {
            status = DMA_IN_PROGRESS;
        }
    }

unlock:
    hal_spin_unlock_irqrestore(&dma_lock, __cpsr);

    return status;
}

hal_dma_status_t hal_dma_start(struct sunxi_dma_chan *chan)
{
    uint32_t high = 0;
    uint32_t irq_val = 0;
    struct sunxi_dma_lli *prev = NULL;
    uint32_t __cpsr;

    if (NULL == chan)
    {
        DMA_ERR("[dma] chan is NULL\n");
        return HAL_DMA_STATUS_INVALID_PARAMETER;
    }

    __cpsr = hal_spin_lock_irqsave(&dma_lock);

    if (chan->cyclic)
        chan->irq_type = IRQ_PKG;
    else
        chan->irq_type = IRQ_QUEUE;

    high = (chan->chan_count + START_CHAN_OFFSET >= HIGH_CHAN) ? 1 : 0;

    irq_val = hal_readl(DMA_IRQ_EN(high));
    irq_val |= SHIFT_IRQ_MASK(chan->irq_type, chan->chan_count);
    hal_writel(irq_val, DMA_IRQ_EN(high));

    SET_OP_MODE(chan->chan_count, SRC_HS_MASK | DST_HS_MASK);

    for (prev = chan->desc; prev != NULL; prev = prev->vlln)
    {
        hal_dcache_clean((unsigned long)prev, sizeof(*prev));
        /* k_dcache_clean(prev, sizeof(*prev)); */
        //k_dcache_clean(prev->src, prev->len);
        //k_dcache_clean_invalidate(prev->dst, prev->len);
    }

    hal_writel(__va_to_pa((unsigned long)chan->desc), DMA_LLI_ADDR(chan->chan_count));
    hal_writel(CHAN_START, DMA_ENABLE(chan->chan_count));
    sunxi_dump_com_regs();
    sunxi_dump_chan_regs(chan);
    hal_spin_unlock_irqrestore(&dma_lock, __cpsr);
    return HAL_DMA_STATUS_OK;
}

hal_dma_status_t hal_dma_stop(struct sunxi_dma_chan *chan)
{
    uint32_t __cpsr;

    if (NULL == chan)
    {
        DMA_ERR("[dma] chan is NULL\n");
        return HAL_DMA_STATUS_INVALID_PARAMETER;
    }

    __cpsr = hal_spin_lock_irqsave(&dma_lock);
    /*We should entry PAUSE state first to avoid missing data
    * count witch transferring on bus.
    */
    hal_writel(CHAN_PAUSE, DMA_PAUSE(chan->chan_count));
    hal_writel(CHAN_STOP, DMA_ENABLE(chan->chan_count));
    hal_writel(CHAN_RESUME, DMA_PAUSE(chan->chan_count));

    if (chan->cyclic)
    {
        chan->cyclic = false;
    }
    hal_spin_unlock_irqrestore(&dma_lock, __cpsr);

    return HAL_DMA_STATUS_OK;
}

hal_dma_status_t hal_dma_chan_free(struct sunxi_dma_chan *chan)
{
    uint32_t high = 0;
    unsigned long irq_val = 0;
    uint32_t __cpsr;

    if (NULL == chan)
    {
        DMA_ERR("[dma] chan is NULL\n");
        return HAL_DMA_STATUS_INVALID_PARAMETER;
    }

    if (!chan->used)
    {
        return HAL_DMA_STATUS_INVALID_PARAMETER;
    }

    __cpsr = hal_spin_lock_irqsave(&dma_lock);

    high = (chan->chan_count + START_CHAN_OFFSET >= HIGH_CHAN) ? 1 : 0;

    irq_val = hal_readl(DMA_IRQ_EN(high));
    irq_val &= ~(SHIFT_IRQ_MASK(chan->irq_type, chan->chan_count));
    hal_writel(irq_val, DMA_IRQ_EN(high));

    chan->used = 0;
    hal_spin_unlock_irqrestore(&dma_lock, __cpsr);

    sunxi_dma_free_ill(chan);

    return HAL_DMA_STATUS_OK;
}

hal_dma_status_t hal_dma_chan_desc_free(struct sunxi_dma_chan *chan)
{
    /* FIXME: Interrupt context cannot release memory in melis OS. */
    if (hal_interrupt_get_nest() <= 0)
    {
        sunxi_dma_free_ill(chan);
        return HAL_DMA_STATUS_OK;
    }
    /* Freeing memory in interrupt is not allowed */
    return HAL_DMA_STATUS_ERR_PERM;
}

/* only need to be executed once */
void hal_dma_init(void)
{
    uint32_t i = 0, high = 0;

    memset((void *)dma_chan_source, 0, NR_MAX_CHAN * sizeof(struct sunxi_dma_chan));

    for (i = 0; i < NR_MAX_CHAN; i++)
    {
        high = (i >= HIGH_CHAN) ? 1 : 0;
        /*disable all dma irq*/
        hal_writel(0, DMA_IRQ_EN(high));
        /*clear all dma irq pending*/
        hal_writel(0xffffffff, DMA_IRQ_STAT(high));
    }
    /* disable auto gating */
    hal_writel(DMA_MCLK_GATE | DMA_COMMON_GATE | DMA_CHAN_GATE, DMA_GATE);
    sunxi_dma_clk_init(true);

    /*request dma irq*/
    if (request_irq(DMA_IRQ_NUM, sunxi_dma_irq_handle, 0, "dma-ctl", NULL) < 0)
    {
        DMA_ERR("[dma] request irq error\n");
    }
    enable_irq(DMA_IRQ_NUM);
}

