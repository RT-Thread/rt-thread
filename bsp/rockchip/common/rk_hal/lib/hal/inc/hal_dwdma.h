/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2019-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

#ifdef HAL_DWDMA_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup DWDMA
 *  @{
 */

#ifndef _HAL_DWDMA_H
#define _HAL_DWDMA_H

#include "hal_def.h"

/** @defgroup DWDMA_Exported_Definition_Group1 Basic Definition
 *  @{
 */

/***************************** MACRO Definition ******************************/

#define NR_DESCS_PER_CHANNEL 8
#define DMA_MAX_CHANNELS     8

/* Bitfields in CTL_LO */
#define DWC_CTLL_INT_EN       (1 << 0)    /**< irqs enabled? */
#define DWC_CTLL_DST_WIDTH(n) ((n)<<1)    /**< bytes per element */
#define DWC_CTLL_SRC_WIDTH(n) ((n)<<4)
#define DWC_CTLL_DST_INC      (0<<7)        /**< DAR update/not */
#define DWC_CTLL_DST_DEC      (1<<7)
#define DWC_CTLL_DST_FIX      (2<<7)
#define DWC_CTLL_SRC_INC      (0<<7)        /**< SAR update/not */
#define DWC_CTLL_SRC_DEC      (1<<9)
#define DWC_CTLL_SRC_FIX      (2<<9)
#define DWC_CTLL_DST_MSIZE(n) ((n)<<11)    /**< burst, \#elements */
#define DWC_CTLL_SRC_MSIZE(n) ((n)<<14)
#define DWC_CTLL_S_GATH_EN    (1 << 17)    /**< src gather, !FIX */
#define DWC_CTLL_D_SCAT_EN    (1 << 18)    /**< dst scatter, !FIX */
#define DWC_CTLL_FC(n)        ((n) << 20)
#define DWC_CTLL_FC_M2M       (0 << 20)    /**< mem-to-mem */
#define DWC_CTLL_FC_M2P       (1 << 20)    /**< mem-to-periph */
#define DWC_CTLL_FC_P2M       (2 << 20)    /**< periph-to-mem */
#define DWC_CTLL_FC_P2P       (3 << 20)    /**< periph-to-periph */
/* plus 4 transfer types for peripheral-as-flow-controller */
#define DWC_CTLL_DMS(n)   ((n)<<23)    /**< dst master select */
#define DWC_CTLL_SMS(n)   ((n)<<25)    /**< src master select */
#define DWC_CTLL_LLP_D_EN (1 << 27)    /**< dest block chain */
#define DWC_CTLL_LLP_S_EN (1 << 28)    /**< src block chain */

/* Bitfields in CTL_HI */
#define DWC_CTLH_DONE          0x00001000
#define DWC_CTLH_BLOCK_TS_MASK 0x00000fff

/* Bitfields in CFG_LO */
#define DWC_CFGL_CH_PRIOR_MASK  (0x7 << 5)    /**< priority mask */
#define DWC_CFGL_CH_PRIOR(x)    ((x) << 5)    /**< priority */
#define DWC_CFGL_CH_SUSP        (1 << 8)    /**< pause xfer */
#define DWC_CFGL_FIFO_EMPTY     (1 << 9)    /**< pause xfer */
#define DWC_CFGL_HS_DST         (1 << 10)    /**< handshake w/dst */
#define DWC_CFGL_HS_SRC         (1 << 11)    /**< handshake w/src */
#define DWC_CFGL_LOCK_CH_XFER   (0 << 12)    /**< scope of LOCK_CH */
#define DWC_CFGL_LOCK_CH_BLOCK  (1 << 12)
#define DWC_CFGL_LOCK_CH_XACT   (2 << 12)
#define DWC_CFGL_LOCK_BUS_XFER  (0 << 14)    /**< scope of LOCK_BUS */
#define DWC_CFGL_LOCK_BUS_BLOCK (1 << 14)
#define DWC_CFGL_LOCK_BUS_XACT  (2 << 14)
#define DWC_CFGL_LOCK_CH        (1 << 15)    /**< channel lockout */
#define DWC_CFGL_LOCK_BUS       (1 << 16)    /**< busmaster lockout */
#define DWC_CFGL_HS_DST_POL     (1 << 18)    /**< dst handshake active low */
#define DWC_CFGL_HS_SRC_POL     (1 << 19)    /**< src handshake active low */
#define DWC_CFGL_MAX_BURST(x)   ((x) << 20)
#define DWC_CFGL_RELOAD_SAR     (1 << 30)
#define DWC_CFGL_RELOAD_DAR     (1 << 31)

/* Bitfields in CFG_HI */
#define DWC_CFGH_FCMODE     (1 << 0)
#define DWC_CFGH_FIFO_MODE  (1 << 1)
#define DWC_CFGH_PROTCTL(x) ((x) << 2)
#define DWC_CFGH_DS_UPD_EN  (1 << 5)
#define DWC_CFGH_SS_UPD_EN  (1 << 6)
#define DWC_CFGH_SRC_PER(x) ((x) << 7)
#define DWC_CFGH_DST_PER(x) ((x) << 11)

/* Bitfields in SGR */
#define DWC_SGR_SGI(x) ((x) << 0)
#define DWC_SGR_SGC(x) ((x) << 20)

/* Bitfields in DSR */
#define DWC_DSR_DSI(x) ((x) << 0)
#define DWC_DSR_DSC(x) ((x) << 20)

/* Bitfields in CFG */
#define DW_CFG_DMA_EN (1 << 0)

/* bursts size */
typedef enum {
    DWDMA_MSIZE_1,
    DWDMA_MSIZE_4,
    DWDMA_MSIZE_8,
    DWDMA_MSIZE_16,
    DWDMA_MSIZE_32,
    DWDMA_MSIZE_64,
    DWDMA_MSIZE_128,
    DWDMA_MSIZE_256,
} eDWDMA_MSIZE;

/***************************** Structure Definition **************************/

/**
 * LLI == Linked List Item; a.k.a. DMA block descriptor
 */
struct DW_LLI {
    uint32_t sar; /**< values that are not changed by hardware */
    uint32_t dar; /**< values that are not changed by hardware */
    uint32_t llp; /**< chain to next lli */
    uint32_t ctllo;
    uint32_t ctlhi;

    uint32_t sstat; /**< values that may get written back. */
    uint32_t dstat; /**< values that may get written back. */
};

/**
 * struct DW_DESC - dma transfer desc
 */
struct DW_DESC {
    struct DW_LLI lli; /**< FIRST values the hardware uses, must be in the first place. */

    uint32_t len;
};

/**
 * struct DWDMA_CHAN - dw dma channel.
 */
struct DWDMA_CHAN {
    struct HAL_DWDMA_DEV *dw;
    struct DMA_CHAN_REGS *creg;
    struct DMA_SLAVE_CONFIG config;
    struct DW_DESC *desc;
    eDMA_TRANSFER_DIRECTION direction;

    uint8_t mask;
    uint8_t srcMaster;
    uint8_t dstMaster;
    uint8_t periId;
    uint8_t chanId;

    bool cyclic;
    bool paused;

    DMA_Callback callback;
    void *cparam;
};

/**
 * struct HAL_DWDMA_DEV - dw dma hal dev.
 */
struct HAL_DWDMA_DEV {
    struct DMA_REG *pReg;
    struct DWDMA_CHAN chan[DMA_MAX_CHANNELS];
    uint8_t irq[DMA_MAX_CHANNELS];
    uint8_t allChanMask;
    uint8_t used;
    uint8_t maxChans;
    /* hardware configuration */
    uint8_t dataWidth;
    uint32_t blockSize;

    void *priv;
};

/** @} */

/***************************** Function Declare ******************************/
/** @defgroup DWDMA_Public_Function_Declare Public Function Declare
 *  @{
 */

uint32_t HAL_DWDMA_GetRawBlockStatus(struct HAL_DWDMA_DEV *dw);
uint32_t HAL_DWDMA_GetRawErrStatus(struct HAL_DWDMA_DEV *dw);
uint32_t HAL_DWDMA_GetRawXferStatus(struct HAL_DWDMA_DEV *dw);

HAL_Status HAL_DWDMA_Init(struct HAL_DWDMA_DEV *dw);
HAL_Status HAL_DWDMA_DeInit(struct HAL_DWDMA_DEV *dw);

HAL_Status HAL_DWDMA_Start(struct DWDMA_CHAN *dwc);
HAL_Status HAL_DWDMA_Stop(struct DWDMA_CHAN *dwc);
HAL_Status HAL_DWDMA_Pause(struct DWDMA_CHAN *dwc);
HAL_Status HAL_DWDMA_Resume(struct DWDMA_CHAN *dwc);

struct DWDMA_CHAN *HAL_DWDMA_RequestChannel(struct HAL_DWDMA_DEV *dma, DMA_REQ_Type id);
HAL_Status HAL_DWDMA_ReleaseChannel(struct DWDMA_CHAN *dwc);

HAL_Status HAL_DWDMA_Config(struct DWDMA_CHAN *dwc, struct DMA_SLAVE_CONFIG *config);
HAL_Status HAL_DWDMA_PrepDmaMemcpy(struct DWDMA_CHAN *dwc, uint32_t dst,
                                   uint32_t src, uint32_t len,
                                   DMA_Callback callback, void *cparam);
HAL_Status HAL_DWDMA_PrepDmaCyclic(struct DWDMA_CHAN *dwc, uint32_t dmaAddr,
                                   uint32_t len, uint32_t periodLen,
                                   eDMA_TRANSFER_DIRECTION direction,
                                   DMA_Callback callback, void *cparam);
HAL_Status HAL_DWDMA_PrepDmaSingle(struct DWDMA_CHAN *dwc, uint32_t dmaAddr,
                                   uint32_t len,
                                   eDMA_TRANSFER_DIRECTION direction,
                                   DMA_Callback callback, void *cparam);

uint32_t HAL_DWDMA_IrqHandler(struct HAL_DWDMA_DEV *dw, uint32_t chanId);
uint32_t HAL_DWDMA_HandleChan(struct HAL_DWDMA_DEV *dw, uint32_t chanId);
struct DWDMA_CHAN *HAL_DWDMA_GetChannel(struct HAL_DWDMA_DEV *dw, uint32_t chanId);

/** @} */

#endif

/** @} */

/** @} */

#endif /* HAL_DWDMA_MODULE_ENABLED */
