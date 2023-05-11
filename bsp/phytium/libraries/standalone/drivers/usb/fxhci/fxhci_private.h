/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fxhci_private.h
 * Date: 2022-02-11 13:33:12
 * LastEditTime: 2022-02-18 09:16:44
 * Description:  This files is for definition of XHCI internal function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#ifndef  FXHCI_PRIVATE_H
#define  FXHCI_PRIVATE_H

/***************************** Include Files *********************************/
#include "fusb_private.h"
#include "fxhci_hw.h"
#include "fxhci.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
typedef enum
{
    FXHCI_TRB_NORMAL = 1,
    FXHCI_TRB_SETUP_STAGE = 2,
    FXHCI_TRB_DATA_STAGE = 3,
    FXHCI_TRB_STATUS_STAGE = 4,
    FXHCI_TRB_LINK = 6,
    FXHCI_TRB_EVENT_DATA = 7,
    FXHCI_TRB_CMD_ENABLE_SLOT = 9,
    FXHCI_TRB_CMD_DISABLE_SLOT = 10,
    FXHCI_TRB_CMD_ADDRESS_DEV = 11,
    FXHCI_TRB_CMD_CONFIGURE_EP = 12,
    FXHCI_TRB_CMD_EVAL_CTX = 13,
    FXHCI_TRB_CMD_RESET_EP = 14,
    FXHCI_TRB_CMD_STOP_EP = 15,
    FXHCI_TRB_CMD_SET_TR_DQ = 16,
    FXHCI_TRB_CMD_NOOP = 23,
    FXHCI_TRB_EV_TRANSFER = 32,
    FXHCI_TRB_EV_CMD_CMPL = 33,
    FXHCI_TRB_EV_PORTSC = 34,
    FXHCI_TRB_EV_HOST = 37,
} FXhciTrbType;

enum
{
    FXHCI_TRB_TRT_NO_DATA = 0,
    FXHCI_TRB_TRT_OUT_DATA = 2,
    FXHCI_TRB_TRT_IN_DATA = 3
};

enum
{
    FXHCI_TRB_DIR_OUT = 0,
    FXHCI_TRB_DIR_IN = 1
};

#define FXHCI_TRB_MAX_TD_SIZE    0x1F           /* bits 21:17 of TD Size in TRB */
#define FXHCI_DMA_SIZE          (64 * 1024)
#define FXHCI_TIMEOUT           1000000

enum
{
    FXHCI_EP_ISOC_OUT = 1,
    FXHCI_EP_BULK_OUT = 2,
    FXHCI_EP_INTR_OUT = 3,
    FXHCI_EP_CONTROL = 4,
    FXHCI_EP_ISOC_IN = 5,
    FXHCI_EP_BULK_IN = 6,
    FXHCI_EP_INTR_IN = 7
};

/**************************** Type Definitions *******************************/
typedef volatile struct
{
    u32 ptr_low;
    u32 ptr_high;
    u32 status;
    u32 control;
} FXhciTrb;

typedef struct
{
    FXhciTrb *ring;
    FXhciTrb *cur;
    FXhciTrb *last;
    u8 ccs;
    u8 adv;
} FXhciEvtRing;

typedef struct
{
    FXhciTrb *ring;
    FXhciTrb *cur;
    u8 pcs;
} __attribute__((packed)) FXhciTransRing;

typedef FXhciTransRing FXhciCmdRing;

typedef volatile struct
{
    u32 f1;
    u32 f2;
    u32 f3;
    u32 f4;
    u32 rsvd[4];
} FXhciSlotCtx;

typedef volatile struct
{
    u32 f1;
    u32 f2;
    u32 tr_dq_low;
    u32 tr_dq_high;
    u32 f5;
    u32 rsvd[3];
} FXhciEpCtx;

typedef union
{
    /* set of pointers, so we can dynamically adjust Slot/EP context size */
    struct
    {
        union
        {
            FXhciSlotCtx *slot;
            void *raw;  /* Pointer to the whole dev context. */
        };
        FXhciEpCtx *ep0;
        FXhciEpCtx *eps1_30[FXHCI_NUM_EPS - 2];
    };
    FXhciEpCtx *ep[FXHCI_NUM_EPS];  /* At index 0 it's actually the slotctx,
                                    we have it like that so we can use
                                    the ep_id directly as index. */
} FXhciDevCtx;

typedef struct
{
    union
    {
        /* The drop flags are located at the start of the */
        u32 *drop;  /* structure, so a pointer to them is equivalent */
        void *raw;  /* to a pointer to the whole (raw) input context. */
    };
    u32 *add;
    FXhciDevCtx dev;
} FXhciInputCtx;

