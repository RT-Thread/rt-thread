/*
 * Copyright (c) 2001-2002 by David Brownell
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __LINUX_EHCI_HCD_H
#define __LINUX_EHCI_HCD_H


/* definitions used for the EHCI driver */
#include <usb_gen_hcd.h>
#include <usb_os_platform.h>
#include <ehci_def.h>
#include <hal_osal.h>

#define __hc32      uint32_t

#define ehci_readl(a, addr)     readl(addr)
#define ehci_writel(a, val, addr)   writel(val, addr)

#define INTR_MASK (STS_IAA | STS_FATAL | STS_PCD | STS_ERR | STS_INT)
#define PORT_WAKE_BITS  (PORT_WKOC_E|PORT_WKDISC_E|PORT_WKCONN_E)

struct ehci_stats {
    /* irq usage */
    unsigned long       normal;
    unsigned long       error;
    unsigned long       iaa;
    unsigned long       lost_iaa;

    /* termination of urbs from core */
    unsigned long       complete;
    unsigned long       unlink;
};

/*
 * Scheduling and budgeting information for periodic transfers, for both
 * high-speed devices and full/low-speed devices lying behind a TT.
 */
struct ehci_per_sched {
    //struct usb_device *udev;      /* access to the TT */
    struct usb_host_virt_dev *udev;     /* access to the TT */
    //struct usb_host_endpoint *ep;
    struct usb_host_virt_endpoint *ep;
    struct list_head    ps_list;    /* node on ehci_tt's ps_list */
    u16         tt_usecs;   /* time on the FS/LS bus */
    u16         cs_mask;    /* C-mask and S-mask bytes */
    u16         period;     /* actual period in frames */
    u16         phase;      /* actual phase, frame part */
    u8          bw_phase;   /* same, for bandwidth
                           reservation */
    u8          phase_uf;   /* uframe part of the phase */
    u8          usecs, c_usecs; /* times on the HS bus */
    u8          bw_uperiod; /* period in microframes, for
                           bandwidth reservation */
    u8          bw_period;  /* same, in frames */
};
#define NO_FRAME    29999           /* frame not assigned yet */

/* ehci_hcd->lock guards shared data against other CPUs:
 *   ehci_hcd:  async, unlink, periodic (and shadow), ...
 *   usb_host_endpoint: hcpriv
 *   ehci_qh:   qh_next, qtd_list
 *   ehci_qtd:  qtd_list
 *
 * Also, hold this lock when talking to HC registers or
 * when updating hw_* fields in shared qh/qtd/... structures.
 */

#define EHCI_MAX_ROOT_PORTS 15      /* see HCS_N_PORTS */

/*
 * ehci_rh_state values of EHCI_RH_RUNNING or above mean that the
 * controller may be doing DMA.  Lower values mean there's no DMA.
 */
enum ehci_rh_state {
    EHCI_RH_HALTED,
    EHCI_RH_SUSPENDED,
    EHCI_RH_RUNNING,
    EHCI_RH_STOPPING
};

/*
 * Timer events, ordered by increasing delay length.
 * Always update event_delays_ns[] and event_handlers[] (defined in
 * ehci-timer.c) in parallel with this list.
 */
enum ehci_hrtimer_event {
    EHCI_HRTIMER_POLL_ASS,      /* Poll for async schedule off */
    EHCI_HRTIMER_POLL_PSS,      /* Poll for periodic schedule off */
    EHCI_HRTIMER_POLL_DEAD,     /* Wait for dead controller to stop */
    EHCI_HRTIMER_UNLINK_INTR,   /* Wait for interrupt QH unlink */
    EHCI_HRTIMER_FREE_ITDS,     /* Wait for unused iTDs and siTDs */
    EHCI_HRTIMER_ACTIVE_UNLINK, /* Wait while unlinking an active QH */
    EHCI_HRTIMER_START_UNLINK_INTR, /* Unlink empty interrupt QHs */
    EHCI_HRTIMER_ASYNC_UNLINKS, /* Unlink empty async QHs */
    EHCI_HRTIMER_IAA_WATCHDOG,  /* Handle lost IAA interrupts */
    EHCI_HRTIMER_DISABLE_PERIODIC,  /* Wait to disable periodic sched */
    EHCI_HRTIMER_DISABLE_ASYNC, /* Wait to disable async sched */
    EHCI_HRTIMER_IO_WATCHDOG,   /* Check for missing IRQs */
    EHCI_HRTIMER_NUM_EVENTS     /* Must come last */
};
#define EHCI_HRTIMER_NO_EVENT   99

