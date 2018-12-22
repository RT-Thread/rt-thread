/*
 * File      : drv_dma.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */

/*********************************************************************************************************
**   头文件
*********************************************************************************************************/
#include <stdlib.h>
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <dma.h>

#include <cache.h>

#include "board.h"
#include "drv_clock.h"
#include "drv_dma.h"

#define JZDMA_DEBUG 0
#if JZDMA_DEBUG
#include <stdio.h>
#define JZDMA_DBG(...) rt_kprintf(__VA_ARGS__)
#else
#define JZDMA_DBG(...)
#endif

/* 全局变量 */
static struct jzdma_master      _g_jzdma_master;
static struct rt_dma_channel    _g_rt_dma_channel[NR_DMA_CHANNELS];

/*********************************************************************************************************
**   内联函数
*********************************************************************************************************/
const static char dcm_tsz[7] = { 1, 2, 0, 0, 3, 4, 5 };

rt_inline int _fls(int x)
{
    __asm__("clz %0, %1" : "=r" (x) : "r" (x));

    return 32 - x;
}
static inline int ffs(int word)
{
    if (!word)
        return 0;

    return _fls(word & -word);
}

static inline uint16_t get_max_tsz(uint32_t val, uint32_t *dcmp)
{

    int ord;

    ord = ffs(val) - 1;
    if (ord < 0)
        ord = 0;
    else if (ord > 6)
        ord = 6;

    *dcmp &= ~DCM_TSZ_MSK;
    *dcmp |= dcm_tsz[ord] << DCM_TSZ_SHF;

//    rt_kprintf("dcmp = %x\n",*dcmp);

    /* if tsz == 8, set it to 4 */
    return ord == 3 ? 4 : 1 << ord;
}


static void jzdma_mcu_reset(struct jzdma_master *master)
{
    uint32_t dmcs;
    dmcs = readl(master->base + DMCS);
    dmcs |= 0x1;
    writel(dmcs, master->base + DMCS);
}

static uint32_t jzdma_get_current_trans_addr(struct jzdma_channel *jz_dmac,
                                             uint32_t* dst_addr,
                                             uint32_t* src_addr,
                                             uint32_t direction)
{
    uint32_t ret_val = 0;

    if (jz_dmac->status == STAT_STOPED || jz_dmac->status == STAT_PREPED)
        return 0;

    if (direction ==  RT_DMA_MEM_TO_DEV)
    {
        ret_val = readl(jz_dmac->iomem + CH_DSA);
        if (src_addr)
            *src_addr = ret_val;
        if (dst_addr)
            *dst_addr = readl(jz_dmac->iomem + CH_DTA);
    }
    else if (direction == RT_DMA_DEV_TO_MEM)
    {
        ret_val = readl(jz_dmac->iomem + CH_DTA);
        if (dst_addr)
            *dst_addr = ret_val;
        if (src_addr)
            *src_addr = readl(jz_dmac->iomem + CH_DSA);
    }
    else if (direction == RT_DMA_MEM_TO_MEM)
    {
        if (dst_addr)
            *dst_addr = readl(jz_dmac->iomem + CH_DTA);
        if (src_addr)
            *src_addr = readl(jz_dmac->iomem + CH_DSA);
    }

    return ret_val;
}


int jzdma_funcs_status(struct rt_dma_channel *dmac)
{
    struct jzdma_channel     *jz_dmac;

    RT_ASSERT(dmac != RT_NULL);
    jz_dmac = (struct jzdma_channel *)dmac->user_data;

    switch (jz_dmac->status)
    {
        case STAT_STOPED:
            return RT_DMA_STATUS_IDLE;
            break;
        default:
            break;
    }

    return RT_DMA_STATUS_BUSY;
}


