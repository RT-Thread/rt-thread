/*
 * drv_dmic.h
 *
 *  Created on: 2017Äê1ÔÂ11ÈÕ
 *      Author: Urey
 */

#ifndef _DRV_DMIC_H_
#define _DRV_DMIC_H_

/*
 * File      : drv_dmic.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
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

#include <dma.h>
#include "audio_pipe.h"
#define DMIC_DMA_PAGE_SIZE  512
#define DMIC_DMA_PAGE_NUM   RT_DMA_MAX_NODES
struct jz_dmic
{
    struct rt_audio_pipe       pipe;
    struct rt_audio_configure   record_config;
    uint32_t    io_base;

    struct clk *clk_gate;
    struct rt_dma_channel *rx_dmac;

    rt_uint8_t  *dma_buf;
    rt_uint32_t dma_offset;

    /* record */
    int     record_gain;
};
static inline void dmic_write_reg(struct jz_dmic *dmic, uint32_t reg, uint32_t val)
{
    writel(val, dmic->io_base + reg);
}
static inline uint32_t dmic_read_reg(struct jz_dmic *jz_dmic, unsigned int reg)
{
    return readl(jz_dmic->io_base + reg);
}
#define dmic_set_reg(dmic, addr, val, mask, offset)\
    do {    \
        int tmp_val = val;                             \
        int read_val = dmic_read_reg(dmic, addr);      \
        read_val &= (~mask);                            \
        tmp_val = ((tmp_val << offset) & mask);         \
        tmp_val |= read_val;                            \
        dmic_write_reg(dmic, addr, tmp_val);            \
    }while(0)
#define dmic_get_reg(dmic, addr, mask, offset)  \
    ((dmic_read_reg(dmic, addr) & mask) >> offset)
/*********************************************************************************************************
**
*********************************************************************************************************/
#define DMICCR0     0x00
#define DMICGCR     0x04
#define DMICIMR     0x08
#define DMICINTCR   0x0c
#define DMICTRICR   0x10
#define DMICTHRH    0x14
#define DMICTHRL    0x18
#define DMICTRIMMAX 0x1c
#define DMICTRINMAX 0x20
#define DMICDR      0x30
#define DMICFTHR    0x34
#define DMICFSR     0x38
#define DMICCGDIS   0x50
/*    DMICCR0  */
#define DMIC_RESET      31
#define DMIC_RESET_MASK     (0x1 << DMIC_RESET)
#define DMIC_RESET_TRI  30
#define DMIC_RESET_TRI_MASK (0x1 << DMIC_RESET_TRI)
#define DMIC_CHNUM      16
#define DMIC_CHNUM_MASK         (0x7 << DMIC_CHNUM)
#define DMIC_UNPACK_MSB 13
#define DMIC_UNPACK_MSB_MASK    (0x1 << DMIC_UNPACK_MSB)
#define DMIC_UNPACK_DIS 12
#define DMIC_UNPACK_DIS_MASK    (0x1 << DMIC_UNPACK_DIS)
#define DMIC_SW_LR      11
#define DMIC_SW_LR_MASK     (0x1 << DMIC_SW_LR)
#define DMIC_SPLIT_DI   10
#define DMIC_SPLIT_DI_MASK  (0x1 << DMIC_SPLIT_DI)
#define DMIC_PACK_EN    8
#define DMIC_PACK_EN_MASK   (0x1 << DMIC_PACK_EN)
#define DMIC_SR         6
#define DMIC_SR_MASK        (0x3 << DMIC_SR)
#define DMIC_LP_MODE    3
#define DMIC_LP_MODE_MASK   (0x1 << DMIC_LP_MODE)
#define DMIC_HPF1_MODE  2
#define DMIC_HPF1_MODE_MASK (0x1 << DMIC_HPF1_MODE)
#define DMIC_TRI_EN     1
#define DMIC_TRI_EN_MASK    (0x1 << DMIC_TRI_EN)
#define DMIC_EN         0
#define DMIC_EN_MASK        (0x1 << DMIC_EN)
#define __dmic_reset(dmic)\
        dmic_set_reg(dmic,DMICCR0,1,DMIC_RESET_MASK,DMIC_RESET)
#define __dmic_get_reset(dmic)\
        dmic_get_reg(dmic,DMICCR0,DMIC_RESET_MASK,DMIC_RESET)
#define __dmic_reset_tri(dmic)\
        dmic_set_reg(dmic,DMICCR0,1,DMIC_RESET_TRI_MASK,DMIC_RESET_TRI)
#define __dmic_set_chnum(dmic,n)\
        dmic_set_reg(dmic,DMICCR0,n,DMIC_CHNUM_MASK,DMIC_CHNUM)
#define __dmic_get_chnum(dmic,n)\
        dmic_set_reg(dmic,DMICCR0,DMIC_CHNUM_MASK,DMIC_CHNUM)