struct ehci_hcd {           /* one per controller */
    /* timing support */
    enum ehci_hrtimer_event next_hrtimer_event;
    unsigned                enabled_hrtimer_events;
    unsigned long           hr_timeouts[EHCI_HRTIMER_NUM_EVENTS];
    osal_timer_t            hrtimer;

    int         PSS_poll_count;
    int         ASS_poll_count;
    int         died_poll_count;

    /* glue to PCI and HCD framework */
    struct ehci_caps *caps;
    struct ehci_regs *regs;
    //struct ehci_dbg_port __iomem *debug;

    uint32_t        hcs_params; /* cached register copy */
    hal_spinlock_t          lock;
    enum ehci_rh_state  rh_state;

    /* general schedule support */
    bool            scanning:1;
    bool            need_rescan:1;
    bool            intr_unlinking:1;
    bool            iaa_in_progress:1;
    bool            async_unlinking:1;
    bool            shutdown:1;
    struct ehci_qh      *qh_scan_next;

    /* async schedule support */
    struct ehci_qh      *async;
    struct ehci_qh      *dummy;     /* For AMD quirk use */
    struct list_head    async_unlink;
    struct list_head    async_idle;
    struct list_head    wait_free_list; /* akira 20202020 */
    unsigned        async_unlink_cycle;
    unsigned        async_count;    /* async activity count */
    uint32_t        old_current;    /* Test for QH becoming */
    uint32_t        old_token;  /*  inactive during unlink */

    /* periodic schedule support */
#define DEFAULT_I_TDPS      1024        /* some HCs can do less */
    unsigned        periodic_size;
    uint32_t            *periodic;  /* hw periodic table */
    uint32_t        periodic_dma;
    struct list_head    intr_qh_list;
    unsigned        i_thresh;   /* uframes HC might cache */

    union ehci_shadow   *pshadow;   /* mirror hw periodic table */
    struct list_head    intr_unlink_wait;
    struct list_head    intr_unlink;
    unsigned        intr_unlink_wait_cycle;
    unsigned        intr_unlink_cycle;
    unsigned        now_frame;  /* frame from HC hardware */
    unsigned        last_iso_frame; /* last frame scanned for iso */
    unsigned        intr_count; /* intr activity count */
    unsigned        isoc_count; /* isoc activity count */
    unsigned        periodic_count; /* periodic activity count */
    unsigned        uframe_periodic_max; /* max periodic time per uframe */


    /* list of itds & sitds completed while now_frame was still active */
    struct list_head    cached_itd_list;
    struct ehci_itd     *last_itd_to_free;
    struct list_head    cached_sitd_list;
    struct ehci_sitd    *last_sitd_to_free;

    /* per root hub port */
    unsigned long       reset_done[EHCI_MAX_ROOT_PORTS];

    /* bit vectors (one bit per port) */
    unsigned long       bus_suspended;      /* which ports were
            already suspended at the start of a bus suspend */
    unsigned long       companion_ports;    /* which ports are
            dedicated to the companion controller */
    unsigned long       owned_ports;        /* which ports are
            owned by the companion during a bus suspend */
    unsigned long       port_c_suspend;     /* which ports have
            the change-suspend feature turned on */
    unsigned long       suspended_ports;    /* which ports are
            suspended */
    unsigned long       resuming_ports;     /* which ports have
            started to resume */

    /* per-HC memory pools (could be per-bus, but ...) */
    struct dma_pool     *qh_pool;   /* qh per active urb */
    struct dma_pool     *qtd_pool;  /* one or more per qh */
    struct dma_pool     *itd_pool;  /* itd per iso urb */
    struct dma_pool     *sitd_pool; /* sitd per split iso urb */

    unsigned        random_frame;
    uint32_t        command;

    /* SILICON QUIRKS */
    unsigned        no_selective_suspend:1;
    unsigned        has_fsl_port_bug:1; /* FreeScale */
    unsigned        has_fsl_hs_errata:1;    /* Freescale HS quirk */
    unsigned        big_endian_mmio:1;
    unsigned        big_endian_desc:1;
    unsigned        big_endian_capbase:1;
    unsigned        has_amcc_usb23:1;
    unsigned        need_io_watchdog:1;
    unsigned        amd_pll_fix:1;
    unsigned        use_dummy_qh:1; /* AMD Frame List table quirk*/
    unsigned        has_synopsys_hc_bug:1; /* Synopsys HC */
    unsigned        frame_index_bug:1; /* MosChip (AKA NetMos) */
    unsigned        need_oc_pp_cycle:1; /* MPC834X port power */
    unsigned        imx28_write_fix:1; /* For Freescale i.MX28 */