void jzdma_funcs_reset(struct rt_dma_channel *rt_dmac)
{
    struct jzdma_channel     *jz_dmac;

    RT_ASSERT(rt_dmac != RT_NULL);
    jz_dmac = (struct jzdma_channel *)rt_dmac->user_data;
    /* 终止当前传输 */
    jz_dmac->status = STAT_STOPED;
    jz_dmac->desc_nr = 0;

    /* clear dma status */
    writel(0, jz_dmac->iomem + CH_DCS);

    /* 重新设置参数 */
    switch (rt_dmac->config.direction)
    {
        case RT_DMA_MEM_TO_DEV:
            /* MEM_TO_DEV ，按照设备的地址宽度设置DCM */
            switch(rt_dmac->config.dst_addr_width)
            {
            case RT_DMA_BUSWIDTH_1_BYTE:
                jz_dmac->desc.dcm |= DCM_SP_8 | DCM_DP_8;
                break;
            case RT_DMA_BUSWIDTH_2_BYTES:
                jz_dmac->desc.dcm |= DCM_SP_16 | DCM_DP_16;
                break;
            case RT_DMA_BUSWIDTH_4_BYTES:
                jz_dmac->desc.dcm &= ~(DCM_SP_32 | DCM_DP_32);
                break;
            default:
                JZDMA_DBG("bus width error. \r\n");
                return;
            }

            break;
        default:
            /* 其他方式 按照源地址宽度设置 DCM */
            switch(rt_dmac->config.src_addr_width)
            {
            case RT_DMA_BUSWIDTH_1_BYTE:
                jz_dmac->desc.dcm |= DCM_SP_8 | DCM_DP_8;
                break;
            case RT_DMA_BUSWIDTH_2_BYTES:
                jz_dmac->desc.dcm |= DCM_SP_16 | DCM_DP_16;
                break;
            case RT_DMA_BUSWIDTH_4_BYTES:
                jz_dmac->desc.dcm &= ~(DCM_SP_32 | DCM_DP_32);
                break;
            default:
                JZDMA_DBG("bus width error. \r\n");
                return;
            }
            break;
    }
    return;
}