#define __dmic_unpack_msb(dmic)\
        dmic_set_reg(dmic,DMICCR0,1,DMIC_UNPACK_MSB_MASK,DMIC_UNPACK_MSB)
#define __dmic_unpack_dis(dmic)\
        dmic_set_reg(dmic,DMICCR0,1,DMIC_UNPACK_DIS_MASK,DMIC_UNPACK_DIS)
#define __dmic_enable_sw_lr(dmic)\
        dmic_set_reg(dmic,DMICCR0,1,DMIC_SW_LR_MASK,DMIC_SW_LR)
#define __dmic_disable_sw_lr(dmic)\
        dmic_set_reg(dmic,DMICCR0,0,DMIC_SW_LR_MASK,DMIC_SW_LR)
#define __dmic_split(dmic)\
        dmic_set_reg(dmic,DMICCR0,1,DMIC_SPLIT_DI_MASK,DMIC_SPLIT_DI)
#define __dmic_enable_pack(dmic)\
        dmic_set_reg(dmic,DMICCR0,1,DMIC_PACK_EN_MASK,DMIC_PACK_EN)
#define __dmic_set_sr(dmic,n)\
        dmic_set_reg(dmic,DMICCR0,n,DMIC_SR_MASK,DMIC_SR)
#define __dmic_set_sr_8k(dmic)\
        __dmic_set_sr(dmic,0)
#define __dmic_set_sr_16k(dmic)\
        __dmic_set_sr(dmic,1)
#define __dmic_set_sr_48k(dmic)\
        __dmic_set_sr(dmic,2)
#define __dmic_enable_lp(dmic)\
        dmic_set_reg(dmic,DMICCR0,1,DMIC_LP_MODE_MASK,DMIC_LP_MODE)
#define __dmic_disable_lp(dmic)\
        dmic_set_reg(dmic,DMICCR0,0,DMIC_LP_MODE_MASK,DMIC_LP_MODE)
#define __dmic_enable_hpf1(dmic)\
        dmic_set_reg(dmic,DMICCR0,1,DMIC_HPF1_MODE_MASK,DMIC_HPF1_MODE)
#define __dmic_disable_hpf1(dmic)\
        dmic_set_reg(dmic,DMICCR0,0,DMIC_HPF1_MODE_MASK,DMIC_HPF1_MODE)
#define __dmic_is_enable_tri(dmic)\
        dmic_get_reg(dmic,DMICCR0,DMIC_TRI_EN_MASK,DMIC_TRI_EN)
#define __dmic_enable_tri(dmic)\
        dmic_set_reg(dmic,DMICCR0,1,DMIC_TRI_EN_MASK,DMIC_TRI_EN)
#define __dmic_disable_tri(dmic)\
        dmic_set_reg(dmic,DMICCR0,0,DMIC_TRI_EN_MASK,DMIC_TRI_EN)
#define __dmic_is_enable(dmic)\
        dmic_get_reg(dmic,DMICCR0,DMIC_EN_MASK,DMIC_EN)
#define __dmic_enable(dmic)\
        dmic_set_reg(dmic,DMICCR0,1,DMIC_EN_MASK,DMIC_EN)
#define __dmic_disable(dmic)\
        dmic_set_reg(dmic,DMICCR0,0,DMIC_EN_MASK,DMIC_EN)
/*DMICGCR*/
#define DMIC_GCR    0
#define DMIC_GCR_MASK   (0Xf << DMIC_GCR)
#define __dmic_set_gcr(dmic,n)\
        dmic_set_reg(dmic, DMICGCR, n, DMIC_GCR_MASK,DMIC_GCR)
/* DMICIMR */
#define DMIC_FIFO_TRIG_MASK 5
#define DMIC_FIFO_TRIG_MSK      (1 << DMIC_FIFO_TRIG_MASK)
#define DMIC_WAKE_MASK  4
#define DMIC_WAKE_MSK       (1 << DMIC_WAKE_MASK)
#define DMIC_EMPTY_MASK 3
#define DMIC_EMPTY_MSK      (1 << DMIC_EMPTY_MASK)
#define DMIC_FULL_MASK  2
#define DMIC_FULL_MSK       (1 << DMIC_FULL_MASK)
#define DMIC_PRERD_MASK 1
#define DMIC_PRERD_MSK      (1 << DMIC_PRERD_MASK)
#define DMIC_TRI_MASK   0
#define DMIC_TRI_MSK        (1 << DMIC_TRI_MASK)
#define __dmic_mask_all_int(dmic)\
    dmic_set_reg(dmic,DMICIMR, 0x3f, 0x3f, 0)