    /* required for usb32 quirk */
    #define OHCI_CTRL_HCFS          (3 << 6)
    #define OHCI_USB_OPER           (2 << 6)
    #define OHCI_USB_SUSPEND        (3 << 6)

    #define OHCI_HCCTRL_OFFSET      0x4
    #define OHCI_HCCTRL_LEN         0x4
    uint32_t        *ohci_hcctrl_reg;
    unsigned        has_hostpc:1;
    unsigned        has_tdi_phy_lpm:1;
    unsigned        has_ppcd:1; /* support per-port change bits */
    uint8_t         sbrn;       /* packed release number */

    /* irq statistics */
#ifdef EHCI_STATS
    struct ehci_stats   stats;
#   define COUNT(x) ((x)++)
#else
#   define COUNT(x)
#endif

    /* debug files */
#ifdef CONFIG_DYNAMIC_DEBUG
    struct dentry       *debug_dir;
#endif

    /* bandwidth usage */
#define EHCI_BANDWIDTH_SIZE 64
#define EHCI_BANDWIDTH_FRAMES   (EHCI_BANDWIDTH_SIZE >> 3)
    u8          bandwidth[EHCI_BANDWIDTH_SIZE];
                        /* us allocated per uframe */
    u8          tt_budget[EHCI_BANDWIDTH_SIZE];
                        /* us budgeted per uframe */
    struct list_head    tt_list;

    /* platform-specific data -- must come last */
    unsigned long       priv[0];
};

/* convert between an HCD pointer and the corresponding EHCI_HCD */
#if 0
static inline struct ehci_hcd *hcd_to_ehci(struct usb_hcd *hcd)
{
    return (struct ehci_hcd *) (hcd->hcd_priv);
}
#endif

static inline struct hc_gen_dev *ehci_to_hcd(struct ehci_hcd *ehci)
{
    return container_of((void *) ehci, struct hc_gen_dev, hcd_priv);
}
static inline struct ehci_hcd *hcd_to_ehci(struct hc_gen_dev *hcd)
{
    return (struct ehci_hcd *) (hcd->hcd_priv);
}

/*-------------------------------------------------------------------------*/

//#include <linux/usb/ehci_def.h>

/*-------------------------------------------------------------------------*/

#define QTD_NEXT(ehci, dma) cpu_to_hc32(ehci, (u32)dma)

/*
 * EHCI Specification 0.95 Section 3.5
 * QTD: describe data transfer components (buffer, direction, ...)
 * See Fig 3-6 "Queue Element Transfer Descriptor Block Diagram".
 *
 * These are associated only with "QH" (Queue Head) structures,
 * used with control, bulk, and interrupt transfers.
 */
struct ehci_qtd {
    /* first part defined by EHCI spec */
    uint32_t            hw_next;    /* see EHCI 3.5.1 */
    uint32_t            hw_alt_next;    /* see EHCI 3.5.2 */
    uint32_t            hw_token;       /* see EHCI 3.5.3 */
#define QTD_TOGGLE  (1 << 31)   /* data toggle */
#define QTD_LENGTH(tok) (((tok)>>16) & 0x7fff)
#define QTD_IOC     (1 << 15)   /* interrupt on complete */
#define QTD_CERR(tok)   (((tok)>>10) & 0x3)
#define QTD_PID(tok)    (((tok)>>8) & 0x3)
#define QTD_STS_ACTIVE  (1 << 7)    /* HC may execute this */
#define QTD_STS_HALT    (1 << 6)    /* halted on error */
#define QTD_STS_DBE (1 << 5)    /* data buffer error (in HC) */
#define QTD_STS_BABBLE  (1 << 4)    /* device was babbling (qtd halted) */
#define QTD_STS_XACT    (1 << 3)    /* device gave illegal response */
#define QTD_STS_MMF (1 << 2)    /* incomplete split transaction */
#define QTD_STS_STS (1 << 1)    /* split transaction state */
#define QTD_STS_PING    (1 << 0)    /* issue PING? */

#define ACTIVE_BIT(ehci)    cpu_to_hc32(ehci, QTD_STS_ACTIVE)
#define HALT_BIT(ehci)      cpu_to_hc32(ehci, QTD_STS_HALT)
#define STATUS_BIT(ehci)    cpu_to_hc32(ehci, QTD_STS_STS)