typedef struct
{
    u32 seg_base_lo;
    u32 seg_base_hi;
    u32 seg_size;
    u32 rsvd;
} FXhciErstEntry;

typedef struct
{
    size_t size;    /* Size of each transfer */
    size_t count;   /* The number of TRBs to fill at once */
    FXhciTrb *next; /* The next TRB expected to be processed by the controller */
    FXhciTrb *ready;    /* The last TRB in the transfer ring processed by the controller */
    FUsbEndpoint *ep;
} FXhciIntrQ;

typedef struct
{
    FXhciDevCtx ctx;
    FXhciTransRing *transfer_rings[FXHCI_NUM_EPS];
    FXhciIntrQ *interrupt_queues[FXHCI_NUM_EPS];
} FXhciDevInfo;

typedef enum
{
    FXHCI_DMA_SET_ADDR = 0,
    FXHCI_DMA_INPUT_CTX,
    FXHCI_DMA_TRANS_RING,
    FXHCI_DMA_TRANS_RING_TRB,

    FXHCI_MAX_DMA_TYPE
} FXhciDMAType;

typedef struct
{
    FXhciDMAType type;
#define FXHCI_MAX_DMA_ENTRY     10
    void *entries[FXHCI_MAX_DMA_ENTRY];
    uintptr count;
} FXhciDMABuffer;

typedef struct
{
    /* R/W, volatile, Memory -> bitfields allowed */
    u64 *dcbaa; /* pointers to sp_ptrs and output (device) contexts */
    u64 *sp_ptrs;   /* pointers to scratchpad buffers */

    FXhciCmdRing cr;
    FXhciEvtRing er;
    volatile FXhciErstEntry *ev_ring_table;

    FUsbDev *roothub;

    u8 max_slots_en;
    FXhciDevInfo *dev;  /* array of devinfos by slot_id */
    FUsb *usb;
    FXhciMMIO mmio;
} FXhci;
/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FXHCI_MASK(startbit, lenbit) (((1<<(lenbit))-1)<<(startbit))

/* shorcut to access TRB */
#define FXHCI_TRB_PORT_FIELD    ptr_low     /* Pointer field of Port TRB */
#define FXHCI_TRB_PORT_START    24
#define FXHCI_TRB_PORT_LEN      8
#define FXHCI_TRB_TL_FIELD      status      /* TL - Transfer Length */
#define FXHCI_TRB_TL_START      0
#define FXHCI_TRB_TL_LEN        17
#define FXHCI_TRB_EVTL_FIELD    status      /* EVTL - (Event TRB) Transfer Length */
#define FXHCI_TRB_EVTL_START    0
#define FXHCI_TRB_EVTL_LEN      24
#define FXHCI_TRB_TDS_FIELD     status      /* TDS - TD Size */
#define FXHCI_TRB_TDS_START     17
#define FXHCI_TRB_TDS_LEN       5
#define FXHCI_TRB_CC_FIELD      status      /* CC - Completion Code */
#define FXHCI_TRB_CC_START      24
#define FXHCI_TRB_CC_LEN        8
#define FXHCI_TRB_C_FIELD       control     /* C - Cycle Bit */
#define FXHCI_TRB_C_START       0
#define FXHCI_TRB_C_LEN         1
#define FXHCI_TRB_TC_FIELD      control     /* TC - Toggle Cycle */
#define FXHCI_TRB_TC_START      1
#define FXHCI_TRB_TC_LEN        1
#define FXHCI_TRB_ENT_FIELD     control     /* ENT - Evaluate Next TRB */
#define FXHCI_TRB_ENT_START     1
#define FXHCI_TRB_ENT_LEN       1
#define FXHCI_TRB_ISP_FIELD     control     /* ISP - Interrupt-on Short Packet */
#define FXHCI_TRB_ISP_START     2
#define FXHCI_TRB_ISP_LEN       1
#define FXHCI_TRB_CH_FIELD      control     /* CH - Chain Bit */
#define FXHCI_TRB_CH_START      4
#define FXHCI_TRB_CH_LEN        1
#define FXHCI_TRB_IOC_FIELD     control     /* IOC - Interrupt On Completion */
#define FXHCI_TRB_IOC_START     5
#define FXHCI_TRB_IOC_LEN       1
#define FXHCI_TRB_IDT_FIELD     control     /* IDT - Immediate Data */
#define FXHCI_TRB_IDT_START     6
#define FXHCI_TRB_IDT_LEN       1
#define FXHCI_TRB_DC_FIELD      control     /* DC - Deconfigure */
#define FXHCI_TRB_DC_START      9
#define FXHCI_TRB_DC_LEN        1
#define FXHCI_TRB_TT_FIELD      control     /* TT - TRB Type */
#define FXHCI_TRB_TT_START      10
#define FXHCI_TRB_TT_LEN        6
#define FXHCI_TRB_TRT_FIELD     control     /* TRT - Transfer Type */
#define FXHCI_TRB_TRT_START     16
#define FXHCI_TRB_TRT_LEN       2
#define FXHCI_TRB_DIR_FIELD     control     /* DIR - Direction */
#define FXHCI_TRB_DIR_START     16
#define FXHCI_TRB_DIR_LEN       1
#define FXHCI_TRB_EP_FIELD      control     /* EP - Endpoint ID */
#define FXHCI_TRB_EP_START      16
#define FXHCI_TRB_EP_LEN        5
#define FXHCI_TRB_ID_FIELD      control     /* ID - Slot ID */
#define FXHCI_TRB_ID_START      24
#define FXHCI_TRB_ID_LEN        8
#define FXHCI_TRB_MASK(tok)     FXHCI_MASK(FXHCI_TRB_##tok##_START, FXHCI_TRB_##tok##_LEN)
#define FXHCI_TRB_GET(tok, trb) (((trb)->FXHCI_TRB_##tok##_FIELD & FXHCI_TRB_MASK(tok)) \
                                 >> FXHCI_TRB_##tok##_START)
