/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-13     weety     first version
 */

/*
 * This EDMA3 programming framework exposes two basic kinds of resource:
 *
 *  Channel Triggers transfers, usually from a hardware event but
 *      also manually or by "chaining" from DMA completions.
 *      Each channel is coupled to a Parameter RAM (PaRAM) slot.
 *
 *  Slot    Each PaRAM slot holds a DMA transfer descriptor (PaRAM
 *      "set"), source and destination addresses, a link to a
 *      next PaRAM slot (if any), options for the transfer, and
 *      instructions for updating those addresses.  There are
 *      more than twice as many slots as event channels.
 *
 * Each PaRAM set describes a sequence of transfers, either for one large
 * buffer or for several discontiguous smaller buffers.  An EDMA transfer
 * is driven only from a channel, which performs the transfers specified
 * in its PaRAM slot until there are no more transfers.  When that last
 * transfer completes, the "link" field may be used to reload the channel's
 * PaRAM slot with a new transfer descriptor.
 *
 * The EDMA Channel Controller (CC) maps requests from channels into physical
 * Transfer Controller (TC) requests when the channel triggers (by hardware
 * or software events, or by chaining).  The two physical DMA channels provided
 * by the TCs are thus shared by many logical channels.
 *
 * DaVinci hardware also has a "QDMA" mechanism which is not currently
 * supported through this interface.  (DSP firmware uses it though.)
 */

#ifndef EDMA_H_
#define EDMA_H_

#include <rtthread.h>
#include <dm36x.h>

#ifdef RT_EDMA_DEBUG
#define edma_dbg(fmt, ...)  rt_kprintf(fmt, ##__VA_ARGS__)
#else
#define edma_dbg(fmt, ...)
#endif


/* PaRAM slots are laid out like this */
struct edmacc_param {
    unsigned int opt;
    unsigned int src;
    unsigned int a_b_cnt;
    unsigned int dst;
    unsigned int src_dst_bidx;
    unsigned int link_bcntrld;
    unsigned int src_dst_cidx;
    unsigned int ccnt;
};

#define CCINT0_INTERRUPT     16
#define CCERRINT_INTERRUPT   17
#define TCERRINT0_INTERRUPT   18
#define TCERRINT1_INTERRUPT   19

/* fields in edmacc_param.opt */
#define SAM     BIT(0)
#define DAM     BIT(1)
#define SYNCDIM     BIT(2)
#define STATIC      BIT(3)
#define EDMA_FWID   (0x07 << 8)
#define TCCMODE     BIT(11)
#define EDMA_TCC(t) ((t) << 12)
#define TCINTEN     BIT(20)
#define ITCINTEN    BIT(21)
#define TCCHEN      BIT(22)
#define ITCCHEN     BIT(23)

#define TRWORD (0x7<<2)
#define PAENTRY (0x1ff<<5)