    uint32_t            hw_buf[5];        /* see EHCI 3.5.4 */
    uint32_t            hw_buf_hi[5];        /* Appendix B */

    /* the rest is HCD-private */
    dma_addr_t      qtd_dma;        /* qtd address */
    struct list_head    qtd_list;       /* sw qtd list */
    struct urb      *urb;           /* qtd's urb */
    size_t          length;         /* length of buffer */
} __aligned(32);

/* mask NakCnt+T in qh->hw_alt_next */
#define QTD_MASK(ehci)  cpu_to_hc32(ehci, ~0x1f)

#define IS_SHORT_READ(token) (QTD_LENGTH(token) != 0 && QTD_PID(token) == 1)

/*-------------------------------------------------------------------------*/

/* type tag from {qh,itd,sitd,fstn}->hw_next */
#define Q_NEXT_TYPE(ehci, dma)  ((dma) & cpu_to_hc32(ehci, 3 << 1))

/*
 * Now the following defines are not converted using the
 * cpu_to_le32() macro anymore, since we have to support
 * "dynamic" switching between be and le support, so that the driver
 * can be used on one system with SoC EHCI controller using big-endian
 * descriptors as well as a normal little-endian PCI EHCI controller.
 */
/* values for that type tag */
#define Q_TYPE_ITD  (0 << 1)
#define Q_TYPE_QH   (1 << 1)
#define Q_TYPE_SITD (2 << 1)
#define Q_TYPE_FSTN (3 << 1)

/* next async queue entry, or pointer to interrupt/periodic QH */
#define QH_NEXT(ehci, dma) \
        (cpu_to_hc32(ehci, (((u32) dma) & ~0x01f) | Q_TYPE_QH))

/* for periodic/async schedules and qtd lists, mark end of list */
#define EHCI_LIST_END(ehci) cpu_to_hc32(ehci, 1) /* "null pointer" to hw */

/*
 * Entries in periodic shadow table are pointers to one of four kinds
 * of data structure.  That's dictated by the hardware; a type tag is
 * encoded in the low bits of the hardware's periodic schedule.  Use
 * Q_NEXT_TYPE to get the tag.
 *
 * For entries in the async schedule, the type tag always says "qh".
 */
union ehci_shadow {
    struct ehci_qh      *qh;        /* Q_TYPE_QH */
    struct ehci_itd     *itd;       /* Q_TYPE_ITD */
    struct ehci_sitd    *sitd;      /* Q_TYPE_SITD */
    struct ehci_fstn    *fstn;      /* Q_TYPE_FSTN */
    uint32_t            *hw_next;   /* (all types) */
    void            *ptr;
};

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specification 0.95 Section 3.6
 * QH: describes control/bulk/interrupt endpoints
 * See Fig 3-7 "Queue Head Structure Layout".
 *
 * These appear in both the async and (for interrupt) periodic schedules.
 */

/* first part defined by EHCI spec */
struct ehci_qh_hw {
    uint32_t            hw_next;    /* see EHCI 3.6.1 */
    uint32_t            hw_info1;       /* see EHCI 3.6.2 */
#define QH_CONTROL_EP   (1 << 27)   /* FS/LS control endpoint */
#define QH_HEAD     (1 << 15)   /* Head of async reclamation list */
#define QH_TOGGLE_CTL   (1 << 14)   /* Data toggle control */
#define QH_HIGH_SPEED   (2 << 12)   /* Endpoint speed */
#define QH_LOW_SPEED    (1 << 12)
#define QH_FULL_SPEED   (0 << 12)
#define QH_INACTIVATE   (1 << 7)    /* Inactivate on next transaction */
    uint32_t            hw_info2;        /* see EHCI 3.6.2 */
#define QH_SMASK    0x000000ff
#define QH_CMASK    0x0000ff00
#define QH_HUBADDR  0x007f0000
#define QH_HUBPORT  0x3f800000
#define QH_MULT     0xc0000000
    uint32_t            hw_current; /* qtd list - see EHCI 3.6.4 */