#define FXHCI_TRB_SET(tok, trb, to) (trb)->FXHCI_TRB_##tok##_FIELD = \
        (((trb)->FXHCI_TRB_##tok##_FIELD & ~FXHCI_TRB_MASK(tok)) | \
         (((to) << FXHCI_TRB_##tok##_START) & FXHCI_TRB_MASK(tok)))
#define FXHCI_TRB_DUMP(dumper, tok, trb)    dumper(" "#tok"\t0x%04x ", FXHCI_TRB_GET(tok, trb))

#define FXHCI_TRB_CYCLE     (1 << 0)

/* shortcut to access slot context */
#define FXHCI_SC_ROUTE_FIELD        f1      /* ROUTE - Route String */
#define FXHCI_SC_ROUTE_START        0
#define FXHCI_SC_ROUTE_LEN          20
#define FXHCI_SC_SPEED1_FIELD       f1      /* SPEED - Port speed plus one (compared to FUsbSpeed enum) */
#define FXHCI_SC_SPEED1_START       20
#define FXHCI_SC_SPEED1_LEN         4
#define FXHCI_SC_MTT_FIELD          f1      /* MTT - Multi Transaction Translator */
#define FXHCI_SC_MTT_START          25
#define FXHCI_SC_MTT_LEN            1
#define FXHCI_SC_HUB_FIELD          f1      /* HUB - Is this a hub? */
#define FXHCI_SC_HUB_START          26
#define FXHCI_SC_HUB_LEN            1
#define FXHCI_SC_CTXENT_FIELD       f1      /* CTXENT - Context Entries (number of following ep contexts) */
#define FXHCI_SC_CTXENT_START       27
#define FXHCI_SC_CTXENT_LEN         5
#define FXHCI_SC_RHPORT_FIELD       f2      /* RHPORT - Root Hub Port Number */
#define FXHCI_SC_RHPORT_START       16
#define FXHCI_SC_RHPORT_LEN         8
#define FXHCI_SC_NPORTS_FIELD       f2      /* NPORTS - Number of Ports */
#define FXHCI_SC_NPORTS_START       24
#define FXHCI_SC_NPORTS_LEN         8
#define FXHCI_SC_TTID_FIELD         f3      /* TTID - TT Hub Slot ID */
#define FXHCI_SC_TTID_START         0
#define FXHCI_SC_TTID_LEN           8
#define FXHCI_SC_TTPORT_FIELD       f3      /* TTPORT - TT Port Number */
#define FXHCI_SC_TTPORT_START       8
#define FXHCI_SC_TTPORT_LEN         8
#define FXHCI_SC_TTT_FIELD          f3      /* TTT - TT Think Time */
#define FXHCI_SC_TTT_START          16
#define FXHCI_SC_TTT_LEN            2
#define FXHCI_SC_UADDR_FIELD        f4      /* UADDR - USB Device Address */
#define FXHCI_SC_UADDR_START        0
#define FXHCI_SC_UADDR_LEN          8
#define FXHCI_SC_STATE_FIELD        f4      /* STATE - Slot State */
#define FXHCI_SC_STATE_START        27
#define FXHCI_SC_STATE_LEN          5
#define FXHCI_SC_MASK(tok)          FXHCI_MASK(FXHCI_SC_##tok##_START, FXHCI_SC_##tok##_LEN)
#define FXHCI_SC_GET(tok, sc)       (((sc)->FXHCI_SC_##tok##_FIELD & FXHCI_SC_MASK(tok)) \
                                     >> FXHCI_SC_##tok##_START)
#define FXHCI_SC_SET(tok, sc, to)   (sc)->FXHCI_SC_##tok##_FIELD = \
        (((sc)->FXHCI_SC_##tok##_FIELD & ~FXHCI_SC_MASK(tok)) | \
         (((to) << FXHCI_SC_##tok##_START) & FXHCI_SC_MASK(tok)))
#define FXHCI_SC_DUMP(dumper, tok, sc)  dumper(" "#tok"\t0x%04x ", FXHCI_SC_GET(tok, sc))

/* shortcut to access endpoint context */
#define FXHCI_EC_STATE_FIELD        f1      /* STATE - Endpoint State */
#define FXHCI_EC_STATE_START        0
#define FXHCI_EC_STATE_LEN          3
#define FXHCI_EC_INTVAL_FIELD       f1      /* INTVAL - Interval */
#define FXHCI_EC_INTVAL_START       16
#define FXHCI_EC_INTVAL_LEN         8
#define FXHCI_EC_CERR_FIELD         f2      /* CERR - Error Count */
#define FXHCI_EC_CERR_START         1
#define FXHCI_EC_CERR_LEN           2
#define FXHCI_EC_TYPE_FIELD         f2      /* TYPE - EP Type */
#define FXHCI_EC_TYPE_START         3
#define FXHCI_EC_TYPE_LEN           3
#define FXHCI_EC_MBS_FIELD          f2      /* MBS - Max Burst Size */
#define FXHCI_EC_MBS_START          8
#define FXHCI_EC_MBS_LEN            8
#define FXHCI_EC_MPS_FIELD          f2      /* MPS - Max Packet Size */
#define FXHCI_EC_MPS_START          16
#define FXHCI_EC_MPS_LEN            16
#define FXHCI_EC_DCS_FIELD          tr_dq_low   /* DCS - Dequeue Cycle State */
#define FXHCI_EC_DCS_START          0
#define FXHCI_EC_DCS_LEN            1
#define FXHCI_EC_AVRTRB_FIELD       f5      /* AVRTRB - Average TRB Length */
#define FXHCI_EC_AVRTRB_START       0
#define FXHCI_EC_AVRTRB_LEN         16
#define FXHCI_EC_MXESIT_FIELD       f5      /* MXESIT - Max ESIT Payload */
#define FXHCI_EC_MXESIT_START       16
#define FXHCI_EC_MXESIT_LEN         16
#define FXHCI_EC_BPKTS_FIELD        rsvd[0]     /* BPKTS - packets tx in scheduled uframe */
#define FXHCI_EC_BPKTS_START        0
#define FXHCI_EC_BPKTS_LEN          6
#define FXHCI_EC_BBM_FIELD          rsvd[0]     /* BBM - burst mode for scheduling */
#define FXHCI_EC_BBM_START          11
#define FXHCI_EC_BBM_LEN            1

#define FXHCI_EC_MASK(tok)          FXHCI_MASK(FXHCI_EC_##tok##_START, FXHCI_EC_##tok##_LEN)
#define FXHCI_EC_GET(tok, ec)       (((ec)->FXHCI_EC_##tok##_FIELD & FXHCI_EC_MASK(tok)) \
                                     >> FXHCI_EC_##tok##_START)
#define FXHCI_EC_SET(tok, ec, to)   (ec)->FXHCI_EC_##tok##_FIELD = \
        (((ec)->FXHCI_EC_##tok##_FIELD & ~FXHCI_EC_MASK(tok)) | \
         (((to) << FXHCI_EC_##tok##_START) & FXHCI_EC_MASK(tok)))
#define FXHCI_EC_DUMP(dumper, tok, ec)  dumper(" "#tok"\t0x%04x ", FXHCI_EC_GET(tok, ec))

/* the current operational state of the endpoint. */
enum
{
    FXHCI_EC_STATE_DISABLED = 0, /*  endpoint is not operational */
    FXHCI_EC_STATE_RUNNING = 1, /* endpoint is operational */
    FXHCI_EC_STATE_HALTED = 2, /* endpoint is halted due to a Halt condition detected on the USB */
    FXHCI_EC_STATE_STOPPED = 3, /* endpoint is not running due to a Stop Endpoint Command */
    FXHCI_EC_STATE_ERROR = 4 /* endpoint is not running due to a TRB Error */
};

#define FXHCI_INST_GET(controller) ((FXhci*)((controller)->instance))

static inline int FXhciEpId(const FUsbEndpoint *const ep)
{
    /* calculate endpoint ID (Device Context Index (DCI)) The range of DCI values is 0 to 31.
     *      For Isoch, Interrupt, or Bulk type endpoints
     *          DCI = (Endpoint Number * 2) + Direction ,  Direction = ‘0’ for OUT  ‘1’ for IN
     *      For Control type endpoints
     *          DCI = (Endpoint Number * 2) + 1.
    */
    return ((ep->endpoint & 0x7f) * 2) + (ep->direction != FUSB_OUT);
}

#define FXHCI_EP0_ID            1

/************************** Function Prototypes ******************************/
/* 初始化Roothub */
void FXhciRootHubInit(FUsbDev *dev);

/* 分配一段对齐的内存 */
void *FXhciAlign(FXhci *xhci, const size_t min_align, const size_t size);

/* 初始化TRB ring */
void FXhciInitCycleRing(FXhciTransRing *ring, const size_t ring_size);

/* 设备USB设备的地址 */
FUsbDev *FXhciSetAddress(FUsbHc *hc, FUsbSpeed speed, int hubport, int hubaddr);

/* 完成USB设备配置 */
FXhciTransCode FXhciFinishDevConfig(FUsbDev *hc);

/* 删除指定USB设备实例 */
void FXhciDestoryDev(FUsbHc *xhci, int slot_id);

/* 重置Event TRB ring */
void FXhciResetEvtRing(FXhciEvtRing *ring);

void FXhciAdvanceEvtRing(FXhci *xhci);
void FXhciUpdateEvtDQ(FXhci *xhci);
void FXhciHandleEvts(FXhci *xhci);

FXhciTransCode FXhciWaitForCmdAborted(FXhci *xhci, const FXhciTrb *trb);
FXhciTransCode FXhciWaitForCmdDone(FXhci *xhci, const FXhciTrb *trb, int clear_event);
FXhciTransCode FXhciWaitForTransfer(FXhci *xhci, const int slot_id, const int ep_id);

void FXhciClearTrb(FXhciTrb *trb, int pcs);
FXhciTrb *FXhciNextCmdTrb(FXhci *xhci);
void FXhciPostCmd(FXhci *xhci);

FXhciTransCode FXhciCmdNop(FXhci *const xhci);
FXhciTransCode FXhciCmdEnableSlot(FXhci *xhci, int *slot_id);
FXhciTransCode FXhciCmdDisableSlot(FXhci *xhci, int slot_id);
FXhciTransCode FXhciCmdAddressDevice(FXhci *xhci, int slot_id, FXhciInputCtx *ctx);
FXhciTransCode FXhciCmdConfigureEp(FXhci *xhci, int slot_id, int config_id, FXhciInputCtx *ctx);
FXhciTransCode FXhciCmdEvaluateCtx(FXhci *xhci, int slot_id, FXhciInputCtx *ctx);
FXhciTransCode FXhciCmdResetEp(FXhci *xhci, int slot_id, int ep);
FXhciTransCode FXhciCmdStopEp(FXhci *xhci, int slot_id, int ep);
FXhciTransCode FXhciCmdSetTrDq(FXhci *xhci, int slot_id, int ep, FXhciTrb *trb, int dcs);

void FXhciDumpSlotCtx(const FXhciSlotCtx *ctx);
void FXhciDumpEpCtx(const FXhciEpCtx *ctx);
void FXhciDumpDevCtx(const FXhciDevCtx *ctx, const u32 ctx_mask);
void FXhciDumpInputCtx(const FXhciInputCtx *ctx);
void FXhciDumpTransferTrb(const FXhciTrb *trb);
void FXhciDumpTransferTrbs(const FXhciTrb *first, const FXhciTrb *last);


/* 支持带TAG的内存分配，用于跟踪动态内存使用 */
#ifdef FMEMP_TAG_DEBUG
void *FXhciAlignTag(FXhci *const xhci, const size_t min_align, const size_t size, const char *file, unsigned long line, const char *msg);

#define FXHCI_ALIGN(xhci, min_align, size)  FXhciAlignTag((xhci), (min_align), (size), __FILE__, __LINE__, "")
#else

#define FXHCI_ALIGN(xhci, min_align, size)  FXhciAlign((xhci), (min_align), (size))
#endif

#ifdef __cplusplus
}
#endif


#endif