/* DM365 specific EDMA3 Events Information */
enum dm365_edma_ch {
    DM365_DMA_TIMER3_TINT6,
    DM365_DMA_TIMER3_TINT7,
    DM365_DMA_MCBSP_TX = 2,
    DM365_DMA_VCIF_TX = 2,
    DM365_DMA_MCBSP_RX = 3,
    DM365_DMA_VCIF_RX = 3,
    DM365_DMA_VPSS_EVT1,
    DM365_DMA_VPSS_EVT2,
    DM365_DMA_VPSS_EVT3,
    DM365_DMA_VPSS_EVT4,
    DM365_DMA_TIMER2_TINT4,
    DM365_DMA_TIMER2_TINT5,
    DM365_DMA_SPI2XEVT,
    DM365_DMA_SPI2REVT,
    DM365_DMA_IMCOP_IMX0INT = 12,
    DM365_DMA_KALEIDO_ARMINT = 12,
    DM365_DMA_IMCOP_SEQINT,
    DM365_DMA_SPI1XEVT,
    DM365_DMA_SPI1REVT,
    DM365_DMA_SPI0XEVT,
    DM365_DMA_SPI0REVT,
    DM365_DMA_URXEVT0 = 18,
    DM365_DMA_SPI3XEVT = 18,
    DM365_DMA_UTXEVT0 = 19,
    DM365_DMA_SPI3REVT = 19,
    DM365_DMA_URXEVT1,
    DM365_DMA_UTXEVT1,
    DM365_DMA_TIMER4_TINT8,
    DM365_DMA_TIMER4_TINT9,
    DM365_DMA_RTOINT,
    DM365_DMA_GPIONT9,
    DM365_DMA_MMC0RXEVT = 26,
    DM365_DMA_MEMSTK_MSEVT = 26,
    DM365_DMA_MMC0TXEVT,
    DM365_DMA_I2C_ICREVT,
    DM365_DMA_I2C_ICXEVT,
    DM365_DMA_MMC1RXEVT,
    DM365_DMA_MMC1TXEVT,
    DM365_DMA_GPIOINT0,
    DM365_DMA_GPIOINT1,
    DM365_DMA_GPIOINT2,
    DM365_DMA_GPIOINT3,
    DM365_DMA_GPIOINT4,
    DM365_DMA_GPIOINT5,
    DM365_DMA_GPIOINT6,
    DM365_DMA_GPIOINT7,
    DM365_DMA_GPIOINT10 = 40,
    DM365_DMA_EMAC_RXTHREESH = 40,
    DM365_DMA_GPIOINT11 = 41,
    DM365_DMA_EMAC_RXPULSE = 41,
    DM365_DMA_GPIOINT12 = 42,
    DM365_DMA_EMAC_TXPULSE = 42,
    DM365_DMA_GPIOINT13 = 43,
    DM365_DMA_EMAC_MISCPULSE = 43,
    DM365_DMA_GPIOINT14 = 44,
    DM365_DMA_SPI4XEVT = 44,
    DM365_DMA_GPIOINT15 = 45,
    DM365_DMA_SPI4REVT = 45,
    DM365_DMA_ADC_ADINT,
    DM365_DMA_GPIOINT8,
    DM365_DMA_TIMER0_TINT0,
    DM365_DMA_TIMER0_TINT1,
    DM365_DMA_TIMER1_TINT2,
    DM365_DMA_TIMER1_TINT3,
    DM365_DMA_PWM0,
    DM365_DMA_PWM1 = 53,
    DM365_DMA_IMCOP_IMX1INT = 53,
    DM365_DMA_PWM2 = 54,
    DM365_DMA_IMCOP_NSFINT = 54,
    DM365_DMA_PWM3 = 55,
    DM365_DMA_KALEIDO6_CP_UNDEF = 55,
    DM365_DMA_IMCOP_VLCDINT = 56,
    DM365_DMA_KALEIDO5_CP_ECDCMP = 56,
    DM365_DMA_IMCOP_BIMINT = 57,
    DM365_DMA_KALEIDO8_CP_ME = 57,
    DM365_DMA_IMCOP_DCTINT = 58,
    DM365_DMA_KALEIDO1_CP_CALC = 58,
    DM365_DMA_IMCOP_QIQINT = 59,
    DM365_DMA_KALEIDO7_CP_IPE = 59,
    DM365_DMA_IMCOP_BPSINT = 60,
    DM365_DMA_KALEIDO2_CP_BS = 60,
    DM365_DMA_IMCOP_VLCDERRINT = 61,
    DM365_DMA_KALEIDO0_CP_LPF = 61,
    DM365_DMA_IMCOP_RCNTINT = 62,
    DM365_DMA_KALEIDO3_CP_MC = 62,
    DM365_DMA_IMCOP_COPCINT = 63,
    DM365_DMA_KALEIDO4_CP_ECDEND = 63,
};
/* end DM365 specific info */


/*ch_status paramater of callback function possible values*/
#define DMA_COMPLETE 1
#define DMA_CC_ERROR 2
#define DMA_TC1_ERROR 3
#define DMA_TC2_ERROR 4