    /* qtd overlay (hardware parts of a struct ehci_qtd) */
    uint32_t            hw_qtd_next;
    uint32_t            hw_alt_next;
    uint32_t            hw_token;
    uint32_t            hw_buf[5];
    uint32_t            hw_buf_hi[5];
} __aligned(32);

struct ehci_qh {
    struct ehci_qh_hw   *hw;        /* Must come first */
    /* the rest is HCD-private */
    dma_addr_t      qh_dma;     /* address of qh */
    union ehci_shadow   qh_next;    /* ptr to qh; or periodic */
    struct list_head    qtd_list;   /* sw qtd list */
    struct list_head    intr_node;  /* list of intr QHs */
    struct ehci_qtd     *dummy;
    struct list_head    unlink_node;
    struct ehci_per_sched   ps;     /* scheduling info */

    unsigned        unlink_cycle;

    u8          qh_state;
#define QH_STATE_LINKED     1       /* HC sees this */
#define QH_STATE_UNLINK     2       /* HC may still see this */
#define QH_STATE_IDLE       3       /* HC doesn't see this */
#define QH_STATE_UNLINK_WAIT    4       /* LINKED and on unlink q */
#define QH_STATE_COMPLETING 5       /* don't touch token.HALT */

    u8          xacterrs;   /* XactErr retry counter */
#define QH_XACTERR_MAX      32      /* XactErr retry limit */

    u8          unlink_reason;
#define QH_UNLINK_HALTED    0x01        /* Halt flag is set */
#define QH_UNLINK_SHORT_READ    0x02        /* Recover from a short read */
#define QH_UNLINK_DUMMY_OVERLAY 0x04        /* QH overlayed the dummy TD */
#define QH_UNLINK_SHUTDOWN  0x08        /* The HC isn't running */
#define QH_UNLINK_QUEUE_EMPTY   0x10        /* Reached end of the queue */
#define QH_UNLINK_REQUESTED 0x20        /* Disable, reset, or dequeue */

    u8          gap_uf;     /* uframes split/csplit gap */

    unsigned        is_out:1;   /* bulk or intr OUT */
    unsigned        clearing_tt:1;  /* Clear-TT-Buf in progress */
    unsigned        dequeue_during_giveback:1;
    unsigned        should_be_inactive:1;
};

/*-------------------------------------------------------------------------*/

/* description of one iso transaction (up to 3 KB data if highspeed) */
struct ehci_iso_packet {
    /* These will be copied to iTD when scheduling */
    u64         bufp;       /* itd->hw_bufp{,_hi}[pg] |= */
    uint32_t            transaction;    /* itd->hw_transaction[i] |= */
    u8          cross;      /* buf crosses pages */
    /* for full speed OUT splits */
    u32         buf1;
};

/* temporary schedule data for packets from iso urbs (both speeds)
 * each packet is one logical usb transaction to the device (not TT),
 * beginning at stream->next_uframe
 */
struct ehci_iso_sched {
    struct list_head    td_list;
    unsigned        span;
    unsigned        first_packet;
    struct ehci_iso_packet  packet[0];
};

/*
 * ehci_iso_stream - groups all (s)itds for this endpoint.
 * acts like a qh would, if EHCI had them for ISO.
 */
struct ehci_iso_stream {
    /* first field matches ehci_hq, but is NULL */
    struct ehci_qh_hw   *hw;

    u8          bEndpointAddress;
    u8          highspeed;
    struct list_head    td_list;    /* queued itds/sitds */
    struct list_head    free_list;  /* list of unused itds/sitds */

    /* output of (re)scheduling */
    struct ehci_per_sched   ps;     /* scheduling info */
    unsigned        next_uframe;
    uint32_t            splits;

    /* the rest is derived from the endpoint descriptor,
     * including the extra info for hw_bufp[0..2]
     */
    u16         uperiod;    /* period in uframes */
    u16         maxp;
    unsigned        bandwidth;

    /* This is used to initialize iTD's hw_bufp fields */
    uint32_t            buf0;
    uint32_t            buf1;
    uint32_t            buf2;

    /* this is used to initialize sITD's tt info */
    uint32_t            address;
};

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specification 0.95 Section 3.3
 * Fig 3-4 "Isochronous Transaction Descriptor (iTD)"
 *
 * Schedule records for high speed iso xfers
 */