rt_size_t jzdma_funcs_transfer(struct rt_dma_channel  *rt_dmac , struct dma_message *message)
{
    struct jzdma_channel     *jz_dmac;
    uint32_t    tsz;

    RT_ASSERT(rt_dmac != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    jz_dmac = (struct jzdma_channel *)rt_dmac->user_data;

    if(jz_dmac->status == STAT_RUNNING)
        return -RT_EBUSY;
    /* 清除硬件寄存器 */
//    writel(0, jz_dmac->iomem + CH_DCM);
//    writel(0, jz_dmac->iomem + CH_DCS);

    /* clear dma status */
    writel(0, jz_dmac->iomem + CH_DCS);


    //刷新cache
    switch(rt_dmac->config.direction)
    {
    case RT_DMA_MEM_TO_DEV:
    case RT_DMA_MEM_TO_MEM:
        rt_hw_dcache_flush_range((rt_ubase_t)(message->src_addr),message->t_size);
        break;

    default:
        break;
    }
//    /* 重新设置参数 */
//    switch (rt_dmac->config.direction)
//    {
//        case RT_DMA_MEM_TO_DEV:
//            /* MEM_TO_DEV ，按照设备的地址宽度设置DCM */
//            switch(rt_dmac->config.dst_addr_width)
//            {
//            case RT_DMA_BUSWIDTH_1_BYTE:
//                jz_dmac->desc.dcm |= DCM_SP_8 | DCM_DP_8;
//                break;
//            case RT_DMA_BUSWIDTH_2_BYTES:
//                jz_dmac->desc.dcm |= DCM_SP_16 | DCM_DP_16;
//                break;
//            case RT_DMA_BUSWIDTH_4_BYTES:
//                jz_dmac->desc.dcm &= ~(DCM_SP_32 | DCM_DP_32);
//                break;
//            default:
//                JZDMA_DBG("bus width error. \r\n");
//                return -1;
//            }
//
//            break;
//        default:
//            /* 其他方式 按照源地址宽度设置 DCM */
//            switch(rt_dmac->config.src_addr_width)
//            {
//            case RT_DMA_BUSWIDTH_1_BYTE:
//                jz_dmac->desc.dcm |= DCM_SP_8 | DCM_DP_8;
//                break;
//            case RT_DMA_BUSWIDTH_2_BYTES:
//                jz_dmac->desc.dcm |= DCM_SP_16 | DCM_DP_16;
//                break;
//            case RT_DMA_BUSWIDTH_4_BYTES:
//                jz_dmac->desc.dcm &= ~(DCM_SP_32 | DCM_DP_32);
//                break;
//            default:
//                JZDMA_DBG("bus width error. \r\n");
//                return 0;
//            }
//            break;
//    }

    /* clear LINK bit when issue pending */
    jz_dmac->desc.dcm |= DCM_TIE;
    /* Disable desc link */
    jz_dmac->desc.dcm &= ~DCM_LINK;

    /* 识别传输地址控制 */
    switch(message->src_option)
    {
    case RT_DMA_ADDR_INC:
        jz_dmac->desc.dcm |= DCM_SAI;
        break;
    case RT_DMA_ADDR_FIX:
        jz_dmac->desc.dcm &= ~DCM_SAI;
        break;
    default:
        return -RT_EIO;
    }

    switch(message->dst_option)
    {
    case RT_DMA_ADDR_INC:
        jz_dmac->desc.dcm |= DCM_DAI;
        break;
    case RT_DMA_ADDR_FIX:
        jz_dmac->desc.dcm &= ~DCM_DAI;
        break;
    default:
        return -RT_EIO;
    }

    /* 设置TSZ */
    if(rt_dmac->ch == 1)
    {
        /*
         * for special channel1 tsz = 7 (auto)
         */
        jz_dmac->desc.dcm |= 7 << 8;
        tsz = message->t_size;
    }
    else
    {
        if(rt_dmac->config.direction == RT_DMA_MEM_TO_DEV)
        {
            tsz = get_max_tsz((uint32_t)(message->src_addr) | message->t_size | rt_dmac->config.dst_maxburst, &jz_dmac->desc.dcm);
            tsz = message->t_size / tsz;
        }
        else
        {
            tsz = get_max_tsz((uint32_t)(message->dst_addr) | message->t_size | rt_dmac->config.src_maxburst, &jz_dmac->desc.dcm);
            tsz = message->t_size / tsz;
        }
    }
    jz_dmac->desc.dsa = (uint32_t)(message->src_addr) & 0x1FFFFFFF;
    JZDMA_DBG("dsa = %x\n",jz_dmac->desc.dsa);
    jz_dmac->desc.dta = (uint32_t)(message->dst_addr) & 0x1FFFFFFF;
    JZDMA_DBG("dta = %x\n",jz_dmac->desc.dta);
    jz_dmac->desc.dtc =  tsz;
    JZDMA_DBG("dtc = %x\n",jz_dmac->desc.dtc);
//    jz_dmac->desc.drt = jz_dmac->type;
    jz_dmac->desc.drt = (uint32_t)message->t_mode;
    JZDMA_DBG("drt = %x\n",jz_dmac->desc.drt);
    jz_dmac->desc.sd = 0;
    JZDMA_DBG("dcm = %x\n",jz_dmac->desc.dcm);

    /* I don't want to use 8-word descriptors */
    writel(DCS_NDES,jz_dmac->iomem + CH_DCS);

    /* Update DMA Channel Register */
    writel(jz_dmac->desc.dsa, jz_dmac->iomem + CH_DSA);
    writel(jz_dmac->desc.dta, jz_dmac->iomem + CH_DTA);
    writel(jz_dmac->desc.dtc, jz_dmac->iomem + CH_DTC);
    writel(jz_dmac->desc.drt, jz_dmac->iomem + CH_DRT);

    jz_dmac->status = STAT_RUNNING;
    jz_dmac->desc.dcm &= ~DCM_LINK;
    jz_dmac->desc.dcm |= DCM_TIE;
    writel(jz_dmac->desc.dcm, jz_dmac->iomem + CH_DCM);

    /* DCS.CTE = 1 */
    writel(readl(jz_dmac->iomem + CH_DCS) | DCS_CTE,(jz_dmac->iomem + CH_DCS));

    return message->t_size;
}

static void jzdma_int_handler(int vector,void *param)
{
    struct jzdma_master *master = &_g_jzdma_master;
    uint32_t pending,dcs;
    int i;

    pending = readl(master->base + DIRQP);

    for (i = 0; i < NR_DMA_CHANNELS; i++)
    {
        struct rt_dma_channel *rt_dmac = &_g_rt_dma_channel[i];
        struct jzdma_channel  *jz_dmac = (struct jzdma_channel  *)rt_dmac->user_data;

        if (!(pending & (1 << i)))
            continue;

        dcs = readl(jz_dmac->iomem + CH_DCS);
        jz_dmac->dcs_saved = dcs;

        writel(0, jz_dmac->iomem + CH_DCS);
        if (jz_dmac->status != STAT_RUNNING)
            continue;

        /* Address Error. */
        if(dcs & DCS_AR)
        {
            JZDMA_DBG("Addr Error: DCS%d=%lx\n",i,dcs);

            rt_dma_contex_service(rt_dmac,RT_DMA_EVENT_ERROR);
        }

        /* DMA halt */
        if (dcs & DCS_HLT)
        {
            JZDMA_DBG("DMA Halt: DCS%d=%lx\n", i, dcs);
        }

        /* DMA 传输已完成 */
        if (dcs & DCS_TT)
        {
            jz_dmac->status = STAT_STOPED;
            JZDMA_DBG("DMA CH%d Over\n",i);

            //刷新cache
            switch(rt_dmac->config.direction)
            {
            case RT_DMA_DEV_TO_MEM:
            case RT_DMA_MEM_TO_MEM:
            {
                struct dma_message  *message;
                message = rt_dma_get_current_message(rt_dmac);
                if(message)
                {
//                    r4k_dcache_inv((rt_ubase_t)(message->dst_addr),message->t_size);
                    rt_hw_dcache_invalidate_range((rt_ubase_t)(message->dst_addr),message->t_size);
                }
            }
            break;

            default:
                break;
            }
            rt_dma_contex_service(rt_dmac,RT_DMA_EVENT_COMPLETE);
        }
    }

    pending = readl(master->base + DMAC);
    pending &= ~(DMAC_HLT | DMAC_AR);
    writel(pending, master->base + DMAC);
    writel(0, master->base + DIRQP);

}

/* not use */
static void jzdma_link_int_handler(int irq, void *param)
{
    struct jzdma_master *master = &_g_jzdma_master;
    uint32_t pending;
    int i;

    pending = readl(master->base + DESIRQP);

    JZDMA_DBG("Link INT \n");

    for (i = 0; i < NR_DMA_CHANNELS; i++)
    {
        struct rt_dma_channel *rt_dmac = &_g_rt_dma_channel[i];
        struct jzdma_channel  *jz_dmac = (struct jzdma_channel  *)rt_dmac->user_data;

        if (!(pending & (1 << i)))
            continue;
        if (jz_dmac->status != STAT_RUNNING)
            continue;
    }

    writel((readl(master->base + DIC)&(~pending)),master->base + DIC);
}

/* RTDMA 驱动层 接口*/
struct dma_ops _g_jzdma_ops =
{
    .reset     = jzdma_funcs_reset,
    .trans     = jzdma_funcs_transfer,
    .status    = jzdma_funcs_status
};


int rt_hw_jzdma_init(void)
{
    int i;
    struct jzdma_master *master = &_g_jzdma_master;
    uint32_t pdma_program = 0;
    /* 使能DMA 时钟 */
    master->clk = clk_get("pdma");
    clk_enable(master->clk);

    master->base = DMAC_BASE;
    master->irq  = IRQ_PDMA;
    master->irq_pdmad = IRQ_PDMAD;

    /* ???
     * indeed it think we should also enable special channel<0,1>
     * but when you guys enable it (set bit1) the main cpu will never get interrupt from dma channel when TC count down to 0
     */
    writel(1 | (0x3f << 16), master->base + DMAC);

    for (i = 0; i < NR_DMA_CHANNELS; i++)
    {
        struct rt_dma_channel   *rt_dmac = &(_g_rt_dma_channel[i]);
        struct jzdma_channel    *jz_dmac = &(master->channel[i]);
        struct dma_config   config =
        {
            .direction      = RT_DMA_MEM_TO_MEM,
            .src_addr_width = RT_DMA_BUSWIDTH_4_BYTES,
            .src_maxburst   = (64 * 1024),
            .dst_addr_width = RT_DMA_BUSWIDTH_4_BYTES,
            .dst_maxburst   = (64 * 1024),
        };

        rt_dmac->ch         = i;

        jz_dmac->type       = JZDMA_REQ_AUTO;
        jz_dmac->iomem      = master->base + i * 0x20;
        jz_dmac->status     = STAT_STOPED;
        jz_dmac->dcm_def    = 0;

        pdma_program |= (0x01 << i);

        rt_dma_drv_install(rt_dmac,&_g_jzdma_ops,&config,jz_dmac);
    }

    /* the corresponding dma channel is set programmable */
//    writel(pdma_program, dma->base + DMACP);

    jzdma_mcu_reset(master);

    /* 注册 DMA中断 */
    rt_hw_interrupt_install(IRQ_PDMA,jzdma_int_handler,RT_NULL,"PDMA");
    rt_hw_interrupt_umask(IRQ_PDMA);

    rt_hw_interrupt_install(IRQ_PDMAD,jzdma_link_int_handler,RT_NULL,"PDMAD");
    rt_hw_interrupt_umask(IRQ_PDMAD);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_jzdma_init);
