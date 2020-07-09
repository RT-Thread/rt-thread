/*
 * File      : drv_dma.h
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


#ifndef _DRV_DMA_H_
#define _DRV_DMA_H_
#include <stdint.h>

#define NR_DMA_CHANNELS     8


#define CH_DSA  0x00
#define CH_DTA  0x04
#define CH_DTC  0x08
#define CH_DRT  0x0C
#define CH_DCS  0x10
#define CH_DCM  0x14
#define CH_DDA  0x18
#define CH_DSD  0x1C

#define TCSM    0x2000

#define DMAC    0x1000
#define DIRQP   0x1004
#define DESIRQP 0x1010
#define DIC     0x1014
#define DDR     0x1008
#define DDRS    0x100C
#define DMACP   0x101C
#define DSIRQP  0x1020
#define DSIRQM  0x1024
#define DCIRQP  0x1028
#define DCIRQM  0x102C

/* MCU of PDMA */
#define DMCS    0x1030
#define DMNMB   0x1034
#define DMSMB   0x1038
#define DMINT   0x103C

/* MCU of PDMA */
#define DMINT_S_IP      BIT(17)
#define DMINT_N_IP      BIT(16)

#define DMAC_HLT    BIT(3)
#define DMAC_AR     BIT(2)

#define DCS_NDES    BIT(31)
#define DCS_AR      BIT(4)
#define DCS_TT      BIT(3)
#define DCS_HLT     BIT(2)
#define DCS_CTE     BIT(0)

#define DCM_SAI     BIT(23)
#define DCM_DAI     BIT(22)
#define DCM_SP_MSK  (0x3 << 14)
#define DCM_SP_32   DCM_SP_MSK
#define DCM_SP_16   BIT(15)
#define DCM_SP_8    BIT(14)
#define DCM_DP_MSK  (0x3 << 12)
#define DCM_DP_32   DCM_DP_MSK
#define DCM_DP_16   BIT(13)
#define DCM_DP_8    BIT(12)
#define DCM_TSZ_MSK (0x7 << 8)
#define DCM_TSZ_SHF 8
#define DCM_STDE    BIT(2)
#define DCM_TIE     BIT(1)
#define DCM_LINK    BIT(0)

#define DCM_CH1_SRC_TCSM    (0x0 << 26)
#define DCM_CH1_SRC_NEMC    (0x1 << 26)
#define DCM_CH1_SRC_DDR     (0x2 << 26)

#define DCM_CH1_DST_TCSM    (0x0 << 24)
#define DCM_CH1_DST_NEMC    (0x1 << 24)
#define DCM_CH1_DST_DDR     (0x2 << 24)

#define DCM_CH1_DDR_TO_NAND  (DCM_CH1_SRC_DDR  | DCM_CH1_DST_NEMC)
#define DCM_CH1_NAND_TO_DDR  (DCM_CH1_SRC_NEMC | DCM_CH1_DST_DDR)

#define DCM_CH1_TCSM_TO_NAND (DCM_CH1_SRC_TCSM | DCM_CH1_DST_NEMC)
#define DCM_CH1_NAND_TO_TCSM (DCM_CH1_SRC_NEMC | DCM_CH1_DST_TCSM)

#define DCM_CH1_TCSM_TO_DDR  (DCM_CH1_SRC_TCSM | DCM_CH1_DST_DDR)
#define DCM_CH1_DDR_TO_TCSM  (DCM_CH1_SRC_DDR  | DCM_CH1_DST_TCSM)

#define MCU_MSG_TYPE_NORMAL 0x1
#define MCU_MSG_TYPE_INTC   0x2
#define MCU_MSG_TYPE_INTC_MASKA 0x3

enum jzdma_req_type {
#define _RTP(NAME) JZDMA_REQ_##NAME##_TX,JZDMA_REQ_##NAME##_RX
    JZDMA_REQ_RESERVED0 = 0x03,
    _RTP(DMIC),
    _RTP(I2S0),
    JZDMA_REQ_AUTO_TXRX = 0x08,
    JZDMA_REQ_SADC_RX,
    JZDMA_REQ_RESERVED1 = 0x0b,
    _RTP(UART4),
    _RTP(UART3),
    _RTP(UART2),
    _RTP(UART1),
    _RTP(UART0),
    _RTP(SSI0),
    _RTP(SSI1),
    _RTP(MSC0),
    _RTP(MSC1),
    _RTP(MSC2),
    _RTP(PCM0),
    _RTP(PCM1),
    _RTP(I2C0),
    _RTP(I2C1),
    _RTP(I2C2),
    _RTP(I2C3),
    _RTP(I2C4),
    _RTP(DES),
#undef _RTP
};

enum jzdma_type {
    JZDMA_REQ_INVAL = 0,
#define _RTP(NAME) JZDMA_REQ_##NAME = JZDMA_REQ_##NAME##_TX
    _RTP(DMIC),
    _RTP(I2S0),
    JZDMA_REQ_AUTO = JZDMA_REQ_AUTO_TXRX,
    JZDMA_REQ_SADC = JZDMA_REQ_SADC_RX,
    _RTP(UART4),
    _RTP(UART3),
    _RTP(UART2),
    _RTP(UART1),
    _RTP(UART0),
    _RTP(SSI0),
    _RTP(SSI1),
    _RTP(MSC0),
    _RTP(MSC1),
    _RTP(MSC2),
    _RTP(PCM0),
    _RTP(PCM1),
    _RTP(I2C0),
    _RTP(I2C1),
    _RTP(I2C2),
    _RTP(I2C3),
    _RTP(I2C4),
    _RTP(DES),
    JZDMA_REQ_NAND0 = JZDMA_REQ_AUTO_TXRX | (1 << 16),
    JZDMA_REQ_NAND1 = JZDMA_REQ_AUTO_TXRX | (2 << 16),
    JZDMA_REQ_NAND2 = JZDMA_REQ_AUTO_TXRX | (3 << 16),
    JZDMA_REQ_NAND3 = JZDMA_REQ_AUTO_TXRX | (4 << 16),
    JZDMA_REQ_NAND4 = JZDMA_REQ_AUTO_TXRX | (5 << 16),
    TYPE_MASK = 0xffff,
#undef _RTP
};

#define GET_MAP_TYPE(type) (type & (TYPE_MASK))


enum channel_status
{
    STAT_STOPED,STAT_SUBED,STAT_PREPED,STAT_RUNNING,
};

struct jzdma_desc
{
    uint32_t    dcm;
    uint32_t    dsa;
    uint32_t    dta;
    uint32_t    dtc;
    uint32_t    sd;
    uint32_t    drt;
    uint32_t    reserved[2];
};

struct jzdma_channel
{
//    int         id;
    uint32_t    iomem;
    uint32_t    dcs_saved;
    uint32_t    dcm_def;

    enum jzdma_type             type;
    enum channel_status         status;

    //´«Êä¿ØÖÆÃèÊö·û
    struct jzdma_desc           desc;
    uint32_t    desc_nr;

//    struct  rt_dma_channel      *parant;
};

struct jzdma_master
{
    uint32_t    base;
    struct clk  *clk;
    int         irq;
    int         irq_pdmad;   /* irq_pdmad for PDMA_DESC irq */

    struct jzdma_channel    channel[NR_DMA_CHANNELS];
};


extern struct rt_dma_funcs _g_jzdma_funcs;

#endif /* _DRV_DMA_H_ */