struct ehci_itd {
    /* first part defined by EHCI spec */
    uint32_t            hw_next;           /* see EHCI 3.3.1 */
    uint32_t            hw_transaction[8]; /* see EHCI 3.3.2 */
#define EHCI_ISOC_ACTIVE        (1<<31)        /* activate transfer this slot */
#define EHCI_ISOC_BUF_ERR       (1<<30)        /* Data buffer error */
#define EHCI_ISOC_BABBLE        (1<<29)        /* babble detected */
#define EHCI_ISOC_XACTERR       (1<<28)        /* XactErr - transaction error */
#define EHCI_ITD_LENGTH(tok)    (((tok)>>16) & 0x0fff)
#define EHCI_ITD_IOC        (1 << 15)   /* interrupt on complete */

#define ITD_ACTIVE(ehci)    cpu_to_hc32(ehci, EHCI_ISOC_ACTIVE)

    uint32_t            hw_bufp[7]; /* see EHCI 3.3.3 */
    uint32_t            hw_bufp_hi[7];  /* Appendix B */

    /* the rest is HCD-private */
    uint32_t        itd_dma;    /* for this itd */
    union ehci_shadow   itd_next;   /* ptr to periodic q entry */

    struct urb      *urb;
    struct ehci_iso_stream  *stream;    /* endpoint's queue */
    struct list_head    itd_list;   /* list of stream's itds */

    /* any/all hw_transactions here may be used by that urb */
    unsigned        frame;      /* where scheduled */
    unsigned        pg;
    unsigned        index[8];   /* in urb->iso_frame_desc */
} __aligned(32);

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specification 0.95 Section 3.4
 * siTD, aka split-transaction isochronous Transfer Descriptor
 *       ... describe full speed iso xfers through TT in hubs
 * see Figure 3-5 "Split-transaction Isochronous Transaction Descriptor (siTD)
 */
struct ehci_sitd {
    /* first part defined by EHCI spec */
    uint32_t            hw_next;
/* uses bit field macros above - see EHCI 0.95 Table 3-8 */
    uint32_t            hw_fullspeed_ep;    /* EHCI table 3-9 */
    uint32_t            hw_uframe;      /* EHCI table 3-10 */
    uint32_t            hw_results;     /* EHCI table 3-11 */
#define SITD_IOC    (1 << 31)   /* interrupt on completion */
#define SITD_PAGE   (1 << 30)   /* buffer 0/1 */
#define SITD_LENGTH(x)  (((x) >> 16) & 0x3ff)
#define SITD_STS_ACTIVE (1 << 7)    /* HC may execute this */
#define SITD_STS_ERR    (1 << 6)    /* error from TT */
#define SITD_STS_DBE    (1 << 5)    /* data buffer error (in HC) */
#define SITD_STS_BABBLE (1 << 4)    /* device was babbling */
#define SITD_STS_XACT   (1 << 3)    /* illegal IN response */
#define SITD_STS_MMF    (1 << 2)    /* incomplete split transaction */
#define SITD_STS_STS    (1 << 1)    /* split transaction state */

#define SITD_ACTIVE(ehci)   cpu_to_hc32(ehci, SITD_STS_ACTIVE)

    uint32_t            hw_buf[2];      /* EHCI table 3-12 */
    uint32_t            hw_backpointer;     /* EHCI table 3-13 */
    uint32_t            hw_buf_hi[2];       /* Appendix B */

    /* the rest is HCD-private */
    uint32_t        sitd_dma;
    union ehci_shadow   sitd_next;  /* ptr to periodic q entry */

    struct urb      *urb;
    struct ehci_iso_stream  *stream;    /* endpoint's queue */
    struct list_head    sitd_list;  /* list of stream's sitds */
    unsigned        frame;
    unsigned        index;
} __aligned(32);

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specification 0.96 Section 3.7
 * Periodic Frame Span Traversal Node (FSTN)
 *
 * Manages split interrupt transactions (using TT) that span frame boundaries
 * into uframes 0/1; see 4.12.2.2.  In those uframes, a "save place" FSTN
 * makes the HC jump (back) to a QH to scan for fs/ls QH completions until
 * it hits a "restore" FSTN; then it returns to finish other uframe 0/1 work.
 */
struct ehci_fstn {
    uint32_t            hw_next;    /* any periodic q entry */
    uint32_t            hw_prev;    /* qh or EHCI_LIST_END */

    /* the rest is HCD-private */
    uint32_t        fstn_dma;
    union ehci_shadow   fstn_next;  /* ptr to periodic q entry */
} __aligned(32);

/*-------------------------------------------------------------------------*/