enum address_mode {
    INCR = 0,
    FIFO = 1
};

enum fifo_width {
    W8BIT = 0,
    W16BIT = 1,
    W32BIT = 2,
    W64BIT = 3,
    W128BIT = 4,
    W256BIT = 5
};

enum dma_event_q {
    EVENTQ_0 = 0,
    EVENTQ_1 = 1,
    EVENTQ_2 = 2,
    EVENTQ_3 = 3,
    EVENTQ_DEFAULT = -1
};

enum sync_dimension {
    ASYNC = 0,
    ABSYNC = 1
};

#define EDMA_CTLR_CHAN(ctlr, chan)  (((ctlr) << 16) | (chan))
#define EDMA_CTLR(i)            ((i) >> 16)
#define EDMA_CHAN_SLOT(i)       ((i) & 0xffff)

#define EDMA_CHANNEL_ANY        -1  /* for edma_alloc_channel() */
#define EDMA_SLOT_ANY           -1  /* for edma_alloc_slot() */
#define EDMA_CONT_PARAMS_ANY         1001
#define EDMA_CONT_PARAMS_FIXED_EXACT     1002
#define EDMA_CONT_PARAMS_FIXED_NOT_EXACT 1003

#define EDMA_MAX_CC               2

/* alloc/free DMA channels and their dedicated parameter RAM slots */
int edma_alloc_channel(int channel,
    void (*callback)(unsigned channel, rt_uint16_t ch_status, void *data),
    void *data, enum dma_event_q);
void edma_free_channel(unsigned channel);

/* alloc/free parameter RAM slots */
int edma_alloc_slot(unsigned ctlr, int slot);
void edma_free_slot(unsigned slot);

/* alloc/free a set of contiguous parameter RAM slots */
int edma_alloc_cont_slots(unsigned ctlr, unsigned int id, int slot, int count);
int edma_free_cont_slots(unsigned slot, int count);

/* calls that operate on part of a parameter RAM slot */
void edma_set_src(unsigned slot, rt_uint32_t src_port,
                enum address_mode mode, enum fifo_width);
void edma_set_dest(unsigned slot, rt_uint32_t dest_port,
                 enum address_mode mode, enum fifo_width);
void edma_get_position(unsigned slot, rt_uint32_t *src, rt_uint32_t *dst);
void edma_set_src_index(unsigned slot, rt_int16_t src_bidx, rt_int16_t src_cidx);
void edma_set_dest_index(unsigned slot, rt_int16_t dest_bidx, rt_int16_t dest_cidx);
void edma_set_transfer_params(unsigned slot, rt_uint16_t acnt, rt_uint16_t bcnt, rt_uint16_t ccnt,
        rt_uint16_t bcnt_rld, enum sync_dimension sync_mode);
void edma_link(unsigned from, unsigned to);
void edma_unlink(unsigned from);

/* calls that operate on an entire parameter RAM slot */
void edma_write_slot(unsigned slot, const struct edmacc_param *params);
void edma_read_slot(unsigned slot, struct edmacc_param *params);

/* channel control operations */
int edma_start(unsigned channel);
void edma_stop(unsigned channel);
void edma_clean_channel(unsigned channel);
void edma_clear_event(unsigned channel);
void edma_pause(unsigned channel);
void edma_resume(unsigned channel);


struct edma_rsv_info {

    const rt_int16_t    (*rsv_chans)[2];
    const rt_int16_t    (*rsv_slots)[2];
};

/* platform_data for EDMA driver */
struct edma_soc_info {

    /* how many dma resources of each type */
    unsigned    n_channel;
    unsigned    n_region;
    unsigned    n_slot;
    unsigned    n_tc;
    unsigned    n_cc;
    enum dma_event_q    default_queue;

    /* Resource reservation for other cores */
    struct edma_rsv_info    *rsv;

    const rt_int8_t (*queue_tc_mapping)[2];
    const rt_int8_t (*queue_priority_mapping)[2];
};

int edma_init(struct edma_soc_info **info);


#endif