/*DMICINTCR*/
#define DMIC_FIFO_TRIG_FLAG 4
#define DMIC_FIFO_TRIG_FLAG_MASK        (1 << DMIC_WAKE_FLAG)
#define DMIC_WAKE_FLAG  4
#define DMIC_WAKE_FLAG_MASK     (1 << DMIC_WAKE_FLAG)
#define DMIC_EMPTY_FLAG 3
#define DMIC_EMPTY_FLAG_MASK    (1 << DMIC_EMPTY_FLAG)
#define DMIC_FULL_FLAG  2
#define DMIC_FULL_FLAG_MASK     (1 << DMIC_FULL_FLAG)
#define DMIC_PRERD_FLAG 1
#define DMIC_PRERD_FLAG_MASK    (1 << DMIC_PRERD_FLAG)
#define DMIC_TRI_FLAG   0
#define DMIC_TRI_FLAG_MASK      (1 << DMIC_TRI_FLAG)
/*DMICTRICR*/
#define DMIC_TRI_MODE   16
#define DMIC_TRI_MODE_MASK  (0xf << DMIC_TRI_MODE)
#define DMIC_TRI_DEBUG  4
#define DMIC_TRI_DEBUG_MASK (0x1 << DMIC_TRI_DEBUG)
#define DMIC_HPF2_EN    3
#define DMIC_HPF2_EN_MASK (0x1 << DMIC_HPF2_EN)
#define DMIC_PREFETCH   1
#define DMIC_PREFETCH_MASK  (0x3 << DMIC_PREFETCH)
#define DMIC_TRI_CLR    0
#define DMIC_TRI_CLR_MASK   (0x1 << DMIC_TRI_CLR)
#define __dmic_enable_hpf2(dmic) \
    dmic_set_reg(dmic, DMICTRICR, 1, DMIC_HPF2_EN_MASK, DMIC_HPF2_EN)
#define __dmic_disable_hpf2(dmic)    \
    dmic_set_reg(dmic, DMICTRICR, 0, DMIC_HPF2_EN_MASK, DMIC_HPF2_EN)
/*DMICTHRH*/
#define DMIC_THR_H 0
#define DMIC_THR_H_MASK (0xfffff << DMIC_THR_H)
#define __dmic_set_thr_high(dmic,n)  \
    dmic_set_reg(dmic, DMICTHRH, n, DMIC_THR_H_MASK, DMIC_THR_H)
/*DMICTHRL*/
#define DMIC_THR_L 0
#define DMIC_THR_L_MASK (0xfffff << DMIC_THR_L)
#define __dmic_set_thr_low(dmic,n)   \
    dmic_set_reg(dmic, DMICTHRL, n, DMIC_THR_L_MASK, DMIC_THR_L)
/* DMICTRIMMAX */
#define DMIC_M_MAX  0
#define DMIC_M_MAX_MASK (0xffffff << DMIC_M_MAX)
/* DMICTRINMAX */
#define DMIC_N_MAX  0
#define DMIC_N_MAX_MASK (0xffff << DMIC_N_MAX)
/* DMICFTHR */
#define DMIC_RDMS   31
#define DMIC_RDMS_MASK  (0x1 << DMIC_RDMS)
#define DMIC_FIFO_THR   0
#define DMIC_FIFO_THR_MASK  (0x3f << DMIC_FIFO_THR)
#define __dmic_is_enable_rdms(dmic)\
    dmic_get_reg(dmic, DMICFTHR,DMIC_RDMS_MASK,DMIC_RDMS)
#define __dmic_enable_rdms(dmic)\
    dmic_set_reg(dmic, DMICFTHR,1,DMIC_RDMS_MASK,DMIC_RDMS)
#define __dmic_disable_rdms(dmic)\
    dmic_set_reg(dmic, DMICFTHR,1,DMIC_RDMS_MASK,DMIC_RDMS)
#define __dmic_set_request(dmic,n)   \
    dmic_set_reg(dmic, DMICFTHR, n, DMIC_FIFO_THR_MASK, DMIC_FIFO_THR)
/*DMICFSR*/
#define DMIC_FULLS      19
#define DMIC_FULLS_MASK (0x1 << DMIC_FULLS)
#define DMIC_TRIGS      18
#define DMIC_TRIGS_MASK (0x1 << DMIC_TRIGS)
#define DMIC_PRERDS     17
#define DMIC_PRERDS_MASK    (0x1 << DMIC_PRERDS)
#define DMIC_EMPTYS     16
#define DMIC_EMPTYS_MASK    (0x1 << DMIC_EMPTYS)
#define DMIC_FIFO_LVL   0
#define DMIC_FIFO_LVL_MASK  (0x3f << DMIC_FIFO_LVL)
/*********************************************************************************************************
**
*********************************************************************************************************/
struct jz_dmic* rt_hw_dmic_init(void);
int jz_dmic_set_rate(struct jz_dmic*   dmic, int rate);
int jz_dmic_set_gain(struct jz_dmic*   dmic, int vol);
int jz_dmic_set_channels(struct jz_dmic*   dmic, int channels);

#endif /* _DRV_DMIC_H_ */