/*
 * USB-2.0 Specification Sections 11.14 and 11.18
 * Scheduling and budgeting split transactions using TTs
 *
 * A hub can have a single TT for all its ports, or multiple TTs (one for each
 * port).  The bandwidth and budgeting information for the full/low-speed bus
 * below each TT is self-contained and independent of the other TTs or the
 * high-speed bus.
 *
 * "Bandwidth" refers to the number of microseconds on the FS/LS bus allocated
 * to an interrupt or isochronous endpoint for each frame.  "Budget" refers to
 * the best-case estimate of the number of full-speed bytes allocated to an
 * endpoint for each microframe within an allocated frame.
 *
 * Removal of an endpoint invalidates a TT's budget.  Instead of trying to
 * keep an up-to-date record, we recompute the budget when it is needed.
 */

struct ehci_tt {
    u16         bandwidth[EHCI_BANDWIDTH_FRAMES];

    struct list_head    tt_list;    /* List of all ehci_tt's */
    struct list_head    ps_list;    /* Items using this TT */
    struct usb_tt       *usb_tt;
    int         tt_port;    /* TT port number */
};

/*-------------------------------------------------------------------------*/

/* Prepare the PORTSC wakeup flags during controller suspend/resume */

#define ehci_prepare_ports_for_controller_suspend(ehci, do_wakeup)  \
        ehci_adjust_port_wakeup_flags(ehci, true, do_wakeup)

#define ehci_prepare_ports_for_controller_resume(ehci)          \
        ehci_adjust_port_wakeup_flags(ehci, false, false)

//#define   ehci_is_TDI(e)          (ehci_to_hcd(e)->has_tt)
//static inline unsigned int
//ehci_port_speed(struct ehci_hcd *ehci, unsigned int portsc)
//{
//  if (ehci_is_TDI(ehci)) {
//      switch ((portsc >> (ehci->has_hostpc ? 25 : 26)) & 3) {
//      case 0:
//          return 0;
//      case 1:
//          return USB_PORT_STAT_LOW_SPEED;
//      case 2:
//      default:
//          return USB_PORT_STAT_HIGH_SPEED;
//      }
//  }
//  return USB_PORT_STAT_HIGH_SPEED;
//}
#define ehci_is_TDI(e)          (0)
//
#define ehci_port_speed(ehci, portsc)   USB_PORT_STAT_HIGH_SPEED
//#endif
/*-------------------------------------------------------------------------*/

#define ehci_has_fsl_portno_bug(e)      (0)

#define PORTSC_FSL_PFSC 24  /* Port Force Full-Speed Connect */

#define ehci_has_fsl_hs_errata(e)   (0)
/*
 * While most USB host controllers implement their registers in
 * little-endian format, a minority (celleb companion chip) implement
 * them in big endian format.
 *
 * This attempts to support either format at compile time without a
 * runtime penalty, or both formats with the additional overhead
 * of checking a flag bit.
 *
 * ehci_big_endian_capbase is a special quirk for controllers that
 * implement the HC capability registers as separate registers and not
 * as fields of a 32-bit register.
 */

#ifdef CONFIG_USB_EHCI_BIG_ENDIAN_MMIO
#define ehci_big_endian_mmio(e)     ((e)->big_endian_mmio)
#define ehci_big_endian_capbase(e)  ((e)->big_endian_capbase)
#else
#define ehci_big_endian_mmio(e)     0
#define ehci_big_endian_capbase(e)  0
#endif

/*
 * Big-endian read/write functions are arch-specific.
 * Other arches can be added if/when they're needed.
 */
//#if defined(CONFIG_ARM) && defined(CONFIG_ARCH_IXP4XX)
//#define readl_be(addr)        __raw_readl((__force unsigned *)addr)
//#define writel_be(val, addr)  __raw_writel(val, (__force unsigned *)addr)
//#endif
//
//static inline unsigned int ehci_readl(const struct ehci_hcd *ehci,
//      __u32  *regs)
//{
//  return readl(regs);
//}
//
//#ifdef CONFIG_SOC_IMX28
//static inline void imx28_ehci_writel(const unsigned int val,
//      volatile __u32 __iomem *addr)
//{
//  __asm__ ("swp %0, %0, [%1]" : : "r"(val), "r"(addr));
//}
//#else
//static inline void imx28_ehci_writel(const unsigned int val,
//      volatile __u32 __iomem *addr)
//{
//}
//#endif
//static inline void ehci_writel(const struct ehci_hcd *ehci,
//      const unsigned int val, __u32 __iomem *regs)
//{
//#ifdef CONFIG_USB_EHCI_BIG_ENDIAN_MMIO
//  ehci_big_endian_mmio(ehci) ?
//      writel_be(val, regs) :
//      writel(val, regs);
//#else
//  if (ehci->imx28_write_fix)
//      imx28_ehci_writel(val, regs);
//  else
//      writel(val, regs);
//#endif
//}
static inline void set_ohci_hcfs(struct ehci_hcd *ehci, int operational)
{ }

/* cpu to ehci */
static inline uint32_t cpu_to_hc32(const struct ehci_hcd *ehci, const u32 x)
{
    return cpu_to_le32(x);
}

/* ehci to cpu */
static inline u32 hc32_to_cpu(const struct ehci_hcd *ehci, const uint32_t x)
{
    return le32_to_cpu(x);
}

static inline uint32_t hc32_to_cpup(const struct ehci_hcd *ehci, const uint32_t *x)
{
    return le32_to_cpup(x);
}


#define ehci_dbg(fmt, args...) \
    hal_log_debug(fmt, ## args)
#define ehci_err(fmt, args...) \
    hal_log_err(fmt, ## args)
#define ehci_info(fmt, args...) \
    hal_log_info(fmt, ## args)
#define ehci_warn(fmt, args...) \
    hal_log_warn(fmt, ## args)
/*-------------------------------------------------------------------------*/
/*
#define ehci_dbg(ehci, fmt, args...) \
      dev_dbg(ehci_to_hcd(ehci)->self.controller, fmt, ## args)
#define ehci_err(ehci, fmt, args...) \
      dev_err(ehci_to_hcd(ehci)->self.controller, fmt, ## args)
#define ehci_info(ehci, fmt, args...) \
      dev_info(ehci_to_hcd(ehci)->self.controller, fmt, ## args)
#define ehci_warn(ehci, fmt, args...) \
    dev_warn(ehci_to_hcd(ehci)->self.controller, fmt, ## args)
*/
/*-------------------------------------------------------------------------*/

/* Declarations of things exported for use by ehci platform drivers */

struct ehci_driver_overrides {
    size_t      extra_priv_size;
    int     (*reset)(struct hc_gen_dev *hcd);
    int     (*port_power)(struct hc_gen_dev *hcd,
                int portnum, bool enable);
};

extern void ehci_init_driver(struct hc_driver *drv,
                const struct ehci_driver_overrides *over);
extern int  ehci_setup(struct hc_gen_dev *hcd);
extern int  ehci_handshake(struct ehci_hcd *ehci, u32 *ptr,
                u32 mask, u32 done, int usec);
extern int  ehci_reset(struct ehci_hcd *ehci);

extern int  ehci_suspend(struct hc_gen_dev *hcd, bool do_wakeup);
extern int  ehci_resume(struct hc_gen_dev *hcd, bool force_reset);
extern void ehci_adjust_port_wakeup_flags(struct ehci_hcd *ehci,
            bool suspending, bool do_wakeup);

extern int  ehci_hub_control(struct hc_gen_dev *hcd, u16 typeReq, u16 wValue,
                 u16 wIndex, char *buf, u16 wLength);

void ehci_stop (struct hc_gen_dev *hcd);
int ehci_init(struct hc_gen_dev *hcd);
int ehci_halt (struct ehci_hcd *ehci);
void ehci_work (struct ehci_hcd *ehci);
int ehci_run (struct hc_gen_dev *hcd);
int ehci_urb_enqueue (struct hc_gen_dev *hcd, struct urb *urb, unsigned mem_flags);
int ehci_urb_dequeue(struct hc_gen_dev *hcd, struct urb *urb);
int ehci_get_frame (struct hc_gen_dev *hcd);
void ehci_endpoint_disable (struct hc_gen_dev *hcd, struct usb_host_virt_endpoint *ep);
int ehci_hub_status_data (struct hc_gen_dev *hcd, char *buf);
int ehci_bus_suspend (struct hc_gen_dev *hcd);
int ehci_bus_resume (struct hc_gen_dev *hcd);
irqreturn_t ehci_irq_handler (int dummy, void *dev);

int sunxi_ehci_hcd_init(int hci_num);
int sunxi_ehci_hcd_deinit(int hci_num);

#endif /* __LINUX_EHCI_HCD_H */
